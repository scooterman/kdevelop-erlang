// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef ERLANG_DEFAULT_VISITOR_H_INCLUDED
#define ERLANG_DEFAULT_VISITOR_H_INCLUDED

#include "erlangvisitor.h"

#include <parserexport.h>
namespace erlang
{

class KDEVERLANGPARSER_EXPORT DefaultVisitor: public Visitor
{
public:
    virtual void visitAddOp(AddOpAst *node);
    virtual void visitArgumentList(ArgumentListAst *node);
    virtual void visitAtom1(Atom1Ast *node);
    virtual void visitAtomic(AtomicAst *node);
    virtual void visitAttrVal(AttrValAst *node);
    virtual void visitAttribute(AttributeAst *node);
    virtual void visitAttributeDeclaration(AttributeDeclarationAst *node);
    virtual void visitBinBaseType(BinBaseTypeAst *node);
    virtual void visitBinElement(BinElementAst *node);
    virtual void visitBinElements(BinElementsAst *node);
    virtual void visitBinUnitType(BinUnitTypeAst *node);
    virtual void visitBinary(BinaryAst *node);
    virtual void visitBinaryComprehension(BinaryComprehensionAst *node);
    virtual void visitBinaryType(BinaryTypeAst *node);
    virtual void visitBitExpr(BitExprAst *node);
    virtual void visitBitSizeExpr(BitSizeExprAst *node);
    virtual void visitBitType(BitTypeAst *node);
    virtual void visitBitTypeList(BitTypeListAst *node);
    virtual void visitCaseExpr(CaseExprAst *node);
    virtual void visitClauseArgs(ClauseArgsAst *node);
    virtual void visitClauseBody(ClauseBodyAst *node);
    virtual void visitClauseGuard(ClauseGuardAst *node);
    virtual void visitCompOp(CompOpAst *node);
    virtual void visitCrClause(CrClauseAst *node);
    virtual void visitCrClauses(CrClausesAst *node);
    virtual void visitExportDeclaration(ExportDeclarationAst *node);
    virtual void visitExpr(ExprAst *node);
    virtual void visitExpr100(Expr100Ast *node);
    virtual void visitExpr150(Expr150Ast *node);
    virtual void visitExpr160(Expr160Ast *node);
    virtual void visitExpr200(Expr200Ast *node);
    virtual void visitExpr300(Expr300Ast *node);
    virtual void visitExpr400(Expr400Ast *node);
    virtual void visitExpr400a(Expr400aAst *node);
    virtual void visitExpr500(Expr500Ast *node);
    virtual void visitExpr500a(Expr500aAst *node);
    virtual void visitExpr600(Expr600Ast *node);
    virtual void visitExpr700(Expr700Ast *node);
    virtual void visitExpr800(Expr800Ast *node);
    virtual void visitExpr900(Expr900Ast *node);
    virtual void visitExpr900a(Expr900aAst *node);
    virtual void visitExprMax(ExprMaxAst *node);
    virtual void visitExprOrTypedExpr(ExprOrTypedExprAst *node);
    virtual void visitExprs(ExprsAst *node);
    virtual void visitFieldType(FieldTypeAst *node);
    virtual void visitFieldTypes(FieldTypesAst *node);
    virtual void visitFileDeclaration(FileDeclarationAst *node);
    virtual void visitForm(FormAst *node);
    virtual void visitFunClause(FunClauseAst *node);
    virtual void visitFunClauses(FunClausesAst *node);
    virtual void visitFunExpr(FunExprAst *node);
    virtual void visitFunType(FunTypeAst *node);
    virtual void visitFunType100(FunType100Ast *node);
    virtual void visitFunctionCall(FunctionCallAst *node);
    virtual void visitFunctionOrRule(FunctionOrRuleAst *node);
    virtual void visitFunctionOrRuleClause(FunctionOrRuleClauseAst *node);
    virtual void visitFunctionSlashArity(FunctionSlashArityAst *node);
    virtual void visitGuard(GuardAst *node);
    virtual void visitIfClause(IfClauseAst *node);
    virtual void visitIfClauses(IfClausesAst *node);
    virtual void visitIfExpr(IfExprAst *node);
    virtual void visitImportDeclaration(ImportDeclarationAst *node);
    virtual void visitLcExpr(LcExprAst *node);
    virtual void visitLcExprs(LcExprsAst *node);
    virtual void visitListComprehension(ListComprehensionAst *node);
    virtual void visitListOp(ListOpAst *node);
    virtual void visitModuleDeclaration(ModuleDeclarationAst *node);
    virtual void visitMultOp(MultOpAst *node);
    virtual void visitOptBitSizeExpr(OptBitSizeExprAst *node);
    virtual void visitOptBitTypeList(OptBitTypeListAst *node);
    virtual void visitPrefixOp(PrefixOpAst *node);
    virtual void visitQueryExpr(QueryExprAst *node);
    virtual void visitReceiveExpr(ReceiveExprAst *node);
    virtual void visitRecordDeclaration(RecordDeclarationAst *node);
    virtual void visitRecordExpr(RecordExprAst *node);
    virtual void visitRecordField(RecordFieldAst *node);
    virtual void visitRecordFields(RecordFieldsAst *node);
    virtual void visitRecordTuple(RecordTupleAst *node);
    virtual void visitRuleBody(RuleBodyAst *node);
    virtual void visitRuleClause(RuleClauseAst *node);
    virtual void visitRuleClauses(RuleClausesAst *node);
    virtual void visitSpecFun(SpecFunAst *node);
    virtual void visitTail(TailAst *node);
    virtual void visitTopType(TopTypeAst *node);
    virtual void visitTopType100(TopType100Ast *node);
    virtual void visitTopTypes(TopTypesAst *node);
    virtual void visitTryCatch(TryCatchAst *node);
    virtual void visitTryClause(TryClauseAst *node);
    virtual void visitTryClauses(TryClausesAst *node);
    virtual void visitTryExpr(TryExprAst *node);
    virtual void visitTuple(TupleAst *node);
    virtual void visitType(TypeAst *node);
    virtual void visitTypeGuard(TypeGuardAst *node);
    virtual void visitTypeGuards(TypeGuardsAst *node);
    virtual void visitTypeSig(TypeSigAst *node);
    virtual void visitTypeSigs(TypeSigsAst *node);
    virtual void visitTypeSpec(TypeSpecAst *node);
    virtual void visitTypedAttrVal(TypedAttrValAst *node);
    virtual void visitTypedExpr(TypedExprAst *node);
    virtual void visitTypedExprs(TypedExprsAst *node);
    virtual void visitTypedRecordFields(TypedRecordFieldsAst *node);
};

} // end of namespace erlang

#endif

