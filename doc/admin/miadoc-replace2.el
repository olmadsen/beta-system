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
    (tags-query-replace "<h[1-6]>\\s-*[0-9]+\\.*\\s-*\\([^<]+\\)\\s-*</h[1-6]>" "<H1>\\1</H1>" nil)))

(defun miadoc-replace4 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Fixing PRE CLASS=BETA")
    (tags-query-replace "<pre\\s-*class\\s-*=\\s-*beta>\\([][
\\s- 	a-zA-Z0-9@#$%^&*()-+=|';:,.<>~/]*\\)</pre>" "<BETA>\\1</BETA>" nil)))

(defun miadoc-replace5 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Fixing PRE CLASS=BETA with headings")
    (tags-query-replace "<a name=.*><h4\\s-*class\\s-*=\\s-*betacaption\\s-*>\\s-*\\(.*\\)\\s-*</h4></a>[
\\s-	]*<pre\\s-*class=beta>" "<BETA LIST=\"\\1\">" nil)))

(defun miadoc-replace5a ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Fixing PRE CLASS=BETA with headings (no anchors)")
    (tags-query-replace "<h4\\s-*class\\s-*=\\s-*betacaption\\s-*>\\s-*\\(.*\\)\\s-*</h4>[
\\s-	]*<pre\\s-*class=beta>" "<BETA LIST=\"\\1\">" nil)))


(defun miadoc-replace6 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Fixing STRONG -> FIG")
    (tags-query-replace "<A NAME=figure_[0-9]+><STRONG CLASS=figure>Figure [0-9]+\\(.*\\)</STRONG></A>" "<FIG LIST=\"\\1\"></FIG>" nil)))
