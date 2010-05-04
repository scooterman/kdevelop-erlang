// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef ERLANG_H_INCLUDED
#define ERLANG_H_INCLUDED

#include "erlangast.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>

#include <parserexport.h>
namespace erlang
{

class KDEVERLANGPARSER_EXPORT Parser
{
public:
    typedef TokenStream::Token Token;
    TokenStream *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(TokenStream *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_AFTER = 1000,
        Token_AND = 1001,
        Token_ANDALSO = 1002,
        Token_ASSIGN = 1003,
        Token_ATOM_LITERAL = 1004,
        Token_BEGIN = 1005,
        Token_BEHAVIOUR_DIRECTIVE = 1006,
        Token_BINARY_CLOSE = 1007,
        Token_BINARY_OPEN = 1008,
        Token_BIT_AND = 1009,
        Token_BIT_NOT = 1010,
        Token_BIT_OR = 1011,
        Token_BIT_XOR = 1012,
        Token_CASE = 1013,
        Token_CATCH = 1014,
        Token_CHAR_LITERAL = 1015,
        Token_COLON = 1016,
        Token_COMMA = 1017,
        Token_COMMENT = 1018,
        Token_COMPILE_DIRECTIVE = 1019,
        Token_COND = 1020,
        Token_DEFINE_DIRECTIVE = 1021,
        Token_DOT = 1022,
        Token_DOUBLE_COLON = 1023,
        Token_DOUBLE_PIPE = 1024,
        Token_ELSE_DIRECTIVE = 1025,
        Token_END = 1026,
        Token_ENDIF_DIRECTIVE = 1027,
        Token_EOF = 1028,
        Token_EXACT_EQUATIONAL = 1029,
        Token_EXACT_NOT_EQUATIONAL = 1030,
        Token_EXCLAMATION = 1031,
        Token_EXPORT_DIRECTIVE = 1032,
        Token_FILE_DIRECTIVE = 1033,
        Token_FLOAT_LITERAL = 1034,
        Token_FORWARD_SLASH = 1035,
        Token_FUN = 1036,
        Token_HALT_COMPILER = 1037,
        Token_IF = 1038,
        Token_IFDEF_DIRECTIVE = 1039,
        Token_IFNDEF_DIRECTIVE = 1040,
        Token_IMPORT_DIRECTIVE = 1041,
        Token_INCLUDE_DIRECTIVE = 1042,
        Token_INCLUDE_LIB = 1043,
        Token_INTEGER_LITERAL = 1044,
        Token_INT_DIV = 1045,
        Token_INT_REM = 1046,
        Token_INVALID = 1047,
        Token_IS_EQUAL = 1048,
        Token_IS_GREATER = 1049,
        Token_IS_GREATER_OR_EQUAL = 1050,
        Token_IS_NOT_EQUAL = 1051,
        Token_IS_SMALLER = 1052,
        Token_IS_SMALLER_OR_EQUAL = 1053,
        Token_LBRACE = 1054,
        Token_LBRACKET = 1055,
        Token_LEADS_TO = 1056,
        Token_LET = 1057,
        Token_LIST_ADDITION = 1058,
        Token_LIST_COMPREHENSION_LEADS_TO = 1059,
        Token_LIST_DIFFERENCE = 1060,
        Token_LPAREN = 1061,
        Token_MINUS = 1062,
        Token_MOD = 1063,
        Token_MODULE_DIRECTIVE = 1064,
        Token_MUL = 1065,
        Token_NOT = 1066,
        Token_NUM_STRING = 1067,
        Token_OF = 1068,
        Token_OR = 1069,
        Token_ORELSE = 1070,
        Token_PIPE = 1071,
        Token_PLUS = 1072,
        Token_POUND_SIGN = 1073,
        Token_QUERY = 1074,
        Token_QUESTION = 1075,
        Token_RBRACE = 1076,
        Token_RBRACKET = 1077,
        Token_RECEIVE = 1078,
        Token_RECORD_DIRECTIVE = 1079,
        Token_RPAREN = 1080,
        Token_SEMICOLON = 1081,
        Token_SL = 1082,
        Token_SPEC = 1083,
        Token_SR = 1084,
        Token_STRING_LITERAL = 1085,
        Token_TRY = 1086,
        Token_UNDEF = 1087,
        Token_UNDERLINE = 1088,
        Token_VARIABLE = 1089,
        Token_WHEN = 1090,
        Token_WHITESPACE = 1091,
        Token_XOR = 1092,
        TokenTypeSize
    }; // TokenType

// user defined declarations:
public:

