/*
    Copyright (C) 2009 George Kiagiadakis <kiagiadakis.george@gmail.com>
    Copyright (C) 2011 Collabora Ltd.
      @author George Kiagiadakis <george.kiagiadakis@collabora.co.uk>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "call-handler.h"
#include "version.h"

#include <QIcon>

#include <KAboutData>
#include <KLocalizedString>

#include <TelepathyQt/Types>
#include <TelepathyQt/Debug>
#include <TelepathyQt/ClientRegistrar>
#include <TelepathyQt/CallChannel>
#include <TelepathyQt/ChannelClassSpec>
#include <TelepathyQt/ChannelFactory>

#include <KTp/telepathy-handler-application.h>

int main(int argc, char **argv)
{
    KTp::TelepathyHandlerApplication app(argc, argv);
    KAboutData aboutData("ktp-call-ui", i18n("KDE Telepathy Call Ui"),
                          KTP_CALL_UI_VERSION,
                          i18n("VoIP client for KDE"), KAboutLicense::GPL,
                          i18n("(C) 2009-2012, George Kiagiadakis\n"
                                "(C) 2010-2011, Collabora Ltd."));
    aboutData.addAuthor(i18nc("@info:credit", "George Kiagiadakis"), QString(),
                         "kiagiadakis.george@gmail.com");
    aboutData.setProductName("telepathy/call-ui"); //set the correct name for bug reporting
    KAboutData::setApplicationData(aboutData);
    app.setWindowIcon(QIcon::fromTheme("internet-telephony"));

    Tp::AccountFactoryPtr accountFactory = Tp::AccountFactory::create(
        QDBusConnection::sessionBus(),
        Tp::Features() << Tp::Account::FeatureCore
    );

    Tp::ConnectionFactoryPtr connectionFactory = Tp::ConnectionFactory::create(
        QDBusConnection::sessionBus(),
        Tp::Features() << Tp::Connection::FeatureCore
                       << Tp::Connection::FeatureSelfContact
    );

    Tp::ChannelFactoryPtr channelFactory = Tp::ChannelFactory::create(
        QDBusConnection::sessionBus()
    );
    channelFactory->addCommonFeatures(Tp::Channel::FeatureCore);
    channelFactory->addFeaturesForCalls(
        Tp::Features() << Tp::CallChannel::FeatureContents
                       << Tp::CallChannel::FeatureCallState
                       << Tp::CallChannel::FeatureCallMembers
                       << Tp::CallChannel::FeatureLocalHoldState
    );

    Tp::ContactFactoryPtr contactFactory = Tp::ContactFactory::create(
        Tp::Features() << Tp::Contact::FeatureAlias
                       << Tp::Contact::FeatureAvatarData
    );

    app.setQuitOnLastWindowClosed(true);

    Tp::ClientRegistrarPtr registrar =
        Tp::ClientRegistrar::create(accountFactory, connectionFactory,
                                    channelFactory, contactFactory);

    Tp::SharedPtr<CallHandler> callHandler(new CallHandler());
    registrar->registerClient(Tp::AbstractClientPtr::dynamicCast(callHandler), "KTp.CallUi");

    return app.exec();
}
