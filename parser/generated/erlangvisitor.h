// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef ERLANG_VISITOR_H_INCLUDED
#define ERLANG_VISITOR_H_INCLUDED

#include "erlangast.h"

#include <parserexport.h>
namespace erlang
{

class KDEVERLANGPARSER_EXPORT Visitor
{
    typedef void (Visitor::*ParserFuncType)(AstNode *);
    static ParserFuncType sParserTable[];

public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node)
    {
        if (node) (this->*sParserTable[node->kind - 1000])(node);
    }
    virtual void visitAddOp(AddOpAst *) {}
    virtual void visitArgumentList(ArgumentListAst *) {}
    virtual void visitAtom1(Atom1Ast *) {}
    virtual void visitAtomic(AtomicAst *) {}
    virtual void visitAttrVal(AttrValAst *) {}
    virtual void visitAttribute(AttributeAst *) {}
    virtual void visitAttributeDeclaration(AttributeDeclarationAst *) {}
    virtual void visitBehaviourDeclaration(BehaviourDeclarationAst *) {}
    virtual void visitBinBaseType(BinBaseTypeAst *) {}
    virtual void visitBinElement(BinElementAst *) {}
    virtual void visitBinElements(BinElementsAst *) {}
    virtual void visitBinUnitType(BinUnitTypeAst *) {}
    virtual void visitBinary(BinaryAst *) {}
    virtual void visitBinaryComprehension(BinaryComprehensionAst *) {}
    virtual void visitBinaryType(BinaryTypeAst *) {}
    virtual void visitBitExpr(BitExprAst *) {}
    virtual void visitBitSizeExpr(BitSizeExprAst *) {}
    virtual void visitBitType(BitTypeAst *) {}
    virtual void visitBitTypeList(BitTypeListAst *) {}
    virtual void visitCaseExpr(CaseExprAst *) {}
    virtual void visitClauseArgs(ClauseArgsAst *) {}
    virtual void visitClauseBody(ClauseBodyAst *) {}
    virtual void visitClauseGuard(ClauseGuardAst *) {}
    virtual void visitCompOp(CompOpAst *) {}
    virtual void visitCrClause(CrClauseAst *) {}
    virtual void visitCrClauses(CrClausesAst *) {}
    virtual void visitExportDeclaration(ExportDeclarationAst *) {}
    virtual void visitExpr(ExprAst *) {}
    virtual void visitExpr100(Expr100Ast *) {}
    virtual void visitExpr150(Expr150Ast *) {}
    virtual void visitExpr160(Expr160Ast *) {}
    virtual void visitExpr200(Expr200Ast *) {}
    virtual void visitExpr300(Expr300Ast *) {}
    virtual void visitExpr400(Expr400Ast *) {}
    virtual void visitExpr400a(Expr400aAst *) {}
    virtual void visitExpr500(Expr500Ast *) {}
    virtual void visitExpr500a(Expr500aAst *) {}
    virtual void visitExpr600(Expr600Ast *) {}
    virtual void visitExpr700(Expr700Ast *) {}
    virtual void visitExpr800(Expr800Ast *) {}
    virtual void visitExpr900(Expr900Ast *) {}
    virtual void visitExpr900a(Expr900aAst *) {}
    virtual void visitExprMax(ExprMaxAst *) {}
    virtual void visitExprOrTypedExpr(ExprOrTypedExprAst *) {}
    virtual void visitExprs(ExprsAst *) {}
    virtual void visitFieldType(FieldTypeAst *) {}
    virtual void visitFieldTypes(FieldTypesAst *) {}
    virtual void visitFileDeclaration(FileDeclarationAst *) {}
    virtual void visitForm(FormAst *) {}
    virtual void visitFunClause(FunClauseAst *) {}
    virtual void visitFunClauses(FunClausesAst *) {}
    virtual void visitFunExpr(FunExprAst *) {}
    virtual void visitFunType(FunTypeAst *) {}
    virtual void visitFunType100(FunType100Ast *) {}
    virtual void visitFunctionCall(FunctionCallAst *) {}
    virtual void visitFunctionOrRule(FunctionOrRuleAst *) {}
    virtual void visitFunctionOrRuleClause(FunctionOrRuleClauseAst *) {}
    virtual void visitFunctionSlashArity(FunctionSlashArityAst *) {}
    virtual void visitGuard(GuardAst *) {}
    virtual void visitIfClause(IfClauseAst *) {}
    virtual void visitIfClauses(IfClausesAst *) {}
    virtual void visitIfExpr(IfExprAst *) {}
    virtual void visitImportDeclaration(ImportDeclarationAst *) {}
    virtual void visitLcExpr(LcExprAst *) {}
    virtual void visitLcExprs(LcExprsAst *) {}
    virtual void visitListComprehension(ListComprehensionAst *) {}
    virtual void visitListOp(ListOpAst *) {}
    virtual void visitModuleDeclaration(ModuleDeclarationAst *) {}
    virtual void visitMultOp(MultOpAst *) {}
    virtual void visitOptBitSizeExpr(OptBitSizeExprAst *) {}
    virtual void visitOptBitTypeList(OptBitTypeListAst *) {}
    virtual void visitPrefixOp(PrefixOpAst *) {}
    virtual void visitQueryExpr(QueryExprAst *) {}
    virtual void visitReceiveExpr(ReceiveExprAst *) {}
    virtual void visitRecordDeclaration(RecordDeclarationAst *) {}
    virtual void visitRecordExpr(RecordExprAst *) {}
    virtual void visitRecordField(RecordFieldAst *) {}
    virtual void visitRecordFields(RecordFieldsAst *) {}
    virtual void visitRecordTuple(RecordTupleAst *) {}
    virtual void visitRuleBody(RuleBodyAst *) {}
    virtual void visitRuleClause(RuleClauseAst *) {}
    virtual void visitRuleClauses(RuleClausesAst *) {}
    virtual void visitSpecFun(SpecFunAst *) {}
    virtual void visitTail(TailAst *) {}
    virtual void visitTopType(TopTypeAst *) {}
    virtual void visitTopType100(TopType100Ast *) {}
    virtual void visitTopTypes(TopTypesAst *) {}
    virtual void visitTryCatch(TryCatchAst *) {}
    virtual void visitTryClause(TryClauseAst *) {}
    virtual void visitTryClauses(TryClausesAst *) {}
    virtual void visitTryExpr(TryExprAst *) {}
    virtual void visitTuple(TupleAst *) {}
    virtual void visitType(TypeAst *) {}
    virtual void visitTypeGuard(TypeGuardAst *) {}
    virtual void visitTypeGuards(TypeGuardsAst *) {}
    virtual void visitTypeSig(TypeSigAst *) {}
    virtual void visitTypeSigs(TypeSigsAst *) {}
    virtual void visitTypeSpec(TypeSpecAst *) {}
    virtual void visitTypedAttrVal(TypedAttrValAst *) {}
    virtual void visitTypedExpr(TypedExprAst *) {}
    virtual void visitTypedExprs(TypedExprsAst *) {}
    virtual void visitTypedRecordFields(TypedRecordFieldsAst *) {}
};

} // end of namespace erlang

#endif

