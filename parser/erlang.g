-------------------------------------------------------------------------------
-- Copyright (c) 2010 Victor Vicente de Carvalho <victor.v.carvalho at gmail.com>
--
-- This grammar is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Library General Public
-- License as published by the Free Software Foundation; either
-- version 2 of the License, or (at your option) any later version.
--
-- This grammar is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Library General Public License
-- along with this library; see the file COPYING.LIB.  If not, write to
-- the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
-- Boston, MA 02110-1301, USA.
-----------------------------------------------------------


-----------------------------------------------------------
-- Grammar for Erlang
-- Parts taken from KDevelop PHP Grammar, based on 
---  erl_parse.yrl found on erlang otp source code
-----------------------------------------------------------


[:

#include <QtCore/QString>
#include <kdebug.h>
#include "parser/tokenstream.h"
#include <language/interfaces/iproblem.h>
#include "parser/erlanglexer.h"

namespace KDevelop
{
    class DUContext;
}

:]

------------------------------------------------------------
-- Export macro to use the parser in a shared lib
------------------------------------------------------------
%export_macro "KDEVERLANGPARSER_EXPORT"
%export_macro_header "parser/parserexport.h"

------------------------------------------------------------
-- Ast Node class members
------------------------------------------------------------
%ast_extra_members
[:
  KDevelop::DUContext* ducontext;

  virtual ~AstNode() { }
:]

------------------------------------------------------------
-- Parser class members
------------------------------------------------------------

%parserclass (public declaration)
[:
  /**
   * Transform the raw input into tokens.
   * When this method returns, the parser's token stream has been filled
   * and any parse*() method can be called.
   */
  void tokenize(const QString& contents, int initialState = Lexer::DefaultState);

  enum ProblemType {
      Error,
      Warning,
      Info
  };



  void reportProblem( Parser::ProblemType type, const QString& message );
  QList<KDevelop::ProblemPointer> problems() {
      return m_problems;
  }
  QString tokenText(qint64 begin, qint64 end);
  void setDebug(bool debug);
  void setCurrentDocument(QString url);

    enum InitialLexerState {
        HtmlState = 0,
        DefaultState = 1
    };

:]

%parserclass (private declaration)
[:
    enum VarExpressionState {
        Normal,
        OnlyVariable,
        OnlyNewObject
    };

    struct ParserState {
        VarExpressionState varExpressionState;
        bool varExpressionIsVariable;
    };

    QString m_contents;
    bool m_debug;
    QString m_currentDocument;
    QList<KDevelop::ProblemPointer> m_problems;

   
    ParserState m_state;
:]

%parserclass (constructor)
[:
    m_state.varExpressionState = Normal;
    m_state.varExpressionIsVariable = false;
:]


%token_stream TokenStream ;;

-----------------------------------------------------------
-- List of defined tokens
-----------------------------------------------------------
-- keywords:
%token AFTER("after"), BEGIN("begin"), CASE("case"), CATCH("catch"), COND("cond"),
       END("end"), FUN("fun"), IF("if"), LET("let"), OF("of"), QUERY("query"),
       RECEIVE("receive"), WHEN("when"), SPEC("spec"), TRY("try");;

-- seperators:
%token LBRACKET ("["), RBRACKET ("]"), LPAREN ("("), 
       RPAREN (")"), LBRACE ("{"), RBRACE ("}"),
       COMMA (","), LEADS_TO("->"), QUESTION("?"),
       PIPE("|"), DOUBLE_PIPE("||"), POUND_SIGN("#"), DOT("."),
       SEMICOLON (";"), COLON(":"),DOUBLE_COLON("::"), UNDERLINE("_"), 
       BINARY_OPEN("<<"), BINARY_CLOSE(">>");;

