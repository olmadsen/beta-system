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
\\s- 	\\w@#$%^&*()-+=|';:,.<>~/]*\\)</pre>" "<BETA>\\1</BETA>" nil)))

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


(defun miadoc-replace7 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Removing old HEADING anchors")
    (tags-query-replace "<A\\s-*NAME=HEADING[-0-9]+>\\s-*</A>" "" nil)))

(defun miadoc-replace8 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace nil)(case-fold-search t))
    (message "Changing WORD MARKER to <INX>WORD</INX>")
    (tags-query-replace "\\(\\w+\\)\\s-*<a\\s-+name=marker[-0-9]+>\\s-*</a>" "<INX>\\1</INX>" nil)))

(defun miadoc-replace8a ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace t)(case-fold-search t))
    (message "Changing WORD \"MARKER\" to <INX>WORD</INX>")
    (tags-query-replace "\\([-a-zA-Z0-9]+\\)\\s-*<a\\s-+name=\"marker[-0-9]+\">\\s-*</a>" "<INX>\\1</INX>" nil)))

(defun miadoc-replace9 ()
  (interactive)
  (set-variable 'tags-file-name nil)

  (let ((case-replace t)(case-fold-search t))
    (message "Changing <CODE>...</CODE>MARKER to <INX><CODE>...</CODE></INX>")
    (tags-query-replace "\\(<code>.*</code>\\)\\s-*<a\\s-+name=marker[-0-9]+>\\s-*</a>" "<INX>\\1</INX>" nil)))


