/*
* Written by Chamath Keppitiyagama <chamath@ucsc.cmb.ac.lk> based on the 
* indica.lex included in the sinhala LaTeX package available at 
* http://www.ctan.org/tex-archive/language/sinhala/
* 2006-May-01
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

%{
#define BOOLEAN char
#define UNSIGNED_BYTE unsigned char
#define SIGNED_BYTE signed char
#define TRUE 1
#define FALSE 0



#define SINHALA_SIGN_ANUSVARAYA   2
#define SINHALA_SIGN_VISARGAYA   3
#define SINHALA_LETTER_AYANNA   5
#define SINHALA_LETTER_AAYANNA   6
#define SINHALA_LETTER_AEYANNA   7
#define SINHALA_LETTER_AEEYANNA   8
#define SINHALA_LETTER_IYANNA   9
#define SINHALA_LETTER_IIYANNA   10
#define SINHALA_LETTER_UYANNA   11
#define SINHALA_LETTER_UUYANNA   12
#define SINHALA_LETTER_IRUYANNA   13
#define SINHALA_LETTER_IRUUYANNA   14
#define SINHALA_LETTER_ILUYANNA   15
#define SINHALA_LETTER_ILUUYANNA   16
#define SINHALA_LETTER_EYANNA   17
#define SINHALA_LETTER_EEYANNA   18
#define SINHALA_LETTER_AIYANNA   19
#define SINHALA_LETTER_OYANNA   20
#define SINHALA_LETTER_OOYANNA   21
#define SINHALA_LETTER_AUYANNA   22
#define SINHALA_LETTER_ALPAPRAANA_KAYANNA   26
#define SINHALA_LETTER_MAHAAPRAANA_KAYANNA   27
#define SINHALA_LETTER_ALPAPRAANA_GAYANNA   28
#define SINHALA_LETTER_MAHAAPRAANA_GAYANNA   29
#define SINHALA_LETTER_KANTAJA_NAASIKYAYA   30
#define SINHALA_LETTER_SANYAKA_GAYANNA   31
#define SINHALA_LETTER_ALPAPRAANA_CAYANNA   32
#define SINHALA_LETTER_MAHAAPRAANA_CAYANNA   33
#define SINHALA_LETTER_ALPAPRAANA_JAYANNA   34
#define SINHALA_LETTER_MAHAAPRAANA_JAYANNA   35
#define SINHALA_LETTER_TAALUJA_NAASIKYAYA   36
#define SINHALA_LETTER_TAALUJA_SANYOOGA_NAAKSIKYAYA   37
#define SINHALA_LETTER_SANYAKA_JAYANNA   38
#define SINHALA_LETTER_ALPAPRAANA_TTAYANNA   39
#define SINHALA_LETTER_MAHAAPRAANA_TTAYANNA   40
#define SINHALA_LETTER_ALPAPRAANA_DDAYANNA   41
#define SINHALA_LETTER_MAHAAPRAANA_DDAYANNA   42
#define SINHALA_LETTER_MUURDHAJA_NAYANNA   43
#define SINHALA_LETTER_SANYAKA_DDAYANNA   44
#define SINHALA_LETTER_ALPAPRAANA_TAYANNA   45
#define SINHALA_LETTER_MAHAAPRAANA_TAYANNA   46
#define SINHALA_LETTER_ALPAPRAANA_DAYANNA   47
#define SINHALA_LETTER_MAHAAPRAANA_DAYANNA   48
#define SINHALA_LETTER_DANTAJA_NAYANNA   49
#define SINHALA_LETTER_SANYAKA_DAYANNA   51
#define SINHALA_LETTER_ALPAPRAANA_PAYANNA   52
#define SINHALA_LETTER_MAHAAPRAANA_PAYANNA   53
#define SINHALA_LETTER_ALPAPRAANA_BAYANNA   54
#define SINHALA_LETTER_MAHAAPRAANA_BAYANNA   55
#define SINHALA_LETTER_MAYANNA   56
#define SINHALA_LETTER_AMBA_BAYANNA   57
#define SINHALA_LETTER_YAYANNA   58
#define SINHALA_LETTER_RAYANNA   59
#define SINHALA_LETTER_DANTAJA_LAYANNA   61
#define SINHALA_LETTER_VAYANNA   256
#define SINHALA_LETTER_TAALUJA_SAYANNA   257
#define SINHALA_LETTER_MUURDHAJA_SAYANNA   258
#define SINHALA_LETTER_DANTAJA_SAYANNA   259
#define SINHALA_LETTER_HAYANNA   260
#define SINHALA_LETTER_MUURDHAJA_LAYANNA   261
#define SINHALA_LETTER_FAYANNA   262
#define SINHALA_SIGN_AL_LAKUNA   266
#define SINHALA_VOWEL_SIGN_AELA_PILLA   271
#define SINHALA_VOWEL_SIGN_KETTI_AEDA_PILLA   272
#define SINHALA_VOWEL_SIGN_DIGA_AEDA_PILLA   273
#define SINHALA_VOWEL_SIGN_KETTI_IS_PILLA   274
#define SINHALA_VOWEL_SIGN_DIGA_IS_PILLA   275
#define SINHALA_VOWEL_SIGN_KETTI_PAA_PILLA   276
#define SINHALA_VOWEL_SIGN_DIGA_PAA_PILLA   278
#define SINHALA_VOWEL_SIGN_GAETTA_PILLA   280
#define SINHALA_VOWEL_SIGN_KOMBUVA   281
#define SINHALA_VOWEL_SIGN_DIGA_KOMBUVA   282
#define SINHALA_VOWEL_SIGN_KOMBU_DEKA   283
#define SINHALA_VOWEL_SIGN_KOMBUVA_HAA_AELA_PILLA   284
#define SINHALA_VOWEL_SIGN_KOMBUVA_HAA_DIGA_AELA_PILLA_0DCA   285
#define SINHALA_VOWEL_SIGN_KOMBUVA_HAA_GAYANUKITTA_0DDF   286
#define SINHALA_VOWEL_SIGN_GAYANUKITTA   287
#define SINHALA_VOWEL_SIGN_DIGA_GAETTA_PILLA   306
#define SINHALA_VOWEL_SIGN_DIGA_GAYANUKITTA   307


#define RA_AND_YA 1001



/* Two routines from the indica.lex. They have changed quite a lot from their original version. */
void sh_cons_vow(int, int, int);
void sh_lig_vow(int, int, int, int);


