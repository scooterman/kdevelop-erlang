// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef ERLANG_AST_H_INCLUDED
#define ERLANG_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>

#include <parserexport.h>


#include <QtCore/QString>
#include <kdebug.h>
#include <tokenstream.h>
#include <language/interfaces/iproblem.h>
#include "erlanglexer.h"

namespace KDevelop
{
class DUContext;
}


namespace erlang
{

struct AddOpAst;
struct ArgumentListAst;
struct Atom1Ast;
struct AtomicAst;
struct AttrValAst;
struct AttributeAst;
struct AttributeDeclarationAst;
struct BinBaseTypeAst;
struct BinElementAst;
struct BinElementsAst;
struct BinUnitTypeAst;
struct BinaryAst;
struct BinaryComprehensionAst;
struct BinaryTypeAst;
struct BitExprAst;
struct BitSizeExprAst;
struct BitTypeAst;
struct BitTypeListAst;
struct CaseExprAst;
struct ClauseArgsAst;
struct ClauseBodyAst;
struct ClauseGuardAst;
struct CompOpAst;
struct CrClauseAst;
struct CrClausesAst;
struct ExportDeclarationAst;
struct ExprAst;
struct Expr100Ast;
struct Expr150Ast;
struct Expr160Ast;
struct Expr200Ast;
struct Expr300Ast;
struct Expr400Ast;
struct Expr400aAst;
struct Expr500Ast;
struct Expr500aAst;
struct Expr600Ast;
struct Expr700Ast;
struct Expr800Ast;
struct Expr900Ast;
struct Expr900aAst;
struct ExprMaxAst;
struct ExprOrTypedExprAst;
struct ExprsAst;
struct FieldTypeAst;
struct FieldTypesAst;
struct FileDeclarationAst;
struct FormAst;
struct FunClauseAst;
struct FunClausesAst;
struct FunExprAst;
struct FunTypeAst;
struct FunType100Ast;
struct FunctionCallAst;
struct FunctionOrRuleAst;
struct FunctionOrRuleClauseAst;
struct FunctionSlashArityAst;
struct GuardAst;
struct IfClauseAst;
struct IfClausesAst;
struct IfExprAst;
struct ImportDeclarationAst;
struct LcExprAst;
struct LcExprsAst;
struct ListComprehensionAst;
struct ListOpAst;
struct ModuleDeclarationAst;
struct MultOpAst;
struct OptBitSizeExprAst;
struct OptBitTypeListAst;
struct PrefixOpAst;
struct QueryExprAst;
struct ReceiveExprAst;
struct RecordDeclarationAst;
struct RecordExprAst;
struct RecordFieldAst;
struct RecordFieldsAst;
struct RecordTupleAst;
struct RuleBodyAst;
struct RuleClauseAst;
struct RuleClausesAst;
struct SpecFunAst;
struct TailAst;
struct TopTypeAst;
struct TopType100Ast;
struct TopTypesAst;
struct TryCatchAst;
struct TryClauseAst;
struct TryClausesAst;
struct TryExprAst;
struct TupleAst;
struct TypeAst;
struct TypeGuardAst;
struct TypeGuardsAst;
struct TypeSigAst;
struct TypeSigsAst;
struct TypeSpecAst;
struct TypedAttrValAst;
struct TypedExprAst;
struct TypedExprsAst;
struct TypedRecordFieldsAst;


struct KDEVERLANGPARSER_EXPORT AstNode
{
    enum AstNodeKind
    {
        AddOpKind = 1000,
        ArgumentListKind = 1001,
        Atom1Kind = 1002,
        AtomicKind = 1003,
        AttrValKind = 1004,
        AttributeKind = 1005,
        AttributeDeclarationKind = 1006,
        BinBaseTypeKind = 1007,
        BinElementKind = 1008,
        BinElementsKind = 1009,
        BinUnitTypeKind = 1010,
        BinaryKind = 1011,
        BinaryComprehensionKind = 1012,
        BinaryTypeKind = 1013,
        BitExprKind = 1014,
        BitSizeExprKind = 1015,
        BitTypeKind = 1016,
        BitTypeListKind = 1017,
        CaseExprKind = 1018,
        ClauseArgsKind = 1019,
        ClauseBodyKind = 1020,
        ClauseGuardKind = 1021,
        CompOpKind = 1022,
        CrClauseKind = 1023,
        CrClausesKind = 1024,
        ExportDeclarationKind = 1025,
        ExprKind = 1026,
        Expr100Kind = 1027,
        Expr150Kind = 1028,
        Expr160Kind = 1029,
        Expr200Kind = 1030,
        Expr300Kind = 1031,
        Expr400Kind = 1032,
        Expr400aKind = 1033,
        Expr500Kind = 1034,
        Expr500aKind = 1035,
        Expr600Kind = 1036,
        Expr700Kind = 1037,
        Expr800Kind = 1038,
        Expr900Kind = 1039,
        Expr900aKind = 1040,
        ExprMaxKind = 1041,
        ExprOrTypedExprKind = 1042,
        ExprsKind = 1043,
        FieldTypeKind = 1044,
        FieldTypesKind = 1045,
        FileDeclarationKind = 1046,
        FormKind = 1047,
        FunClauseKind = 1048,
        FunClausesKind = 1049,
        FunExprKind = 1050,
        FunTypeKind = 1051,
        FunType100Kind = 1052,
        FunctionCallKind = 1053,
        FunctionOrRuleKind = 1054,
        FunctionOrRuleClauseKind = 1055,
        FunctionSlashArityKind = 1056,
        GuardKind = 1057,
        IfClauseKind = 1058,
        IfClausesKind = 1059,
        IfExprKind = 1060,
        ImportDeclarationKind = 1061,
        LcExprKind = 1062,
        LcExprsKind = 1063,
        ListComprehensionKind = 1064,
        ListOpKind = 1065,
        ModuleDeclarationKind = 1066,
        MultOpKind = 1067,
        OptBitSizeExprKind = 1068,
        OptBitTypeListKind = 1069,
        PrefixOpKind = 1070,
        QueryExprKind = 1071,
        ReceiveExprKind = 1072,
        RecordDeclarationKind = 1073,
        RecordExprKind = 1074,
        RecordFieldKind = 1075,
        RecordFieldsKind = 1076,
        RecordTupleKind = 1077,
        RuleBodyKind = 1078,
        RuleClauseKind = 1079,
        RuleClausesKind = 1080,
        SpecFunKind = 1081,
        TailKind = 1082,
        TopTypeKind = 1083,
        TopType100Kind = 1084,
        TopTypesKind = 1085,
        TryCatchKind = 1086,
        TryClauseKind = 1087,
        TryClausesKind = 1088,
        TryExprKind = 1089,
        TupleKind = 1090,
        TypeKind = 1091,
        TypeGuardKind = 1092,
        TypeGuardsKind = 1093,
        TypeSigKind = 1094,
        TypeSigsKind = 1095,
        TypeSpecKind = 1096,
        TypedAttrValKind = 1097,
        TypedExprKind = 1098,
        TypedExprsKind = 1099,
        TypedRecordFieldsKind = 1100,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