-- operators:
%token IS_EQUAL ("=="), IS_NOT_EQUAL ("/="), EXACT_EQUATIONAL ("=:="),
       EXACT_NOT_EQUATIONAL ("=/="), IS_SMALLER ("<"), IS_GREATER (">"),
       IS_SMALLER_OR_EQUAL ("=<"), IS_GREATER_OR_EQUAL (">="),
       ASSIGN ("="), PLUS ("+"), MINUS("-"),
       LIST_ADDITION ("++"), LIST_DIFFERENCE ("--"),
       BIT_OR("bor"), BIT_XOR ("bxor"), XOR("xor"), OR("or"),
       SL ("bsl"), SR ("bsr"), MUL("*"), FORWARD_SLASH("/"), MOD ("%"), 
       INT_DIV("div"), INT_REM("rem"), BIT_AND("band"), AND("and"), BIT_NOT("bnot"),
       NOT("not"), EXCLAMATION("!"), LIST_COMPREHENSION_LEADS_TO("<-"),
       ORELSE("orelse"), ANDALSO("andalso");;

-- literals and identifiers:
%token CHAR_LITERAL("char_literal"), COMMENT("comment"), 
       WHITESPACE ("whitespace"), VARIABLE ("variable"),
       NUM_STRING ("num string"), INTEGER_LITERAL("integer literal"), 
       STRING_LITERAL ("string literal"), ATOM_LITERAL("atom literal"),
       HALT_COMPILER ("halt compiler");;

--macros

%token INCLUDE_DIRECTIVE("include"), IMPORT_DIRECTIVE("import"), 
       FILE_DIRECTIVE("file directive"), COMPILE_DIRECTIVE("compile directive"),
       DEFINE_DIRECTIVE("define"), MODULE_DIRECTIVE("module"), 
       RECORD_DIRECTIVE("record"), UNDEF("undef"), 
       IFDEF_DIRECTIVE("ifdef macro directive"), 
       IFNDEF_DIRECTIVE("ifndef macro directive"),
       ELSE_DIRECTIVE("else macro directive"),
       ENDIF_DIRECTIVE("endif macro directive"), INCLUDE_LIB("include"), 
       EXPORT_DIRECTIVE("exported functions"),
       BEHAVIOUR_DIRECTIVE("module behaviour"),
       FLOAT_LITERAL("float literal");;

-- token that makes the parser fail in any case:
%token INVALID ("invalid token") ;;

-- The actual grammar starts here.

      attribute=attribute DOT form_next=form
    | functions=functionOrRule DOT form_next=form
    | 0
-> form;;

      MINUS ( SPEC type_spec=typeSpec 
            | module_declaration=moduleDeclaration
            | export_declaration=exportDeclaration
            | import_declaration=importDeclaration
            | record_declaration=recordDeclaration
            | file_declaration=fileDeclaration
            | define_declaration=defineDeclaration
            | behaviour_declaration=behaviourDeclaration
            | attribute_declaration=attributeDeclaration 
            | include_declaration=includeDeclaration )
-> attribute;;

    MODULE_DIRECTIVE LPAREN module_name=ATOM_LITERAL RPAREN
-> moduleDeclaration;;

    BEHAVIOUR_DIRECTIVE LPAREN behaviour=ATOM_LITERAL RPAREN
