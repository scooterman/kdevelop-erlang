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

#include "variable.h"
#include "debugsession.h"

#include <QXmlStreamReader>

#include <interfaces/icore.h>
#include <debugger/interfaces/ivariablecontroller.h>
#include <debugger/interfaces/iframestackmodel.h>
#include "messages.h"
#include "debugsession.h"

namespace ErlangDebugPlugin {

static bool hasStartedSession()
{
    KDevelop::IDebugSession *session = KDevelop::ICore::self()->debugController()->currentSession();
    if (!session)
        return false;

    KDevelop::IDebugSession::DebuggerState s = session->state();
    return s != KDevelop::IDebugSession::NotStartedState
        && s != KDevelop::IDebugSession::EndedState;
}

Variable::Variable(KDevelop::TreeModel* model, KDevelop::TreeItem* parent,
            const QString& expression, const QString& display)
: KDevelop::Variable(model, parent, expression, display)
{
}

Variable::~Variable()
{
}

class VariableListCallback : public DebugCallbackBase
{
public:
    VariableListCallback(Variable *variable, QObject *callback, const char *callbackMethod)
    : m_variable(variable), m_callback(callback), m_callbackMethod(callbackMethod)
    {}

    virtual void execute(ErlangOutput &output)
    {
	VariableListOutput* v_output = static_cast<VariableListOutput*>(&output);
	if (m_variable->handleProperty(*v_output))	
	{
	  QMetaObject::invokeMethod(m_callback, m_callbackMethod, Q_ARG(bool, true));
	}
    }
    
private:
    QPointer<Variable> m_variable;
    QObject *m_callback;
    const char *m_callbackMethod;
};

void Variable::attachMaybe(QObject *callback, const char *callbackMethod)
{
    if (hasStartedSession())
    {
        KDevelop::IDebugSession* is = KDevelop::ICore::self()->debugController()->currentSession();
        DebugSession* s = static_cast<DebugSession*>(is);
	s->requestVariables(new VariableListCallback(this, callback, callbackMethod));
    }
    
}

void Variable::fetchMoreChildren()
{
}

bool Variable::handleProperty(VariableListOutput &variableList)
{
    setInScope(true); 
    
    QDomDocument& document = variableList.getDocument();
    QDomNodeList lst = document.elementsByTagName("variable");
       
    for (int i = 0; i < lst.size(); ++i)
    {
      QDomNode nd = lst.at(i);
      if (nd.attributes().namedItem("name").nodeValue() == expression())
      {
	setValue(nd.firstChild().nodeValue());
	return true;
      }
    }	  
    
    return false;
}

QString Variable::fullName() const
{
    return m_fullName;
}


}
