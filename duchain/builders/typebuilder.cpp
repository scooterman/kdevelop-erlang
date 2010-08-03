/*
* This file is part of KDevelop
*
* Copyright 2010 Victor Vicente de Carvalho
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU Library General Public License as
* published by the Free Software Foundation; either version 2 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#include "typebuilder.h"

#include <language/duchain/types/functiontype.h>
#include "../types/objecttype.h"

namespace erlang  {

TypeBuilder::TypeBuilder(): TypeBuilderBase()
{
}


void TypeBuilder::visitFunctionOrRuleClause(FunctionOrRuleClauseAst* node)
{
    KDevelop::FunctionType::Ptr functionType = KDevelop::FunctionType::Ptr(new KDevelop::FunctionType());
    openType(functionType);
    KDevelop::AbstractType::Ptr returnType(new ObjectType());
    functionType->setReturnType(returnType);

    TypeBuilderBase::visitFunctionOrRuleClause(node);

    updateCurrentType();
    closeType();

}

void TypeBuilder::visitArgExprs(ArgExprsAst* node)
{
    if (hasCurrentType())
    {
        KDevelop::DelayedType::Ptr type(new KDevelop::DelayedType());
        QString id = editor()->parseSession()->symbol(node);


        //We have  to prevent automatic parsing and splitting by QualifiedIdentifier and Identifier
        KDevelop::Identifier idd;
        idd.setIdentifier(id);

        KDevelop::QualifiedIdentifier ident;
        ident.push(idd);

        type->setIdentifier( KDevelop::IndexedTypeIdentifier(ident) );

        openType<KDevelop::DelayedType>(type);
        closeType();

        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        TypePtr<KDevelop::FunctionType> ctype = currentType<KDevelop::FunctionType>();
        ctype->addArgument(TypePtr<KDevelop::AbstractType>::staticCast(type));
    }
}

void TypeBuilder::updateCurrentType()
{
    //reimplemented in DeclarationBuilder
}

}
