/****************************************************************************
** $Id$
**
** Implementation of QSinhalaTInputContext class
**
** Copyright (C) 2004 by Anuradha Ratnaweera
**
** This file is written to contribute to Trolltech AS under their own
** licence. You may use this file under your Qt license. Following
** description is copied from their original file headers. Contact
** sinhala@linux.lk if any conditions of this licensing are not
** clear to you.
**
**
** This file is part of the input method module of the Qt GUI Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid Qt Enterprise Edition or Qt Professional Edition
** licenses may use this file in accordance with the Qt Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#include "qsinhalainputcontext.h"

#include <qnamespace.h>
#include <qevent.h>
#include <qglobal.h>

static const int ignoreKeys[] = {
    Qt::Key_Shift,
    Qt::Key_Control,
    Qt::Key_Meta,
    Qt::Key_Alt,
    Qt::Key_CapsLock,
    Qt::Key_Super_L,
    Qt::Key_Super_R,
    Qt::Key_Hyper_L,
    Qt::Key_Hyper_R,
    Qt::Key_Mode_switch
};

struct {
	unsigned char character;
	unsigned char mahaprana;
	unsigned char sagngnaka;
	unsigned char key;
} consonents[] = {
	{0xa4, 0x00, 0x00, 'q'},
	{0xa5, 0x00, 0x00, 'Q'},
	{0xc0, 0x00, 0x00, 'w'},
	{0x0c, 0x00, 0x00, 'W'},
	{0xbb, 0x00, 0x00, 'r'},
	{0xbb, 0x00, 0x00, 'R'},
	{0xad, 0xae, 0x00, 't'},
	{0xa7, 0xa8, 0x00, 'T'},
	{0xba, 0x00, 0x00, 'y'},
	{0xba, 0x00, 0x00, 'Y'},
	{0xb4, 0xb5, 0x00, 'p'},
	{0xb5, 0xb5, 0x00, 'P'},
	{0xc3, 0xc2, 0x00, 's'},
	{0xc1, 0xc2, 0x00, 'S'},
	{0xaf, 0xb0, 0xb3, 'd'},
	{0xa9, 0xaa, 0xac, 'D'},
	{0xc6, 0x00, 0x00, 'f'},
	{0xc6, 0x00, 0x00, 'F'},
	{0x9c, 0x9d, 0x9f, 'g'},
	{0x9f, 0x9d, 0x00, 'G'},
	{0xc4, 0x83, 0x00, 'h'},
	{0xc4, 0x00, 0x00, 'H'},
	{0xa2, 0xa3, 0xa6, 'j'},
	{0xa3, 0xa3, 0xa6, 'J'},
	{0x9a, 0x9b, 0x00, 'k'},
	{0x9b, 0x9b, 0x00, 'K'},
	{0xbd, 0x00, 0x00, 'l'},
	{0xc5, 0x00, 0x00, 'L'},
	{0x8f, 0x00, 0x00, 'z'},
	{0x90, 0x00, 0x00, 'Z'},
	{0x82, 0x00, 0x00, 'x'},
	{0x9e, 0x00, 0x00, 'X'},
	{0xa0, 0xa1, 0x00, 'c'},
	{0xa1, 0xa1, 0x00, 'C'},
	{0xc0, 0x00, 0x00, 'v'},
	{0xc0, 0x00, 0x00, 'V'},
	{0xb6, 0xb7, 0xb9, 'b'},
	{0xb7, 0xb7, 0xb9, 'B'},
	{0xb1, 0x00, 0x82, 'n'},
	{0xab, 0x00, 0x9e, 'N'},
	{0xb8, 0x00, 0x00, 'm'},
	{0xb9, 0x00, 0x00, 'M'},
	{0, 0, 0, 0}
};

struct {
	unsigned char single0;
	unsigned char double0;
	unsigned char single1;
	unsigned char double1;
	unsigned char key;
} vowels[] = {
	{0x85, 0x86, 0xcf, 0xcf, 'a'},
	{0x87, 0x88, 0xd0, 0xd1, 'A'},
	{0x91, 0x92, 0xd9, 0xda, 'e'},
	{0x91, 0x92, 0xd9, 0xda, 'E'},
	{0x89, 0x8a, 0xd2, 0xd3, 'i'},
	{0x93, 0x00, 0xdb, 0xdb, 'I'},
	{0x94, 0x95, 0xdc, 0xdd, 'o'},
	{0x96, 0x00, 0xde, 0xdf, 'O'},
	{0x8b, 0x8c, 0xd4, 0xd6, 'u'},
	{0x8d, 0x8e, 0xd8, 0xf2, 'U'},
	{0, 0, 0, 0, 0}
};


QSinhalaTInputContext::QSinhalaTInputContext()
    : QInputContext()
{
}

QSinhalaTInputContext::~QSinhalaTInputContext()
{
}

bool QSinhalaTInputContext::filterEvent( const QEvent *event )
{
    if ( event->type() != QEvent::KeyPress )
        return FALSE;

    QKeyEvent *keyevent = (QKeyEvent *)event;
    int keyval = keyevent->key();
	QString text = keyevent->text();
    int val = 0;

    if ( isIgnoreKeys( keyval ) )
        return FALSE;

	qDebug( "%d %s\n", keyval, text.ascii() );

    return FALSE;
}

void QSinhalaTInputContext::setFocus()
{
    qDebug( "QSinhalaTInputContext: %p->setFocus(), focusWidget()=%p",
            this, focusWidget() );
}

void QSinhalaTInputContext::unsetFocus()
{
    qDebug( "QSinhalaTInputContext: %p->unsetFocus(), focusWidget()=%p",
            this, focusWidget() );
    reset();
}

void QSinhalaTInputContext::setMicroFocus( int x, int y, int w, int h, QFont *f )
{
}

void QSinhalaTInputContext::mouseHandler( int x, QEvent::Type type,
				     Qt::ButtonState button,
				     Qt::ButtonState state )
{
    switch ( type ) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseMove:
        qDebug( "QSinhalaTInputContext::mouseHandler: "
                "x=%d, type=%d, button=%d, state=%d", x, type, button, state );
        break;
    default:
        break;
    }
}


void QSinhalaTInputContext::reset()
{
    QInputContext::reset();
}

QString QSinhalaTInputContext::identifierName()
{
    return "sinhala-t";
}

QString QSinhalaTInputContext::language()
{
    return "si";
}

bool QSinhalaTInputContext::isIgnoreKeys( int keyval )
{
    for ( uint i = 0; i < (sizeof(ignoreKeys)/sizeof(ignoreKeys[0])); i++ )
        if ( keyval == ignoreKeys[i] )
            return TRUE;

    return FALSE;
}

void QSinhalaTInputContext::commitChar( uint c )
{
    sendIMEvent( QEvent::IMStart );
    sendIMEvent( QEvent::IMEnd, QString(QChar(c)) );
}

// Checks TEXT to see if it starts with a Sinhala Unicode character or a
// Joiner, and returns the 8 least significant bits of the unicode
// value.
//
// If the returned value XX larger than or equal to 128, it represents
// the Sinhala character 0x0DXX.
//
// If it returns a non-zero value YY smaller than 128, it represents the
// joiner 0x20YY.  Only "known" joiners, ZWJ and ZWNJ, will return
// non-zero.
//
// Returns 0 for other cases.

int QSinhalaTInputContext::getKnownLsbCharacter(unsigned char *text)
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

// Returns true if C is a consonent.

int QSinhalaTInputContext::isConsonent(int c)
{
	return (c >= 0x9a) && (c <= 0xc6) ? 1 : 0;
}

// Search the consonent list to see if a key has a corresponding
// entry. Returns the index in the list or -1 if not found.

int QSinhalaTInputContext::findConsonentByKey(int k)
{
	int i = 0;

	while (consonents[i].character) {
		if (consonents[i].key == k) return i;
		i++;
	}
	return -1;
}

// Search the consonent list to see if a character is in one
// of its sublists.  Returns the index or -1 if not found.

int QSinhalaTInputContext::findConsonent(int c)
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

// Search the vowel list to see if a key has a corresponding
// entry. Returns the index in the list or -1 if not found.

int QSinhalaTInputContext::findVowelByKey(int k)
{
	int i = 0;

	while (vowels[i].single0) {
		if (vowels[i].key == k) return i;
		i++;
	}
	return -1;
}

// Creates a UTF-8 sequence for a given LSB value.
// IMPORTANT: the returned value must be delete()ed.

unsigned char *QSinhalaTInputContext::createUnicodeCharacterFromLsb(int lsb)
{
	unsigned char *u = new unsigned char[4];

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
		u[0] = 0;
	}

	return u;
}

