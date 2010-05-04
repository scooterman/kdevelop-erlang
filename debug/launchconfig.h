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

#ifndef ERLANGLAUNCHCONFIG_H
#define ERLANGLAUNCHCONFIG_H

#include <interfaces/ilauncher.h>
#include <interfaces/launchconfigurationpage.h>
#include <QTreeWidget>

#include "ui_debug_config.h"

namespace KDevelop {
    class PathMappingsWidget;
}

namespace ErlangDebugPlugin
{
class ErlangDebuggerPlugin;

class ConfigPageFactory : public KDevelop::LaunchConfigurationPageFactory
{
public:
    virtual KDevelop::LaunchConfigurationPage* createWidget(QWidget* parent);
};

class ConfigPage : public KDevelop::LaunchConfigurationPage , public Ui::ErlangDebugConfigDialog
{
Q_OBJECT
public:
    ConfigPage( QWidget* parent = 0 );
    virtual KIcon icon() const;
    virtual void loadFromConfiguration(const KConfigGroup& cfg, KDevelop::IProject* = 0);
    virtual void saveToConfiguration(KConfigGroup, KDevelop::IProject* = 0 ) const;
    virtual QString title() const;
private:
    KDevelop::PathMappingsWidget *m_pathMappings;
    QTreeView* m_treeView;
};


class ErlangLauncher : public KDevelop::ILauncher
{
public:
    ErlangLauncher(ErlangDebugPlugin::ErlangDebuggerPlugin* plugin);

    virtual KJob* start(const QString& launchMode, KDevelop::ILaunchConfiguration* cfg);
    virtual QList< KDevelop::LaunchConfigurationPageFactory* > configPages() const;
    virtual QStringList supportedModes() const;
    virtual QString description() const;
    virtual QString name() const;
    virtual QString id();

private:
    QList<KDevelop::LaunchConfigurationPageFactory*> factoryList;
    ErlangDebuggerPlugin* m_plugin;
};

}

#endif // ERLANGLAUNCHCONFIG_H
