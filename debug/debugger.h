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

#ifndef ERLANGDEBUGGER_H
#define ERLANGDEBUGGER_H

#include <kconfiggroup.h>
#include <QString>
#include <kprocess.h>
#include "messages.h"

namespace ErlangDebugPlugin
{
class ErlangCommand;

class ErlangDebugger : public QObject
{
  Q_OBJECT
public:
  
  void start(const KConfigGroup& config);  
  void execute(ErlangCommand* command);
  void stop();

signals:
  void outputCommand(ErlangOutput* ouput);
  
protected:
  QString m_erlShellBinary;
  KProcess* m_erlShellProcess;
  QByteArray m_buffer;
  
  void processLine(QByteArray data);
  
private Q_SLOTS:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processErrored(QProcess::ProcessError);
    
};

}

#endif // ERLANGDEBUGGER_H
