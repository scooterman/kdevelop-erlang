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

#include "erlanglanguagesupport.h"

#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <kaboutdata.h>
#include <KTextEditor/Document>

#include <language/codecompletion/codecompletion.h>
#include <interfaces/idocument.h>
#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

//#include "completion/model.h"
#include "parsejob.h"
//#include "navigation/navigationwidget.h"
#include "parser/parsesession.h"

K_PLUGIN_FACTORY(KDevErlangSupportFactory, registerPlugin<erlang::LanguageSupport>();)
K_EXPORT_PLUGIN(KDevErlangSupportFactory(KAboutData("kdeverlangsupport","kdeverlang", ki18n("Erlang Support"), "0.1", ki18n("Support for Erlang Language"), KAboutData::License_GPL)
    .addAuthor(ki18n("Victor Vicente de Carbalho"), ki18n("Author"), "victor.v.carvalho@gmail.com", "")
))

namespace erlang
{
LanguageSupport* LanguageSupport::m_self = 0;

#if KDE_VERSION > KDE_MAKE_VERSION(4, 3, 80)
int debugArea() { static int s_area = KDebug::registerArea("kdeverlangsupport"); return s_area; }
#else
int debugArea() { return 1; }
#endif

LanguageSupport::LanguageSupport(QObject* parent, const QVariantList& /*args*/)
    : KDevelop::IPlugin(KDevErlangSupportFactory::componentData(), parent),
      KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE(KDevelop::ILanguageSupport)

    m_self = this;

    //CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    //new KDevelop::CodeCompletion(this, ccModel, name());
}

QString LanguageSupport::name() const
{
    return "Erlang";
}

KDevelop::ParseJob *LanguageSupport::createParseJob(const KUrl &url)
{
    kDebug(debugArea()) << url;
    return new ParseJob(url);
}

LanguageSupport *LanguageSupport::self()
{
    return m_self;
}
}

#include "erlanglanguagesupport.moc"
