;; Based on beta-mode for GNU Emacs

;; (autoload 'run-mode "~beta/emacs/current/run-mode")
;; (setq auto-mode-alist (append (list (cons "\\.run$" 'run-mode))
;;                               auto-mode-alist))

(defvar run-mode-abbrev-table nil
  "Abbrev table in use in run-mode buffers.")
(define-abbrev-table 'run-mode-abbrev-table ())

(defvar run-mode-map ()
  "Keymap used in Run mode.")
(if run-mode-map
    ()
  (setq run-mode-map (make-sparse-keymap))
  ;;(define-key run-mode-map "<" 'run-open-pattern)
  ;;(define-key run-mode-map ">" 'run-close-pattern)
  (define-key run-mode-map "\177" 'backward-delete-char-untabify)
  (define-key run-mode-map "\t" 'run-tab)
  (define-key run-mode-map "\^m" 'run-newline))

(autoload 'c-macro-expand "cmacexp"
  "Display the result of expanding all C macros occurring in the region.
The expansion is entirely correct because it uses the C preprocessor."
  t)

(defvar run-mode-syntax-table nil
  "Syntax table in use in run-mode buffers.")

(if run-mode-syntax-table
    ()
  (setq run-mode-syntax-table (make-syntax-table (standard-syntax-table)))
  (modify-syntax-entry ?\( "()1" run-mode-syntax-table)
  (modify-syntax-entry ?\) ")(4" run-mode-syntax-table)
;;;  (modify-syntax-entry ?\( ". 1" run-mode-syntax-table)
;;;  (modify-syntax-entry ?\) ". 4" run-mode-syntax-table)
  (modify-syntax-entry ?* ". 23" run-mode-syntax-table)
  (modify-syntax-entry ?% "." run-mode-syntax-table)
  (modify-syntax-entry ?{ "(}" run-mode-syntax-table)
  (modify-syntax-entry ?} "){" run-mode-syntax-table)
  (modify-syntax-entry ?& "." run-mode-syntax-table)
  (modify-syntax-entry ?+ "." run-mode-syntax-table)
  (modify-syntax-entry ?- "." run-mode-syntax-table)
  (modify-syntax-entry ?/ "." run-mode-syntax-table)
  (modify-syntax-entry ?< "." run-mode-syntax-table)
  (modify-syntax-entry ?= "." run-mode-syntax-table)
  (modify-syntax-entry ?> "." run-mode-syntax-table)
  (modify-syntax-entry ?| "." run-mode-syntax-table)
  (modify-syntax-entry ?@ "." run-mode-syntax-table)
)

(defconst run-indent-level 3
  "*Indentation of Run statements with respect to containing block.")

(defconst run-separator-indent-level 0
  "*Indentation of enter-, do-, and exit-lines with respect to containing
block.")

(defconst run-case-indent-level 1
  "*Indentation of //-lines in if-blocks with respect to containing
if block.")

(defconst run-else-indent-level 1
  "*Indentation of else-lines in if-blocks with respect to containing
if block.")

(defconst run-below-separator-indent 0
  "*Extra indentation of statements belonging to the enter-, do-, or
exit-part of a pattern. /, repeat are handled as separators
as well.")

(defconst run-block-indent-level 2
  "*Extra indentation of a new block, with respect to the containing block.")

(defconst run-evaluation-indent-level 2
  "*Extra indentation of a line beginning with '->', with respect to the 
containing block.")

(defconst run-tab-to-comment nil
  "*Non-nil means that a TAB at the end of a non-empty line will start
a comment at beginning at comment-column.")

(defconst run-auto-indent t
  "*Non-nil means that NEWLINE at the end of a line will auto-indent to
the 'correct' position on the new line.")

(defconst run-combined-indent t
  "*If non-nil, multiple closing constructors  on the same line
(e.g. if)for)#) ) will be indented relative to the opening constructor 
corresponding to the *last* closing constructor")

(defconst run-comment-indent-level 2
  "*Indentation of comment-lines after the first one.")

(defconst run-if-indent-level 4
  "*Indentation of statements within an if-block, with respect to
the \(if block.")

(defconst run-code-indent-level 3
  "*Indentation of statements within a code-block, with respect to
the \(for block.")

(defconst run-for-indent-level 5
  "*Indentation of statements within a for-block, with respect to
the \(for block.")

(defun run-mode ()
  "Major mode for editing RUN code.

Tab indents the current line of RUN code.
To get an ordinary tab-character use C-q TAB
<Return> indents the current line and the new line.
A \{ opens a new pattern \(#.
A \} closes the innermost construct with the appropriate end marker like
#\) or if\).
<Delete> converts tabs to spaces as it moves back.

RUN-comments:
==============

Comments are delimited with { ... }.

Local key map:
==============
\\{run-mode-map}
Variables controlling indentation style:
========================================

 run-tab-to-comment
    Non-nil means that for lines which don't need indenting, TAB will
    either delete an empty comment, indent an existing comment, move 
    to end-of-line, or if at end-of-line already, create a new comment.
 run-auto-indent
    Non-nil means that NEWLINE at the end of a line will auto-indent to
    the 'correct' position on the new line.
 run-indent-level
    Indentation of RUN statements within surrounding block.
    The surrounding block's indentation is the indentation
    of the line on which an open-construct like \(# or \(for appears.
 run-separator-indent-level
    Indentation of an enter-, do- or exit-line with respect
    to the containing block.
 run-case-indent-level
    Indentation of the // lines in if-blocks with respect to the
    containing block.
 run-below-separator-indent
    Extra indentation of lines belonging to the do-, enter- or
    exit-part of a pattern.
 run-comment-indent-level
    Indentation of comment-lines after the first one, with respect
    to the containing block.
 run-if-indent-level
    Indentation of lines within an \(if-block except lines starting
    with // or else.
 run-else-indent-level
   Indentation of else-lines in if-blocks with respect to containing
   if block.
 run-for-indent-level
    Indentation of lines within a for-block.
 run-block-indent-level
    Extra indentation of a new block.
 run-evaluation-indent-level
    Extra indentation of a line beginning with ->.
 run-combined-indent
    If non-nil, multiple closing constructors  on the same line
    (e.g. if)for)#) ) will be indented relative to the opening constructor 
    corresponding to the *last* closing constructor

Invoking run-mode:
===================

Add the following to your .emacs file to automatically go into run-mode when
the name of the buffer ends in \".bet\"

 (autoload 'run-mode \"~run/emacs/current/run\")
 (setq auto-mode-alist (append (list (cons \"\\\\.bet$\" 'run-mode))
                                auto-mode-alist))

run-mode-hook:
===============

Turning on RUN mode calls the value of the variable run-mode-hook with no 
args, if that value is non-nil. For instance, adding the following in your
.emacs file will bind some of the often used functions in RUN mode to
key-sequences prefixed by C-xC-r:

 (defun myrun ()
   \"Make the following local bindings in run-mode:
C-xC-ri calls indent-buffer.\"
   (interactive)
   (local-unset-key \"\\C-x\\C-r\")
   (local-set-key \"\\C-x\\C-ri\" 'indent-buffer))

 (setq run-mode-hook 'myrun) "


  (interactive)
  (kill-all-local-variables)
  (use-local-map run-mode-map)
  (setq major-mode 'run-mode)
  (setq mode-name "Run")
  (setq local-abbrev-table run-mode-abbrev-table)
  (set-syntax-table run-mode-syntax-table)
  (make-local-variable 'paragraph-start)
  (setq paragraph-start (concat "^$\\|" page-delimiter))
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate paragraph-start)
  (make-local-variable 'paragraph-ignore-fill-prefix)
  (setq paragraph-ignore-fill-prefix t)
  (make-local-variable 'indent-line-function)
  (setq indent-line-function 'run-indent-line)
  (make-local-variable 'require-final-newline)
  (setq require-final-newline t)
  (make-local-variable 'comment-start)
  (setq comment-start "{ ")
  (make-local-variable 'comment-end)
  (setq comment-end " }")
  (make-local-variable 'comment-column)
  (setq comment-column 40)
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "\(\\*+ " )
  (make-local-variable 'run-construct-start)
  (setq run-construct-start "\\(\(if\\b\\|\(for\\b\\|\(code\\b\\|\(#\\)")
  (make-local-variable 'run-construct-end)
  (setq run-construct-end "\\(\\bif\)\\|\\bfor\)\\|\\bcode\)\\|#\)\\)")
  (make-local-variable 'run-construct-delimiters)
  ;; this should be both run-construct-start and run-construct-end
  (setq run-construct-delimiters "\\(\(if\\b\\|\\bif\)\\|\(for\\b\\|\\bfor\)\\|\(code\\b\\|\\bcode\)\\|\(#\\|#\)\\)")
  (make-local-variable 'run-separator)
  (setq run-separator "\\(\\bdo\\b\\|\\benter\\b\\|\\bexit\\b\\|//\\|\\belse\\b\\|\\brepeat\\b\\)")
  (make-local-variable 'comment-indent-hook)
  (setq comment-indent-hook 'run-comment-indent)
  (make-local-variable 'parse-sexp-ignore-comments)
  (setq parse-sexp-ignore-comments nil)
  (run-hooks 'run-mode-hook))

;; This is used by indent-for-comment
;; to decide how much to indent a comment in Run code
;; based on its context.
(defun run-comment-indent ()
  (if (and (bolp) (not (eolp)))
      0		;Existing comment at bol stays there.
  (save-excursion
      (skip-chars-backward " \t")
      (max (1+ (current-column))	;Else indent at comment column
	   comment-column))))		; except leave at least one space.

(defun run-indent-to-comment ()
  "Move point to comment-column and start run comment."
  (interactive)
  (indent-to comment-column 1)
  (insert comment-start comment-end)
  (backward-char 2))

;; Run comments cannot be nested
(defun run-within-comment ()
  "Return t if within a Run comment, nil otherwise."
  (interactive)
  (save-excursion
    (if (= (point) 1)
	nil ;; optimization
      (progn
	(if (looking-at "\{") (forward-char 1))
	(re-search-backward "\\(\{\\|\}\\)" 1 t)
	(looking-at "\{")))))

(defun run-newline (arg)
  "Insert a newline and indent current and following line."
  (interactive "P")
  (if run-auto-indent
      (progn
	(newline)
	(save-excursion ;; indent previous line
	  (backward-char 1) 
	  (skip-chars-backward " \t")
	  (run-indent-line))
	(run-indent-line))
    (newline)))

(defun line-no ()
  "Return current line number in buffer"
  (interactive)
  (save-excursion
    (beginning-of-line)
    (1+ (count-lines 1 (point)))))

(defun run-tab ()
  "Indent current line as Run-code.
If at end of line, and run-tab-to-comment is t, then moves to
comment-column, and begins Run comment."
  (interactive)
  (if (and (eolp) (< (current-indentation) (current-column))
	   run-tab-to-comment)
      (run-indent-to-comment))
  (if (<= (current-column) (current-indentation))
      (run-indent-line)
    (save-excursion (run-indent-line))))

;; the main function indenting the current line
(defun run-indent-line ()
  "Indent current line as Run-code."
  (interactive)
  (let ((indent-tabs-mode nil) 
	(ilevel 0) 
	(olevel 0)
	(run-inside-if nil)
	(run-inside-for nil)
	(run-inside-asm nil)
	(beg 0)
	(skip 0)
	(lin 0)
	(after-colon nil))
    (beginning-of-line)
    (setq beg (point))
    (skip-chars-forward " \t")
    (if (and (not (looking-at "\{")) (run-within-comment))
	(progn
	  (save-excursion
	    (goto-char (match-beginning 0))
	    (setq ilevel (current-column)))
	  (if (not (looking-at "\}"))
	      (setq ilevel (+ run-comment-indent-level ilevel)))
	  
	  ;; do the indentation of the comment line
	  (if (>= ilevel (current-column))
	      (indent-to ilevel)
	    (progn
	      (delete-region beg (point))
	      (indent-to ilevel))))
      
      ;; Not within comment
      (progn
	(save-excursion
	  (if run-combined-indent
	      (if (run-ending-constructor-on-line)
		  (progn
		    (setq skip 1)
		    (setq lin (line-no))
		    (end-of-line))
		(progn
		  (setq skip 0)
		  (beginning-of-line)))
	    (progn
	      (setq skip 0)
	      (beginning-of-line)))
	  (run-beginning-of-construct skip)
	  (while (and (= skip 1) (= lin (line-no)))
	    ;; opening construct was on same line, go back one more
	    (run-beginning-of-construct 0))
	  (setq olevel (current-column))
	  (if (= (point) 1)
	      ;; outside any construct
	      (setq ilevel olevel)
	    (setq ilevel (+ run-indent-level olevel)))
	  (if (looking-at "\(if\\b") (setq run-inside-if t))
	  (if (looking-at "\(for\\b") (setq run-inside-for t))
	  (if (looking-at "\(code\\b") (setq run-inside-asm t)))
		
	;; Do the indentation
	(beginning-of-line)
	(setq beg (point))
	(skip-chars-forward " \t")

	(setq after-colon (run-after-colon))
	
	(cond
	 ;; if looking at an //-line use special indentation
	 ((looking-at "//")
	  (setq ilevel (+ ilevel (- run-case-indent-level 
				    run-indent-level))))
	 
	 ;; if looking at an else-line use special indentation
	 ((looking-at "else")
	  (setq ilevel (+ ilevel (- run-else-indent-level 
				    run-indent-level))))
	 
	 ;; if inside an if-block, not looking at '//' or else, use special...
	 (run-inside-if (setq ilevel (+ ilevel (- run-if-indent-level
						   run-indent-level))))
	 
	 ;; if inside a for-block, use special...
	 (run-inside-for (setq ilevel (+ ilevel (- run-for-indent-level
						    run-indent-level))))
	 ;; if inside a code-block, use special...
	 (run-inside-asm (setq ilevel (+ ilevel (- run-code-indent-level
						    run-indent-level))))
	 
	 ;; if looking at an enter-,do- or exit-line use special...
	 ((looking-at "\\(\\benter\\b\\|\\bdo\\b\\|\\bexit\\b\\)")
	  (progn
	    (setq ilevel (+ ilevel (- run-separator-indent-level
				      run-indent-level)))
	    (setq after-colon nil))) ;; No special indentation, see below.
	 ) ;;cond
	
	(cond
	 ;;if positioned at pattern after colon, indent some more.
	 ((and after-colon (looking-at "\(#"))
	  (setq ilevel (+ ilevel run-block-indent-level)))

	 ;; if looking at '->' indent some more
	 ((looking-at "->")
	  (setq ilevel (+ ilevel run-evaluation-indent-level)))
	 
	 ;; if below a separator indent some more.
	 ((and (not (looking-at run-separator))
	       (setq incode (run-below-separator)))
	  (setq ilevel (+ ilevel run-below-separator-indent)))
	 ) ;; cond
	
	;; if a  run-construct-end start the line
	;; don't indent so much
	(if (looking-at run-construct-end)
	    (setq ilevel olevel))
	
	;; do the indentation
	(if (>= ilevel (current-column))
	    (indent-to ilevel)
	  (progn
	    (delete-region beg (point))
	    (indent-to ilevel)))))))

(defun run-ending-constructor-on-line ()
  "Are there any ending constructors on current line?"
  (interactive "p")
  (beginning-of-line)
  (let ( (begin (point)) (result nil) (done nil) )
    (end-of-line)
    (while (not done)
      (setq result (re-search-backward run-construct-end begin 'move))
      (if (not (run-in-pattern-variable)) (setq done t)))
    result))

(defun run-in-pattern-variable ()
  "Are we positioned in between the two #'s in a pattern variable?"
  (interactive)
  (and (looking-at "#")
       (save-excursion
	 (if (and (> (point) 1) (progn (backward-char 1)(looking-at "##")))
	     ;; we are just before two #'s
	     (if (> (point) 1)
		 (progn 
		   (backward-char 1)
		   (not (looking-at "\(##")))
	       ;; There was nothing before the two #'s
	       t)
	   ;; there were not two #'s
	   nil))))
	    
(defun run-beginning-of-construct (&optional arg)
  "Move backward to the beginning of this construct, or to start of buffer.
With argument, ignore that many closing constructors.
Returns new value of point in all cases."
  (interactive "p")
  (or arg (setq arg 0))
  (if (>= arg 0)
      (let ((cnt 0))
	;; cnt is the number of non-matched beginning constructs to skip backwards
	(while (>= cnt 0)
	  (re-search-backward run-construct-delimiters 1 'move)
	  ;; check that it was a real beginning construct:
	  (while (run-within-comment)
	    (re-search-backward run-construct-delimiters 1 'move))
	  (if (= (point) 1)
	      ;; beginning of buffer reached
	      (setq cnt -1)
	    (if (looking-at run-construct-end)
		;; this looks like an ending construct
		(if (not (or (run-in-pattern-variable) (run-within-comment)))
		    ;; looking at a real ending construct
		    (if (> arg 0)
			;; Still some endings left to skip
			(setq arg (1- arg))
		      ;; looking at real ending construct, and no more to skip
		      (setq cnt (1+ cnt))))
	      ;; looking at real beginning construct: one less to match
	      (setq cnt (1- cnt)))))))
  (point))

(defun run-after-colon ()
  "Returns t if point is after a colon, possibly with <, @, ^, white space, 
a prefix and/or a comment in between."
  (interactive)
  (save-excursion
    (beginning-of-line)
    (run-skip-comment-backward)
    (skip-chars-backward " \t\n")
    (skip-chars-backward "A-Za-z0-9().") ;; prefix
    (skip-chars-backward " \t\n<@^|")     ;; whitespace and instantiation
    (if (> (point) 1) (backward-char 1))
    (looking-at ":")))

(defun run-skip-comment-backward ( )
  "Skip backward past { ... }."
  (interactive)
  (skip-chars-backward " \t\n")
  (if (> (point) 2)
      (progn
	(backward-char 2)
	(if (looking-at "\}")
	    (if (not (search-backward "\{" 1 t))
		(forward-char 2))
	  (forward-char 2)))))

(defun run-below-separator ()
  "Returns t if point is below a separator as enter, exit, or //."
  (interactive)
  (save-excursion
    (re-search-backward 
     (concat "\\(" run-separator "\\|"	run-construct-delimiters "\\)")
     nil 'move 1)
    (goto-char (match-beginning 0))
    (while (looking-at run-construct-end)
      (run-beginning-of-construct)
      (re-search-backward 
       (concat "\\(" run-separator "\\|" run-construct-delimiters "\\)")
       nil 'move 1)
      (goto-char (match-beginning 0)))
    (not (looking-at run-construct-start))))

(defun run-open-pattern ()
  "Insert pattern start \(#, and indent line."
  (interactive)
  (insert "\(# ")
  (run-tab))

(defun run-close-pattern ()
  "Insert end marker for current construct, and indent the line."
  (interactive)
  (let ((c ""))
    (if (run-within-comment)
	(save-excursion
	  (setq c "\}")
	  (skip-chars-backward " \t")
	  (if (> (current-column) 1)
	      (progn
		(backward-char 1)
		(if (looking-at "\*")
		    (delete-char 1)))))
      (save-excursion
	(run-beginning-of-construct)
	(cond
	 ((looking-at "\(#")   (setq c "#\)"))
	 ((looking-at "\(for\\b") (setq c "for\)"))
	 ((looking-at "\(if\\b")  (setq c "if\)"))
	 ((looking-at "\(")    (setq c "\)")))))
    (if (equal c "")
	(error "Run-mode error: Not inside construct")
      (insert c))
    (save-excursion
      (beginning-of-line)
      (run-indent-line))))

;;; A generally applicable function:

(defun indent-buffer ( )
  "Indent the whole buffer according to mode."
  (interactive "*")
  (save-excursion
    (message "Indenting the whole buffer ...")
    (indent-region (point-min) (point-max) nil)
    (message "Indenting the whole buffer ... done")))




;;;;;;;; That's all, folks! ;;;;;;;;;