    KDevelop::DUContext* ducontext;

};

struct KDEVERLANGPARSER_EXPORT AddOpAst: public AstNode
{
    enum { KIND = AddOpKind };

};

struct KDEVERLANGPARSER_EXPORT ArgumentListAst: public AstNode
{
    enum { KIND = ArgumentListKind };

    ExprsAst *exprs;
};

struct KDEVERLANGPARSER_EXPORT Atom1Ast: public AstNode
{
    enum { KIND = Atom1Kind };

    qint64 literal;
};

struct KDEVERLANGPARSER_EXPORT AtomicAst: public AstNode
{
    enum { KIND = AtomicKind };

    const KDevPG::ListNode<qint64 > *stringsSequence;
};

struct KDEVERLANGPARSER_EXPORT AttrValAst: public AstNode
{
    enum { KIND = AttrValKind };

    ExprAst *expr;
    ExprsAst *exprs;
};

struct KDEVERLANGPARSER_EXPORT AttributeAst: public AstNode
{
    enum { KIND = AttributeKind };

    TypeSpecAst *type_spec;
    ModuleDeclarationAst *module_declaration;
    ExportDeclarationAst *export_declaration;
    ImportDeclarationAst *import_declaration;
    RecordDeclarationAst *record_declaration;
    FileDeclarationAst *file_declaration;
    AttributeDeclarationAst *attribute_declaration;
};

struct KDEVERLANGPARSER_EXPORT AttributeDeclarationAst: public AstNode
{
    enum { KIND = AttributeDeclarationKind };