-> behaviourDeclaration;;


    EXPORT_DIRECTIVE LPAREN LBRACKET (#exported_functions=functionSlashArity @ COMMA | 0) RBRACKET RPAREN
-> exportDeclaration;;

    function_name=ATOM_LITERAL FORWARD_SLASH function_arity=INTEGER_LITERAL
-> functionSlashArity;;

    IMPORT_DIRECTIVE LPAREN module_name=ATOM_LITERAL COMMA #imported_functions=functionSlashArity @ COMMA RPAREN
-> importDeclaration;;

    RECORD_DIRECTIVE LPAREN record_name=ATOM_LITERAL COMMA type_record_fields=typedRecordFields RPAREN
-> recordDeclaration;;

    FILE_DIRECTIVE LPAREN file_name=STRING_LITERAL COMMA line=INTEGER_LITERAL RPAREN
-> fileDeclaration;;

    DEFINE_DIRECTIVE LPAREN define_name=VARIABLE (argument_list=argumentList | 0 ) COMMA expression=expr RPAREN
-> defineDeclaration;;

    ATOM_LITERAL LPAREN name=STRING_LITERAL COMMA line=INTEGER_LITERAL RPAREN
-> attributeDeclaration;;

    INCLUDE_DIRECTIVE LPAREN STRING_LITERAL RPAREN
-> includeDeclaration;;

      SPEC 
    | literal=ATOM_LITERAL
-> atom1;;

      expr=expr ( COMMA LBRACE typed_exprs=typedExprs RBRACE | DOUBLE_COLON top_type=topType)
-> typedAttrVal;;
 
   try/rollback(LPAREN expr=expr COMMA exprs=exprs RPAREN)
   catch(expr=expr ( COMMA exprs=exprs | 0 ))
-> attrVal;;

    (LPAREN | 0) spec_fun=specFun types_sigs=typeSigs (RPAREN | 0)
-> typeSpec;;

    atom1 ( COLON ATOM_LITERAL | 0 )
-> specFun;;

    #e=exprOrTypedExpr @ COMMA
-> typedExprs;;

      typed_expr=typedExpr 
    | expr=expr
-> exprOrTypedExpr;;

    LBRACE typed_exprs=typedExprs RBRACE
-> typedRecordFields;;

    DOUBLE_COLON top_type=topType
-> typedExpr;;

    #ts=typeSig @ SEMICOLON
->typeSigs;;

    fun_type=funType (WHEN type_guards=typeGuards | 0)
-> typeSig;;

    #tg=typeGuard @ COMMA
-> typeGuards;;

    atom1 LPAREN top_type=topTypes RPAREN
-> typeGuard;;

    #tt=topType @ COMMA
-> topTypes;;

    (VARIABLE DOUBLE_COLON | 0) top_type100=topType100
-> topType;;

    type=type ( PIPE top_type100=topType100 | 0 )
->topType100;;

      LPAREN top_type=topType RPAREN
    | VARIABLE
    | atom1 (  LPAREN (top_types=topTypes | 0) RPAREN 
             | COLON atom1 LPAREN (top_types=topTypes | 0) RPAREN 
             |  0)
    | LBRACKET (top_type=topType (COMMA DOT DOT DOT | 0) | 0) RBRACKET
    | LBRACE (top_types=topTypes | 0 ) RBRACE
    | POUND_SIGN atom1 LBRACE (field_types=fieldTypes | 0 ) RBRACE
    | binary_type=binaryType
    | INTEGER_LITERAL ( DOT DOT INTEGER_LITERAL | 0 )
    | FUN LPAREN (fun_type100=funType100 | 0) RPAREN
-> type;;

      LPAREN (DOT DOT DOT | (top_types=topTypes | 0)) RPAREN LEADS_TO top_type=topType
-> funType100;;

    LPAREN (top_types=topTypes | 0) RPAREN LEADS_TO top_type=topType
-> funType;;

    #ft=fieldType @ COMMA
-> fieldTypes;;

    atom1 DOUBLE_COLON top_type=topType
-> fieldType;;

    BINARY_OPEN ( VARIABLE COLON ( INTEGER_LITERAL ( COMMA bin_unit_type=binUnitType | 0) | bin_unit_type=binUnitType ) | 0 ) BINARY_CLOSE
-> binaryType;;

    VARIABLE COLON 
-> binBaseType;;

    VARIABLE MUL INTEGER_LITERAL
-> binUnitType;;

    #fc=functionOrRuleClause @ SEMICOLON
-> functionOrRule;;

   function_name=atom1 clause_args=clauseArgs clause_guard=clauseGuard (body=clauseBody | rule_body=ruleBody)
->functionOrRuleClause;;

    argument_list=argumentList
-> clauseArgs;;

    WHEN (#guards=guard @ SEMICOLON) | 0
-> clauseGuard;;

    LEADS_TO exprs=exprs
-> clauseBody;;

%< expr700
%pre CATCH 50
%bin ASSIGN 100 %right
%bin EXCLAMATION 100 %right
%bin ORELSE 150 %right
%bin ANDALSO 160 %right
%bin ?[: compAllowed :] IS_EQUAL [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] IS_GREATER [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] IS_GREATER_OR_EQUAL [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] IS_NOT_EQUAL [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] IS_SMALLER [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] IS_SMALLER_OR_EQUAL [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] EXACT_NOT_EQUATIONAL [: compAllowed = false; :] 200 %left
%bin ?[: compAllowed :] EXACT_EQUATIONAL [: compAllowed = false; :] 200 %left
%bin LIST_ADDITION 300 %right
%bin LIST_DIFFERENCE 300 %right
%bin PLUS 400 %right
%bin MINUS 400 %right
%bin BIT_OR 400 %right
%bin BIT_XOR 400 %right
%bin SL 400 %right
%bin SR 400 %right
%bin OR 400 %right
%bin XOR 400 %right
%bin FORWARD_SLASH 500 %right
%bin MUL 500 %right
%bin INT_DIV 500 %right
%bin INT_REM 500 %right
%bin BIT_AND 500 %right
%bin AND 500 %right
%pre ?[: preAllowed :] PLUS [: preAllowed = false; :] 600
%pre ?[: preAllowed :] MINUS [: preAllowed = false; :] 600
%pre ?[: preAllowed :] BIT_NOT [: preAllowed = false; :] 600
%pre ?[: preAllowed :] NOT [: preAllowed = false; :] 600
%> expr [:
   bool preAllowed = true;
   bool compAllowed = true;
:];;

   PLUS
 | MINUS
 | BIT_NOT
 | NOT
-> prefixOp ;;

    try/rollback(record_expr=recordExpr)
    catch(try/rollback(functionCall=functionCall)
          catch(expr800=expr800))
-> expr700;;

    expr900=expr900 ( COLON expr_max=exprMax | 0)
-> expr800;;

      DOT atom1 expr900a=expr900a
    | expr_max=exprMax 
-> expr900;;

    DOT atom1 expr900a=expr900a | expr_max=exprMax expr900a=expr900a | 0
-> expr900a;;

      var=variable
    | atomic=atomic
    | try/rollback(binary=binary)
      catch(binary_comprehension=binaryComprehension)
    | try/rollback(LBRACKET (expr=expr tail=tail | RBRACKET))
      catch(list_comprehension=listComprehension)
    | tuple=tuple
    | LPAREN expr=expr RPAREN
    | BEGIN exprs=exprs END
    | if_expr=ifExpr
    | case_expr=caseExpr
    | receive_expr=receiveExpr
    | fun_expr=funExpr
    | try_expr=tryExpr
    | query_expr=queryExpr
    | QUESTION define_name=VARIABLE (define_function=argumentList | 0)
-> exprMax;;

    literal=VARIABLE | UNDERLINE
-> variable;;

      RBRACKET
    | PIPE expr=expr RBRACKET
    | COMMA expr=expr tail=tail
-> tail;;

    BINARY_OPEN ( bin_elements=binElements | 0 ) BINARY_CLOSE
-> binary;;

    #be=binElement @ COMMA
-> binElements;;

    bit_expr=bitExpr opt_bit_size_expr=optBitSizeExpr opt_bit_type_list=optBitTypeList
-> binElement;;

    (prefix_op=prefixOp | 0) expr_max=exprMax
-> bitExpr;;

    COLON bit_size_expr=bitSizeExpr | 0
-> optBitSizeExpr;;

    FORWARD_SLASH bit_type_list=bitTypeList | 0
-> optBitTypeList;;

    bit_type=bitType (MINUS bit_type_list=bitTypeList | 0 )
-> bitTypeList;;

    atom1 (COLON INTEGER_LITERAL | 0)
-> bitType;;

    expr_max=exprMax
-> bitSizeExpr;;

    LBRACKET expr=expr DOUBLE_PIPE lc_exprs=lcExprs RBRACKET
-> listComprehension;;

    BINARY_OPEN binary=binary DOUBLE_PIPE lc_exprs=lcExprs BINARY_CLOSE
-> binaryComprehension;;

    #lc=lcExpr @ COMMA
-> lcExprs;;


    try/rollback(expr=expr (LIST_COMPREHENSION_LEADS_TO  expr=expr | 0))
    catch(binary=binary LIST_COMPREHENSION_LEADS_TO  expr=expr)    
-> lcExpr;;

    LBRACE (exprs | 0 ) RBRACE
-> tuple;;

      POUND_SIGN atom1 ( DOT atom1 | record_tuple=recordTuple )
    | expr_max=exprMax POUND_SIGN atom1 ( DOT atom1 | record_tuple=recordTuple )
-> recordExpr;;

    LBRACE (record_fields=recordFields | 0 ) RBRACE
-> recordTuple;;

    #rf=recordField @ COMMA
-> recordFields;;

      VARIABLE ASSIGN expr=expr
    | atom1 ASSIGN expr=expr
-> recordField;;

    expr800=expr800 argument_list=argumentList
-> functionCall;;

    IF if_clauses=ifClauses END
-> ifExpr;;

    #ic=ifClause @ SEMICOLON
-> ifClauses;;

    guard=guard clause_body=clauseBody
-> ifClause;;

    CASE expr=expr OF cr_clauses=crClauses END
-> caseExpr;;

    #cc=crClause @ SEMICOLON
-> crClauses;;

    expr clause_guard=clauseGuard clause_body=clauseBody
-> crClause;;

      RECEIVE (cr_clauses=crClauses | 0) (AFTER clause_body=clauseBody | 0) END
-> receiveExpr;;

      FUN (atom1 (FORWARD_SLASH INTEGER_LITERAL | COLON atom1 FORWARD_SLASH INTEGER_LITERAL)
           | funClauses END)
-> funExpr;;

      #fc=funClause @ SEMICOLON
-> funClauses;;

      argument_list=argumentList clause_guard=clauseGuard clause_body=clauseBody
-> funClause;;

    TRY exprs=exprs (OF cr_clauses=crClauses | 0 ) try_catch=tryCatch
-> tryExpr;;

      CATCH try_clauses=tryClauses (AFTER exprs=exprs | 0) END
    | AFTER exprs=exprs END
-> tryCatch;;

    #tc=tryClause @ SEMICOLON
-> tryClauses;;

-- Using LA(2) to remove ambiguities with expr
    (?[:LA(2).kind == Token_COLON:] atom1 COLON expr=expr | ?[:LA(2).kind == Token_COLON:] VARIABLE COLON expr=expr | expr=expr) clause_guard=clauseGuard clause_body=clauseBody
-> tryClause;;

    QUERY list_comprehension=listComprehension END
-> queryExpr;;

    LPAREN (exprs=exprs | 0) RPAREN
-> argumentList;;

    #e=expr @ COMMA
-> exprs;;

   #guard=exprs
-> guard;;

      CHAR_LITERAL
    | (PLUS|MINUS|0) INTEGER_LITERAL
    | FLOAT_LITERAL
    | ATOM_LITERAL
    | #strings=STRING_LITERAL
-> atomic;;

    #rc=ruleClause @ SEMICOLON
-> ruleClauses;;

    atom1 clause_args=clauseArgs clause_guard=clauseGuard rule_body=ruleBody
-> ruleClause;;

    COLON MINUS lc_exprs=lcExprs
-> ruleBody;;

-----------------------------------------------------------------
-- Code segments copied to the implementation (.cpp) file.
-- If existent, kdevelop-pg's current syntax requires this block
-- to occur at the end of the file.
-----------------------------------------------------------------

[:

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
        while (kind == Parser::Token_WHITESPACE || kind == Parser::Token_COMMENT) {
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
    switch ( type ) {
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

:]

-- kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on; auto-insert-doxygen on
