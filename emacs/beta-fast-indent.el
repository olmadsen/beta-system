;;; beta-fast-indent.el --- indent whole buffer according to beta-mode

;; Copyright (C) 1996 Peter von der Ahe

;; Created: 26 jan 1996
;; Time-stamp: "96/02/08 10:19:50 pahe"
;; Version: 1.2

;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

;;; Howto contact author:
;; e-mail: pahe@daimi.aau.dk
;; Snail-mail: Peter von der Ahe
;;             Ny Munkegade 101,1 tv
;;             DK-8000 Aarhus C
;;             Denmark
;; Phone: + 45 86 13 26 34 or + 45 86 52 48 75

;;; Howto use beta-fast-indent in beta-mode:
;; Add the following to your .emacs
;;     (add-hook 'beta-mode-hook
;;               '(lambda ()
;;                  (require 'beta-fast-indent "beta-fast-indent")))

(provide 'beta-fast-indent)

(defvar beta-fast-relop 
  "\\(=\\|<\\|<=\\|=<\\|>\\|>=\\|=>\\|<>\\|or\\b\\|\\+\\|-\\|\\*\\|/\\|div\\b\\|mod\\b\\|and\\b\\)"
  "Operators used in beta")

(defvar beta-fast-id
  "[A-Za-z_][A-Za-z_0-9]*"
  "Names used in beta")

(defvar beta-fast-remote-name
  "&?[ \t]*[A-Za-z_][A-Za-z_0-9]*\\(\\.\\([A-Za-z_][A-Za-z_0-9]*\\)+\\)*"
  "Names used in beta")

;; created 31-jan-96 by pahe
(defun beta-fast-indent-one-line () ""
  (interactive)
  (if (boundp 'beta-fast-debug) ()
    (error "This function is not yet complete!"))
  (save-excursion
    (let ((open-construct-stack ())
	  (beg-pnt 1)			;beginning of this line.
	  (end-pnt 1)			;end of this line.
	  (prev-beg-pnt 1)		;beginning of the previous line.
	  (prev-i-level)		;indent level of previous line.
	  )
      (end-of-line)
      (setq end-pnt (point))
      (beginning-of-line)
      (if (= (setq beg-pnt (point)) (point-min))
	  (progn			;This is the beginning of the buffer!
	    (skip-chars-forward " \t")
	    (beta-fast-indent-to beg-pnt 0))
	(progn				;else...
	  (forward-line -1)
	  (setq prev-beg-pnt (point))
	  (skip-chars-forward " \t")
	  (setq prev-i-level (current-column))
	  (goto-char beg-pnt)
	  (while (<= (point) end-pnt)
	    (if (looking-at beta-construct-end)
		(progn
		  (setq prev-i-level 
			(- prev-i-level (length (match-string 0)) 1))
		  (goto-char (match-end 0))))
	      (forward-char 1))
	  (goto-char beg-pnt)
	  (skip-chars-forward " \t")
	  (beta-fast-indent-to beg-pnt prev-i-level)	  
	  ))				;endif
      )))

;; created 26-jan-96 by pahe
(defun beta-fast-indent-buffer ()
  "Indent current buffer according to beta-mode.
You can not nest comments!
You can not split strings over several lines!
On a line where you close constructs, you should not leave any open
constructs, eg:
  #)#); PatternName(#

but 
  #)#); PatternName(# ... #)

should be OK."
  (interactive)
  (if (not (eq major-mode 'beta-mode))
      (error "Trying to use beta-fast-indent-buffer while not in beta-mode"))
  (let ((line-number 0)
	(total-lines 0)
	(colon-i-level 0)
	(open-construct-stack '(0))
	(origin-body-etc nil)
	(relop nil)
	(inherit nil)
	(mdbody nil)
	(enter-or-exit 0)
	(gc-cons-threshold 1000000)
	(relop-i-level 0))
    (if (boundp 'beta-fast-debug)
      (save-excursion
	(set-buffer "*Messages*")
	(delete-region (point-min) (point-max))))
    (save-excursion
      (message "Fast-indenting the whole buffer...")
      (goto-char (point-min))
      (setq total-lines(count-lines (point-min) (point-max)))
      (while (not (looking-at "\\'"))
	(message "Line: %d/%d" (setq line-number (1+ line-number)) total-lines)
	(beta-fast-indent-line))
      (message "Fast-indenting the whole buffer...done"))
    (if (equal open-construct-stack '(0)) ()
      (message "Your buffer seems unbalanced!"))))

;; suggested by jlk 28-01-96
;; Not needed if using elisp 2.4 or later (introduced in emacs 19.29)
(if (not (fboundp 'match-string))
    (defun match-string (count)
      (buffer-substring (match-beginning count) (match-end count))))

;;created 30-jan-96 by pahe
(defsubst beta-fast-indent-to (from to)
  (if (= to (current-column)) ()
    (progn
      (delete-region from (point))
      (indent-to to))))

(defmacro beta-fast-stack-pop (stack)
  (list 'let (list (list 'popped (list 'car stack)))
	(list 'setq stack (list 'cdr stack))
	'popped))

(defmacro beta-fast-stack-push (stack value)
  (list 'setq stack (list 'cons value stack)))

;; created 26-jan-96 by pahe
(defsubst beta-fast-indent-line ()	;An inline function
(let ((beg-pnt 1)			;Stores the beginning of current line
      (pnt 1)				;Temporary
      (i-level 0)			;Stores the calculated indentationlevel
      (last-pop 0)			;Stores the last popped indentationlvl
      (cnt t)				;Temporary
      (comment-i-level 0)		;Stores the comment indentation
      (construct-end nil)		;Wether this line begins with '#)' etc.
      (case-fold-search t)		;We really like to write (FoR ... foR)
      (relop-level 0))			;Temporary
  
  (beginning-of-line)
  (setq beg-pnt (point))
  (skip-chars-forward " \t")
  (cond 
   ;;case
   ((looking-at "$")
    (setq i-level (current-column)))
   ;;case
   ((looking-at "\(#")
    (setq i-level			;set i-level to the current
	  (+ (car open-construct-stack)	;indent-level plus colon-i-level.
	     colon-i-level))
    (if inherit (setq i-level (+ inherit 2))))
   ;;case
   ((looking-at "---?")
  (if (boundp 'beta-fast-debug) (message "Debug info. \"---?\""))
    (beta-fast-stack-pop open-construct-stack)
    (beta-fast-stack-push open-construct-stack (setq i-level 0))
    (setq mdbody nil))
   ;;case
   ((looking-at "\\(origin\\|include\\|body\\|mdbody\\)\\b")
    (if origin-body-etc
	(beta-fast-stack-pop open-construct-stack))
    (beta-fast-stack-push open-construct-stack (1+ (length (match-string 0))))
    (if (looking-at "mdbody\\b")
	(save-excursion
	  (goto-char (match-end 0))
	  (skip-chars-forward " \t")
	  (looking-at "[a-zA-Z0-9 ]+[^']")
	  (setq mdbody (length (match-string 0))))
      (setq mdbody nil))
    (setq origin-body-etc t)
    (setq i-level 0))
   ;;case
   ((looking-at "repeat")		;If 'repeat', then the colon was
    (setq i-level			;used to declare the range in 'for'.
	  (+ (car open-construct-stack)
	     colon-i-level))
    (setq colon-i-level 0))
   ;;case
   ((looking-at "<<")			;SLOT
    (setq pnt (point))
    (if (re-search-forward 
	 "\\b\\(attributes\\|dopart\\|descriptor\\)\\b"  nil 'move)
	(cond ((string= (downcase (match-string 0)) "attributes") 
	       (setq i-level (car open-construct-stack)))
	      ((string= (downcase (match-string 0)) "dopart") 
	       (setq i-level			
		     (- (car open-construct-stack) 3)))
	      ((string= (downcase (match-string 0)) "descriptor")
	       (setq i-level (car open-construct-stack)))))
    (goto-char pnt)
    (setq colon-i-level 0))		;The open colon wasn't terminated by
					;a semi-colon.
   ;;case
   ((looking-at beta-separator)		;if 'do' 'enter' etc. the indent should
    (cond				;be aligned with the '(#'
     ((looking-at "do")
      (setq enter-or-exit 0))
     ((looking-at "enter")
      (setq enter-or-exit 3))
     ((looking-at "exit")
      (setq enter-or-exit 2)))
    (setq i-level (- (car open-construct-stack) 3 enter-or-exit))
    (setq colon-i-level 0))		;Any colon comes from an attribute
					;not terminated by semi-colon.
   ;;case
   ((looking-at "->") 
    (setq i-level (+ 2 (car open-construct-stack)))
    (if (boundp 'beta-fast-debug)
	(message "Debug info. Arrow: %d" enter-or-exit)))
   ;;case
   ((or (and (looking-at "\(")
	     (not (looking-at beta-construct-start))
	     (not (looking-at "\(\\*"))
	     relop)
	(looking-at beta-fast-relop))
    (setq i-level (max relop-i-level (car open-construct-stack))))
   ;;case
   ((looking-at beta-construct-end)	;The line begins with an end-construct
    (setq construct-end t)		;and should be aligned so.
    (setq i-level (current-column))
    (setq enter-or-exit 0))
   ;;case
   (mdbody
    (if (looking-at "[a-zA-Z0-9 ]+[^']")
	(progn
	  (setq mdbody (length (match-string 0)))
	  (setq i-level (car open-construct-stack)))
      (setq i-level (+ (car open-construct-stack)  mdbody))))
   ;;case
   (t (setq i-level			;Default set i-level to the current
	    (+ (car open-construct-stack) ;indent-level plus colon-i-level.
	       colon-i-level))))

  ;;Do the indentation.
  (goto-char beg-pnt)
  (skip-chars-forward " \t")
  (beta-fast-indent-to beg-pnt (+ enter-or-exit i-level))

  (while (not (looking-at "$"))		;Scan the current-line.
  (skip-chars-forward " \t")
  (if (looking-at "#\)")
      (progn
	(setq relop nil)
	(setq inherit nil)
	(setq enter-or-exit 0)))
  (if (looking-at ";")
      (progn
	(if origin-body-etc
	    (beta-fast-stack-pop open-construct-stack))
	(setq origin-body-etc nil)
	(setq relop nil)
	(setq inherit nil)))
  (cond
   ((looking-at "$"))			;If end of line, we're done.
   
   ((looking-at "---?")
    (setq mdbody nil)
    (setq colon-i-level 0)		;The open colon wasn't terminated by
					;a semi-colon.
    (setq pnt (current-column))
    (goto-char (match-end 0))
    (beta-fast-stack-pop open-construct-stack)
    (if (re-search-forward 
	 "\\b\\(attributes\\|dopart\\|descriptor\\)\\b"  nil)
	(cond ((string= (downcase (match-string 0)) "attributes")
	       (beta-fast-stack-push open-construct-stack pnt))
	      
	      ((string= (downcase (match-string 0)) "dopart")
	       (beta-fast-stack-push open-construct-stack (+ pnt 3)))
	      
	      ((string= (downcase (match-string 0)) "descriptor")
	       (beta-fast-stack-push open-construct-stack pnt))))
    
    (re-search-forward "---?"  nil 'move))

   ((looking-at beta-fast-relop)
    (setq relop t)
    (goto-char (match-end 0)))

   ((or (looking-at beta-construct-end) (looking-at "\)"))
    ;;Bacause we skip over letters we can't see if it's just an
    ;;ordinary ')' or eg. 'for)'. Glad I pushed '(' before.
    (setq colon-i-level 0)		;Last line wasn't terminated by a ';'
    (setq pnt (match-end 0))		;Save end of the construct.
    (if (boundp 'beta-fast-debug)
	(message "Debug info. Closing: %s" (match-string 0)))
    (save-excursion 
      ;; Find the length of construct for the last-pop variable.
      (setq last-pop (car open-construct-stack))
      (if (looking-at beta-construct-end) 
	  (setq last-pop (- last-pop (length (match-string 0)) 1))))
    (goto-char pnt)			;Skip over the end-construct (or ')').
    (beta-fast-stack-pop open-construct-stack))

   ((looking-at "\\b\\(enter\\|do\\|exit\\|else\\|then\\|repeat\\)\\b")
    (setq colon-i-level 0)		;maybe only repeat
    (setq relop nil)
    (setq inherit nil)
    (goto-char (match-end 0)))

   ((looking-at "\\(origin\\|include\\|body\\|mdbody\\)\\b")
    (goto-char (match-end 0)))

   ((looking-at beta-fast-remote-name) 
    (if (= colon-i-level 0)
	(setq inherit (current-column)))
    (if (boundp 'beta-fast-debug)
	(message "Debug info. Remote name: %s" (match-string 0)))
    (goto-char (match-end 0)))

   ((looking-at ":+<*")			;Some things should be aligned
    (setq colon-i-level 2)		;different when under a colon.
    (setq inherit nil)			;No inheirit
    (goto-char (match-end 0)))

   ((looking-at ";")		        ;A semi-colon terminates colons.
    (setq colon-i-level 0)
    (goto-char (match-end 0)))

   ((looking-at "\\(<<\\|>>\\)")	;The open colon comes from a SLOT
    (setq colon-i-level 0)		;name or wasn't terminated by ';'
    (goto-char (match-end 0)))

   ((looking-at "'")			;Skip strings (not my fault if some
    (forward-char 1)			;split strings across several lines).
    (skip-chars-forward "^'")
    (forward-char 1))

   ((looking-at "\(\\*")		;Skip and indent comments.
    (setq comment-i-level (1+ (current-column)))
    (setq cnt t)
    (while cnt
      (re-search-forward "\\(\\*\)\\|$\\)"  nil 'move)
      (if (not (string-equal (match-string 0) "*)"))
	  (progn			;This is a new line within a comment.
	    (setq line-number (1+ line-number))
	    (forward-char 1)
	    (setq pnt (point))
	    (skip-chars-forward " \t")
	    (beta-fast-indent-to pnt comment-i-level))
	(setq cnt nil))))		;The comment is terminated.

   ((or (looking-at beta-construct-start) (looking-at "\(")) ; Construct start
					;'(' should act like open construct.
    (setq colon-i-level 0)		;Forget about colon.
    (goto-char (match-end 0))		;Skip over the construct
    (if (boundp 'beta-fast-debug)
	(message "Debug info. Opening: %s" (match-string 0)))
    ;; push the current column on the stack
    (if (string-match beta-construct-start (match-string 0))
	(setq open-construct-stack (cons (1+ (current-column)) 
					 open-construct-stack))
      (setq relop-level (1+ (car 
			     (setq open-construct-stack 
				   (cons (current-column) 
					 open-construct-stack))))))
    (if relop ()
      (setq relop-i-level relop-level)))

   (t (setq inherit nil)
      (forward-char 1))))		;Unknown char, skip over it.

  ;;Point is now just before end of line or end of buffer

  ;;Correct the above indentation if constructs where ended on
  ;;current line
  (if construct-end
  (let (amark)
    (setq amark (make-marker))
    (set-marker amark (point))
    (goto-char beg-pnt)
    (skip-chars-forward " \t")
    (beta-fast-indent-to beg-pnt last-pop)
    (goto-char amark)
    (set-marker amark nil)))

  (if (not (looking-at "\\'")) (forward-char 1)))) ;Next line
