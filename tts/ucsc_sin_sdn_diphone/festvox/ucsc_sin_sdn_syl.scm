;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                             ;;
;;;                    Sinhala Syllabification Algorithm   	                    ;;
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
;;; Syllabification Algorithm based on:
;;; http://dx.doi.org/10.1007/11562214_39
;;;

;; define vowels (as regex obj.)
(set! vowels "^i$\\|^ii$\\|^e$\\|^ee$\\|^ae$\\|^aee$\\|^u$\\|^uu$\\|^o$\\|^oo$\\|^a$\\|^aa$\\|^aaa$\\|^aaaa$")
;; define consonants (as regex obj.)
(set! consonants "^k$\\|^g$\\|^on$\\|^sg$\\|^cha$\\|^j$\\|^nga$\\|^t$\\|^d$\\|^sd$\\|^tha$\\|^dha$\\|^n$\\|^sdha$\\|^p$\\|^b$\\|^m$\\|^sba$\\|^y$\\|^r$\\|^l$\\|^v$\\|^sha$\\|^s$\\|^h$\\|^f$")
;; define stop consonants
(set! stop_consonants "^k$\\|^g$\\|^cha$\\|^j$\\|^t$\\|^d$\\|^tha$\\|^dha$\\|^p$\\|^b$")
;; define all consonants other than /r/ and /y/
(set! sp_consonants "^k$\\|^g$\\|^on$\\|^sg$\\|^cha$\\|^j$\\|^nga$\\|^t$\\|^d$\\|^sd$\\|^tha$\\|^dha$\\|^n$\\|^sdha$\\|^p$\\|^b$\\|^m$\\|^sba$\\|^l$\\|^v$\\|^sha$\\|^s$\\|^h$\\|^f$")


(set! syls '())             ;; syllables are appended to this variable
(set! current_syl ())       ;; hold the current syllable that is being processed


;; this function returns phonemes after first vowel in a given sequence of phonemes.
(
 define (get_phones_after_vowel phns)
 (set! current_phoneme (car phns))
 (set! current_syl(append current_syl (list current_phoneme)))
 (
  if (string-matches current_phoneme vowels)     
    (cdr phns)   
    (get_phones_after_vowel (cdr phns) )
 )
)


;; this function applies Sinhala Syllabification Rules given in our paper: http://dx.doi.org/10.1007/11562214_39
(
 define (apply_sinhala_rules phns)
  (set! current_syl ())
  (set! gpav(get_phones_after_vowel phns))
  (set! rc current_syl)

  ;;Rule #1
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list rc 0))))
      
      (apply_sinhala_rules gpav)
     )
  )
 ;;Rule #2
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) consonants)
     (string-matches (car (cdr (cdr gpav))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list  (append rc (list (car gpav))) 0))))
      
      (apply_sinhala_rules (cdr gpav))
     )
  )

 ;;Rule #3
  ( 
    and 
     (string-matches (car gpav) vowels)
     t
     (
      begin 
      (set! syls(append syls (list (list rc 0))))
      
      (apply_sinhala_rules  gpav)
     )
  )

 ;;Rule #4
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) consonants)
     (string-matches (car (cdr (cdr gpav))) "r\\|y")
     (string-matches (car (cdr (cdr (cdr gpav)))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list (append rc (list (car gpav))) 0))))
      
      (apply_sinhala_rules (cdr gpav))
     )
  )

 ;;Rule #5
  ( 
    and 
     (string-matches (car gpav) stop_consonants)
     (string-matches (car (cdr gpav)) stop_consonants)
     (string-matches (car (cdr (cdr gpav))) sp_consonants)
     (string-matches (car (cdr (cdr (cdr gpav)))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list  (append rc (list (car gpav))) 0))))
      
      (apply_sinhala_rules (cdr gpav))
     )
  )

 ;;Rule #6
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) consonants)
     (string-matches (car (cdr (cdr gpav))) consonants)
     (string-matches (car (cdr (cdr (cdr gpav)))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list  (append rc (append (list (car gpav)) (list (car (cdr gpav))) ) )   0) )))
      
      (apply_sinhala_rules (cdr (cdr gpav)))
     )
  )

 ;;Rule #7-1 [ccc][r|y]
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) consonants)
     (string-matches (car (cdr (cdr gpav))) consonants)
     (string-matches (car (cdr (cdr (cdr gpav)))) "r\\|y")
     (string-matches (car (cdr (cdr (cdr (cdr gpav))))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list(list  (append rc (append (list (car gpav)) (list (car (cdr gpav))) ) )    0))))
      
      (apply_sinhala_rules (cdr (cdr gpav)))
     )
  )

 ;;Rule #7-2 [cccc][r|y] ->[ccc]...[c][r|y]
  ( 
    and 
     (string-matches (car gpav) consonants)
     (string-matches (car (cdr gpav)) consonants)
     (string-matches (car (cdr (cdr gpav))) consonants)
     (string-matches (car (cdr (cdr (cdr gpav)))) consonants)
     (string-matches (car (cdr (cdr (cdr (cdr gpav))))) "r\\|y")
     (string-matches (car (cdr (cdr (cdr (cdr (cdr gpav)))))) vowels)
     t
     (
      begin 
      (set! syls(append syls (list (list  (append rc (append (list (car gpav)) (append (list (car (cdr gpav))) (list (car (cdr (cdr gpav)))) ) ) )   0) )))
      
      (apply_sinhala_rules (cdr (cdr (cdr gpav))))
     )
  )
)


;;  this function accepts a sequance of phonemes and returns the syllabified form.
(
 define(syllabify phns)
 
 (set! syls '()) ;; clear current syllabified token
 (set! te(append (append phns '(k)) '(a))) ;; to handle rule #1 needs 2 dummy phonemes at the end of phns. this is not the best way to handle this! A very good Schemer could re-write the apply_sinhala_rules function!
 (apply_sinhala_rules te) ;; apply syllabification rules
  ( 
    if (eq syls nil) (lex.syllabify.phstress phns) syls ;; if the word cannot be syllabified use the sonority based (Rule #8) default syllabification algorithm or else apply Sinhala syllabification rules
  )
)

