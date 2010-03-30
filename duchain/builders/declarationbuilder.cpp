/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2008 Niko Sams <niko.sams@gmail.com>                        *
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

#include "declarationbuilder.h"

#include <interfaces/icore.h>
#include <language/duchain/functiondeclaration.h>

#include "erlangast.h"
#include "../../parser/parsesession.h"
#include "../../parser/editorintegrator.h"

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
   
void DeclarationBuilder::visitfunctionOrRuleClause(FunctionOrRuleClauseAst* node)
{
  if (node->function_name)
  {
    openContext(node->clause_args, KDevelop::DUContext::Function,node->function_name);
    visitNode(node->clause_args);
    visitNode(node->clause_guard);
    visitNode(node->rule_body);
    visitNode(node->body);    
  }
  else
  {
    DefaultVisitor::visitFunctionOrRuleClause(node);
  }
}

void DeclarationBuilder::startVisiting(AstNode* formAst)
{
  visitNode(formAst);
}
}