/*
 * Anuradha Ratnaweera (anuadha@gnu.org)
 *
 * Copyright (C) 2004 by Anuradha Ratnaweera
 *
 * GTK+ Sinhala input method (phonetic)
 * http://sinhala.linux.lk
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtkimcontext.h>
#include <gtk/gtkimmodule.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <string.h>

/* A BIG NOTE:  Instead of working with three byte UTF-8 encoded
 * characters, we will be using the 8 least significant bits of each
 * character (including joiners).  So, ayanna will be 0x85 and so on.
 * Sinhala code page will need characters 128 to 255.
 *
 * This leaves us characters 0 to 127.  First 32 is used for control
 * characters. Only 0x0c and 0x0d is used which is also happened to be
 * the least significant bits of ZWNJ and ZWJ respectively.
 *
 * Values between 32 and 127 (0x20 to 0x7f) inclusive are used for
 * character classes.
 *
 * In the present context, we will be calling this LSB representation. */

/* FIXME: the following #definitions should go into imsinhala.h */

#define ZWNJ 0x0c
#define ZWJ  0x0d

static GType type_sinhala = 0;

struct {
	unsigned char character;
	unsigned char mahaprana;
	unsigned char sagngnaka;
	int key;
} consonents[] = {
	{0xa4, 0x00, 0x00, GDK_q},
	{0xa5, 0x00, 0x00, GDK_Q},
	{0xca, 0x00, 0x00, GDK_w},
	{0x0c, 0x00, 0x00, GDK_W},
	{0xbb, 0x00, 0x00, GDK_r},
	{0xbb, 0x00, 0x00, GDK_R},
	{0xad, 0xae, 0x00, GDK_t},
	{0xa7, 0xa8, 0x00, GDK_T},
	{0xba, 0x00, 0x00, GDK_y},
	{0xba, 0x00, 0x00, GDK_Y},
	{0xb4, 0xb5, 0x00, GDK_p},
	{0xb5, 0xb5, 0x00, GDK_P},
	{0xc3, 0xc2, 0x00, GDK_s},
	{0xc1, 0xc2, 0x00, GDK_S},
	{0xaf, 0xb0, 0xb3, GDK_d},
	{0xa9, 0xaa, 0xac, GDK_D},
	{0xc6, 0x00, 0x00, GDK_f},
	{0xc6, 0x00, 0x00, GDK_F},
	{0x9c, 0x9d, 0x9f, GDK_g},
	{0x9f, 0x9d, 0x00, GDK_G},
	{0xc4, 0x83, 0x00, GDK_h},
	{0xc4, 0x00, 0x00, GDK_H},
	{0xa2, 0xa3, 0xa6, GDK_j},
	{0xa3, 0xa3, 0xa6, GDK_J},
	{0x9a, 0x9b, 0x00, GDK_k},
	{0x9b, 0x9b, 0x00, GDK_K},
	{0xbd, 0x00, 0x00, GDK_l},
	{0xc5, 0x00, 0x00, GDK_L},
	{0x8f, 0x00, 0x00, GDK_z},
	{0x90, 0x00, 0x00, GDK_Z},
	{0x82, 0x00, 0x00, GDK_x},
	{0x9e, 0x00, 0x00, GDK_X},
	{0xa0, 0xa1, 0x00, GDK_c},
	{0xa1, 0xa1, 0x00, GDK_C},
	{0xc0, 0x00, 0x00, GDK_v},
	{0xc0, 0x00, 0x00, GDK_V},
	{0xb6, 0xb7, 0xb9, GDK_b},
	{0xb7, 0xb7, 0xb9, GDK_B},
	{0xb1, 0x00, 0x82, GDK_n},
	{0xab, 0x00, 0x9e, GDK_N},
	{0xb8, 0x00, 0x00, GDK_m},
	{0xb9, 0x00, 0x00, GDK_M},
	{0, 0, 0}
};

struct {
	unsigned char single0;
	unsigned char double0;
	unsigned char single1;
	unsigned char double1;
	int key;
} vowels[] = {
	{0x85, 0x86, 0xcf, 0xcf, GDK_a},
	{0x87, 0x88, 0xd0, 0xd1, GDK_A},
	{0x91, 0x92, 0xd9, 0xda, GDK_e},
	{0x91, 0x92, 0xd9, 0xda, GDK_E},
	{0x89, 0x8a, 0xd2, 0xd3, GDK_i},
	{0x93, 0x00, 0xdb, 0xdb, GDK_I},
	{0x94, 0x95, 0xdc, 0xdd, GDK_o},
	{0x96, 0x00, 0xde, 0xdf, GDK_O},
	{0x8b, 0x8c, 0xd4, 0xd6, GDK_u},
	{0x8d, 0x8e, 0xd8, 0xf2, GDK_U},
	{0, 0, 0, 0}
};

