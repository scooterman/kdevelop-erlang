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

void ErlangBreakpointOutput::parse()
{
}

QString ErlangBreakpointOutput::getProcess()
{
  return m_rawData[3];
}
  
int ErlangBreakpointOutput::getLine()
{
  return m_rawData[2].toInt();
}

QString ErlangBreakpointOutput::getModule()
{
  return m_rawData[1];
}
  
ErlangCommand::ErlangCommand(QString meta, InterpreterCommand command)
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

StepCommand::StepCommand(QString meta): ErlangCommand(meta, Step)
{
}

QString StepCommand::getCommand()
{
  return QString("{ action, step , \"%1\" }.").arg(m_meta);
}

ContinueCommand::ContinueCommand(QString meta) : 
  ErlangCommand(meta, Continue)
{
}

QString ContinueCommand::getCommand()
{
  return QString("{ action, continue , \"%1\" }.").arg(m_meta);
}

BreakCommand::BreakCommand(QString module, unsigned int line): 
  ErlangCommand("", Break)
  ,m_module(module)
  ,m_line(line)
{
}

NextCommand::NextCommand(QString meta):
  ErlangCommand(meta, Next)
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

void ErlangVariableListOutput::parse()
{
}

FinishCommand::FinishCommand(QString meta): 
  ErlangCommand(meta, Finish)
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
  : ErlangCommand("", Interpret)
  , m_module(moduleName)
{
}

QString VariablesInContextCommand::getCommand()
{
  return QString("{ var_list, \"%1\" }.").arg(m_meta);
}

VariablesInContextCommand::VariablesInContextCommand(QString meta)
  : ErlangCommand("",VariableList) , m_meta(meta)
{
}

SpawnFunctionCommand::SpawnFunctionCommand(QString module, QString function, QString parameters)
  : ErlangCommand("", SpawnFunction)
  , m_module(module)
  , m_function(function)
  , m_parameters(parameters)
{
}

QString SpawnFunctionCommand::getCommand()
{
  return QString("{ launch , { %1 , %2, [ %3 ] } }.").arg(m_module).arg(m_function).arg(m_parameters);
}

}