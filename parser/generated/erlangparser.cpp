// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "erlangparser.h"



#include <QtCore/QDebug>
#include <KTextEditor/Range>

namespace erlang
{

void Parser::tokenize(const QString& contents, int initialState)
{
    m_contents = contents;
    Lexer lexer(tokenStream, contents, initialState);
    int kind = Parser::Token_EOF;
    int lastDocCommentBegin;
    int lastDocCommentEnd;

    do
    {
        lastDocCommentBegin = 0;
        lastDocCommentEnd = 0;
        kind = lexer.nextTokenKind();
        while (kind == Parser::Token_WHITESPACE || kind == Parser::Token_COMMENT)
        {
            kind = lexer.nextTokenKind();
        }
        if ( !kind ) // when the lexer returns 0, the end of file is reached
        {
            kind = Parser::Token_EOF;
        }
        Parser::Token &t = tokenStream->next();
        t.begin = lexer.tokenBegin();
        t.end = lexer.tokenEnd();
        t.kind = kind;
        if ( m_debug ) qDebug() << kind << tokenText(t.begin,t.end) << t.begin << t.end;
    }
    while ( kind != Parser::Token_EOF );

    yylex(); // produce the look ahead token
}

QString Parser::tokenText(qint64 begin, qint64 end)
{
    return m_contents.mid(begin,end-begin+1);
}

void Parser::reportProblem( Parser::ProblemType type, const QString& message )
{
    if (type == Error)
        qDebug() << "** ERROR:" << message;
    else if (type == Warning)
        qDebug() << "** WARNING:" << message;
    else if (type == Info)
        qDebug() << "** Info:" << message;

    qint64 sLine;
    qint64 sCol;
    qint64 index = tokenStream->index()-1;
    tokenStream->startPosition(index, &sLine, &sCol);
    qint64 eLine;
    qint64 eCol;
    tokenStream->endPosition(index, &eLine, &eCol);
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setSource(KDevelop::ProblemData::Parser);
    switch ( type )
    {
    case Error:
        p->setSeverity(KDevelop::ProblemData::Error);
        break;
    case Warning:
        p->setSeverity(KDevelop::ProblemData::Warning);
        break;
    case Info:
        p->setSeverity(KDevelop::ProblemData::Hint);
        break;
    }
    p->setDescription(message);
    p->setFinalLocation(KDevelop::DocumentRange(m_currentDocument, KTextEditor::Range(sLine, sCol, eLine, eCol+1)));
    m_problems << KDevelop::ProblemPointer(p);
}


// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
    reportProblem( Parser::Error, QString("Expected token \"%1\"").arg(name));
}

void Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
    qint64 line;
    qint64 col;
    qint64 index = tokenStream->index()-1;
    Token &token = tokenStream->token(index);
    kDebug() << "token starts at:" << token.begin;
    kDebug() << "index is:" << index;
    tokenStream->startPosition(index, &line, &col);
    QString tokenValue = tokenText(token.begin, token.end);
    qint64 eLine;
    qint64 eCol;
    tokenStream->endPosition(index, &eLine, &eCol);
    reportProblem( Parser::Error,
                   QString("Expected symbol \"%1\" (current token: \"%2\" [%3] at %4:%5 - %6:%7)")
                   .arg(name)
                   .arg(token.kind != 0 ? tokenValue : "EOF")
                   .arg(token.kind)
                   .arg(line)
                   .arg(col)
                   .arg(eLine)
                   .arg(eCol));
}

void Parser::setDebug( bool debug )
{
    m_debug = debug;
}

void Parser::setCurrentDocument(QString url)
{
    m_currentDocument = url;
}

Parser::ParserState *Parser::copyCurrentState()
{
    ParserState *state = new ParserState();
    state->varExpressionState = m_state.varExpressionState;
    state->varExpressionIsVariable = m_state.varExpressionIsVariable;
    return state;
}

void Parser::restoreState( Parser::ParserState* state)
{
    m_state.varExpressionState = state->varExpressionState;
    m_state.varExpressionIsVariable = state->varExpressionIsVariable;
}

} // end of namespace erlang