/* These variables were taken directly from the indica.lex */
int current_language = 0, current_input_mode = 1;
BOOLEAN already_read = FALSE, r_con_a = FALSE, sh_hyphens_activated = FALSE;


/* Returns an integer calculated from the last two bytes of a UTF-8 encoded character. This is to get a unique number for each sinhala unicode character encoded in UTF-8 encoding. Above #defines were calculated using the same equation.
*/
int utf8_to_number(char *buf)
{

return (unsigned char)buf[1]*256+(unsigned char) buf[2]-46722+2;

}


%}



SINHALA_SIGN_ANUSVARAYA \xe0\xb6\x82
SINHALA_SIGN_VISARGAYA \xe0\xb6\x83
SINHALA_LETTER_AYANNA \xe0\xb6\x85
SINHALA_LETTER_AAYANNA \xe0\xb6\x86
SINHALA_LETTER_AEYANNA \xe0\xb6\x87
SINHALA_LETTER_AEEYANNA \xe0\xb6\x88
SINHALA_LETTER_IYANNA \xe0\xb6\x89
SINHALA_LETTER_IIYANNA \xe0\xb6\x8a
SINHALA_LETTER_UYANNA \xe0\xb6\x8b
SINHALA_LETTER_UUYANNA \xe0\xb6\x8c
SINHALA_LETTER_IRUYANNA \xe0\xb6\x8d
SINHALA_LETTER_IRUUYANNA \xe0\xb6\x8e
SINHALA_LETTER_ILUYANNA \xe0\xb6\x8f
SINHALA_LETTER_ILUUYANNA \xe0\xb6\x90
SINHALA_LETTER_EYANNA \xe0\xb6\x91
SINHALA_LETTER_EEYANNA \xe0\xb6\x92
SINHALA_LETTER_AIYANNA \xe0\xb6\x93
SINHALA_LETTER_OYANNA \xe0\xb6\x94
SINHALA_LETTER_OOYANNA \xe0\xb6\x95
SINHALA_LETTER_AUYANNA \xe0\xb6\x96
SINHALA_LETTER_ALPAPRAANA_KAYANNA \xe0\xb6\x9a
SINHALA_LETTER_MAHAAPRAANA_KAYANNA \xe0\xb6\x9b
SINHALA_LETTER_ALPAPRAANA_GAYANNA \xe0\xb6\x9c
SINHALA_LETTER_MAHAAPRAANA_GAYANNA \xe0\xb6\x9d
SINHALA_LETTER_KANTAJA_NAASIKYAYA \xe0\xb6\x9e
SINHALA_LETTER_SANYAKA_GAYANNA \xe0\xb6\x9f
SINHALA_LETTER_ALPAPRAANA_CAYANNA \xe0\xb6\xa0
SINHALA_LETTER_MAHAAPRAANA_CAYANNA \xe0\xb6\xa1
SINHALA_LETTER_ALPAPRAANA_JAYANNA \xe0\xb6\xa2
SINHALA_LETTER_MAHAAPRAANA_JAYANNA \xe0\xb6\xa3
SINHALA_LETTER_TAALUJA_NAASIKYAYA \xe0\xb6\xa4
SINHALA_LETTER_TAALUJA_SANYOOGA_NAAKSIKYAYA \xe0\xb6\xa5
SINHALA_LETTER_SANYAKA_JAYANNA \xe0\xb6\xa6
SINHALA_LETTER_ALPAPRAANA_TTAYANNA \xe0\xb6\xa7
SINHALA_LETTER_MAHAAPRAANA_TTAYANNA \xe0\xb6\xa8
SINHALA_LETTER_ALPAPRAANA_DDAYANNA \xe0\xb6\xa9
SINHALA_LETTER_MAHAAPRAANA_DDAYANNA \xe0\xb6\xaa
SINHALA_LETTER_MUURDHAJA_NAYANNA \xe0\xb6\xab
SINHALA_LETTER_SANYAKA_DDAYANNA \xe0\xb6\xac
SINHALA_LETTER_ALPAPRAANA_TAYANNA \xe0\xb6\xad
SINHALA_LETTER_MAHAAPRAANA_TAYANNA \xe0\xb6\xae
SINHALA_LETTER_ALPAPRAANA_DAYANNA \xe0\xb6\xaf
SINHALA_LETTER_MAHAAPRAANA_DAYANNA \xe0\xb6\xb0
SINHALA_LETTER_DANTAJA_NAYANNA \xe0\xb6\xb1
SINHALA_LETTER_SANYAKA_DAYANNA \xe0\xb6\xb3
SINHALA_LETTER_ALPAPRAANA_PAYANNA \xe0\xb6\xb4
SINHALA_LETTER_MAHAAPRAANA_PAYANNA \xe0\xb6\xb5
SINHALA_LETTER_ALPAPRAANA_BAYANNA \xe0\xb6\xb6
SINHALA_LETTER_MAHAAPRAANA_BAYANNA \xe0\xb6\xb7
SINHALA_LETTER_MAYANNA \xe0\xb6\xb8
SINHALA_LETTER_AMBA_BAYANNA \xe0\xb6\xb9
SINHALA_LETTER_YAYANNA \xe0\xb6\xba
SINHALA_LETTER_RAYANNA \xe0\xb6\xbb
SINHALA_LETTER_DANTAJA_LAYANNA \xe0\xb6\xbd
SINHALA_LETTER_VAYANNA \xe0\xb7\x80
SINHALA_LETTER_TAALUJA_SAYANNA \xe0\xb7\x81
SINHALA_LETTER_MUURDHAJA_SAYANNA \xe0\xb7\x82
SINHALA_LETTER_DANTAJA_SAYANNA \xe0\xb7\x83
SINHALA_LETTER_HAYANNA \xe0\xb7\x84
SINHALA_LETTER_MUURDHAJA_LAYANNA \xe0\xb7\x85
SINHALA_LETTER_FAYANNA \xe0\xb7\x86
SINHALA_SIGN_AL_LAKUNA \xe0\xb7\x8a
SINHALA_VOWEL_SIGN_AELA_PILLA \xe0\xb7\x8f
SINHALA_VOWEL_SIGN_KETTI_AEDA_PILLA \xe0\xb7\x90
SINHALA_VOWEL_SIGN_DIGA_AEDA_PILLA \xe0\xb7\x91
SINHALA_VOWEL_SIGN_KETTI_IS_PILLA \xe0\xb7\x92
SINHALA_VOWEL_SIGN_DIGA_IS_PILLA \xe0\xb7\x93
SINHALA_VOWEL_SIGN_KETTI_PAA_PILLA \xe0\xb7\x94
SINHALA_VOWEL_SIGN_DIGA_PAA_PILLA \xe0\xb7\x96
SINHALA_VOWEL_SIGN_GAETTA_PILLA \xe0\xb7\x98
SINHALA_VOWEL_SIGN_KOMBUVA \xe0\xb7\x99
SINHALA_VOWEL_SIGN_DIGA_KOMBUVA \xe0\xb7\x9a
SINHALA_VOWEL_SIGN_KOMBU_DEKA \xe0\xb7\x9b
SINHALA_VOWEL_SIGN_KOMBUVA_HAA_AELA_PILLA \xe0\xb7\x9c
SINHALA_VOWEL_SIGN_KOMBUVA_HAA_DIGA_AELA_PILLA_0DCA \xe0\xb7\x9d
SINHALA_VOWEL_SIGN_KOMBUVA_HAA_GAYANUKITTA_0DDF \xe0\xb7\x9e
SINHALA_VOWEL_SIGN_GAYANUKITTA \xe0\xb7\x9f
SINHALA_VOWEL_SIGN_DIGA_GAETTA_PILLA \xe0\xb7\xb2
SINHALA_VOWEL_SIGN_DIGA_GAYANUKITTA \xe0\xb7\xb3

