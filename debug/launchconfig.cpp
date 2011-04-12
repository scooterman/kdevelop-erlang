/*
    Erlang Debugger support for KDevelop
    Copyright (C) 2010  Victor Vicente de Carvalho

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

#include "launchconfig.h"

#include "debugplugin.h"
#include "debugjob.h"
#include "debugsession.h"

#include <execute/iexecuteplugin.h>
#include <debugger/util/pathmappings.h>
#include <interfaces/ilaunchconfiguration.h>
#include <interfaces/iproject.h>

#include <klocale.h>
#include <kdebug.h>

#include <QBoxLayout>
#include <KIcon>
#include <KLocalizedString>
#include <qheaderview.h>
#include <project/projectmodel.h>

#include <kmimetype.h>
#include <kconfiggroup.h>
#include <QFileInfo>
#include <QListView>

namespace ErlangDebugPlugin
{
  
KDevelop::LaunchConfigurationPage* ConfigPageFactory::createWidget( QWidget* parent )
{
    return new ConfigPage( parent );
}

ConfigPage::ConfigPage( QWidget* parent )
    : LaunchConfigurationPage(parent)
{
    setupUi(this);
}

KIcon ConfigPage::icon() const
{
    return KIcon();
}

void ConfigPage::loadFromConfiguration( const KConfigGroup& cfg, KDevelop::IProject* project )
{  
    KMimeType::Ptr mimetype =KMimeType::mimeType("text/x-erlang");
    
    QStringList itens = cfg.readEntry(ErlangDebugPlugin::interpretedModules, QStringList());
    QStringList includeLibraryPaths = cfg.readEntry(ErlangDebugPlugin::libraryPaths, QStringList());
    
    foreach(KDevelop::ProjectFileItem* item, project->files())
    {
      if (KMimeType::findByUrl(item->fileName())->name() == mimetype->name())
      {
	QFileInfo module(item->fileName());
	QString basename = module.baseName();
	QTreeWidgetItem* i = new QTreeWidgetItem(interpretableTreeWidget, QStringList(basename));
	i->setCheckState(0, itens.contains(basename) ? Qt::Checked : Qt::Unchecked);
      }
    }
    
    foreach(QString path, includeLibraryPaths)
    {
      includeLibraryListWidget->addItem(path);
    }
    
    if (includeLibraryPaths.empty())
    {
      includeLibraryListWidget->addItem(project->folder().path() + "ebin/");
    }
    
   QString moduleName = cfg.readEntry(ErlangDebugPlugin::callableModule, QString());
   QString moduleFunction = cfg.readEntry(ErlangDebugPlugin::callableFunction, QString());
   QString arguments = cfg.readEntry(ErlangDebugPlugin::callableArguments, QString());
   
   moduleNameLineEdit->setText(moduleName);
   moduleFunctionLineEdit->setText(moduleFunction);
   functionArgumentsLineEdit->setText(arguments);
}

void ConfigPage::saveToConfiguration( KConfigGroup cfg, KDevelop::IProject* project ) const
{
   QStringList to_be_interpreted;
   
   for(int i = 0; i < interpretableTreeWidget->topLevelItemCount(); ++i)
   {
     QTreeWidgetItem* w_item = interpretableTreeWidget->topLevelItem(i);
     if (w_item->checkState(0) == Qt::Checked)
      to_be_interpreted << w_item->text(0);
   }
   
   QStringList libraryPaths;
   
   for(int i = 0; i < includeLibraryListWidget->count(); ++i)
   { 
     if (QFileInfo(includeLibraryListWidget->item(i)->text()).exists())
     {
       libraryPaths << includeLibraryListWidget->item(i)->text();
     }     
   }
   
   cfg.writeEntry(ErlangDebugPlugin::interpretedModules, to_be_interpreted);   
   cfg.writeEntry(ErlangDebugPlugin::rebuildDebuggerInterface, true);
   cfg.writeEntry(ErlangDebugPlugin::libraryPaths, libraryPaths);
  
   cfg.writeEntry(ErlangDebugPlugin::callableModule, moduleNameLineEdit->text());   
   cfg.writeEntry(ErlangDebugPlugin::callableFunction, moduleFunctionLineEdit->text());
   cfg.writeEntry(ErlangDebugPlugin::callableArguments, functionArgumentsLineEdit->text());
}

QString ConfigPage::title() const
{
    return i18n( "Erlang Configuration" );
}
  
ErlangLauncher::ErlangLauncher(ErlangDebuggerPlugin* plugin)
  : m_plugin(plugin)
{
  factoryList << new ConfigPageFactory();
}
  
KJob* ErlangLauncher::start(const QString& launchMode, KDevelop::ILaunchConfiguration* cfg)
{
    Q_ASSERT(cfg);
    if( !cfg )
    {
        return 0;
    }
    if( launchMode == "debug" )
    {
        return new ErlangDebugJob( m_plugin->createSession(), cfg, m_plugin);
    }
    kWarning() << "Unknown launch mode" << launchMode << "for config:" << cfg->name();
    return 0;
}

QList< KDevelop::LaunchConfigurationPageFactory* > ErlangLauncher::configPages() const
{
  return factoryList;
}

QStringList ErlangLauncher::supportedModes() const
{
  return QStringList() << "debug";
}

QString ErlangLauncher::description() const
{
  return i18n("Executes a erlang application in debug mode");
}

QString ErlangLauncher::name() const
{
  return i18n("Erlang");
}

QString ErlangLauncher::id()
{
  return "erlang";
}

}
