;; BETA utility functions commands for GNU Emacs

;; Created 29-Aug-94 by jlk@daimi.aau.dk

;; These utility functions was programmed by Peter Andersen
;; (datpete@mjolner.dk) and Kim Jensen M|ller (kjm@mjolner.dk) 
;; Tommy Thorn (tthorn@daimi.au.dk), J|rgen Lindskov (jlk@mjolner.dk all
;; contributed with additions, suggestions and bugfixes.

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

;; By putting the following lines of Emacs-Lisp code into your .emacs
;; file, you can make Emacs automagically load these utility functions
;; when it invokes the beta-mode

;; (setq beta-mode-hook
;;       '(lambda ()
;;       (require 'beta-utils "/usr/local/lib/beta/emacs/current/beta-utils")
;;       ;; ... other beta-mode initializations
;; ))

(require 'beta-mode)

(provide 'beta-utils)

;;; TAGS-based replacement functions.

(defun beta-make-dopart-fragment()
  "Tags query replace all BETA descriptor fragments without local attributes to dopart fragments"
  (interactive)
  (let ((case-replace nil))
    (tags-query-replace "---*\\s-*\\(\\w+\\)\\s-*:\\s-*descriptor\\s-*---*\\s-*(#\\s-*do\\([^#]*\\)#)" "-- \\1: dopart --
do\\2" nil)
    (tags-query-replace "---*\\s-*\\(\\w+\\)\\s-*:\\s-*descriptor\\s-*---*\\s-*(#\\s-*#)" "-- \\1: dopart --
do" nil)))
  
(defun beta-make-dopart-slot()
  "Tags query replace all BETA descriptor slots to dopart slots"
  (interactive)
  (let ((case-replace nil))
    (tags-query-replace "do\\s-*\\(<<\\s-*slot\\s-+\\w+\\)\\s-*:\\s-*descriptor>>[\\t ]*;*[\\t ]*" "\\1: dopart>> " nil)))

;;; Non-TAGS based versions.

(defun beta-make-dopart-fragment-local()
  "Query replace all BETA descriptor fragments without local attributes to dopart fragments"
  (interactive)
  (let ((case-replace nil))
    (query-replace-regexp "---*\\s-*\\(\\w+\\)\\s-*:\\s-*descriptor\\s-*---*\\s-*(#\\s-*do\\([^#]*\\)#)" "-- \\1: dopart --
do\\2" nil)))

(defun beta-make-dopart-slot-local()
  "Query replace all BETA descriptor slots to dopart slots"
  (interactive)
  (let ((case-replace nil))
    (query-replace-regexp "do\\s-*\\(<<\\s-*slot\\s-+\\w+\\)\\s-*:\\s-*descriptor>>[\\t ]*;*[\\t ]*" "\\1: dopart>> " nil)))

;;; Find patterns by BETA entry number

(defun beta-find-pattern (num)
  "Find '(#' number NUM in current fragment that is not within a comment"
  (interactive "NGoto pattern number: ")

  (let ( (number num)
         (ulimit (save-excursion 
		   (re-search-forward "^\-\-" (point-max) 'move)
		   ;; the next lines are just to end up with point just before
		   ;; the "--" of next fragment.
		   (if (> (point) 2) (backward-char 2))
		   (if (looking-at "^\-\-")
		       (- (point) 1)
		     (+ (point) 1)))
		 ))
    (re-search-backward "^\-\-" (point-min) 'move)
    (while (> num 0)
      (if (search-forward "(#" ulimit 'move)
	  (if (not (beta-within-comment)) (setq num (1- num)))
	(error "There are only %d patterns in this fragment" (- number num))))))
      
(defun beta-what-pattern ()
  "Find the number of the current pattern (counting '(#' not within a comments)
within current fragment"
  (interactive)
  (save-excursion
    (if (looking-at "#") (backward-char 1))
    (if (not (looking-at "(#"))
	(if (not (search-backward "(#" (point-min) 'move))
	    (error "Not inside pattern")))
    (let ((num 0) (pos (point)))
      (re-search-backward "^\-\-" (point-min) 'move)
      (while (< (point) pos)
	(if (search-forward "(#" (point-max) 'move)
	    (if (not (beta-within-comment)) (setq num (1+ num)))
	  (error "End of buffer reached")))
      (message "The pattern is number %d in current fragment" num))))

;;; Functions to convert from old fragment syntax to new fragment syntax
    
(defun beta-new-include-style()
  (interactive)
  (let ((case-fold-search t) (case-search nil))
    (set-variable 'tags-file-name nil)
    (tags-query-replace "\\s-*--+\\s-*INCLUDE\\s-*'\\(.*\\)'" "\nINCLUDE '\\1';")
    ))

(defun beta-origin-semicolon()
  (interactive)
  (let ((case-fold-search t) (case-search nil))
    (set-variable 'tags-file-name nil)
    (tags-query-replace "\\s-*ORIGIN\\s-*'\\(.*\\)'" "ORIGIN '\\1';")
    ))

(defun beta-body-semicolon()
  (interactive)
  (let ((case-fold-search t) (case-search nil))
    (set-variable 'tags-file-name nil)
    (tags-query-replace "\\s-*BODY\\s-*'\\(.*\\)'" "\nBODY '\\1';")
    ))

(defun beta-remove-brackets ()
  (interactive)
  (set-variable 'tags-file-name nil)
  (tags-query-replace "\\[\\[\\s-*\\|\\s-*--+\\s-*\\]\\]" "" nil))

;;; Utilities to support fragmentation of existing source code files
    
(defvar beta-connected-fragment-file nil 
  "The buffer to which beta-make-region-to-slot inserts the region as a new
fragment.  This variable will be made local to the buffer when the fragment
file is connected to the buffer")

(defvar beta-descriptor-slot "Body: descriptor"
  "The string appended to the name of a descriptor slot name.  May be modified as long as the suffix ':descriptor' is maintained.")

(defvar beta-attribute-slot  "Private: attributes"
  "The string appended to the name of an attribute slot name.  May be modified as long as the suffix ':attributes' is maintained.")

(defvar beta-dopart-slot  "Dopart: dopart"
  "The string appended to the name of a dopart slot name.  May be modified as long as the suffix ':dopart' is maintained.")


(defun beta-convert-region-to-attribute-slot-on-fragment-file (begin end slot-name)
  (interactive    
   (list (region-beginning)
	 (region-end)
         (read-string "Enter SLOT name: ")))
  (beta-find-fragment-separator)
  (save-excursion
    (save-restriction
      (copy-to-register ?A begin end t)
      (insert-string (concat "<<SLOT " slot-name beta-attribute-slot ">>;"))
      (set-buffer beta-connected-fragment-file)
      (if (not (looking-at "^")) (insert-string "\n"))
      (insert-string (concat "--- " slot-name beta-attribute-slot " ---\n"))
      (insert-register ?A t)
      (if (not (looking-at "^")) (insert-string "\n"))
      ))
  (message "Created attribute slot in fragment file: %s" beta-connected-fragment-file))

(defun beta-convert-region-to-descriptor-slot-on-fragment-file (begin end slot-name)
  (interactive    
   (list (region-beginning)
	 (region-end)
         (read-string "Enter SLOT name: ")))
  (beta-find-fragment-separator)
  (save-excursion
    (save-restriction
      (copy-to-register ?A begin end t)
      (insert-string (concat "<<SLOT " slot-name beta-descriptor-slot ">>"))
      (set-buffer beta-connected-fragment-file)
      (if (not (looking-at "^")) (insert-string "\n"))
      (insert-string (concat "--- " slot-name beta-descriptor-slot " ---\n"))
      (insert-string "(# do\n")
      (insert-register ?A t)
      (if (not (looking-at "^")) (insert-string "\n"))
      (insert-string "#)\n")
      ))
  (message "Created descriptor slot in fragment file: %s" beta-connected-fragment-file))

(defun beta-convert-region-to-dopart-slot-on-fragment-file (begin end slot-name)
  (interactive    
   (list (region-beginning)
	 (region-end)
         (read-string "Enter SLOT name: ")))
  (beta-find-fragment-separator)
  (save-excursion
    (save-restriction
      (copy-to-register ?A begin end t)
      (insert-string (concat "<<SLOT " slot-name beta-dopart-slot ">>"))
      (set-buffer beta-connected-fragment-file)
      (if (not (looking-at "^")) (insert-string "\n"))
      (insert-string (concat "--- " slot-name beta-dopart-slot " ---\n"))
      (insert-register ?A t)
      (if (not (looking-at "^")) (insert-string "\n"))
      ))
  (message "Created dopart slot in fragment file: %s" beta-connected-fragment-file))

(defun beta-connect-fragment-file (buffer)
  (interactive (list (find-file-noselect
		      (read-file-name "Which fragment-group file: "
				      default-directory t))))
  (save-excursion
    (save-restriction
      (make-variable-buffer-local 'beta-connected-fragment-file)
      (setq beta-connected-fragment-file buffer)
      (set-buffer buffer)
      )))

(defun beta-find-fragment-separator()
  (save-excursion
    (save-restriction
      (if (not (bufferp beta-connected-fragment-file))
	  (error "No connected fragment file: Connect using 'beta-connect-fragment-file [\\C-c\\C-b\\C-c]"))
      (set-buffer beta-connected-fragment-file)
      (if (re-search-forward "--+[\n\t ]*[a-zA-Z]+[\n\t ]*:[\n\t ]*[a-zA-Z]+[\n\t ]*--+"
			     (point-max) t)
	  (goto-char (match-beginning 0))
	(if (re-search-forward  "--+[\n\t ]*]]" (point-max) t)
	    (goto-char (match-beginning 0))
	  (goto-char (point-max))
	  (if (not (looking-at "^")) (insert-string "\n"))
	  (let ((here (point)))
	    (goto-char here)
	    (re-search-backward "[\n\t ]*")
	    ))))))

(defun beta-comment-justify-macro ()
  (setq last-kbd-macro
	[19 40 42 2 2 escape 120 98 101 116 97 45 99 111 109 109 return 6 6]))

(defun beta-70-comment-justify-buffer ()
  (interactive)
  (beginning-of-buffer)
  (beta-comment-justify-macro)
  (let ((fill-column 70))
    (while t 
      (call-last-kbd-macro))))
 
(defun beta-67-comment-justify-buffer ()
  (interactive)
  (beginning-of-buffer)
  (beta-comment-justify-macro)
  (let ((fill-column 67))
    (while t 
      (call-last-kbd-macro))))
   

(defun beta-wrap-comment()
  "Wrap comments placed after : or :< to next line."
  (interactive)
  (save-excursion
    (let ((case-fold-search t))
      (goto-char (point-min))
      (replace-regexp "\\(:<?\\)[\t ]*(\\*" "\\1
 (*" nil)
      )
    (indent-buffer)))
