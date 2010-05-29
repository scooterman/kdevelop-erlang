/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2010 Victor Vicente de Carvalho                             *
 *                             <victor.v.carvalho@gmail.com>               *
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

#include "declarationbuilder.h"

#include <interfaces/icore.h>
#include <language/duchain/functiondeclaration.h>

#include "erlangast.h"
#include "../../parser/parsesession.h"
#include "../../parser/editorintegrator.h"
#include "../declarations/functiondeclaration.h"
#include "../declarations/variabledeclaration.h"

using namespace KTextEditor;
using namespace KDevelop;
namespace erlang
{
DeclarationBuilder::DeclarationBuilder(EditorIntegrator* editor)
{
  setEditor(editor);
}
   
DeclarationBuilder::DeclarationBuilder()
{
}

void DeclarationBuilder::visitFunctionOrRuleClause(erlang::FunctionOrRuleClauseAst* node)
{
  if (node->function_name)
  {
    FunctionDeclaration* func = openDeclaration<FunctionDeclaration>(node->function_name, node->body);
    DeclarationBuilderBase::visitFunctionOrRuleClause(node);    
    closeDeclaration();
  }
  else
  {
    DefaultVisitor::visitFunctionOrRuleClause(node);
  }
}

void DeclarationBuilder::visitExprMax(ExprMaxAst* node)
{
  if (node->var)
  {
    SimpleRange range = editorFindRange(node->var, node->var);    
    VariableDeclaration *dec = openDeclaration<VariableDeclaration>(identifierForNode(node->var), range);
    dec->setKind(Declaration::Instance);
    eventuallyAssignInternalContext();
    closeDeclaration();
  }
  else
  {
    erlang::DefaultVisitor::visitExprMax(node);
  }
}

void DeclarationBuilder::startVisiting(AstNode* formAst)
{
  visitNode(formAst);
}
}