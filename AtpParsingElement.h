#pragma once
#include "AtpKnBase.h"
enum AtpElementType {
	_TOKEN,
	_VARIABLE,
	_FUNCTOR,
	_TERM,
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
	
	AtpVariable* valueVariable;
	AtpFunctor* valueFunctor;
	AtpTerm* valueTerm;
	AtpPredicate* valuePredicate;
	AtpLiteral* valueLiteral;
	AtpFormula* formula;
	AtpStatement *valueStatement;

	AtpParsingElement(AtpStatement* valueStatement) {
		this->type = _STATEMENT;
		this->valueStatement = valueStatement;
	}

	AtpParsingElement(AtpToken* valueToken) {
		this->type = _TOKEN;
		this->valueToken = valueToken;
	}
};