    /**
     * Transform the raw input into tokens.
     * When this method returns, the parser's token stream has been filled
     * and any parse*() method can be called.
     */
    void tokenize(const QString& contents, int initialState = Lexer::DefaultState);

    enum ProblemType
    {
        Error,
        Warning,
        Info
    };



    void reportProblem( Parser::ProblemType type, const QString& message );
    QList<KDevelop::ProblemPointer> problems()
    {
        return m_problems;
    }
    QString tokenText(qint64 begin, qint64 end);
    void setDebug(bool debug);
    void setCurrentDocument(QString url);

    enum InitialLexerState
    {
        HtmlState = 0,
        DefaultState = 1
    };


private:

    enum VarExpressionState
    {
        Normal,
        OnlyVariable,
        OnlyNewObject
    };

    struct ParserState
    {
        VarExpressionState varExpressionState;
        bool varExpressionIsVariable;
    };

    QString m_contents;
    bool m_debug;
    QString m_currentDocument;
    QList<KDevelop::ProblemPointer> m_problems;


    ParserState m_state;


public:
// The copyCurrentState() and restoreState() methods are only declared
// if you are using try blocks in your grammar, and have to be
// implemented by yourself, and you also have to define a
// "struct ParserState" inside a %parserclass directive.

// This method should create a new ParserState object and return it,
// or return 0 if no state variables need to be saved.
    ParserState *copyCurrentState();

// This method is only called for ParserState objects != 0
// and should restore the parser state given as argument.
    void restoreState(ParserState *state);
    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;

// user defined constructor code:

        m_state.varExpressionState = Normal;
        m_state.varExpressionIsVariable = false;

    }

    virtual ~Parser() {}

