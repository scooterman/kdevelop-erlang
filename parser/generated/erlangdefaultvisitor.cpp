// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "erlangdefaultvisitor.h"

namespace erlang
{

void DefaultVisitor::visitAddOp(AddOpAst *)
{
}

void DefaultVisitor::visitArgumentList(ArgumentListAst *node)
{
    visitNode(node->exprs);
}

void DefaultVisitor::visitAtom1(Atom1Ast *)
{
}

void DefaultVisitor::visitAtomic(AtomicAst *)
{
}

void DefaultVisitor::visitAttrVal(AttrValAst *node)
{
    visitNode(node->expr);
    visitNode(node->exprs);
}

void DefaultVisitor::visitAttribute(AttributeAst *node)
{
    visitNode(node->type_spec);
    visitNode(node->module_declaration);
    visitNode(node->export_declaration);
    visitNode(node->import_declaration);
    visitNode(node->record_declaration);
    visitNode(node->file_declaration);
    visitNode(node->behaviour_declaration);
    visitNode(node->attribute_declaration);
}

void DefaultVisitor::visitAttributeDeclaration(AttributeDeclarationAst *)
{
}

void DefaultVisitor::visitBehaviourDeclaration(BehaviourDeclarationAst *)
{
}

void DefaultVisitor::visitBinBaseType(BinBaseTypeAst *)
{
}

void DefaultVisitor::visitBinElement(BinElementAst *node)
{
    visitNode(node->bit_expr);
    visitNode(node->opt_bit_size_expr);
    visitNode(node->opt_bit_type_list);
}

void DefaultVisitor::visitBinElements(BinElementsAst *node)
{
    if (node->beSequence)
    {
        const KDevPG::ListNode<BinElementAst*> *__it = node->beSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBinUnitType(BinUnitTypeAst *)
{
}

void DefaultVisitor::visitBinary(BinaryAst *node)
{
    visitNode(node->bin_elements);
}

void DefaultVisitor::visitBinaryComprehension(BinaryComprehensionAst *node)
{
    visitNode(node->binary);
    visitNode(node->lc_exprs);
}

void DefaultVisitor::visitBinaryType(BinaryTypeAst *node)
{
    visitNode(node->bin_unit_type);
}

void DefaultVisitor::visitBitExpr(BitExprAst *node)
{
    visitNode(node->prefix_op);
    visitNode(node->expr_max);
}

void DefaultVisitor::visitBitSizeExpr(BitSizeExprAst *node)
{
    visitNode(node->expr_max);
}

void DefaultVisitor::visitBitType(BitTypeAst *)
{
}

void DefaultVisitor::visitBitTypeList(BitTypeListAst *node)
{
    visitNode(node->bit_type);
    visitNode(node->bit_type_list);
}

void DefaultVisitor::visitCaseExpr(CaseExprAst *node)
{
    visitNode(node->expr);
    visitNode(node->cr_clauses);
}

void DefaultVisitor::visitClauseArgs(ClauseArgsAst *node)
{
    visitNode(node->argument_list);
}

void DefaultVisitor::visitClauseBody(ClauseBodyAst *node)
{
    visitNode(node->exprs);
}

void DefaultVisitor::visitClauseGuard(ClauseGuardAst *node)
{
    visitNode(node->guard);
}

void DefaultVisitor::visitCompOp(CompOpAst *)
{
}

void DefaultVisitor::visitCrClause(CrClauseAst *node)
{
    visitNode(node->clause_guard);
    visitNode(node->clause_body);
}

void DefaultVisitor::visitCrClauses(CrClausesAst *node)
{
    if (node->ccSequence)
    {
        const KDevPG::ListNode<CrClauseAst*> *__it = node->ccSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExportDeclaration(ExportDeclarationAst *node)
{
    if (node->exported_functionsSequence)
    {
        const KDevPG::ListNode<FunctionSlashArityAst*> *__it = node->exported_functionsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExpr(ExprAst *node)
{
    visitNode(node->expr);
    visitNode(node->expr100);
}

void DefaultVisitor::visitExpr100(Expr100Ast *node)
{
    visitNode(node->expr150);
    visitNode(node->expr100);
}

void DefaultVisitor::visitExpr150(Expr150Ast *node)
{
    visitNode(node->expr160);
    visitNode(node->expr150);
}

void DefaultVisitor::visitExpr160(Expr160Ast *node)
{
    visitNode(node->expr120);
    visitNode(node->expr160);
}

void DefaultVisitor::visitExpr200(Expr200Ast *node)
{
    visitNode(node->expr300);
    visitNode(node->comp_op);
}

void DefaultVisitor::visitExpr300(Expr300Ast *node)
{
    visitNode(node->expr400);
    visitNode(node->list_op);
    visitNode(node->expr300);
}

void DefaultVisitor::visitExpr400(Expr400Ast *node)
{
    visitNode(node->expr500);
    visitNode(node->expr400a);
}

void DefaultVisitor::visitExpr400a(Expr400aAst *node)
{
    visitNode(node->add_op);
    visitNode(node->expr500);
    visitNode(node->expr400);
}

void DefaultVisitor::visitExpr500(Expr500Ast *node)
{
    visitNode(node->expr600);
    visitNode(node->expr500);
}

void DefaultVisitor::visitExpr500a(Expr500aAst *node)
{
    visitNode(node->mult_op);
    visitNode(node->expr600);
    visitNode(node->expr500a);
}

void DefaultVisitor::visitExpr600(Expr600Ast *node)
{
    visitNode(node->prefix_op);
    visitNode(node->expr700);
}

void DefaultVisitor::visitExpr700(Expr700Ast *node)
{
    visitNode(node->record_expr);
    visitNode(node->expr800);
    visitNode(node->functionCall);
}

void DefaultVisitor::visitExpr800(Expr800Ast *node)
{
    visitNode(node->expr900);
    visitNode(node->expr_max);
}

void DefaultVisitor::visitExpr900(Expr900Ast *node)
{
    visitNode(node->expr900a);
    visitNode(node->expr_max);
}

void DefaultVisitor::visitExpr900a(Expr900aAst *node)
{
    visitNode(node->expr900a);
    visitNode(node->expr_max);
}

void DefaultVisitor::visitExprMax(ExprMaxAst *node)
{
    visitNode(node->atomic);
    visitNode(node->binary);
    visitNode(node->binary_comprehension);
    visitNode(node->expr);
    visitNode(node->tail);
    visitNode(node->list_comprehension);
    visitNode(node->tuple);
    visitNode(node->exprs);
    visitNode(node->if_expr);
    visitNode(node->case_expr);
    visitNode(node->receive_expr);
    visitNode(node->fun_expr);
    visitNode(node->try_expr);
    visitNode(node->query_expr);
}

void DefaultVisitor::visitExprOrTypedExpr(ExprOrTypedExprAst *node)
{
    visitNode(node->typed_expr);
    visitNode(node->expr);
}

void DefaultVisitor::visitExprs(ExprsAst *node)
{
    if (node->eSequence)
    {
        const KDevPG::ListNode<ExprAst*> *__it = node->eSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFieldType(FieldTypeAst *node)
{
    visitNode(node->top_type);
}

void DefaultVisitor::visitFieldTypes(FieldTypesAst *node)
{
    if (node->ftSequence)
    {
        const KDevPG::ListNode<FieldTypeAst*> *__it = node->ftSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFileDeclaration(FileDeclarationAst *)
{
}

void DefaultVisitor::visitForm(FormAst *node)
{
    visitNode(node->functions);
    visitNode(node->attribute);
}

void DefaultVisitor::visitFunClause(FunClauseAst *node)
{
    visitNode(node->argument_list);
    visitNode(node->clause_guard);
    visitNode(node->clause_body);
}

void DefaultVisitor::visitFunClauses(FunClausesAst *node)
{
    if (node->fcSequence)
    {
        const KDevPG::ListNode<FunClauseAst*> *__it = node->fcSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFunExpr(FunExprAst *)
{
}

void DefaultVisitor::visitFunType(FunTypeAst *node)
{
    visitNode(node->top_types);
    visitNode(node->top_type);
}

void DefaultVisitor::visitFunType100(FunType100Ast *node)
{
    visitNode(node->top_types);
    visitNode(node->top_type);
}

void DefaultVisitor::visitFunctionCall(FunctionCallAst *node)
{
    visitNode(node->expr800);
    visitNode(node->argument_list);
}

void DefaultVisitor::visitFunctionOrRule(FunctionOrRuleAst *node)
{
    if (node->fcSequence)
    {
        const KDevPG::ListNode<FunctionOrRuleClauseAst*> *__it = node->fcSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFunctionOrRuleClause(FunctionOrRuleClauseAst *node)
{
    visitNode(node->function_name);
    visitNode(node->clause_args);
    visitNode(node->clause_guard);
    visitNode(node->body);
    visitNode(node->rule_body);
}

void DefaultVisitor::visitFunctionSlashArity(FunctionSlashArityAst *)
{
}

void DefaultVisitor::visitGuard(GuardAst *node)
{
    visitNode(node->expr);
    visitNode(node->guard);
}

void DefaultVisitor::visitIfClause(IfClauseAst *node)
{
    visitNode(node->guard);
    visitNode(node->clause_body);
}

void DefaultVisitor::visitIfClauses(IfClausesAst *node)
{
    if (node->icSequence)
    {
        const KDevPG::ListNode<IfClauseAst*> *__it = node->icSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitIfExpr(IfExprAst *node)
{
    visitNode(node->if_clauses);
}

void DefaultVisitor::visitImportDeclaration(ImportDeclarationAst *node)
{
    if (node->imported_functionsSequence)
    {
        const KDevPG::ListNode<FunctionSlashArityAst*> *__it = node->imported_functionsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLcExpr(LcExprAst *node)
{
    visitNode(node->expr);
    visitNode(node->binary);
}

void DefaultVisitor::visitLcExprs(LcExprsAst *node)
{
    if (node->lcSequence)
    {
        const KDevPG::ListNode<LcExprAst*> *__it = node->lcSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitListComprehension(ListComprehensionAst *node)
{
    visitNode(node->expr);
    visitNode(node->lc_exprs);
}

void DefaultVisitor::visitListOp(ListOpAst *)
{
}

void DefaultVisitor::visitModuleDeclaration(ModuleDeclarationAst *)
{
}

void DefaultVisitor::visitMultOp(MultOpAst *)
{
}

void DefaultVisitor::visitOptBitSizeExpr(OptBitSizeExprAst *node)
{
    visitNode(node->bit_size_expr);
}

void DefaultVisitor::visitOptBitTypeList(OptBitTypeListAst *node)
{
    visitNode(node->bit_type_list);
}

void DefaultVisitor::visitPrefixOp(PrefixOpAst *)
{
}

void DefaultVisitor::visitQueryExpr(QueryExprAst *node)
{
    visitNode(node->list_comprehension);
}

void DefaultVisitor::visitReceiveExpr(ReceiveExprAst *node)
{
    visitNode(node->cr_clauses);
    visitNode(node->clause_body);
}

void DefaultVisitor::visitRecordDeclaration(RecordDeclarationAst *node)
{
    visitNode(node->type_record_fields);
}

void DefaultVisitor::visitRecordExpr(RecordExprAst *node)
{
    visitNode(node->record_tuple);
    visitNode(node->expr_max);
}

void DefaultVisitor::visitRecordField(RecordFieldAst *node)
{
    visitNode(node->expr);
}

void DefaultVisitor::visitRecordFields(RecordFieldsAst *node)
{
    if (node->rfSequence)
    {
        const KDevPG::ListNode<RecordFieldAst*> *__it = node->rfSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitRecordTuple(RecordTupleAst *node)
{
    visitNode(node->record_fields);
}

void DefaultVisitor::visitRuleBody(RuleBodyAst *node)
{
    visitNode(node->lc_exprs);
}

void DefaultVisitor::visitRuleClause(RuleClauseAst *node)
{
    visitNode(node->clause_args);
    visitNode(node->clause_guard);
    visitNode(node->rule_body);
}

void DefaultVisitor::visitRuleClauses(RuleClausesAst *node)
{
    if (node->rcSequence)
    {
        const KDevPG::ListNode<RuleClauseAst*> *__it = node->rcSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSpecFun(SpecFunAst *)
{
}

void DefaultVisitor::visitTail(TailAst *node)
{
    visitNode(node->expr);
    visitNode(node->tail);
}

void DefaultVisitor::visitTopType(TopTypeAst *node)
{
    visitNode(node->top_type100);
}

void DefaultVisitor::visitTopType100(TopType100Ast *node)
{
    visitNode(node->type);
    visitNode(node->top_type100);
}

void DefaultVisitor::visitTopTypes(TopTypesAst *node)
{
    if (node->ttSequence)
    {
        const KDevPG::ListNode<TopTypeAst*> *__it = node->ttSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTryCatch(TryCatchAst *node)
{
    visitNode(node->try_clauses);
    visitNode(node->exprs);
}

void DefaultVisitor::visitTryClause(TryClauseAst *node)
{
    visitNode(node->expr);
    visitNode(node->clause_guard);
    visitNode(node->clause_body);
}

void DefaultVisitor::visitTryClauses(TryClausesAst *node)
{
    if (node->tcSequence)
    {
        const KDevPG::ListNode<TryClauseAst*> *__it = node->tcSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTryExpr(TryExprAst *node)
{
    visitNode(node->exprs);
    visitNode(node->cr_clauses);
    visitNode(node->try_catch);
}

void DefaultVisitor::visitTuple(TupleAst *)
{
}

void DefaultVisitor::visitType(TypeAst *node)
{
    visitNode(node->top_type);
    visitNode(node->top_types);
    visitNode(node->field_types);
    visitNode(node->binary_type);
    visitNode(node->fun_type100);
}

void DefaultVisitor::visitTypeGuard(TypeGuardAst *node)
{
    visitNode(node->top_type);
}

void DefaultVisitor::visitTypeGuards(TypeGuardsAst *node)
{
    if (node->tgSequence)
    {
        const KDevPG::ListNode<TypeGuardAst*> *__it = node->tgSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTypeSig(TypeSigAst *node)
{
    visitNode(node->fun_type);
    visitNode(node->type_guards);
}

void DefaultVisitor::visitTypeSigs(TypeSigsAst *node)
{
    if (node->tsSequence)
    {
        const KDevPG::ListNode<TypeSigAst*> *__it = node->tsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTypeSpec(TypeSpecAst *node)
{
    visitNode(node->spec_fun);
    visitNode(node->types_sigs);
}

void DefaultVisitor::visitTypedAttrVal(TypedAttrValAst *node)
{
    visitNode(node->expr);
    visitNode(node->typed_exprs);
    visitNode(node->top_type);
}

void DefaultVisitor::visitTypedExpr(TypedExprAst *node)
{
    visitNode(node->top_type);
}

void DefaultVisitor::visitTypedExprs(TypedExprsAst *node)
{
    if (node->eSequence)
    {
        const KDevPG::ListNode<ExprOrTypedExprAst*> *__it = node->eSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTypedRecordFields(TypedRecordFieldsAst *node)
{
    visitNode(node->typed_exprs);
}


} // end of namespace erlang

