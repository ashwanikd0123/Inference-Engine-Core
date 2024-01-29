#pragma once
#include "AtpKnBase.h"
enum AtpElementType {
	_TOKEN,
	_VARIABLE,
	_FUNCTOR,
	_PREDICATE,
	_LITERAL,
	_FORMULA,
	_STATEMENT
};

class AtpParsingElement
{
public:

	AtpElementType type;
	
	AtpToken* valueToken;

	AtpFunctor* valueFunctor;
	AtpPredicate* valuePredicate;
	AtpLiteral* valueLiteral;
	AtpFormula* formula;
};

