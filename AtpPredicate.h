#pragma once
#include "AtpFunctor.h"
#include <vector>
#include <algorithm>

class AtpPredicate
{
public:
	int value;
	std::string name;

	std::vector<AtpFunctor*> args;
};