namespace erlang
{

bool Parser::parseAddOp(AddOpAst **yynode)
{
    *yynode = create<AddOpAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BIT_OR
        || yytoken == Token_BIT_XOR
        || yytoken == Token_MINUS
        || yytoken == Token_OR
        || yytoken == Token_PLUS
        || yytoken == Token_SL
        || yytoken == Token_SR
        || yytoken == Token_XOR)
    {
        if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BIT_OR)
        {
            if (yytoken != Token_BIT_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_OR, "bor");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BIT_XOR)
        {
            if (yytoken != Token_BIT_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_XOR, "bxor");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SL)
        {
            if (yytoken != Token_SL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SL, "bsl");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SR)
        {
            if (yytoken != Token_SR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SR, "bsr");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OR)
        {
            if (yytoken != Token_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OR, "or");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_XOR)
        {
            if (yytoken != Token_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_XOR, "xor");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArgumentList(ArgumentListAst **yynode)
{
    *yynode = create<ArgumentListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY_OPEN
            || yytoken == Token_BIT_NOT
            || yytoken == Token_CASE
            || yytoken == Token_CATCH
            || yytoken == Token_CHAR_LITERAL
            || yytoken == Token_DOT
            || yytoken == Token_FLOAT_LITERAL
            || yytoken == Token_FUN
            || yytoken == Token_IF
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET
            || yytoken == Token_LPAREN
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS
            || yytoken == Token_POUND_SIGN
            || yytoken == Token_QUERY
            || yytoken == Token_RECEIVE
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TRY
            || yytoken == Token_VARIABLE)
        {
            ExprsAst *__node_0 = 0;
            if (!parseExprs(&__node_0))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprsKind, "exprs");
                }
                return false;
            }
            (*yynode)->exprs = __node_0;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAtom1(Atom1Ast **yynode)
{
    *yynode = create<Atom1Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->literal = -1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        if (yytoken == Token_SPEC)
        {
            if (yytoken != Token_SPEC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SPEC, "spec");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ATOM_LITERAL)
        {
            if (yytoken != Token_ATOM_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
                }
                return false;
            }
            (*yynode)->literal = tokenStream->index() - 1;
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAtomic(AtomicAst **yynode)
{
    *yynode = create<AtomicAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_STRING_LITERAL)
    {
        if (yytoken == Token_CHAR_LITERAL)
        {
            if (yytoken != Token_CHAR_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CHAR_LITERAL, "char_literal");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INTEGER_LITERAL)
        {
            if (yytoken != Token_INTEGER_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FLOAT_LITERAL)
        {
            if (yytoken != Token_FLOAT_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FLOAT_LITERAL, "float literal");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ATOM_LITERAL)
        {
            if (yytoken != Token_ATOM_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STRING_LITERAL)
        {
            if (yytoken != Token_STRING_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
                }
                return false;
            }
            (*yynode)->stringsSequence = snoc((*yynode)->stringsSequence, tokenStream->index() - 1, memoryPool);
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAttrVal(AttrValAst **yynode)
{
    *yynode = create<AttrValAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        bool blockErrors_1 = blockErrors(true);
        qint64 try_startToken_1 = tokenStream->index() - 1;
        ParserState *try_startState_1 = copyCurrentState();
        {
            if (yytoken != Token_LPAREN)
                goto __catch_1;
            yylex();

            ExprAst *__node_1 = 0;
            if (!parseExpr(&__node_1))
            {
                goto __catch_1;
            }
            (*yynode)->expr = __node_1;

            if (yytoken != Token_COMMA)
                goto __catch_1;
            yylex();

            ExprsAst *__node_2 = 0;
            if (!parseExprs(&__node_2))
            {
                goto __catch_1;
            }
            (*yynode)->exprs = __node_2;

            if (yytoken != Token_RPAREN)
                goto __catch_1;
            yylex();

        }
        blockErrors(blockErrors_1);
        if (try_startState_1)
            delete try_startState_1;

        if (false) // the only way to enter here is using goto
        {
__catch_1:
            if (try_startState_1)
            {
                restoreState(try_startState_1);
                delete try_startState_1;
            }
            blockErrors(blockErrors_1);
            rewind(try_startToken_1);

            ExprAst *__node_3 = 0;
            if (!parseExpr(&__node_3))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_3;

            if (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                ExprsAst *__node_4 = 0;
                if (!parseExprs(&__node_4))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprsKind, "exprs");
                    }
                    return false;
                }
                (*yynode)->exprs = __node_4;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAttribute(AttributeAst **yynode)
{
    *yynode = create<AttributeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MINUS)
    {
        if (yytoken != Token_MINUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MINUS, "-");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_SPEC)
        {
            if (yytoken != Token_SPEC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SPEC, "spec");
                }
                return false;
            }
            yylex();

            TypeSpecAst *__node_5 = 0;
            if (!parseTypeSpec(&__node_5))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeSpecKind, "typeSpec");
                }
                return false;
            }
            (*yynode)->type_spec = __node_5;

        }
        else if (yytoken == Token_MODULE_DIRECTIVE)
        {
            ModuleDeclarationAst *__node_6 = 0;
            if (!parseModuleDeclaration(&__node_6))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ModuleDeclarationKind, "moduleDeclaration");
                }
                return false;
            }
            (*yynode)->module_declaration = __node_6;

        }
        else if (yytoken == Token_EXPORT_DIRECTIVE)
        {
            ExportDeclarationAst *__node_7 = 0;
            if (!parseExportDeclaration(&__node_7))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExportDeclarationKind, "exportDeclaration");
                }
                return false;
            }
            (*yynode)->export_declaration = __node_7;

        }
        else if (yytoken == Token_IMPORT_DIRECTIVE)
        {
            ImportDeclarationAst *__node_8 = 0;
            if (!parseImportDeclaration(&__node_8))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ImportDeclarationKind, "importDeclaration");
                }
                return false;
            }
            (*yynode)->import_declaration = __node_8;

        }
        else if (yytoken == Token_RECORD_DIRECTIVE)
        {
            RecordDeclarationAst *__node_9 = 0;
            if (!parseRecordDeclaration(&__node_9))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RecordDeclarationKind, "recordDeclaration");
                }
                return false;
            }
            (*yynode)->record_declaration = __node_9;

        }
        else if (yytoken == Token_FILE_DIRECTIVE)
        {
            FileDeclarationAst *__node_10 = 0;
            if (!parseFileDeclaration(&__node_10))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FileDeclarationKind, "fileDeclaration");
                }
                return false;
            }
            (*yynode)->file_declaration = __node_10;

        }
        else if (yytoken == Token_BEHAVIOUR_DIRECTIVE)
        {
            BehaviourDeclarationAst *__node_11 = 0;
            if (!parseBehaviourDeclaration(&__node_11))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BehaviourDeclarationKind, "behaviourDeclaration");
                }
                return false;
            }
            (*yynode)->behaviour_declaration = __node_11;

        }
        else if (yytoken == Token_ATOM_LITERAL)
        {
            AttributeDeclarationAst *__node_12 = 0;
            if (!parseAttributeDeclaration(&__node_12))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AttributeDeclarationKind, "attributeDeclaration");
                }
                return false;
            }
            (*yynode)->attribute_declaration = __node_12;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAttributeDeclaration(AttributeDeclarationAst **yynode)
{
    *yynode = create<AttributeDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->name = -1;
    (*yynode)->line = -1;

    if (yytoken == Token_ATOM_LITERAL)
    {
        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_STRING_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
            }
            return false;
        }
        (*yynode)->name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_COMMA)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COMMA, ",");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_INTEGER_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
            }
            return false;
        }
        (*yynode)->line = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBehaviourDeclaration(BehaviourDeclarationAst **yynode)
{
    *yynode = create<BehaviourDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->behaviour = -1;

    if (yytoken == Token_BEHAVIOUR_DIRECTIVE)
    {
        if (yytoken != Token_BEHAVIOUR_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BEHAVIOUR_DIRECTIVE, "module behaviour");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        (*yynode)->behaviour = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinBaseType(BinBaseTypeAst **yynode)
{
    *yynode = create<BinBaseTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE)
    {
        if (yytoken != Token_VARIABLE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_VARIABLE, "variable");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON, ":");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinElement(BinElementAst **yynode)
{
    *yynode = create<BinElementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        BitExprAst *__node_13 = 0;
        if (!parseBitExpr(&__node_13))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitExprKind, "bitExpr");
            }
            return false;
        }
        (*yynode)->bit_expr = __node_13;

        OptBitSizeExprAst *__node_14 = 0;
        if (!parseOptBitSizeExpr(&__node_14))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptBitSizeExprKind, "optBitSizeExpr");
            }
            return false;
        }
        (*yynode)->opt_bit_size_expr = __node_14;

        OptBitTypeListAst *__node_15 = 0;
        if (!parseOptBitTypeList(&__node_15))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptBitTypeListKind, "optBitTypeList");
            }
            return false;
        }
        (*yynode)->opt_bit_type_list = __node_15;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinElements(BinElementsAst **yynode)
{
    *yynode = create<BinElementsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        BinElementAst *__node_16 = 0;
        if (!parseBinElement(&__node_16))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BinElementKind, "binElement");
            }
            return false;
        }
        (*yynode)->beSequence = snoc((*yynode)->beSequence, __node_16, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            BinElementAst *__node_17 = 0;
            if (!parseBinElement(&__node_17))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BinElementKind, "binElement");
                }
                return false;
            }
            (*yynode)->beSequence = snoc((*yynode)->beSequence, __node_17, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinUnitType(BinUnitTypeAst **yynode)
{
    *yynode = create<BinUnitTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VARIABLE)
    {
        if (yytoken != Token_VARIABLE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_VARIABLE, "variable");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_MUL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MUL, "*");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_INTEGER_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinary(BinaryAst **yynode)
{
    *yynode = create<BinaryAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BINARY_OPEN)
    {
        if (yytoken != Token_BINARY_OPEN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_OPEN, "<<");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY_OPEN
            || yytoken == Token_BIT_NOT
            || yytoken == Token_CASE
            || yytoken == Token_CHAR_LITERAL
            || yytoken == Token_FLOAT_LITERAL
            || yytoken == Token_FUN
            || yytoken == Token_IF
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET
            || yytoken == Token_LPAREN
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS
            || yytoken == Token_QUERY
            || yytoken == Token_RECEIVE
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TRY
            || yytoken == Token_VARIABLE)
        {
            BinElementsAst *__node_18 = 0;
            if (!parseBinElements(&__node_18))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BinElementsKind, "binElements");
                }
                return false;
            }
            (*yynode)->bin_elements = __node_18;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_BINARY_CLOSE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_CLOSE, ">>");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinaryComprehension(BinaryComprehensionAst **yynode)
{
    *yynode = create<BinaryComprehensionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BINARY_OPEN)
    {
        if (yytoken != Token_BINARY_OPEN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_OPEN, "<<");
            }
            return false;
        }
        yylex();

        BinaryAst *__node_19 = 0;
        if (!parseBinary(&__node_19))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BinaryKind, "binary");
            }
            return false;
        }
        (*yynode)->binary = __node_19;

        if (yytoken != Token_DOUBLE_PIPE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOUBLE_PIPE, "||");
            }
            return false;
        }
        yylex();

        LcExprsAst *__node_20 = 0;
        if (!parseLcExprs(&__node_20))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LcExprsKind, "lcExprs");
            }
            return false;
        }
        (*yynode)->lc_exprs = __node_20;

        if (yytoken != Token_BINARY_CLOSE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_CLOSE, ">>");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBinaryType(BinaryTypeAst **yynode)
{
    *yynode = create<BinaryTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BINARY_OPEN)
    {
        if (yytoken != Token_BINARY_OPEN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_OPEN, "<<");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_VARIABLE)
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_INTEGER_LITERAL)
            {
                if (yytoken != Token_INTEGER_LITERAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    BinUnitTypeAst *__node_21 = 0;
                    if (!parseBinUnitType(&__node_21))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::BinUnitTypeKind, "binUnitType");
                        }
                        return false;
                    }
                    (*yynode)->bin_unit_type = __node_21;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
            }
            else if (yytoken == Token_VARIABLE)
            {
                BinUnitTypeAst *__node_22 = 0;
                if (!parseBinUnitType(&__node_22))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BinUnitTypeKind, "binUnitType");
                    }
                    return false;
                }
                (*yynode)->bin_unit_type = __node_22;

            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_BINARY_CLOSE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BINARY_CLOSE, ">>");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitExpr(BitExprAst **yynode)
{
    *yynode = create<BitExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_BIT_NOT
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS)
        {
            PrefixOpAst *__node_23 = 0;
            if (!parsePrefixOp(&__node_23))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PrefixOpKind, "prefixOp");
                }
                return false;
            }
            (*yynode)->prefix_op = __node_23;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        ExprMaxAst *__node_24 = 0;
        if (!parseExprMax(&__node_24))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprMaxKind, "exprMax");
            }
            return false;
        }
        (*yynode)->expr_max = __node_24;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitSizeExpr(BitSizeExprAst **yynode)
{
    *yynode = create<BitSizeExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprMaxAst *__node_25 = 0;
        if (!parseExprMax(&__node_25))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprMaxKind, "exprMax");
            }
            return false;
        }
        (*yynode)->expr_max = __node_25;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitType(BitTypeAst **yynode)
{
    *yynode = create<BitTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_26 = 0;
        if (!parseAtom1(&__node_26))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_INTEGER_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitTypeList(BitTypeListAst **yynode)
{
    *yynode = create<BitTypeListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        BitTypeAst *__node_27 = 0;
        if (!parseBitType(&__node_27))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitTypeKind, "bitType");
            }
            return false;
        }
        (*yynode)->bit_type = __node_27;

        if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            BitTypeListAst *__node_28 = 0;
            if (!parseBitTypeList(&__node_28))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitTypeListKind, "bitTypeList");
                }
                return false;
            }
            (*yynode)->bit_type_list = __node_28;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCaseExpr(CaseExprAst **yynode)
{
    *yynode = create<CaseExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE)
    {
        if (yytoken != Token_CASE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CASE, "case");
            }
            return false;
        }
        yylex();

        ExprAst *__node_29 = 0;
        if (!parseExpr(&__node_29))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->expr = __node_29;

        if (yytoken != Token_OF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_OF, "of");
            }
            return false;
        }
        yylex();

        CrClausesAst *__node_30 = 0;
        if (!parseCrClauses(&__node_30))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::CrClausesKind, "crClauses");
            }
            return false;
        }
        (*yynode)->cr_clauses = __node_30;

        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClauseArgs(ClauseArgsAst **yynode)
{
    *yynode = create<ClauseArgsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        ArgumentListAst *__node_31 = 0;
        if (!parseArgumentList(&__node_31))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ArgumentListKind, "argumentList");
            }
            return false;
        }
        (*yynode)->argument_list = __node_31;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClauseBody(ClauseBodyAst **yynode)
{
    *yynode = create<ClauseBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LEADS_TO)
    {
        if (yytoken != Token_LEADS_TO)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LEADS_TO, "->");
            }
            return false;
        }
        yylex();

        ExprsAst *__node_32 = 0;
        if (!parseExprs(&__node_32))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprsKind, "exprs");
            }
            return false;
        }
        (*yynode)->exprs = __node_32;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClauseGuard(ClauseGuardAst **yynode)
{
    *yynode = create<ClauseGuardAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_WHEN || yytoken == Token_COLON
        || yytoken == Token_EOF
        || yytoken == Token_LEADS_TO)
    {
        if (yytoken == Token_WHEN)
        {
            if (yytoken != Token_WHEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHEN, "when");
                }
                return false;
            }
            yylex();

            GuardAst *__node_33 = 0;
            if (!parseGuard(&__node_33))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::GuardKind, "guard");
                }
                return false;
            }
            (*yynode)->guard = __node_33;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompOp(CompOpAst **yynode)
{
    *yynode = create<CompOpAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXACT_EQUATIONAL
        || yytoken == Token_EXACT_NOT_EQUATIONAL
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_IS_GREATER
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_IS_SMALLER_OR_EQUAL)
    {
        if (yytoken == Token_IS_EQUAL)
        {
            if (yytoken != Token_IS_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_EQUAL, "==");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_GREATER)
        {
            if (yytoken != Token_IS_GREATER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_GREATER, ">");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_GREATER_OR_EQUAL)
        {
            if (yytoken != Token_IS_GREATER_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_GREATER_OR_EQUAL, ">=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_NOT_EQUAL)
        {
            if (yytoken != Token_IS_NOT_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_NOT_EQUAL, "/=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_SMALLER)
        {
            if (yytoken != Token_IS_SMALLER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_SMALLER, "<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IS_SMALLER_OR_EQUAL)
        {
            if (yytoken != Token_IS_SMALLER_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IS_SMALLER_OR_EQUAL, "=<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_EXACT_EQUATIONAL)
        {
            if (yytoken != Token_EXACT_EQUATIONAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXACT_EQUATIONAL, "=:=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_EXACT_NOT_EQUATIONAL)
        {
            if (yytoken != Token_EXACT_NOT_EQUATIONAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXACT_NOT_EQUATIONAL, "=/=");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCrClause(CrClauseAst **yynode)
{
    *yynode = create<CrClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprAst *__node_34 = 0;
        if (!parseExpr(&__node_34))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        ClauseGuardAst *__node_35 = 0;
        if (!parseClauseGuard(&__node_35))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseGuardKind, "clauseGuard");
            }
            return false;
        }
        (*yynode)->clause_guard = __node_35;

        ClauseBodyAst *__node_36 = 0;
        if (!parseClauseBody(&__node_36))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
            }
            return false;
        }
        (*yynode)->clause_body = __node_36;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCrClauses(CrClausesAst **yynode)
{
    *yynode = create<CrClausesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        CrClauseAst *__node_37 = 0;
        if (!parseCrClause(&__node_37))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::CrClauseKind, "crClause");
            }
            return false;
        }
        (*yynode)->ccSequence = snoc((*yynode)->ccSequence, __node_37, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            CrClauseAst *__node_38 = 0;
            if (!parseCrClause(&__node_38))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CrClauseKind, "crClause");
                }
                return false;
            }
            (*yynode)->ccSequence = snoc((*yynode)->ccSequence, __node_38, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExportDeclaration(ExportDeclarationAst **yynode)
{
    *yynode = create<ExportDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXPORT_DIRECTIVE)
    {
        if (yytoken != Token_EXPORT_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EXPORT_DIRECTIVE, "exported functions");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACKET, "[");
            }
            return false;
        }
        yylex();

        FunctionSlashArityAst *__node_39 = 0;
        if (!parseFunctionSlashArity(&__node_39))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FunctionSlashArityKind, "functionSlashArity");
            }
            return false;
        }
        (*yynode)->exported_functionsSequence = snoc((*yynode)->exported_functionsSequence, __node_39, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            FunctionSlashArityAst *__node_40 = 0;
            if (!parseFunctionSlashArity(&__node_40))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionSlashArityKind, "functionSlashArity");
                }
                return false;
            }
            (*yynode)->exported_functionsSequence = snoc((*yynode)->exported_functionsSequence, __node_40, memoryPool);

        }
        if (yytoken != Token_RBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACKET, "]");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_DOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOT, ".");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr(ExprAst **yynode)
{
    *yynode = create<ExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_CATCH)
        {
            if (yytoken != Token_CATCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CATCH, "catch");
                }
                return false;
            }
            yylex();

            ExprAst *__node_41 = 0;
            if (!parseExpr(&__node_41))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_41;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_BIT_NOT
                 || yytoken == Token_CASE
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_DOT
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_POUND_SIGN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            Expr100Ast *__node_42 = 0;
            if (!parseExpr100(&__node_42))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr100Kind, "expr100");
                }
                return false;
            }
            (*yynode)->expr100 = __node_42;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr100(Expr100Ast **yynode)
{
    *yynode = create<Expr100Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr150Ast *__node_43 = 0;
        if (!parseExpr150(&__node_43))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr150Kind, "expr150");
            }
            return false;
        }
        (*yynode)->expr150 = __node_43;

        if (yytoken == Token_ASSIGN
            || yytoken == Token_EXCLAMATION)
        {
            if (yytoken == Token_ASSIGN)
            {
                if (yytoken != Token_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_EXCLAMATION)
            {
                if (yytoken != Token_EXCLAMATION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_EXCLAMATION, "!");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Expr100Ast *__node_44 = 0;
            if (!parseExpr100(&__node_44))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr100Kind, "expr100");
                }
                return false;
            }
            (*yynode)->expr100 = __node_44;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr150(Expr150Ast **yynode)
{
    *yynode = create<Expr150Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr160Ast *__node_45 = 0;
        if (!parseExpr160(&__node_45))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr160Kind, "expr160");
            }
            return false;
        }
        (*yynode)->expr160 = __node_45;

        if (yytoken == Token_ORELSE)
        {
            if (yytoken != Token_ORELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ORELSE, "orelse");
                }
                return false;
            }
            yylex();

            Expr150Ast *__node_46 = 0;
            if (!parseExpr150(&__node_46))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr150Kind, "expr150");
                }
                return false;
            }
            (*yynode)->expr150 = __node_46;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr160(Expr160Ast **yynode)
{
    *yynode = create<Expr160Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr200Ast *__node_47 = 0;
        if (!parseExpr200(&__node_47))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr200Kind, "expr200");
            }
            return false;
        }
        (*yynode)->expr120 = __node_47;

        if (yytoken == Token_ANDALSO)
        {
            if (yytoken != Token_ANDALSO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ANDALSO, "andalso");
                }
                return false;
            }
            yylex();

            Expr160Ast *__node_48 = 0;
            if (!parseExpr160(&__node_48))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr160Kind, "expr160");
                }
                return false;
            }
            (*yynode)->expr160 = __node_48;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr200(Expr200Ast **yynode)
{
    *yynode = create<Expr200Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr300Ast *__node_49 = 0;
        if (!parseExpr300(&__node_49))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr300Kind, "expr300");
            }
            return false;
        }
        (*yynode)->expr300 = __node_49;

        if (yytoken == Token_EXACT_EQUATIONAL
            || yytoken == Token_EXACT_NOT_EQUATIONAL
            || yytoken == Token_IS_EQUAL
            || yytoken == Token_IS_GREATER
            || yytoken == Token_IS_GREATER_OR_EQUAL
            || yytoken == Token_IS_NOT_EQUAL
            || yytoken == Token_IS_SMALLER
            || yytoken == Token_IS_SMALLER_OR_EQUAL)
        {
            CompOpAst *__node_50 = 0;
            if (!parseCompOp(&__node_50))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompOpKind, "compOp");
                }
                return false;
            }
            (*yynode)->comp_op = __node_50;

            Expr300Ast *__node_51 = 0;
            if (!parseExpr300(&__node_51))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr300Kind, "expr300");
                }
                return false;
            }
            (*yynode)->expr300 = __node_51;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr300(Expr300Ast **yynode)
{
    *yynode = create<Expr300Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr400Ast *__node_52 = 0;
        if (!parseExpr400(&__node_52))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr400Kind, "expr400");
            }
            return false;
        }
        (*yynode)->expr400 = __node_52;

        if (yytoken == Token_MINUS
            || yytoken == Token_PLUS)
        {
            ListOpAst *__node_53 = 0;
            if (!parseListOp(&__node_53))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ListOpKind, "listOp");
                }
                return false;
            }
            (*yynode)->list_op = __node_53;

            Expr300Ast *__node_54 = 0;
            if (!parseExpr300(&__node_54))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr300Kind, "expr300");
                }
                return false;
            }
            (*yynode)->expr300 = __node_54;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr400(Expr400Ast **yynode)
{
    *yynode = create<Expr400Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr500Ast *__node_55 = 0;
        if (!parseExpr500(&__node_55))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr500Kind, "expr500");
            }
            return false;
        }
        (*yynode)->expr500 = __node_55;

        Expr400aAst *__node_56 = 0;
        if (!parseExpr400a(&__node_56))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr400aKind, "expr400a");
            }
            return false;
        }
        (*yynode)->expr400a = __node_56;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr400a(Expr400aAst **yynode)
{
    *yynode = create<Expr400aAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BIT_OR
        || yytoken == Token_BIT_XOR
        || yytoken == Token_MINUS
        || yytoken == Token_OR
        || yytoken == Token_PLUS
        || yytoken == Token_SL
        || yytoken == Token_SR
        || yytoken == Token_XOR || yytoken == Token_AFTER
        || yytoken == Token_ANDALSO
        || yytoken == Token_ASSIGN
        || yytoken == Token_BINARY_CLOSE
        || yytoken == Token_CATCH
        || yytoken == Token_COMMA
        || yytoken == Token_DOT
        || yytoken == Token_DOUBLE_COLON
        || yytoken == Token_DOUBLE_PIPE
        || yytoken == Token_END
        || yytoken == Token_EOF
        || yytoken == Token_EXACT_EQUATIONAL
        || yytoken == Token_EXACT_NOT_EQUATIONAL
        || yytoken == Token_EXCLAMATION
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_IS_GREATER
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_LEADS_TO
        || yytoken == Token_LIST_COMPREHENSION_LEADS_TO
        || yytoken == Token_MINUS
        || yytoken == Token_OF
        || yytoken == Token_ORELSE
        || yytoken == Token_PIPE
        || yytoken == Token_PLUS
        || yytoken == Token_RBRACE
        || yytoken == Token_RBRACKET
        || yytoken == Token_RPAREN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_WHEN)
    {
        if (yytoken == Token_BIT_OR
            || yytoken == Token_BIT_XOR
            || yytoken == Token_MINUS
            || yytoken == Token_OR
            || yytoken == Token_PLUS
            || yytoken == Token_SL
            || yytoken == Token_SR
            || yytoken == Token_XOR)
        {
            AddOpAst *__node_57 = 0;
            if (!parseAddOp(&__node_57))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AddOpKind, "addOp");
                }
                return false;
            }
            (*yynode)->add_op = __node_57;

            Expr500Ast *__node_58 = 0;
            if (!parseExpr500(&__node_58))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr500Kind, "expr500");
                }
                return false;
            }
            (*yynode)->expr500 = __node_58;

            Expr400aAst *__node_59 = 0;
            if (!parseExpr400a(&__node_59))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr400aKind, "expr400a");
                }
                return false;
            }
            (*yynode)->expr400 = __node_59;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr500(Expr500Ast **yynode)
{
    *yynode = create<Expr500Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr600Ast *__node_60 = 0;
        if (!parseExpr600(&__node_60))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr600Kind, "expr600");
            }
            return false;
        }
        (*yynode)->expr600 = __node_60;

        Expr500aAst *__node_61 = 0;
        if (!parseExpr500a(&__node_61))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr500aKind, "expr500a");
            }
            return false;
        }
        (*yynode)->expr500 = __node_61;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr500a(Expr500aAst **yynode)
{
    *yynode = create<Expr500aAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_BIT_AND
        || yytoken == Token_FORWARD_SLASH
        || yytoken == Token_INT_DIV
        || yytoken == Token_INT_REM
        || yytoken == Token_MUL || yytoken == Token_AFTER
        || yytoken == Token_ANDALSO
        || yytoken == Token_ASSIGN
        || yytoken == Token_BINARY_CLOSE
        || yytoken == Token_BIT_OR
        || yytoken == Token_BIT_XOR
        || yytoken == Token_CATCH
        || yytoken == Token_COMMA
        || yytoken == Token_DOT
        || yytoken == Token_DOUBLE_COLON
        || yytoken == Token_DOUBLE_PIPE
        || yytoken == Token_END
        || yytoken == Token_EOF
        || yytoken == Token_EXACT_EQUATIONAL
        || yytoken == Token_EXACT_NOT_EQUATIONAL
        || yytoken == Token_EXCLAMATION
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_IS_GREATER
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_LEADS_TO
        || yytoken == Token_LIST_COMPREHENSION_LEADS_TO
        || yytoken == Token_MINUS
        || yytoken == Token_OF
        || yytoken == Token_OR
        || yytoken == Token_ORELSE
        || yytoken == Token_PIPE
        || yytoken == Token_PLUS
        || yytoken == Token_RBRACE
        || yytoken == Token_RBRACKET
        || yytoken == Token_RPAREN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SL
        || yytoken == Token_SR
        || yytoken == Token_WHEN
        || yytoken == Token_XOR)
    {
        if (yytoken == Token_AND
            || yytoken == Token_BIT_AND
            || yytoken == Token_FORWARD_SLASH
            || yytoken == Token_INT_DIV
            || yytoken == Token_INT_REM
            || yytoken == Token_MUL)
        {
            MultOpAst *__node_62 = 0;
            if (!parseMultOp(&__node_62))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MultOpKind, "multOp");
                }
                return false;
            }
            (*yynode)->mult_op = __node_62;

            Expr600Ast *__node_63 = 0;
            if (!parseExpr600(&__node_63))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr600Kind, "expr600");
                }
                return false;
            }
            (*yynode)->expr600 = __node_63;

            Expr500aAst *__node_64 = 0;
            if (!parseExpr500a(&__node_64))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr500aKind, "expr500a");
                }
                return false;
            }
            (*yynode)->expr500a = __node_64;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr600(Expr600Ast **yynode)
{
    *yynode = create<Expr600Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_BIT_NOT
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS)
        {
            PrefixOpAst *__node_65 = 0;
            if (!parsePrefixOp(&__node_65))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PrefixOpKind, "prefixOp");
                }
                return false;
            }
            (*yynode)->prefix_op = __node_65;

            Expr700Ast *__node_66 = 0;
            if (!parseExpr700(&__node_66))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr700Kind, "expr700");
                }
                return false;
            }
            (*yynode)->expr700 = __node_66;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_CASE
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_DOT
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_POUND_SIGN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            Expr700Ast *__node_67 = 0;
            if (!parseExpr700(&__node_67))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr700Kind, "expr700");
                }
                return false;
            }
            (*yynode)->expr700 = __node_67;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr700(Expr700Ast **yynode)
{
    *yynode = create<Expr700Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        bool blockErrors_2 = blockErrors(true);
        qint64 try_startToken_2 = tokenStream->index() - 1;
        ParserState *try_startState_2 = copyCurrentState();
        {
            RecordExprAst *__node_68 = 0;
            if (!parseRecordExpr(&__node_68))
            {
                goto __catch_2;
            }
            (*yynode)->record_expr = __node_68;

        }
        blockErrors(blockErrors_2);
        if (try_startState_2)
            delete try_startState_2;

        if (false) // the only way to enter here is using goto
        {
__catch_2:
            if (try_startState_2)
            {
                restoreState(try_startState_2);
                delete try_startState_2;
            }
            blockErrors(blockErrors_2);
            rewind(try_startToken_2);

            bool blockErrors_3 = blockErrors(true);
            qint64 try_startToken_3 = tokenStream->index() - 1;
            ParserState *try_startState_3 = copyCurrentState();
            {
                Expr800Ast *__node_69 = 0;
                if (!parseExpr800(&__node_69))
                {
                    goto __catch_3;
                }
                (*yynode)->expr800 = __node_69;

            }
            blockErrors(blockErrors_3);
            if (try_startState_3)
                delete try_startState_3;

            if (false) // the only way to enter here is using goto
            {
__catch_3:
                if (try_startState_3)
                {
                    restoreState(try_startState_3);
                    delete try_startState_3;
                }
                blockErrors(blockErrors_3);
                rewind(try_startToken_3);

                FunctionCallAst *__node_70 = 0;
                if (!parseFunctionCall(&__node_70))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunctionCallKind, "functionCall");
                    }
                    return false;
                }
                (*yynode)->functionCall = __node_70;

            }

        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr800(Expr800Ast **yynode)
{
    *yynode = create<Expr800Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr900Ast *__node_71 = 0;
        if (!parseExpr900(&__node_71))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr900Kind, "expr900");
            }
            return false;
        }
        (*yynode)->expr900 = __node_71;

        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ExprMaxAst *__node_72 = 0;
            if (!parseExprMax(&__node_72))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprMaxKind, "exprMax");
                }
                return false;
            }
            (*yynode)->expr_max = __node_72;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr900(Expr900Ast **yynode)
{
    *yynode = create<Expr900Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            Atom1Ast *__node_73 = 0;
            if (!parseAtom1(&__node_73))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            Expr900aAst *__node_74 = 0;
            if (!parseExpr900a(&__node_74))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr900aKind, "expr900a");
                }
                return false;
            }
            (*yynode)->expr900a = __node_74;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_CASE
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            ExprMaxAst *__node_75 = 0;
            if (!parseExprMax(&__node_75))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprMaxKind, "exprMax");
                }
                return false;
            }
            (*yynode)->expr_max = __node_75;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpr900a(Expr900aAst **yynode)
{
    *yynode = create<Expr900aAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE || yytoken == Token_AFTER
        || yytoken == Token_AND
        || yytoken == Token_ANDALSO
        || yytoken == Token_ASSIGN
        || yytoken == Token_BINARY_CLOSE
        || yytoken == Token_BIT_AND
        || yytoken == Token_BIT_OR
        || yytoken == Token_BIT_XOR
        || yytoken == Token_CATCH
        || yytoken == Token_COLON
        || yytoken == Token_COMMA
        || yytoken == Token_DOT
        || yytoken == Token_DOUBLE_COLON
        || yytoken == Token_DOUBLE_PIPE
        || yytoken == Token_END
        || yytoken == Token_EOF
        || yytoken == Token_EXACT_EQUATIONAL
        || yytoken == Token_EXACT_NOT_EQUATIONAL
        || yytoken == Token_EXCLAMATION
        || yytoken == Token_FORWARD_SLASH
        || yytoken == Token_INT_DIV
        || yytoken == Token_INT_REM
        || yytoken == Token_IS_EQUAL
        || yytoken == Token_IS_GREATER
        || yytoken == Token_IS_GREATER_OR_EQUAL
        || yytoken == Token_IS_NOT_EQUAL
        || yytoken == Token_IS_SMALLER
        || yytoken == Token_IS_SMALLER_OR_EQUAL
        || yytoken == Token_LEADS_TO
        || yytoken == Token_LIST_COMPREHENSION_LEADS_TO
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MUL
        || yytoken == Token_OF
        || yytoken == Token_OR
        || yytoken == Token_ORELSE
        || yytoken == Token_PIPE
        || yytoken == Token_PLUS
        || yytoken == Token_RBRACE
        || yytoken == Token_RBRACKET
        || yytoken == Token_RPAREN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SL
        || yytoken == Token_SR
        || yytoken == Token_WHEN
        || yytoken == Token_XOR)
    {
        if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            Atom1Ast *__node_76 = 0;
            if (!parseAtom1(&__node_76))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            Expr900aAst *__node_77 = 0;
            if (!parseExpr900a(&__node_77))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr900aKind, "expr900a");
                }
                return false;
            }
            (*yynode)->expr900a = __node_77;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_CASE
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            ExprMaxAst *__node_78 = 0;
            if (!parseExprMax(&__node_78))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprMaxKind, "exprMax");
                }
                return false;
            }
            (*yynode)->expr_max = __node_78;

            Expr900aAst *__node_79 = 0;
            if (!parseExpr900a(&__node_79))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expr900aKind, "expr900a");
                }
                return false;
            }
            (*yynode)->expr900a = __node_79;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExprMax(ExprMaxAst **yynode)
{
    *yynode = create<ExprMaxAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->variable = -1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_VARIABLE)
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            (*yynode)->variable = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_STRING_LITERAL)
        {
            AtomicAst *__node_80 = 0;
            if (!parseAtomic(&__node_80))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AtomicKind, "atomic");
                }
                return false;
            }
            (*yynode)->atomic = __node_80;

        }
        else if (yytoken == Token_BINARY_OPEN)
        {
            bool blockErrors_4 = blockErrors(true);
            qint64 try_startToken_4 = tokenStream->index() - 1;
            ParserState *try_startState_4 = copyCurrentState();
            {
                BinaryAst *__node_81 = 0;
                if (!parseBinary(&__node_81))
                {
                    goto __catch_4;
                }
                (*yynode)->binary = __node_81;

            }
            blockErrors(blockErrors_4);
            if (try_startState_4)
                delete try_startState_4;

            if (false) // the only way to enter here is using goto
            {
__catch_4:
                if (try_startState_4)
                {
                    restoreState(try_startState_4);
                    delete try_startState_4;
                }
                blockErrors(blockErrors_4);
                rewind(try_startToken_4);

                BinaryComprehensionAst *__node_82 = 0;
                if (!parseBinaryComprehension(&__node_82))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BinaryComprehensionKind, "binaryComprehension");
                    }
                    return false;
                }
                (*yynode)->binary_comprehension = __node_82;

            }

        }
        else if (yytoken == Token_LBRACKET)
        {
            bool blockErrors_5 = blockErrors(true);
            qint64 try_startToken_5 = tokenStream->index() - 1;
            ParserState *try_startState_5 = copyCurrentState();
            {
                if (yytoken != Token_LBRACKET)
                    goto __catch_5;
                yylex();

                if (yytoken == Token_ATOM_LITERAL
                    || yytoken == Token_BEGIN
                    || yytoken == Token_BINARY_OPEN
                    || yytoken == Token_BIT_NOT
                    || yytoken == Token_CASE
                    || yytoken == Token_CATCH
                    || yytoken == Token_CHAR_LITERAL
                    || yytoken == Token_DOT
                    || yytoken == Token_FLOAT_LITERAL
                    || yytoken == Token_FUN
                    || yytoken == Token_IF
                    || yytoken == Token_INTEGER_LITERAL
                    || yytoken == Token_LBRACE
                    || yytoken == Token_LBRACKET
                    || yytoken == Token_LPAREN
                    || yytoken == Token_MINUS
                    || yytoken == Token_NOT
                    || yytoken == Token_PLUS
                    || yytoken == Token_POUND_SIGN
                    || yytoken == Token_QUERY
                    || yytoken == Token_RECEIVE
                    || yytoken == Token_STRING_LITERAL
                    || yytoken == Token_TRY
                    || yytoken == Token_VARIABLE)
                {
                    ExprAst *__node_83 = 0;
                    if (!parseExpr(&__node_83))
                    {
                        goto __catch_5;
                    }
                    (*yynode)->expr = __node_83;

                    TailAst *__node_84 = 0;
                    if (!parseTail(&__node_84))
                    {
                        goto __catch_5;
                    }
                    (*yynode)->tail = __node_84;

                }
                else if (yytoken == Token_RBRACKET)
                {
                    if (yytoken != Token_RBRACKET)
                        goto __catch_5;
                    yylex();

                }
                else
                {
                    goto __catch_5;
                }
            }
            blockErrors(blockErrors_5);
            if (try_startState_5)
                delete try_startState_5;

            if (false) // the only way to enter here is using goto
            {
__catch_5:
                if (try_startState_5)
                {
                    restoreState(try_startState_5);
                    delete try_startState_5;
                }
                blockErrors(blockErrors_5);
                rewind(try_startToken_5);

                ListComprehensionAst *__node_85 = 0;
                if (!parseListComprehension(&__node_85))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ListComprehensionKind, "listComprehension");
                    }
                    return false;
                }
                (*yynode)->list_comprehension = __node_85;

            }

        }
        else if (yytoken == Token_LBRACE)
        {
            TupleAst *__node_86 = 0;
            if (!parseTuple(&__node_86))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TupleKind, "tuple");
                }
                return false;
            }
            (*yynode)->tuple = __node_86;

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExprAst *__node_87 = 0;
            if (!parseExpr(&__node_87))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_87;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BEGIN)
        {
            if (yytoken != Token_BEGIN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BEGIN, "begin");
                }
                return false;
            }
            yylex();

            ExprsAst *__node_88 = 0;
            if (!parseExprs(&__node_88))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprsKind, "exprs");
                }
                return false;
            }
            (*yynode)->exprs = __node_88;

            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IF)
        {
            IfExprAst *__node_89 = 0;
            if (!parseIfExpr(&__node_89))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IfExprKind, "ifExpr");
                }
                return false;
            }
            (*yynode)->if_expr = __node_89;

        }
        else if (yytoken == Token_CASE)
        {
            CaseExprAst *__node_90 = 0;
            if (!parseCaseExpr(&__node_90))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CaseExprKind, "caseExpr");
                }
                return false;
            }
            (*yynode)->case_expr = __node_90;

        }
        else if (yytoken == Token_RECEIVE)
        {
            ReceiveExprAst *__node_91 = 0;
            if (!parseReceiveExpr(&__node_91))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ReceiveExprKind, "receiveExpr");
                }
                return false;
            }
            (*yynode)->receive_expr = __node_91;

        }
        else if (yytoken == Token_FUN)
        {
            FunExprAst *__node_92 = 0;
            if (!parseFunExpr(&__node_92))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunExprKind, "funExpr");
                }
                return false;
            }
            (*yynode)->fun_expr = __node_92;

        }
        else if (yytoken == Token_TRY)
        {
            TryExprAst *__node_93 = 0;
            if (!parseTryExpr(&__node_93))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TryExprKind, "tryExpr");
                }
                return false;
            }
            (*yynode)->try_expr = __node_93;

        }
        else if (yytoken == Token_QUERY)
        {
            QueryExprAst *__node_94 = 0;
            if (!parseQueryExpr(&__node_94))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::QueryExprKind, "queryExpr");
                }
                return false;
            }
            (*yynode)->query_expr = __node_94;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExprOrTypedExpr(ExprOrTypedExprAst **yynode)
{
    *yynode = create<ExprOrTypedExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_DOUBLE_COLON
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_DOUBLE_COLON)
        {
            TypedExprAst *__node_95 = 0;
            if (!parseTypedExpr(&__node_95))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypedExprKind, "typedExpr");
                }
                return false;
            }
            (*yynode)->typed_expr = __node_95;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_BIT_NOT
                 || yytoken == Token_CASE
                 || yytoken == Token_CATCH
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_DOT
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_POUND_SIGN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            ExprAst *__node_96 = 0;
            if (!parseExpr(&__node_96))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_96;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExprs(ExprsAst **yynode)
{
    *yynode = create<ExprsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprAst *__node_97 = 0;
        if (!parseExpr(&__node_97))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->eSequence = snoc((*yynode)->eSequence, __node_97, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ExprAst *__node_98 = 0;
            if (!parseExpr(&__node_98))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->eSequence = snoc((*yynode)->eSequence, __node_98, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFieldType(FieldTypeAst **yynode)
{
    *yynode = create<FieldTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_99 = 0;
        if (!parseAtom1(&__node_99))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        if (yytoken != Token_DOUBLE_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOUBLE_COLON, "::");
            }
            return false;
        }
        yylex();

        TopTypeAst *__node_100 = 0;
        if (!parseTopType(&__node_100))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypeKind, "topType");
            }
            return false;
        }
        (*yynode)->top_type = __node_100;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFieldTypes(FieldTypesAst **yynode)
{
    *yynode = create<FieldTypesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        FieldTypeAst *__node_101 = 0;
        if (!parseFieldType(&__node_101))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FieldTypeKind, "fieldType");
            }
            return false;
        }
        (*yynode)->ftSequence = snoc((*yynode)->ftSequence, __node_101, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            FieldTypeAst *__node_102 = 0;
            if (!parseFieldType(&__node_102))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FieldTypeKind, "fieldType");
                }
                return false;
            }
            (*yynode)->ftSequence = snoc((*yynode)->ftSequence, __node_102, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFileDeclaration(FileDeclarationAst **yynode)
{
    *yynode = create<FileDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->file_name = -1;
    (*yynode)->line = -1;

    if (yytoken == Token_FILE_DIRECTIVE)
    {
        if (yytoken != Token_FILE_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FILE_DIRECTIVE, "file directive");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_STRING_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
            }
            return false;
        }
        (*yynode)->file_name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_COMMA)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COMMA, ",");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_INTEGER_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
            }
            return false;
        }
        (*yynode)->line = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForm(FormAst **yynode)
{
    *yynode = create<FormAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_MINUS
        || yytoken == Token_SPEC || yytoken == Token_EOF)
    {
        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_SPEC)
        {
            FunctionOrRuleAst *__node_103 = 0;
            if (!parseFunctionOrRule(&__node_103))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionOrRuleKind, "functionOrRule");
                }
                return false;
            }
            (*yynode)->functions = __node_103;

            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            FormAst *__node_104 = 0;
            if (!parseForm(&__node_104))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FormKind, "form");
                }
                return false;
            }
        }
        else if (yytoken == Token_MINUS)
        {
            AttributeAst *__node_105 = 0;
            if (!parseAttribute(&__node_105))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AttributeKind, "attribute");
                }
                return false;
            }
            (*yynode)->attribute = __node_105;

            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            FormAst *__node_106 = 0;
            if (!parseForm(&__node_106))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FormKind, "form");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunClause(FunClauseAst **yynode)
{
    *yynode = create<FunClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        ArgumentListAst *__node_107 = 0;
        if (!parseArgumentList(&__node_107))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ArgumentListKind, "argumentList");
            }
            return false;
        }
        (*yynode)->argument_list = __node_107;

        ClauseGuardAst *__node_108 = 0;
        if (!parseClauseGuard(&__node_108))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseGuardKind, "clauseGuard");
            }
            return false;
        }
        (*yynode)->clause_guard = __node_108;

        ClauseBodyAst *__node_109 = 0;
        if (!parseClauseBody(&__node_109))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
            }
            return false;
        }
        (*yynode)->clause_body = __node_109;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunClauses(FunClausesAst **yynode)
{
    *yynode = create<FunClausesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        FunClauseAst *__node_110 = 0;
        if (!parseFunClause(&__node_110))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FunClauseKind, "funClause");
            }
            return false;
        }
        (*yynode)->fcSequence = snoc((*yynode)->fcSequence, __node_110, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            FunClauseAst *__node_111 = 0;
            if (!parseFunClause(&__node_111))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunClauseKind, "funClause");
                }
                return false;
            }
            (*yynode)->fcSequence = snoc((*yynode)->fcSequence, __node_111, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunExpr(FunExprAst **yynode)
{
    *yynode = create<FunExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FUN)
    {
        if (yytoken != Token_FUN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FUN, "fun");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_SPEC)
        {
            Atom1Ast *__node_112 = 0;
            if (!parseAtom1(&__node_112))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken == Token_FORWARD_SLASH)
            {
                if (yytoken != Token_FORWARD_SLASH)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FORWARD_SLASH, "/");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_INTEGER_LITERAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_COLON)
            {
                if (yytoken != Token_COLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COLON, ":");
                    }
                    return false;
                }
                yylex();

                Atom1Ast *__node_113 = 0;
                if (!parseAtom1(&__node_113))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Atom1Kind, "atom1");
                    }
                    return false;
                }
                if (yytoken != Token_FORWARD_SLASH)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FORWARD_SLASH, "/");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_INTEGER_LITERAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LPAREN)
        {
            FunClausesAst *__node_114 = 0;
            if (!parseFunClauses(&__node_114))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunClausesKind, "funClauses");
                }
                return false;
            }
            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunType(FunTypeAst **yynode)
{
    *yynode = create<FunTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_BINARY_OPEN
            || yytoken == Token_FUN
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET
            || yytoken == Token_LPAREN
            || yytoken == Token_POUND_SIGN
            || yytoken == Token_SPEC
            || yytoken == Token_VARIABLE)
        {
            TopTypesAst *__node_115 = 0;
            if (!parseTopTypes(&__node_115))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopTypesKind, "topTypes");
                }
                return false;
            }
            (*yynode)->top_types = __node_115;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LEADS_TO)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LEADS_TO, "->");
            }
            return false;
        }
        yylex();

        TopTypeAst *__node_116 = 0;
        if (!parseTopType(&__node_116))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypeKind, "topType");
            }
            return false;
        }
        (*yynode)->top_type = __node_116;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunType100(FunType100Ast **yynode)
{
    *yynode = create<FunType100Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_FUN
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_POUND_SIGN
                 || yytoken == Token_SPEC
                 || yytoken == Token_VARIABLE)
        {
            TopTypesAst *__node_117 = 0;
            if (!parseTopTypes(&__node_117))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopTypesKind, "topTypes");
                }
                return false;
            }
            (*yynode)->top_types = __node_117;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LEADS_TO)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LEADS_TO, "->");
            }
            return false;
        }
        yylex();

        TopTypeAst *__node_118 = 0;
        if (!parseTopType(&__node_118))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypeKind, "topType");
            }
            return false;
        }
        (*yynode)->top_type = __node_118;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionCall(FunctionCallAst **yynode)
{
    *yynode = create<FunctionCallAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        Expr800Ast *__node_119 = 0;
        if (!parseExpr800(&__node_119))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Expr800Kind, "expr800");
            }
            return false;
        }
        (*yynode)->expr800 = __node_119;

        ArgumentListAst *__node_120 = 0;
        if (!parseArgumentList(&__node_120))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ArgumentListKind, "argumentList");
            }
            return false;
        }
        (*yynode)->argument_list = __node_120;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionOrRule(FunctionOrRuleAst **yynode)
{
    *yynode = create<FunctionOrRuleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        FunctionOrRuleClauseAst *__node_121 = 0;
        if (!parseFunctionOrRuleClause(&__node_121))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FunctionOrRuleClauseKind, "functionOrRuleClause");
            }
            return false;
        }
        (*yynode)->fcSequence = snoc((*yynode)->fcSequence, __node_121, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            FunctionOrRuleClauseAst *__node_122 = 0;
            if (!parseFunctionOrRuleClause(&__node_122))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionOrRuleClauseKind, "functionOrRuleClause");
                }
                return false;
            }
            (*yynode)->fcSequence = snoc((*yynode)->fcSequence, __node_122, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionOrRuleClause(FunctionOrRuleClauseAst **yynode)
{
    *yynode = create<FunctionOrRuleClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_123 = 0;
        if (!parseAtom1(&__node_123))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        (*yynode)->function_name = __node_123;

        ClauseArgsAst *__node_124 = 0;
        if (!parseClauseArgs(&__node_124))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseArgsKind, "clauseArgs");
            }
            return false;
        }
        (*yynode)->clause_args = __node_124;

        ClauseGuardAst *__node_125 = 0;
        if (!parseClauseGuard(&__node_125))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseGuardKind, "clauseGuard");
            }
            return false;
        }
        (*yynode)->clause_guard = __node_125;

        if (yytoken == Token_LEADS_TO)
        {
            ClauseBodyAst *__node_126 = 0;
            if (!parseClauseBody(&__node_126))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
                }
                return false;
            }
            (*yynode)->body = __node_126;

        }
        else if (yytoken == Token_COLON)
        {
            RuleBodyAst *__node_127 = 0;
            if (!parseRuleBody(&__node_127))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RuleBodyKind, "ruleBody");
                }
                return false;
            }
            (*yynode)->rule_body = __node_127;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionSlashArity(FunctionSlashArityAst **yynode)
{
    *yynode = create<FunctionSlashArityAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->function_name = -1;
    (*yynode)->function_arity = -1;

    if (yytoken == Token_ATOM_LITERAL)
    {
        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        (*yynode)->function_name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_FORWARD_SLASH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FORWARD_SLASH, "/");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_INTEGER_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
            }
            return false;
        }
        (*yynode)->function_arity = tokenStream->index() - 1;
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseGuard(GuardAst **yynode)
{
    *yynode = create<GuardAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprsAst *__node_128 = 0;
        if (!parseExprs(&__node_128))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprsKind, "exprs");
            }
            return false;
        }
        (*yynode)->expr = __node_128;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

        GuardAst *__node_129 = 0;
        if (!parseGuard(&__node_129))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::GuardKind, "guard");
            }
            return false;
        }
        (*yynode)->guard = __node_129;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfClause(IfClauseAst **yynode)
{
    *yynode = create<IfClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        GuardAst *__node_130 = 0;
        if (!parseGuard(&__node_130))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::GuardKind, "guard");
            }
            return false;
        }
        (*yynode)->guard = __node_130;

        ClauseBodyAst *__node_131 = 0;
        if (!parseClauseBody(&__node_131))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
            }
            return false;
        }
        (*yynode)->clause_body = __node_131;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfClauses(IfClausesAst **yynode)
{
    *yynode = create<IfClausesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        IfClauseAst *__node_132 = 0;
        if (!parseIfClause(&__node_132))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IfClauseKind, "ifClause");
            }
            return false;
        }
        (*yynode)->icSequence = snoc((*yynode)->icSequence, __node_132, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            IfClauseAst *__node_133 = 0;
            if (!parseIfClause(&__node_133))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IfClauseKind, "ifClause");
                }
                return false;
            }
            (*yynode)->icSequence = snoc((*yynode)->icSequence, __node_133, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfExpr(IfExprAst **yynode)
{
    *yynode = create<IfExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF)
    {
        if (yytoken != Token_IF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IF, "if");
            }
            return false;
        }
        yylex();

        IfClausesAst *__node_134 = 0;
        if (!parseIfClauses(&__node_134))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IfClausesKind, "ifClauses");
            }
            return false;
        }
        (*yynode)->if_clauses = __node_134;

        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseImportDeclaration(ImportDeclarationAst **yynode)
{
    *yynode = create<ImportDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->module_name = -1;

    if (yytoken == Token_IMPORT_DIRECTIVE)
    {
        if (yytoken != Token_IMPORT_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IMPORT_DIRECTIVE, "import");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        (*yynode)->module_name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_COMMA)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COMMA, ",");
            }
            return false;
        }
        yylex();

        FunctionSlashArityAst *__node_135 = 0;
        if (!parseFunctionSlashArity(&__node_135))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FunctionSlashArityKind, "functionSlashArity");
            }
            return false;
        }
        (*yynode)->imported_functionsSequence = snoc((*yynode)->imported_functionsSequence, __node_135, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            FunctionSlashArityAst *__node_136 = 0;
            if (!parseFunctionSlashArity(&__node_136))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::FunctionSlashArityKind, "functionSlashArity");
                }
                return false;
            }
            (*yynode)->imported_functionsSequence = snoc((*yynode)->imported_functionsSequence, __node_136, memoryPool);

        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_DOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOT, ".");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLcExpr(LcExprAst **yynode)
{
    *yynode = create<LcExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        bool blockErrors_6 = blockErrors(true);
        qint64 try_startToken_6 = tokenStream->index() - 1;
        ParserState *try_startState_6 = copyCurrentState();
        {
            ExprAst *__node_137 = 0;
            if (!parseExpr(&__node_137))
            {
                goto __catch_6;
            }
            (*yynode)->expr = __node_137;

            if (yytoken == Token_LIST_COMPREHENSION_LEADS_TO)
            {
                if (yytoken != Token_LIST_COMPREHENSION_LEADS_TO)
                    goto __catch_6;
                yylex();

                ExprAst *__node_138 = 0;
                if (!parseExpr(&__node_138))
                {
                    goto __catch_6;
                }
                (*yynode)->expr = __node_138;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                goto __catch_6;
            }
        }
        blockErrors(blockErrors_6);
        if (try_startState_6)
            delete try_startState_6;

        if (false) // the only way to enter here is using goto
        {
__catch_6:
            if (try_startState_6)
            {
                restoreState(try_startState_6);
                delete try_startState_6;
            }
            blockErrors(blockErrors_6);
            rewind(try_startToken_6);

            BinaryAst *__node_139 = 0;
            if (!parseBinary(&__node_139))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BinaryKind, "binary");
                }
                return false;
            }
            (*yynode)->binary = __node_139;

            if (yytoken != Token_LIST_COMPREHENSION_LEADS_TO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LIST_COMPREHENSION_LEADS_TO, "<-");
                }
                return false;
            }
            yylex();

            ExprAst *__node_140 = 0;
            if (!parseExpr(&__node_140))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_140;

        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLcExprs(LcExprsAst **yynode)
{
    *yynode = create<LcExprsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        LcExprAst *__node_141 = 0;
        if (!parseLcExpr(&__node_141))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LcExprKind, "lcExpr");
            }
            return false;
        }
        (*yynode)->lcSequence = snoc((*yynode)->lcSequence, __node_141, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            LcExprAst *__node_142 = 0;
            if (!parseLcExpr(&__node_142))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LcExprKind, "lcExpr");
                }
                return false;
            }
            (*yynode)->lcSequence = snoc((*yynode)->lcSequence, __node_142, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseListComprehension(ListComprehensionAst **yynode)
{
    *yynode = create<ListComprehensionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET)
    {
        if (yytoken != Token_LBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACKET, "[");
            }
            return false;
        }
        yylex();

        ExprAst *__node_143 = 0;
        if (!parseExpr(&__node_143))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->expr = __node_143;

        if (yytoken != Token_DOUBLE_PIPE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOUBLE_PIPE, "||");
            }
            return false;
        }
        yylex();

        LcExprsAst *__node_144 = 0;
        if (!parseLcExprs(&__node_144))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LcExprsKind, "lcExprs");
            }
            return false;
        }
        (*yynode)->lc_exprs = __node_144;

        if (yytoken != Token_RBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACKET, "]");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseListOp(ListOpAst **yynode)
{
    *yynode = create<ListOpAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MINUS
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseModuleDeclaration(ModuleDeclarationAst **yynode)
{
    *yynode = create<ModuleDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->module_name = -1;

    if (yytoken == Token_MODULE_DIRECTIVE)
    {
        if (yytoken != Token_MODULE_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MODULE_DIRECTIVE, "module");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        (*yynode)->module_name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultOp(MultOpAst **yynode)
{
    *yynode = create<MultOpAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_BIT_AND
        || yytoken == Token_FORWARD_SLASH
        || yytoken == Token_INT_DIV
        || yytoken == Token_INT_REM
        || yytoken == Token_MUL)
    {
        if (yytoken == Token_FORWARD_SLASH)
        {
            if (yytoken != Token_FORWARD_SLASH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FORWARD_SLASH, "/");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MUL)
        {
            if (yytoken != Token_MUL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MUL, "*");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INT_DIV)
        {
            if (yytoken != Token_INT_DIV)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INT_DIV, "div");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INT_REM)
        {
            if (yytoken != Token_INT_REM)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INT_REM, "rem");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "band");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_AND)
        {
            if (yytoken != Token_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND, "and");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptBitSizeExpr(OptBitSizeExprAst **yynode)
{
    *yynode = create<OptBitSizeExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON || yytoken == Token_BINARY_CLOSE
        || yytoken == Token_COMMA
        || yytoken == Token_EOF
        || yytoken == Token_FORWARD_SLASH)
    {
        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            BitSizeExprAst *__node_145 = 0;
            if (!parseBitSizeExpr(&__node_145))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitSizeExprKind, "bitSizeExpr");
                }
                return false;
            }
            (*yynode)->bit_size_expr = __node_145;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptBitTypeList(OptBitTypeListAst **yynode)
{
    *yynode = create<OptBitTypeListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FORWARD_SLASH || yytoken == Token_BINARY_CLOSE
        || yytoken == Token_COMMA
        || yytoken == Token_EOF)
    {
        if (yytoken == Token_FORWARD_SLASH)
        {
            if (yytoken != Token_FORWARD_SLASH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FORWARD_SLASH, "/");
                }
                return false;
            }
            yylex();

            BitTypeListAst *__node_146 = 0;
            if (!parseBitTypeList(&__node_146))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitTypeListKind, "bitTypeList");
                }
                return false;
            }
            (*yynode)->bit_type_list = __node_146;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrefixOp(PrefixOpAst **yynode)
{
    *yynode = create<PrefixOpAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BIT_NOT
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BIT_NOT)
        {
            if (yytoken != Token_BIT_NOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_NOT, "bnot");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NOT)
        {
            if (yytoken != Token_NOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NOT, "not");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseQueryExpr(QueryExprAst **yynode)
{
    *yynode = create<QueryExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_QUERY)
    {
        if (yytoken != Token_QUERY)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_QUERY, "query");
            }
            return false;
        }
        yylex();

        ListComprehensionAst *__node_147 = 0;
        if (!parseListComprehension(&__node_147))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ListComprehensionKind, "listComprehension");
            }
            return false;
        }
        (*yynode)->list_comprehension = __node_147;

        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseReceiveExpr(ReceiveExprAst **yynode)
{
    *yynode = create<ReceiveExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_RECEIVE)
    {
        if (yytoken != Token_RECEIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RECEIVE, "receive");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY_OPEN
            || yytoken == Token_BIT_NOT
            || yytoken == Token_CASE
            || yytoken == Token_CATCH
            || yytoken == Token_CHAR_LITERAL
            || yytoken == Token_DOT
            || yytoken == Token_FLOAT_LITERAL
            || yytoken == Token_FUN
            || yytoken == Token_IF
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET
            || yytoken == Token_LPAREN
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS
            || yytoken == Token_POUND_SIGN
            || yytoken == Token_QUERY
            || yytoken == Token_RECEIVE
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TRY
            || yytoken == Token_VARIABLE)
        {
            CrClausesAst *__node_148 = 0;
            if (!parseCrClauses(&__node_148))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CrClausesKind, "crClauses");
                }
                return false;
            }
            (*yynode)->cr_clauses = __node_148;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_AFTER)
        {
            if (yytoken != Token_AFTER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AFTER, "after");
                }
                return false;
            }
            yylex();

            ClauseBodyAst *__node_149 = 0;
            if (!parseClauseBody(&__node_149))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
                }
                return false;
            }
            (*yynode)->clause_body = __node_149;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRecordDeclaration(RecordDeclarationAst **yynode)
{
    *yynode = create<RecordDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->record_name = -1;

    if (yytoken == Token_RECORD_DIRECTIVE)
    {
        if (yytoken != Token_RECORD_DIRECTIVE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RECORD_DIRECTIVE, "record");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_ATOM_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
            }
            return false;
        }
        (*yynode)->record_name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_COMMA)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COMMA, ",");
            }
            return false;
        }
        yylex();

        TypedRecordFieldsAst *__node_150 = 0;
        if (!parseTypedRecordFields(&__node_150))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypedRecordFieldsKind, "typedRecordFields");
            }
            return false;
        }
        (*yynode)->type_record_fields = __node_150;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRecordExpr(RecordExprAst **yynode)
{
    *yynode = create<RecordExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_CASE
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_POUND_SIGN)
        {
            if (yytoken != Token_POUND_SIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_POUND_SIGN, "#");
                }
                return false;
            }
            yylex();

            Atom1Ast *__node_151 = 0;
            if (!parseAtom1(&__node_151))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken == Token_DOT)
            {
                if (yytoken != Token_DOT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOT, ".");
                    }
                    return false;
                }
                yylex();

                Atom1Ast *__node_152 = 0;
                if (!parseAtom1(&__node_152))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Atom1Kind, "atom1");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LBRACE)
            {
                RecordTupleAst *__node_153 = 0;
                if (!parseRecordTuple(&__node_153))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RecordTupleKind, "recordTuple");
                    }
                    return false;
                }
                (*yynode)->record_tuple = __node_153;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_CASE
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            ExprMaxAst *__node_154 = 0;
            if (!parseExprMax(&__node_154))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprMaxKind, "exprMax");
                }
                return false;
            }
            (*yynode)->expr_max = __node_154;

            if (yytoken != Token_POUND_SIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_POUND_SIGN, "#");
                }
                return false;
            }
            yylex();

            Atom1Ast *__node_155 = 0;
            if (!parseAtom1(&__node_155))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken == Token_DOT)
            {
                if (yytoken != Token_DOT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOT, ".");
                    }
                    return false;
                }
                yylex();

                Atom1Ast *__node_156 = 0;
                if (!parseAtom1(&__node_156))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Atom1Kind, "atom1");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LBRACE)
            {
                RecordTupleAst *__node_157 = 0;
                if (!parseRecordTuple(&__node_157))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RecordTupleKind, "recordTuple");
                    }
                    return false;
                }
                (*yynode)->record_tuple = __node_157;

            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRecordField(RecordFieldAst **yynode)
{
    *yynode = create<RecordFieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_VARIABLE)
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            ExprAst *__node_158 = 0;
            if (!parseExpr(&__node_158))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_158;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_SPEC)
        {
            Atom1Ast *__node_159 = 0;
            if (!parseAtom1(&__node_159))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            ExprAst *__node_160 = 0;
            if (!parseExpr(&__node_160))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_160;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRecordFields(RecordFieldsAst **yynode)
{
    *yynode = create<RecordFieldsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        RecordFieldAst *__node_161 = 0;
        if (!parseRecordField(&__node_161))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RecordFieldKind, "recordField");
            }
            return false;
        }
        (*yynode)->rfSequence = snoc((*yynode)->rfSequence, __node_161, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            RecordFieldAst *__node_162 = 0;
            if (!parseRecordField(&__node_162))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RecordFieldKind, "recordField");
                }
                return false;
            }
            (*yynode)->rfSequence = snoc((*yynode)->rfSequence, __node_162, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRecordTuple(RecordTupleAst **yynode)
{
    *yynode = create<RecordTupleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_SPEC
            || yytoken == Token_VARIABLE)
        {
            RecordFieldsAst *__node_163 = 0;
            if (!parseRecordFields(&__node_163))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RecordFieldsKind, "recordFields");
                }
                return false;
            }
            (*yynode)->record_fields = __node_163;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRuleBody(RuleBodyAst **yynode)
{
    *yynode = create<RuleBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON)
    {
        if (yytoken != Token_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON, ":");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_MINUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MINUS, "-");
            }
            return false;
        }
        yylex();

        LcExprsAst *__node_164 = 0;
        if (!parseLcExprs(&__node_164))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LcExprsKind, "lcExprs");
            }
            return false;
        }
        (*yynode)->lc_exprs = __node_164;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRuleClause(RuleClauseAst **yynode)
{
    *yynode = create<RuleClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_165 = 0;
        if (!parseAtom1(&__node_165))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        ClauseArgsAst *__node_166 = 0;
        if (!parseClauseArgs(&__node_166))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseArgsKind, "clauseArgs");
            }
            return false;
        }
        (*yynode)->clause_args = __node_166;

        ClauseGuardAst *__node_167 = 0;
        if (!parseClauseGuard(&__node_167))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseGuardKind, "clauseGuard");
            }
            return false;
        }
        (*yynode)->clause_guard = __node_167;

        RuleBodyAst *__node_168 = 0;
        if (!parseRuleBody(&__node_168))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RuleBodyKind, "ruleBody");
            }
            return false;
        }
        (*yynode)->rule_body = __node_168;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRuleClauses(RuleClausesAst **yynode)
{
    *yynode = create<RuleClausesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        RuleClauseAst *__node_169 = 0;
        if (!parseRuleClause(&__node_169))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RuleClauseKind, "ruleClause");
            }
            return false;
        }
        (*yynode)->rcSequence = snoc((*yynode)->rcSequence, __node_169, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            RuleClauseAst *__node_170 = 0;
            if (!parseRuleClause(&__node_170))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RuleClauseKind, "ruleClause");
                }
                return false;
            }
            (*yynode)->rcSequence = snoc((*yynode)->rcSequence, __node_170, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSpecFun(SpecFunAst **yynode)
{
    *yynode = create<SpecFunAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_171 = 0;
        if (!parseAtom1(&__node_171))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_ATOM_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ATOM_LITERAL, "atom literal");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTail(TailAst **yynode)
{
    *yynode = create<TailAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COMMA
        || yytoken == Token_PIPE
        || yytoken == Token_RBRACKET)
    {
        if (yytoken == Token_RBRACKET)
        {
            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_PIPE)
        {
            if (yytoken != Token_PIPE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PIPE, "|");
                }
                return false;
            }
            yylex();

            ExprAst *__node_172 = 0;
            if (!parseExpr(&__node_172))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_172;

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ExprAst *__node_173 = 0;
            if (!parseExpr(&__node_173))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_173;

            TailAst *__node_174 = 0;
            if (!parseTail(&__node_174))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TailKind, "tail");
                }
                return false;
            }
            (*yynode)->tail = __node_174;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTopType(TopTypeAst **yynode)
{
    *yynode = create<TopTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_FUN
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_VARIABLE)
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_DOUBLE_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_COLON, "::");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        TopType100Ast *__node_175 = 0;
        if (!parseTopType100(&__node_175))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopType100Kind, "topType100");
            }
            return false;
        }
        (*yynode)->top_type100 = __node_175;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTopType100(TopType100Ast **yynode)
{
    *yynode = create<TopType100Ast>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_FUN
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        TypeAst *__node_176 = 0;
        if (!parseType(&__node_176))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeKind, "type");
            }
            return false;
        }
        (*yynode)->type = __node_176;

        if (yytoken == Token_PIPE)
        {
            if (yytoken != Token_PIPE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PIPE, "|");
                }
                return false;
            }
            yylex();

            TopType100Ast *__node_177 = 0;
            if (!parseTopType100(&__node_177))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopType100Kind, "topType100");
                }
                return false;
            }
            (*yynode)->top_type100 = __node_177;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTopTypes(TopTypesAst **yynode)
{
    *yynode = create<TopTypesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_FUN
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        TopTypeAst *__node_178 = 0;
        if (!parseTopType(&__node_178))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypeKind, "topType");
            }
            return false;
        }
        (*yynode)->ttSequence = snoc((*yynode)->ttSequence, __node_178, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            TopTypeAst *__node_179 = 0;
            if (!parseTopType(&__node_179))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopTypeKind, "topType");
                }
                return false;
            }
            (*yynode)->ttSequence = snoc((*yynode)->ttSequence, __node_179, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTryCatch(TryCatchAst **yynode)
{
    *yynode = create<TryCatchAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AFTER
        || yytoken == Token_CATCH)
    {
        if (yytoken == Token_CATCH)
        {
            if (yytoken != Token_CATCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CATCH, "catch");
                }
                return false;
            }
            yylex();

            TryClausesAst *__node_180 = 0;
            if (!parseTryClauses(&__node_180))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TryClausesKind, "tryClauses");
                }
                return false;
            }
            (*yynode)->try_clauses = __node_180;

            if (yytoken == Token_AFTER)
            {
                if (yytoken != Token_AFTER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_AFTER, "after");
                    }
                    return false;
                }
                yylex();

                ExprsAst *__node_181 = 0;
                if (!parseExprs(&__node_181))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExprsKind, "exprs");
                    }
                    return false;
                }
                (*yynode)->exprs = __node_181;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_AFTER)
        {
            if (yytoken != Token_AFTER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AFTER, "after");
                }
                return false;
            }
            yylex();

            ExprsAst *__node_182 = 0;
            if (!parseExprs(&__node_182))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprsKind, "exprs");
                }
                return false;
            }
            (*yynode)->exprs = __node_182;

            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTryClause(TryClauseAst **yynode)
{
    *yynode = create<TryClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_SPEC
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        if ((yytoken == Token_ATOM_LITERAL
             || yytoken == Token_SPEC) && (LA(2).kind == Token_COLON))
        {
            Atom1Ast *__node_183 = 0;
            if (!parseAtom1(&__node_183))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ExprAst *__node_184 = 0;
            if (!parseExpr(&__node_184))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_184;

        }
        else if ((yytoken == Token_VARIABLE) && (LA(2).kind == Token_COLON))
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ExprAst *__node_185 = 0;
            if (!parseExpr(&__node_185))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_185;

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY_OPEN
                 || yytoken == Token_BIT_NOT
                 || yytoken == Token_CASE
                 || yytoken == Token_CATCH
                 || yytoken == Token_CHAR_LITERAL
                 || yytoken == Token_DOT
                 || yytoken == Token_FLOAT_LITERAL
                 || yytoken == Token_FUN
                 || yytoken == Token_IF
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LBRACE
                 || yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_POUND_SIGN
                 || yytoken == Token_QUERY
                 || yytoken == Token_RECEIVE
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TRY
                 || yytoken == Token_VARIABLE)
        {
            ExprAst *__node_186 = 0;
            if (!parseExpr(&__node_186))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprKind, "expr");
                }
                return false;
            }
            (*yynode)->expr = __node_186;

        }
        else
        {
            return false;
        }
        ClauseGuardAst *__node_187 = 0;
        if (!parseClauseGuard(&__node_187))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseGuardKind, "clauseGuard");
            }
            return false;
        }
        (*yynode)->clause_guard = __node_187;

        ClauseBodyAst *__node_188 = 0;
        if (!parseClauseBody(&__node_188))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClauseBodyKind, "clauseBody");
            }
            return false;
        }
        (*yynode)->clause_body = __node_188;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTryClauses(TryClausesAst **yynode)
{
    *yynode = create<TryClausesAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_SPEC
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        TryClauseAst *__node_189 = 0;
        if (!parseTryClause(&__node_189))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TryClauseKind, "tryClause");
            }
            return false;
        }
        (*yynode)->tcSequence = snoc((*yynode)->tcSequence, __node_189, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            TryClauseAst *__node_190 = 0;
            if (!parseTryClause(&__node_190))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TryClauseKind, "tryClause");
                }
                return false;
            }
            (*yynode)->tcSequence = snoc((*yynode)->tcSequence, __node_190, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTryExpr(TryExprAst **yynode)
{
    *yynode = create<TryExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_TRY)
    {
        if (yytoken != Token_TRY)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_TRY, "try");
            }
            return false;
        }
        yylex();

        ExprsAst *__node_191 = 0;
        if (!parseExprs(&__node_191))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprsKind, "exprs");
            }
            return false;
        }
        (*yynode)->exprs = __node_191;

        if (yytoken == Token_OF)
        {
            if (yytoken != Token_OF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OF, "of");
                }
                return false;
            }
            yylex();

            CrClausesAst *__node_192 = 0;
            if (!parseCrClauses(&__node_192))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CrClausesKind, "crClauses");
                }
                return false;
            }
            (*yynode)->cr_clauses = __node_192;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        TryCatchAst *__node_193 = 0;
        if (!parseTryCatch(&__node_193))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TryCatchKind, "tryCatch");
            }
            return false;
        }
        (*yynode)->try_catch = __node_193;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTuple(TupleAst **yynode)
{
    *yynode = create<TupleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ATOM_LITERAL
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY_OPEN
            || yytoken == Token_BIT_NOT
            || yytoken == Token_CASE
            || yytoken == Token_CATCH
            || yytoken == Token_CHAR_LITERAL
            || yytoken == Token_DOT
            || yytoken == Token_FLOAT_LITERAL
            || yytoken == Token_FUN
            || yytoken == Token_IF
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET
            || yytoken == Token_LPAREN
            || yytoken == Token_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS
            || yytoken == Token_POUND_SIGN
            || yytoken == Token_QUERY
            || yytoken == Token_RECEIVE
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TRY
            || yytoken == Token_VARIABLE)
        {
            ExprsAst *__node_194 = 0;
            if (!parseExprs(&__node_194))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprsKind, "exprs");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType(TypeAst **yynode)
{
    *yynode = create<TypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_FUN
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_SPEC
        || yytoken == Token_VARIABLE)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            TopTypeAst *__node_195 = 0;
            if (!parseTopType(&__node_195))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopTypeKind, "topType");
                }
                return false;
            }
            (*yynode)->top_type = __node_195;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VARIABLE)
        {
            if (yytoken != Token_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VARIABLE, "variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ATOM_LITERAL
                 || yytoken == Token_SPEC)
        {
            Atom1Ast *__node_196 = 0;
            if (!parseAtom1(&__node_196))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_ATOM_LITERAL
                    || yytoken == Token_BINARY_OPEN
                    || yytoken == Token_FUN
                    || yytoken == Token_INTEGER_LITERAL
                    || yytoken == Token_LBRACE
                    || yytoken == Token_LBRACKET
                    || yytoken == Token_LPAREN
                    || yytoken == Token_POUND_SIGN
                    || yytoken == Token_SPEC
                    || yytoken == Token_VARIABLE)
                {
                    TopTypesAst *__node_197 = 0;
                    if (!parseTopTypes(&__node_197))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TopTypesKind, "topTypes");
                        }
                        return false;
                    }
                    (*yynode)->top_types = __node_197;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_COLON)
            {
                if (yytoken != Token_COLON)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COLON, ":");
                    }
                    return false;
                }
                yylex();

                Atom1Ast *__node_198 = 0;
                if (!parseAtom1(&__node_198))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Atom1Kind, "atom1");
                    }
                    return false;
                }
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_ATOM_LITERAL
                    || yytoken == Token_BINARY_OPEN
                    || yytoken == Token_FUN
                    || yytoken == Token_INTEGER_LITERAL
                    || yytoken == Token_LBRACE
                    || yytoken == Token_LBRACKET
                    || yytoken == Token_LPAREN
                    || yytoken == Token_POUND_SIGN
                    || yytoken == Token_SPEC
                    || yytoken == Token_VARIABLE)
                {
                    TopTypesAst *__node_199 = 0;
                    if (!parseTopTypes(&__node_199))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TopTypesKind, "topTypes");
                        }
                        return false;
                    }
                    (*yynode)->top_types = __node_199;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ATOM_LITERAL
                || yytoken == Token_BINARY_OPEN
                || yytoken == Token_FUN
                || yytoken == Token_INTEGER_LITERAL
                || yytoken == Token_LBRACE
                || yytoken == Token_LBRACKET
                || yytoken == Token_LPAREN
                || yytoken == Token_POUND_SIGN
                || yytoken == Token_SPEC
                || yytoken == Token_VARIABLE)
            {
                TopTypeAst *__node_200 = 0;
                if (!parseTopType(&__node_200))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TopTypeKind, "topType");
                    }
                    return false;
                }
                (*yynode)->top_type = __node_200;

                if (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken != Token_DOT)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_DOT, ".");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken != Token_DOT)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_DOT, ".");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken != Token_DOT)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_DOT, ".");
                        }
                        return false;
                    }
                    yylex();

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ATOM_LITERAL
                || yytoken == Token_BINARY_OPEN
                || yytoken == Token_FUN
                || yytoken == Token_INTEGER_LITERAL
                || yytoken == Token_LBRACE
                || yytoken == Token_LBRACKET
                || yytoken == Token_LPAREN
                || yytoken == Token_POUND_SIGN
                || yytoken == Token_SPEC
                || yytoken == Token_VARIABLE)
            {
                TopTypesAst *__node_201 = 0;
                if (!parseTopTypes(&__node_201))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TopTypesKind, "topTypes");
                    }
                    return false;
                }
                (*yynode)->top_types = __node_201;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_POUND_SIGN)
        {
            if (yytoken != Token_POUND_SIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_POUND_SIGN, "#");
                }
                return false;
            }
            yylex();

            Atom1Ast *__node_202 = 0;
            if (!parseAtom1(&__node_202))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Atom1Kind, "atom1");
                }
                return false;
            }
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ATOM_LITERAL
                || yytoken == Token_SPEC)
            {
                FieldTypesAst *__node_203 = 0;
                if (!parseFieldTypes(&__node_203))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FieldTypesKind, "fieldTypes");
                    }
                    return false;
                }
                (*yynode)->field_types = __node_203;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BINARY_OPEN)
        {
            BinaryTypeAst *__node_204 = 0;
            if (!parseBinaryType(&__node_204))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BinaryTypeKind, "binaryType");
                }
                return false;
            }
            (*yynode)->binary_type = __node_204;

        }
        else if (yytoken == Token_INTEGER_LITERAL)
        {
            if (yytoken != Token_INTEGER_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_DOT)
            {
                if (yytoken != Token_DOT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOT, ".");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_DOT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOT, ".");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_INTEGER_LITERAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_FUN)
        {
            if (yytoken != Token_FUN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUN, "fun");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LPAREN)
            {
                FunType100Ast *__node_205 = 0;
                if (!parseFunType100(&__node_205))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::FunType100Kind, "funType100");
                    }
                    return false;
                }
                (*yynode)->fun_type100 = __node_205;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeGuard(TypeGuardAst **yynode)
{
    *yynode = create<TypeGuardAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        Atom1Ast *__node_206 = 0;
        if (!parseAtom1(&__node_206))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Atom1Kind, "atom1");
            }
            return false;
        }
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        TopTypesAst *__node_207 = 0;
        if (!parseTopTypes(&__node_207))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypesKind, "topTypes");
            }
            return false;
        }
        (*yynode)->top_type = __node_207;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeGuards(TypeGuardsAst **yynode)
{
    *yynode = create<TypeGuardsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_SPEC)
    {
        TypeGuardAst *__node_208 = 0;
        if (!parseTypeGuard(&__node_208))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeGuardKind, "typeGuard");
            }
            return false;
        }
        (*yynode)->tgSequence = snoc((*yynode)->tgSequence, __node_208, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            TypeGuardAst *__node_209 = 0;
            if (!parseTypeGuard(&__node_209))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeGuardKind, "typeGuard");
                }
                return false;
            }
            (*yynode)->tgSequence = snoc((*yynode)->tgSequence, __node_209, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeSig(TypeSigAst **yynode)
{
    *yynode = create<TypeSigAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        FunTypeAst *__node_210 = 0;
        if (!parseFunType(&__node_210))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::FunTypeKind, "funType");
            }
            return false;
        }
        (*yynode)->fun_type = __node_210;

        if (yytoken == Token_WHEN)
        {
            if (yytoken != Token_WHEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHEN, "when");
                }
                return false;
            }
            yylex();

            TypeGuardsAst *__node_211 = 0;
            if (!parseTypeGuards(&__node_211))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeGuardsKind, "typeGuards");
                }
                return false;
            }
            (*yynode)->type_guards = __node_211;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeSigs(TypeSigsAst **yynode)
{
    *yynode = create<TypeSigsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        TypeSigAst *__node_212 = 0;
        if (!parseTypeSig(&__node_212))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeSigKind, "typeSig");
            }
            return false;
        }
        (*yynode)->tsSequence = snoc((*yynode)->tsSequence, __node_212, memoryPool);

        while (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            TypeSigAst *__node_213 = 0;
            if (!parseTypeSig(&__node_213))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeSigKind, "typeSig");
                }
                return false;
            }
            (*yynode)->tsSequence = snoc((*yynode)->tsSequence, __node_213, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeSpec(TypeSpecAst **yynode)
{
    *yynode = create<TypeSpecAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_LPAREN
        || yytoken == Token_SPEC)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        SpecFunAst *__node_214 = 0;
        if (!parseSpecFun(&__node_214))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::SpecFunKind, "specFun");
            }
            return false;
        }
        (*yynode)->spec_fun = __node_214;

        TypeSigsAst *__node_215 = 0;
        if (!parseTypeSigs(&__node_215))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeSigsKind, "typeSigs");
            }
            return false;
        }
        (*yynode)->types_sigs = __node_215;

        if (yytoken == Token_RPAREN)
        {
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypedAttrVal(TypedAttrValAst **yynode)
{
    *yynode = create<TypedAttrValAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprAst *__node_216 = 0;
        if (!parseExpr(&__node_216))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprKind, "expr");
            }
            return false;
        }
        (*yynode)->expr = __node_216;

        if (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            TypedExprsAst *__node_217 = 0;
            if (!parseTypedExprs(&__node_217))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypedExprsKind, "typedExprs");
                }
                return false;
            }
            (*yynode)->typed_exprs = __node_217;

            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DOUBLE_COLON)
        {
            if (yytoken != Token_DOUBLE_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_COLON, "::");
                }
                return false;
            }
            yylex();

            TopTypeAst *__node_218 = 0;
            if (!parseTopType(&__node_218))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TopTypeKind, "topType");
                }
                return false;
            }
            (*yynode)->top_type = __node_218;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypedExpr(TypedExprAst **yynode)
{
    *yynode = create<TypedExprAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOUBLE_COLON)
    {
        if (yytoken != Token_DOUBLE_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOUBLE_COLON, "::");
            }
            return false;
        }
        yylex();

        TopTypeAst *__node_219 = 0;
        if (!parseTopType(&__node_219))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TopTypeKind, "topType");
            }
            return false;
        }
        (*yynode)->top_type = __node_219;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypedExprs(TypedExprsAst **yynode)
{
    *yynode = create<TypedExprsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ATOM_LITERAL
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY_OPEN
        || yytoken == Token_BIT_NOT
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR_LITERAL
        || yytoken == Token_DOT
        || yytoken == Token_DOUBLE_COLON
        || yytoken == Token_FLOAT_LITERAL
        || yytoken == Token_FUN
        || yytoken == Token_IF
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_POUND_SIGN
        || yytoken == Token_QUERY
        || yytoken == Token_RECEIVE
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TRY
        || yytoken == Token_VARIABLE)
    {
        ExprOrTypedExprAst *__node_220 = 0;
        if (!parseExprOrTypedExpr(&__node_220))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExprOrTypedExprKind, "exprOrTypedExpr");
            }
            return false;
        }
        (*yynode)->eSequence = snoc((*yynode)->eSequence, __node_220, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ExprOrTypedExprAst *__node_221 = 0;
            if (!parseExprOrTypedExpr(&__node_221))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExprOrTypedExprKind, "exprOrTypedExpr");
                }
                return false;
            }
            (*yynode)->eSequence = snoc((*yynode)->eSequence, __node_221, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypedRecordFields(TypedRecordFieldsAst **yynode)
{
    *yynode = create<TypedRecordFieldsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        TypedExprsAst *__node_222 = 0;
        if (!parseTypedExprs(&__node_222))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypedExprsKind, "typedExprs");
            }
            return false;
        }
        (*yynode)->typed_exprs = __node_222;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace erlang