ZWJ  \xe2\x80\x8d




SHVOWEL		("\xe0\xb6"[\x85-\x96])
SHCONSONANT	("\xe0\xb6"[\x9a-\xbb\xbd]|"\xe0\xb7"[\x80-\x86])
SHLIGATURE	("\xe0\xb6\x9a\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb7\x82"|"\xe0\xb6\x9a\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb7\x80"|"\xe0\xb6\xb1\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb6\xaf"|"\xe0\xb6\xb1\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb6\xb0"|"\xe0\xb6\xb1\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb6\xae"|"\xe0\xb6\xad\xe0\xb7\x8a\xe2\x80\x8d\xe0\xb6\xae")

RA_OR_YA    ("\xe0\xb6\xbb"|"\xe0\xb6\xba")

VOWEL_SIGN  ("\xe0\xb7\x8f"|"\xe0\xb7\x90"|"\xe0\xb7\x91"|"\xe0\xb7\x92"|"\xe0\xb7\x93"|"\xe0\xb7\x94"|"\xe0\xb7\x96"|"\xe0\xb7\x98"|"\xe0\xb7\x99"|"\xe0\xb7\x9a"|"\xe0\xb7\x9b"|"\xe0\xb7\x9c"|"\xe0\xb7\x9d"|"\xe0\xb7\x9e"|"\xe0\xb7\x9f"|"\xe0\xb7\xb2"|"\xe0\xb7\xb3")


