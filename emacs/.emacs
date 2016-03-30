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

;; add marmalade package directory
(when (>= emacs-major-version 24)
  (require 'package)
  (add-to-list
   'package-archives
   '("melpa" . "http://melpa.org/packages/")
   t)
  (package-initialize))
