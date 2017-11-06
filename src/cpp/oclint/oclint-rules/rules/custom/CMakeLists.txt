SET(BuildAssignWithUninitVariableRuleRule AssignWithUninitVariableRule)
BUILD_DYNAMIC_RULES("${BuildAssignWithUninitVariableRuleRule}")

SET(BuildIdenticalSubExprsRule IdenticalSubExprs)
BUILD_DYNAMIC_RULES("${BuildIdenticalSubExprsRule}")

SET(BuildLowerPriorityOfConditionalExpressionRule LowerPriorityOfConditionalExpression)
BUILD_DYNAMIC_RULES("${BuildLowerPriorityOfConditionalExpressionRule}")

SET(BuildNonSensicalPointerComparisonRule NonSensicalPointerComparison)
BUILD_DYNAMIC_RULES("${BuildNonSensicalPointerComparisonRule}")

SET(BuildMissingSemicolonAfterReturnRule MissingSemicolonAfterReturn)
BUILD_DYNAMIC_RULES("${BuildMissingSemicolonAfterReturnRule}")

SET(BuildAllocaInLoopRule AllocaInLoop)
BUILD_DYNAMIC_RULES("${BuildAllocaInLoopRule}")

SET(BuildInvalidPointToLocalVariableRule InvalidPointToLocalVariable)
BUILD_DYNAMIC_RULES("${BuildInvalidPointToLocalVariableRule}")

SET(BuildInvalidPointToLocalArrayRule InvalidPointToLocalArray)
BUILD_DYNAMIC_RULES("${BuildInvalidPointToLocalArrayRule}")

SET(BuildIllegalThrowWithoutInTryCatchInDestructorRule IllegalThrowWithoutInTryCatchInDestructor)
BUILD_DYNAMIC_RULES("${BuildIllegalThrowWithoutInTryCatchInDestructorRule}")

SET(BuildClassAsStringArgumentRule ClassAsStringArgument)
BUILD_DYNAMIC_RULES("${BuildClassAsStringArgumentRule}")

SET(BuildInvalidSizeOfArgumentArrayPointRule InvalidSizeOfArgumentArrayPoint)
BUILD_DYNAMIC_RULES("${BuildInvalidSizeOfArgumentArrayPointRule}")

SET(BuildMemFunCallLeadOverOrUnderFlowWithSizeofRule MemFunCallLeadOverOrUnderFlowWithSizeof)
BUILD_DYNAMIC_RULES("${BuildMemFunCallLeadOverOrUnderFlowWithSizeofRule}")

SET(BuildDividingSizeofAPointerByAnotherValueRule DividingSizeofAPointerByAnotherValue)
BUILD_DYNAMIC_RULES("${BuildDividingSizeofAPointerByAnotherValueRule}")

SET(BuildNoNullFunctionPointerComparedWithNullRule NoNullFunctionPointerComparedWithNull)
BUILD_DYNAMIC_RULES("${BuildNoNullFunctionPointerComparedWithNullRule}")

SET(BuildRepeatedIfConditionRule RepeatedIfCondition)
BUILD_DYNAMIC_RULES("${BuildRepeatedIfConditionRule}")

SET(BuildStrlenConstantValueInMallocRule StrlenConstantValueInMalloc)
BUILD_DYNAMIC_RULES("${BuildStrlenConstantValueInMallocRule}")

SET(BuildAssignSameVariableTwiceSuccessivelyRule AssignSameVariableTwiceSuccessively)
BUILD_DYNAMIC_RULES("${BuildAssignSameVariableTwiceSuccessivelyRule}")

SET(BuildUseCommaInArrayIndexRule UseCommaInArrayIndex)
BUILD_DYNAMIC_RULES("${BuildUseCommaInArrayIndexRule}")

SET(BuildUseUnSenseCommaInExpressionRule UseUnSenseCommaInExpression)
BUILD_DYNAMIC_RULES("${BuildUseUnSenseCommaInExpressionRule}")

SET(BuildDereferencingNullPointerRule DereferencingNullPointer)
BUILD_DYNAMIC_RULES("${BuildDereferencingNullPointerRule}")

SET(BuildThenAndElseBodyEquivalentRule ThenAndElseBodyEquivalent)
BUILD_DYNAMIC_RULES("${BuildThenAndElseBodyEquivalentRule}")

SET(BuildTwoFunctionBodyEquivalentRule TwoFunctionBodyEquivalent)
BUILD_DYNAMIC_RULES("${BuildTwoFunctionBodyEquivalentRule}")

SET(BuildCmpFuncUseInConditionRule CmpFuncUseInCondition)
BUILD_DYNAMIC_RULES("${BuildCmpFuncUseInConditionRule}")

SET(BuildAssignZeroValueToPointerRule AssignZeroValueToPointer)
BUILD_DYNAMIC_RULES("${BuildAssignZeroValueToPointerRule}")