%%

{SHVOWEL} 	{ sh_cons_vow(0, 0,utf8_to_number(yytext)); }

{SINHALA_SIGN_ANUSVARAYA}   { sh_cons_vow(SINHALA_SIGN_ANUSVARAYA, 0, 0); }

{SINHALA_SIGN_VISARGAYA}   { sh_cons_vow(SINHALA_SIGN_VISARGAYA, 0, 0); }

{SHCONSONANT}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{SINHALA_LETTER_RAYANNA}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{SINHALA_LETTER_YAYANNA}{VOWEL_SIGN}    {sh_cons_vow(utf8_to_number(yytext), RA_AND_YA,utf8_to_number(yytext+21));}

{SHCONSONANT}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{SINHALA_LETTER_RAYANNA}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{SINHALA_LETTER_YAYANNA}    {sh_cons_vow(utf8_to_number(yytext), RA_AND_YA,SINHALA_LETTER_AYANNA);}

{SHCONSONANT}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{RA_OR_YA}{VOWEL_SIGN}   { sh_cons_vow(utf8_to_number(yytext), utf8_to_number(yytext+9),utf8_to_number(yytext+12) ); }


{SHCONSONANT}{SINHALA_SIGN_AL_LAKUNA}{ZWJ}{RA_OR_YA}   { sh_cons_vow(utf8_to_number(yytext), utf8_to_number(yytext+9),SINHALA_LETTER_AYANNA ); }

