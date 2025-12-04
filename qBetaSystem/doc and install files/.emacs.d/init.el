  ;; Do not use tabs. Use space characters instead.
  (setq-default indent-tabs-mode nil)

  ;; to do copy, cut and paste the windows way
  (cua-mode t)


;;; Modify the syntax table, so that we only match parenthesis, i.e. '(' and ')'
   ;; Put the brackets [] in the word class, so as to remove their interpretation as delimiters
   (modify-syntax-entry ?[ "w")
   (modify-syntax-entry ?] "w")
   ;; Put thecurly  brackets {} in the word class, so as to remove their interpretation as delimiters
   (modify-syntax-entry ?{ "w")
   (modify-syntax-entry ?} "w")
