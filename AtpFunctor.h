#pragma once
#include <vector>
#include <string>
#include <set>

enum AtpFunctorType {
	FUNCTOR,
	VARIABLE,
	CONSTANT
};

class AtpFunctor
{
public:
	int value;   
	std::string name;

	int arity;
	AtpFunctorType type;
	std::vector<AtpFunctor> functors;
};
