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

#include "variablecontroller.h"

#include <QXmlStreamReader>

#include <debugger/variable/variablecollection.h>
#include <debugger/breakpoint/breakpointmodel.h>
#include <interfaces/icore.h>
#include <interfaces/idebugcontroller.h>
#include <debugger/interfaces/iframestackmodel.h>

#include "debugsession.h"
#include "variable.h"
#include "stringhelpers.h"
#include "messages.h"
#include "variable.h"

namespace ErlangDebugPlugin {

VariableController::VariableController(DebugSession* parent)
    : KDevelop::IVariableController(parent) , m_currentVarList(0)
{
    Q_ASSERT(parent);    
    //connect(parent, SIGNAL(variableListUpdate(VariableListOutput*)), SLOT(handleLocals(VariableListOutput*)));
}

void VariableController::handleLocals(VariableListOutput* variableList)
{
  /*
  TODO: check with someone if there's a way to make this work
  
  m_currentVarList = new VariableListOutput(*variableList);
  
  QDomDocument& document = variableList->getDocument();
    
  QStringList updatable;
  
  QDomNodeList lst =  document.firstChildElement().elementsByTagName("variable");
  
  for (int i = 0; i < lst.size(); ++i)
  {
    updatable << lst.at(i).attributes().namedItem("name").nodeValue();
    kDebug() << "Updating: " << updatable;
    
    QList<KDevelop::Variable*> locals = KDevelop::ICore::self()->debugController()->variableCollection()->locals()->updateLocals(updatable);  
  
    Q_ASSERT(locals.size() == 1);
    static_cast<Variable*>(locals.at(0))->handleProperty(lst.at(i));    
    updatable.clear();
  }*/
}

DebugSession *VariableController::debugSession() const
{
    return static_cast<DebugSession*>(const_cast<QObject*>(QObject::parent()));
}

void VariableController::update()
{
  variableCollection()->watches()->reinstall();
}

QString VariableController::expressionUnderCursor(KTextEditor::Document* doc, const KTextEditor::Cursor& cursor)
{
    QString line = doc->line(cursor.line());
    int index = cursor.column();
    QChar c = line[index];
    if (!c.isLetterOrNumber() && c != '_' && c != '$')
        return QString();

    int start = Utils::expressionAt(line, index);
    int end = index;
    for (; end < line.size(); ++end) {
        QChar c = line[end];
        if (!(c.isLetterOrNumber() || c == '_' || c == '$'))
            break;
    }
    if (!(start < end))
        return QString();

    QString expression(line.mid(start, end-start));
    expression = expression.trimmed();
    return expression;
}


void VariableController::addWatch(KDevelop::Variable* variable)
{
    if (Variable *v = dynamic_cast<Variable*>(variable)) {
        variableCollection()->watches()->add(v->fullName());
    }
}

void VariableController::addWatchpoint(KDevelop::Variable* variable)
{
    if (Variable *v = dynamic_cast<Variable*>(variable)) {
        KDevelop::ICore::self()->debugController()->breakpointModel()->addWatchpoint(v->fullName());
    }
}

KDevelop::Variable* VariableController::
createVariable(KDevelop::TreeModel* model, KDevelop::TreeItem* parent,
               const QString& expression, const QString& display)
{
    return new Variable(model, parent, expression, display);
}

void VariableController::handleEvent(KDevelop::IDebugSession::event_t event)
{
    IVariableController::handleEvent(event);
}

}

#include "variablecontroller.moc"
