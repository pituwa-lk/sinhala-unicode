;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                             ;;
;;;                           Sinhala Text Normalizer                           ;;
;;;                                                                             ;;
;;;      Copyright (c) 2005-2007, Language Technology Research Laboratory       ;;
;;;             University of Colombo School of Computing, Sri Lanka.           ;;
;;;                           <ltrl@ucsc.cmb.ac.lk>                             ;;
;;;                                                                             ;;
;;;  This program is a part of Festival-si.                                     ;;
;;;                                                                             ;;
;;;  festival-si is free software; you can redistribute it and/or modify        ;;
;;;  it under the terms of the GNU General Public License as published by       ;;
;;;  the Free Software Foundation; either version 2 of the License, or          ;;
;;;  (at your option) any later version.                                        ;;
;;;                                                                             ;;
;;;  This program is distributed in the hope that it will be useful,            ;;
;;;  but WITHOUT ANY WARRANTY; without even the implied warranty of             ;;
;;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              ;;
;;;  GNU General Public License for more details.                               ;;
;;;                                                                             ;;
;;;  You should have received a copy of the GNU General Public License          ;;
;;;  along with this program; if not, write to the Free Software                ;;
;;;  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA  ;;
;;;                                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Token rules to map (tokens to words) - Modified by Asanka Wasala 
;;; This program provides minimal functionality in tokenization of Sinhala text.
;;; This is to be improved.

;;; Part of speech done by crude lookup using gpos 
(set! ucsc_sin_guess_pos 
'((fn
    wa ga ka wo o no e he de da desu dewa )
  )
)

(define (ucsc_sin_token_to_words token name)
  "(ucsc_sin_token_to_words TOKEN NAME)
Returns a list of words for the NAME from TOKEN.  This primarily
allows the treatment of numbers, money etc."
  (cond
   ((and (string-matches name "[1-9]")
	 (string-equal (item.feat token "n.name") "yi"))
    ;; hitotsu, futatsu, mitsu, yotsu ...
    (cmu_js_tsu_number name))
   ;; A more complex number system is required
   ((string-matches name "[1-9][0-9]+")
    ;; Normal numbers (uncommaed)
    (ucsc_sin_number token name))

   ;; Add many other rules, for numbers, abbrev, alphanumerics, homographs
   (t
    (list name))))

(define (ucsc_sin_tsu_number token name)
  "(ucsc_sin_tsu_number token name)
Return generic counter number."
  (let ((tsu (assoc_string name 
	      '(("1" eka)
		("2" dhzeka)
		("3" thuna)
		("4" hathxra)
		("5" paha)
		("6" haya)
		("7" hathza)
		("8" ata)
		("9" navaya)))))
    (if tsu
	(cdr tsu)
	(list "nani"))  ;; this is probably an error
    ))

(define (ucsc_sin_number token name)
  "(ucsc_sin_number token name)
Return list of words that pronounce this number in ja."
  (let ((digits (symbolexplode name)))
    (if (string-equal "0" (car digits))
	(ucsc_sin_sayas_digits digits)
	(ucsc_sin_sayas_number digits))))

(set! ucsc_sin_digit_to_number
      '(("0" "binduvx")
	("1" "ekx")
	("2" "dekx")
	("3" "thzunx")
	("4" "hathxrx")  ;; nobody I know says shi (^0^)
	("5" "paha")
	("6" "hayx")
	("7" "hathx")
	("8" "atx")
	("9" "navayx")))

(define (ucsc_sin_sayas_number digits)
  "(ucsc_sin_sayas_number digits)
Returns list of words saying this as a simple number."
  (cond
   ((string-equal "0" (car digits))
    (ucsc_sin_sayas_number (cdr digits)))
   ((equal? 1 (length digits))
    ;; will be nil if digit is "0"
    (cdr (assoc_string (car digits) ucsc_sin_digit_to_number)))
   ((equal? 2 (length digits))
    (append
     (if (string-equal "1" (car digits))
	 nil
	 (cdr (assoc_string (car digits) ucsc_sin_digit_to_number)))
     '("ju")
     (ucsc_sin_sayas_number (cdr digits))))
   ((equal? 3 (length digits))
    (append
     (if (string-equal "1" (car digits))
	 nil
	 (cdr (assoc_string (car digits) ucsc_sin_digit_to_number)))
     '("hyaku")
     (ucsc_sin_sayas_number (cdr digits))))
   ((equal? 4 (length digits))
    (append
     (if (string-equal "1" (car digits))
	 nil
	 (cdr (assoc_string (car digits) ucsc_sin_digit_to_number)))
     '("seN")
     (ucsc_sin_sayas_number (cdr digits))))
   ((> (length digits) 12)
    ;; read it as digits
    (ucsc_sin_sayas_digits digits))
   ((> (length digits) 8)
    (format t "oku\n")
    (append
     (ucsc_sin_sayas_number
      (reverse (nth_cdr 8 (reverse digits))))
     '("oku")
     (ucsc_sin_sayas_number 
      (nth_cdr (- (length digits) 8) digits))))
   ((> (length digits) 4)
    (append
     (ucsc_sin_sayas_number
      (reverse (nth_cdr 4 (reverse digits))))
     '("maN")
     (ucsc_sin_sayas_number
      (nth_cdr (- (length digits) 4) digits))))
   (t
    ;; can't get here
    (ucsc_sin_sayas_digits digits))))

(provide 'ucsc_sin_token)
