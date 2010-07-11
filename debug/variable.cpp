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

namespace ErlangDebugPlugin
{

static bool hasStartedSession()
{
    KDevelop::IDebugSession *session = KDevelop::ICore::self()->debugController()->currentSession();
    if ( !session )
        return false;

    KDevelop::IDebugSession::DebuggerState s = session->state();
    return s != KDevelop::IDebugSession::NotStartedState
           && s != KDevelop::IDebugSession::EndedState;
}

Variable::Variable ( KDevelop::TreeModel* model, KDevelop::TreeItem* parent,
                     const QString& expression, const QString& display )
        : KDevelop::Variable ( model, parent, expression, display )
{
}

Variable::~Variable()
{
}

class VariableListCallback : public DebugCallbackBase
{
public:
    VariableListCallback ( Variable *variable, QObject *callback, const char *callbackMethod )
            : m_variable ( variable ), m_callback ( callback ), m_callbackMethod ( callbackMethod ) {}

    virtual void execute ( ErlangOutput &output )
    {
        if ( !m_variable )
            return;

        VariableListOutput* v_output = static_cast<VariableListOutput*> ( &output );

        QDomDocument doc = v_output->getDocument();
        QDomNodeList lst = doc.firstChild().childNodes();


        for ( int i = 0; i < lst.size(); ++i )
        {
            QDomNode node = lst.at ( i );
            if ( node.attributes().namedItem ( "name" ).nodeValue() == m_variable->expression() &&
                    m_variable->handleProperty ( node ) )
            {
                QMetaObject::invokeMethod ( m_callback, m_callbackMethod, Q_ARG ( bool, true ) );
                break;
            }
        }
    }

private:
    QPointer<Variable> m_variable;
    QObject *m_callback;
    const char *m_callbackMethod;
};

void Variable::attachMaybe ( QObject *callback, const char *callbackMethod )
{
    if ( hasStartedSession() )
    {
      KDevelop::IDebugSession* is = KDevelop::ICore::self()->debugController()->currentSession();
      DebugSession* s = static_cast<DebugSession*>(is);
      s->requestVariables(new VariableListCallback(this, callback, callbackMethod));
    }
}

void Variable::fetchMoreChildren()
{
}

bool Variable::handleProperty ( QDomNode variable )
{
    setInScope ( true );

    QDomNodeList lst = variable.childNodes();
    QString var_name;
    
    for ( int i = 0; i < lst.size(); ++i )
    {
        QDomNode node = lst.item ( i );
        QString node_name = node.nodeName();

        if ( node_name == "item" )
        {            
            QString data = node.firstChildElement ( "raw_value" ).firstChild().toCDATASection().data();

            Variable* v = new Variable ( model(), this, data);	    
            appendChild ( v, false );
            v->handleProperty ( node );
        }
        else if ( node_name == "value" )
        {
            QString data = node.firstChild().toCDATASection().data();

            if ( variable.attributes().contains ( "kind" ) )
            {
                Variable* v = new Variable ( model(), this, data );
                appendChild ( v, false );
	    }
	    else
	    {
	      setValue(data);
	    }
        }
    }

    return true;
}

QString Variable::fullName() const
{
    return m_fullName;
}


}