{SHCONSONANT}{SINHALA_SIGN_AL_LAKUNA}   { sh_cons_vow(utf8_to_number(yytext), 0,0); }

{SHCONSONANT}{VOWEL_SIGN}   { sh_cons_vow(utf8_to_number(yytext), 0, utf8_to_number(yytext+3)); }

{SHLIGATURE}{VOWEL_SIGN}	{sh_lig_vow(utf8_to_number(yytext),utf8_to_number(yytext+9),0,utf8_to_number(yytext+12));}

{SHLIGATURE}	{sh_lig_vow(utf8_to_number(yytext),utf8_to_number(yytext+9),0,SINHALA_LETTER_AYANNA);}

{SHCONSONANT}   { sh_cons_vow(utf8_to_number(yytext), 0,SINHALA_LETTER_AYANNA); }



%%

void sh_place_normal_vowel(char *s, int extension, int vow)
{
	char r[32],y[32];
	
	switch (extension) {
		case 0x00: r[0] = 0x00; y[0] = 0x00; break;
		case SINHALA_LETTER_RAYANNA: strcpy(r,"r"); y[0] = 0x00; break;
		case SINHALA_LETTER_YAYANNA:	r[0] = 0x00; strcpy(y,"a\\SHb\\char205"); break;
		//case RA_AND_YA: strcpy(r,"r"); strcpy(y,"a\\SHb\\char205"); break;
		// The indica.lex had one similar to the above line, but it incorrectly type set the the rakaransaya. I changed it to the following line. CHECK this again later.
 
		case RA_AND_YA: r[0] = 0x00; strcpy(y,"ar\\SHb\\char205"); break;
		default: break; }

	switch (vow) {
		case 0:	printf("%s%s%s",s,r,y); break;
		// An implicit vowel Ayanna
		case SINHALA_LETTER_AYANNA: printf("%s%sa%s",s,y,r); break;
		
		case SINHALA_VOWEL_SIGN_AELA_PILLA: printf("%s%sa%s\\char0",s,y,r); break;
		
		case SINHALA_VOWEL_SIGN_KETTI_AEDA_PILLA: if ((!strcmp(s,"\\char29")) && (extension == 0x00)) printf("\\char29u"); else
						printf("%s%sa%s\\char8",s,y,r); break;
		case SINHALA_VOWEL_SIGN_DIGA_AEDA_PILLA: if ((!strcmp(s,"\\char29")) && (extension == 0x00)) printf("\\char29uu"); else
						printf("%s%sa%s\\char9",s,y,r); break;
		case SINHALA_VOWEL_SIGN_KETTI_IS_PILLA: printf("%s%si%s",s,y,r); break;
		case SINHALA_VOWEL_SIGN_DIGA_IS_PILLA: printf("%s%sii%s",s,y,r); break;
		
		
		case SINHALA_VOWEL_SIGN_KETTI_PAA_PILLA: if ((extension == 0x00) || (extension == SINHALA_LETTER_YAYANNA)) 
			{	if ((!strcmp(s,"\\char29")) && (extension == 0x00)) printf("\\char29a\\char8"); else
				printf("%s%su",s,y); }
			else if ((extension == SINHALA_LETTER_RAYANNA) || (extension == RA_AND_YA)) printf("%s%sa\\char1",s,y); break;
		case SINHALA_VOWEL_SIGN_DIGA_PAA_PILLA: if ((extension == 0x00) || (extension == SINHALA_LETTER_YAYANNA)) 
			{	if ((!strcmp(s,"\\char29")) && (extension == 0x00)) printf("\\char29a\\char9"); else
				printf("%s%suu",s,y); }
			else if ((extension == SINHALA_LETTER_RAYANNA) || (extension == RA_AND_YA)) printf("%s%sa\\char2",s,y); break;

		
		case SINHALA_VOWEL_SIGN_GAETTA_PILLA: printf("%s%sa%s\\char1",s,y,r); break;
		case SINHALA_VOWEL_SIGN_DIGA_GAETTA_PILLA: printf("%s%sa%s\\char2",s,y,r); break;

		
		case SINHALA_VOWEL_SIGN_GAYANUKITTA: printf("%s%sa%s\\char3",s,y,r); break;
		
		case SINHALA_VOWEL_SIGN_DIGA_GAYANUKITTA: printf("%s%sa%s\\char4",s,y,r); break;

		/*
		case CANDRA_E: break;
		*/

		case SINHALA_VOWEL_SIGN_KOMBUVA: printf("\\char5%s%sa%s",s,y,r); break;
		case SINHALA_VOWEL_SIGN_DIGA_KOMBUVA: printf("\\char5%s%s%s",s,y,r); break;
		case SINHALA_VOWEL_SIGN_KOMBU_DEKA: printf("\\char6%s%sa%s",s,y,r); break;

		//case CANDRA_O: break;

		case SINHALA_VOWEL_SIGN_KOMBUVA_HAA_AELA_PILLA: printf("\\char5%s%sa%s\\char0",s,y,r); break;
		case SINHALA_VOWEL_SIGN_KOMBUVA_HAA_DIGA_AELA_PILLA_0DCA: printf("\\char5%s%sa%s\\char7",s,y,r); break;
		case SINHALA_VOWEL_SIGN_KOMBUVA_HAA_GAYANUKITTA_0DDF: printf("\\char5%s%sa%s\\char3",s,y,r); break;
                
		default: break;
		}
}



