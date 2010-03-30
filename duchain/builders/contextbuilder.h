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

#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include "erlangdefaultvisitor.h"
#include <language/duchain/builders/abstractcontextbuilder.h>
#include <parser/editorintegrator.h>

namespace erlang
{
class EditorIntegrator;
class ParseSession;

typedef KDevelop::AbstractContextBuilder<AstNode, Atom1Ast> ContextBuilderBase;

class ContextBuilder : public ContextBuilderBase, public DefaultVisitor
{
  public:

  ContextBuilder();
    virtual ~ContextBuilder();

    void setEditor(EditorIntegrator* editor);
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AstNode* node,
            KDevelop::ReferencedTopDUContext updateContext
            = KDevelop::ReferencedTopDUContext(), bool useSmart = true);

  protected:
    EditorIntegrator* editor() const;

    void visitFunctionOrRuleClause(erlang::FunctionOrRuleClauseAst* node);
    void startVisiting(AstNode* node);
    
    virtual KDevelop::QualifiedIdentifier identifierForNode(Atom1Ast* id);
    
    virtual KDevelop::TopDUContext* newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file = 0);

    virtual void setContextOnNode(AstNode* node, KDevelop::DUContext* ctx);
    virtual KDevelop::DUContext* contextFromNode(AstNode* node);
    virtual KTextEditor::Range editorFindRange(AstNode* fromRange, AstNode* toRange);
    /// Find Cursor for start of a node, useful to limit findLocalDeclarations() searches.
    KDevelop::SimpleCursor startPos(AstNode* node);

    /// Whether semantic problems should get reported
    bool m_reportErrors;
};

}
#endif // CONTEXTBUILDER_H
