;;; html-mode: Major mode for editing HTML hypertext documents.
;;; Adapted by pa@mjolner.com for editing MIADOC manuals

;;; ------------------------------ INSTRUCTIONS ------------------------------
;; 
;;  Put the following code in your .emacs file:
;; 
;;  (setq betalib (getenv "BETALIB"))
;;  (if (not betalib) (setq betalib "/users/beta/r5.2"))
;;  
;;  (setq load-path (append (list (format "%s/doc/bin" betalib)) load-path))
;;  
;;  (autoload 'html-mode "html-mode" "HTML major mode." t)
;;  (or (assoc "\\.html$" auto-mode-alist)
;;    (setq auto-mode-alist (cons '("\\.html$" . html-mode) auto-mode-alist)))
;; 
;;  ;;Emacs will then detect the ``.html'' suffix and activate html-mode
;;  ;;appropriately.
;;
;;  ;; Suggestion for use in editing MIADOC manuals:
;;  (defun myhtml ()
;;    (interactive)
;;    (local-set-key [f1]   (function (lambda () (interactive)(html-add-code 1))))
;;    (local-set-key [f2]   (function (lambda () (interactive)(html-add-bold 1))))
;;    (local-set-key [f3]   (function (lambda () (interactive)(html-add-emphasis 1))))
;;    (local-set-key [f4]   (function (lambda () (interactive)(html-add-beta 1))))
;;    (local-set-key [f5]   (function (lambda () (interactive)(html-add-fig 1))))
;;    (local-set-key [f6]   (function (lambda () (interactive)(html-add-inx 1))))
;;  )
;;  
;;  (setq html-mode-hook 'myhtml)
;;


;; Copyright (C) 1985 Free Software Foundation, Inc.
;; Copyright (C) 1992, 1993 National Center for Supercomputing Applications.
;; NCSA modifications by Marc Andreessen (marca@ncsa.uiuc.edu).
;; Copyright (C) 1995 Howard R. Melman <melman@osf.org>

;;
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You didn't receive a copy of the GNU General Public License along
;; with this program; so, write to the Free Software Foundation, Inc.,
;; 675 Mass Ave, Cambridge, MA 02139, USA.

;; This package has only been tested with GNU Emacs 19.28.
;;
;; HISTORY:
;;   3.0:  Created: 12 May 1995 by Howard R. Melman <melman@osf.org>

;;; Commentary:
;;    One of theories in the design of this mode is that people can
;;    type in the buffer better than they can in the minibuffer.
;;    Therefore very few values are prompted for, but instead the tags
;;    are inserted in the text and point positioned relevantly.
;;    None of the commands change mark.  For all commands where it makes
;;    sense, a prefix arguement means to operate on the region.  This
;;    means there are no extra commands or bindings to learn (or to
;;    fit on menus).
;;
;;    The keys bindings are long, but they do meet Emacs style.
;;    No commands are bound to C-c <letter>, leaving these for the
;;    user.  (They can decide if  C-c t will be <TITLE> or <TABLE> :-)

;;  This package is based on:
;;    html-mode.el   version 2.0  by Marc Andresssen
;;    html-extras.el version 1.12 by Sean Dowd. 

;;; TODO
;;    - support Xemacs menus
;;    - write html-initialize-document
;;    - be more intelligent about html, header, body and title markups

;;; New in this version:
;;    - Removed trailing space from <LI>'s so they work as paragraph separators
;;    - Added support for Netscape previewing
;;    - rewrote forms
;;    - generalize strings in html-font-lock-keywords (not just HREF and SRC)
;;    - removed highlighting (not Font-Lock) support
;;    - changed previewer to use cci.el
;;    - removed all of the quotify-hrefs stuff
;;    - had to move html-title to C-c C-d
;;    - added tables
;;    - got rid of html-real-*, use quoted-insert instead
;;    - added alternative text for html-add-img
;;    - added w3 support for the previewer
;;    - rewrote html-preview-document to use CCI
;;    - Stop using html-add-header-num
;;    - Added <U>
;;    - Added <SUP> and <SUB> and <DFN>
;;    - Added forms support from html-extras.el
;;    - Took html, head, and body commands from html-extras.el.
;;      Do I need to bind these to keys?
;;    - Added <BR> and <HR> commands and markup-internal 
;;    - Incorparated all and renamed some list commands
;;    - Rewrote link and reference commands removing the need for
;;      separate "region" versions of the commands.  Removed those
;;      from the menus
;;    - Added html-quote and html-real-quote (do I need these?)
;;    - Added html-add-header-num
;;    - Added comment-indent-function from sgml-mode.
;;    - Added paragraph variable settings from sgml-mode.
;;    - Changed key bindings for character formatting commands to be
;;      on C-c C-c
;;    - Wrote html-add-tag-internal and rewrote commands to use it.  
;;      Now most formatting commands can work on a region automatically.
;;    - Added comment support.  
;;    - Removed support for deprecated HTML elements:
;;         html-add-listing
;;         html-add-plaintext
;;    - Changed definition of C-c z to be (fboundp 'signal-process)
;;      instead of html-running-lemacs.  html-preview-document does
;;      work on GNU Emacs 19.
;;    - Changed html-document-previewer to be "Mosaic" not "xmosaic".
;;    - Font-lock-mode turned on in GNU Emacs 19.  All decisions based
;;      on (fboundp 'font-lock-mode) not html-running-lemacs.  Should
;;      be using the same code for FSF and XEmacs.  Removed the "Hey
;;      Boss" message after fontifying.
;;    - Added HTML menus for GNU Emacs 19.
;; 

;;; ------------------------------- VARIABLES --------------------------------

(defvar html-use-font-lock (fboundp 'font-lock-mode)
  "*Flag to use font-lock for HTML directives in Emacs 19.  If non-NIL,
font-lock will be used.  Default is T if font-lock-mode is available;
NIL otherwise.")

(defvar html-previewer 'netscape
  "*Type of previewer to use.  If 'cci then CCI is used, else w3 is used.")

(defvar html-preview-new-window nil
  "*If non-nil browser will open a new window for the previewed document.")

;; old vars that will go away over time
(defvar html-running-lemacs (if (string-match "Lucid" emacs-version) t nil)
  "Non-nil if running Lucid Emacs.")

(defvar html-running-epoch (boundp 'epoch::version)
  "Non-nil if running Epoch.")

;;; ------------------------INTERNAL VARIABLES--------------------------------

(defvar html-mode-version "3.0"
  "Version number of html-mode.el")

(defvar html-mode-syntax-table nil
  "Syntax table used while in html mode.")

(defvar html-mode-abbrev-table nil
  "Abbrev table used while in html mode.")
(define-abbrev-table 'html-mode-abbrev-table ())

(if html-mode-syntax-table
    ()
  (setq html-mode-syntax-table (make-syntax-table))
  ;; anything to do for something like &amp;
;;  (modify-syntax-entry ?<  "(>"  html-mode-syntax-table)
;;  (modify-syntax-entry ?>  ")<"  html-mode-syntax-table)
;;  (modify-syntax-entry ?=  ". "  html-mode-syntax-table)
  (modify-syntax-entry ?\" ". "  html-mode-syntax-table)
  (modify-syntax-entry ?\\ ". "  html-mode-syntax-table)
  (modify-syntax-entry ?'  "w "  html-mode-syntax-table))

(defvar html-mode-map nil 
  "Keymap used in HTML mode")
(if html-mode-map
    ()
  (setq html-mode-map (make-sparse-keymap))
  (define-key html-mode-map "&"            'html-ampersand)
  (define-key html-mode-map "<"            'html-less-than)
  (define-key html-mode-map ">"            'html-greater-than)
;  (define-key html-mode-map "\""           'html-quote)
  (define-key html-mode-map "\C-c1"        'html-add-header-1)
  (define-key html-mode-map "\C-c2"        'html-add-header-2)
  (define-key html-mode-map "\C-c3"        'html-add-header-3)
  (define-key html-mode-map "\C-c4"        'html-add-header-4)
  (define-key html-mode-map "\C-c5"        'html-add-header-5)
  (define-key html-mode-map "\C-c6"        'html-add-header-6)
  (define-key html-mode-map "\C-c\C-a"     'html-add-address)
  (define-key html-mode-map "\C-c\C-b"     'html-add-blockquote)
  (define-key html-mode-map "\C-c\C-c\C-b" 'html-add-bold)
  (define-key html-mode-map "\C-c\C-c\C-f" 'html-add-fixed)
  (define-key html-mode-map "\C-c\C-c\C-i" 'html-add-italics)
  (define-key html-mode-map "\C-c\C-c\C-u" 'html-add-underline)
  (define-key html-mode-map "\C-c\C-cb"    'html-add-subscript)
  (define-key html-mode-map "\C-c\C-cp"    'html-add-superscript)
  (define-key html-mode-map "\C-c\C-ca"    'html-add-sample)
  (define-key html-mode-map "\C-c\C-cc"    'html-add-citation)
  (define-key html-mode-map "\C-c\C-cd"    'html-add-definition)
  (define-key html-mode-map "\C-c\C-ce"    'html-add-emphasis)
  (define-key html-mode-map "\C-c\C-ck"    'html-add-keyboard)
  (define-key html-mode-map "\C-c\C-co"    'html-add-code)
  (define-key html-mode-map "\C-c\C-cs"    'html-add-strong)
  (define-key html-mode-map "\C-c\C-cv"    'html-add-variable)
  (define-key html-mode-map "\C-c\C-d"     'html-add-title)
  (define-key html-mode-map "\C-c\C-ff"    'html-add-form)
  (define-key html-mode-map "\C-c\C-fi"    'html-add-form-input)
  (define-key html-mode-map "\C-c\C-fb"    'html-add-form-button)
  (define-key html-mode-map "\C-c\C-fs"    'html-add-form-select)
  (define-key html-mode-map "\C-c\C-fo"    'html-add-form-option)
  (define-key html-mode-map "\C-c\C-ft"    'html-add-form-textarea)
  (define-key html-mode-map "\C-c\C-i"     'html-add-img)
  (define-key html-mode-map "\C-c\C-k"     'html-add-link)
  (define-key html-mode-map "\C-c\C-ld"    'html-add-definition-list)
  (define-key html-mode-map "\C-c\C-li"    'html-add-list-item)
  (define-key html-mode-map "\C-c\C-lm"    'html-add-menu)
  (define-key html-mode-map "\C-c\C-lo"    'html-add-ordered-list)
  (define-key html-mode-map "\C-c\C-lt"    'html-add-definition-term)
  (define-key html-mode-map "\C-c\C-lu"    'html-add-unordered-list)
  (define-key html-mode-map "\C-c\C-p"     'html-add-preformatted)
  (define-key html-mode-map "\C-c\C-r"     'html-add-named-anchor)
  (define-key html-mode-map "\C-c\C-tt"    'html-add-table)
  (define-key html-mode-map "\C-c\C-tc"    'html-add-table-caption)
  (define-key html-mode-map "\C-c\C-tr"    'html-add-table-row)
  (define-key html-mode-map "\C-c\C-td"    'html-add-table-data)
  (define-key html-mode-map "\C-c\C-th"    'html-add-table-header)
  (define-key html-mode-map "\C-c\C-xb"    'html-add-br)
  (define-key html-mode-map "\C-c\C-xh"    'html-add-hr)
  (define-key html-mode-map "\C-c\C-xp"    'html-add-paragraph-separator)
  (define-key html-mode-map "\t"           'tab-to-tab-stop)
  (and (fboundp 'signal-process)
       (define-key html-mode-map "\C-c\C-z" 'html-preview-document))
)

;;; ------------------------------- html-mode --------------------------------

;;;###autoload
(defun html-mode ()
  "Major mode for editing HTML hypertext documents.

Turning on html-mode calls the value of the variable text-mode-hook, 
sgml-mode-hook, and html-mode-hook in that order, if those values are non-nil.

Special commands:
\\{html-mode-map}"
  (interactive)
  (kill-all-local-variables)
  (use-local-map html-mode-map)
  (setq mode-name "HTML")
  (setq major-mode 'html-mode)
  (setq local-abbrev-table html-mode-abbrev-table)
  (set-syntax-table html-mode-syntax-table)
  ;; Comment stuff
  (make-local-variable 'comment-start)
  (setq comment-start "<!-- ")
  (make-local-variable 'comment-end)
  (setq comment-end " -->")
  (make-local-variable 'comment-column)
  (setq comment-column 0)
  (make-local-variable 'comment-start-skip) ; This allows recoginition of
  (setq comment-start-skip "--[ \t]*")      ; existing comments in declarations
  (make-local-variable 'comment-indent-function)
  (setq comment-indent-function 'html-comment-indent)
  ;; Paragraph stuff
  (make-local-variable 'paragraph-start)
  ;; A start or end tag by itself on a line separates a paragraph.
  ;; This is desirable because SGML discards a newline that appears
  ;; immediately after a start tag or immediately before an end tag.
  (setq paragraph-start
	"^[ \t\n]\\|\
\\(</?\\([A-Za-z]\\([-.A-Za-z0-9= \t\n]\\|\"[^\"]*\"\\|'[^']*'\\)*\\)?>$\\)")
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate
	"^[ \t\n]*$\\|\
^</?\\([A-Za-z]\\([-.A-Za-z0-9= \t\n]\\|\"[^\"]*\"\\|'[^']*'\\)*\\)?>$")
  ;; Do the hooks
  (run-hooks 'text-mode-hook 'sgml-mode-hook 'html-mode-hook)
  (and html-use-font-lock (html-fontify)))

(defun html-comment-indent ()
  (if (and (looking-at "--")
	   (not (and (eq (char-after (1- (point))) ?!)
		     (eq (char-after (- (point) 2)) ?<))))
      (progn
	(skip-chars-backward " \t")
	(max comment-column (1+ (current-column))))
    0))

;;; -------------------------------- Commands --------------------------------

(defun html-add-html (&optional arg)
  "Create a <HTML></HTML> pair."
  (interactive "*")
  (html-add-tag-internal "HTML" arg t))

(defun html-add-head (&optional arg)
  "Create a <HEAD></HEAD> pair."
  (interactive "*")
  (html-add-tag-internal "HEAD" arg t))

(defun html-add-body (&optional arg)
  "Create a <BODY></BODY> pair."
  (interactive "*")
  (html-add-tag-internal "BODY" arg t))

(defun html-add-header (size &optional arg)
  "Add a header."
  (interactive "*sSize (1-6; 1 biggest): \nP")
  (html-add-tag-internal (concat "H" size) arg))

;; this is neat but if bound to keys, screws up menus
;; in menus all the key bindings say C-c 6
(defun html-add-header-num (&optional arg)
  "Add a header of size based on the number of the key bound to.
This must only be bound to a key sequence ending in the keys 1 to 6."
  (interactive "*P")
  (html-add-tag-internal (concat "H" (char-to-string last-command-event))
                         arg))

(defun html-add-header-1 (&optional arg)
  "Add a level 1 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "1" arg))

(defun html-add-header-2 (&optional arg)
  "Add a level 2 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "2" arg))

(defun html-add-header-3 (&optional arg)
  "Add a level 3 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "3" arg))

(defun html-add-header-4 (&optional arg)
  "Add a level 4 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "4" arg))

(defun html-add-header-5 (&optional arg)
  "Add a level 5 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "5" arg))

(defun html-add-header-6 (&optional arg)
  "Add a level 6 header.
If called with a PREFIX argument surround region with header markup."
  (interactive "*P")
  (html-add-header "6" arg))

(defun html-add-img (href alt)
  "Add an imbedded image with alternative text."
  (interactive "sImage URL: \nsAlternative Text: ")
  (insert "<IMG SRC=\"" href "\" ALT=\"" alt "\">"))

(defun html-add-link (link &optional arg)
  "Add a link."
  (interactive "*sLink to: \nP")
  (html-add-anchor-internal "HREF" link arg))

(defun html-add-named-anchor (ref &optional arg)
  "Add a reference (named anchor)."
  (interactive "*sAnchor name: \nP")
  (html-add-anchor-internal "NAME" ref arg))

(defun html-add-title (title)
  "Add a title or change an existing one."
  (interactive "sTitle: ")
  (save-excursion
    (goto-char (point-min))
    (if (and (looking-at "<TITLE>")
             (save-excursion
               (forward-char 7)
               (re-search-forward "[^<]*" 
                                  (save-excursion (end-of-line) (point)) 
                                  t)))
        ;; Plop the new title in its place.
        (replace-match title t)
      (insert "<TITLE>" title "</TITLE>\n"))))

(defun html-add-paragraph-separator ()
  "Add a paragraph separator."
  (interactive "*")
  (html-add-markup-internal "P"))

(defun html-add-br ()
  "Add a line break."
  (interactive "*")
  (html-add-markup-internal "BR"))

(defun html-add-hr ()
  "Add a horizontal line."
  (interactive "*")
  (html-add-markup-internal "HR"))

;;; ----------------  Formatting Commands --------------------

(defun html-add-address (&optional arg)
  "Add an address formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with address."
  (interactive "*P")
  (html-add-tag-internal "ADDRESS" arg t))

(defun html-add-blockquote (&optional arg)
  "Add a blockquote formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with blockquote markup."
  (interactive "*P")
  (html-add-tag-internal "BLOCKQUOTE" arg t))

(defun html-add-preformatted (&optional arg)
  "Add a preformatted formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with preformatted markup."
  (interactive "*P")
  (html-add-tag-internal "PRE" arg t))

(defun html-add-beta (&optional arg)
  "Add BETA tags.
If called with a PREFIX argument surround region with preformatted markup."
  (interactive "*P")
  (html-add-tag-internal "BETA" arg t))

(defun html-add-fig (&optional arg)
  "Add FIG tags.
If called with a PREFIX argument surround region with preformatted markup."
  (interactive "*P")
  (html-add-tag-internal "FIG" arg))

(defun html-add-inx (&optional arg)
  "Add BETA tags.
If called with a PREFIX argument surround region with preformatted markup."
  (interactive "*P")
  (html-add-tag-internal "INX" arg))

;;; ---------------- Character Formatting Commands --------------------

(defun html-add-emphasis (&optional arg)
  "Add an emphasis formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with emphasis."
  (interactive "*P")
  (html-add-tag-internal "EM" arg))

(defun html-add-citation (&optional arg)
  "Add a citation formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with citation."
  (interactive "*P")
  (html-add-tag-internal "CITE" arg))

(defun html-add-strong (&optional arg)
  "Add a strong formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with strong."
  (interactive "*P")
  (html-add-tag-internal "STRONG" arg))

(defun html-add-code (&optional arg)
  "Add a code formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with code."
  (interactive "*P")
  (html-add-tag-internal "CODE" arg))

(defun html-add-sample (&optional arg)
  "Add a sample formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with sample."
  (interactive "*P")
  (html-add-tag-internal "SAMP" arg))

(defun html-add-keyboard (&optional arg)
  "Add a keyboard formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with keyboard."
  (interactive "*P")
  (html-add-tag-internal "KBD" arg))

(defun html-add-variable (&optional arg)
  "Add a variable formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with variable."
  (interactive "*P")
  (html-add-tag-internal "VAR" arg))

;;; --- New in HTML 3.0 ---

(defun html-add-definition (&optional arg)
  "Add a definition formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with definition."
  (interactive "*P")
  (html-add-tag-internal "DFN" arg))

;;; ---------------- Font Style Commands --------------------

(defun html-add-bold (&optional arg)
  "Add a bold formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with bold."
  (interactive "*P")
  (html-add-tag-internal "B" arg))

(defun html-add-italics (&optional arg)
  "Add an italics formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with italics."
  (interactive "*P")
  (html-add-tag-internal "I" arg))

(defun html-add-fixed (&optional arg)
  "Add a fixed formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with fixed."
  (interactive "*P")
  (html-add-tag-internal "TT" arg))

(defun html-add-underline (&optional arg)
  "Add an underline formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with underline."
  (interactive "*P")
  (html-add-tag-internal "U" arg))

;;; --- New in HTML 3.0 ---

(defun html-add-superscript (&optional arg)
  "Add a superscript formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with superscript."
  (interactive "*P")
  (html-add-tag-internal "SUP" arg))

(defun html-add-subscript (&optional arg)
  "Add a subscript formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with subcript."
  (interactive "*P")
  (html-add-tag-internal "SUB" arg))

;;; -------------------- Special Character Commands --------------------

(defun html-less-than ()
  "Insert the HTML escape sequence representing a <.
To insert a real < type: \\[quoted-insert] <"
  (interactive "*")
  (insert "&lt;"))

(defun html-greater-than ()
  "Insert the HTML escape sequence representing a >.
To insert a real > type: \\[quoted-insert] >"
  (interactive "*")
  (insert "&gt;"))

(defun html-ampersand ()
  "Insert the HTML escape sequence representing an &.
To insert a real & type: \\[quoted-insert] &"
  (interactive "*")
  (insert "&amp;"))

(defun html-quote ()
  "Insert the HTML escape sequence for a `\"'."
  (interactive "*")
  (insert "&quot;"))

;;; --------------------------- List Commands -------------------------------

(defun html-add-menu ()
  "Add a menu."
  (interactive "*")
  (html-add-list-internal "MENU"))

(defun html-add-ordered-list ()
  "Add an ordered list."
  (interactive "*")
  (html-add-list-internal "OL"))

(defun html-add-unordered-list ()
  "Add an unordered list."
  (interactive "*")
  (html-add-list-internal "UL"))

(defun html-add-list-item ()
  "Add a list or menu item at the beginning of a line."
  (interactive "*")
  (if (not (bolp)) (insert "\n"))
  (insert "<LI>"))

(defun html-add-definition-list ()
  "Add a definition list."
  (interactive "*")
  (insert "<DL>\n")
  (insert "<DT>")
  ;; Point goes right there.
  (save-excursion
    (insert "\n<DD>\n</DL>\n")))

(defun html-add-definition-term ()
  "Add a definition entry.  Assume we're at the end of a previous entry."
  (interactive "*")
  (if (not (bolp)) (insert "\n"))
  (insert "<DT>")
  (save-excursion
    (insert "\n<DD>")))

;;; ------------------------ Forms Commands ------------------------

(defvar html-valid-buttons
  '(("checkbox" 1) ("radio" 2) ("submit" 3) ("reset" 4))
  "Valid button types for html-add-form-button.")

(defvar html-valid-inputs
  '(("checkbox" 1) ("radio" 2) ("submit" 3) ("reset" 4)
    ("text" 5) ("password" 6) ("hidden" 7))
  "Valid input types for html-add-form-input.")

(defun html-add-form (action)
  "Create a form"
  (interactive (list (read-string "Action: " "/cgi-bin/")))
  (insert "<FORM ACTION=\"" action "\" METHOD=POST>\n")
  (save-excursion
    (insert "\n")
    (html-add-form-button "submit" "Submit" "submit")
    (html-add-form-button "reset" "Reset" "reset")
    (insert "</FORM>\n")
    (exchange-point-and-mark)))

(defun html-add-form-input (type name)
  "Create an input field"
  (interactive (list 
                (completing-read "Type: " html-valid-inputs nil t)
                (read-string "Name: ")))
  (insert "<INPUT TYPE=\"" type "\"NAME=\"" name "\">"))

(defun html-add-form-button (type name value &optional arg)
  "Create a button"
  (interactive (list 
                (completing-read "Type: " html-valid-buttons nil t)
                (read-string "Name: ")  ; not s/r
                (read-string "Value: ")
                current-prefix-arg))    ; not s/r
  (or (assoc type html-valid-buttons)
      (error "Invalid button type."))
  (insert "<INPUT TYPE=\"" type "\""
          " NAME=\"" name "\"")
  (if (not (string= value "")) (insert " VALUE=\"" value "\""))
  (if arg (insert " CHECKED"))
  (insert ">\n"))

(defun html-add-form-select (name &optional arg)
  "Add a select formatting directive to the buffer leaving point inside.
Optional PREFIX argument means to mark select as `MULTIPLE'."
  (interactive "*sName: ")
  (insert "<SELECT NAME=\"" name "\""
          (if arg " MULTIPLE") ">\n")
  (save-excursion
    (insert"</SELECT>\n")))

(defun html-add-form-option (&optional arg)
  "Add an option item at the beginning of a line.
Optional PREFIX argument means to mark option as `SELECTED'."
  (interactive "*P")
  (if (not (bolp)) (insert "\n"))
  (insert "<OPTION" (if arg " SELECTED") "> "))

(defun html-add-form-textarea (name rows cols)
  "Add a textarea formatting directive to the buffer leaving point inside."
  (interactive "*sName: \nsRows: \nsColumns: ")
  (insert "<TEXTAREA NAME=\"" name "\""
          "ROWS=" rows " "
          "COLS=" cols ">")
  (save-excursion
    (insert "</TEXTAREA>\n")))

;;; ------------------------ Table Commands ------------------------
(defun html-add-table (&optional arg)
  "Add a table formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with table."
  (interactive "*P")
  (html-add-tag-internal "TABLE" arg t))

(defun html-add-table-caption (&optional arg)
  "Add a caption formatting directive to buffer leaving point inside.
If called with a PREFIX argument surround region with caption."
  (interactive "*P")
  (html-add-tag-internal "CAPTION" arg t))

(defun html-add-table-row ()
  "Add a table row."
  (interactive "*")
  (html-add-markup-internal "TR"))

(defun html-add-table-data (&optional arg)
  "Add a table data directive to buffer leaving point inside.
If called with a PREFIX argument surround region with table data."
  (interactive "*P")
  (html-add-tag-internal "TD" arg))

(defun html-add-table-header (&optional arg)
  "Add a table header directive to buffer leaving point inside.
If called with a PREFIX argument surround region with table header."
  (interactive "*P")
  (html-add-tag-internal "TH" arg))

;;; ------------------------ INTERNAL FUNCTIONS ------------------------------

(defun html-add-tag-internal (tag arg &optional area)
  "Add an HTML TAG to document leaving point within.
If ARG is non-nil surround region with beginning and ending TAG.
If optional AREA is non-nil insert extra newlines"
  (if arg
      (let ((start (min (mark) (point)))
            (end   (max (mark) (point))))
        (save-excursion
          ;; use trick since the first (insert) changes location of end
          (goto-char end)
          (save-excursion
            (goto-char start)
            (insert "<" tag ">")
            (if area (insert "\n")))
          (insert "</" tag ">")
          (if area (insert "\n"))))
    (insert "<" tag ">")
    (if area (insert "\n"))
    (save-excursion
     (insert "</" tag ">")
     (if area (insert "\n")))))

(defun html-add-list-internal (type)
  "Insert begin/end pair of a TYPE of list and create an initial element.  
Single argument TYPE is a string, assumed to be a valid HTML list type
(e.g. \"UL\" or \"OL\")."
  (insert "<" type ">\n<LI>")
  ;; Point goes right there.
  (save-excursion
    (insert "\n</" type ">\n")))

(defun html-add-markup-internal (markup &optional newline)
  "Add a markup."
  (interactive "*")
  (insert "<" markup ">" (if newline "\n" "")))

(defun html-add-anchor-internal (type tag &optional arg)
  "Add a some form of anchor."
  (if arg
      (let ((start (min (mark) (point)))
            (end   (max (mark) (point))))
        (save-excursion
          (goto-char end)
          (save-excursion
            (goto-char start)
            (insert "<A " type "=\"" tag "\">"))
          (insert "</A>")))
    (progn
      (insert "<A " type "=\"" tag "\">")
      (save-excursion
        (insert "</A>")))))

;;; --------------------------- PREVIEWING ----------------------------
;;; This replaces the remote control hack with the CCI interface.

(defvar html-preview-tmp-number 0
  "Number added to temporary names 
since make-temp-name is unique per process, not per call.")

(defun html-preview-document ()
  "Preview the current buffer's HTML document using a CCI connection."
  (interactive)
  (let* (html-proc
         (ready t)
         (tmp-file (concat
                    (make-temp-name
                     ;; using the current directory is important so
                     ;; relative anchors in the document work
                     (file-name-directory (buffer-file-name)))
                    ;; this puts the same extension on the filename
                    ;; this way a .html is probably added so that
                    ;; <HTML> is not needed in doc to tell browser
                    ;; what the data is.
                    (int-to-string html-preview-tmp-number)
                    (file-name-nondirectory (buffer-file-name))))
         (url (concat "file:" tmp-file)))
    (write-region (point-min) (point-max) tmp-file nil 'foo)
    (cond ((eq html-previewer 'cci)
           (progn
             (require 'cci)
             (cci-get-url url html-preview-new-window)
             (setq ready nil)))
          ((eq html-previewer 'netscape)
           (shell-command  (concat "netscape -remote 'openURL("
                                   url
                                   (if html-preview-new-window ", new-window")
                                   ")'")))
          (t
           (w3-fetch url)))
    (or ready (sleep-for 3))
    (setq html-preview-tmp-number (1+ html-preview-tmp-number))
    (delete-file tmp-file)))

;;; -------------------------- Font-lock setup ---------------------------

(if (fboundp 'font-lock-mode)
    (progn
      (defconst html-font-lock-keywords
        (list
         '("\\(<[^>]*>\\)+" . font-lock-comment-face)
         '("<[^<>]*[a-zA-Z]+\\s-*=\\s-*\"\\([^\"]*\\)\"[^<>]*>" 1 font-lock-string-face t))
        "Patterns to highlight in HTML buffers.")

      (defun html-fontify ()
        (font-lock-mode 1)
        (make-local-variable 'font-lock-keywords) 
        (setq font-lock-keywords html-font-lock-keywords)
        (font-lock-hack-keywords (point-min) (point-max)))))

;;; -------------------------- FSF menubar setup ---------------------------

(condition-case nil
    (progn
      (define-key html-mode-map [menu-bar]
        (make-sparse-keymap "html-menu-bar"))
      (define-key html-mode-map [menu-bar tables]
        (cons "Tables" (make-sparse-keymap "Tables")))
      (define-key html-mode-map [menu-bar forms]
        (cons "Forms" (make-sparse-keymap "Fill-out Forms")))
      (define-key html-mode-map [menu-bar lists]
        (cons "Lists" (make-sparse-keymap "Lists")))
      (define-key html-mode-map [menu-bar chars]
        (cons "Char" (make-sparse-keymap "Character Formatting")))
      (define-key html-mode-map [menu-bar html]
        (cons "HTML" (make-sparse-keymap "HTML")))

      (defvar html-list-map (make-sparse-keymap "HTML Lists"))

      (define-key html-mode-map [menu-bar html html-preview-document]
        '("Preview Document" . html-preview-document))
      (define-key html-mode-map [menu-bar html separator-1]
        '("--"))
      (define-key html-mode-map [menu-bar html html-add-hr]
        '("Horizontal Line" . html-add-hr))
      (define-key html-mode-map [menu-bar html html-add-br]
        '("Line Break" . html-add-br))
      (define-key html-mode-map [menu-bar html html-add-paragraph-separator]
        '("End Paragraph" . html-add-paragraph-separator))
      (define-key html-mode-map [menu-bar html separator-2]
        '("--"))
      (define-key html-mode-map [menu-bar html html-add-blockquote]
        '("Blockquote" . html-add-blockquote))
      (define-key html-mode-map [menu-bar html html-add-address]
        '("Address" . html-add-address))
      (define-key html-mode-map [menu-bar html html-add-preformatted]
        '("Preformatted" . html-add-preformatted))
      (define-key html-mode-map [menu-bar html html-add-img]
        '("Inlined Image" . html-add-img))
      (define-key html-mode-map [menu-bar html html-add-named-anchor]
        '("Reference" . html-add-named-anchor))
      (define-key html-mode-map [menu-bar html html-add-link]
        '("Hyperlink" . html-add-link))
      (define-key html-mode-map [menu-bar html html-header-map]
        '("Header" . html-header-map))
      (define-key html-mode-map [menu-bar html html-add-title]
        '("Title" . html-add-title))

      (define-key html-mode-map [menu-bar chars html-add-underline]
        '("Underline" . html-add-underline))
      (define-key html-mode-map [menu-bar chars html-add-fixed]
        '("Fixed" . html-add-fixed))
      (define-key html-mode-map [menu-bar chars html-add-italics]
        '("Italics" . html-add-italics))
      (define-key html-mode-map [menu-bar chars html-add-bold]
        '("Bold" . html-add-bold))
      (define-key html-mode-map [menu-bar chars separator-3]
        '("--"))
      (define-key html-mode-map [menu-bar chars html-add-subscript]
        '("Subscript" . html-add-subscript))
      (define-key html-mode-map [menu-bar chars html-add-superscript]
        '("Superscript" . html-add-superscript))
      (define-key html-mode-map [menu-bar chars html-add-definition]
        '("Definition" . html-add-definition))
      (define-key html-mode-map [menu-bar chars html-add-variable]
        '("Variable" . html-add-variable))
      (define-key html-mode-map [menu-bar chars html-add-keyboard]
        '("Keyboard" . html-add-keyboard))
      (define-key html-mode-map [menu-bar chars html-add-sample]
        '("Sample" . html-add-sample))
      (define-key html-mode-map [menu-bar chars html-add-code]
        '("Code" . html-add-code))
      (define-key html-mode-map [menu-bar chars html-add-strong]
        '("Strong" . html-add-strong))
      (define-key html-mode-map [menu-bar chars html-add-citation]
        '("Citation" . html-add-citation))
      (define-key html-mode-map [menu-bar chars html-add-emphasis]
        '("Emphasized" . html-add-emphasis))

      (define-key html-mode-map [menu-bar lists html-add-definition-term]
        '("Definition Entry" . html-add-definition-term))
      (define-key html-mode-map [menu-bar lists html-add-definition-list]
        '("Definition List" . html-add-definition-list))
      (define-key html-mode-map [menu-bar lists html-add-list-item]
        '("List Or Menu Item" . html-add-list-item))
      (define-key html-mode-map [menu-bar lists html-add-ordered-list]
        '("Ordered List" . html-add-ordered-list))
      (define-key html-mode-map [menu-bar lists html-add-unorderedlist]
        '("Unordered List" . html-add-unordered-list))
      (define-key html-mode-map [menu-bar lists html-add-menu]
        '("Menu" . html-add-menu))

      (define-key html-mode-map [menu-bar tables html-add-table-row]
        '("Row" . html-add-table-row))
      (define-key html-mode-map [menu-bar tables html-add-table-data]
        '("Data" . html-add-table-data))
      (define-key html-mode-map [menu-bar tables html-add-table-header]
        '("Header" . html-add-table-header))
      (define-key html-mode-map [menu-bar tables html-add-table-caption]
        '("Caption" . html-add-table-caption))
      (define-key html-mode-map [menu-bar tables html-add-table]
        '("Table" . html-add-table))

      (define-key html-mode-map [menu-bar forms html-add-form-textarea]
        '("Textarea" . html-add-form-textarea))
      (define-key html-mode-map [menu-bar forms html-add-form-option]
        '("Option" . html-add-form-option))
      (define-key html-mode-map [menu-bar forms html-add-form-select]
        '("Select" . html-add-form-select))
      (define-key html-mode-map [menu-bar forms html-add-form-button]
        '("Button" . html-add-form-button))
      (define-key html-mode-map [menu-bar forms html-add-form-input]
        '("Input" . html-add-form-input))
      (define-key html-mode-map [menu-bar forms html-add-form]
        '("Form" . html-add-form))

      (defvar html-header-map (make-sparse-keymap "Header Size"))
      (define-key html-header-map "6" '("6" . html-add-header-6))
      (define-key html-header-map "5" '("5" . html-add-header-5))
      (define-key html-header-map "4" '("4" . html-add-header-4))
      (define-key html-header-map "3" '("3" . html-add-header-3))
      (define-key html-header-map "2" '("2" . html-add-header-2))
      (define-key html-header-map "1" '("1" . html-add-header-1))
      (fset 'html-header-map (symbol-value 'html-header-map))

      ;; RMS: mouse-3 should not select this menu.  mouse-3's global
      ;; definition is useful in HTML mode and we should not interfere
      ;; with that.  The menu is mainly for beginners, and for them,
      ;; the menubar requires less memory than a special click.
      t)
  (error nil))

;;; -------------------------- lucid menubar setup ---------------------------

(if html-running-lemacs
    (progn
      (defvar html-menu
        '("HTML Mode"
          ["Open Address"         html-add-address      t]
          ["Open Blockquote"      html-add-blockquote   t]
          ["Open Header"          html-add-header       t]
          ["Open Hyperlink"       html-add-link  t]
          ["Open Preformatted"    html-add-preformatted t]
          ["Open Reference"       html-add-named-anchor t]
          ["Open Title"           html-add-title        t]
          "----"
          ["Open Bold"            html-add-bold         t]
          ["Open Citation"        html-add-citation     t]
          ["Open Code"            html-add-code         t]
          ["Open Emphasized"      html-add-emphasized   t]
          ["Open Fixed"           html-add-fixed        t]
          ["Open Keyboard"        html-add-keyboard     t]
          ["Open Sample"          html-add-sample       t]
          ["Open Strong"          html-add-strong       t]
          ["Open Variable"        html-add-variable     t]
          "----"
          ["Add Inlined Image"    html-add-img          t]
          ["End Paragraph"        html-add-paragraph-separator t]
          ["Preview Document"     html-preview-document t]
          "----"
          ("Definition List ..."
           ["Open Definition List"    html-add-definition-list  t]
           ["Add Definition Entry"    html-add-definition-term t]
           )
          ("Other Lists ..."
           ["Open Unnumbered List"    html-add-unordered-list t]
           ["Open Numbered List"      html-add-ordered-list  t]
           ["Open Menu"               html-add-menu          t]
           "----"
           ["Add List Or Menu Item"   html-add-list-item   t]
           )           
          )
        )

      (defvar html-forms-menu
        '("Forms"
          ["Form"            html-open-form      t]
          ["Textarea"        html-form-textarea  t]
          ["Input Field"     html-form-input     t]
          ["Select"          html-form-select    t]
          ["Select Option"   html-form-select-option t]
          ["Scrolling List"  html-form-scrolllist t]
          ["Radio Item"      html-form-radio     t]
          ["Button"          html-form-button    t]
          "----"
          ("Formatting..."
           ["Make Region Bold"    html-make-region-bold   t]
           ["Make Region Italic"  html-make-region-italic t]
           )
          "----"
          ("Other..."
           ["Comment"        html-comment t]
           ["<HTML></HTML>"  html-html t]
           ["<HEAD></HEAD>"  html-head t]
           ["<BODY></BODY>"  html-body t]
           ["<LINK REV=..."  html-link-rev-made t]
           ["<HR ...>     "  html-hr t]
           ["<BR>         "  html-br t]
           )
          "----"
          ["HTML-Extras Version"          html-extras-version   t]
          ))

      (defun html-menu (e)
        (interactive "e")
        (mouse-set-point e)
        (beginning-of-line)
        (popup-menu html-menu))
      (define-key html-mode-map 'button3 'html-menu)

      (defun html-install-menubar ()
        (if (and current-menubar (not (assoc "HTML" current-menubar)))
            (progn
              (set-buffer-menubar (copy-sequence current-menubar))
              (add-menu nil "HTML" (cdr html-menu)))))
      (add-hook 'html-mode-hook 'html-install-menubar t)

      (defun html-install-form-menubar ()
        (if (and current-menubar (not (assoc "Forms" current-menubar)))
            (progn
              (set-buffer-menubar (copy-sequence current-menubar))
              (add-menu nil "Forms" (cdr html-forms-menu)))))
      (add-hook 'html-mode-hook 'html-install-form-menubar t)

      )
  )

(provide 'html-mode)

;;; html-mode.el ends here
