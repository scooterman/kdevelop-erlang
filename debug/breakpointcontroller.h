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

#ifndef ERLANGBREAKPOINTCONTROLLER_H
#define ERLANGBREAKPOINTCONTROLLER_H

#include <debugger/interfaces/ibreakpointcontroller.h>
#include <debugger/interfaces/idebugsession.h>

namespace ErlangDebugPlugin
{
class DebugSession;
class ErlangBreakpointOutput;

class ErlangBreakpointController : public KDevelop::IBreakpointController 
{
  Q_OBJECT
public:
    ErlangBreakpointController(DebugSession* parent);

protected:
    virtual void sendMaybe(KDevelop::Breakpoint* breakpoint);

private slots:
    void stateChanged(KDevelop::IDebugSession::DebuggerState state);
    void hitBreakpoint(ErlangBreakpointOutput* breakpoint);
    
private:
    DebugSession *debugSession();
    QMap<KDevelop::Breakpoint*, QString> m_ids;
  
};

}
#endif // ERLANGBREAKPOINTCONTROLLER_H
