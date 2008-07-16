/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) Dushara Jayasinghe
 *  Copyright (C) 2004 - 2008 
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <sys/types.h>

#include "layout.h"
#include "parser.h"
#include "imcompat.h"

// state handler prototypes
#define PRS_STATE(name) static int handle_##name(void *, u_int16_t);
#include "states.h"

// state names for debugging
#define PRS_STATE(name) #name,
static const char * const state[ePrsCount] = {
#include "states.h"
};

// state handlers
#define PRS_STATE(name) handle_##name,
static int (* const handler[ePrsCount])(void*,u_int16_t) = {
#include "states.h"
};

// parser flags
#define DISABLE_YANS    (1<<0)
#define DISABLE_REP     (1<<1)
#define DISABLE_RAK     (1<<2)
#define DISABLE_JOIN    (1<<3)
#define RAW_INPUT       (1<<4)

#define IDLE_CLEAR      (DISABLE_YANS | DISABLE_REP | DISABLE_RAK | DISABLE_JOIN)

#define ZWJ     0x200d

const u_int16_t consonents[] = {
    SCH_KAYANNA, SCH__KAYANNA, SCH_GAYANNA, SCH__GAYANNA, SCH_NAASIKAYA,
    SCH_NGAYANNA, SCH_CAYANNA, SCH__CAYANNA, SCH_JAYANNA, SCH__JAYANNA,
    SCH_NYAYANNA, SCH_GNYAYANNA, SCH_NJAYANNA, SCH_TTAYANNA, SCH__TTAYANNA,
    SCH_DDAYANNA, SCH__DDAYANNA, SCH__NAYANNA, SCH_NDDAYANNA, SCH_TAYANNA,
    SCH__TAYANNA, SCH_DAYANNA, SCH__DAYANNA, SCH_NAYANNA, SCH_NDAYANNA,
    SCH_PAYANNA, SCH__PAYANNA, SCH_BAYANNA, SCH__BAYANNA, SCH_MAYANNA,
    SCH_MBAYANNA, SCH_YAYANNA, SCH_RAYANNA, SCH_LAYANNA, SCH_VAYANNA,
    SCH_SHAYANNA, SCH__SAYANNA, SCH_SAYANNA, SCH_HAYANNA, SCH__LAYANNA,
    SCH_FAYANNA,
};

// compound characters
static const u_int16_t yans[] = {
    SINHALA_PAGE | SCH_AL, 
    ZWJ, 
    SINHALA_PAGE | SCH_YAYANNA
};

static const u_int16_t rak[] = {
    SINHALA_PAGE | SCH_AL, 
    ZWJ, 
    SINHALA_PAGE | SCH_RAYANNA
};

static const u_int16_t rep[] = {
    SINHALA_PAGE | SCH_RAYANNA, 
    SINHALA_PAGE | SCH_AL, 
    ZWJ
};

static const u_int16_t mlu[] = {
    SINHALA_PAGE | SCH__LAYANNA, 
    SINHALA_PAGE | SCH_PAA
};

static const u_int16_t baendi[] = {
    SINHALA_PAGE | SCH_AL, 
    ZWJ, 
};

static const u_int16_t touch[] = {
    ZWJ, 
    SINHALA_PAGE | SCH_AL, 
};

#define COMPLEX_DEF(name)	{name, sizeof(name)/sizeof(name[0]) },
static const struct
{
    const u_int16_t *data;
    int size;
} compound[eCmplx_Count] = {
#include "complex_def.h"
};

static const u_int16_t invalid_key[] = {
    SINHALA_PAGE | SCH_YAYANNA,
    SINHALA_PAGE | SCH_TAYANNA,
    SINHALA_PAGE | SCH_PAA,
    SINHALA_PAGE | SCH_RAYANNA,
    ' ',
    SINHALA_PAGE | SCH_AYANNA, 
    SINHALA_PAGE | SCH_VAYANNA, 
    SINHALA_PAGE | SCH_LAYANNA, 
    SINHALA_PAGE | SCH_ANUSWARA, 
    SINHALA_PAGE | SCH_GAYANNA, 
    SINHALA_PAGE | SCH_PAA, 
    SINHALA_PAGE | SCH_YAYANNA, 
    SINHALA_PAGE | SCH_IS, 
};

