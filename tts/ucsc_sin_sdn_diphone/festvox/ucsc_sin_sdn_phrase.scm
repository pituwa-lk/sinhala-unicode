;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                             ;;
;;;                  A Better Phrasing Algorithm for Sinhala                    ;;
;;;                                                                             ;;
;;;      Copyright (c) 2005-2007, Language Technology Research Laboratory       ;;
;;;             University of Colombo School of Computing, Sri Lanka.           ;;
;;;                           <ltrl@ucsc.cmb.ac.lk>                             ;;
;;;  Author:                                                                    ;;
;;;                                                                             ;;
;;;                    Asanka Wasala <awasala@webmail.cmb.ac.lk>                ;;
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

(set! sinhala_guess_pos
      '((fn 
	"සිට" "සඳහා" "හා" "නම්" "වස්" "අමතරව" "මෙන්ම" "අයත්" "සහ" "යටතේ" "දී" "සමඟ" "සමග" 
            "වන" "තිබුනේ" "තිබුණේ" "ව"  "කරමින්" "ගැන" "කොට" "නමුත්" "කිරීමට" "පෙර" "වගේම" 
	"බව" "බවට" "අතර" "බවත්" "හෝ" "එහෙත්" "නිසා" "නොකොට" "එබැවින්" "වශයෙන්" "යන්න"
	"අනුව" "යයි" "නමුදු" "වූ" "වැනි" "ගැනීමට" "ලත්" "නැත්නම්" "අතරෙන්" "විට" "නොව" "වුවහොත්"
	"ලෙස" "තුළ" "තුල" "වීම" "ඇතැයි" "වුවත්" 
      )
	(punc "." "," ":" ";" "\"" "'" "(" "?" ")" "!")
	))

(define (since_punctuation word)
 "(since_punctuation word)
Number of words since last punctuation or beginning of utterance."
 (cond
   ((null word) 0) ;; beginning or utterance
 ((string-equal "." (item.feat word "p.lisp_token_end_punc")) 1)
   (t
    (+ 1 (since_punctuation (item.prev word))))))

(define (until_punctuation word)
 "(until_punctuation word)
Number of words until next punctuation or end of utterance."
 (cond
   ((null word) 0) ;; beginning or utterance
 ((string-equal "." (token_end_punc word)) 0)
   (t
    (+ 1 (until_punctuation (item.next word))))))

(set! simple_phrase_cart_tree_2
'
((lisp_token_end_punc in ("?" "." ":" "!"))
  ((BB))
  ((lisp_token_end_punc in ("'" "\"" "," ";"))
   ((B))
   ((n.name is 0)  ;; end of utterance
    ((BB))
    ((lisp_since_punctuation > 5)
     ((lisp_until_punctuation > 5)
	  ((gpos is content)
        ((n.gpos is content)
         ((NB))
        ((NB)))   ;; not content so a function word
       ((B)))   ;; this is a function word
      ((NB)))    ;; to close to punctuation
     ((NB)))     ;; to soon after punctuation
    ((NB))))))

(set! simple_phrase_cart_tree_1
'
((lisp_token_end_punc in ("'" "\"" "?" "." "," ":" ";"))
  ((BB))
  ((n.name is 0)
   ((B))
   ((NB)))))

