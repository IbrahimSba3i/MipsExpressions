#include "OperationsFactory.h"



Operation *OperationsFactory::getOperation(const OperationString &source)
{
	if(source.operation == "+") {
		return new AdditionOperation(source);
	} else if(source.operation == "-") {
		return new SubtractionOperation(source);
	} else if(source.operation == "*") {
		return new MultiplicationOperation(source);
	} else if(source.operation == "/") {
		return new DivisionOperation(source);
	} else if(source.operation == "%") {
		return new ModuloOperation(source);
	} else if(source.operation == ",") {
		return new CommaOperation(source);
	} else if(source.operation == "=") {
		return new AssignmentOperation(source);
	} else if(source.operation == "+=") {
		return new AdditionAssignmentOperation(source);
	} else if(source.operation == "-=") {
		return new SubtractionAssignmentOperation(source);
	} else if(source.operation == "*=") {
		return new MultiplicationAssignmentOperation(source);
	} else if(source.operation == "/=") {
		return new DivisionAssignmentOperation(source);
	} else if(source.operation == "%=") {
		return new ModuloAssignmentOperation(source);
	} else if(source.operation == "|=") {
		return new BitwiseOrAssignmentOperation(source);
	} else if(source.operation == "&=") {
		return new BitwiseAndAssignmentOperation(source);
	} else if(source.operation == "^=") {
		return new BitwiseXorAssignmentOperation(source);
	} else if(source.operation == "<<=") {
		return new BitwiseShiftLeftAssignmentOperation(source);
	} else if(source.operation == ">>=") {
		return new BitwiseShiftRightAssignmentOperation(source);
	} else if(source.operation == ">>") {
		return new BitwiseShiftRightOperation(source);
	} else if(source.operation == "<<") {
		return new BitwiseShiftLeftOperation(source);
	} else if(source.operation == "||") {
		return new LogicalOrOperation(source);
	} else if(source.operation == "&&") {
		return new LogicalAndOperation(source);
	} else if(source.operation == "|") {
		return new BitwiseOrOperation(source);
	} else if(source.operation == "&") {
		return new BitwiseAndOperation(source);
	} else if(source.operation == "^") {
		return new BitwiseXorOperation(source);
	} else if(source.operation == "==") {
		return new EqualityComparisonOperation(source);
	} else if(source.operation == "!=") {
		return new InequalityComparisonOperation(source);
	} else if(source.operation == ">=") {
		return new GreaterOrEqualComparisonOperation(source);
	} else if(source.operation == "<=") {
		return new LessOrEqualComparisonOperation(source);
	} else if(source.operation == ">") {
		return new GreaterComparisonOperation(source);
	} else if(source.operation == "<") {
		return new LessComparisonOperation(source);
	} else if(source.operation == "~") {
		return new BitwiseInvOperation(source);
	} else if(source.operation == "!") {
		return new LogicalNotOperation(source);
	} else if(source.operation == "++") {
		return new IncrementOperation(source);
	} else if(source.operation == "--") {
		return new DecrementOperation(source);
	} else if(source.operation == "pow") {
		return new PowOperation(source);
	} else if(source.operation == "max") {
		return new MaxOperation(source);
	} else if(source.operation == "min") {
		return new MinOperation(source);
	} else if(source.operation == "abs") {
		return new AbsOperation(source);
	} else if(Utility::isVariable(source.operation)) {
		return new FunctionCallOperation(source);
	}
	return NULL;
}
