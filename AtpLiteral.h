#pragma once
#include "AtpPredicate.h"

class AtpLiteral
{
public:
	int value;
	bool polarity;
	AtpPredicate predicate;

	bool operator==(const AtpLiteral& literal) const {
		return this->polarity == literal.polarity &&
			this->predicate == literal.predicate;
	}

	bool operator<(const AtpLiteral& literal) const {
		return this->value < literal.value;
	}
};