SET(BuildComparePointerWithZeroValueRule ComparePointerWithZeroValue)
BUILD_DYNAMIC_RULES("${BuildComparePointerWithZeroValueRule}")

SET(BuildAddSemiAfterIfForWhileConditionRule AddSemiAfterIfForWhileCondition)
BUILD_DYNAMIC_RULES("${BuildAddSemiAfterIfForWhileConditionRule}")

SET(BuildWithoutUseReturnValueOfFunctionRule WithoutUseReturnValueOfFunction)
BUILD_DYNAMIC_RULES("${BuildWithoutUseReturnValueOfFunctionRule}")

SET(BuildTwoSizeofMultipliedRule TwoSizeofMultiplied)
BUILD_DYNAMIC_RULES("${BuildTwoSizeofMultipliedRule}")

SET(BuildPointerUnaryAndDerefConfuseRule PointerUnaryAndDerefConfuse)
BUILD_DYNAMIC_RULES("${BuildPointerUnaryAndDerefConfuseRule}")

SET(BuildWrongVariableIncreaseInForLoopRule WrongVariableIncreaseInForLoop)
BUILD_DYNAMIC_RULES("${BuildWrongVariableIncreaseInForLoopRule}")

SET(BuildWrongVariableComparedInForLoopRule WrongVariableComparedInForLoop)
BUILD_DYNAMIC_RULES("${BuildWrongVariableComparedInForLoopRule}")

SET(BuildSameVariableUseInForLoopRule SameVariableUseInForLoop)
BUILD_DYNAMIC_RULES("${BuildSameVariableUseInForLoopRule}")

SET(BuildConstantValueWithZeroPrefixRule ConstantValueWithZeroPrefix)
BUILD_DYNAMIC_RULES("${BuildConstantValueWithZeroPrefixRule}")

SET(BuildIteratorsAsArgumentRule IteratorsAsArgument)
BUILD_DYNAMIC_RULES("${BuildIteratorsAsArgumentRule}")

SET(BuildFormatStringIntoItselfInSprintfRule FormatStringIntoItselfInSprintf)
BUILD_DYNAMIC_RULES("${BuildFormatStringIntoItselfInSprintfRule}")

SET(BuildOddTypeCastRule OddTypeCast)
BUILD_DYNAMIC_RULES("${BuildOddTypeCastRule}")

SET(BuildConstResultAccordToValueRangeRule ConstResultAccordToValueRange)
BUILD_DYNAMIC_RULES("${BuildConstResultAccordToValueRangeRule}")

SET(BuildTwoDimArrayToPointerRule TwoDimArrayToPointer)
BUILD_DYNAMIC_RULES("${BuildTwoDimArrayToPointerRule}")

SET(BuildSameArgumentForFuncCallRule SameArgumentForFuncCall)
BUILD_DYNAMIC_RULES("${BuildSameArgumentForFuncCallRule}")

SET(BuildOddFloatPreciseComparisionRule OddFloatPreciseComparision)
BUILD_DYNAMIC_RULES("${BuildOddFloatPreciseComparisionRule}")

SET(BuildBoolIncrementRule BoolIncrement)
BUILD_DYNAMIC_RULES("${BuildBoolIncrementRule}")

SET(BuildUnsignedValueMinusComapreRule UnsignedValueMinusComapre)
BUILD_DYNAMIC_RULES("${BuildUnsignedValueMinusComapreRule}")

SET(BuildDifferentEnumComparisonRule DifferentEnumComparison)
BUILD_DYNAMIC_RULES("${BuildDifferentEnumComparisonRule}")

SET(BuildArrayIndexOutOfBoundRule ArrayIndexOutOfBound)
BUILD_DYNAMIC_RULES("${BuildArrayIndexOutOfBoundRule}")

SET(BuildAssignInConditionRule AssignInCondition)
BUILD_DYNAMIC_RULES("${BuildAssignInConditionRule}")

SET(BuildPartOfConditionIsConstantValueRule PartOfConditionIsConstantValue)
BUILD_DYNAMIC_RULES("${BuildPartOfConditionIsConstantValueRule}")

SET(BuildCompareBoolWithIntRule CompareBoolWithInt)
BUILD_DYNAMIC_RULES("${BuildCompareBoolWithIntRule}")

SET(BuildElseAlignWhichIfProblemRule ElseAlignWhichIfProblem)
BUILD_DYNAMIC_RULES("${BuildElseAlignWhichIfProblemRule}")

SET(BuildEmptyExceptionHandlerRule EmptyExceptionHandler)
BUILD_DYNAMIC_RULES("${BuildEmptyExceptionHandlerRule}")

SET(BuildArgumentOfSizeofIsExpressionRule ArgumentOfSizeofIsExpression)
BUILD_DYNAMIC_RULES("${BuildArgumentOfSizeofIsExpressionRule}")
