/****************************************************************************
** $Id$
**
** Implementation of QSinhalaTInputContext class
**
** Copyright (C) 2004 by Anuradha Ratnaweera.
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
#include <qlineedit.h>

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
	sinhalaInput = TRUE;
}

QSinhalaTInputContext::~QSinhalaTInputContext()
{
}

bool QSinhalaTInputContext::filterEvent(const QEvent *event)
{
	if (event->type() != QEvent::KeyPress)
		return FALSE;

	QKeyEvent *keyevent = (QKeyEvent *)event;

	int keyval = keyevent->key();
	if (isIgnoreKeys(keyval))
		return FALSE;

	if (keyval == Qt::Key_F12) {
		sinhalaInput = !sinhalaInput;
		return TRUE;
	}

	QString keytext = keyevent->text();
	if (keytext.length() < 1)
		return FALSE;

	int key = keytext[0].unicode();
	if (!sinhalaInput && (keyval < 128)) {
		commitChar(key);
		return TRUE;
	}

	QString text;
	int cursor;
	bool hasSurrounding = getSurrounding(&text, &cursor);

	if (hasSurrounding) qDebug("%s %d\n", text.ascii(), cursor);

	int c = findConsonentByKey(key);

	if (c >= 0) {
		if (hasSurrounding && (cursor >= 1)) {
			int c1 = getKnownLsbCharacter(text[cursor - 1].unicode());
			int l1 = findConsonent(c1);
			if (l1 >= 0) {
				if (key == 'w') {
					commitChar(0xdca);
					return TRUE;
				}
				if (key == 'W') {
					commitChar(0xdca);
					commitChar(0x200d);
					return TRUE;
				}
				if ((key == 'H') && (consonents[l1].mahaprana)) {
					deleteSurrounding(-1, 1);
					commitChar(lsbToUnicode(consonents[l1].mahaprana));
					return TRUE;
				}
				if ((key == 'G') && (consonents[l1].mahaprana)) {
					deleteSurrounding(-1, 1);
					commitChar(lsbToUnicode(consonents[l1].mahaprana));
					return TRUE;
				}
				if (key == 'R') {
					commitChar(0x0dca);
					commitChar(0x200d);
					commitChar(0x0dbb);
					return TRUE;
				}
				if (key == 'Y') {
					commitChar(0x0dca);
					commitChar(0x200d);
					commitChar(0x0dba);
					return TRUE;
				}
			}
		}

		commitChar(lsbToUnicode(consonents[c].character));
		return TRUE;
		// End of consonent handling
	}

	c = findVowelByKey(key);

	if (c >=0) {
		if (hasSurrounding && (cursor >= 1)) {
			int c1 = getKnownLsbCharacter(text[cursor - 1].unicode());
			if (isConsonent(c1)) {
				commitChar(lsbToUnicode(vowels[c].single1));
				return TRUE;
			}
			else if (c1 == vowels[c].single0) {
				deleteSurrounding(-1, 1);
				commitChar(lsbToUnicode(vowels[c].double0));
				return TRUE;
			}
			else if (c1 == vowels[c].single1) {
				deleteSurrounding(-1, 1);
				commitChar(lsbToUnicode(vowels[c].double1));
				return TRUE;
			}
		}
		commitChar(lsbToUnicode(vowels[c].single0));
		return TRUE;
	}

	return FALSE;
}

void QSinhalaTInputContext::setFocus()
{
}

void QSinhalaTInputContext::unsetFocus()
{
	reset();
}

void QSinhalaTInputContext::setMicroFocus(int x, int y, int w, int h, QFont *f)
{
}

void QSinhalaTInputContext::mouseHandler(int x, QEvent::Type type,
					 Qt::ButtonState button,
					 Qt::ButtonState state)
{
	switch (type) {
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	case QEvent::MouseButtonDblClick:
	case QEvent::MouseMove:
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

bool QSinhalaTInputContext::isIgnoreKeys(int keyval)
{
	for (uint i = 0; i < (sizeof(ignoreKeys)/sizeof(ignoreKeys[0])); i++)
		if (keyval == ignoreKeys[i])
			return TRUE;

	return FALSE;
}

void QSinhalaTInputContext::commitChar(uint c)
{
	sendIMEvent(QEvent::IMStart);
	sendIMEvent(QEvent::IMEnd, QString(QChar(c)));
}

int QSinhalaTInputContext::getKnownLsbCharacter(int c)
{
	if ((c >= 0xd80) && (c <= 0xdff))
		return c - 0xd80 + 128;
	if ((c == 0x200c) && (c == 0x200d))
		return c - 0x2000;
	return -1;
}

int QSinhalaTInputContext::isConsonent(int c)
{
	return (c >= 0x9a) && (c <= 0xc6) ? 1 : 0;
}

int QSinhalaTInputContext::findConsonentByKey(int k)
{
	int i = -1;
	while (consonents[++i].character)
		if (consonents[i].key == k)
			return i;
	return -1;
}

int QSinhalaTInputContext::findConsonent(int c)
{
	int i = -1;

	while (consonents[++i].character)
		if ((consonents[i].character == c)
				|| (consonents[i].mahaprana == c)
				|| (consonents[i].sagngnaka == c))
			return i;
	return -1;
}

int QSinhalaTInputContext::findVowelByKey(int k)
{
	int i = -1;

	while (vowels[++i].single0)
		if (vowels[i].key == k)
			return i;
	return -1;
}

int QSinhalaTInputContext::lsbToUnicode(int lsb)
{
	if (lsb >= 128)
		return 0x0D80 + (lsb - 128);
	if ((lsb == 0x0c) || (lsb == 0x0d))
		return 0x2000 + lsb;
	return 0;
}

