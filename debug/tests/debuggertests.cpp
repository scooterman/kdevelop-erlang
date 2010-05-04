/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "debuggertests.h"
#include "../erlangdebugger.h"
#include "../debugsession.h"

#include <QApplication>

#include <KSharedConfig>
#include <kglobal.h>

#include <KDebug>
#include <KProcess>
#include <KConfig>
#include <qtest_kde.h>
#include <tests/testcore.h>
#include <tests/autotestshell.h>

#include <QTest>

QTEST_MAIN(DebuggerTests)

void DebuggerTests::debuggerIntegration()
{
  ErlangDebugPlugin::ErlangDebugger debugger;
  
  KConfigGroup grp(KGlobal::config(), "Erlang Debugger");  
  
  grp.writeEntry(ErlangDebugPlugin::erlangShellExecPath,"");
  grp.writeEntry(ErlangDebugPlugin::rebuildDebuggerInterface, true);
  
  debugger.start(grp);
  
  QApplication::exec();
}

DebuggerTests::DebuggerTests()
{

}

void DebuggerTests::initTestCase()
{
  KDevelop::AutoTestShell::init();
  m_core = new KDevelop::TestCore();
  m_core->initialize(KDevelop::Core::NoUi);
}


