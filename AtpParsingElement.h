#pragma once
#include "AtpKnBase.h"
enum AtpElementType {
	TOKEN,
	CLAUSE,
	STATEMENT,
	ACTOR
};

class AtpParsingElement
{
public:
	AtpElementType type;

	AtpActor *valueActor;
	AtpClause *valueClause;
	AtpStatement *valueStatement;
	AtpToken *valueToken;

	AtpParsingElement(AtpActor* valueActor) {
		this->type = ACTOR;
		this->valueActor = valueActor;
	}

	AtpParsingElement(AtpClause* valueClause) {
		this->type = CLAUSE;
		this->valueClause = valueClause;
	}

	AtpParsingElement(AtpStatement* valueStatement) {
		this->type = STATEMENT;
		this->valueStatement = valueStatement;
	}

	AtpParsingElement(AtpToken* valueToken) {
		this->type = TOKEN;
		this->valueToken = valueToken;
	}
};

