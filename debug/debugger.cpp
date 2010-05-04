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

#include "debugger.h"

#include "debugsession.h"
#include "kdebug.h"
#include <kstandarddirs.h>

namespace ErlangDebugPlugin
{

void ErlangDebugger::start(const KConfigGroup& config)
{
    KUrl erlangdebuggerUrl = config.readEntry(ErlangDebugPlugin::erlangShellExecPath, KUrl());
    if (erlangdebuggerUrl.isEmpty()) {
        m_erlShellBinary = "/usr/bin/erl";
    } else {
        // FIXME: verify its' a local path.
        m_erlShellBinary = erlangdebuggerUrl.toLocalFile(KUrl::RemoveTrailingSlash);
    }

    m_erlShellProcess = new KProcess(this);

    m_erlShellProcess->setOutputChannelMode( KProcess::SeparateChannels );
    connect(m_erlShellProcess, SIGNAL(readyReadStandardOutput()),
            SLOT(readyReadStandardOutput()));
    
    connect(m_erlShellProcess, SIGNAL(readyReadStandardError()),
            SLOT(readyReadStandardError()));
	    
    connect(m_erlShellProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            SLOT(processFinished(int, QProcess::ExitStatus)));
	    
    connect(m_erlShellProcess, SIGNAL(error(QProcess::ProcessError)),
            SLOT(processErrored(QProcess::ProcessError)));

    QString debuggerInterpreterBeamPath = KStandardDirs::locateLocal("data", "kdevelop/debug_interpreter.beam");
    QString debuggerInterpreterFolder = KStandardDirs::locateLocal("data", "kdevelop/");
    Q_ASSERT(KStandardDirs::exists(debuggerInterpreterFolder));

    //if we dont have the precompiled beam, invoke erlc to build it
    if (!KStandardDirs::exists(debuggerInterpreterBeamPath) ||
            (config.hasKey(rebuildDebuggerInterface) && config.readEntry(rebuildDebuggerInterface, false)))
    {
        kDebug() << "Trying to build debugger interpreter source... ";

        QString debuggerInterpreterErlPath = KStandardDirs::locate("data", "kdeverlangsupport/debug_interpreter.erl");

        Q_ASSERT(KStandardDirs::exists(debuggerInterpreterErlPath));

        KProcess erlcProcess;
        erlcProcess << "/usr/bin/erlc" << "-o" << debuggerInterpreterFolder << debuggerInterpreterErlPath ;
        erlcProcess.execute();
        erlcProcess.waitForFinished();

        kDebug() << "process exit code: " << erlcProcess.exitCode();

        kDebug() << "erlc stdout: " << erlcProcess.readAll();
        kDebug() << "erlc stderr: " << erlcProcess.readAllStandardError();
    }
    
    
    //Passing as ERL_FLAGS since somehow the KProcess isn't providing them to the erlang shell
    QStringList arguments;
    arguments << "-noshell" << "-eval \"debug_interpreter:start()\"" << "-pa" <<  debuggerInterpreterFolder;
    
    QStringList libraryIncludePaths = config.readEntry(ErlangDebugPlugin::libraryPaths, QStringList());
    
    foreach(QString path, libraryIncludePaths)
    {
	arguments << "-pa" << path;    
    }
       
    kDebug() << "ERL_FLAGS are: " << arguments.join(" ");
    
    m_erlShellProcess->setEnv("ERL_FLAGS", arguments.join(" "), true);    
    
    m_erlShellProcess->setProgram(m_erlShellBinary);
    m_erlShellProcess->start();

    kDebug() << "Erlang shell PID is: " << m_erlShellProcess->pid();
    kDebug() << "STARTING ERLANG SHELL\n";
}

void ErlangDebugger::processErrored(QProcess::ProcessError )
{
    kDebug() << "erlang shell process error: " << m_erlShellProcess->readAllStandardError();
}

void ErlangDebugger::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    kDebug() << "erlang shell process finished: " << ((exitCode == 0) ?  m_erlShellProcess->readAllStandardOutput() :  m_erlShellProcess->readAllStandardError());
}

void ErlangDebugger::readyReadStandardError()
{
    kDebug() << "erlang shell process error: " << m_erlShellProcess->readAllStandardError();
}

void ErlangDebugger::readyReadStandardOutput()
{
    m_erlShellProcess->setReadChannel(QProcess::StandardOutput);
    m_buffer += m_erlShellProcess->readAll();
    
    for (;;)
    {
        int i = m_buffer.indexOf('\n');
        if (i == -1)
            break;

        QByteArray reply(m_buffer.left(i));
        m_buffer = m_buffer.mid(i+1);

        processLine(reply);
    }
}

void ErlangDebugger::execute(ErlangCommand* command)
{
  QString cmdStr = command->getCommand();
  
  kDebug() << "Sending command to erlang process: " << cmdStr;  
  m_erlShellProcess->write(cmdStr.toLatin1(), cmdStr.size());
  m_erlShellProcess->write("\n");
  
  delete command;
}

void ErlangDebugger::processLine(QByteArray data)
{
  if (data.contains("---"))
  {
    kDebug() << "Debug information from erlang debugger process: " << data;
  }
  else if (data.length() > 1 && data[0] == '\001')
  { 
    kDebug() << "Received command: " << data;
    
    data.remove(0,1);
    QString command(data);
    
    QStringList items = command.split("|");
    
    //todo: shared ptrs?
    ErlangOutput* output = 0;
    
    if (items[0] == "break")
    {
      output = new ErlangBreakpointOutput(items);
      
    }
    else if (items[0] == "meta")
    {
      output = new  MetaProcessOutput(items);
    }    
    
    if (output)
    {
      output->parse(); 
      emit outputCommand(output);
    }
    
    delete output;    
  }
}

void ErlangDebugger::stop()
{
  m_erlShellProcess->kill();
}

}
