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

#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H

#include "contextbuilder.h"
#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <erlangast.h>
#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include "typebuilder.h"

namespace KDvelop
{
class Declaration;
}
namespace erlang
{
class ParseSession;
class EditorIntegrator;
class ClassDeclaration;
class FunctionDeclaration;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, AstNode, TypeBuilder > DeclarationBuilderBase;

class DeclarationBuilder : public DeclarationBuilderBase
{
public:
    DeclarationBuilder(EditorIntegrator* editor);
    DeclarationBuilder();
    
protected:
    virtual void visitExprMax(ExprMaxAst* node);
    virtual void visitFunctionOrRuleClause(erlang::FunctionOrRuleClauseAst* node);    
    
    virtual void updateCurrentType();
};

}

#endif // DECLARATIONBUILDER_H

