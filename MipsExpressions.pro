#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T12:33:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MipsExpressions
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	System/ParsingString.cpp \
	Expressions/ExpressionParser.cpp \
	Expressions/OperationString.cpp \
	Expressions/OperationsFactory.cpp \
	System/RegistersManager.cpp \
	Expressions/Operations/AdditionOperation.cpp \
	Expressions/Operations/MultiplicationOperation.cpp \
	Expressions/Operations/Operation.cpp \
	Expressions/Operations/SubtractionOperation.cpp \
	Expressions/Operations/AdditionAssignmentOperation.cpp \
	Expressions/Operations/AssignmentOperation.cpp \
	Expressions/Operations/BitwiseAndAssignmentOperation.cpp \
	Expressions/Operations/BitwiseAndOperation.cpp \
	Expressions/Operations/BitwiseInvOperation.cpp \
	Expressions/Operations/BitwiseOrAssignmentOperation.cpp \
	Expressions/Operations/BitwiseOrOperation.cpp \
	Expressions/Operations/BitwiseShiftLeftAssignmentOperation.cpp \
	Expressions/Operations/BitwiseShiftLeftOperation.cpp \
	Expressions/Operations/BitwiseShiftRightAssignmentOperation.cpp \
	Expressions/Operations/BitwiseShiftRightOperation.cpp \
	Expressions/Operations/BitwiseXorAssignmentOperation.cpp \
	Expressions/Operations/BitwiseXorOperation.cpp \
	Expressions/Operations/CommaOperation.cpp \
	Expressions/Operations/DecrementOperation.cpp \
	Expressions/Operations/DivisionAssignmentOperation.cpp \
	Expressions/Operations/DivisionOperation.cpp \
	Expressions/Operations/EqualityComparisonOperation.cpp \
	Expressions/Operations/GreaterComparisonOperation.cpp \
	Expressions/Operations/GreaterOrEqualComparisonOperation.cpp \
	Expressions/Operations/IncrementOperation.cpp \
	Expressions/Operations/InequalityComparisonOperation.cpp \
	Expressions/Operations/LessComparisonOperation.cpp \
	Expressions/Operations/LessOrEqualComparisonOperation.cpp \
	Expressions/Operations/LogicalAndOperation.cpp \
	Expressions/Operations/LogicalNotOperation.cpp \
	Expressions/Operations/LogicalOrOperation.cpp \
	Expressions/Operations/ModuloAssignmentOperation.cpp \
	Expressions/Operations/ModuloOperation.cpp \
	Expressions/Operations/MultiplicationAssignmentOperation.cpp \
	Expressions/Operations/SubtractionAssignmentOperation.cpp \
	Expressions/Operations/AbsOperation.cpp \
	Expressions/Operations/FunctionCallOperation.cpp \
	Expressions/Operations/MaxOperation.cpp \
	Expressions/Operations/MinOperation.cpp \
	Expressions/Operations/PowOperation.cpp \
	System/SettingsManager.cpp \
	System/LabelsManager.cpp \
	System/AssemblyInstruction.cpp \
	mipstexthighlighter.cpp \
	System/AssemblyCodeBase.cpp \
	SettingsPage.cpp \
    System/Utility.cpp \
    System/IncorrectSymbol.cpp \
    Expressions/OperationObject.cpp

HEADERS  += mainwindow.h \
	System/ParsingString.h \
	Expressions/ExpressionParser.h \
	Expressions/OperationString.h \
	Expressions/OperationsFactory.h \
	Expressions/OperationsIncludes.h \
	System/RegistersManager.h \
	System/Utility.h \
	Expressions/SymbolDescription.h \
	Expressions/Operations/AdditionOperation.h \
	Expressions/Operations/MultiplicationOperation.h \
	Expressions/Operations/Operation.h \
	Expressions/Operations/SubtractionOperation.h \
	Expressions/Operations/AdditionAssignmentOperation.h \
	Expressions/Operations/AssignmentOperation.h \
	Expressions/Operations/BitwiseAndAssignmentOperation.h \
	Expressions/Operations/BitwiseAndOperation.h \
	Expressions/Operations/BitwiseInvOperation.h \
	Expressions/Operations/BitwiseOrAssignmentOperation.h \
	Expressions/Operations/BitwiseOrOperation.h \
	Expressions/Operations/BitwiseShiftLeftAssignmentOperation.h \
	Expressions/Operations/BitwiseShiftLeftOperation.h \
	Expressions/Operations/BitwiseShiftRightAssignmentOperation.h \
	Expressions/Operations/BitwiseShiftRightOperation.h \
	Expressions/Operations/BitwiseXorAssignmentOperation.h \
	Expressions/Operations/BitwiseXorOperation.h \
	Expressions/Operations/CommaOperation.h \
	Expressions/Operations/DecrementOperation.h \
	Expressions/Operations/DivisionAssignmentOperation.h \
	Expressions/Operations/DivisionOperation.h \
	Expressions/Operations/EqualityComparisonOperation.h \
	Expressions/Operations/GreaterComparisonOperation.h \
	Expressions/Operations/GreaterOrEqualComparisonOperation.h \
	Expressions/Operations/IncrementOperation.h \
	Expressions/Operations/InequalityComparisonOperation.h \
	Expressions/Operations/LessComparisonOperation.h \
	Expressions/Operations/LessOrEqualComparisonOperation.h \
	Expressions/Operations/LogicalAndOperation.h \
	Expressions/Operations/LogicalNotOperation.h \
	Expressions/Operations/LogicalOrOperation.h \
	Expressions/Operations/ModuloAssignmentOperation.h \
	Expressions/Operations/ModuloOperation.h \
	Expressions/Operations/MultiplicationAssignmentOperation.h \
	Expressions/Operations/SubtractionAssignmentOperation.h \
	Expressions/Operations/AbsOperation.h \
	Expressions/Operations/FunctionCallOperation.h \
	Expressions/Operations/MaxOperation.h \
	Expressions/Operations/MinOperation.h \
	Expressions/Operations/PowOperation.h \
	System/SettingsManager.h \
	System/LabelsManager.h \
	System/AssemblyInstruction.h \
	mipstexthighlighter.h \
	System/AssemblyCodeBase.h \
	SettingsPage.h \
    System/IncorrectSymbol.h \
    Expressions/OperationObject.h

FORMS    += mainwindow.ui \
	SettingsPage.ui