static int translate_key(const keypair_t *lookup, int key, int count)
{
    int i;
    for(i=0; i<count; i++) {
        if(lookup[i].key == key)
            return lookup[i].translated;
    }

    return 0;
}

static int char_in_list(u_int16_t tr, const u_int16_t *buf, int size)
{
    while(size--) {
        if(tr == *buf++) {
            return 1;
        }
    }

    return 0;
}

static void append_compound(parser_data_t *pdata, u_int16_t tr)
{
    int i;

    tr &= ~COMPOUND_MASK;
    for(i=0; i<compound[tr].size; i++) {
        pdata->preedit[pdata->pe_count++] = compound[tr].data[i];
    }
}

static void insert_compound(parser_data_t *pdata, u_int16_t tr, int offset)
{
    int i;
    tr &= ~COMPOUND_MASK;

    for(i = pdata->pe_count; i >= offset; i--) {
        pdata->preedit[i+compound[tr].size] = pdata->preedit[i];
    }

    for(i = 0; i<compound[tr].size; i++) {
        pdata->preedit[offset + i] = compound[tr].data[i];
    }

    pdata->pe_count += compound[tr].size;
}

static int handle_Iru(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_GAETA) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_IRUUYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_Ilu(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_GAYANU) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_ILUUYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_KombuDekaCons(void *context, u_int16_t tr)
{
    parser_data_t *pdata = get_parser_data(context);
    int ret = 0;

    if(tr == (COMPOUND_MASK  | eCmplx_rak)) {
        insert_compound(pdata, tr, pdata->pe_count-1);
    } else if(tr == (COMPOUND_MASK  | eCmplx_rep)) {
        insert_compound(pdata, tr, pdata->pe_count-2);
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_KombuDeka(void *context, u_int16_t tr)
{
    int ret = 0, commit=1;
    parser_data_t *pdata = get_parser_data(context);

    if(char_in_list(tr, consonents, sizeof(consonents)/sizeof(consonents[0]))) {
        pdata->preedit[pdata->pe_count++] = pdata->preedit[0];
        pdata->preedit[0] = SINHALA_PAGE | tr;
        pdata->state = ePrsKombuDekaCons;
        commit = 0;
    } else {
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_ConsRak(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AELA || tr == SCH_AEDA || tr == SCH_DAEDA ) {
        pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;
    return ret;
}

static int handle_KombuAela(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AL) {
        pdata->preedit[pdata->pe_count-1] = SINHALA_PAGE | SCH_DKOMBUAELA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_Gaeta(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_GAETA) {
        pdata->preedit[1] = SINHALA_PAGE | SCH_DGAETA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_KombuJoiner(void *context, u_int16_t tr)
{
    int ret = 0, commit=1;
    parser_data_t *pdata = get_parser_data(context);

    if(char_in_list(tr, consonents, sizeof(consonents)/sizeof(consonents[0]))) {
        // go back to consonent page (now joiner won't be accepted
        pdata->preedit[pdata->pe_count] = pdata->preedit[pdata->pe_count-1];
        pdata->preedit[pdata->pe_count-1] = SINHALA_PAGE | tr;
        pdata->pe_count++;
        pdata->state = ePrsKombuCons;
        commit = 0;
    } else {
        pdata->pe_count-=2; // drop the joiner
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_KombuCons(void *context, u_int16_t tr)
{
    parser_data_t *pdata = get_parser_data(context);
    int ret = 0, commit=1;

    if(tr == SCH_AL) {
        pdata->preedit[pdata->pe_count-1] = SINHALA_PAGE | SCH_DKOMBUWA;
    } else if(tr == SCH_AELA ) {
        pdata->preedit[pdata->pe_count-1] = SINHALA_PAGE | SCH_KOMBUAELA;
        pdata->state = ePrsKombuAela;
        commit = 0;
    } else if(tr == SCH_GAYANU ) {
        pdata->preedit[pdata->pe_count-1] = SINHALA_PAGE | SCH_KOMBUGAYANU;
    } else if(tr == (COMPOUND_MASK  | eCmplx_yans) && !(pdata->flags & DISABLE_YANS)) {
        insert_compound(pdata, tr, 1);
        commit = 0;
        pdata->flags |= DISABLE_YANS;
    } else if(tr == (COMPOUND_MASK  | eCmplx_rak) && !(pdata->flags & DISABLE_RAK)) {
        pdata->flags |= (DISABLE_RAK | DISABLE_REP);
        commit = 0;
        insert_compound(pdata, tr, pdata->pe_count-1);
    } else if(tr == (COMPOUND_MASK  | eCmplx_rep) && !(pdata->flags & DISABLE_REP)) {
        if(pdata->flags & DISABLE_YANS) {
            if(pdata->preedit[pdata->pe_count-5] != (SINHALA_PAGE | SCH_YAYANNA)) {
                // no yayanna before yansaya (invalid!)
                ret = -1;
            } else {
                insert_compound(pdata, tr, pdata->pe_count-5);
            }
        } else {
            insert_compound(pdata, tr, pdata->pe_count-2);
        }
        commit = 0;
        pdata->flags |= (DISABLE_RAK | DISABLE_REP);
    } else if((tr == (COMPOUND_MASK  | eCmplx_baendi) || tr == (COMPOUND_MASK  | eCmplx_touch)) 
        && !(pdata->flags & (DISABLE_YANS | DISABLE_RAK | DISABLE_REP | DISABLE_JOIN))) {

        insert_compound(pdata, tr, pdata->pe_count-1);
        //dump_buf(pdata);
        commit = 0;
        pdata->flags |= DISABLE_JOIN;
        pdata->state = ePrsKombuJoiner;
    } else {
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_Kombuwa(void *context, u_int16_t tr)
{
    int ret = 0, commit=1;
    parser_data_t *pdata = get_parser_data(context);

    if(char_in_list(tr, consonents, sizeof(consonents)/sizeof(consonents[0]))) {
        pdata->preedit[pdata->pe_count++] = pdata->preedit[0];
        pdata->preedit[0] = SINHALA_PAGE | tr;
        pdata->state = ePrsKombuCons;
        commit = 0;
    } else if(tr == SCH_EYANNA ) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_AIYANNA;
    } else if(tr == SCH_KOMBUWA ) {
        pdata->preedit[0] = SCH_KOMBUDEKA | SINHALA_PAGE;
        pdata->state = ePrsKombuDeka;
        commit = 0;
    } else {
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_Ispilli(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == (COMPOUND_MASK  | eCmplx_rak) ) {
        insert_compound(pdata, tr, pdata->pe_count-1);
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;
    return ret;
}

static int handle_Joiner(void *context, u_int16_t tr)
{
    int ret = 0, commit=1;
    parser_data_t *pdata = get_parser_data(context);

    if(char_in_list(tr, consonents, sizeof(consonents)/sizeof(consonents[0]))) {
        // go back to consonent page (now joiner won't be accepted
        pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
        pdata->state = ePrsConsonent;
        commit = 0;
    } else {
        pdata->pe_count-=2; // drop the joiner
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_Consonent(void *context, u_int16_t tr)
{
    int ret = 0, commit=1;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AL || tr == SCH_AELA || tr == SCH_AEDA 
        || tr == SCH_DAEDA || tr == SCH_GAYANU ) {
        pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
    } else if(tr == SCH_IS || tr == SCH_DIS) {
        pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
        pdata->state = ePrsIspilli;
        commit = 0;
    } else if(tr == SCH_GAETA ) {
        pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
        pdata->state = ePrsGaeta;
        commit = 0;
    } else if(tr == (COMPOUND_MASK  | eCmplx_rep) && !(pdata->flags & DISABLE_REP) ) {
        if(pdata->flags & DISABLE_YANS) {
            if(pdata->preedit[pdata->pe_count-4] != (SINHALA_PAGE | SCH_YAYANNA)) {
                // no yayanna before yansaya (invalid!)
                ret = -1;
            } else {
                insert_compound(pdata, tr, pdata->pe_count-4);
            }
        } else {
            insert_compound(pdata, tr, pdata->pe_count-1);
        }
        commit = 0;
        pdata->flags |= DISABLE_REP;
    } else if(tr == (COMPOUND_MASK  | eCmplx_yans) && !(pdata->flags & DISABLE_YANS)) {
        append_compound(pdata, (COMPOUND_MASK  | eCmplx_yans));
        commit = 0;
        pdata->flags |= DISABLE_YANS;
    } else if(tr == (COMPOUND_MASK  | eCmplx_rak) && !(pdata->flags & DISABLE_RAK)) {
        append_compound(pdata, (COMPOUND_MASK  | eCmplx_rak));
        commit = 0;
        pdata->flags |= DISABLE_RAK;
        pdata->state = ePrsConsRak;
    } else if((tr == (COMPOUND_MASK  | eCmplx_baendi) || tr == (COMPOUND_MASK  | eCmplx_touch))
        && !(pdata->flags & (DISABLE_YANS | DISABLE_RAK | DISABLE_REP | DISABLE_JOIN))) {
        append_compound(pdata, tr);
        commit = 0;
        pdata->flags |= DISABLE_JOIN;
        pdata->state = ePrsJoiner;
    } else {
        ret = -1;
    }

    if(commit) {
        commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
        pdata->state = ePrsIdle;
    } else {
        write_preedit(context, pdata->preedit, pdata->pe_count);
    }

    return ret;
}

static int handle_Oyanna(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AL) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_OOYANNA;
    } else if(tr == SCH_GAYANU) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_AUYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);

    pdata->state = ePrsIdle;
    return ret;
}

static int handle_Eyanna(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AL) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_EEYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);

    pdata->state = ePrsIdle;
    return ret;
}

static int handle_Uyanna(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_GAYANU) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_UUYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_Ayanna(void *context, u_int16_t tr)
{
    int ret = 0;
    parser_data_t *pdata = get_parser_data(context);

    if(tr == SCH_AEDA) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_AEYANNA;
    } else if(tr == SCH_DAEDA) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_AEEYANNA;
    } else if(tr == SCH_AELA) {
        pdata->preedit[0] = SINHALA_PAGE | SCH_AAYANNA;
    } else {
        ret = -1;
    }

    commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
    pdata->state = ePrsIdle;

    return ret;
}

static int handle_Luyanna(void *context, u_int16_t tr)
{
	int ret = 0;
	parser_data_t *pdata = get_parser_data(context);

	if(tr == SCH_DPAA) {
		pdata->preedit[1] = SINHALA_PAGE | SCH_DPAA;
	} else {
		ret = -1;
	}

	commit_clearing_preedit(context, pdata->preedit, pdata->pe_count);
	pdata->state = ePrsIdle;

	return ret;
}

static int handle_Idle(void *context, u_int16_t tr)
{
    int ret = 0, commit_len=0, use_buf=1;
    const u_int16_t *commit_buf;
    parser_data_t *pdata = get_parser_data(context);

    const u_int16_t immediate[] = {
        SCH_IYANNA, SCH_IIYANNA, SCH_PUNCT, SCH_ANUSWARA, SCH_VISARGA,
	SCH_IS, SCH_DIS, SCH_PAA, SCH_DPAA, SCH_DGAYANU
    };

    const u_int16_t invalid[] = {
        SCH_AL, SCH_AELA, SCH_AEDA, SCH_DAEDA, SCH_GAYANU, SCH_GAETA, 
        SCH_DGAETA, (COMPOUND_MASK  | eCmplx_yans), (COMPOUND_MASK  | eCmplx_rak), 
        (COMPOUND_MASK  | eCmplx_rep), (COMPOUND_MASK  | eCmplx_baendi), 
        (COMPOUND_MASK  | eCmplx_touch)
    };

    pdata->pe_count = 0;
    pdata->flags &= ~IDLE_CLEAR;

    if(pdata->flags & RAW_INPUT) {
        pdata->flags &= ~RAW_INPUT;
        commit_buf = &tr;
        commit_len = 1;
    } else if(char_in_list(tr, immediate, sizeof(immediate)/sizeof(immediate[0]))) {
        // immediately commit these
        if(tr & COMPOUND_MASK) {
            tr &= ~COMPOUND_MASK;
            commit_buf = compound[tr].data;
            commit_len = compound[tr].size;
        } else {
            if(tr & SINHALA_MASK) {
                tr |= SINHALA_PAGE;
            }
            commit_buf = &tr;
            commit_len = 1;
        }
    } else if(char_in_list(tr, invalid, sizeof(invalid)/sizeof(invalid[0]))) {
        write_status(context, invalid_key, sizeof(invalid_key)/
            sizeof(invalid_key[0]));
        use_buf = 0;
        pdata->status_on = 1;
    } else if(tr == SCH_AYANNA) {
        pdata->state = ePrsAyanna;
    } else if(tr == (COMPOUND_MASK  | eCmplx_mlu)) {
	pdata->state = ePrsLuyanna;
    } else if(tr == SCH_UYANNA) {
        pdata->state = ePrsUyanna;
    } else if(tr == SCH_ILUYANNA) {
        pdata->state = ePrsIlu;
    } else if(tr == SCH_IRUYANNA) {
        pdata->state = ePrsIru;
    } else if(tr == SCH_EYANNA) {
        pdata->state = ePrsEyanna;
    } else if(tr == SCH_OYANNA) {
        pdata->state = ePrsOyanna;
    } else if(tr == SCH_KOMBUWA) {
        pdata->state = ePrsKombuwa;
    } else if(char_in_list(tr, consonents, sizeof(consonents)/sizeof(consonents[0]))) {
        pdata->state = ePrsConsonent;
    } else {
        use_buf = 0;
        ret = -1;
    }

    if(use_buf) {
        // close the previous status message
        if(pdata->status_on) {
            pdata->status_on = 0;
            close_status(context);
        }

        if(commit_len) {
            commit_utf16(context, commit_buf, commit_len);
        } else {
		if(tr & COMPOUND_MASK) {
			append_compound(pdata, tr);
		} else {
			pdata->preedit[pdata->pe_count++] = SINHALA_PAGE | tr;
		}
		write_preedit(context, pdata->preedit, pdata->pe_count);
	}
    }

    return ret;
}

int parse_key(int keyCode, int modifier, int AltGr, void *context)
{
    u_int16_t tr=0;
    parser_data_t *pdata = get_parser_data(context);
    int ret;
    parser_state_t entry;

    modifier &= SI_MOD_KEEP_MASK;

    if(keyCode == SI_KEYCODE_ALT || keyCode == SI_KEYCODE_SHIFT || keyCode == SI_KEYCODE_CONTROL){
        // ignore don't even send through parser
        return -1;
    } else if(modifier == SI_SHIFT_MASK && !AltGr) {
        if((tr = translate_key(wijesekera.shift, keyCode, wijesekera.shift_count)));
        else if((tr = translate_key(wijesekera.shreplace, keyCode, wijesekera.shreplace_count))) { 
            pdata->flags |= RAW_INPUT;
        }
    } else if(AltGr && modifier != SI_SHIFT_MASK){
        tr = translate_key(wijesekera.altgr, keyCode, wijesekera.altgr_count);
    } else if(modifier){
        // ALT_GR is really ALT + CTRL. This handles ALT and CTRL on their own
        return -1;
    } else {
        if((tr = translate_key(wijesekera.plain, keyCode, wijesekera.plain_count)));
        else if((tr = translate_key(wijesekera.replace, keyCode, wijesekera.replace_count))) {
            pdata->flags |= RAW_INPUT;
        }
    }

    do {
	    if(pdata->status_on) {
		    pdata->status_on = 0;
		    close_status(context);
	    }

	    entry = pdata->state;
        ret = handler[pdata->state](context, tr);
        if(entry == ePrsIdle)
            break;
    } while(ret);

    return ret;
}

