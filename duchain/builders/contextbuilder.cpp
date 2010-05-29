/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2010 Victor Vicente de Carvalho                             *
 *   		      <victor.v.carvalho@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "contextbuilder.h"



#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classdeclaration.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>

#include <klocalizedstring.h>

#include "../../parser/parsesession.h"
#include "../../parser/editorintegrator.h"
#include "erlangast.h"

namespace erlang
{
  
ContextBuilder::ContextBuilder() : m_reportErrors(true)
{
}

ContextBuilder::~ContextBuilder()
{
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(erlang::AstNode* id)
{
  Atom1Ast* atom = 0;
  VariableAst* variable = 0;
  if (( atom = dynamic_cast<Atom1Ast*>(id)) != 0)
  {
    return KDevelop::QualifiedIdentifier(editor()->parseSession()->symbol(atom->literal));  
  }
  else if ((variable = dynamic_cast<VariableAst*>(id)) != 0)
  {
    return KDevelop::QualifiedIdentifier(editor()->parseSession()->symbol(variable->literal));  
  }
  else
  {
    return KDevelop::QualifiedIdentifier(); 
  }
}

KDevelop::ReferencedTopDUContext ContextBuilder::build(const KDevelop::IndexedString& url, AstNode* node,
        KDevelop::ReferencedTopDUContext updateContext, bool useSmart)
{
    if ( KDevelop::ICore::self() ) {
        m_reportErrors = KDevelop::ICore::self()->languageController()->completionSettings()->highlightSemanticProblems();
    }
    return ContextBuilderBase::build(url, node, updateContext, useSmart);
}
  
void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    ContextBuilderBase::setEditor(editor, false);
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(editor()->currentUrl());
        file->setLanguage(KDevelop::IndexedString("Erlang"));
    }
    return new KDevelop::TopDUContext(editor()->currentUrl(), range, file);
}

void ContextBuilder::setContextOnNode(AstNode* node, KDevelop::DUContext* ctx)
{
  if (node)
  {
    node->ducontext = ctx;
  }
}

KDevelop::DUContext* ContextBuilder::contextFromNode(erlang::AstNode* node)
{
  if (node)
  {
    return node->ducontext;
  }
}

EditorIntegrator* ContextBuilder::editor() const
{
    return static_cast<EditorIntegrator*>(ContextBuilderBase::editor());
}

KTextEditor::Range ContextBuilder::editorFindRange(AstNode* fromRange, AstNode* toRange)
{
    return editor()->findRange(fromRange, toRange).textRange();
}

KDevelop::SimpleCursor ContextBuilder::startPos(AstNode* node)
{
    return editor()->findPosition(node->startToken, KDevelop::EditorIntegrator::FrontEdge);
}

void ContextBuilder::startVisiting(AstNode* node)
{
  visitNode(node);
}

void ContextBuilder::visitFunctionOrRuleClause(FunctionOrRuleClauseAst* node)
{
  if (node->function_name)
  {
    openContext(node->clause_args, KDevelop::DUContext::Function, node->function_name);
    visitNode(node->clause_args);
    closeContext();
    visitNode(node->clause_guard);
    visitNode(node->rule_body);
    visitNode(node->body);    
  }
  else
  {
    DefaultVisitor::visitFunctionOrRuleClause(node);
  }
}

}
