#ifndef OPERATIONSFACTORY_H
#define OPERATIONSFACTORY_H
#include "OperationsIncludes.h"

class OperationsFactory
{
public:
	static Operation* getOperation(const OperationString& source);
};

#endif // OPERATIONSFACTORY_H