    qint64 name;
    qint64 line;
};

struct KDEVERLANGPARSER_EXPORT BinBaseTypeAst: public AstNode
{
    enum { KIND = BinBaseTypeKind };

};

struct KDEVERLANGPARSER_EXPORT BinElementAst: public AstNode
{
    enum { KIND = BinElementKind };

    BitExprAst *bit_expr;
    OptBitSizeExprAst *opt_bit_size_expr;
    OptBitTypeListAst *opt_bit_type_list;
};

struct KDEVERLANGPARSER_EXPORT BinElementsAst: public AstNode
{
    enum { KIND = BinElementsKind };

    const KDevPG::ListNode<BinElementAst *> *beSequence;
};

struct KDEVERLANGPARSER_EXPORT BinUnitTypeAst: public AstNode
{
    enum { KIND = BinUnitTypeKind };

};

struct KDEVERLANGPARSER_EXPORT BinaryAst: public AstNode
{
    enum { KIND = BinaryKind };

    BinElementsAst *bin_elements;
};

struct KDEVERLANGPARSER_EXPORT BinaryComprehensionAst: public AstNode
{
    enum { KIND = BinaryComprehensionKind };

    BinaryAst *binary;
    LcExprsAst *lc_exprs;
};

struct KDEVERLANGPARSER_EXPORT BinaryTypeAst: public AstNode
{
    enum { KIND = BinaryTypeKind };

    BinUnitTypeAst *bin_unit_type;
};

struct KDEVERLANGPARSER_EXPORT BitExprAst: public AstNode
{
    enum { KIND = BitExprKind };

