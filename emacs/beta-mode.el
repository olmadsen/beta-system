;; BETA code editing commands for GNU Emacs.
;;
;; By putting the following lines of Emacs-Lisp code into your .emacs
;; file, you can make Emacs automagically recognize your BETA source code
;; file if they have the suffix .bet, as required by the BETA compiler.

;; (autoload 'beta-mode "/usr/local/lib/beta/emacs/current/beta-mode")
;; (setq auto-mode-alist (append (list (cons "\\.bet$" 'beta-mode))
;;                               auto-mode-alist))
;;
;; When in beta-mode, you can get to know more about beta-mode by using
;; M-x describe-mode.

;; This mode was programmed by Peter |rb{k (poe@daimi.aau.dk).
;; Peter Andersen (datpete@mjolner.dk), Kim Jensen M|ller (kjm@mjolner.dk)
;; Tommy Thorn (tthorn@daimi.au.dk) all contributed with additions, 
;; suggestions and bugfixes.
;; J|rgen Lindskov (jlk@mjolner.dk) provided the comment-justify etc. 
;; functions.
;; Suggestions, bugs etc. may be reported to support@mjolner.dk.

;; This code is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY.  No author or distributor
;; accepts responsibility to anyone for the consequences of using it
;; or for whether it serves any particular purpose or works at all,
;; unless he says so in writing.  Refer to the GNU Emacs General Public
;; License for full details.

;; Everyone is granted permission to copy, modify and redistribute
;; this code, but only under the conditions described in the
;; GNU Emacs General Public License.   A copy of this license is
;; supposed to have been given to you along with GNU Emacs so you
;; can know your rights and responsibilities.  It should be in a
;; file named COPYING.  Among other things, the copyright notice
;; and this notice must be preserved on all copies.

(provide 'beta-mode)

(defvar beta-mode-abbrev-table nil
  "Abbrev table in use in beta-mode buffers.")
(define-abbrev-table 'beta-mode-abbrev-table ())

(defvar beta-mode-map ()
  "Keymap used in beta-mode.")
(if beta-mode-map
    ()
  (setq beta-mode-map (make-sparse-keymap))
  (define-key beta-mode-map "{" 'beta-open-pattern)
  (define-key beta-mode-map "}" 'beta-close-pattern)
  (define-key beta-mode-map ")" 'beta-right-paren)
  (define-key beta-mode-map "\177" 'backward-delete-char-untabify)
  (define-key beta-mode-map "\t" 'beta-tab)
  (define-key beta-mode-map "\^m" 'beta-newline))

(autoload 'c-macro-expand "cmacexp"
  "Display the result of expanding all C macros occurring in the region.
The expansion is entirely correct because it uses the C preprocessor."
  t)

(defvar beta-mode-syntax-table nil
  "Syntax table in use in beta-mode buffers.")

(if beta-mode-syntax-table
    ()
  (setq beta-mode-syntax-table (make-syntax-table (standard-syntax-table)))
  (modify-syntax-entry ?\( "()1" beta-mode-syntax-table)
  (modify-syntax-entry ?\) ")(4" beta-mode-syntax-table)
;;;  (modify-syntax-entry ?\( ". 1" beta-mode-syntax-table)
;;;  (modify-syntax-entry ?\) ". 4" beta-mode-syntax-table)
  (modify-syntax-entry ?* ". 23" beta-mode-syntax-table)
  (modify-syntax-entry ?% "." beta-mode-syntax-table)
  (modify-syntax-entry ?{ "(" beta-mode-syntax-table)
  (modify-syntax-entry ?} ")" beta-mode-syntax-table)
  (modify-syntax-entry ?& "." beta-mode-syntax-table)
  (modify-syntax-entry ?+ "." beta-mode-syntax-table)
  (modify-syntax-entry ?- "." beta-mode-syntax-table)
  (modify-syntax-entry ?_ "w" beta-mode-syntax-table)
  (modify-syntax-entry ?/ "." beta-mode-syntax-table)
  (modify-syntax-entry ?< "." beta-mode-syntax-table)
  (modify-syntax-entry ?= "." beta-mode-syntax-table)
  (modify-syntax-entry ?> "." beta-mode-syntax-table)
  (modify-syntax-entry ?| "." beta-mode-syntax-table)
  (modify-syntax-entry ?@ "." beta-mode-syntax-table)
  (modify-syntax-entry ?' "\"" beta-mode-syntax-table)
  )

(defconst beta-indent-level 3
  "*Indentation of BETA statements with respect to containing block.")

(defconst beta-separator-indent-level 0
  "*Indentation of enter-, do-, and exit-lines with respect to containing
block.")

(defconst beta-case-indent-level 1
  "*Indentation of //-lines in if-blocks with respect to containing
if block.")

(defconst beta-else-indent-level 1
  "*Indentation of else-lines in if-blocks with respect to containing
if block.")

(defconst beta-below-separator-indent 0
  "*Extra indentation of statements belonging to the enter-, do-, or
exit-part of a pattern. /, repeat are handled as separators
as well.")

(defconst beta-block-indent-level 2
  "*Extra indentation of a new block, with respect to the containing block.")

(defconst beta-evaluation-indent-level 2
  "*Extra indentation of a line beginning with '->', with respect to the 
containing block.")

(defconst beta-tab-to-comment nil
  "*Non-nil means that a TAB at the end of a non-empty line will start
a comment at beginning at comment-column.")

(defconst beta-auto-indent t
  "*Non-nil means that NEWLINE at the end of a line will auto-indent to
the 'correct' position on the new line.")

(defconst beta-space-after-star t
  "*Non-nil means, that if beta-auto-indent is t, \"* \" is inserted after NEWLINE within 
comments instead of only \"*\".")

(defconst beta-semicolon-after-closing nil
  "*Non-nil means, that a semicolon is inserted after the closing construction (if needed) by beta-close-pattern")

(defconst beta-combined-indent t
  "*If non-nil, multiple closing constructors  on the same line
(e.g. if)for)#) ) will be indented relative to the opening constructor 
corresponding to the *last* closing constructor")

(defconst beta-comment-indent-level 1
  "*Indentation of comment-lines after the first one.")

(defconst beta-if-indent-level 4
  "*Indentation of statements within an if-block, with respect to
the \(if block.")

(defconst beta-for-indent-level 5
  "*Indentation of statements within a for-block, with respect to
the \(for block.")

(defun beta-mode ()
  "Major mode for editing BETA code.

Tab indents the current line of BETA code.
To get an ordinary tab-character use C-q TAB
<Return> indents the current line and the new line.
A \{ opens a new pattern \(#.
A \} closes the innermost construct with the appropriate end marker like
#\) or if\).
<Delete> converts tabs to spaces as it moves back.

BETA-comments:
==============

Comments are delimited with (* ... *), multiline comments are begin with an 
extra '*'
Four useful functions exist for manipulating comments:
 beta-comment-justify 
   Formats a BETA comment according to the BETA recommandations (i.e. with '*'
   in front of each new line in the comment).  Furthermore, the comment is
   formatted to fill as little as possible. Assumes that the cursor is 
   positioned within a BETA comment.  If not, the first comment found before
   the cursor is justified.  If no comment is found before the cursor position,
   the first comment following the cursor position will be affected.
 beta-comment-justify-region
   Like beta-comment-justify, except that the marked region is expected to be
   part of some BETA comment, and that only that part of the region is to be
   reformatted.
 beta-convert-region-to-comment
   Takes the marked region and surrounds it with BETA comment symbols, and
   formats the new comment according to the BETA comment recommandations.  Any
   comment symbols in the marked region will be converted into {*, 
   respectively *} to avoid spurious problems with nested comments (not 
   supported by the BETA compiler). 
 beta-remove-comment 
   Is the 'inverse' of beta-convert-region-to-comment'.  Removes the BETA
   comment symbols at the either end of the region, restoring any nested 
   comment symbols, enclosed in this comment.

Also the function indent-buffer is supplied as an alternative to indent-region.

Local key map:
==============
\\{beta-mode-map}
Variables controlling indentation style:
========================================

 beta-tab-to-comment
    Non-nil means that for lines which don't need indenting, TAB will
    either delete an empty comment, indent an existing comment, move 
    to end-of-line, or if at end-of-line already, create a new comment.
 beta-auto-indent
    Non-nil means that NEWLINE at the end of a line will auto-indent to
    the 'correct' position on the new line.
 beta-space-after-star
    Non-nil means, that if beta-auto-indent is t, \"* \" is inserted after NEWLINE within 
    comments instead of only \"*\".
 beta-semicolon-after-closing
    Non-nil means that a semicolon is inserted after the closing construction 
   (if needed) by beta-close-pattern.
 beta-indent-level
    Indentation of BETA statements within surrounding block.
    The surrounding block's indentation is the indentation
    of the line on which an open-construct like \(# or \(for appears.
 beta-separator-indent-level
    Indentation of an enter-, do- or exit-line with respect
    to the containing block.
 beta-case-indent-level
    Indentation of the // lines in if-blocks with respect to the
    containing block.
 beta-below-separator-indent
    Extra indentation of lines belonging to the do-, enter- or
    exit-part of a pattern.
 beta-comment-indent-level
    Indentation of comment-lines after the first one, with respect
    to the containing block.
 beta-if-indent-level
    Indentation of lines within an \(if-block except lines starting
    with // or else.
 beta-else-indent-level
   Indentation of else-lines in if-blocks with respect to containing
   if block.
 beta-for-indent-level
    Indentation of lines within a for-block.
 beta-block-indent-level
    Extra indentation of a new block.
 beta-evaluation-indent-level
    Extra indentation of a line beginning with ->.
 beta-combined-indent
    If non-nil, multiple closing constructors  on the same line
    (e.g. if)for)#) ) will be indented relative to the opening constructor 
    corresponding to the *last* closing constructor

Invoking beta-mode:
===================

Add the following to your .emacs file to automatically go into beta-mode when
the name of the buffer ends in \".bet\"

 (autoload 'beta-mode \"/usr/local/lib/beta/emacs/current/beta-mode\")
 (setq auto-mode-alist (append (list (cons \"\\\\.bet$\" 'beta-mode))
                                auto-mode-alist))

beta-mode-hook:
===============

Turning on beta-mode calls the value of the variable beta-mode-hook with no 
args, if that value is non-nil. For instance, adding the following in your
.emacs file will bind some of the often used functions in beta-mode to
key-sequences prefixed by C-xC-r:

 (defun mybeta ()
   \"Make the following local bindings in beta-mode:
C-xC-rj calls beta-comment-justify
C-xC-rr calls beta-comment-justify-region
C-xC-rc calls beta-convert-region-to-comment
C-xC-ru calls beta-remove-comment
C-xC-ri calls indent-buffer.\"
   (interactive)
   (local-unset-key \"\\C-x\\C-r\")
   (local-set-key \"\\C-x\\C-rj\" 'beta-comment-justify)
   (local-set-key \"\\C-x\\C-rr\" 'beta-comment-justify-region)
   (local-set-key \"\\C-x\\C-rc\" 'beta-convert-region-to-comment)
   (local-set-key \"\\C-x\\C-ru\" 'beta-remove-comment)
   (local-set-key \"\\C-x\\C-ri\" 'indent-buffer))

 (setq beta-mode-hook 'mybeta) "


  (interactive)
  (kill-all-local-variables)
  (use-local-map beta-mode-map)
  (setq major-mode 'beta-mode)
  (setq mode-name "BETA")
  (setq local-abbrev-table beta-mode-abbrev-table)
  (set-syntax-table beta-mode-syntax-table)
  (make-local-variable 'beta-mode-version)
  (setq beta-mode-version "v1.6")
  (make-local-variable 'paragraph-start)
  (setq paragraph-start (concat "^$\\|" page-delimiter))
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate paragraph-start)
  (make-local-variable 'paragraph-ignore-fill-prefix)
  (setq paragraph-ignore-fill-prefix t)
  (make-local-variable 'indent-line-function)
  (setq indent-line-function 'beta-indent-line)
  (make-local-variable 'require-final-newline)
  (setq require-final-newline t)
  (make-local-variable 'comment-start)
  (setq comment-start "(* ")
  (make-local-variable 'comment-end)
  (setq comment-end " *)")
  (make-local-variable 'comment-column)
  (setq comment-column 40)
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "\(\\*+ *" )
  (make-local-variable 'beta-construct-start)
  (setq beta-construct-start "\\(\(if\\b\\|\(for\\b\\|\(#\\)")
  (make-local-variable 'beta-construct-end)
  (setq beta-construct-end "\\(\\bif\)\\|\\bfor\)\\|#\)\\)")
  (make-local-variable 'beta-construct-delimiters)
  ;; this should be both beta-construct-start and beta-construct-end
  (setq beta-construct-delimiters "\\(\(if\\b\\|\\bif\)\\|\(for\\b\\|\\bfor\)\\|\\(^\-\-\\)\\|\(#\\|#\)\\)")
  (make-local-variable 'beta-separator)
  (setq beta-separator "\\(\\bdo\\b\\|\\benter\\b\\|\\bexit\\b\\|//\\|\\belse\\b\\|\\brepeat\\b\\)")
  (make-local-variable 'comment-indent-hook)
  (setq comment-indent-hook 'beta-comment-indent)
  (make-local-variable 'parse-sexp-ignore-comments)
  (setq parse-sexp-ignore-comments nil)
  (run-hooks 'beta-mode-hook))

;; This is used by indent-for-comment
;; to decide how much to indent a comment in BETA code
;; based on its context.
(defun beta-comment-indent ()
  (if (and (bolp) (not (eolp)))
      0					;Existing comment at bol stays there.
    (save-excursion
      (skip-chars-backward " \t")
      (max (1+ (current-column))	;Else indent at comment column
	   comment-column))))		; except leave at least one space.

(defun beta-indent-to-comment ()
  "Move point to comment-column and start BETA comment."
  (interactive)
  (indent-to comment-column 1)
  (insert comment-start comment-end)
  (backward-char 3))

;; BETA comments cannot be nested
(defun beta-within-comment ()
  "Return t if within a BETA comment, nil otherwise."
  (interactive)
  (save-excursion
    (if (= (point) 1)
	nil;; optimization
      (progn
	(if (looking-at "\\*") (forward-char 1))
	(let ((end (point)))
	  (if (re-search-backward "\\(\(\\*\\|\\*\)\\)" 1 t)
	      (if (looking-at "\(\\*")
		  t;;(not (beta-within-string end))
		nil)
	    nil))))))

(defun beta-newline (arg)
  "Insert a newline and indent current and following line."
  (interactive "P")
  (if beta-auto-indent
      (let ( (comment (beta-within-comment)) )
	(newline)
	(save-excursion;; indent previous line
	  (backward-char 1) 
	  (skip-chars-backward " \t")
	  (if comment;; insert "*" if not already there
	      (if (= (current-column) 0)
		  (progn
		    ;; Nothing on the line
		    (insert "*")
		    (if beta-space-after-star (insert " ")))
		(progn
		  (backward-char 1)
		  (if (looking-at "\(")
		      (progn
			(forward-char 1)
			(insert "*")
			(if beta-space-after-star (insert " ")))))))
	  (beta-indent-line))
	(if comment
	    (progn
	      (skip-chars-forward " \t")
	      (if (not (looking-at "\\*")) 
		  (progn 
		    (insert "*")
		    (if (not (looking-at "\)"))
			;;			(forward-char 1)
			(if beta-space-after-star (insert " ")))
		    (save-excursion (beta-indent-line)))
                (progn
                  (beta-indent-line)
                  ;; we are placed at a '*'. Check if is is comment-end.
                  (if (looking-at "\\*)")
		      ;; step back to before the comment-end
		      (progn
			(backward-char 1))
                    (progn
                      ;; newline was inserted just before a '*' in a comment. 
                      ;; Step over '*' to allow continous type-in of the
                      ;; comment
		      (forward-char 1)
		      (if (not (eolp)) (forward-char 1)))))))
	  (beta-indent-line)))
    (newline)))

;; added 9-Apr-92 by datpete
(defun line-no ()
  "Return current line number in buffer"
  (interactive)
  (save-excursion
    (beginning-of-line)
    (1+ (count-lines 1 (point)))))

;; added 6-Feb-91
(defun beta-tab ()
  "Indent current line as BETA code.
If at end of line, and beta-tab-to-comment is t, then moves to
comment-column, and begins BETA comment."
  (interactive)
  (if (and (eolp) (< (current-indentation) (current-column))
	   beta-tab-to-comment)
      (beta-indent-to-comment))
  (if (<= (current-column) (current-indentation))
      (beta-indent-line)
    (save-excursion (beta-indent-line))))

;; the main function indenting the current line
(defun beta-indent-line ()
  "Indent current line as BETA code."
  (interactive)
  (let ((indent-tabs-mode nil) 
	(ilevel 0)
	(olevel 0) 
	(beta-frag nil)
	(dopart-frag nil)
	(beta-inside-if nil)
	(beta-inside-for nil)
	(beg 0)
	(beginning-construct-at-point-min nil)
	(skip 0)
	(lin 0)
	(col 0)
	(incode nil)
	(after-colon nil)
	(case-fold-search t))
    ;; Added 9-Apr-92 by datpete
    (beginning-of-line)
    (setq beg (point))
    (skip-chars-forward " \t")
    (if (and (not (looking-at "\(\\*")) (beta-within-comment))
	(progn
	  (save-excursion
	    (goto-char (match-beginning 0))
	    (setq ilevel (+ beta-comment-indent-level (current-column))))
	  
	  ;; do the indentation of the comment line
	  (if (>= ilevel (current-column))
	      (indent-to ilevel)
	    (progn
	      (delete-region beg (point))
	      (indent-to ilevel))))
      
      ;; Not within comment
      (progn
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ;; Save excursion and search back for the beginning contructor.     ;;
	;; Choose the current indentation for the surrounding contructor as ;;
        ;; basis for the indentation of the current line.                   ;;
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(save-excursion
	  (if beta-combined-indent
	      (if (beta-ending-constructor-on-line)
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

	  (setq beg (point))
	  (beta-beginning-of-construct skip)
	  (setq col -1)
	  (if (= skip 1)
	      (while (and (= lin (line-no)) (not (= (current-column) col)))
		;; opening construct was on same line, go back one more
		(setq col (current-column))
		(beta-beginning-of-construct 0)))

	  (setq olevel (current-column))
          (setq ilevel olevel)
	
	  (if (and (= (point) (point-min)) (not (looking-at "\\bdo\\b")))
	      (setq beta-frag t))

	  (if (= (point) beg) 
	      (setq beginning-construct-at-point-min t)
	    (cond 
	     ((looking-at "\(if\\b")
	      (setq beta-inside-if t))
	     ((looking-at "\(for\\b")
	      (setq beta-inside-for t))))

	  (if (looking-at "--")
	      (progn 
		(setq beta-frag t)
		(if (looking-at "---*\\s-*\\w+\\s-*:\\s-*dopart") 
		    (setq dopart-frag t)))))

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Now we are back on the line to indent: Do the indentation ;;
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(beginning-of-line)
	(setq beg (point))
	(skip-chars-forward " \t")
	
	(setq after-colon (beta-after-colon))
	
	;; Check special fragment indentation.
	(cond
	 ;; if beginning-of-construct found dopart-frag, use normal indentation
	 (dopart-frag 
	  (if (not (looking-at "\\bdo\\b"))
	      (setq ilevel (+ ilevel beta-indent-level))))
	 
	 ;; if beginning-of-construct found "--", use zero indentation
	 (beta-frag (setq ilevel 0)))

	;; check special indentation inside constructs
	(cond
	 ;; if looking at an //-line use special indentation
	 ((looking-at "//")
	  (setq ilevel (+ ilevel beta-case-indent-level)))
	 
	 ;; if looking at an else-line use special indentation
	 ((looking-at "\\belse\\b")
	  (setq ilevel (+ ilevel beta-else-indent-level)))
	 
	 ;; if inside an if-block, not looking at '//' or else, use special...
	 (beta-inside-if
	  (setq ilevel (+ ilevel beta-if-indent-level)))
	 
	 ;; if inside a for-block, use special...
	 (beta-inside-for
	  (setq ilevel (+ ilevel beta-for-indent-level)))
	 
	 ;; if looking at a fragment use special indentation
	 ((looking-at "--")
	  (setq ilevel 0))
	 
	 ;; if looking at dopart-slot, use special...
	 ((looking-at "<<\\s-*slot\\s-+\\w+\\s-*:\\s-*dopart")
	  (progn
	    (setq ilevel (+ ilevel beta-separator-indent-level))))
	 
	 ;; if looking at an enter-,do- or exit-line use special...
	 ((looking-at "\\(\\benter\\b\\|\\bdo\\b\\|\\bexit\\b\\)")
	  (progn
	    (setq ilevel (- ilevel beta-separator-indent-level))
	    (setq after-colon nil)));; No special indentation, see below.

	 ;; else
	 ((and (not beta-frag) 
	       (not beginning-construct-at-point-min))
	  (setq ilevel (+ ilevel beta-indent-level)))
	 );;cond
	
	(cond
	 ;; if looking at construct-start after colon, indent some more
	 ;;((and after-colon (looking-at beta-construct-start))
	 ;; (setq ilevel (+ ilevel beta-block-indent-level)))
	 
	 ;; if looking at beginning of comment after colon, indent some more
	 ;;((and after-colon (looking-at "\(\\*"))
	 ;; (setq ilevel (+ ilevel beta-block-indent-level)))
	 
	 ;;if positioned after colon, indent some more.
	 (after-colon
	  (setq ilevel (+ ilevel beta-block-indent-level)))
	 
	 ;; if looking at '->' indent some more
	 ((looking-at "->")
	  (setq ilevel (+ ilevel beta-evaluation-indent-level)))
	 
	 ;; if below a separator indent some more.
	 ((and (not (looking-at beta-separator))
	       (setq incode (beta-below-separator)))
	  (setq ilevel (+ ilevel beta-below-separator-indent)))
	 );; cond
	
	;; if a  beta-construct-end start the line
	;; don't indent so much
	(if (looking-at beta-construct-end)
	    (setq ilevel olevel))
	
	;; do the indentation
	(if (>= ilevel (current-column))
	    (indent-to ilevel)
	  (progn
	    (delete-region beg (point))
	    (indent-to ilevel))))))
 0)

;; Added 8-Apr-92 by datpete
(defun beta-ending-constructor-on-line ()
  "Are there any ending constructors on current line?"
  (interactive "p")
  (beginning-of-line)
  (let ( (begin (point)) (result nil) (done nil) (case-fold-search t) )
    (end-of-line)
    (while (not done)
      (setq result (re-search-backward beta-construct-end begin 'move))
      (if (not (beta-in-pattern-variable)) (setq done t)))
    result))

(defun beta-in-pattern-variable ()
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

(defun beta-within-string (end)
  (interactive "p")
  (save-excursion
    (save-restriction
      (if (= end 1)
	  nil;; optimization
	(progn
	  (narrow-to-region (point) end)
;;(message "Occurrences: %d" (beta-count-matches "\\([^\\]\\|\\\\\\\\\\)'"))
	  (> (mod (beta-count-matches "\\([^\\]\\|\\\\\\\\\\)'") 2) 0))))))

(defun beta-count-matches (regexp)
  "Returns number of matches for REGEXP following point.
Based on the standard how-many function"
  (interactive "sHow many matches for (regexp): ")
  (let ((count 0) (opoint -1))
    (save-excursion
      ;; If we did forward-char on the previous loop,
      ;; and that brought us to eof, search anyway.
      (while (and (or (not (eobp)) (/= opoint (point)))
                  (re-search-forward regexp nil t))
        (if (prog1 (= opoint (point)) (setq opoint (point)))
            (forward-char 1)
          (setq count (1+ count))))
     count)))

(defun beta-beginning-of-construct (&optional arg)
  "Move backward to the beginning of this construct, or to start of buffer.
With argument, ignore that many closing constructors.
Returns new value of point in all cases."
  (interactive "p")
  (or arg (setq arg 0))
  (let ((end (point)) (cont nil) (cnt 0) (case-fold-search t) (p 0) )
    ;; cnt is the number of non-matched beginning constructs to skip backwards
    (if (>= arg 0)
	(while (>= cnt 0)
	  (re-search-backward beta-construct-delimiters 1 'move)
	  ;; check that it was a real beginning construct:
	  (setq cont t)
	  (while cont
	    (if nil;;(beta-within-string end)
		(progn
		  (setq p (point))
		  (re-search-backward beta-construct-delimiters 1 'move)
		  (setq cont (not(= p (point)))))
	      (if (beta-within-comment)
		  (progn
		    (setq p (point))
		    (re-search-backward beta-construct-delimiters 1 'move)
		    (setq cont (not(= p (point)))))
		(setq cont nil))))
	  (if (looking-at "--") 
	      (setq cnt -1)
	    (progn
	      (if (= (point) 1)
		  ;; beginning of buffer reached
		  (setq cnt -1)
		(if (looking-at beta-construct-end)
		    ;; this looks like an ending construct
		    (if (not (or (beta-in-pattern-variable) (beta-within-comment)))
			;; looking at a real ending construct
			(if (> arg 0)
			    ;; Still some endings left to skip
			    (setq arg (1- arg))
			  ;; looking at real ending construct, and no more to skip
			  (setq cnt (1+ cnt))))
		  ;; looking at real beginning construct: one less to match
		  (setq cnt (1- cnt)))))))
	(point))
    (point))
  (point))

;;; Added 13-Apr-92 by datpete
(defun beta-after-colon ()
  "Returns t if point is after a colon, possibly with <, @, ^, white space, 
a prefix and/or a comment in between."
  (interactive)
  (save-excursion
    (beginning-of-line)
    (beta-skip-comment-backward)
    (skip-chars-backward " \t\n")
    (skip-chars-backward "A-Za-z0-9().");; prefix
    (skip-chars-backward " \t\n<@^|");; whitespace and instantiation
    (if (> (point) 1) (backward-char 1))
    (looking-at ":")))

;;; Added 13-Apr-92 by datpete
(defun beta-skip-comment-backward ( )
  "Skip backward past (* ... *)."
  (interactive)
  (skip-chars-backward " \t\n")
  (if (> (point) 2)
      (progn
	(backward-char 2)
	(if (looking-at "\\*\)")
	    (if (not (search-backward "(*" 1 t))
		(forward-char 2))
	  (forward-char 2)))))

(defun beta-below-separator ()
  "Returns t if point is below a separator as enter, exit, or //."
  (interactive)
  (save-excursion
    (let ( (col 0) (case-fold-search t) )
      (re-search-backward 
       (concat "\\(" beta-separator "\\|" beta-construct-delimiters "\\)")
       nil 'move 1)
      (goto-char (match-beginning 0))
      (setq col -1)
      (while (and (looking-at beta-construct-end) (not (= (current-column) col)))
	(setq col (current-column))
	(beta-beginning-of-construct) 
	(re-search-backward 
	 (concat "\\(" beta-separator "\\|" beta-construct-delimiters "\\)")
	 nil 'move 1)
	(goto-char (match-beginning 0)))
      (not (looking-at beta-construct-start)))))


(defun beta-open-pattern ()
  "Insert pattern start \(#, and indent line."
  (interactive)
  (insert "\(# ")
  (beta-tab))

(defun beta-right-paren ()
  "Insert right parenthes. Delete blank before point if after '*' in a comment"
  (interactive)
  (if (> (current-column) 1)
      (progn
	(backward-char 2)
	(if (looking-at "\* ")
	    (progn
	      (forward-char 1)
	      (delete-char 1))
	  (forward-char 2))))
  (insert "\)")(blink-matching-open))

(defun beta-close-pattern ()
  "Insert end marker for current construct plus semicolon (if needed) and indent the line."
  (interactive)
  (let ((c "") (d "") (case-fold-search t))
    (if (beta-within-comment)
	(save-excursion
	  (setq c "\*\)")
	  (skip-chars-backward " \t")
	  (if (> (current-column) 1)
	      (progn
		(backward-char 2)
		(if (not (looking-at "\(\\*"))
		    (progn
		      (forward-char 1)
		      (if (looking-at "\\*") (delete-char 1)))))))

      (save-excursion
	(beta-beginning-of-construct)
	(cond
	 ((looking-at "\(#")   (setq c "#\)"))
	 ((looking-at "\(for\\b") (setq c "for\)"))
	 ((looking-at "\(if\\b")  (setq c "if\)"))
	 ((looking-at "\(")    (setq c "\)")))
	(if (> (current-column) 1)
	    ;; current-column is 1 if this is a descriptor fragment
	    (setq d ";"))
	))
    (if (equal c "")
	(error "beta-mode error: Not inside construct")
      (insert c)(blink-matching-open)
      (if beta-semicolon-after-closing
	  (if (not (looking-at ";"))(insert d))))
    (save-excursion
      (beginning-of-line)
      (beta-indent-line))))

;;; Functions manipulating BETA comments, written by jlk@mjolner.dk
(defun bulk-replace-regexp(regexp replacement)
  "Implements replace-regexp such that it can be undone in one undo step"
  (while (re-search-forward regexp (point-max) t)
    (replace-match replacement)
    ))

(defun bulk-replace-string(string replacement)
  "Implements replace-string such that it can be undone in one undo step"
  (while (search-forward string (point-max) t)
    (replace-match replacement)
    ))

(defun beta-comment-justify()
  "Formats a BETA comment according to the BETA recommandations (i.e. with '*'
in front of each new line in the comment).  Furthermore, the comment is
formatted to fill as little as possible. Assumes that the cursor is positioned
within a BETA comment.  If not, the first comment found before the cursor is
justified.  If no comment is found before the cursor position, the first
comment following the cursor position will be affected."
  (interactive)
  (save-excursion
    (save-restriction
      (let ((indent-tabs-mode nil)
	    (bline (make-marker))
	    (bmark (make-marker))
	    (emark (make-marker))
	    (xxindent 0)
	    (old-fill-column 0)
	    (comment-prefix ""))
	(end-of-line)
	(if (search-backward "(*" (point-min) t)
	    (goto-char (+ (point) 2))
	  (if (search-forward "(*" (point-max) t)
	      ()
	    (error "No comment found in file !!!")))
	(set-marker bmark (point))
	(search-forward  "*)" (point-max)) 
	(set-marker emark (- (point) 1))
	(goto-char bmark)
	(beta-indent-line)
	(beginning-of-line)(set-marker bline (point))(end-of-line)
	(if (or (< (point) (- emark -1)) (< fill-column (- (point) bline)))
	    (progn
	      (goto-char bmark)
	      (insert-string "\n")
	      (setq xxindent (- bmark bline))
	      (narrow-to-region bmark (- emark 1))
	      (beginning-of-buffer)
	      (bulk-replace-regexp "^[ \t]*\\*[ \t]?" "")
	      (setq old-fill-column fill-column)
	      (setq fill-column (- old-fill-column xxindent 1))
	      (fill-region (point-min) (point-max))
	      (setq fill-column old-fill-column)
	      (goto-char bmark)(forward-line)
	      (setq comment-prefix (format "%%%ds* \\1" (- xxindent 1)))
	      (setq comment-prefix (format comment-prefix " "))
	      (bulk-replace-regexp "\\(^[ \t]*[^*]\\)" comment-prefix)
	      (widen)(forward-line)
	      (beta-indent-line)
	      (goto-char bmark)(delete-char (+ xxindent 2))
	      (if (>= fill-column (- emark bline -1))
		  (progn (goto-char bmark)
			 (narrow-to-region bmark (- emark 1))
			 (bulk-replace-regexp "\n" "")
			 (widen)))
	      ))))))

(defun beta-comment-justify-region(breg ereg)
  "Like beta-comment-justify, except that the marked region is expected to be
part of some BETA comment, and that only that part of the region is to be
reformatted."
  (interactive "r")
  (save-excursion
    (save-restriction
      (let ((indent-tabs-mode nil)
	    (bline 0)
	    (xxindent 0)
	    (old-fill-column 0)
	    (comment-prefix ""))
	(end-of-line)
	(beta-indent-line)
	(beginning-of-line)(setq bline (point))
	(search-forward "*" (point-max) t)(setq breg (point))
	(setq xxindent (- breg bline))
	(narrow-to-region breg ereg)
	(beginning-of-buffer)
	(bulk-replace-regexp "^[ \t]*\\*[ \t]?" "")
	(setq old-fill-column fill-column)
	(setq fill-column (- old-fill-column xxindent 1))
	(fill-region (point-min) (point-max))
	(setq fill-column old-fill-column)
	(goto-char breg)(forward-line)
	(setq comment-prefix (format "%%%ds* \\1" (- xxindent 1)))
	(setq comment-prefix (format comment-prefix " "))
	(bulk-replace-regexp "\\(^[ \t]*[^*]\\)" comment-prefix)
	(widen)(forward-line)
	(beta-indent-line)
	))))
  
;; changed 13-Nov-1992 by jlk@daimi.aau.dk
(defun beta-convert-region-to-comment(begin end)
  "Takes the marked region and surrounds it with BETA comment symbols, and
formats the new comment according to the BETA comment recommandations.  Any
comment symbols in the marked region will be converted into {*, respectively *}
to avoid spurious problems with nested comments (not supported by the BETA
compiler)."
  (interactive "r")  
  (save-excursion
    (save-restriction
      (let ((indent-tabs-mode nil)
	    (bline 0)
	    (bmark (make-marker))
	    (emark (make-marker))
	    (xxindent 0)
	    (comment-prefix ""))
	(set-marker bmark begin)
	(set-marker emark end)
	(goto-char bmark)(insert-before-markers "(* ")
	(goto-char emark)
	(if (looking-at "[ \t]*$") 
	    (insert-string "\n*)")
	  (insert-string "\n*)\n")(beta-indent-line))
	(goto-char bmark)(beta-indent-line)
	(beginning-of-line)(setq bline (point))
	(setq xxindent (- bmark bline))
	(narrow-to-region bmark emark)
	(beginning-of-buffer)(bulk-replace-regexp "(\\*" "{*")
	(beginning-of-buffer)(bulk-replace-regexp "\\*)" "*}")
	(beginning-of-buffer)(forward-line)(beginning-of-line)
	(setq comment-prefix (format "%%%ds* " (- xxindent 2)))
	(setq comment-prefix (format comment-prefix " "))
	(bulk-replace-regexp "^" comment-prefix)
	(widen)
	(forward-line 1)
	(beta-indent-line)
	))))

;; changed 2-Mar-1993 by jlk@daimi.aau.dk
(defun beta-remove-comment()
  "Is the 'inverse' of beta-convert-region-to-comment'.  Removes the nearest
surrounding BETA comments, restoring any nested comment symbols, enclosed in
this comment"
  (interactive)
  (save-excursion
    (save-restriction
      (let ((indent-tabs-mode nil)
            (case-fold-search nil)
            (bmark (make-marker))
            (emark (make-marker)))
	(end-of-line)
	(if (not (search-backward "(*" (point-min) t))
	    (if (not (search-forward "(*" (point-max) t))
		(error "No comment found in file !!!")))
	(set-marker bmark (point))
	(search-forward  "*)" (point-max)) 
	(beginning-of-line)
	(if (looking-at "^[ \t]*\\*)[ \t]*$") (kill-line 1))
	(set-marker emark (point))
	(goto-char bmark)
        (narrow-to-region bmark emark)
        (goto-char bmark)
	(if (re-search-forward "(\\* ?" (point-max) t)(replace-match ""))
        (goto-char emark)
	(if (re-search-backward " ?\\*)" (point-min) t)(replace-match ""))
        (goto-char bmark)(bulk-replace-regexp "\\*}" "\\*)")
        (goto-char bmark)(bulk-replace-regexp "{\\*" "(\\*")
        (goto-char bmark)(bulk-replace-regexp "\n *\\* " "\n")
        (push-mark bmark "nomsg") (goto-char emark)
	(save-excursion (save-restriction (delete-blank-lines)))
        (widen)(call-interactively 'indent-region)
        (pop-mark)(goto-char bmark)(beta-indent-line)))))

;; Added 25-Aug-1992 by jlk@mjolner.dk
(defun beta-prettyprint()
  "Converts a non-standard indented BETA source code file into a standard one."
  (interactive)
  (save-excursion
    (let ((case-fold-search t))
      (goto-char (point-min))
      (bulk-replace-regexp "[\t ]*\/\/[\t ]*" "//")
      (goto-char (point-min))
      (bulk-replace-regexp "[\t ]*:[\t ]*" ": ")
      (goto-char (point-min))
      (bulk-replace-regexp "@[\t ]+" "@")
      (goto-char (point-min))
      (bulk-replace-regexp "\\^[\t ]+" "^")
      (goto-char (point-min))
      (bulk-replace-regexp ": <[\t ]*\\([^<]\\)" ":< \\1")
      ;;(bulk-replace-regexp ": <[\t\n ]*\\([^<]\\)" ":< \\1")
      (goto-char (point-min))
      (bulk-replace-string ": <<<" ":< <<")
      (goto-char (point-min))
      (bulk-replace-regexp ":[\t\n ]*<[\t\n ]*<[\t\n ]*\\([^<]\\)" ": <<\\1")
      (goto-char (point-min))
      (bulk-replace-string ": :" "::")
      (goto-char (point-min))
      (bulk-replace-regexp "(if\\b" "(if")
      (goto-char (point-min))
      (bulk-replace-regexp "(for\\b" "(for")
      (goto-char (point-min))
      (bulk-replace-regexp "\\binner\\b" "INNER")
      (goto-char (point-min))
      (bulk-replace-regexp "(#[ \t]*" "(# ")
      (goto-char (point-min))
      (bulk-replace-regexp "\n[\t\n ]**#)" "\n#)")
      (goto-char (point-min))
      (bulk-replace-regexp "<<[ \t\n]*" "<<")
      (goto-char (point-min))
      (bulk-replace-regexp "[ \t\n]*>>" ">>")
      (goto-char (point-min))
      (bulk-replace-regexp "\\bdo\\b[ \t\n]*" "do ")
      (goto-char (point-min))
      (bulk-replace-regexp "<<\\bslot\\b[ \t\n]*" "<<SLOT ")
      (goto-char (point-min))
      (bulk-replace-regexp "\\([^\t\n ]\\)[\t ]*->[\t ]*\\([^\t\n ]\\)" "\\1->\\2")
      (goto-char (point-min))
      (bulk-replace-string"(##)" "(# #)")
      (goto-char (point-min))
      (bulk-replace-string"(#do" "(# do")
      )
    (indent-buffer)))

;; Added 24-Aug-1994 by jlk@mjolner.dk
(defvar beta-compiler-options nil
  "Options supplied to the compiler in beta-check and beta-compile functions.")
(defvar beta-compiler-command
  (if (getenv "BETALIB") (concat (getenv "BETALIB")"/bin/beta") "/usr/local/bin/beta")
  "BETA compiler command.")
(defun beta-check ()
  (interactive)
  (compile (concat beta-compiler-command" "beta-compiler-options" --nocode "buffer-file-name)))
(defun beta-compile ()
  (interactive)
  (compile (concat beta-compiler-command" "beta-compiler-options" "buffer-file-name)))
(defun beta-execute ()
  (interactive)
  (make-comint "execution" (substring buffer-file-name 0 -4))
  (pop-to-buffer "*execution*"))



;;; A generally applicable function:

(defun indent-buffer ( )
  "Indent the entire buffer according to mode."
  (interactive "*")
  (save-excursion
    (if (> (point-max) 10000)
	(message "Indenting the entire buffer ... (be patient)")
      (message "Indenting the entire buffer ..."))
    (indent-region (point-min) (point-max) nil)
    (message "Indenting the entire buffer ... done")))

;;; A much faster indent-buffer:

(defun beta-indent-buffer ( )
  "Indent the entire buffer, using beta-fast-indent-buffer."
  (interactive "*")
  (require 'beta-fast-indent)
  (save-excursion
    (if (> (point-max) 10000)
	(message "Indenting the entire buffer ... (be patient)")
      (message "Indenting the entire buffer ..."))
    (beta-fast-indent-buffer)
    (message "Indenting the entire buffer ... done")))




;;;;;;;; That's all, folks! ;;;;;;;;;
