;; Hilite support in emacs 19 for beta-mode

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

;; The BETA hilite faces is based on code from
;;     law@tauon.ph.unimelb.edu.au (Lachlan Witham)

(cond (window-system
       (setq hilit-mode-enable-list  '(not text-mode)
	     hilit-background-mode   'light
	     hilit-inhibit-hooks     nil
	     hilit-inhibit-rebinding nil)
 
       (require 'hilit19)

       ;; Enable automatic highlighting (colourising) of files when opened
       (setq hilit-auto-highlight t)

       (hilit-translate beta-fragment-property	'Sienna)
       (hilit-translate beta-fragment-form	'Sienna)
       (hilit-translate beta-fragment-slot	'Red-italic)
       (hilit-translate beta-comment            'gray20-italic)
       (hilit-translate beta-tos		'Red)
       (hilit-translate beta-inner		'Red)
       (hilit-translate beta-string		'Blue-italic)
       (hilit-translate beta-keyword		'Blue)
       (hilit-translate beta-descriptor		'Blue-unbold)
       (hilit-translate beta-if	                'Blue)
       (hilit-translate beta-for 	        'Blue)
       (hilit-translate beta-code	        'Blue)
       (hilit-translate beta-symbol		'Blue)
       (hilit-translate beta-type		'DarkGreen)
       (hilit-translate beta-object-reference	'Blue-bold)
       (hilit-translate beta-pattern		'Blue-bold)
       (hilit-translate beta-virtual		'Blue-bold)
       (hilit-translate beta-label	        'Blue-bold)

       (hilit-set-mode-patterns 
	'beta-mode
	'(
	  ;; comments
	  ("(\\*" "\\*)" beta-comment)
	  ;; strings
	  ("'[^\\']*\\(\\\\\\(.\\|\n\\)[^\\']*\\)*'" nil beta-string)
	  ;; descriptors
	  ("\(#\\|#\)" nil beta-descriptor)
	  ;; fragment properties
	  ("\\<\\(ORIGIN\\|BODY\\|MDBODY\\|INCLUDE\\|LIBFILE\\|LIBOPT\\|MAKE\\|OBJFILE\\)\\>" ";\\|--+" beta-fragment-property)
	  ;; SLOTs
	  ("--+\\s-*\\w+\\s-*:\\s-*\\w+\\s-*--+" nil beta-fragment-form)
	  ;; fragment forms
	  ("<<\\s-*SLOT\\s-*\\w+\\s-*:\\s-*\\w+\\s-*>>" nil beta-fragment-slot)
	  ;; special symbols
	  (":<\\|::<\\|::\\|@\\|\\^\\|&\\|%\\|##\\|\\[\\]" nil beta-symbol)
	  ("tos'[^\\']*\\(\\\\\\(.\\|\n\\)[^\\']*\\)*'" nil beta-tos)
	  ;; single keyword
	  ("\\<\\(do\\|enter\\|exit\\|false\\|true\\|leave\\|restart\\|suspend\\|this\\|none\\|not\\|not\\|div\\|mod\\|or\\|xor\\|and\\)\\>" nil beta-keyword)
	  ;; constructions 
	  ("\(if\\>" nil beta-if) ("//" nil beta-if)
	  ("\\<then\\>" nil beta-if) ("\\<else\\>" nil beta-if)
	  ("\\<if\)" nil beta-if)
	  ("\(for\\>" nil beta-for) ("\\<repeat\\>" nil beta-for)
	  ("\\<for\)" nil beta-for)
	  ("\(code\\>" nil beta-code) ("\\<code\)" nil beta-code)
	  ;; INNER
	  ("\\<inner\\>" nil beta-inner)
	  ;; special patterns
	  ;; ("integer\\|char\\|boolean\\|real\\|shortint\\|data" nil beta-type)
	  ;; object references
	  ("\\(\\w+\\s-*,\\s-*\\)*\\w+\\s-*:\\s-*\\(\\^\\|@\\|\\[\\)" nil beta-object-reference)
	  ;; virtual patterns
	  ("\\(\\w+\\s-*,\\s-*\\)*\\w+\\s-*\\(:<\\|::<\\|::\\)" nil beta-virtual)
	  ;; patterns
	  ("\\(\\w+\\s-*,\\s-*\\)*\\w+\\s-*:" nil beta-pattern)
	  ;; labels
	  ("\\(\\<do\\>\\|;\\)\\s-*\\w+\\s-*:" nil beta-label)
	  ) nil 'case-insensitive)

       ;; Use these colours for BETA mode hilighting with hilit19
       ;; Change colour names to suit your personal taste :-)

       ))

(provide 'beta-hilit19)
