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

#ifndef KDEVERLANGLANGUAGESUPPORT_H
#define KDEVERLANGLANGUAGESUPPORT_H

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>
#include <QtCore/QVariant>
#include <QReadWriteLock>

#include <language/duchain/indexedstring.h>

namespace KDevelop
{
class IDocument;
class IProject;
class CodeHighlighting;
class ReferencedTopDUContext;
class ParseJob;
}


namespace erlang
{

class Highlighting;

class LanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::ILanguageSupport)

public:
    explicit LanguageSupport(QObject *parent, const QVariantList& args = QVariantList());
    
    virtual ~LanguageSupport()
    {
    }
    
    /*Name Of the Language*/
    QString name() const;
    /*Parsejob used by background parser to parse given Url*/
    KDevelop::ParseJob *createParseJob(const KUrl &url);

    static LanguageSupport* self();
    /*the code highlighter*/
    //const KDevelop::ICodeHighlighting* codeHighlighting() const;
private:
    static LanguageSupport* m_self;
};

}

#endif

