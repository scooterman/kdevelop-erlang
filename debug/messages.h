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

#ifndef ERLANGCOMMAND_H
#define ERLANGCOMMAND_H

#include <QString>
#include <QStringList>
#include <QDomDocument>

namespace ErlangDebugPlugin
{

namespace InterpreterCommand
{
enum InterpreterCommand
{
  BREAK,
  CONDITIONAL_BREAK,
  CONTINUE,
  STEP,
  NEXT,
  FINISH,
  INTERPRET,
  VARIABLE_LIST,
  SPAWN_FUNCTION,
  REMOVE_BREAKPOINT
};

}

enum OutputCommandType
{
  VariableListOutputType,
  BreakpointOutputType,
  MetaOutputType,
  ProcessStatusUpdateType,
  StackTraceOutputType
};

namespace ErlangProcessStatus
{
enum status
{
  Running,
  Idle,
  Exit
};

}

class ErlangOutput
{
public:
  ErlangOutput(const QStringList& rawData, OutputCommandType command);
  virtual void parse() = 0;
  
  OutputCommandType getCommandType();
  
  virtual ~ErlangOutput();
protected:
  QStringList m_rawData;
  OutputCommandType m_command;
};

class VariableListOutput : public ErlangOutput
{      
  public:
    VariableListOutput(const QStringList& rawData) 
    : ErlangOutput(rawData, VariableListOutputType)
    { 
    } 
    void parse();
    
    QDomDocument& getDocument();    
  
  protected:
    QDomDocument m_document;
};

struct StackInfo
{
  QString function_name;
  QString filename;
  int line;
  int stack_pos;
};

class StackTraceOutput : public ErlangOutput
{      
  public:
    StackTraceOutput(const QStringList& rawData) 
    : ErlangOutput(rawData, StackTraceOutputType)
    { 
    } 
    void parse();
    
    QList<StackInfo>& getStackTrace();    
    QString& getProcess();
  protected:
    QString m_process;
    QList<StackInfo> m_stackTrace;
};

class MetaProcessOutput : public ErlangOutput
{
  public:
     MetaProcessOutput(const QStringList& rawData) 
    : ErlangOutput(rawData, MetaOutputType) 
    { 
    } 
    
    void parse();
    QString getProcess();
    QString getMeta();
};

class BreakpointOutput : public ErlangOutput
{
public:
  BreakpointOutput(const QStringList& rawData)
    : ErlangOutput(rawData, BreakpointOutputType)
  {
  }
  
  void parse();
  QString getModule();
  int getLine();
  QString getProcess();  
};

class ProcessStatusUpdateOutput : public ErlangOutput
{
public:
     ProcessStatusUpdateOutput(const QStringList& rawData)
    : ErlangOutput(rawData, ProcessStatusUpdateType)
  {
  }
  
  void parse();
  QString getProcess();
  ErlangProcessStatus::status getProcessStatus();
  QString getProcessAdditionalInfo();
};

class ErlangCommand
{
public:
  ErlangCommand(QString meta, InterpreterCommand::InterpreterCommand command);  
  virtual QString getCommand() = 0;
  virtual ~ErlangCommand();
protected:
  QString m_meta;
  InterpreterCommand::InterpreterCommand m_command;
};

class StepCommand : public ErlangCommand
{
public:
  StepCommand(QString meta);
  
  virtual QString getCommand(); 
};

class ContinueCommand : public ErlangCommand
{
public:
  ContinueCommand(QString meta);  
  virtual QString getCommand();
};

class NextCommand : public ErlangCommand
{
public:
  NextCommand (QString meta);  
  virtual QString getCommand();
};

class FinishCommand : public ErlangCommand
{
public:
  FinishCommand (QString meta);  
  virtual QString getCommand();
};

class InterpretModuleCommand : public ErlangCommand
{
public:
    InterpretModuleCommand (QString moduleName);   
    virtual QString getCommand();
protected:
    QString m_module;
};


class SpawnFunctionCommand : public ErlangCommand
{
public:
  SpawnFunctionCommand(QString module, QString function, QString parameters);
  virtual QString getCommand();
protected:
  QString m_function;
  QString m_module;
  QString m_parameters;
};

class VariablesInContextCommand : public ErlangCommand
{
public:
    VariablesInContextCommand (QString meta);   
    virtual QString getCommand();
    
protected:
    QString m_meta;  
};

class RemoveBreakpoint : public ErlangCommand
{
public:
  RemoveBreakpoint(QString module, unsigned int line);
  virtual QString getCommand();
protected:
      unsigned int m_line;
  QString m_module;
};

class BreakCommand : public ErlangCommand
{
public:
  BreakCommand(QString module, unsigned int line);
  virtual QString getCommand();
protected:  
  QString m_module;
  unsigned int m_line;
};

}

#endif // ERLANGCOMMAND_H