void sh_cons_vow(int con, int extension, int vow)
{
	printf("{");
	if (con == 0) {
		switch (vow) {
			case SINHALA_LETTER_AYANNA:		printf("\\SHa\\char16"); break;
			case SINHALA_LETTER_AAYANNA:	printf("\\SHa\\char16\\char0"); break;
			case SINHALA_LETTER_AEYANNA:	printf("\\SHa\\char16\\char8"); break;
			case SINHALA_LETTER_AEEYANNA :	printf("\\SHa\\char16\\char9"); break;
			case SINHALA_LETTER_IYANNA:		printf("\\SHa\\char17"); break;
			case SINHALA_LETTER_IIYANNA:	printf("\\SHa\\char18"); break;
			case SINHALA_LETTER_UYANNA:		printf("\\SHa\\char19"); break;
			case SINHALA_LETTER_UUYANNA:	printf("\\SHa\\char19\\char3"); break;
			case SINHALA_LETTER_IRUYANNA:		printf("\\SHa\\char20\\char1"); break;
			case SINHALA_LETTER_IRUUYANNA:	printf("\\SHa\\char20\\char2"); break;
			case SINHALA_LETTER_ILUYANNA:		printf("\\SHa\\char21"); break;
			case SINHALA_LETTER_ILUUYANNA:	printf("\\SHa\\char21\\char3"); break;
			//case CANDRA_E:	break;
			case SINHALA_LETTER_EYANNA:		printf("\\SHa\\char22"); break;
			case SINHALA_LETTER_EEYANNA:	printf("\\SHa\\char23"); break;
			case SINHALA_LETTER_AIYANNA:	printf("\\SHa\\char5\\char22"); break;
			//case CANDRA_O:	break;
			case SINHALA_LETTER_OYANNA :		printf("\\SHa\\char24"); break;
			case SINHALA_LETTER_OOYANNA:	printf("\\SHa\\char25"); break;
			case SINHALA_LETTER_AUYANNA:	printf("\\SHa\\char24\\char3"); break;
			default: break;
			}}
	else if (con == SINHALA_SIGN_ANUSVARAYA) printf("\\SHa\\char11");
	else if (con == SINHALA_SIGN_VISARGAYA) printf("\\SHa\\char10");
	else {
		//CHECK this again with the original
		if ((con >= 26) && (con <= 56) && (con != SINHALA_LETTER_TAALUJA_NAASIKYAYA) && (con != SINHALA_LETTER_ALPAPRAANA_DAYANNA ) && (con!=SINHALA_LETTER_SANYAKA_GAYANNA) && (con!=SINHALA_LETTER_SANYAKA_JAYANNA) && (con!=SINHALA_LETTER_SANYAKA_DDAYANNA) && (con!=SINHALA_LETTER_SANYAKA_DAYANNA)) printf("\\SHa");
		else printf("\\SHb");
		//CHECK
		//if (sh_hyphens_activated == TRUE) printf("\\-"); else sh_hyphens_activated = TRUE;
		if (r_con_a == TRUE) printf("{}r");
		switch(con) {
			case SINHALA_LETTER_ALPAPRAANA_KAYANNA: 	sh_place_normal_vowel("\\char77",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_KAYANNA: 	sh_place_normal_vowel("\\char85",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_GAYANNA : 	sh_place_normal_vowel("\\char66",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_GAYANNA: 	sh_place_normal_vowel("\\char101",extension,vow); break;
			case SINHALA_LETTER_KANTAJA_NAASIKYAYA: 	sh_place_normal_vowel("\\char109",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_CAYANNA: 	sh_place_normal_vowel("\\char117",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_CAYANNA: 	sh_place_normal_vowel("\\char125",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_JAYANNA: 	sh_place_normal_vowel("\\char133",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_JAYANNA: 	sh_place_normal_vowel("\\char141",extension,vow); break;
			/*
			case CON_NY: 	if(current_input_mode == SAMANALA)
					{
						sh_place_normal_vowel("\\char139",extension,vow); break;
					}
					else
					{
						sh_place_da_like_vowel("\\char139",extension,vow); break;
					}
			*/
			case SINHALA_LETTER_ALPAPRAANA_TTAYANNA: 	sh_place_normal_vowel("\\char149",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_TTAYANNA: 	sh_place_normal_vowel("\\char157",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_DDAYANNA: 	sh_place_normal_vowel("\\char165",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_DDAYANNA: 	sh_place_normal_vowel("\\char173",extension,vow); break;
			case SINHALA_LETTER_MUURDHAJA_NAYANNA: 	sh_place_normal_vowel("\\char181",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_TAYANNA : 	sh_place_normal_vowel("\\char189",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_TAYANNA: 	sh_place_normal_vowel("\\char197",extension,vow); break;

			case SINHALA_LETTER_ALPAPRAANA_DAYANNA: 	sh_place_normal_vowel("\\char163",extension,vow); break;
			
			/*
			case CON_D: 	if(current_input_mode == SAMANALA)
					{
						sh_place_normal_vowel("\\char163",extension,vow); break;
					}
					else
					{
						sh_place_da_like_vowel("\\char163",extension,vow); break;
					}
			*/

			case SINHALA_LETTER_MAHAAPRAANA_DAYANNA: 	sh_place_normal_vowel("\\char205",extension,vow); break;
			case SINHALA_LETTER_DANTAJA_NAYANNA: 	sh_place_normal_vowel("\\char213",extension,vow); break;
			//case CON_NNN: 	break; 
			case SINHALA_LETTER_ALPAPRAANA_PAYANNA: 	sh_place_normal_vowel("\\char221",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_PAYANNA: 	sh_place_normal_vowel("\\char229",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_BAYANNA: 	sh_place_normal_vowel("\\char237",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_BAYANNA: 	sh_place_normal_vowel("\\char245",extension,vow); break;
			case SINHALA_LETTER_MAYANNA: 	sh_place_normal_vowel("\\char253",extension,vow); break;
			case SINHALA_LETTER_YAYANNA: 	sh_place_normal_vowel("\\char21",extension,vow); break;
			case SINHALA_LETTER_RAYANNA: 	sh_place_normal_vowel("\\char29",extension,vow); break;
			//CHECK
			//case CON_RR: 	break;
			case SINHALA_LETTER_DANTAJA_LAYANNA: 	sh_place_normal_vowel("\\char37",extension,vow); break;
			//CHECK
			case SINHALA_LETTER_MUURDHAJA_LAYANNA: 	sh_place_normal_vowel("\\char85",extension,vow); break;
			case SINHALA_LETTER_VAYANNA : 	sh_place_normal_vowel("\\char14",extension,vow); break;
			case SINHALA_LETTER_TAALUJA_SAYANNA: 	sh_place_normal_vowel("\\char53",extension,vow); break;
			case SINHALA_LETTER_MUURDHAJA_SAYANNA: 	sh_place_normal_vowel("\\char61",extension,vow); break;
			case SINHALA_LETTER_DANTAJA_SAYANNA: 	sh_place_normal_vowel("\\char69",extension,vow); break;
			case SINHALA_LETTER_HAYANNA: 	sh_place_normal_vowel("\\char77",extension,vow); break;
			case  SINHALA_LETTER_FAYANNA: 	sh_place_normal_vowel("\\char213",extension,vow); break;
			case SINHALA_LETTER_SANYAKA_GAYANNA: 	sh_place_normal_vowel("\\char93",extension,vow); break;
			//case CON_NAS_C: 	sh_place_normal_vowel("\\char101",extension,vow); break;
			case SINHALA_LETTER_SANYAKA_DDAYANNA: 	sh_place_normal_vowel("\\char109",extension,vow); break;
			
			case SINHALA_LETTER_SANYAKA_DAYANNA: sh_place_normal_vowel("\\char187",extension,vow); break;
			/*
			CHECK - 
			case CON_NAS_D: 	if(current_input_mode == SAMANALA)
						{
							sh_place_normal_vowel("\\char187",extension,vow); break;
						}
						else
						{
					 		sh_place_da_like_vowel("\\char187",extension,vow); break;
						}
			*/
			case SINHALA_LETTER_AMBA_BAYANNA: 	sh_place_normal_vowel("\\char117",extension,vow); break;
			case SINHALA_LETTER_SANYAKA_JAYANNA : 	sh_place_normal_vowel("\\char125",extension,vow); break;
			//case CON_KS: 		break;
			//case CON_LLL: 		break;
			

			default: break;
			}
		}
	printf("}");
}


void sh_lig_vow(int cona, int conb, int extension, int vow)
{
	//printf("%d:%d\n", cona, conb);

	if ((cona == SINHALA_LETTER_ALPAPRAANA_DDAYANNA) && (conb == SINHALA_LETTER_VAYANNA)) printf("{\\SHb");
	else printf("{\\SHc");
	//if (sh_hyphens_activated == TRUE) printf("\\-"); else sh_hyphens_activated = TRUE;
	if (r_con_a == TRUE) printf("{}r");
	switch(cona) {
		case SINHALA_LETTER_ALPAPRAANA_KAYANNA: switch(conb) {
			case SINHALA_LETTER_VAYANNA: sh_place_normal_vowel("\\char15",extension,vow); break;
			case SINHALA_LETTER_MUURDHAJA_SAYANNA: sh_place_normal_vowel("\\char61",extension,vow); break;
			default: break; } break;
		
		case SINHALA_LETTER_DANTAJA_NAYANNA: switch(conb) {
			case SINHALA_LETTER_MAHAAPRAANA_DAYANNA: sh_place_normal_vowel("\\char69",extension,vow); break;
			case SINHALA_LETTER_MAHAAPRAANA_TAYANNA: sh_place_normal_vowel("\\char77",extension,vow); break;
			case SINHALA_LETTER_ALPAPRAANA_DAYANNA: sh_place_normal_vowel("\\char91",extension,vow); break;
				/*	
				if(current_input_mode == SAMANALA)
					{
						sh_place_normal_vowel("\\char91",extension,vow); break;
					}
					else
					{
						sh_place_da_like_vowel("\\char91",extension,vow); break;
					}
				*/
			default: break; } break;
		/*
		case CON_J: switch(conb) {
			case CON_NY: 	if(current_input_mode == SAMANALA)
					{
						sh_place_normal_vowel("\\char27",extension,vow); break;
					}
					else
					{
						sh_place_da_like_vowel("\\char27",extension,vow); break;
					}
			default: break; } break;
		*/
		case SINHALA_LETTER_ALPAPRAANA_TAYANNA: switch(conb) {
			case SINHALA_LETTER_MAHAAPRAANA_TAYANNA: sh_place_normal_vowel("\\char109",extension,vow); break;
			default: break; } break;
		/*
		case CON_D: switch(conb) {
			case CON_V: sh_place_normal_vowel("\\char101",extension,vow); break;
			default: break; } break;
		*/
		default: break; }
		printf("}");
}



int main()
{
	yylex();
	return 0;
}

