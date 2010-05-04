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

#ifndef ERLANGDEBUGPLUGIN_H
#define ERLANGDEBUGPLUGIN_H

#include <interfaces/iplugin.h>
#include <debugger/interfaces/idebugsession.h>

namespace ErlangDebugPlugin
{
class DebugSession;

class ErlangDebuggerPlugin : public KDevelop::IPlugin
{
  Q_OBJECT
public:
  ErlangDebuggerPlugin( QObject* parent, const QVariantList & = QVariantList() );
  ~ErlangDebuggerPlugin();
  
  DebugSession* createSession() const;  
};

}

#endif // ERLANGDEBUGPLUGIN_H