/* Checks TEXT to see if it starts with a Sinhala Unicode
 * character or a Joiner, and returns the 8 least significant
 * bits of the unicode value.
 *
 * If the returned value XX larger than or equal to 128, it represents
 * the Sinhala character 0x0DXX.
 *
 * If it returns a non-zero value YY smaller than 128, it represents the
 * joiner 0x20YY.  Only "known" joiners, ZWJ and ZWNJ, will return
 * non-zero.
 *
 * Returns 0 for other cases. */

static int
get_known_lsb_character(guchar *text)
{
	if (*text == 0xe0) {
		if (*++text == 0xb6) return *++text;
		if (*text == 0xb7) return *++text | 0x40;
	}
	if ((*text == 0xe2) && (*++text == 0x80)) {
		if (*++text == 0x8c) return 0x0c;
		if (*text == 0x8d) return 0x0d;
	}
	return 0;
}

/* Returns true if C is a consonent. */

int
is_consonent(int c)
{
	return (c >= 0x9a) && (c <= 0xc6) ? 1 : 0;
}

/* Search the consonent list to see if a key has a corresponding
 * entry. Returns the index in the list or -1 if not found. */

int
find_consonent_by_key(int k)
{
	int i = 0;

	while (consonents[i].character) {
		if (consonents[i].key == k) return i;
		i++;
	}
	return -1;
}

/* Search the consonent list to see if a character is in one
 * of its sublists.  Returns the index or -1 if not found. */

int
find_consonent(int c)
{
	int i = 0;

	while (consonents[i].character) {
		if ((consonents[i].character == c)
			|| (consonents[i].mahaprana == c)
			|| (consonents[i].sagngnaka == c))
				return i;
		i++;
	}
	return -1;
}

/* Search the vowel list to see if a key has a corresponding
 * entry. Returns the index in the list or -1 if not found. */

int
find_vowel_by_key(int k)
{
	int i = 0;

	while (vowels[i].single0) {
		if (vowels[i].key == k) return i;
		i++;
	}
	return -1;
}

/* Creates a UTF-8 sequence for a given LSB value.
 * IMPORTANT: the returned value must be free()ed. */

guchar *
create_unicode_character_from_lsb(int lsb)
{
	guchar *u = malloc(4);

	if (lsb >= 128) {
		u[0] = 0xe0;
		if (lsb < 192) {
			u[1] = 0xb6;
			u[2] = lsb;
		}
		else {
			u[1] = 0xb7;
			u[2] = (lsb & 0x3f) | 0x80;
		}
		u[3] = 0;
	}
	else if ((lsb == 0x0c) || (lsb == 0x0d)) {
		u[0] = 0xe2;
		u[1] = 0x80;
		u[2] = 0x80 | lsb;
		u[3] = 0;
	}
	else {
		strcpy(u, "");
	}

	return u;
}

static void
sinhala_phonetic_reset(GtkIMContext *context)
{
	//gtk_im_context_get_surrounding(context, &editing_text, &cursor_ptr);
	/* do we need to check editing_text for not NULL */
	//g_signal_emit_by_name(context, "preedit-changed");
}


/* FIXME : made this non-static to avoid a warning, change later */

void     
sinhala_phonetic_get_preedit_string(GtkIMContext *context,
                           gchar **str,
                           PangoAttrList **attrs,
                           gint *cursor_pos)
{
}

