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

#include "duchain.h"

#include <QtTest/QtTest>

#include <language/duchain/parsingenvironment.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>

QTEST_MAIN(erlang::TestDUChain)

namespace erlang
{

void TestDUChain::testDuchain()
{
  //                   012345678901234
  QByteArray function("myfunc() -> ok.");
  
  KDevelop::TopDUContext* top = parse(function, DumpAll); 
  KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
 
  QCOMPARE(top->childContexts().count(), 1);
  KDevelop::DUContext *dec = top->childContexts().at(0);
  QVERIFY(top->childContexts().first()->range() == KDevelop::SimpleRange(0, 0, 0, 5));
}
  
}