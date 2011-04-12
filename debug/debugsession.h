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

#ifndef DEBUGSESSION_H
#define DEBUGSESSION_H

#include <debugger/interfaces/idebugsession.h>
#include <debugger/interfaces/iframestackmodel.h>

#include <interfaces/ilaunchconfiguration.h>

#include <kconfiggroup.h>

#include <QPointer>
#include <QQueue>

namespace ErlangDebugPlugin
{
class ErlangCommand;
class ErlangDebugger;
class ErlangDebugger;
class ErlangOutput;
class BreakpointOutput;
class VariableListOutput;
class StackTraceOutput;

static QString erlangShellExecPath = "Erlang ERTS Path";
static QString rebuildDebuggerInterface = "Rebuild erlang debugger interface prior staring";
static QString interpretedModules = "List of modules to be interpreted";
static QString projectDir = "Current project directory";
static QString libraryPaths = "Libraries folder to be added on debug runtime";
static QString callableFunction = "function to be called when debugging";
static QString callableModule = "module to be called when debugging";
static QString callableArguments = "function arguments to be called when debugging";

class DebugCallbackBase
{
public:
    virtual void execute(ErlangOutput&) = 0;
    
    virtual ~DebugCallbackBase() { }
};

class DebugSession : public KDevelop::IDebugSession
{
  Q_OBJECT
public:
    DebugSession();
    void requestVariables(DebugCallbackBase* callback);
    void startDebugger(KDevelop::ILaunchConfiguration* cfg);
    void sendBreakpoint(QString location, int line);
    void interpretMoule(QString module);
    void spawn(QString module, QString function, QString arguments); 
    void removeBreakpoint(QString module, int line);

Q_SIGNALS:
    void breakpointUpdate(BreakpointOutput*);
    void variableListUpdate(VariableListOutput*);
    void stackTraceUpdate(StackTraceOutput*);
    void stdoutReceived(QString data);
    
public Q_SLOTS:    
    ///called when user selects a different process (not thread) on our stack model
    virtual void updateCurrentActiveProcess(QString processID);
    
    
    virtual void stepOut();
    virtual void stepOverInstruction();
    virtual void stepInto();
    virtual void stepIntoInstruction();
    virtual void stepOver();
    virtual void jumpToCursor();
    virtual void runToCursor();
    virtual void run();
    virtual void interruptDebugger();
    virtual void stopDebugger();
    virtual void restartDebugger();
    virtual bool restartAvaliable() const;
    virtual KDevelop::IDebugSession::DebuggerState state() const;
     
private slots:
  
    void executeCmd();    
    void handleDebuggerCommand(ErlangOutput* command);
    
protected:
  virtual KDevelop::IFrameStackModel* createFrameStackModel();
   
private:
   QPointer<ErlangDebugger> m_erlDebugger;   
   QQueue<ErlangCommand*> m_commands;
   
   ///Stores information about metaprocesses and its relation to 
   ///real processes
   QMap<QString, QString> m_processToMeta;
   QMap<qlonglong, DebugCallbackBase* > m_callbacks;
   
   QList<QString> m_interpretedModules;
   
   QString m_currentProcess;
   
   qlonglong m_requestID;
};

}
#endif // DEBUGSESSION_H
