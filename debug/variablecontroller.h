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

#ifndef ERLANG_VARIABLECONTROLLER_H
#define ERLANG_VARIABLECONTROLLER_H

#include <debugger/interfaces/ivariablecontroller.h>

class QDomDocument;
namespace KDevelop {
class Locals;
}
namespace ErlangDebugPlugin {

class Variable;
class DebugSession;
class VariableListOutput;

class VariableController : public KDevelop::IVariableController
{
    Q_OBJECT

public:
    VariableController(DebugSession* parent);

    KDevelop::Variable* createVariable(KDevelop::TreeModel* model, KDevelop::TreeItem* parent,
                                     const QString& expression,
                                     const QString& display = "");
				     
    virtual QString expressionUnderCursor(KTextEditor::Document* doc, const KTextEditor::Cursor& cursor);
    virtual void addWatch(KDevelop::Variable* variable);
    virtual void addWatchpoint(KDevelop::Variable* variable);
    virtual void update();

private slots:    
    void handleLocals(VariableListOutput*);    
    
private:
    DebugSession* debugSession() const;    
    void handleEvent(KDevelop::IDebugSession::event_t event);
    VariableListOutput* m_currentVarList;
};

}

#endif // GDBDEBUGGER_VARIABLECONTROLLER_H