static gboolean
sinhala_phonetic_filter_keypress(GtkIMContext *context,
                        GdkEventKey  *event)
{
	int c, c1, l1;
	guchar *u = NULL;
	gchar *text;
	gint cursor, has_surroundings;

	if (event->type == GDK_KEY_RELEASE) return FALSE;

	if (event->state & (gtk_accelerator_get_default_mod_mask() & ~GDK_SHIFT_MASK))
		return FALSE;

	if (event->keyval) {
		has_surroundings = gtk_im_context_get_surrounding(context, &text, &cursor);

		c = find_consonent_by_key(event->keyval);
		if (c >= 0) {
			/* a consonent is pressed. */

			/* do modifiers first. */
			if (has_surroundings && (cursor >= 3)) {
				c1 = get_known_lsb_character(text + cursor - 3);
				l1 = find_consonent(c1);
				/* do modifiers only if there is a valid character before */
				if (l1 >= 0) {
					if (event->keyval == GDK_H) {
						if (consonents[l1].mahaprana) {
							gtk_im_context_delete_surrounding(context, -1, 1);
							u = create_unicode_character_from_lsb(consonents[l1].mahaprana);
          					g_signal_emit_by_name (context, "commit", u);
							free(u);
							free(text);
							return TRUE;
						}
					}
					else if (event->keyval == GDK_G) {
						if (consonents[l1].sagngnaka) {
							gtk_im_context_delete_surrounding(context, -1, 1);
							u = create_unicode_character_from_lsb(consonents[l1].sagngnaka);
          					g_signal_emit_by_name (context, "commit", u);
							free(u);
							free(text);
							return TRUE;
						}
					}
					else if (event->keyval == GDK_R) {
						/* rakaraanshaya */
						u = malloc(10);

						u[0] = 0xe0;
						u[1] = 0xb7;
						u[2] = 0x8a;

						u[3] = 0xe2;
						u[4] = 0x80;
						u[5] = 0x8d;

						u[6] = 0xe0;
						u[7] = 0xb6;
						u[8] = 0xbb;

						u[9] = 0;
       					g_signal_emit_by_name (context, "commit", u);

						free(u);
						free(text);
						return TRUE;
					}
					else if (event->keyval == GDK_Y) {
						/* yansaya */
						u = malloc(7);

						u[0] = 0xe0;
						u[1] = 0xb7;
						u[2] = 0x8a;

						u[3] = 0xe0;
						u[4] = 0xb6;
						u[5] = 0xba;

						u[6] = 0;
       					g_signal_emit_by_name (context, "commit", u);

						free(u);
						free(text);
						return TRUE;
					}
				}
			}

			u = create_unicode_character_from_lsb(consonents[c].character);
          	g_signal_emit_by_name (context, "commit", u);
			free(u);
			if (has_surroundings) free(text);
			return TRUE;
			/* end of consonent handling. */
		}

		c = find_vowel_by_key(event->keyval);
		if (c >= 0) {
			/* a vowel is pressed. */

			/* look for a previous character first. */
			u = NULL;
			if (has_surroundings && (cursor >= 3)) {
				c1 = get_known_lsb_character(text + cursor - 3);
				if (is_consonent(c1)) {
					u = create_unicode_character_from_lsb(vowels[c].single1);
				}
				else if (c1 == vowels[c].single0) {
					gtk_im_context_delete_surrounding(context, -1, 1);
					u = create_unicode_character_from_lsb(vowels[c].double0);
				}
				else if (c1 == vowels[c].single1) {
					gtk_im_context_delete_surrounding(context, -1, 1);
					u = create_unicode_character_from_lsb(vowels[c].double1);
				}
			}

			if (u == NULL)
				u = create_unicode_character_from_lsb(vowels[c].single0);

			g_signal_emit_by_name (context, "commit", u);

			free(u);
			if (has_surroundings) free(text);
			return TRUE;
			/* end of vowel handling. */
		}
		if (event->keyval < 128) {
			u = malloc(2);
			u[0] = event->keyval;
			u[1] = 0;
			g_signal_emit_by_name (context, "commit", u);
			free(u);
			if (has_surroundings) free(text);
			return TRUE;
		}
		if (event->keyval == GDK_BackSpace) {
		    gtk_im_context_delete_surrounding(context, -1, 1);
		    if (has_surroundings) free(text);
		    return TRUE;
		}
		if (has_surroundings) free(text);
	}

	return FALSE;
}

static void
sinhala_phonetic_class_init(GtkIMContextClass *clazz)
{
	clazz->filter_keypress = sinhala_phonetic_filter_keypress;
//	clazz->get_preedit_string = sinhala_phonetic_get_preedit_string;
	clazz->reset = sinhala_phonetic_reset;
}

void 
im_module_exit()
{
}

static void
sinhala_phonetic_init(GtkIMContext *im_context)
{
}

static void
sinhala_phonetic_register_type(GTypeModule *module)
{
	static const GTypeInfo object_info = {
		sizeof(GtkIMContextClass),
		(GBaseInitFunc)NULL,
		(GBaseFinalizeFunc)NULL,
		(GClassInitFunc)sinhala_phonetic_class_init,
		NULL,           /* class_finalize */
		NULL,           /* class_data */
		sizeof(GtkIMContext),
		0,
		(GInstanceInitFunc)sinhala_phonetic_init,
	};

	type_sinhala = 
		g_type_module_register_type(module, GTK_TYPE_IM_CONTEXT,
				"GtkIMContextSinhalaPhonetic", &object_info, 0);
}

static const
GtkIMContextInfo sinhala_phonetic_info = 
{
	"sinhala-phonetic",       /* ID */
	"Sinhala (phonetic)",   /* Human readable name */
	GETTEXT_PACKAGE, /* Translation domain */
	LOCALEDIR,       /* Dir for bindtextdomain */
	"si",            /* Languages for which this module is the default */
};

static const
GtkIMContextInfo *info_list[] = 
{
	&sinhala_phonetic_info,
};

void
im_module_init(GTypeModule *module)
{
	sinhala_phonetic_register_type(module);
}

void 
im_module_list(const GtkIMContextInfo ***contexts, gint *n_contexts)
{
	*contexts = info_list;
	*n_contexts = G_N_ELEMENTS(info_list);
}

GtkIMContext *
im_module_create(const gchar *context_id)
{
	if (strcmp(context_id, "sinhala-phonetic") == 0)
		return GTK_IM_CONTEXT(g_object_new(type_sinhala, NULL));
	else
		return NULL;
}

