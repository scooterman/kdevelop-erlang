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


#include "debugjob.h"

#include <QFileInfo>
#include <QDesktopServices>

#include <KProcess>
#include <kconfiggroup.h>
#include <kicon.h>
#include <klocale.h>
#include <kshell.h>
#include <KMessageBox>
#include <KParts/MainWindow>

#include <outputview/outputmodel.h>
#include <interfaces/ilaunchconfiguration.h>
#include <util/environmentgrouplist.h>
#include <execute/iexecuteplugin.h>
#include <interfaces/iproject.h>
#include <project/interfaces/iprojectbuilder.h>
#include <project/builderjob.h>
#include <interfaces/iuicontroller.h>
#include <project/interfaces/ibuildsystemmanager.h>
#include <util/executecompositejob.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/icore.h>
#include <util/processlinemaker.h>

#include "debugsession.h"
#include "debugplugin.h"

#include <kdebug.h>

namespace ErlangDebugPlugin {

ErlangDebugJob::ErlangDebugJob( DebugSession* session, KDevelop::ILaunchConfiguration* cfg, QObject* parent)
    : m_proc(0), m_session(session), m_launchConfig(cfg)
{
    setCapabilities(Killable);

    connect(m_session, SIGNAL(stdoutReceived(QString)), SLOT(stdoutReceived(QString)));    
    
    setObjectName(cfg->name());
   

}

void ErlangDebugJob::start()
{
    setBehaviours(KDevelop::IOutputView::AllowUserClose | KDevelop::IOutputView::AutoScroll);    
    setStandardToolView(KDevelop::IOutputView::DebugView);
    setModel( new KDevelop::OutputModel(), KDevelop::IOutputView::TakeOwnership );
    
    KDevelop::EnvironmentGroupList l(KGlobal::config());
    IExecutePlugin * iface = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
    
    Q_ASSERT(iface); 
    QString err;
    QString envgrp = iface->environmentGroup( m_launchConfig );
    
    if( envgrp.isEmpty() )
    {
        kWarning() << i18n("No environment group specified, looks like a broken "
        "configuration, please check run configuration '%1'. "
        "Using default environment group.", m_launchConfig->name() );
        envgrp = l.defaultGroup();
    }
    
    QStringList arguments = iface->arguments( m_launchConfig, err );
    
    if( !err.isEmpty() )
    {
        setError( -1 );
        setErrorText( err );
    }
    
    if( error() != 0 )
    {
        emitResult();
        return;
    }
          
    startOutput();  
    
    m_session->startDebugger(m_launchConfig);
}

bool ErlangDebugJob::doKill()
{
    kDebug();
    if (m_session) m_session->stopDebugger();
    return true;
}

void ErlangDebugJob::processFinished( int exitCode , QProcess::ExitStatus status )
{
    emitResult();

    if (m_session) delete m_session;
}

void ErlangDebugJob::processError( QProcess::ProcessError error )
{
    if( error == QProcess::FailedToStart )
    {
        setError( -1 );
        QString errmsg =  i18n("Could not start program '%1'. Make sure that the "
                           "path is specified correctly.", m_proc->property("executable").toString() );
        KMessageBox::error( KDevelop::ICore::self()->uiController()->activeMainWindow(), errmsg, i18n("Could not start application") );
        setErrorText( errmsg );
        emitResult();
    }
    kDebug() << "Process error";

    if (m_session) delete m_session;
}

KDevelop::OutputModel* ErlangDebugJob::model()
{
    return dynamic_cast<KDevelop::OutputModel*>( KDevelop::OutputJob::model() );
}

void ErlangDebugJob::stdoutReceived(QString data)
{
    if (KDevelop::OutputModel* m = model()) {
        m->appendLine(data);
    }
}


}

#include "debugjob.moc"
