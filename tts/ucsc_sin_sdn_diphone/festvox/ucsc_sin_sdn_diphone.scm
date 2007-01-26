;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;-*-mode:scheme-*-;;;;;;
;;;                                                                             ;;
;;;                      A Diphone Voice for Sinhala Language                   ;;
;;;                        UCSC Sinhala Sandun Diphone Voice                    ;;
;;;                              version 0.9 (beta)                             ;;
;;;                                                                             ;;
;;;      Copyright (c) 2005-2007, Language Technology Research Laboratory       ;;
;;;             University of Colombo School of Computing, Sri Lanka.           ;;
;;;                           <ltrl@ucsc.cmb.ac.lk>                             ;;
;;;  Authors:                                                                   ;;
;;;                                                                             ;;
;;;                    Asanka Wasala <awasala@webmail.cmb.ac.lk>                ;;
;;;  	                 Viraj Welgama <vwelgama@webmail.cmb.ac.lk>               ;;
;;;  	                 Kumudu Gamage <kgamage@webmail.cmb.ac.lk>                ;;
;;;  	                 Sandun Sulakshana <SandunSu@masholdings.com>             ;;
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
;;; ucsc_sin_sdn_diphone.scm is modified by Asanka Wasala.

;;; Try to find out where we are
(if (assoc 'ucsc_sin_sdn_diphone voice-locations)
    (defvar ucsc_sin_sdn_dir 
      (cdr (assoc 'ucsc_sin_sdn_diphone voice-locations)))
    ;;; Not installed in Festival yet so assume running in place
    (defvar ucsc_sin_sdn_dir (pwd)))

(if (not (probe_file (path-append ucsc_sin_sdn_dir "festvox/")))
    (begin
     (format stderr "ucsc_sin_sdn: Can't find voice scm files they are not in\n")
     (format stderr "   %s\n" (path-append ucsc_sin_sdn_dir "festvox/"))
     (format stderr "   Either the voice isn't linked into Festival\n")
     (format stderr "   or you are starting festival in the wrong directory\n")
     (error)))

;;;  Add the directory contains general voice stuff to load-path
(set! load-path (cons (path-append ucsc_sin_sdn_dir "festvox/") load-path))

;;; Voice specific parameter are defined in each of the following
;;; files
(require 'ucsc_sin_sdn_phoneset)
(require 'ucsc_sin_lexi)
(require 'ucsc_sin_sdn_phrase)      ;;; <Asanka>
(require 'phrase)                   ;;; <Asanka>
(require 'tobi)
(require 'f2bf0lr)
(require 'ucsc_sin_token)

;;; Speaker specific prosody parameters
;;; For the moment, use English speaker Kal's parameters for modeling Intonation.

(require 'cmu_us_kal_int)
(require 'cmu_us_kal_dur)

;;;  Ensure we have a festival with the right diphone support compiled in
(require_module 'UniSyn)

(set! ucsc_sin_sdn_lpc_sep 
      (list
       '(name "ucsc_sin_sdn_lpc_sep")
       (list 'index_file (path-append ucsc_sin_sdn_dir "dic/sdndiph.est"))
       '(grouped "false")
       (list 'coef_dir (path-append ucsc_sin_sdn_dir "lpc"))
       (list 'sig_dir  (path-append ucsc_sin_sdn_dir "lpc"))
       '(coef_ext ".lpc")
       '(sig_ext ".res")
       (list 'default_diphone 
	     (string-append
	      (car (cadr (car (PhoneSet.description '(silences)))))
	      "-"
	      (car (cadr (car (PhoneSet.description '(silences)))))))))

(set! ucsc_sin_sdn_lpc_group 
      (list
       '(name "sdn_lpc_group")
       (list 'index_file 
	     (path-append ucsc_sin_sdn_dir "group/sdnlpc.group"))
       '(grouped "true")
       (list 'default_diphone 
	     (string-append
	      (car (cadr (car (PhoneSet.description '(silences)))))
	      "-"
	      (car (cadr (car (PhoneSet.description '(silences)))))))))

;; Go ahead and set up the diphone db
;; (set! ucsc_sin_sdn_db_name (us_diphone_init ucsc_sin_sdn_lpc_sep))
;; Once you've built the group file you can comment out the above and
;; uncomment the following.
(set! ucsc_sin_sdn_db_name (us_diphone_init ucsc_sin_sdn_lpc_group))

(define (ucsc_sin_sdn_diphone_fix utt)
"(ucsc_sin_sdn_diphone_fix UTT)
Map phones to phonological variants if the diphone database supports
them."
  (mapcar
   (lambda (s)
     (let ((name (item.name s)))
       ;;(ucsc_sin_sdn_diphone_fix_phone_name utt s)
       ))
   (utt.relation.items utt 'Segment))
  utt)

(define (ucsc_sin_sdn_diphone_fix_phone_name utt seg)
"(ucsc_sin_sdn_fix_phone_name UTT SEG)
Add the feature diphone_phone_name to given segment with the appropriate
name for constructing a diphone.  Basically adds _ if either side is part
of the same consonant cluster, adds $ either side if in different
syllable for preceding/succeeding vowel syllable."
  (let ((name (item.name seg)))
    (cond
     ((string-equal name "pau") t)
     ((string-equal "-" (item.feat seg 'ph_vc))
      (if (and (member_string name '(r w y l))
	       (member_string (item.feat seg "p.name") '(p t k b d g))
	       (item.relation.prev seg "SylStructure"))
	  (item.set_feat seg "us_diphone_right" (format nil "_%s" name)))
      (if (and (member_string name '(w y l m n p t k))
	       (string-equal (item.feat seg "p.name") 's)
	       (item.relation.prev seg "SylStructure"))
	  (item.set_feat seg "us_diphone_right" (format nil "_%s" name)))
      (if (and (string-equal name 's)
	       (member_string (item.feat seg "n.name") '(w y l m n p t k))
	       (item.relation.next seg "SylStructure"))
	  (item.set_feat seg "us_diphone_left" (format nil "%s_" name)))
      (if (and (string-equal name 'hh)
	       (string-equal (item.feat seg "n.name") 'y))
	  (item.set_feat seg "us_diphone_left" (format nil "%s_" name)))
      (if (and (string-equal name 'y)
	       (string-equal (item.feat seg "p.name") 'hh))
	  (item.set_feat seg "us_diphone_right" (format nil "_%s" name)))
      (if (and (member_string name '(p t k b d g))
	       (member_string (item.feat seg "n.name") '(r w y l))
	       (item.relation.next seg "SylStructure"))
	  (item.set_feat seg "us_diphone_left" (format nil "%s_" name)))
      )
     ((string-equal "ah" (item.name seg))
      (item.set_feat seg "us_diphone" "aa"))

   )))

(define (ucsc_sin_sdn_voice_reset)
  "(ucsc_sin_sdnl_voice_reset)
Reset global variables back to previous voice."
  ;; whatever
)

;;;  Full voice definition 
(define (voice_ucsc_sin_sdn_diphone)
"(voice_ucsc_sin_sdn_diphone)
Set speaker to sdn in Sinhala from ucsc."
  ;; Select appropriate phone set
   (voice_reset)
  (Parameter.set 'Language 'english) ;; if defined/patched you can use 'sinhala for the language <Asanka>
  ;; Phone set
  (Parameter.set 'PhoneSet 'ucsc_sin_sdn)
  (PhoneSet.select 'ucsc_sin_sdn)

  ;; token expansion
  (set! token_to_words ucsc_sin_token_to_words) ;;english_token_to_words)

  ;; For part of speech tagging
 (set! guess_pos sinhala_guess_pos)   ;; need this for accents ;; <Asanka>

 (lex.select "ucsc_sin_l")
 (set! postlex_rules_hooks nil)
 (set! phrase_cart_tree simple_phrase_cart_tree_2)
 (Parameter.set 'Phrase_Method 'cart_tree)

 (set! int_tone_cart_tree f2b_int_tone_cart_tree)
 (set! int_accent_cart_tree f2b_int_accent_cart_tree)
  
 (set! f0_lr_start f2b_f0_lr_start)
 (set! f0_lr_mid f2b_f0_lr_mid)
 (set! f0_lr_end f2b_f0_lr_end)
 (Parameter.set 'Int_Method Intonation_Tree)
 (set! int_lr_params cmu_us_kal_int_lr_params)
 (Parameter.set 'Int_Target_Method Int_Targets_LR)

 (set! duration_cart_tree cmu_us_dur_tree)
 (set! duration_ph_info cmu_us_kal_phone_durs)
 
 (Parameter.set 'Duration_Method 'Tree_ZScores)
 (Parameter.set 'Duration_Stretch 1.1)


  ;; Waveform synthesizer: UniSyn diphones
  (set! UniSyn_module_hooks (list ucsc_sin_sdn_diphone_fix))
  (set! us_abs_offset 0.0)
  (set! window_factor 1.0)
  (set! us_rel_offset 0.0)
  (set! us_gain 0.9)

  (Parameter.set 'Synth_Method 'UniSyn)
  (Parameter.set 'us_sigpr 'lpc)
  (us_db_select ucsc_sin_sdn_db_name)

  ;; This is where you can modify power (and sampling rate) if desired
  (set! after_synth_hooks nil)
;  (set! after_synth_hooks
;      (list
;        (lambda (utt)
;          (utt.wave.rescale utt 2.1))))

  ;; set callback to restore some original values changed by this voice
  (set! current_voice_reset ucsc_sin_sdn_voice_reset)

  (set! current-voice 'ucsc_sin_sdn_diphone)
)

(proclaim_voice
 'ucsc_sin_sdn_diphone
 '((language sinhala)
   (gender male)
   (dialect sinhala)
   (description
    "UCSC Sinhala Sandun Diphone Voice"
    )
    (builtwith festvox-1.3)
    (coding UTF-8)
    ))


(provide 'ucsc_sin_sdn_diphone)
