(defvar position 50 "The knob starts at 50.")
(defvar points 0 "The number of times the dial has landed on 0.")

(defun step (instruction)
  (let* ((direction (substring instruction 0 1))
         (steps
          (string-to-number
           (cadr (split-string instruction "[LR]")))))
    (setq position
          (if (string= direction "L")
              (- position steps)
            (+ position steps)))
    (setq position (mod position 100))
    (when (= position 0)
      (setq points (1+ points)))))

(defun part1 ()
  (setq position 50
        points 0)
  (let* ((input (with-temp-buffer
                  (insert-file-contents "./day1.txt")
                  (string-trim (buffer-string))))
         (instructions (split-string input "\n")))
    (mapc #'step instructions))
  points)
