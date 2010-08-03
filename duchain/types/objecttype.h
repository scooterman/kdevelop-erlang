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
#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include <language/duchain/types/structuretype.h>

namespace erlang {

class ObjectTypeData: public KDevelop::StructureTypeData {
public:
    ObjectTypeData(): KDevelop::StructureTypeData() { }
    ObjectTypeData(const ObjectTypeData& rhs): KDevelop::StructureTypeData(rhs) { }
    void setPrettyName(QString arg1);
    QString m_prettyName;
};

class ObjectType: public KDevelop::StructureType {
public:
    typedef TypePtr<ObjectType> Ptr;

    /// Default constructor
    ObjectType();
    /// Copy constructor. \param rhs type to copy
    ObjectType(const ObjectType& rhs);
    /// Constructor using raw data. \param data internal data.
    ObjectType(ObjectTypeData& data);

    virtual AbstractType* clone() const;
    virtual QString toString() const;
    virtual uint hash() const;
    void setPrettyName(const QString& name);
    enum {
        Identity = 60
    };

    typedef ObjectTypeData Data;
    typedef KDevelop::StructureType BaseType;
    
protected:
    TYPE_DECLARE_DATA(ObjectType);
};

}

#endif