    bool parseAddOp(AddOpAst **yynode);
    bool parseArgumentList(ArgumentListAst **yynode);
    bool parseAtom1(Atom1Ast **yynode);
    bool parseAtomic(AtomicAst **yynode);
    bool parseAttrVal(AttrValAst **yynode);
    bool parseAttribute(AttributeAst **yynode);
    bool parseAttributeDeclaration(AttributeDeclarationAst **yynode);
    bool parseBehaviourDeclaration(BehaviourDeclarationAst **yynode);
    bool parseBinBaseType(BinBaseTypeAst **yynode);
    bool parseBinElement(BinElementAst **yynode);
    bool parseBinElements(BinElementsAst **yynode);
    bool parseBinUnitType(BinUnitTypeAst **yynode);
    bool parseBinary(BinaryAst **yynode);
    bool parseBinaryComprehension(BinaryComprehensionAst **yynode);
    bool parseBinaryType(BinaryTypeAst **yynode);
    bool parseBitExpr(BitExprAst **yynode);
    bool parseBitSizeExpr(BitSizeExprAst **yynode);
    bool parseBitType(BitTypeAst **yynode);
    bool parseBitTypeList(BitTypeListAst **yynode);
    bool parseCaseExpr(CaseExprAst **yynode);
    bool parseClauseArgs(ClauseArgsAst **yynode);
    bool parseClauseBody(ClauseBodyAst **yynode);
    bool parseClauseGuard(ClauseGuardAst **yynode);
    bool parseCompOp(CompOpAst **yynode);
    bool parseCrClause(CrClauseAst **yynode);
    bool parseCrClauses(CrClausesAst **yynode);
    bool parseExportDeclaration(ExportDeclarationAst **yynode);
    bool parseExpr(ExprAst **yynode);
    bool parseExpr100(Expr100Ast **yynode);
    bool parseExpr150(Expr150Ast **yynode);
    bool parseExpr160(Expr160Ast **yynode);
    bool parseExpr200(Expr200Ast **yynode);
    bool parseExpr300(Expr300Ast **yynode);
    bool parseExpr400(Expr400Ast **yynode);
    bool parseExpr400a(Expr400aAst **yynode);
    bool parseExpr500(Expr500Ast **yynode);
    bool parseExpr500a(Expr500aAst **yynode);
    bool parseExpr600(Expr600Ast **yynode);
    bool parseExpr700(Expr700Ast **yynode);
    bool parseExpr800(Expr800Ast **yynode);
    bool parseExpr900(Expr900Ast **yynode);
    bool parseExpr900a(Expr900aAst **yynode);
    bool parseExprMax(ExprMaxAst **yynode);
    bool parseExprOrTypedExpr(ExprOrTypedExprAst **yynode);
    bool parseExprs(ExprsAst **yynode);
    bool parseFieldType(FieldTypeAst **yynode);
    bool parseFieldTypes(FieldTypesAst **yynode);
    bool parseFileDeclaration(FileDeclarationAst **yynode);
    bool parseForm(FormAst **yynode);
    bool parseFunClause(FunClauseAst **yynode);
    bool parseFunClauses(FunClausesAst **yynode);
    bool parseFunExpr(FunExprAst **yynode);
    bool parseFunType(FunTypeAst **yynode);
    bool parseFunType100(FunType100Ast **yynode);
    bool parseFunctionCall(FunctionCallAst **yynode);
    bool parseFunctionOrRule(FunctionOrRuleAst **yynode);
    bool parseFunctionOrRuleClause(FunctionOrRuleClauseAst **yynode);
    bool parseFunctionSlashArity(FunctionSlashArityAst **yynode);
    bool parseGuard(GuardAst **yynode);
    bool parseIfClause(IfClauseAst **yynode);
    bool parseIfClauses(IfClausesAst **yynode);
    bool parseIfExpr(IfExprAst **yynode);
    bool parseImportDeclaration(ImportDeclarationAst **yynode);
    bool parseLcExpr(LcExprAst **yynode);
    bool parseLcExprs(LcExprsAst **yynode);
    bool parseListComprehension(ListComprehensionAst **yynode);
    bool parseListOp(ListOpAst **yynode);
    bool parseModuleDeclaration(ModuleDeclarationAst **yynode);
    bool parseMultOp(MultOpAst **yynode);
    bool parseOptBitSizeExpr(OptBitSizeExprAst **yynode);
    bool parseOptBitTypeList(OptBitTypeListAst **yynode);
    bool parsePrefixOp(PrefixOpAst **yynode);
    bool parseQueryExpr(QueryExprAst **yynode);
    bool parseReceiveExpr(ReceiveExprAst **yynode);
    bool parseRecordDeclaration(RecordDeclarationAst **yynode);
    bool parseRecordExpr(RecordExprAst **yynode);
    bool parseRecordField(RecordFieldAst **yynode);
    bool parseRecordFields(RecordFieldsAst **yynode);
    bool parseRecordTuple(RecordTupleAst **yynode);
    bool parseRuleBody(RuleBodyAst **yynode);
    bool parseRuleClause(RuleClauseAst **yynode);
    bool parseRuleClauses(RuleClausesAst **yynode);
    bool parseSpecFun(SpecFunAst **yynode);
    bool parseTail(TailAst **yynode);
    bool parseTopType(TopTypeAst **yynode);
    bool parseTopType100(TopType100Ast **yynode);
    bool parseTopTypes(TopTypesAst **yynode);
    bool parseTryCatch(TryCatchAst **yynode);
    bool parseTryClause(TryClauseAst **yynode);
    bool parseTryClauses(TryClausesAst **yynode);
    bool parseTryExpr(TryExprAst **yynode);
    bool parseTuple(TupleAst **yynode);
    bool parseType(TypeAst **yynode);
    bool parseTypeGuard(TypeGuardAst **yynode);
    bool parseTypeGuards(TypeGuardsAst **yynode);
    bool parseTypeSig(TypeSigAst **yynode);
    bool parseTypeSigs(TypeSigsAst **yynode);
    bool parseTypeSpec(TypeSpecAst **yynode);
    bool parseTypedAttrVal(TypedAttrValAst **yynode);
    bool parseTypedExpr(TypedExprAst **yynode);
    bool parseTypedExprs(TypedExprsAst **yynode);
    bool parseTypedRecordFields(TypedRecordFieldsAst **yynode);
};

} // end of namespace erlang

#endif

