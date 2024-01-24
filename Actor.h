#pragma once
#include <set>
#include "Term.h"

enum ActorType {
	PREDICATE,
	FUNCTION
};

class Actor
{
	ActorType type;
	int value;
	std::set<Term> terms;
	std::set<Actor> actors;
};

