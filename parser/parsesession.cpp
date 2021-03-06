/*****************************************************************************
 * Copyright (c) 2007 Piyush verma <piyush.verma@gmail.com>                  *
 * Copyright (c) 2008 Niko Sams <niko.sams@gmail.com>                        *
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

#include "parsesession.h"

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-token-stream.h"

#include <QFile>
#include <QTextCodec>
#include "erlangast.h"

namespace erlang
{

ParseSession::ParseSession()
        :   m_debug(false),
        m_pool(new KDevPG::MemoryPool()),
        m_tokenStream(new TokenStream())
{
}
ParseSession::~ParseSession()
{
    delete m_pool;
    delete m_tokenStream;
}

QString ParseSession::contents() const
{
    return m_contents;
}

void ParseSession::setContents(const QString& contents)
{
    m_contents = contents;
}

void ParseSession::setCurrentDocument(const QString& filename)
{
    m_currentDocument = filename;
}

bool ParseSession::readFile(const QString& filename, const char* codec)
{
    m_currentDocument = filename;

    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        kDebug() << "Couldn't open project file:" << filename;
        return false;
    }
    QTextStream s(&f);
    if (codec)
        s.setCodec(QTextCodec::codecForName(codec));
    m_contents = s.readAll();
    return true;
}
void ParseSession::setDebug(bool debug)
{
    m_debug = debug;
}

TokenStream* ParseSession::tokenStream() const
{
    return m_tokenStream;
}


Parser* ParseSession::createParser(int initialState)
{
    Parser* parser = new Parser;
    parser->setTokenStream(m_tokenStream);
    parser->setMemoryPool(m_pool);
    parser->setDebug(m_debug);
    parser->setCurrentDocument(m_currentDocument);

    parser->tokenize(m_contents, initialState);
    return parser;
}

bool ParseSession::parse(erlang::FormAst** ast)
{
    Parser* parser = createParser();
    FormAst* erlangAst;
    bool matched = parser->parseForm(&erlangAst);
    if (matched) {
        kDebug() << "Successfully parsed";
        *ast = erlangAst;
    } else {
        *ast = 0;
        parser->expectedSymbol(AstNode::FormKind, "module declaration");
        kDebug() << "Couldn't parse content";
    }
    m_problems = parser->problems();
    delete parser;
    return matched;
}

KDevelop::SimpleCursor ParseSession::positionAt(qint64 offset) const
{
    qint64 line, column;
    m_tokenStream->locationTable()->positionAt(offset, &line, &column);
    return KDevelop::SimpleCursor(line, column);
}

QString ParseSession::symbol(qint64 token) const
{
    const TokenStream::Token& tok = m_tokenStream->token(token);
    return m_contents.mid(tok.begin, tok.end - tok.begin + 1);
}

QString ParseSession::symbol(AstNode* node) const
{
    const TokenStream::Token& startTok = m_tokenStream->token(node->startToken);
    const TokenStream::Token& endTok = m_tokenStream->token(node->endToken);
    return m_contents.mid(startTok.begin, endTok.end - startTok.begin + 1);
}

QString ParseSession::docComment(qint64 token) const
{
    const TokenStream::Token& tok = m_tokenStream->token(token);
    if (!tok.docCommentEnd) return QString();
    return m_contents.mid(tok.docCommentBegin, tok.docCommentEnd - tok.docCommentBegin + 1);
}

QList<KDevelop::ProblemPointer> ParseSession::problems()
{
    return m_problems;
}

}
