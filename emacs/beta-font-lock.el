;;; beta-font-lock.el --- using font-lock-mode with BETA.

;;; Copyright (C) 1996 Erik Ernst.

;;; Author: Erik Ernst <eernst@daimi.aau.dk>
;;; Version: 0.1
;;; Requires: GNU Emacs 19.30 or newer

;;; This program is free software; you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 2, or (at your option)
;;; any later version.

;;; This program is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.

;;; You should have received a copy of the GNU General Public License
;;; along with GNU Emacs; see the file COPYING.  If not, write to
;;; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                ;;;
;;;                   Using font-lock with BETA                    ;;;
;;;                                                                ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Adds support for font-lock decoration of BETA source code.
;;;
;;; To use this library, simply 'require' it in your mode hook 
;;; for BETA, '(require 'beta-font-lock)'.
;;;
;;; You must use 'add-hook' in stead of 'setq' when installing your
;;; beta-mode-hook; the facilities in this file are installed with 
;;; 'add-hook', and a subsequent '(setq beta-mode-hook ...)' will simply
;;; overwrite all previously added hooks.  So your normal beta-mode 
;;; customizations should be loaded with something like 
;;; '(add-hook 'beta-mode-hook 'mybeta)'.
;;;
;;; To make it possible for emacs to find this file, you must have the 
;;; path to it in your 'load-path'.  This might already be the case, 
;;; otherwise you can use something like
;;; '(setq load-path (cons "/usr/local/lib/beta/emacs/v1.6" load-path))'.
;;;
;;; NB: If you _do_not_ want to use "beta-menu19" you can execute
;;; '(setq beta-font-lock-insert-menus-p nil)'.  By default,
;;; beta-menu19 will be loaded if not already present, and 
;;; a few beta font lock specific menu items will be inserted 
;;; to allow selection between different font-lock styles.
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Executive summary:
;;;
;;;  (setq load-path (cons "/users/beta/emacs/v1.6" load-path)); if needed
;;; 
;;;  (defun mybeta () 
;;;    (interactive)
;;;    (require 'beta-font-lock)
;;;    <<your-usual-stuff-to-initialize-beta-mode>>)
;;;
;;;  (add-hook 'beta-mode-hook 'mybeta) ; NB: 'add-hook', not 'setq'
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require 'font-lock)
(require 'make-regexp)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Some regexps useful in defining
;; highlighting specifications; each
;; regexp selects a set of strings which
;; is somewhat ;-) well-defined in terms
;; of BETA and the fragment language
;; constructs
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; fragment language
(defconst beta-font-lock-property-regexp
  (eval-when-compile
    (concat "^\\("
	    (make-regexp '("ORIGIN" "BODY" "MDBODY" "INCLUDE"
			   "LIBFILE" "LINKOPT" "OBJFILE" "MAKE" "BUILD"))
	    "\\)\\(\\s *\\w*\\s '[^']*'\\)+;?")))
(defconst beta-font-lock-slotdecl-regexp
  ;; safer but slower: "--+\\s *\\w+\\s *:\\s *\\w+\\s *--+"
  "--+ *\\w+: *\\w+ *--+")
(defconst beta-font-lock-slotappl-regexp
  ;; safer but slower: "<<\\s *SLOT\\s *\\w+\\s *:\\s *\\w+\\s *>>"
  "<<SLOT +\\w+: *\\w+>>")
(defconst beta-font-lock-fragment-regexp
  ;; quick-and-dirty
  (eval-when-compile
    (concat "\\(^\\("
	    (make-regexp '("ORIGIN" "BODY" "MDBODY" "INCLUDE"
			   "LIBFILE" "LINKOPT" "OBJFILE" "MAKE" "BUILD"))
	    "\\)\\)\\|"
	    "\\(--+[a-z_0-9: \\t]*--+\\)\\|"
	    "\\(<<SLOT [a-z_0-9:]*>>\\)")))

;; many-line construct markers: object descriptors, control structure stm.s
(defconst beta-font-lock-scope-regexp
  (eval-when-compile
    (make-regexp '("(#" "#)"
		   "(if\\>" "\\<if)"
		   "(for\\>" "\\<for)"
		   "(code\\>" "\\<code)"
		   "\\<then\\>" "\\<else\\>" "\\<repeat\\>" "//"))))

