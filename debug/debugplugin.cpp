/*
    Erlang Debugger support for KDevelop
    Copyright (C) 2010  Victor Vicente de Carvalho

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/
#include "debugplugin.h"

#include <interfaces/icore.h>
#include <interfaces/idebugcontroller.h>
#include <kpluginfactory.h>
#include <klocalizedstring.h>
#include <kaboutdata.h>

#include <execute/iexecuteplugin.h>
#include <interfaces/launchconfigurationtype.h>
#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>

#include "debugsession.h"
#include "launchconfig.h"

namespace ErlangDebugPlugin
{
K_PLUGIN_FACTORY(ErlangDebuggerFactory, registerPlugin<ErlangDebuggerPlugin>(); )
K_EXPORT_PLUGIN(ErlangDebuggerFactory(KAboutData("kdeverldebug","kdeverldebug", ki18n("Erlang debug support"), "0.1", ki18n("Support for debugging erlang apps"), KAboutData::License_GPL)))


ErlangDebuggerPlugin::ErlangDebuggerPlugin(QObject* parent, const QVariantList& ): IPlugin(ErlangDebuggerFactory::componentData(), parent )
{
    {
        IExecutePlugin* iface = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
        Q_ASSERT(iface);
        KDevelop::LaunchConfigurationType* type = core()->runController()->launchConfigurationTypeForId( iface->nativeAppConfigTypeId() );
        Q_ASSERT(type);
        type->addLauncher( new ErlangLauncher( this ) );
    }
}

DebugSession* ErlangDebuggerPlugin::createSession() const
{
    DebugSession *session = new DebugSession();
    KDevelop::ICore::self()->debugController()->addSession(session);
    connect(session, SIGNAL(showMessage(QString,int)), SLOT(controllerMessage(QString,int)));
    connect(session, SIGNAL(reset()), SIGNAL(reset()));
    connect(session, SIGNAL(finished()), SLOT(slotFinished()));
    connect(session, SIGNAL(raiseOutputViews()), SIGNAL(raiseOutputViews()));
    connect(session, SIGNAL(raiseVariableViews()), SIGNAL(raiseVariableViews()));
    return session;
}

ErlangDebuggerPlugin::~ErlangDebuggerPlugin()
{

}

}
