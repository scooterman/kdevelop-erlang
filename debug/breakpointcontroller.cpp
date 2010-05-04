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

#include "breakpointcontroller.h"

#include "debugsession.h"
#include <kdebug.h>
#include <debugger/breakpoint/breakpointmodel.h>
#include "messages.h"

namespace ErlangDebugPlugin
{
  
DebugSession* ErlangBreakpointController::debugSession()
{
  return static_cast<DebugSession*>(KDevelop::IBreakpointController::debugSession());
}

ErlangBreakpointController::ErlangBreakpointController(DebugSession* parent): IBreakpointController(parent)
{
    connect(parent, SIGNAL(stateChanged(KDevelop::IDebugSession::DebuggerState)),
                SLOT(stateChanged(KDevelop::IDebugSession::DebuggerState)));
		
    connect(parent, SIGNAL(breakpointUpdate(ErlangBreakpointOutput*)),
                SLOT(hitBreakpoint(ErlangBreakpointOutput*)));
}

void ErlangBreakpointController::sendMaybe(KDevelop::Breakpoint* breakpoint)
{
  if (breakpoint->kind() == KDevelop::Breakpoint::CodeBreakpoint && !m_ids.contains(breakpoint))
  {
    debugSession()->sendBreakpoint(breakpoint->url().fileName().split(".")[0], breakpoint->line());        
    m_ids[breakpoint] = breakpoint->url().path() + ":" +  QString::number(breakpoint->line());
  }
}

void ErlangBreakpointController::stateChanged(KDevelop::IDebugSession::DebuggerState state)
{
    kDebug() << state;
    if (state == KDevelop::IDebugSession::StartingState) {
        m_ids.clear();
        sendMaybeAll();
    }
}

void ErlangBreakpointController::hitBreakpoint(ErlangBreakpointOutput* breakpoint)
{
  QString id = breakpoint->getModule() + ":" +  QString::number(breakpoint->getLine());
  
  KDevelop::Breakpoint* b = m_ids.key(id);
  
  if (b)
  {
    b = breakpointModel()->addCodeBreakpoint(KUrl::fromPath(breakpoint->getModule()), breakpoint->getLine() - 1);
    hit(b);
  }
}
  
}