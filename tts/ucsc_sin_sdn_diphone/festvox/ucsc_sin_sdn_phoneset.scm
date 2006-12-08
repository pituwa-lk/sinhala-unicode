;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                             ;;
;;;                     PhoneSet for UCSC Sinhala Sandun Voice                  ;;
;;;      Copyright (c) 2005-2007, Language Technology Research Laboratory       ;;
;;;             University of Colombo School of Computing, Sri Lanka.           ;;
;;;                           <ltrl@ucsc.cmb.ac.lk>                             ;;
;;;                                                                             ;;
;;;  Authors:                                                                   ;;
;;;                           Asanka Wasala <awasala@webmail.cmb.ac.lk>         ;;
;;;  	                        Kumudu Gamage <kgamage@webmail.cmb.ac.lk>         ;;
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

(defPhoneSet
  ucsc_sin_sdn
(;; vowel or consonant
   (vc + -)  
   ;; vowel length: short long dipthong schwa
   (vlng s l d a 0)
   ;; vowel height: high mid low
   (vheight 1 2 3 0)
   ;; vowel frontness: front mid back
   (vfront 1 2 3 0)
   ;; lip rounding
   (vrnd + - 0)
   ;; consonant type: stop fricative affricative nasal lateral prenasalized semivowel trill
   (ctype s f a n l p w t 0)
   ;; place of articulation: labial alveolar palatal labio-dental
   ;;                         dental velar retroflex glottal
   (cplace l a p b d v r g 0)
   ;; consonant voicing
   (cvox + - 0)
   )
  (

   (i    + s 1 1 - 0 0 0)
   (ii   + l 1 1 - 0 0 0)
   (e    + l 2 1 - 0 0 0)
   (ee   + l 2 1 - 0 0 0)
   (ae   + s 3 1 - 0 0 0)
   (aee  + l 3 1 - 0 0 0)
   (u    + s 1 3 + 0 0 0)
   (uu   + l 1 3 + 0 0 0)
   (o    + s 2 3 + 0 0 0)
   (oo   + l 2 3 + 0 0 0)
   (a    + s 3 2 - 0 0 0)
   (aa   + l 3 2 - 0 0 0)
   (aaa  + a 2 2 - 0 0 0)
   (aaaa + l 2 2 - 0 0 0)
   ;; consonants
   (k    - 0 0 0 0 s v -)
   (g    - 0 0 0 0 s v +)
   (on   - 0 0 0 0 n v +)
   (sg   - 0 0 0 0 p v +)
   (cha  - 0 0 0 0 a p -)
   (j    - 0 0 0 0 a p +)
   (nga  - 0 0 0 0 n p +)
   (t    - 0 0 0 0 s r -)
   (d    - 0 0 0 0 s r +)
   (sd   - 0 0 0 0 p d +)
   (tha  - 0 0 0 0 s d -)
   (dha  - 0 0 0 0 s d +)
   (n    - 0 0 0 0 n a +)
   (sdha - 0 0 0 0 p r +)
   (p    - 0 0 0 0 s l -)
   (b    - 0 0 0 0 s l +)
   (m    - 0 0 0 0 n l +)
   (sba  - 0 0 0 0 p l +)
   (y    - 0 0 0 0 w p +)
   (r    - 0 0 0 0 t a -)
   (l    - 0 0 0 0 l a +)
   (v    - 0 0 0 0 w l +)
   (sha  - 0 0 0 0 f p -)
   (s    - 0 0 0 0 f d -)
   (h    - 0 0 0 0 f g -)
   (f    - 0 0 0 0 f l +)
  
   ;; slience ... 
   (SIL  - 0 0 0 - 0 0 0)
  )
)

(PhoneSet.silences '(SIL))
(provide 'ucsc_sin_sdn)
