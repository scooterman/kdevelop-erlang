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
#ifndef ERLANG_DEBUG_JOB_H_
#define ERLANG_DEBUG_JOB_H_

#include <QProcess>
#include <KUrl>

#include <outputview/outputjob.h>

class KProcess;
namespace KDevelop
{
class OutputModel;
class ILaunchConfiguration;
class ProcessLineMaker;
}

namespace ErlangDebugPlugin
{

class DebugSession;

class ErlangDebugJob : public KDevelop::OutputJob
{
Q_OBJECT
public:
    ErlangDebugJob( DebugSession* session, KDevelop::ILaunchConfiguration*, QObject* parent = 0 );
    virtual void start();
    
protected:
    virtual bool doKill();   

private slots:
    void processError(QProcess::ProcessError);
    void processFinished(int, QProcess::ExitStatus);
    
private:
    KDevelop::ILaunchConfiguration* m_launchConfig;
    
    KDevelop::OutputModel* model();
    KProcess* m_proc;
    QPointer<DebugSession> m_session;
};


}

#endif
