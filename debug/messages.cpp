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

#include "messages.h"
#include "kdebug.h"
#include <QXmlReader>
#include <QString>

namespace ErlangDebugPlugin
{
  
ErlangOutput::ErlangOutput(const QStringList& rawData, ErlangDebugPlugin::OutputCommandType command)
  : m_rawData(rawData) 
  , m_command(command)
{
}

OutputCommandType ErlangOutput::getCommandType()
{
  return m_command;
}

ErlangOutput::~ErlangOutput()
{
}

void BreakpointOutput::parse()
{
}

QString BreakpointOutput::getProcess()
{
  return m_rawData[3];
}
  
int BreakpointOutput::getLine()
{
  return m_rawData[2].toInt();
}

QString BreakpointOutput::getModule()
{
  return m_rawData[1];
}
  
ErlangCommand::ErlangCommand(QString meta, InterpreterCommand::InterpreterCommand command)
  : m_meta(meta)
,m_command(command)
{
}

QString MetaProcessOutput::getMeta()
{
  return m_rawData[2];
}

QString MetaProcessOutput::getProcess()
{
  return m_rawData[1];
}

void MetaProcessOutput::parse()
{
}

ErlangCommand::~ErlangCommand()
{
}

StepCommand::StepCommand(QString meta): ErlangCommand(meta, InterpreterCommand::STEP)
{
}

QString StepCommand::getCommand()
{
  return QString("{ action, step , \"%1\" }.").arg(m_meta);
}

ContinueCommand::ContinueCommand(QString meta) : 
  ErlangCommand(meta, InterpreterCommand::CONTINUE)
{
}

QString ContinueCommand::getCommand()
{
  return QString("{ action, continue , \"%1\" }.").arg(m_meta);
}

QString ProcessStatusUpdateOutput::getProcess()
{
  return m_rawData[1];
}

QString ProcessStatusUpdateOutput::getProcessAdditionalInfo()
{
  return m_rawData[3];
}

ErlangProcessStatus::status ProcessStatusUpdateOutput::getProcessStatus()
{
  if (m_rawData[2] == "running")
    return ErlangProcessStatus::Running;
  else if (m_rawData[2] == "exit")
    return ErlangProcessStatus::Exit;
  else
    return ErlangProcessStatus::Idle;
}

void ProcessStatusUpdateOutput::parse()
{
}

QList< StackInfo >& StackTraceOutput::getStackTrace()
{
  return m_stackTrace;
}

void StackTraceOutput::parse()
{
  m_process = m_rawData[1];

  QStringList frames = m_rawData[2].trimmed().split(" ");
  
  foreach(QString frame, frames)
  {
    QStringList frame_itens = frame.split(",");
    StackInfo info;
    
    info.stack_pos = frame_itens[0].toInt();
    info.function_name = frame_itens[1];
    info.filename = frame_itens[2];
    info.line = frame_itens[3].toInt() - 1;
    
    m_stackTrace.append(info);
  }  
}

QString& StackTraceOutput::getProcess()
{
  return m_process;
}

BreakCommand::BreakCommand(QString module, unsigned int line): 
  ErlangCommand("", InterpreterCommand::BREAK)
  ,m_module(module)
  ,m_line(line)
{
}

NextCommand::NextCommand(QString meta):
  ErlangCommand(meta, InterpreterCommand::NEXT)
{
}

QString NextCommand::getCommand()
{
  return QString("{ action, next, \"%1\" }.").arg(m_meta);
}

QString BreakCommand::getCommand()
{
  return QString("{ break, %1, %2 }.").arg(m_module).arg(m_line);
}


QDomDocument& VariableListOutput::getDocument()
{
  return m_document;
}

void VariableListOutput::parse()
{
  QString errorMsg;
  int errorLine;
  int errorColumn;
  
  if (!m_document.setContent(m_rawData[1], &errorMsg, &errorLine, &errorColumn))
  {
      kError() << "Error parsing variables list on line " << errorLine << " and column " << errorColumn << ": " << errorMsg;
  }
  
  //kDebug() << m_document.toString(2);  
}

FinishCommand::FinishCommand(QString meta): 
  ErlangCommand(meta, InterpreterCommand::FINISH)
{  
}

QString FinishCommand::getCommand()
{
  return QString("{ action, finish, \"%1\" }.").arg(m_meta);
}

QString InterpretModuleCommand::getCommand()
{
  return QString("{ interpret, %1 }.").arg(m_module);
}

InterpretModuleCommand::InterpretModuleCommand(QString moduleName)
  : ErlangCommand("", InterpreterCommand::INTERPRET)
  , m_module(moduleName)
{
}

QString VariablesInContextCommand::getCommand()
{
  return QString("{ var_list, \"%1\" }.").arg(m_meta);
}

VariablesInContextCommand::VariablesInContextCommand(QString meta)
  : ErlangCommand("",InterpreterCommand::VARIABLE_LIST) , m_meta(meta)
{
}

SpawnFunctionCommand::SpawnFunctionCommand(QString module, QString function, QString parameters)
  : ErlangCommand("", InterpreterCommand::SPAWN_FUNCTION)
  , m_module(module)
  , m_function(function)
  , m_parameters(parameters)
{
}

QString SpawnFunctionCommand::getCommand()
{
  return QString("{ launch , { %1 , %2, [ %3 ] } }.").arg(m_module).arg(m_function).arg(m_parameters);
}

QString RemoveBreakpoint::getCommand()
{
  return QString("{ break_remove, %1 , %2 }.").arg(m_module).arg(m_line);
}

RemoveBreakpoint::RemoveBreakpoint(QString module, unsigned int line)
: ErlangCommand("", InterpreterCommand::REMOVE_BREAKPOINT),
  m_module(module), 
  m_line(line)
{
}


}