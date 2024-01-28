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

	AtpStatement *valueStatement;
	AtpToken *valueToken;

	AtpParsingElement(AtpStatement* valueStatement) {
		this->type = STATEMENT;
		this->valueStatement = valueStatement;
	}

	AtpParsingElement(AtpToken* valueToken) {
		this->type = TOKEN;
		this->valueToken = valueToken;
	}
};

