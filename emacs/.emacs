;; start the emacsserver that listens to emacsclient
;; check the setup in the .bash_profile 
(server-start)

;; Recent files menu item
(require 'recentf)
    (recentf-mode 1)
    (setq recentf-max-menu-items 25)
    (global-set-key "\C-x\ r" 'recentf-open-files)

;; remove the splash and start messages
(setq inhibit-splash-screen t)
(setq inhibit-startup-message t)

;; put fortune in scratch buffer
(setq initial-scratch-message 
      (format 
       ";; %s\n\n" 
       (replace-regexp-in-string  
        "\n" "\n;; " ; comment each line
        (replace-regexp-in-string 
         "\n$" ""    ; remove trailing linebreak
         (shell-command-to-string "/opt/local/bin/fortune")))))

;; setup brackets and curly braces on mac
(setq mac-option-modifier nil
      mac-command-modifier 'meta
      x-select-enable-clipboard t)

;; add marmelade package directory
(when (>= emacs-major-version 24)
  (require 'package)
  (add-to-list
   'package-archives
   '("melpa" . "http://melpa.org/packages/")
   t)
  (package-initialize))

;; setup file associations
(setq auto-mode-alist (cons '("README" . text-mode) auto-mode-alist))
(setq auto-mode-alist (cons '("\\.asciidoc$" . adoc-mode) auto-mode-alist))

