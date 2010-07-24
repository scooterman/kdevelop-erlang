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

#include <QXmlStreamReader>

#include <KDebug>

#include "framestackmodel.h"
#include "messages.h"

namespace ErlangDebugPlugin {

void FrameStackModel::fetchThreads()
{
}

/*
void FrameStackModel::handleStack(const QDomDocument &xml)
{
    Q_ASSERT(xml.documentElement().attribute("command") == "stack_get");

    QList<KDevelop::FrameStackModel::FrameItem> frames;
    QDomElement el = xml.documentElement().firstChildElement("stack");
    while (!el.isNull()) {
        KDevelop::FrameStackModel::FrameItem f;
        f.nr = el.attribute("level").toInt();
        f.name = el.attribute("where");
        f.file = el.attribute("filename");
        f.line = el.attribute("lineno").toInt() - 1;
        frames << f;
        el = el.nextSiblingElement("stack");
    }
    setFrames(0, frames);
    setHasMoreFrames(0, false);
}*/

void FrameStackModel::fetchFrames(int threadNumber, int from, int to)
{
    Q_UNUSED(from); //we fetch always everything
    Q_UNUSED(to);
}

void FrameStackModel::handleStackList(StackTraceOutput* output)
{
  QList<KDevelop::FrameStackModel::FrameItem> frames;
  
  foreach(StackInfo item, output->getStackTrace())
  {
    KDevelop::FrameStackModel::FrameItem f;
    f.name = item.function_name;
    f.line = item.line;
    f.nr = item.stack_pos;
    f.file = item.filename;
    
    frames << f;
  }
  
  int threadID;
  if (m_processToThreadID.contains(output->getProcess()))
  {
    threadID = m_processToThreadID[output->getProcess()]; 
  }
  else
  {
    threadID = m_processToThreadID[output->getProcess()] = m_threadID++;    
  }
  
  QList<KDevelop::FrameStackModel::ThreadItem> threads;
  QMap<QString, int>::iterator it = m_processToThreadID.begin();
  
  for (; it != m_processToThreadID.end(); ++it)
  {
    KDevelop::FrameStackModel::ThreadItem item;
    item.name = it.key();
    item.nr = it.value();
    threads << item;
  }
  
  setThreads(threads);
  
  setFrames(threadID, frames); 
  setHasMoreFrames(threadID, false);
  setCurrentThread(threadID);
}

FrameStackModel::FrameStackModel(DebugSession* session) : 
  KDevelop::FrameStackModel(session) , m_threadID(0)
{
  connect(session, SIGNAL(stackTraceUpdate(StackTraceOutput*)), this, SLOT(handleStackList(StackTraceOutput*)));
}

}
