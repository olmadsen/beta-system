;; Menu for beta-mode in emacs 19

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

(defun beta-hilit-off ()
  "Turn of highlight"
  (interactive)
  (require 'beta-hilit19)
  (hilit-unhighlight-region (point-min) (point-max))
  (setq hilit-auto-rehighlight nil)
  (setq hilit-auto-highlight nil))

(defun beta-hilit-on ()
  "Turn on highlight"
  (interactive)
  (require 'beta-hilit19)
  (hilit-highlight-region (point-min) (point-max))
  (setq hilit-auto-rehighlight t)
  (setq hilit-auto-highlight t))

;;; Insert new beta code
(defun beta-new-program ()
  (interactive)
  (goto-char (point-min))
  (insert "ORIGIN '~beta/basiclib/v1.4/betaenv';\n")
  (insert "--PROGRAM: descriptor--\n")
  (insert "(# \n")
  (insert "do \n")
  (insert "#)\n")
  (previous-line 2)
  (end-of-line)
  )

(defun beta-new-library ()
  (interactive)
  (goto-char (point-min))
  (insert "ORIGIN '~beta/basiclib/v1.4/betaenv';\n")
  (insert "--LIB: attributes--\n")
  )

(cond (window-system
       (require 'beta-mode)
       
       (define-key beta-mode-map [menu-bar] (make-sparse-keymap))
       
       (define-key beta-mode-map [menu-bar beta]
	 (cons "BETA" (make-sparse-keymap "BETA")))

       (define-key beta-mode-map [menu-bar beta beta-hilit-on]
	 '("Enable Hilit" . beta-hilit-on))
       (define-key beta-mode-map [menu-bar beta beta-hilit-off]
	 '("Disable Hilit" . beta-hilit-off))       

       (define-key beta-mode-map [menu-bar beta beta-beginning-of-construct]
	 '("Beginning of Construct" . beta-beginning-of-construct))

       (define-key beta-mode-map [menu-bar beta beta-close-pattern]
	 '("Close Construct" . beta-close-pattern))
       (define-key beta-mode-map [menu-bar beta beta-open-pattern]
	 '("Open Pattern" . beta-open-pattern))

       (define-key beta-mode-map [menu-bar beta beta-tab]
	 '("Indent Line" . beta-tab))
       (define-key beta-mode-map [menu-bar beta indent-buffer]
	 '("Indent Buffer" . indent-buffer))

       (define-key beta-mode-map [menu-bar beta beta-remove-comment]
	 '("Remove Comment" . beta-remove-comment))
       (define-key beta-mode-map [menu-bar beta beta-convert-region-to-comment]
	 '("Comment Out Region" . beta-convert-region-to-comment))
       (define-key beta-mode-map [menu-bar beta beta-comment-justify]
	 '("Justify Comment" . beta-comment-justify))
       (define-key beta-mode-map [menu-bar beta beta-prettyprint]
	 '("Prettyprint current buffer" . beta-prettyprint))

       (define-key beta-mode-map [menu-bar beta beta-execute]
	 '("Execute current buffer" . beta-execute))
       (define-key beta-mode-map [menu-bar beta beta-check]
	 '("Check current buffer" . beta-check))
       (define-key beta-mode-map [menu-bar beta beta-compile]
	 '("Compile current buffer" . beta-compile))

       (define-key beta-mode-map [menu-bar beta beta-new-library]
	 '("Library skeleton" . beta-new-library))
       (define-key beta-mode-map [menu-bar beta beta-new-program]
	 '("Program skeleton" . beta-new-program))


       ))

(provide 'beta-menu19)
      
      
      