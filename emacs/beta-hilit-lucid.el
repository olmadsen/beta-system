;; If you use Lucid Emacs 19.9 (or better) you might want to try to put
;; this code into your .emacs file.  It provides nice colors and fonts
;; for BETA programs.
;; Provided by Gisle.Aas@nr.no
;;
;; Should probably be updated to be consistent with beta-hilit19.el

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

(defun beta-font-lock-hook ()
  (modify-syntax-entry (string-to-char "_") "w")
  (set (make-local-variable 'font-lock-keywords-case-fold-search) t)
  (turn-on-font-lock)
)
(setq beta-font-lock-keywords
      (list
       '("'[^']+'" . font-lock-string-face)
       "\\b\\(do\\|enter\\|exit\\|if\\|then\\|else\\|inner\\|for\\|repeat\\|leav
e\\|restart\\|suspend\\|none\\|true\\|false\\|not\\|and\\|or\\|div\\|mod\\|this\
\)\\b"
       "^\\(ORIGIN\\|BODY\\|MDBODY\\)\\b"
       '("^[ \t]*\\((#\\)?[ \t]*\\(\\w+\\)[ \t]*:[ \t]*@"
         2 font-lock-type-face)
       '("^[ \t]*\\((#\\)?[ \t]*\\(\\w+\\)[ \t]*:"
         2 font-lock-function-name-face)
       '("<<SLOT.*>>" . font-lock-doc-string-face)
       '("^--.*--" . font-lock-doc-string-face)
       '("^--+[ \t]*include" . font-lock-doc-string-face)
       '("^--+\\]\\]" . font-lock-doc-string-face)
       '("^\\[\\[" . font-lock-doc-string-face)
       )
)
(add-hook 'beta-mode-hook 'beta-font-lock-hook)