;; important for understanding overall structure
(defconst beta-font-lock-structurekeyword-regexp
  (eval-when-compile
    (concat "\\<\\("
	    (make-regexp '("do" "enter" "exit"))
	    "\\)\\>")))

(defconst beta-font-lock-structurestatement-regexp
  (eval-when-compile
    (concat "\\<\\("
	    (make-regexp '("leave" "restart" "suspend" "inner"))
	    "\\)\\>")))

;; other keywords
(defconst beta-font-lock-keyword-regexp
  (eval-when-compile
    (concat "\\<\\("
	    (make-regexp '("this" "not" "div" "mod" "or" "xor" "and"))
	    "\\)\\>"
	    "\\|\\+\\|-\\|\\*\\|/\\|=\\|>\\|<")))

;; basic patterns and values
(defconst beta-font-lock-basic-regexp
  (eval-when-compile
    (concat "\\<\\("
	    (make-regexp '("integer" "char" "boolean" "real"
			   "shortint" "data" "true" "false" "none"))
	    "\\)\\>")))

;; declaration markers
(setq beta-font-lock-decl-regexp
  ;; safer but slower: "\\(\\(\\w+\\s *,\\s *\\)*\\w+\\s *\\):"
  "\\(\\(\\w+, *\\)*\\w+\\):")
(defconst beta-font-lock-patterndecl-regexp
  (eval-when-compile
    (concat beta-font-lock-decl-regexp "\\s *\\((#\\|(\\*\\|\\w\\)")))
(defconst beta-font-lock-virtualdecl-regexp
  (eval-when-compile
    (concat beta-font-lock-decl-regexp "<")))
(defconst beta-font-lock-furtherdecl-regexp
  (eval-when-compile
    (concat beta-font-lock-decl-regexp "\\(:<\\|:\\)")))
(defconst beta-font-lock-substancedecl-regexp
  (eval-when-compile
    (concat beta-font-lock-decl-regexp "\\s *\\(@\\|\\^\\|##\\|\\[\\)")))

;; Coercion -- "get me a reference value", "get me a pattern value"
(defconst beta-font-lock-coercion-regexp
  "\\w+\\s *\\(##\\|\\[\\]\\)")

;; dynamic instance creation
(defconst beta-font-lock-new-regexp
  ;; safer but slower: "\&\\s *\\(\\w+\\|(#\\)"
  "\&\\(w+\\|(#\\)")


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  A few faces special for BETA
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar beta-font-lock-fragment-face
  'beta-font-lock-fragment-face
  "Face to use for fragment language expressions")

(defvar beta-font-lock-fragmentdecl-face
  'beta-font-lock-fragmentdecl-face
  "Face to use for fragment language declarations")

(defvar beta-font-lock-fragmentappl-face
  'beta-font-lock-fragmentappl-face
  "Face to use for fragment language references")

(defvar beta-font-lock-block-face
  'beta-font-lock-block-face
  "Face to use for block/scope delimiters")

(defvar beta-font-lock-structurestatement-face
  'beta-font-lock-structurestatement-face
  "Face to use for structurally important statements")

(defvar beta-font-lock-basic-face
  'beta-font-lock-basic-face
  "Face to use for names of basic types and values")

(defvar beta-font-lock-pdecl-face
  'beta-font-lock-pdecl-face
  "Face to use for pattern declarations")

(defvar beta-font-lock-vdecl-face
  'beta-font-lock-vdecl-face
  "Face to ude for virtual declarations")

(defvar beta-font-lock-fdecl-face
  'beta-font-lock-fdecl-face
  "Face to ude for virtual further binding or final declarations")

(defvar beta-font-lock-sdecl-face
  'beta-font-lock-sdecl-face
  "Face to use for declarations of substance")

(defvar beta-font-lock-face-defs
  ;; (FACE FOREGROUND BACKGROUND BOLD-P ITALIC-P UNDERLINE-P)
  (list '(beta-font-lock-fragment-face "Sienna")
	'(beta-font-lock-fragmentdecl-face "Sienna" nil t)
	'(beta-font-lock-fragmentappl-face "Red" nil nil t)
	'(beta-font-lock-block-face "Dark Green")
	'(beta-font-lock-structurestatement-face "Red")
	'(beta-font-lock-basic-face "Dark Green")
	'(beta-font-lock-pdecl-face "Blue" "Yellow")
	'(beta-font-lock-vdecl-face "Blue" "Green")
	'(beta-font-lock-fdecl-face "White" "Green" t)
	'(beta-font-lock-sdecl-face "Blue" nil t)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  A sparse ('thin') highlighting
;;;  specification, a more gorgeous
;;;  one, and a hilit19-wannabee
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defconst beta-font-lock-keywords-sparse
  (list

   ;; Properties
   (list beta-font-lock-fragment-regexp 0 font-lock-reference-face t)

   ;; Structural clues when reading a descriptor
   (list beta-font-lock-structurestatement-regexp 0 font-lock-keyword-face)

   ;; Declared names
   (list beta-font-lock-decl-regexp 1 font-lock-function-name-face))

  "Font-lock specification: simple, well-behaved, only standard faces used")

(defconst beta-font-lock-keywords-fruitcake
  (list

   ;; Properties
   (list beta-font-lock-property-regexp 0 beta-font-lock-fragment-face t)

   ;; Form decl/appl
   (list beta-font-lock-slotdecl-regexp 0 beta-font-lock-fragmentdecl-face)
   (list beta-font-lock-slotappl-regexp 0 beta-font-lock-fragmentappl-face)

   ;; Blocks
   (list beta-font-lock-scope-regexp 0 beta-font-lock-block-face)

   ;; Structural clues when reading a descriptor
   (list beta-font-lock-structurekeyword-regexp 0 font-lock-keyword-face)
   (list beta-font-lock-structurestatement-regexp 0
	 beta-font-lock-structurestatement-face)
   (list beta-font-lock-keyword-regexp 0 font-lock-keyword-face)
   (list beta-font-lock-coercion-regexp 1 font-lock-keyword-face)

   ;; Basic patterns and special values
   (list beta-font-lock-basic-regexp 0 beta-font-lock-basic-face)

   ;; Declared names
   (list beta-font-lock-patterndecl-regexp 1 beta-font-lock-pdecl-face)
   (list beta-font-lock-virtualdecl-regexp 1 beta-font-lock-vdecl-face)
   (list beta-font-lock-furtherdecl-regexp 1 beta-font-lock-fdecl-face)
   (list beta-font-lock-substancedecl-regexp 1 beta-font-lock-sdecl-face))

  "Font-lock specification: many colors, non-standard faces, bad taste")

(defconst beta-font-lock-keywords-hilit-like
  (list

   ;; Properties
   (list beta-font-lock-property-regexp 0 beta-font-lock-fragment-face t)

   ;; Form decl/appl
   (list beta-font-lock-slotdecl-regexp 0 beta-font-lock-fragmentdecl-face)
   (list beta-font-lock-slotappl-regexp 0 beta-font-lock-fragmentappl-face)

   ;; Blocks
   (list beta-font-lock-scope-regexp 0 font-lock-keyword-face)

   ;; Structural clues when reading a descriptor
   (list beta-font-lock-structurekeyword-regexp 0
	 font-lock-keyword-face)
   (list beta-font-lock-structurestatement-regexp 0
	 beta-font-lock-structurestatement-face)
   (list beta-font-lock-keyword-regexp 0
	 font-lock-keyword-face)
   (list beta-font-lock-coercion-regexp 1
	 font-lock-keyword-face)

   ;; Declared names
   (list beta-font-lock-decl-regexp 1 beta-font-lock-sdecl-face))

  "Font-lock specification: somewhat like hilit19 with beta-hilit19.el")


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  Beta mode menu related functions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun beta-font-lock-choose-sparse ()
  (interactive)
  (beta-font-lock-change-specification beta-font-lock-keywords-sparse))

(defun beta-font-lock-choose-hilit-like ()
  (interactive)
  (beta-font-lock-change-specification beta-font-lock-keywords-hilit-like))

(defun beta-font-lock-choose-fruitcake ()
  (interactive)
  (beta-font-lock-change-specification beta-font-lock-keywords-fruitcake))

(defvar beta-font-lock-map (make-sparse-keymap "Beta Font Lock Styles")
  "Local keymap for sub-menu entries to choose beta-font-lock style")
(defalias 'beta-font-lock-map (symbol-value 'beta-font-lock-map))