    PrefixOpAst *prefix_op;
    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT BitSizeExprAst: public AstNode
{
    enum { KIND = BitSizeExprKind };

    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT BitTypeAst: public AstNode
{
    enum { KIND = BitTypeKind };

};

struct KDEVERLANGPARSER_EXPORT BitTypeListAst: public AstNode
{
    enum { KIND = BitTypeListKind };

    BitTypeAst *bit_type;
    BitTypeListAst *bit_type_list;
};

struct KDEVERLANGPARSER_EXPORT CaseExprAst: public AstNode
{
    enum { KIND = CaseExprKind };

    ExprAst *expr;
    CrClausesAst *cr_clauses;
};

struct KDEVERLANGPARSER_EXPORT ClauseArgsAst: public AstNode
{
    enum { KIND = ClauseArgsKind };

    ArgumentListAst *argument_list;
};

struct KDEVERLANGPARSER_EXPORT ClauseBodyAst: public AstNode
{
    enum { KIND = ClauseBodyKind };

    ExprsAst *exprs;
};

struct KDEVERLANGPARSER_EXPORT ClauseGuardAst: public AstNode
{
    enum { KIND = ClauseGuardKind };

    GuardAst *guard;
};

struct KDEVERLANGPARSER_EXPORT CompOpAst: public AstNode
{
    enum { KIND = CompOpKind };

};

struct KDEVERLANGPARSER_EXPORT CrClauseAst: public AstNode
{
    enum { KIND = CrClauseKind };

    ClauseGuardAst *clause_guard;
    ClauseBodyAst *clause_body;
};

struct KDEVERLANGPARSER_EXPORT CrClausesAst: public AstNode
{
    enum { KIND = CrClausesKind };

    const KDevPG::ListNode<CrClauseAst *> *ccSequence;
};

struct KDEVERLANGPARSER_EXPORT ExportDeclarationAst: public AstNode
{
    enum { KIND = ExportDeclarationKind };

    const KDevPG::ListNode<FunctionSlashArityAst *> *exported_functionsSequence;
};

struct KDEVERLANGPARSER_EXPORT ExprAst: public AstNode
{
    enum { KIND = ExprKind };

    ExprAst *expr;
    Expr100Ast *expr100;
};

struct KDEVERLANGPARSER_EXPORT Expr100Ast: public AstNode
{
    enum { KIND = Expr100Kind };

    Expr150Ast *expr150;
    Expr100Ast *expr100;
};

struct KDEVERLANGPARSER_EXPORT Expr150Ast: public AstNode
{
    enum { KIND = Expr150Kind };

    Expr160Ast *expr160;
    Expr150Ast *expr150;
};

struct KDEVERLANGPARSER_EXPORT Expr160Ast: public AstNode
{
    enum { KIND = Expr160Kind };

    Expr200Ast *expr120;
    Expr160Ast *expr160;
};

struct KDEVERLANGPARSER_EXPORT Expr200Ast: public AstNode
{
    enum { KIND = Expr200Kind };

    Expr300Ast *expr300;
    CompOpAst *comp_op;
};

struct KDEVERLANGPARSER_EXPORT Expr300Ast: public AstNode
{
    enum { KIND = Expr300Kind };

    Expr400Ast *expr400;
    ListOpAst *list_op;
    Expr300Ast *expr300;
};

struct KDEVERLANGPARSER_EXPORT Expr400Ast: public AstNode
{
    enum { KIND = Expr400Kind };

    Expr500Ast *expr500;
    Expr400aAst *expr400a;
};

struct KDEVERLANGPARSER_EXPORT Expr400aAst: public AstNode
{
    enum { KIND = Expr400aKind };

    AddOpAst *add_op;
    Expr500Ast *expr500;
    Expr400aAst *expr400;
};

struct KDEVERLANGPARSER_EXPORT Expr500Ast: public AstNode
{
    enum { KIND = Expr500Kind };

    Expr600Ast *expr600;
    Expr500aAst *expr500;
};

struct KDEVERLANGPARSER_EXPORT Expr500aAst: public AstNode
{
    enum { KIND = Expr500aKind };

    MultOpAst *mult_op;
    Expr600Ast *expr600;
    Expr500aAst *expr500a;
};

struct KDEVERLANGPARSER_EXPORT Expr600Ast: public AstNode
{
    enum { KIND = Expr600Kind };

    PrefixOpAst *prefix_op;
    Expr700Ast *expr700;
};

struct KDEVERLANGPARSER_EXPORT Expr700Ast: public AstNode
{
    enum { KIND = Expr700Kind };

    RecordExprAst *record_expr;
    Expr800Ast *expr800;
    FunctionCallAst *functionCall;
};

struct KDEVERLANGPARSER_EXPORT Expr800Ast: public AstNode
{
    enum { KIND = Expr800Kind };

    Expr900Ast *expr900;
    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT Expr900Ast: public AstNode
{
    enum { KIND = Expr900Kind };

    Expr900aAst *expr900a;
    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT Expr900aAst: public AstNode
{
    enum { KIND = Expr900aKind };

    Expr900aAst *expr900a;
    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT ExprMaxAst: public AstNode
{
    enum { KIND = ExprMaxKind };

    qint64 variable;
    AtomicAst *atomic;
    BinaryAst *binary;
    BinaryComprehensionAst *binary_comprehension;
    ExprAst *expr;
    TailAst *tail;
    ListComprehensionAst *list_comprehension;
    TupleAst *tuple;
    ExprsAst *exprs;
    IfExprAst *if_expr;
    CaseExprAst *case_expr;
    ReceiveExprAst *receive_expr;
    FunExprAst *fun_expr;
    TryExprAst *try_expr;
    QueryExprAst *query_expr;
};

struct KDEVERLANGPARSER_EXPORT ExprOrTypedExprAst: public AstNode
{
    enum { KIND = ExprOrTypedExprKind };

    TypedExprAst *typed_expr;
    ExprAst *expr;
};

struct KDEVERLANGPARSER_EXPORT ExprsAst: public AstNode
{
    enum { KIND = ExprsKind };

    const KDevPG::ListNode<ExprAst *> *eSequence;
};

struct KDEVERLANGPARSER_EXPORT FieldTypeAst: public AstNode
{
    enum { KIND = FieldTypeKind };

    TopTypeAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT FieldTypesAst: public AstNode
{
    enum { KIND = FieldTypesKind };

    const KDevPG::ListNode<FieldTypeAst *> *ftSequence;
};

struct KDEVERLANGPARSER_EXPORT FileDeclarationAst: public AstNode
{
    enum { KIND = FileDeclarationKind };

    qint64 file_name;
    qint64 line;
};

struct KDEVERLANGPARSER_EXPORT FormAst: public AstNode
{
    enum { KIND = FormKind };

    FunctionOrRuleAst *functions;
    AttributeAst *attribute;
};

struct KDEVERLANGPARSER_EXPORT FunClauseAst: public AstNode
{
    enum { KIND = FunClauseKind };

    ArgumentListAst *argument_list;
    ClauseGuardAst *clause_guard;
    ClauseBodyAst *clause_body;
};

struct KDEVERLANGPARSER_EXPORT FunClausesAst: public AstNode
{
    enum { KIND = FunClausesKind };

    const KDevPG::ListNode<FunClauseAst *> *fcSequence;
};

struct KDEVERLANGPARSER_EXPORT FunExprAst: public AstNode
{
    enum { KIND = FunExprKind };

};

struct KDEVERLANGPARSER_EXPORT FunTypeAst: public AstNode
{
    enum { KIND = FunTypeKind };

    TopTypesAst *top_types;
    TopTypeAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT FunType100Ast: public AstNode
{
    enum { KIND = FunType100Kind };

    TopTypesAst *top_types;
    TopTypeAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT FunctionCallAst: public AstNode
{
    enum { KIND = FunctionCallKind };

    Expr800Ast *expr800;
    ArgumentListAst *argument_list;
};

struct KDEVERLANGPARSER_EXPORT FunctionOrRuleAst: public AstNode
{
    enum { KIND = FunctionOrRuleKind };

    const KDevPG::ListNode<FunctionOrRuleClauseAst *> *fcSequence;
};

struct KDEVERLANGPARSER_EXPORT FunctionOrRuleClauseAst: public AstNode
{
    enum { KIND = FunctionOrRuleClauseKind };

    Atom1Ast *function_name;
    ClauseArgsAst *clause_args;
    ClauseGuardAst *clause_guard;
    ClauseBodyAst *body;
    RuleBodyAst *rule_body;
};

struct KDEVERLANGPARSER_EXPORT FunctionSlashArityAst: public AstNode
{
    enum { KIND = FunctionSlashArityKind };

    qint64 function_name;
    qint64 function_arity;
};

struct KDEVERLANGPARSER_EXPORT GuardAst: public AstNode
{
    enum { KIND = GuardKind };

    ExprsAst *expr;
    GuardAst *guard;
};

struct KDEVERLANGPARSER_EXPORT IfClauseAst: public AstNode
{
    enum { KIND = IfClauseKind };

    GuardAst *guard;
    ClauseBodyAst *clause_body;
};

struct KDEVERLANGPARSER_EXPORT IfClausesAst: public AstNode
{
    enum { KIND = IfClausesKind };

    const KDevPG::ListNode<IfClauseAst *> *icSequence;
};

struct KDEVERLANGPARSER_EXPORT IfExprAst: public AstNode
{
    enum { KIND = IfExprKind };

    IfClausesAst *if_clauses;
};

struct KDEVERLANGPARSER_EXPORT ImportDeclarationAst: public AstNode
{
    enum { KIND = ImportDeclarationKind };

    qint64 module_name;
    const KDevPG::ListNode<FunctionSlashArityAst *> *imported_functionsSequence;
};

struct KDEVERLANGPARSER_EXPORT LcExprAst: public AstNode
{
    enum { KIND = LcExprKind };

    ExprAst *expr;
    BinaryAst *binary;
};

struct KDEVERLANGPARSER_EXPORT LcExprsAst: public AstNode
{
    enum { KIND = LcExprsKind };

    const KDevPG::ListNode<LcExprAst *> *lcSequence;
};

struct KDEVERLANGPARSER_EXPORT ListComprehensionAst: public AstNode
{
    enum { KIND = ListComprehensionKind };

    ExprAst *expr;
    LcExprsAst *lc_exprs;
};

struct KDEVERLANGPARSER_EXPORT ListOpAst: public AstNode
{
    enum { KIND = ListOpKind };

};

struct KDEVERLANGPARSER_EXPORT ModuleDeclarationAst: public AstNode
{
    enum { KIND = ModuleDeclarationKind };

    qint64 module_name;
};

struct KDEVERLANGPARSER_EXPORT MultOpAst: public AstNode
{
    enum { KIND = MultOpKind };

};

struct KDEVERLANGPARSER_EXPORT OptBitSizeExprAst: public AstNode
{
    enum { KIND = OptBitSizeExprKind };

    BitSizeExprAst *bit_size_expr;
};

struct KDEVERLANGPARSER_EXPORT OptBitTypeListAst: public AstNode
{
    enum { KIND = OptBitTypeListKind };

    BitTypeListAst *bit_type_list;
};

struct KDEVERLANGPARSER_EXPORT PrefixOpAst: public AstNode
{
    enum { KIND = PrefixOpKind };

};

struct KDEVERLANGPARSER_EXPORT QueryExprAst: public AstNode
{
    enum { KIND = QueryExprKind };

    ListComprehensionAst *list_comprehension;
};

struct KDEVERLANGPARSER_EXPORT ReceiveExprAst: public AstNode
{
    enum { KIND = ReceiveExprKind };

    CrClausesAst *cr_clauses;
    ClauseBodyAst *clause_body;
};

struct KDEVERLANGPARSER_EXPORT RecordDeclarationAst: public AstNode
{
    enum { KIND = RecordDeclarationKind };

    qint64 record_name;
    TypedRecordFieldsAst *type_record_fields;
};

struct KDEVERLANGPARSER_EXPORT RecordExprAst: public AstNode
{
    enum { KIND = RecordExprKind };

    RecordTupleAst *record_tuple;
    ExprMaxAst *expr_max;
};

struct KDEVERLANGPARSER_EXPORT RecordFieldAst: public AstNode
{
    enum { KIND = RecordFieldKind };

    ExprAst *expr;
};

struct KDEVERLANGPARSER_EXPORT RecordFieldsAst: public AstNode
{
    enum { KIND = RecordFieldsKind };

    const KDevPG::ListNode<RecordFieldAst *> *rfSequence;
};

struct KDEVERLANGPARSER_EXPORT RecordTupleAst: public AstNode
{
    enum { KIND = RecordTupleKind };

    RecordFieldsAst *record_fields;
};

struct KDEVERLANGPARSER_EXPORT RuleBodyAst: public AstNode
{
    enum { KIND = RuleBodyKind };

    LcExprsAst *lc_exprs;
};

struct KDEVERLANGPARSER_EXPORT RuleClauseAst: public AstNode
{
    enum { KIND = RuleClauseKind };

    ClauseArgsAst *clause_args;
    ClauseGuardAst *clause_guard;
    RuleBodyAst *rule_body;
};

struct KDEVERLANGPARSER_EXPORT RuleClausesAst: public AstNode
{
    enum { KIND = RuleClausesKind };

    const KDevPG::ListNode<RuleClauseAst *> *rcSequence;
};

struct KDEVERLANGPARSER_EXPORT SpecFunAst: public AstNode
{
    enum { KIND = SpecFunKind };

};

struct KDEVERLANGPARSER_EXPORT TailAst: public AstNode
{
    enum { KIND = TailKind };

    ExprAst *expr;
    TailAst *tail;
};

struct KDEVERLANGPARSER_EXPORT TopTypeAst: public AstNode
{
    enum { KIND = TopTypeKind };

    TopType100Ast *top_type100;
};

struct KDEVERLANGPARSER_EXPORT TopType100Ast: public AstNode
{
    enum { KIND = TopType100Kind };

    TypeAst *type;
    TopType100Ast *top_type100;
};

struct KDEVERLANGPARSER_EXPORT TopTypesAst: public AstNode
{
    enum { KIND = TopTypesKind };

    const KDevPG::ListNode<TopTypeAst *> *ttSequence;
};

struct KDEVERLANGPARSER_EXPORT TryCatchAst: public AstNode
{
    enum { KIND = TryCatchKind };

    TryClausesAst *try_clauses;
    ExprsAst *exprs;
};

struct KDEVERLANGPARSER_EXPORT TryClauseAst: public AstNode
{
    enum { KIND = TryClauseKind };

    ExprAst *expr;
    ClauseGuardAst *clause_guard;
    ClauseBodyAst *clause_body;
};

struct KDEVERLANGPARSER_EXPORT TryClausesAst: public AstNode
{
    enum { KIND = TryClausesKind };

    const KDevPG::ListNode<TryClauseAst *> *tcSequence;
};

struct KDEVERLANGPARSER_EXPORT TryExprAst: public AstNode
{
    enum { KIND = TryExprKind };

    ExprsAst *exprs;
    CrClausesAst *cr_clauses;
    TryCatchAst *try_catch;
};

struct KDEVERLANGPARSER_EXPORT TupleAst: public AstNode
{
    enum { KIND = TupleKind };

};

struct KDEVERLANGPARSER_EXPORT TypeAst: public AstNode
{
    enum { KIND = TypeKind };

    TopTypeAst *top_type;
    TopTypesAst *top_types;
    FieldTypesAst *field_types;
    BinaryTypeAst *binary_type;
    FunType100Ast *fun_type100;
};

struct KDEVERLANGPARSER_EXPORT TypeGuardAst: public AstNode
{
    enum { KIND = TypeGuardKind };

    TopTypesAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT TypeGuardsAst: public AstNode
{
    enum { KIND = TypeGuardsKind };

    const KDevPG::ListNode<TypeGuardAst *> *tgSequence;
};

struct KDEVERLANGPARSER_EXPORT TypeSigAst: public AstNode
{
    enum { KIND = TypeSigKind };

    FunTypeAst *fun_type;
    TypeGuardsAst *type_guards;
};

struct KDEVERLANGPARSER_EXPORT TypeSigsAst: public AstNode
{
    enum { KIND = TypeSigsKind };

    const KDevPG::ListNode<TypeSigAst *> *tsSequence;
};

struct KDEVERLANGPARSER_EXPORT TypeSpecAst: public AstNode
{
    enum { KIND = TypeSpecKind };

    SpecFunAst *spec_fun;
    TypeSigsAst *types_sigs;
};

struct KDEVERLANGPARSER_EXPORT TypedAttrValAst: public AstNode
{
    enum { KIND = TypedAttrValKind };

    ExprAst *expr;
    TypedExprsAst *typed_exprs;
    TopTypeAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT TypedExprAst: public AstNode
{
    enum { KIND = TypedExprKind };

    TopTypeAst *top_type;
};

struct KDEVERLANGPARSER_EXPORT TypedExprsAst: public AstNode
{
    enum { KIND = TypedExprsKind };

    const KDevPG::ListNode<ExprOrTypedExprAst *> *eSequence;
};

struct KDEVERLANGPARSER_EXPORT TypedRecordFieldsAst: public AstNode
{
    enum { KIND = TypedRecordFieldsKind };

    TypedExprsAst *typed_exprs;
};



} // end of namespace erlang

#endif

