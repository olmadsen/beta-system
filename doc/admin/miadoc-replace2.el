(defun miadoc-replace1 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace t))
    (message "Fixing headings level 3")
    (tags-query-replace "<H[1-6]>\\s-*[0-9]+\\.[0-9]+\\.[0-9]+\\.*\\s-*\\([^<]+\\)\\s-*</H[1-6]>" "<H3>\\1</H3>" nil)))

(defun miadoc-replace2 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace t))
    (message "Fixing headings level 2")
    (tags-query-replace "<H[1-6]>\\s-*[0-9]+\\.[0-9]+\\.*\\s-*\\([^<]+\\)\\s-*</H[1-6]>" "<H2>\\1</H2>" nil)))

(defun miadoc-replace3 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace t))
    (message "Fixing headings level 1")
    (tags-query-replace "<H[1-6]>\\s-*[0-9]+\\.*\\s-*\\([^<]+\\)\\s-*</H[1-6]>" "<H1>\\1</H1>" nil)))

