#include "AtpKnBase.h"
#include "AtpParsingElement.h"

extern void errorLog(std::string msg);

void throughError(std::string msg) {
	errorLog(msg);
	exit(8);
}

AtpStatement getParsedStatement(AtpKnBase &kb, std::vector<AtpParsingElement> elements);

void AtpKnBase::init()
{
	this->axioms.clear();
	this->conjenctures.clear();
	this->termMap.clear();
	this->varMap.clear();
}

void AtpKnBase::addAxiom(AtpStatement statement)
{
	this->axioms.insert(statement);
}

void AtpKnBase::addConjencture(AtpStatement statement)
{
	this->conjenctures.insert(statement);
}

void checkLanguageValidity(AtpToken langToken) {
	if (std::strcmp(langToken.value.c_str(), "fof") != 0) {
		errorLog("Language not supported...");
		exit(8);
	}
}

void AtpKnBase::parseFormula(std::vector<AtpToken> tokens)
{
	std::string name;
	AtpStatementType type;
	std::stack<AtpParsingElement> tokenStack;
	std::vector<AtpToken>::iterator it = tokens.begin();

	AtpToken temp = *it;
	checkLanguageValidity(temp);
	std::vector<AtpParsingElement> parsingTokens;

	temp = *(++it);
	if (temp.type == BRACKET_ROUND_START) {
		temp = *(++it);
		if (temp.type == FORMULA_NAME) {
			name = temp.value;
			temp = *(++it);
			if (temp.type == COMMA) {
				temp = *(++it);
				if (temp.type == FORMULA_TYPE) {
					if (std::strcmp(temp.value.c_str(), "axiom")) {
						type = AXIOM;
					}
					else if (std::strcmp(temp.value.c_str(), "conjecture")) {
						type = CONJENCTURE;
					}
					else {
						throughError("Type should be either \"axiom\" or \"conjencture\"");
					}
					temp = *(++it);
					if (temp.type == COMMA) {
						for (int i = 6; i < tokens.size() - 2; i++) {
							parsingTokens.push_back(AtpParsingElement(&tokens[i]));
						}
					}
					else {
						throughError(", expected...");
					}
				}
				else {
					throughError("Formula type expected...");
				}
			}
			else {
				throughError(", expected...");
			}
		}
		else {
			throughError("Formula name expected...");
		}
	}
	else {
		throughError("( expected...");
	}

	AtpStatement statement = getParsedStatement(*this, parsingTokens);
	statement.name = name;
	statement.type = type;
	if (type == AXIOM) {
		this->axioms.insert(statement);
	}
	else {
		this->conjenctures.insert(statement);
	}
}


AtpStatement getParsedStatement(AtpKnBase& kb, std::vector<AtpParsingElement> elements) {
	std::vector<AtpParsingElement>::iterator it = elements.begin();
	AtpStatement statement;
	while (it != elements.end()) {
		std::cout << (*it).valueToken->value;
		it++;
	}
	std::cout << std::endl;
	return statement;
}