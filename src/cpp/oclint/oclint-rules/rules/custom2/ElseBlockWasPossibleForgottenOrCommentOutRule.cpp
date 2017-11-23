#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ElseBlockWasPossibleForgottenOrCommentOutRule : public AbstractASTVisitorRule<ElseBlockWasPossibleForgottenOrCommentOutRule>
{
public:
    virtual const string name() const override
    {
        return "else block was possible forgotten or comment out";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "custom2";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.12";
    }

    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // TODO: modify the example for this rule.
    }
        )rst";
    }

    /* fill in the file name only when it does not match the rule identifier
    virtual const std::string fileName() const override
    {
        return "";
    }
    */

    /* add each threshold's key, description, and its default value to the map.
    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        return thresholdMapping;
    }
    */

    /* add additional document for the rule, like references, notes, etc.
    virtual const std::string additionalDocument() const override
    {
        return "";
    }
    */

    /* uncomment this method when the rule is enabled to be suppressed.
    virtual bool enableSuppress() const override
    {
        return true;
    }
    */
#endif

    virtual void setUp() override {}
    virtual void tearDown() override {}

    
    /* Visit NullStmt
    bool VisitNullStmt(NullStmt *node)
    {
        return true;
    }
     */

    /* Visit CompoundStmt
    bool VisitCompoundStmt(CompoundStmt *node)
    {
        return true;
    }
     */

    /* Visit LabelStmt
    bool VisitLabelStmt(LabelStmt *node)
    {
        return true;
    }
     */

    /* Visit AttributedStmt
    bool VisitAttributedStmt(AttributedStmt *node)
    {
        return true;
    }
     */

    /* Visit IfStmt
    bool VisitIfStmt(IfStmt *node)
    {
        return true;
    }
     */

    /* Visit SwitchStmt
    bool VisitSwitchStmt(SwitchStmt *node)
    {
        return true;
    }
     */

    /* Visit WhileStmt
    bool VisitWhileStmt(WhileStmt *node)
    {
        return true;
    }
     */

    /* Visit DoStmt
    bool VisitDoStmt(DoStmt *node)
    {
        return true;
    }
     */

    /* Visit ForStmt
    bool VisitForStmt(ForStmt *node)
    {
        return true;
    }
     */

    /* Visit GotoStmt
    bool VisitGotoStmt(GotoStmt *node)
    {
        return true;
    }
     */

    /* Visit IndirectGotoStmt
    bool VisitIndirectGotoStmt(IndirectGotoStmt *node)
    {
        return true;
    }
     */

    /* Visit ContinueStmt
    bool VisitContinueStmt(ContinueStmt *node)
    {
        return true;
    }
     */

    /* Visit BreakStmt
    bool VisitBreakStmt(BreakStmt *node)
    {
        return true;
    }
     */

    /* Visit ReturnStmt
    bool VisitReturnStmt(ReturnStmt *node)
    {
        return true;
    }
     */

    /* Visit DeclStmt 
    bool VisitDeclStmt (DeclStmt  *node)
    {
        return true;
    }
     */

    /* Visit SwitchCase
    bool VisitSwitchCase(SwitchCase *node)
    {
        return true;
    }
     */

    /* Visit CaseStmt
    bool VisitCaseStmt(CaseStmt *node)
    {
        return true;
    }
     */

    /* Visit DefaultStmt
    bool VisitDefaultStmt(DefaultStmt *node)
    {
        return true;
    }
     */

    /* Visit CapturedStmt
    bool VisitCapturedStmt(CapturedStmt *node)
    {
        return true;
    }
     */

    /* Visit AsmStmt
    bool VisitAsmStmt(AsmStmt *node)
    {
        return true;
    }
     */

    /* Visit GCCAsmStmt
    bool VisitGCCAsmStmt(GCCAsmStmt *node)
    {
        return true;
    }
     */

    /* Visit MSAsmStmt
    bool VisitMSAsmStmt(MSAsmStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtTryStmt
    bool VisitObjCAtTryStmt(ObjCAtTryStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtCatchStmt
    bool VisitObjCAtCatchStmt(ObjCAtCatchStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtFinallyStmt
    bool VisitObjCAtFinallyStmt(ObjCAtFinallyStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtThrowStmt
    bool VisitObjCAtThrowStmt(ObjCAtThrowStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtSynchronizedStmt
    bool VisitObjCAtSynchronizedStmt(ObjCAtSynchronizedStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCForCollectionStmt
    bool VisitObjCForCollectionStmt(ObjCForCollectionStmt *node)
    {
        return true;
    }
     */

    /* Visit ObjCAutoreleasePoolStmt
    bool VisitObjCAutoreleasePoolStmt(ObjCAutoreleasePoolStmt *node)
    {
        return true;
    }
     */

    /* Visit CXXCatchStmt
    bool VisitCXXCatchStmt(CXXCatchStmt *node)
    {
        return true;
    }
     */

    /* Visit CXXTryStmt
    bool VisitCXXTryStmt(CXXTryStmt *node)
    {
        return true;
    }
     */

    /* Visit CXXForRangeStmt
    bool VisitCXXForRangeStmt(CXXForRangeStmt *node)
    {
        return true;
    }
     */

    /* Visit CoroutineBodyStmt
    bool VisitCoroutineBodyStmt(CoroutineBodyStmt *node)
    {
        return true;
    }
     */

    /* Visit CoreturnStmt
    bool VisitCoreturnStmt(CoreturnStmt *node)
    {
        return true;
    }
     */

    /* Visit Expr
    bool VisitExpr(Expr *node)
    {
        return true;
    }
     */

    /* Visit PredefinedExpr
    bool VisitPredefinedExpr(PredefinedExpr *node)
    {
        return true;
    }
     */

    /* Visit DeclRefExpr
    bool VisitDeclRefExpr(DeclRefExpr *node)
    {
        return true;
    }
     */

    /* Visit IntegerLiteral
    bool VisitIntegerLiteral(IntegerLiteral *node)
    {
        return true;
    }
     */

    /* Visit FloatingLiteral
    bool VisitFloatingLiteral(FloatingLiteral *node)
    {
        return true;
    }
     */

    /* Visit ImaginaryLiteral
    bool VisitImaginaryLiteral(ImaginaryLiteral *node)
    {
        return true;
    }
     */

    /* Visit StringLiteral
    bool VisitStringLiteral(StringLiteral *node)
    {
        return true;
    }
     */

    /* Visit CharacterLiteral
    bool VisitCharacterLiteral(CharacterLiteral *node)
    {
        return true;
    }
     */

    /* Visit ParenExpr
    bool VisitParenExpr(ParenExpr *node)
    {
        return true;
    }
     */

    /* Visit UnaryOperator
    bool VisitUnaryOperator(UnaryOperator *node)
    {
        return true;
    }
     */

    /* Visit OffsetOfExpr
    bool VisitOffsetOfExpr(OffsetOfExpr *node)
    {
        return true;
    }
     */

    /* Visit UnaryExprOrTypeTraitExpr
    bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *node)
    {
        return true;
    }
     */

    /* Visit ArraySubscriptExpr
    bool VisitArraySubscriptExpr(ArraySubscriptExpr *node)
    {
        return true;
    }
     */

    /* Visit OMPArraySectionExpr
    bool VisitOMPArraySectionExpr(OMPArraySectionExpr *node)
    {
        return true;
    }
     */

    /* Visit CallExpr
    bool VisitCallExpr(CallExpr *node)
    {
        return true;
    }
     */

    /* Visit MemberExpr
    bool VisitMemberExpr(MemberExpr *node)
    {
        return true;
    }
     */

    /* Visit CastExpr
    bool VisitCastExpr(CastExpr *node)
    {
        return true;
    }
     */

    /* Visit BinaryOperator
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        return true;
    }
     */

    /* Visit CompoundAssignOperator
    bool VisitCompoundAssignOperator(CompoundAssignOperator *node)
    {
        return true;
    }
     */

    /* Visit AbstractConditionalOperator
    bool VisitAbstractConditionalOperator(AbstractConditionalOperator *node)
    {
        return true;
    }
     */

    /* Visit ConditionalOperator
    bool VisitConditionalOperator(ConditionalOperator *node)
    {
        return true;
    }
     */

    /* Visit BinaryConditionalOperator
    bool VisitBinaryConditionalOperator(BinaryConditionalOperator *node)
    {
        return true;
    }
     */

    /* Visit ImplicitCastExpr
    bool VisitImplicitCastExpr(ImplicitCastExpr *node)
    {
        return true;
    }
     */

    /* Visit ExplicitCastExpr
    bool VisitExplicitCastExpr(ExplicitCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CStyleCastExpr
    bool VisitCStyleCastExpr(CStyleCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CompoundLiteralExpr
    bool VisitCompoundLiteralExpr(CompoundLiteralExpr *node)
    {
        return true;
    }
     */

    /* Visit ExtVectorElementExpr
    bool VisitExtVectorElementExpr(ExtVectorElementExpr *node)
    {
        return true;
    }
     */

    /* Visit InitListExpr
    bool VisitInitListExpr(InitListExpr *node)
    {
        return true;
    }
     */

    /* Visit DesignatedInitExpr
    bool VisitDesignatedInitExpr(DesignatedInitExpr *node)
    {
        return true;
    }
     */

    /* Visit DesignatedInitUpdateExpr
    bool VisitDesignatedInitUpdateExpr(DesignatedInitUpdateExpr *node)
    {
        return true;
    }
     */

    /* Visit ImplicitValueInitExpr
    bool VisitImplicitValueInitExpr(ImplicitValueInitExpr *node)
    {
        return true;
    }
     */

    /* Visit NoInitExpr
    bool VisitNoInitExpr(NoInitExpr *node)
    {
        return true;
    }
     */

    /* Visit ArrayInitLoopExpr
    bool VisitArrayInitLoopExpr(ArrayInitLoopExpr *node)
    {
        return true;
    }
     */

    /* Visit ArrayInitIndexExpr
    bool VisitArrayInitIndexExpr(ArrayInitIndexExpr *node)
    {
        return true;
    }
     */

    /* Visit ParenListExpr
    bool VisitParenListExpr(ParenListExpr *node)
    {
        return true;
    }
     */

    /* Visit VAArgExpr
    bool VisitVAArgExpr(VAArgExpr *node)
    {
        return true;
    }
     */

    /* Visit GenericSelectionExpr
    bool VisitGenericSelectionExpr(GenericSelectionExpr *node)
    {
        return true;
    }
     */

    /* Visit PseudoObjectExpr
    bool VisitPseudoObjectExpr(PseudoObjectExpr *node)
    {
        return true;
    }
     */

    /* Visit AtomicExpr
    bool VisitAtomicExpr(AtomicExpr *node)
    {
        return true;
    }
     */

    /* Visit AddrLabelExpr
    bool VisitAddrLabelExpr(AddrLabelExpr *node)
    {
        return true;
    }
     */

    /* Visit StmtExpr
    bool VisitStmtExpr(StmtExpr *node)
    {
        return true;
    }
     */

    /* Visit ChooseExpr
    bool VisitChooseExpr(ChooseExpr *node)
    {
        return true;
    }
     */

    /* Visit GNUNullExpr
    bool VisitGNUNullExpr(GNUNullExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXOperatorCallExpr
    bool VisitCXXOperatorCallExpr(CXXOperatorCallExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXMemberCallExpr
    bool VisitCXXMemberCallExpr(CXXMemberCallExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXNamedCastExpr
    bool VisitCXXNamedCastExpr(CXXNamedCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXStaticCastExpr
    bool VisitCXXStaticCastExpr(CXXStaticCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXDynamicCastExpr
    bool VisitCXXDynamicCastExpr(CXXDynamicCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXReinterpretCastExpr
    bool VisitCXXReinterpretCastExpr(CXXReinterpretCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXConstCastExpr
    bool VisitCXXConstCastExpr(CXXConstCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXFunctionalCastExpr
    bool VisitCXXFunctionalCastExpr(CXXFunctionalCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXTypeidExpr
    bool VisitCXXTypeidExpr(CXXTypeidExpr *node)
    {
        return true;
    }
     */

    /* Visit UserDefinedLiteral
    bool VisitUserDefinedLiteral(UserDefinedLiteral *node)
    {
        return true;
    }
     */

    /* Visit CXXBoolLiteralExpr
    bool VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXNullPtrLiteralExpr
    bool VisitCXXNullPtrLiteralExpr(CXXNullPtrLiteralExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXThisExpr
    bool VisitCXXThisExpr(CXXThisExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXThrowExpr
    bool VisitCXXThrowExpr(CXXThrowExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXDefaultArgExpr
    bool VisitCXXDefaultArgExpr(CXXDefaultArgExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXDefaultInitExpr
    bool VisitCXXDefaultInitExpr(CXXDefaultInitExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXScalarValueInitExpr
    bool VisitCXXScalarValueInitExpr(CXXScalarValueInitExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXStdInitializerListExpr
    bool VisitCXXStdInitializerListExpr(CXXStdInitializerListExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXNewExpr
    bool VisitCXXNewExpr(CXXNewExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXDeleteExpr
    bool VisitCXXDeleteExpr(CXXDeleteExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXPseudoDestructorExpr
    bool VisitCXXPseudoDestructorExpr(CXXPseudoDestructorExpr *node)
    {
        return true;
    }
     */

    /* Visit TypeTraitExpr
    bool VisitTypeTraitExpr(TypeTraitExpr *node)
    {
        return true;
    }
     */

    /* Visit ArrayTypeTraitExpr
    bool VisitArrayTypeTraitExpr(ArrayTypeTraitExpr *node)
    {
        return true;
    }
     */

    /* Visit ExpressionTraitExpr
    bool VisitExpressionTraitExpr(ExpressionTraitExpr *node)
    {
        return true;
    }
     */

    /* Visit DependentScopeDeclRefExpr
    bool VisitDependentScopeDeclRefExpr(DependentScopeDeclRefExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXConstructExpr
    bool VisitCXXConstructExpr(CXXConstructExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXInheritedCtorInitExpr
    bool VisitCXXInheritedCtorInitExpr(CXXInheritedCtorInitExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXBindTemporaryExpr
    bool VisitCXXBindTemporaryExpr(CXXBindTemporaryExpr *node)
    {
        return true;
    }
     */

    /* Visit ExprWithCleanups
    bool VisitExprWithCleanups(ExprWithCleanups *node)
    {
        return true;
    }
     */

    /* Visit CXXTemporaryObjectExpr
    bool VisitCXXTemporaryObjectExpr(CXXTemporaryObjectExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXUnresolvedConstructExpr
    bool VisitCXXUnresolvedConstructExpr(CXXUnresolvedConstructExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXDependentScopeMemberExpr
    bool VisitCXXDependentScopeMemberExpr(CXXDependentScopeMemberExpr *node)
    {
        return true;
    }
     */

    /* Visit OverloadExpr
    bool VisitOverloadExpr(OverloadExpr *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedLookupExpr
    bool VisitUnresolvedLookupExpr(UnresolvedLookupExpr *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedMemberExpr
    bool VisitUnresolvedMemberExpr(UnresolvedMemberExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXNoexceptExpr
    bool VisitCXXNoexceptExpr(CXXNoexceptExpr *node)
    {
        return true;
    }
     */

    /* Visit PackExpansionExpr
    bool VisitPackExpansionExpr(PackExpansionExpr *node)
    {
        return true;
    }
     */

    /* Visit SizeOfPackExpr
    bool VisitSizeOfPackExpr(SizeOfPackExpr *node)
    {
        return true;
    }
     */

    /* Visit SubstNonTypeTemplateParmExpr
    bool VisitSubstNonTypeTemplateParmExpr(SubstNonTypeTemplateParmExpr *node)
    {
        return true;
    }
     */

    /* Visit SubstNonTypeTemplateParmPackExpr
    bool VisitSubstNonTypeTemplateParmPackExpr(SubstNonTypeTemplateParmPackExpr *node)
    {
        return true;
    }
     */

    /* Visit FunctionParmPackExpr
    bool VisitFunctionParmPackExpr(FunctionParmPackExpr *node)
    {
        return true;
    }
     */

    /* Visit MaterializeTemporaryExpr
    bool VisitMaterializeTemporaryExpr(MaterializeTemporaryExpr *node)
    {
        return true;
    }
     */

    /* Visit LambdaExpr
    bool VisitLambdaExpr(LambdaExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXFoldExpr
    bool VisitCXXFoldExpr(CXXFoldExpr *node)
    {
        return true;
    }
     */

    /* Visit CoroutineSuspendExpr
    bool VisitCoroutineSuspendExpr(CoroutineSuspendExpr *node)
    {
        return true;
    }
     */

    /* Visit CoawaitExpr
    bool VisitCoawaitExpr(CoawaitExpr *node)
    {
        return true;
    }
     */

    /* Visit CoyieldExpr
    bool VisitCoyieldExpr(CoyieldExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCStringLiteral
    bool VisitObjCStringLiteral(ObjCStringLiteral *node)
    {
        return true;
    }
     */

    /* Visit ObjCBoxedExpr
    bool VisitObjCBoxedExpr(ObjCBoxedExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCArrayLiteral
    bool VisitObjCArrayLiteral(ObjCArrayLiteral *node)
    {
        return true;
    }
     */

    /* Visit ObjCDictionaryLiteral
    bool VisitObjCDictionaryLiteral(ObjCDictionaryLiteral *node)
    {
        return true;
    }
     */

    /* Visit ObjCEncodeExpr
    bool VisitObjCEncodeExpr(ObjCEncodeExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCMessageExpr
    bool VisitObjCMessageExpr(ObjCMessageExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCSelectorExpr
    bool VisitObjCSelectorExpr(ObjCSelectorExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCProtocolExpr
    bool VisitObjCProtocolExpr(ObjCProtocolExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCIvarRefExpr
    bool VisitObjCIvarRefExpr(ObjCIvarRefExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCPropertyRefExpr
    bool VisitObjCPropertyRefExpr(ObjCPropertyRefExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCIsaExpr
    bool VisitObjCIsaExpr(ObjCIsaExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCIndirectCopyRestoreExpr
    bool VisitObjCIndirectCopyRestoreExpr(ObjCIndirectCopyRestoreExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCBoolLiteralExpr
    bool VisitObjCBoolLiteralExpr(ObjCBoolLiteralExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCSubscriptRefExpr
    bool VisitObjCSubscriptRefExpr(ObjCSubscriptRefExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCAvailabilityCheckExpr
    bool VisitObjCAvailabilityCheckExpr(ObjCAvailabilityCheckExpr *node)
    {
        return true;
    }
     */

    /* Visit ObjCBridgedCastExpr
    bool VisitObjCBridgedCastExpr(ObjCBridgedCastExpr *node)
    {
        return true;
    }
     */

    /* Visit CUDAKernelCallExpr
    bool VisitCUDAKernelCallExpr(CUDAKernelCallExpr *node)
    {
        return true;
    }
     */

    /* Visit ShuffleVectorExpr
    bool VisitShuffleVectorExpr(ShuffleVectorExpr *node)
    {
        return true;
    }
     */

    /* Visit ConvertVectorExpr
    bool VisitConvertVectorExpr(ConvertVectorExpr *node)
    {
        return true;
    }
     */

    /* Visit BlockExpr
    bool VisitBlockExpr(BlockExpr *node)
    {
        return true;
    }
     */

    /* Visit OpaqueValueExpr
    bool VisitOpaqueValueExpr(OpaqueValueExpr *node)
    {
        return true;
    }
     */

    /* Visit TypoExpr
    bool VisitTypoExpr(TypoExpr *node)
    {
        return true;
    }
     */

    /* Visit MSPropertyRefExpr
    bool VisitMSPropertyRefExpr(MSPropertyRefExpr *node)
    {
        return true;
    }
     */

    /* Visit MSPropertySubscriptExpr
    bool VisitMSPropertySubscriptExpr(MSPropertySubscriptExpr *node)
    {
        return true;
    }
     */

    /* Visit CXXUuidofExpr
    bool VisitCXXUuidofExpr(CXXUuidofExpr *node)
    {
        return true;
    }
     */

    /* Visit SEHTryStmt
    bool VisitSEHTryStmt(SEHTryStmt *node)
    {
        return true;
    }
     */

    /* Visit SEHExceptStmt
    bool VisitSEHExceptStmt(SEHExceptStmt *node)
    {
        return true;
    }
     */

    /* Visit SEHFinallyStmt
    bool VisitSEHFinallyStmt(SEHFinallyStmt *node)
    {
        return true;
    }
     */

    /* Visit SEHLeaveStmt
    bool VisitSEHLeaveStmt(SEHLeaveStmt *node)
    {
        return true;
    }
     */

    /* Visit MSDependentExistsStmt
    bool VisitMSDependentExistsStmt(MSDependentExistsStmt *node)
    {
        return true;
    }
     */

    /* Visit AsTypeExpr
    bool VisitAsTypeExpr(AsTypeExpr *node)
    {
        return true;
    }
     */

    /* Visit OMPExecutableDirective
    bool VisitOMPExecutableDirective(OMPExecutableDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPLoopDirective
    bool VisitOMPLoopDirective(OMPLoopDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPParallelDirective
    bool VisitOMPParallelDirective(OMPParallelDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPSimdDirective
    bool VisitOMPSimdDirective(OMPSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPForDirective
    bool VisitOMPForDirective(OMPForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPForSimdDirective
    bool VisitOMPForSimdDirective(OMPForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPSectionsDirective
    bool VisitOMPSectionsDirective(OMPSectionsDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPSectionDirective
    bool VisitOMPSectionDirective(OMPSectionDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPSingleDirective
    bool VisitOMPSingleDirective(OMPSingleDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPMasterDirective
    bool VisitOMPMasterDirective(OMPMasterDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPCriticalDirective
    bool VisitOMPCriticalDirective(OMPCriticalDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPParallelForDirective
    bool VisitOMPParallelForDirective(OMPParallelForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPParallelForSimdDirective
    bool VisitOMPParallelForSimdDirective(OMPParallelForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPParallelSectionsDirective
    bool VisitOMPParallelSectionsDirective(OMPParallelSectionsDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskDirective
    bool VisitOMPTaskDirective(OMPTaskDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskyieldDirective
    bool VisitOMPTaskyieldDirective(OMPTaskyieldDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPBarrierDirective
    bool VisitOMPBarrierDirective(OMPBarrierDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskwaitDirective
    bool VisitOMPTaskwaitDirective(OMPTaskwaitDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskgroupDirective
    bool VisitOMPTaskgroupDirective(OMPTaskgroupDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPFlushDirective
    bool VisitOMPFlushDirective(OMPFlushDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPOrderedDirective
    bool VisitOMPOrderedDirective(OMPOrderedDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPAtomicDirective
    bool VisitOMPAtomicDirective(OMPAtomicDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetDirective
    bool VisitOMPTargetDirective(OMPTargetDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetDataDirective
    bool VisitOMPTargetDataDirective(OMPTargetDataDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetEnterDataDirective
    bool VisitOMPTargetEnterDataDirective(OMPTargetEnterDataDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetExitDataDirective
    bool VisitOMPTargetExitDataDirective(OMPTargetExitDataDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetParallelDirective
    bool VisitOMPTargetParallelDirective(OMPTargetParallelDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetParallelForDirective
    bool VisitOMPTargetParallelForDirective(OMPTargetParallelForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetUpdateDirective
    bool VisitOMPTargetUpdateDirective(OMPTargetUpdateDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTeamsDirective
    bool VisitOMPTeamsDirective(OMPTeamsDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPCancellationPointDirective
    bool VisitOMPCancellationPointDirective(OMPCancellationPointDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPCancelDirective
    bool VisitOMPCancelDirective(OMPCancelDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskLoopDirective
    bool VisitOMPTaskLoopDirective(OMPTaskLoopDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTaskLoopSimdDirective
    bool VisitOMPTaskLoopSimdDirective(OMPTaskLoopSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPDistributeDirective
    bool VisitOMPDistributeDirective(OMPDistributeDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPDistributeParallelForDirective
    bool VisitOMPDistributeParallelForDirective(OMPDistributeParallelForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPDistributeParallelForSimdDirective
    bool VisitOMPDistributeParallelForSimdDirective(OMPDistributeParallelForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPDistributeSimdDirective
    bool VisitOMPDistributeSimdDirective(OMPDistributeSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetParallelForSimdDirective
    bool VisitOMPTargetParallelForSimdDirective(OMPTargetParallelForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetSimdDirective
    bool VisitOMPTargetSimdDirective(OMPTargetSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTeamsDistributeDirective
    bool VisitOMPTeamsDistributeDirective(OMPTeamsDistributeDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTeamsDistributeSimdDirective
    bool VisitOMPTeamsDistributeSimdDirective(OMPTeamsDistributeSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTeamsDistributeParallelForSimdDirective
    bool VisitOMPTeamsDistributeParallelForSimdDirective(OMPTeamsDistributeParallelForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTeamsDistributeParallelForDirective
    bool VisitOMPTeamsDistributeParallelForDirective(OMPTeamsDistributeParallelForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetTeamsDirective
    bool VisitOMPTargetTeamsDirective(OMPTargetTeamsDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetTeamsDistributeDirective
    bool VisitOMPTargetTeamsDistributeDirective(OMPTargetTeamsDistributeDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetTeamsDistributeParallelForDirective
    bool VisitOMPTargetTeamsDistributeParallelForDirective(OMPTargetTeamsDistributeParallelForDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetTeamsDistributeParallelForSimdDirective
    bool VisitOMPTargetTeamsDistributeParallelForSimdDirective(OMPTargetTeamsDistributeParallelForSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit OMPTargetTeamsDistributeSimdDirective
    bool VisitOMPTargetTeamsDistributeSimdDirective(OMPTargetTeamsDistributeSimdDirective *node)
    {
        return true;
    }
     */

    /* Visit TranslationUnitDecl
    bool VisitTranslationUnitDecl(TranslationUnitDecl *node)
    {
        return true;
    }
     */

    /* Visit PragmaCommentDecl
    bool VisitPragmaCommentDecl(PragmaCommentDecl *node)
    {
        return true;
    }
     */

    /* Visit PragmaDetectMismatchDecl
    bool VisitPragmaDetectMismatchDecl(PragmaDetectMismatchDecl *node)
    {
        return true;
    }
     */

    /* Visit ExternCContextDecl
    bool VisitExternCContextDecl(ExternCContextDecl *node)
    {
        return true;
    }
     */

    /* Visit NamedDecl
    bool VisitNamedDecl(NamedDecl *node)
    {
        return true;
    }
     */

    /* Visit NamespaceDecl
    bool VisitNamespaceDecl(NamespaceDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingDirectiveDecl
    bool VisitUsingDirectiveDecl(UsingDirectiveDecl *node)
    {
        return true;
    }
     */

    /* Visit NamespaceAliasDecl
    bool VisitNamespaceAliasDecl(NamespaceAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit LabelDecl
    bool VisitLabelDecl(LabelDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeDecl
    bool VisitTypeDecl(TypeDecl *node)
    {
        return true;
    }
     */

    /* Visit TypedefNameDecl
    bool VisitTypedefNameDecl(TypedefNameDecl *node)
    {
        return true;
    }
     */

    /* Visit TypedefDecl
    bool VisitTypedefDecl(TypedefDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeAliasDecl
    bool VisitTypeAliasDecl(TypeAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCTypeParamDecl
    bool VisitObjCTypeParamDecl(ObjCTypeParamDecl *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedUsingTypenameDecl
    bool VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *node)
    {
        return true;
    }
     */

    /* Visit TagDecl
    bool VisitTagDecl(TagDecl *node)
    {
        return true;
    }
     */

    /* Visit EnumDecl
    bool VisitEnumDecl(EnumDecl *node)
    {
        return true;
    }
     */

    /* Visit RecordDecl
    bool VisitRecordDecl(RecordDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXRecordDecl
    bool VisitCXXRecordDecl(CXXRecordDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassTemplateSpecializationDecl
    bool VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateTypeParmDecl
    bool VisitTemplateTypeParmDecl(TemplateTypeParmDecl *node)
    {
        return true;
    }
     */

    /* Visit ValueDecl
    bool VisitValueDecl(ValueDecl *node)
    {
        return true;
    }
     */

    /* Visit EnumConstantDecl
    bool VisitEnumConstantDecl(EnumConstantDecl *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedUsingValueDecl
    bool VisitUnresolvedUsingValueDecl(UnresolvedUsingValueDecl *node)
    {
        return true;
    }
     */

    /* Visit IndirectFieldDecl
    bool VisitIndirectFieldDecl(IndirectFieldDecl *node)
    {
        return true;
    }
     */

    /* Visit BindingDecl
    bool VisitBindingDecl(BindingDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPDeclareReductionDecl
    bool VisitOMPDeclareReductionDecl(OMPDeclareReductionDecl *node)
    {
        return true;
    }
     */

    /* Visit DeclaratorDecl
    bool VisitDeclaratorDecl(DeclaratorDecl *node)
    {
        return true;
    }
     */

    /* Visit FieldDecl
    bool VisitFieldDecl(FieldDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCIvarDecl
    bool VisitObjCIvarDecl(ObjCIvarDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtDefsFieldDecl
    bool VisitObjCAtDefsFieldDecl(ObjCAtDefsFieldDecl *node)
    {
        return true;
    }
     */

    /* Visit MSPropertyDecl
    bool VisitMSPropertyDecl(MSPropertyDecl *node)
    {
        return true;
    }
     */

    /* Visit FunctionDecl
    bool VisitFunctionDecl(FunctionDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXMethodDecl
    bool VisitCXXMethodDecl(CXXMethodDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXConstructorDecl
    bool VisitCXXConstructorDecl(CXXConstructorDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXDestructorDecl
    bool VisitCXXDestructorDecl(CXXDestructorDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXConversionDecl
    bool VisitCXXConversionDecl(CXXConversionDecl *node)
    {
        return true;
    }
     */

    /* Visit VarDecl
    bool VisitVarDecl(VarDecl *node)
    {
        return true;
    }
     */

    /* Visit VarTemplateSpecializationDecl
    bool VisitVarTemplateSpecializationDecl(VarTemplateSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit ImplicitParamDecl
    bool VisitImplicitParamDecl(ImplicitParamDecl *node)
    {
        return true;
    }
     */

    /* Visit ParmVarDecl
    bool VisitParmVarDecl(ParmVarDecl *node)
    {
        return true;
    }
     */

    /* Visit DecompositionDecl
    bool VisitDecompositionDecl(DecompositionDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPCapturedExprDecl
    bool VisitOMPCapturedExprDecl(OMPCapturedExprDecl *node)
    {
        return true;
    }
     */

    /* Visit NonTypeTemplateParmDecl
    bool VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateDecl
    bool VisitTemplateDecl(TemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit RedeclarableTemplateDecl
    bool VisitRedeclarableTemplateDecl(RedeclarableTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit FunctionTemplateDecl
    bool VisitFunctionTemplateDecl(FunctionTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassTemplateDecl
    bool VisitClassTemplateDecl(ClassTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit VarTemplateDecl
    bool VisitVarTemplateDecl(VarTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeAliasTemplateDecl
    bool VisitTypeAliasTemplateDecl(TypeAliasTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateTemplateParmDecl
    bool VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *node)
    {
        return true;
    }
     */

    /* Visit BuiltinTemplateDecl
    bool VisitBuiltinTemplateDecl(BuiltinTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingDecl
    bool VisitUsingDecl(UsingDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingPackDecl
    bool VisitUsingPackDecl(UsingPackDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingShadowDecl
    bool VisitUsingShadowDecl(UsingShadowDecl *node)
    {
        return true;
    }
     */

    /* Visit ConstructorUsingShadowDecl
    bool VisitConstructorUsingShadowDecl(ConstructorUsingShadowDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCMethodDecl
    bool VisitObjCMethodDecl(ObjCMethodDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCContainerDecl
    bool VisitObjCContainerDecl(ObjCContainerDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCategoryDecl
    bool VisitObjCCategoryDecl(ObjCCategoryDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCProtocolDecl
    bool VisitObjCProtocolDecl(ObjCProtocolDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCInterfaceDecl
    bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCImplDecl
    bool VisitObjCImplDecl(ObjCImplDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCategoryImplDecl
    bool VisitObjCCategoryImplDecl(ObjCCategoryImplDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCImplementationDecl
    bool VisitObjCImplementationDecl(ObjCImplementationDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCPropertyDecl
    bool VisitObjCPropertyDecl(ObjCPropertyDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCompatibleAliasDecl
    bool VisitObjCCompatibleAliasDecl(ObjCCompatibleAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit LinkageSpecDecl
    bool VisitLinkageSpecDecl(LinkageSpecDecl *node)
    {
        return true;
    }
     */

    /* Visit ExportDecl
    bool VisitExportDecl(ExportDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCPropertyImplDecl
    bool VisitObjCPropertyImplDecl(ObjCPropertyImplDecl *node)
    {
        return true;
    }
     */

    /* Visit FileScopeAsmDecl
    bool VisitFileScopeAsmDecl(FileScopeAsmDecl *node)
    {
        return true;
    }
     */

    /* Visit AccessSpecDecl
    bool VisitAccessSpecDecl(AccessSpecDecl *node)
    {
        return true;
    }
     */

    /* Visit FriendDecl
    bool VisitFriendDecl(FriendDecl *node)
    {
        return true;
    }
     */

    /* Visit FriendTemplateDecl
    bool VisitFriendTemplateDecl(FriendTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit StaticAssertDecl
    bool VisitStaticAssertDecl(StaticAssertDecl *node)
    {
        return true;
    }
     */

    /* Visit BlockDecl
    bool VisitBlockDecl(BlockDecl *node)
    {
        return true;
    }
     */

    /* Visit CapturedDecl
    bool VisitCapturedDecl(CapturedDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassScopeFunctionSpecializationDecl
    bool VisitClassScopeFunctionSpecializationDecl(ClassScopeFunctionSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit ImportDecl
    bool VisitImportDecl(ImportDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPThreadPrivateDecl
    bool VisitOMPThreadPrivateDecl(OMPThreadPrivateDecl *node)
    {
        return true;
    }
     */

    /* Visit EmptyDecl
    bool VisitEmptyDecl(EmptyDecl *node)
    {
        return true;
    }
     */

};

static RuleSet rules(new ElseBlockWasPossibleForgottenOrCommentOutRule());