(defun beta-font-lock-insert-menu-entries ()
  (interactive)
  (require 'beta-menu19)

  (define-key beta-mode-map [menu-bar beta beta-font-lock-map]
    '("Font Lock Styles" . beta-font-lock-map))
  
  (define-key beta-font-lock-map [hilit] 
    '("Hilit-like" . beta-font-lock-choose-hilit-like))
  
  (define-key beta-font-lock-map [fruit-cake] 
    '("Fruit Cake" . beta-font-lock-choose-fruitcake))

  (define-key beta-font-lock-map [sparse] 
    '("Sparse but Fast" . beta-font-lock-choose-sparse)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  Choose a specification
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun beta-font-lock-syntax-begin ()
  (re-search-backward "^\\S \\|\\`"))

(defvar beta-font-lock-keywords beta-font-lock-keywords-sparse
  "The default font lock specification being used")

(defvar beta-font-lock-insert-menus-p t
  "Should 'beta-font-lock-install' also insert menu items in the BETA menu?")

;; arrange for font-lock mode to be initialized along with beta-mode
(defun beta-font-lock-install ()
  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults
        (list
         'beta-font-lock-keywords
         nil           ; (KEYWORDS-ONLY) yes to strings/comments
         t             ; (CASE-FOLD) keywords case-insensitive
         '((?_ . "w"))  ; (SYNTAX-ALIST) allow '_'in words
         'beta-font-lock-syntax-begin ; (SYNTAX-BEGIN)
         ))
  ;; install special BETA faces
  (font-lock-make-faces t)
  (setq font-lock-face-attributes
        (append font-lock-face-attributes beta-font-lock-face-defs))
  ;; insert menus
  (if beta-font-lock-insert-menus-p
      (beta-font-lock-insert-menu-entries))
  ;; ensure that font-lock is in fact used
  (turn-on-font-lock))

(defun beta-font-lock-change-specification (spec)
  (interactive "SChoose a BETA font-lock spec: ")
  (setq beta-font-lock-keywords spec)
  (font-lock-mode nil)
  (beta-mode)
  (font-lock-mode t))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  Tell 'em
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(add-hook 'beta-mode-hook 'beta-font-lock-install)

;; we expect to be loaded by 'require' in a mode-hook, so first execution 
;; must be manual (the hook isn't called before the next file is loaded):
(if (equal mode-name "BETA")
    (beta-font-lock-install))

(provide 'beta-font-lock)
