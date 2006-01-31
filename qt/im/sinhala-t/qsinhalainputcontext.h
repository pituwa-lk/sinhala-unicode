/****************************************************************************
** $Id$
**
** Definition of QSinhalaTInputContext class
**
** Copyright (C) 2004 by Anuradha Ratnaweera.
**
** This file is written to contribute to Trolltech AS under their own
** licence. You may use this file under your Qt license. Following
** description is copied from their original file headers. Contact
** sinhalat@linux.lk if any conditions of this licensing are not
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

#ifndef QSINHALATINPUT_CONTEXT_H
#define QSINHALATINPUT_CONTEXT_H

#include <qinputcontext.h>
#include <qnamespace.h>

#define QT_KEYSEQUENCE_MAX_LEN 6
#define UNITIZE(qkey) (0x02000000|qkey)

struct QComposeTableElement {
    uint keys[QT_KEYSEQUENCE_MAX_LEN];
    uint value;
};

struct QComposeTable {
    const QComposeTableElement *data;
    uint size;
};


class QSinhalaTInputContext : public QInputContext {
    Q_OBJECT
public:
    QSinhalaTInputContext();
    ~QSinhalaTInputContext();

    virtual QString identifierName();
    virtual QString language();

    virtual bool filterEvent(const QEvent *event);
    virtual void reset();
    virtual void setFocus();
    virtual void unsetFocus();
    virtual void setMicroFocus(int x, int y, int w, int h, QFont *f = 0);
    virtual void mouseHandler(int x, QEvent::Type type,
			       Qt::ButtonState button, Qt::ButtonState state);

protected:
    bool isIgnoreKeys(int keyval);
    bool isComposingKeys(int keyval);
//    bool checkComposeTable(uint composeBuffer[], const QComposeTable *composeTable);

    void commitChar(uint c);
	int getKnownLsbCharacter(int);
	int isConsonent(int);
	int findConsonentByKey(int);
	int findConsonent(int);
	int findVowelByKey(int);
	int lsbToUnicode(int);

private:
    bool sinhalaInput;
	bool shift_pressed;
	bool ctrl_pressed;
};

#endif // QSINHALATINPUT_CONTEXT_H
