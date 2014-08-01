/*
 * Copyright (C) 2014 Ekaitz Zárraga <ekaitz.zarraga@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <KDE/KStandardDirs>

#include <KLocalizedString>
#include "dtmf-qml.h"

struct DtmfQml::Private
{
    QDeclarativeView *view;
};

DtmfQml::DtmfQml(QWidget *parent)
: QMainWindow(parent), d(new Private)
{
    d->view = new QDeclarativeView(this);
    d->view->setSource(QUrl(KStandardDirs::locate("data", QLatin1String("ktp-call-ui/core/Dtmf.qml"))));
    d->view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setFixedSize(d->view->size());
    setWindowTitle( i18n("Dialpad"));
    setCentralWidget(d->view);
    connect(d->view->rootObject(), SIGNAL(release(QString)), this, SIGNAL(stopSendDtmfEvent()));
    connect(d->view->rootObject(), SIGNAL(press(QString)), this, SLOT(onButtonPressed(QString)));
}

DtmfQml::~DtmfQml()
{
    delete d;
}

void DtmfQml::onButtonPressed(QString digit)
{
    int code;
    if(digit=="#")
    {
        code=Tp::DTMFEventHash;
    }else if(digit=="*"){
        code=Tp::DTMFEventAsterisk;
    }
    else{
        code=digit.toInt();
    }
    Q_EMIT startSendDtmfEvent(static_cast<Tp::DTMFEvent>(code));
}
