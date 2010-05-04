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

#include "debugsession.h"

#include "debugger.h"
#include "messages.h"
#include "breakpointcontroller.h"
#include "variablecontroller.h"
#include "framestackmodel.h"

#include <kdebug.h>

#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>
#include <execute/iexecuteplugin.h>
#include <QFileInfo>

namespace ErlangDebugPlugin
{

KDevelop::IFrameStackModel* DebugSession::createFrameStackModel()
{
    return new FrameStackModel(this);
}

void DebugSession::requestVariables(ErlangDebugPlugin::DebugCallbackBase* callback)
{
    m_callbacks.insert(m_requestID++, callback);
    m_commands.enqueue(new VariablesInContextCommand(m_processToMeta[m_currentProcess]));
    executeCmd();
}

void DebugSession::interpretMoule(QString module)
{
    if (!m_interpretedModules.contains(module))
    {
    m_interpretedModules.append(module);
    m_commands.enqueue(new InterpretModuleCommand(module));
    executeCmd();
    }
}

void DebugSession::spawn(QString module, QString function, QString arguments)
{
    m_commands.enqueue(new SpawnFunctionCommand(module,function, arguments));
    executeCmd();
}

void DebugSession::startDebugger(KDevelop::ILaunchConfiguration* config)
{
    IExecutePlugin* iface = KDevelop::ICore::self()->pluginController()->pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
    Q_ASSERT(iface);

    // Only dummy err here, actual erros have been checked already in the job and we don't get here if there were any
    QString err;
    QString executable = iface->executable(config, err).toLocalFile();
    QString envgrp = iface->environmentGroup(config);

    QStringList arguments = iface->arguments(config, err);
    // Change the "Working directory" to the correct one
    QString dir = iface->workingDirectory(config).toLocalFile();
    if (dir.isEmpty() || !KUrl(dir).isValid())
    {
        dir = QFileInfo(executable).absolutePath();
    }
  
    kDebug() << "current directory is: " << dir;
        
    m_erlDebugger = new ErlangDebugger();   
    
    connect(m_erlDebugger, SIGNAL(outputCommand(ErlangOutput*)), this, SLOT(handleDebuggerCommand(ErlangOutput*)));
    
    
    m_erlDebugger->start(config->config());

    QStringList to_be_interpreted = config->config().readEntry(interpretedModules,QStringList());

    kDebug() << "interpreted modules: " << to_be_interpreted;

    foreach(QString module, to_be_interpreted)
    {
        interpretMoule(module);
    }
    
    QString module = config->config().readEntry(callableModule,"");
    QString function = config->config().readEntry(callableFunction,"");
    QString functionArguments = config->config().readEntry(callableArguments,"");
    
    spawn(module, function, functionArguments);   
}

void DebugSession::stepOut()
{
    m_commands.enqueue(new FinishCommand(m_processToMeta[m_currentProcess]));
    executeCmd();
}

void DebugSession::updateCurrentActiveProcess(QString processID)
{
    m_currentProcess = processID;
}

void DebugSession::stepOverInstruction()
{
}

DebugSession::DebugSession() : m_requestID(0)
{
    m_breakpointController = new ErlangBreakpointController(this);
    m_variableController = new VariableController(this);       
}

void DebugSession::sendBreakpoint(QString location, int line)
{
    if (!m_interpretedModules.contains(location))
    {
        m_commands.enqueue(new InterpretModuleCommand(location));
        m_interpretedModules.append(location);
	executeCmd();
    }

    m_commands.enqueue(new BreakCommand(location, line));
    executeCmd();
}

void DebugSession::stepInto()
{
    m_commands.enqueue(new StepCommand(m_processToMeta[m_currentProcess]));
    executeCmd();
}

void DebugSession::stepIntoInstruction()
{

}

void DebugSession::stepOver()
{
    m_commands.enqueue(new NextCommand(m_processToMeta[m_currentProcess]));
    executeCmd();
}

void DebugSession::jumpToCursor()
{

}

void DebugSession::runToCursor()
{

}

void DebugSession::run()
{
    m_commands.enqueue(new ContinueCommand(m_processToMeta[m_currentProcess]));
    executeCmd();
}

void DebugSession::interruptDebugger()
{

}

void DebugSession::stopDebugger()
{
    if (m_erlDebugger)
    {
        m_erlDebugger->stop();
    }
    
    emit finished();
}

void DebugSession::restartDebugger()
{

}

bool DebugSession::restartAvaliable() const
{
    return false;
}

KDevelop::IDebugSession::DebuggerState DebugSession::state() const
{
    return KDevelop::IDebugSession::ActiveState;
}

void DebugSession::executeCmd()
{
    m_erlDebugger->execute(m_commands.dequeue());
}

void DebugSession::handleDebuggerCommand(ErlangOutput* command)
{
  switch (command->getCommandType())
  {
    case BreakpointOutputType:
      {
	ErlangBreakpointOutput* i_cmd = static_cast<ErlangBreakpointOutput*>(command);     
	
	m_currentProcess = i_cmd->getProcess();
	
	emit breakpointUpdate(i_cmd);      
	emit showStepInSource(KUrl::fromPath(i_cmd->getModule()), i_cmd->getLine() - 1); 
      
	emit stateChanged(KDevelop::IDebugSession::PausedState);
      }
      break;    
    case MetaOutputType:
      {
	MetaProcessOutput* i_cmd = static_cast<MetaProcessOutput*>(command);
	m_processToMeta[i_cmd->getProcess()] = i_cmd->getMeta();
      }
      break;
  }
}

}
