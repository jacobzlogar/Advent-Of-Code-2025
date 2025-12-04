(defvar position 50 "The knob starts at 50.")
(defvar points 0 "The number of times the dial has landed on 0.")

(defun step (instruction &optional part2)
  (let* ((direction (substring instruction 0 1))
         (steps
          (string-to-number
           (cadr (split-string instruction "[LR]"))))
         (delta (if (string= direction "L") -1 1)))
    (if (not part2)
        (progn
          (setq position (mod (+ position (* delta steps)) 100))
          (when (= position 0)
            (setq points (1+ points))))
      (dotimes (_ steps)
        (setq position (mod (+ position delta) 100))
        (when (= position 0)
          (setq points (1+ points)))))))

(defun day1 ()
  (let* ((input (with-temp-buffer
                  (insert-file-contents "./day1.txt")
                  (string-trim (buffer-string))))
         (instructions (split-string input "\n"))
         (p1 (part1 instructions))
         (p2 (part2 instructions)))
    p2))

(defun part1 (instructions)
  (setq position 50
        points 0)
  (mapc #'step instructions)
  points)

(defun part2 (instructions)
  (setq position 50
        points 0)
  (mapc (lambda (x) (step x t)) instructions)
  points)
