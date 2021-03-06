/*****************************************************************************
 * Copyright (c) 2010 Victor Vicente de Carvalho                             *
 *              <victor.v.carvalho@gmail.com>                                *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/

#ifndef ERLANG_PARSEJOB_H
#define ERLANG_PARSEJOB_H

#include <language/backgroundparser/parsejob.h>

// from the parser subdirectory
#include "erlangast.h"

#include <QStringList>

#include <ksharedptr.h>
#include <ktexteditor/range.h>

namespace erlang
{

class AstNode;
class LanguageSupport;
class EditorIntegrator;

class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    explicit ParseJob(const KUrl &url);
    virtual ~ParseJob();

    LanguageSupport* erlang() const;

protected:
    virtual void run();

};
}

#endif
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
