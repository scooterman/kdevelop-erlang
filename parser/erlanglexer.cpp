/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2010 Victor Vicente de Carvalho                             *
 *   		      <victor.v.carvalho@gmail.com>                        *
 *                                                                         *
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

#include "erlanglexer.h"

#include "erlanglexer.h"
#include "tokenstream.h"
#include <erlangparser.h>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QRegExp>
#include <QtCore/QDebug>

#include <iostream>

namespace erlang
{

Lexer::Lexer(TokenStream* tokenStream, const QString& content, int initialState):
        m_content(content), m_tokenStream(tokenStream),
        m_curpos(0), m_contentSize(m_content.size()),
        m_tokenBegin(0), m_tokenEnd(0), m_haltCompiler(0)
{
    pushState(ErrorState);
    pushState(initialState);
}

int Lexer::state(int deepness) const
{
    return m_state.at(m_state.size() - deepness - 1);
}
void Lexer::printState()
{
    int s = state();
    if (s == ErrorState)
        qDebug() << "ErrorState";
    else if (s == DefaultState)
        qDebug() << "DefaultState";
    else if (s == String)
        qDebug() << "String";
}

void Lexer::pushState(int state)
{
    m_state.push(state);
}

void Lexer::popState()
{
    m_state.pop();
}

bool Lexer::processCharLiteral(QChar* it)
{
    return it->unicode() != '\n';
}

bool Lexer::isValidNumeric(QChar* it, bool isExponential, bool hasRadix, bool hasPoint)
{
    bool nextIsValid = m_curpos + 1 < m_contentSize;
    return it->isDigit()
           || (it->unicode() == '.' && nextIsValid && (it + 1)->isDigit())
           || (it->unicode() == '#' && nextIsValid && (it + 1)->isDigit())
           || (nextIsValid && isExponential && hasPoint && (it->unicode() == '+' || it->unicode() == '-') && (it + 1)->isDigit())
           || (hasRadix && !hasPoint && (it->toLower() == 'a' || it->toLower() == 'b' ||
                                         it->toLower() == 'c' || it->toLower() == 'd' ||
                                         it->toLower() == 'e' || it->toLower() == 'f'));

}

int Lexer::nextTokenKind()
{
    int token = Parser::Token_INVALID;
    if (m_curpos >= m_contentSize) {
        m_tokenBegin = -1;
        m_tokenEnd = -1;
        createNewline(m_curpos);
        return 0;
    }
    QChar* it = m_content.data();
    it += m_curpos;
    m_tokenBegin = m_curpos;

    if (it->isSpace())
    {
        token = Parser::Token_WHITESPACE;
        while (m_curpos < m_contentSize && it->isSpace())
        {
            if (it->unicode() == '\n')
            {
                createNewline(m_curpos);
            }
            it++;
            m_curpos++;
        }
        m_curpos--;
    }
    else if (it->isDigit())
    {
        QString num;

        bool hasPoint = false;
        bool hasRadix = false;
        bool isExponential = false;

        while (m_curpos < m_contentSize && isValidNumeric(it, isExponential, hasRadix, hasPoint))
        {
            if (it->unicode() == '.' && hasPoint)
            {
                m_haltCompiler = true;
            }

            if (it->unicode() == '.' && (it + 1)->isDigit())
            {
                hasPoint = true;
            }
            if (it->unicode() == '#'  && (it + 1)->isDigit())
            {
                hasRadix = true;
            }
            if (!hasRadix && hasPoint && it->toLower() == 'e')
            {
                isExponential = true;
            }

            num.append(*it);
            it++;

            if (m_curpos < m_contentSize && isValidNumeric(it, isExponential, hasRadix, hasPoint))
            {
                m_curpos++;
            }
        }

        if (hasPoint)
        {
            token = Parser::Token_FLOAT_LITERAL;
        }
        else
        {
            token = Parser::Token_INTEGER_LITERAL;
        }
    }
    else if (it->unicode() == '$' && processCharLiteral(it + 1))
    {
        token = Parser::Token_CHAR_LITERAL;
    }
    else if (it->unicode() == '}')
    {
        token = Parser::Token_RBRACE;
        if (state() == Tuple)
        {
            popState();
        }
    }
    else if (it->unicode() == '_')
    {
        token = Parser::Token_UNDERLINE;
    }
    else if (it->unicode() == '{')
    {
        token = Parser::Token_LBRACE;
        pushState(Tuple);
    }
    else if (it->unicode() == ')')
    {
        token = Parser::Token_RPAREN;
    }
    else if (it->unicode() == '(')
    {
        token = Parser::Token_LPAREN;
    }
    else if (it->unicode() == ']')
    {
        token = Parser::Token_RBRACKET;
    }
    else if (it->unicode() == '[')
    {
        token = Parser::Token_LBRACKET;
    }
    else if (it->unicode() == ',')
    {
        token = Parser::Token_COMMA;
    }
    else if (it->unicode() == '#')
    {
        token = Parser::Token_POUND_SIGN;
    }
    else if (it->unicode() == '!')
    {
        token = Parser::Token_EXCLAMATION;
    }
    else if (it->unicode() == '<')
    {
        if ( (it + 1)->unicode() == '-')
        {
            m_curpos += 1;
            token = Parser::Token_LIST_COMPREHENSION_LEADS_TO;
        }
        else if ( (it + 1)->unicode() == '<' )
        {
            m_curpos += 1;
            token = Parser::Token_BINARY_OPEN;
        }
        else
        {
            token = Parser::Token_IS_SMALLER;
        }
    }
    else if (it->unicode() == '>')
    {
        if ((it + 1)->unicode() == '=')
        {
            m_curpos++;
            token = Parser::Token_IS_GREATER_OR_EQUAL;
        }
        else if ( (it + 1)->unicode() == '>' )
        {
            m_curpos += 1;
            token = Parser::Token_BINARY_CLOSE;
        }
        else
        {
            token = Parser::Token_IS_GREATER;
        }
    }
    else if (it->unicode() == '?')
    {
        token = Parser::Token_QUESTION;
    }
    else if (it->unicode() == '%')
    {
        token = Parser::Token_COMMENT;
        while (it->unicode() != '\n')
        {
            m_curpos++;
            it++;
        }
        createNewline(m_curpos);
    }
    else if (it->unicode() == '/')
    {
        if ((it + 1)->unicode() == '=')
        {
            token = Parser::Token_IS_NOT_EQUAL;
        }
        else
        {
            token = Parser::Token_FORWARD_SLASH;
        }
    }
    else if (it->unicode() == '*')
    {
        token = Parser::Token_MUL;
    }
    else if (it->unicode() == '|')
    {
        if ((it + 1)->unicode() == '|')
        {
            m_curpos++;
            token = Parser::Token_DOUBLE_PIPE;
        }
        else
        {
            token = Parser::Token_PIPE;
        }
    }
    else if (it->unicode() == '+')
    {
        if ((it + 1)->unicode() == '+')
        {
            m_curpos++;
            token = Parser::Token_LIST_ADDITION;
        }
        else
        {
            token = Parser::Token_PLUS;
        }
    }
    else if (it->unicode() == '-')
    {
        if ((it + 1)->unicode() == '>')
        {
            m_curpos++;
            token = Parser::Token_LEADS_TO;
        }
        else  if ((it + 1)->unicode() == '-')
        {
            m_curpos++;
            token = Parser::Token_LIST_DIFFERENCE;
        }
        else
        {
            token = Parser::Token_MINUS;
        }
    }
    else if (it->unicode() == ':')
    {
        if ( (it + 1)->unicode() == ':')
        {
            m_curpos += 1;
            token = Parser::Token_DOUBLE_COLON;
        }
        else
        {
            token = Parser::Token_COLON;
        }
    }
    else if (it->unicode() == '.')
    {
        token = Parser::Token_DOT;
    }
    else if (it->unicode() == ';')
    {
        token = Parser::Token_SEMICOLON;
    }
    else if (it->unicode() == '\'')
    {
        token = Parser::Token_ATOM_LITERAL;
        it++;
        m_curpos++;
        int startPos = m_curpos;
        while (m_curpos < m_contentSize
                && (it->unicode() != '\'')) {
            if (it->unicode() == '\n') createNewline(m_curpos);
            it++;
            m_curpos++;
        }
        // if the string is never terminated, make sure we don't overflow the boundaries
        if ( m_curpos == m_contentSize ) {
            --m_curpos;
        }
    }
    else if (it->unicode() == '"')
    {
        token = Parser::Token_STRING_LITERAL;
        it++;
        m_curpos++;
        while (m_curpos < m_contentSize
                && (it->unicode() != '\"')) {
            if (it->unicode() == '\n') createNewline(m_curpos);
            it++;
            m_curpos++;
        }
        // if the string is never terminated, make sure we don't overflow the boundaries
        if ( m_curpos == m_contentSize ) {
            --m_curpos;
        }
    }
    else if (it->unicode() == '=')
    {
        if ((it + 1)->unicode() == '=')
        {
            m_curpos++;
            token = Parser::Token_IS_EQUAL;
        }
        else if ((it + 1)->unicode() == '<') {
            m_curpos++;
            token = Parser::Token_IS_SMALLER_OR_EQUAL;
        }
        else if ((it + 1)->unicode() == ':' && (it + 2)->unicode() == '=')
        {
            m_curpos += 2;
            token = Parser::Token_EXACT_EQUATIONAL;
        }
        else if ((it + 1)->unicode() == '/' && (it + 2)->unicode() == '=')
        {
            m_curpos += 2;
            token = Parser::Token_EXACT_NOT_EQUATIONAL;
        }
        else
        {
            token = Parser::Token_ASSIGN;
        }
    }
    else if (it->isLetter() && it->isUpper())
    {
        QString name;
        while (m_curpos < m_contentSize && (isValidVariableIdentifier(it))) {
            name.append(*it);
            it++;
            m_curpos++;
        }
        m_curpos--;
        token = Parser::Token_VARIABLE;
    }
    else if (it->isLetter() && it->isLower())
    {
        QString name;
        while (m_curpos < m_contentSize && (isValidVariableIdentifier(it))) {
            name.append(*it);
            it++;
            m_curpos++;
        }

        m_curpos--;

        if (name == "after") {
            token = Parser::Token_AFTER;
        } else if (name == "begin") {
            token = Parser::Token_BEGIN;
        } else if (name == "case") {
            token = Parser::Token_CASE;
        } else if (name == "if") {
            token = Parser::Token_IF;
        } else if (name == "catch") {
            token = Parser::Token_CATCH;
        } else if (name == "cond") {
            token = Parser::Token_COND;
        } else if (name == "end") {
            token = Parser::Token_END;
        } else if (name == "fun") {
            token = Parser::Token_FUN;
        } else if (name == "let") {
            token = Parser::Token_LET;
        } else if (name == "of") {
            token = Parser::Token_OF;
        } else if (name == "catch") {
            token = Parser::Token_QUERY;
        } else if (name == "class") {
            token = Parser::Token_RECEIVE;
        } else if (name == "when") {
            token = Parser::Token_WHEN;
        } else if (name == "div") {
            token = Parser::Token_INT_DIV;
        } else if (name == "rem") {
            token = Parser::Token_INT_REM;
        } else if (name == "or") {
            token = Parser::Token_OR;
        } else if (name == "xor") {
            token = Parser::Token_XOR;
        } else if (name == "bor") {
            token = Parser::Token_BIT_OR;
        } else if (name == "bxor") {
            token = Parser::Token_BIT_XOR;
        } else if (name == "bsl") {
            token = Parser::Token_SL;
        } else if (name == "bsr") {
            token = Parser::Token_SR;
        } else if (name == "and") {
            token = Parser::Token_AND;
        } else if (name == "band") {
            token = Parser::Token_BIT_AND;
        } else if (name == "not") {
            token = Parser::Token_NOT;
        } else if (name == "bnot") {
            token = Parser::Token_BIT_NOT;
        } else if (name == "orelse") {
            token = Parser::Token_ORELSE;
        } else if (name == "andalso") {
            token = Parser::Token_ANDALSO;
        } else if (name == "module") {
            token = Parser::Token_MODULE_DIRECTIVE;
        } else if (name == "include") {
            token = Parser::Token_INCLUDE_DIRECTIVE;
        } else if (name == "export") {
            token = Parser::Token_EXPORT_DIRECTIVE;
        } else if (name == "file") {
            token = Parser::Token_FILE_DIRECTIVE;
        } else if (name == "record") {
            token = Parser::Token_RECORD_DIRECTIVE;
        } else if (name == "include") {
            token = Parser::Token_INCLUDE_DIRECTIVE;
        } else if (name == "behaviour"){
	  token = Parser::Token_BEHAVIOUR_DIRECTIVE;
	} else if (name == "define"){
	  token = Parser::Token_DEFINE_DIRECTIVE;
	}	
        else
        {
            token = Parser::Token_ATOM_LITERAL;
        }
    }

    m_tokenEnd = m_curpos;
    m_curpos++;

    return token;
}

qint64 Lexer::tokenBegin() const
{
    return m_tokenBegin;
}

qint64 Lexer::tokenEnd() const
{
    return m_tokenEnd;
}

bool Lexer::isValidVariableIdentifier(QChar* it)
{
    return it->isLetter() || it->isDigit() || it->unicode() == '_' || it->unicode() == '@';
}

void Lexer::createNewline(int pos)
{
    if (m_tokenStream) m_tokenStream->locationTable()->newline(pos);
}

}

