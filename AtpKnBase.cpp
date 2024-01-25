#include "AtpKnBase.h"

void AtpKnBase::init()
{
	this->axioms.clear();
	this->conjenctures.clear();
	this->termMap.clear();
	this->varMap.clear();
}

void AtpKnBase::parseFormula(std::vector<AtpToken> tokens)
{
	std::cout << "FORMULA: ";
	for (auto& token : tokens) {
		std::cout << token.value;
	}
	std::cout << std::endl;
}
