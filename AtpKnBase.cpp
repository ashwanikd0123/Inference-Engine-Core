#include "AtpKnBase.h"
#include "AtpParsingElement.h"

extern void errorLog(std::string msg);

void throughError(std::string msg) {
	errorLog(msg);
	exit(8);
}

AtpStatement* getParsedStatement(AtpKnBase &kb, std::vector<AtpParsingElement> elements);

void AtpKnBase::init()
{
	this->axioms.clear();
	this->conjenctures.clear();
	this->varMap.clear();
	this->counter = 1;
	this->skolemCount = 0;
}

void AtpKnBase::addAxiom(AtpStatement& statement)
{
	this->axioms.push_back(&statement);
}

void AtpKnBase::addConjencture(AtpStatement& statement)
{
	this->conjenctures.push_back(&statement);
}

void checkLanguageValidity(AtpToken langToken) {
	if (std::strcmp(langToken.value.c_str(), "fof") != 0) {
		errorLog("Language not supported...");
		exit(8);
	}
}

void AtpKnBase::parseFormula(std::vector<AtpToken>& tokens)
{
	std::string name;
	AtpStatementType type;
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
							AtpParsingElement e;
							e.type = _TOKEN;
							e.valueToken = &tokens[i];
							parsingTokens.push_back(e);
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
	AtpStatement *statement = getParsedStatement(*this, parsingTokens);
	statement->name = name;
	statement->type = type;
	if (type == AXIOM) {
		this->axioms.push_back(statement);
	}
	else {
		this->conjenctures.push_back(statement);
	}
}

const std::set<std::string> multiCharOps = {
	"=>",
	"<=>",
	"<~>",
	"!="
};

void resolveMultiCharOperators(std::vector<AtpParsingElement>& elements) {
	std::vector<AtpParsingElement>::iterator it = elements.begin();
	while (it != elements.end()) {
		if (it->valueToken->type == OP_EQUALS && 
			(it + 1)->valueToken->type == OP_GREATER_THAN) {
			it->valueToken->type = OP_IMPLICATION;
			it->valueToken->value = "=>";
			it++;
			it = elements.erase(it);
			continue;
		}
		else if (it->valueToken->type == OP_LESS_THAN) {
			if ((it + 1)->valueToken->type == OP_NOT &&
				(it + 2)->valueToken->type == OP_GREATER_THAN) {
				it->valueToken->type = OP_XOR;
				it->valueToken->value = "<~>";
			}
			else if ((it + 1)->valueToken->type == OP_EQUALS &&
				(it + 2)->valueToken->type == OP_GREATER_THAN) {
				it->valueToken->type = OP_EQUIVALENCE;
				it->valueToken->value = "<=>";
			}
			it++;
			it = elements.erase(it);
			it = elements.erase(it);
			continue;
		} else if (it->valueToken->type == OP_FOR_ALL &&
			(it + 1)->valueToken->type == OP_EQUALS) {
			it->valueToken->type = OP_NOT_EQUALS;
			it->valueToken->value = "!=";
			it++;
			it = elements.erase(it);
			continue;
		}
		it++;
	}
}

void resolveEquality(AtpKnBase& kb, std::vector<AtpParsingElement>& parsElems) {
	int temp, last, first;
	int idx = 0;
	while (idx < parsElems.size()) {
		if (parsElems[idx].type == _TOKEN && parsElems[idx].valueToken->type == OP_EQUALS) {

			// RHS parsing
			temp = idx + 1;
			if (parsElems[temp].type == _TOKEN && 
				parsElems[temp].valueToken->type == VAR_NAME) {
				if (parsElems[temp + 1].type == _TOKEN &&
					parsElems[temp + 1].valueToken->type == BRACKET_ROUND_START) {
					
					std::stack<AtpParsingElement> elementStack;
					elementStack.push(parsElems[temp]);

					elementStack.push(parsElems[++temp]);
					temp++;

					bool lastF = true;
					while (!elementStack.empty()) {

						if (parsElems[temp].type == _TOKEN &&
							parsElems[temp].valueToken->type == BRACKET_ROUND_END) {
							last = temp;
							first = temp;

							AtpParsingElement element = elementStack.top();
							elementStack.pop();
							first--;

							std::vector<AtpFunctor*> functorSet;

							while (!(element.type == _TOKEN && 
								element.valueToken->type == BRACKET_ROUND_START)) {
								if (element.type == _FUNCTOR) {
									functorSet.push_back(element.valueFunctor);
								}
								else if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
									AtpFunctor *f = new AtpFunctor();
									f->type = std::isupper(element.valueToken->value[0]) ? 
										VARIABLE :
										CONSTANT;
									f->arity = 0;
									f->value = kb.counter++;
									f->name = element.valueToken->value;
									functorSet.push_back(f);
								}
								else if (!(element.type == _TOKEN && element.valueToken->type == COMMA)) {
									errorLog("unexpected token value type...");
									exit(9);
								}

								element = elementStack.top();
								elementStack.pop();
								first--;
							}

							element = elementStack.top();
							elementStack.pop();
							first--;

							if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
								AtpFunctor *f = new AtpFunctor();
								f->type = FUNCTOR;
								f->functors = functorSet;
								f->name = element.valueToken->value;
								f->arity += f->functors.size();
								f->value = kb.counter++;
								element.type = _FUNCTOR;
								element.valueFunctor = f;
								first++;
								int n = last - first + 1;
								while (n > 0) {
									parsElems.erase(std::next(parsElems.begin(), first));
								}
							}
							else {
								errorLog("Functor name not present...");
								exit(9);
							}
						}
						else {
							elementStack.push(parsElems[temp]);
						}
						temp++;
					}
				}
				else {
					AtpFunctor *f = new AtpFunctor();
					f->type = std::isupper(parsElems[temp].valueToken->value[0]) ?
						VARIABLE :
						CONSTANT;
					f->arity = 0;
					f->value = kb.counter++;
					f->name = parsElems[temp].valueToken->value;

					parsElems[temp].type = _FUNCTOR;
					parsElems[temp].valueFunctor = f;
				}
			}
			else if (!(parsElems[temp].type == _FUNCTOR)) {
				errorLog("functor name expected...");
				exit(9);
			}

			// LHS parsing
			temp = idx - 1;

			if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == VAR_NAME) {
				AtpFunctor *f = new AtpFunctor();
				f->type = std::isupper(parsElems[temp].valueToken->value[0]) ?
					VARIABLE :
					CONSTANT;
				f->arity = 0;
				f->value = kb.counter++;
				f->name = parsElems[temp].valueToken->value;

				parsElems[temp].type = _FUNCTOR;
				parsElems[temp].valueFunctor = f;
			}
			else if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == BRACKET_ROUND_END) {
				std::stack<AtpParsingElement> elementStack;

				while (!elementStack.empty()) {
					if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == BRACKET_ROUND_START) {
						last = temp;
						first = temp;

						AtpParsingElement element = elementStack.top();
						elementStack.pop();
						first--;

						AtpFunctor *functor = new AtpFunctor();
						functor->value = kb.counter++;
						functor->name = parsElems[first].valueToken->value;

						while (!(element.type == _TOKEN &&
							element.valueToken->type == BRACKET_ROUND_END)) {
							if (element.type == _FUNCTOR) {
								functor->functors.push_back(element.valueFunctor);
								functor->arity++;
							}
							else if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
								AtpFunctor *f = new AtpFunctor();
								f->type = std::isupper(element.valueToken->value[0]) ?
									VARIABLE :
									CONSTANT;
								f->name = element.valueToken->value;
								f->value = kb.counter++;
								f->arity = 0;
								functor->functors.push_back(f);
							}
							else if (!(element.type == _TOKEN && element.valueToken->type == COMMA)) {
								errorLog("unexpected token value type...");
								exit(9);
							}

							element = elementStack.top();
							elementStack.pop();
							last++;
						}
						parsElems[first].type = _FUNCTOR;
						parsElems[first].valueFunctor = functor;

						first++;
						int n = last - first + 1;
						while (n > 0) {
							parsElems.erase(std::next(parsElems.begin(), first));
						}
					}
					else {
						elementStack.push(parsElems[temp]);
					}

					temp--;
				}
			}
			else if (!(parsElems[temp].type == _FUNCTOR)) {
				errorLog("functor name expected...");
				exit(9);
			}

			AtpPredicate *predicate = new AtpPredicate();
			predicate->name = equalityPredicate;
			predicate->value = kb.counter++;
			predicate->args.push_back(parsElems[idx - 1].valueFunctor);
			predicate->args.push_back(parsElems[idx + 1].valueFunctor);

			AtpLiteral *literal = new AtpLiteral();
			literal->polarity = false;
			literal->value = kb.counter++;
			literal->predicate = predicate;
			
			parsElems[idx - 1].type = _LITERAL;
			parsElems[idx - 1].valueLiteral = literal;

			parsElems.erase(std::next(parsElems.begin(), idx));
			parsElems.erase(std::next(parsElems.begin(), idx));
			continue;
		}
		else if (parsElems[idx].type == _TOKEN && parsElems[idx].valueToken->type == OP_NOT_EQUALS) {
			// RHS parsing
			temp = idx + 1;
			if (parsElems[temp].type == _TOKEN &&
				parsElems[temp].valueToken->type == VAR_NAME) {
				if (parsElems[temp + 1].type == _TOKEN &&
					parsElems[temp + 1].valueToken->type == BRACKET_ROUND_START) {

					std::stack<AtpParsingElement> elementStack;
					elementStack.push(parsElems[temp]);
					elementStack.push(parsElems[++temp]);
					temp++;

					AtpFunctor lastFunctor;
					bool lastF = true;
					while (!elementStack.empty()) {

						if (parsElems[temp].type == _TOKEN &&
							parsElems[temp].valueToken->type == BRACKET_ROUND_END) {
							last = temp;
							first = temp;

							AtpParsingElement element = elementStack.top();
							elementStack.pop();
							first--;

							std::vector<AtpFunctor*> functorSet;

							while (!(element.type == _TOKEN &&
								element.valueToken->type == BRACKET_ROUND_START)) {
								if (element.type == _FUNCTOR) {
									functorSet.push_back(element.valueFunctor);
								}
								else if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
									AtpFunctor *f = new AtpFunctor();
									f->type = std::isupper(element.valueToken->value[0]) ?
										VARIABLE :
										CONSTANT;
									f->arity = 0;
									f->value = kb.counter++;
									f->name = element.valueToken->value;
									functorSet.push_back(f);
								}
								else if (!(element.type == _TOKEN && element.valueToken->type == COMMA)) {
									errorLog("unexpected token value type...");
									exit(9);
								}

								element = elementStack.top();
								elementStack.pop();
								first--;
							}

							element = elementStack.top();
							elementStack.pop();
							first--;

							if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
								AtpFunctor *f = new AtpFunctor();
								f->type = FUNCTOR;
								f->functors = functorSet;
								f->name = element.valueToken->value;
								f->arity += f->functors.size();
								f->value = kb.counter++;
								element.type = _FUNCTOR;
								element.valueFunctor = f;
								first++;
								int n = last - first + 1;
								while (n > 0) {
									parsElems.erase(std::next(parsElems.begin(), first));
								}
							}
							else {
								errorLog("Functor name not present...");
								exit(9);
							}
						}
						else {
							elementStack.push(parsElems[temp]);
						}
						temp++;
					}
				}
				else {
					AtpFunctor *f = new AtpFunctor();
					f->type = std::isupper(parsElems[temp].valueToken->value[0]) ?
						VARIABLE :
						CONSTANT;
					f->arity = 0;
					f->value = kb.counter++;
					f->name = parsElems[temp].valueToken->value;

					parsElems[temp].type = _FUNCTOR;
					parsElems[temp].valueFunctor = f;
				}
			}
			else if (!(parsElems[temp].type == _FUNCTOR)) {
				errorLog("functor name expected...");
				exit(9);
			}

			// LHS parsing
			temp = idx - 1;

			if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == VAR_NAME) {
				AtpFunctor *f1 = new AtpFunctor();
				f1->type = std::isupper(parsElems[temp].valueToken->value[0]) ?
					VARIABLE :
					CONSTANT;
				f1->arity = 0;
				f1->value = kb.counter++;
				f1->name = parsElems[temp].valueToken->value;

				parsElems[temp].type = _FUNCTOR;
				parsElems[temp].valueFunctor = f1;
			}
			else if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == BRACKET_ROUND_END) {
				std::stack<AtpParsingElement> elementStack;

				while (!elementStack.empty()) {
					if (parsElems[temp].type == _TOKEN && parsElems[temp].valueToken->type == BRACKET_ROUND_START) {
						last = temp;
						first = temp;

						AtpParsingElement element = elementStack.top();
						elementStack.pop();
						first--;

						AtpFunctor *functor = new AtpFunctor();
						functor->value = kb.counter++;
						functor->name = parsElems[first].valueToken->value;

						while (!(element.type == _TOKEN &&
							element.valueToken->type == BRACKET_ROUND_END)) {
							if (element.type == _FUNCTOR) {
								functor->functors.push_back(element.valueFunctor);
								functor->arity++;
							}
							else if (element.type == _TOKEN && element.valueToken->type == VAR_NAME) {
								AtpFunctor *f = new AtpFunctor();
								f->type = std::isupper(element.valueToken->value[0]) ?
									VARIABLE :
									CONSTANT;
								f->name = element.valueToken->value;
								f->value = kb.counter++;
								f->arity = 0;
								functor->functors.push_back(f);
							}
							else if (!(element.type == _TOKEN && element.valueToken->type == COMMA)) {
								errorLog("unexpected token value type...");
								exit(9);
							}

							element = elementStack.top();
							elementStack.pop();
							last++;
						}
						parsElems[first].type = _FUNCTOR;
						parsElems[first].valueFunctor = functor;

						first++;
						int n = last - first + 1;
						while (n > 0) {
							parsElems.erase(std::next(parsElems.begin(), first));
						}
					}
					else {
						elementStack.push(parsElems[temp]);
					}

					temp--;
				}
			}
			else if (!(parsElems[temp].type == _FUNCTOR)) {
				errorLog("functor name expected...");
				exit(9);
			}

			AtpPredicate *predicate = new AtpPredicate();
			predicate->name = equalityPredicate;
			predicate->value = kb.counter++;
			predicate->args.push_back(parsElems[idx - 1].valueFunctor);
			predicate->args.push_back(parsElems[idx + 1].valueFunctor);

			AtpLiteral *literal = new AtpLiteral();
			literal->polarity = false;
			literal->value = kb.counter++;
			literal->predicate = predicate;

			idx--;
			parsElems[idx].type = _LITERAL;
			parsElems[idx].valueLiteral = literal;
			idx++;
			parsElems.erase(std::next(parsElems.begin(), idx));
			parsElems.erase(std::next(parsElems.begin(), idx));
			continue;
		}
		idx++;
	}
}

void resolvePredicatesAndFunctions(AtpKnBase& kb, std::vector<AtpParsingElement>& elements) {
	int idx = 0;

	while (idx < elements.size()) {
		AtpParsingElement e = elements[idx];
		if (e.type == _TOKEN) {
			switch (e.valueToken->type)
			{
			case OP_FOR_ALL:
			case OP_THERE_EXIST:
				while (!(e.type == _TOKEN && e.valueToken->type == COLON)) {
					e = elements[++idx];
				}
				break;

			case VAR_NAME:
				int pIdx = idx++;
				e = elements[idx++];
				if (e.type == _TOKEN && e.valueToken->type == BRACKET_ROUND_START) {
					std::stack<AtpParsingElement> elementStack;
					elementStack.push(elements[pIdx]);
					elementStack.push(e);

					AtpFunctor* f = NULL;
					while (!elementStack.empty()) {
						e = elements[idx++];

						if (e.type == _TOKEN && e.valueToken->type == BRACKET_ROUND_END) {
							int last = idx - 1;

							e = elementStack.top();
							elementStack.pop();
							int first = last - 1;

							std::vector<AtpFunctor*> functorSet;

							while (!(e.type == _TOKEN &&
								e.valueToken->type == BRACKET_ROUND_START)) {
								if (e.type == _FUNCTOR) {
									functorSet.push_back(e.valueFunctor);
								}
								else if (e.type == _TOKEN && e.valueToken->type == VAR_NAME) {
									AtpFunctor* f = new AtpFunctor();
									f->type = std::isupper(e.valueToken->value[0]) ?
										VARIABLE :
										CONSTANT;
									f->arity = 0;
									f->value = kb.counter++;
									f->name = e.valueToken->value;
									functorSet.push_back(f);
								}
								else if (!(e.type == _TOKEN && e.valueToken->type == COMMA)) {
									errorLog("unexpected token value type...");
									exit(9);
								}

								e = elementStack.top();
								elementStack.pop();
								first--;
							}

							e = elementStack.top();
							elementStack.pop();
							first--;

							// add to t a new function
							
							if (e.type == _TOKEN && e.valueToken->type == VAR_NAME) {
								if (first == pIdx) {
									AtpPredicate* pred = new AtpPredicate();
									pred->args = functorSet;
									pred->name = e.valueToken->value;
									pred->value = kb.counter++;

									elements[first].type = _PREDICATE;
									elements[first].valuePredicate = pred;
								}
								else {
									AtpFunctor* f = new AtpFunctor();
									f->type = std::isupper(e.valueToken->value[0]) ?
										VARIABLE :
										CONSTANT;
									f->arity = 0;
									f->value = kb.counter++;
									f->name = e.valueToken->value;
									f->functors = functorSet;

									// set it at first
									elements[first].type = _FUNCTOR;
									elements[first].valueFunctor = f;
								}

								idx = first + 1;
							}
							else {
								errorLog("unexpected token value type...");
								exit(9);
							}

							int n = last - first;
							while (n > 0) {
								elements.erase(std::next(elements.begin(), first + 1));
								n--;
							}
						}
						else {
							elementStack.push(e);
						}
					}
				}
				else {
					AtpPredicate* pred = new AtpPredicate();
					pred->name = elements[pIdx].valueToken->value;
					pred->value = kb.counter++;
					elements[pIdx].type = _PREDICATE;
					elements[pIdx].valuePredicate = pred;
				}
				continue;
			}
		}
		idx++;
	}
}

void resolveVariablesInFunctor(AtpStatement& statement, AtpFunctor* functor) {
	int idx = 0;
	while (idx < functor->functors.size()) {
		AtpFunctor* f = functor->functors[idx];
		if (statement.varMap.find(f->name) != statement.varMap.end() &&
			statement.varMap[f->name] != f) {
			functor->functors.erase(std::next(functor->functors.begin(), idx));
			std::string name = f->name;
			functor->functors.push_back(statement.varMap[name]);
			delete f;
			continue;
		}
		else {
			resolveVariablesInFunctor(statement, f);
		}
		idx++;
	}
}

void resolveVariablesInPredicate(AtpStatement& statement, std::vector<AtpParsingElement>& elements) {
	int idx = 0;
	while (idx < elements.size()) {
		if (elements[idx].type == _PREDICATE) {
			std::vector<AtpFunctor*>& args = elements[idx].valuePredicate->args;
			int idx = 0;
			while (idx < args.size()) {
				AtpFunctor* f = args[idx];
				if (statement.varMap.find(f->name) != statement.varMap.end() &&
					statement.varMap[f->name] != f) {
					args.erase(std::next(args.begin(), idx));
					std::string name = f->name;
					args.push_back(statement.varMap[name]);
					delete f;
					continue;
				}
				else {
					resolveVariablesInFunctor(statement, f);
				}
				idx++;
			}
		}
		idx++;
	}
}

void resolveVariables(AtpKnBase& kb, AtpStatement& statement, std::vector<AtpParsingElement>& elements) {
	int idx = 0, first, n;
	AtpParsingElement e;
	while (idx < elements.size()) {
		e = elements[idx];

		if (e.type == _TOKEN) {
			 switch (e.valueToken->type) {
			 case OP_FOR_ALL:
				 first = idx;
				 e = elements[idx];
				 while (!(e.type == _TOKEN && e.valueToken->type == COLON)) {
					 // Variables stored for universal elimination in future
					 if (e.type == _TOKEN && e.valueToken->type == VAR_NAME) {
						 AtpFunctor* f = new AtpFunctor();
						 f->arity = 0;
						 f->name = e.valueToken->value;
						 f->type = VARIABLE;
						 f->value = kb.counter++;
						 statement.varMap[e.valueToken->value] = f;
					 }
					 e = elements[++idx];
				 }
				 n = idx - first + 1;
				 while (n > 0) {
					 elements.erase(std::next(elements.begin(), first));
					 n--;
				 }
				 idx = first;
				 continue;
				 break;
			 case OP_THERE_EXIST:
				 first = idx;
				 e = elements[idx];
				 while (!(e.type == _TOKEN && e.valueToken->type == COLON)) {
					 // Skolemization
					 if (e.type == _TOKEN && e.valueToken->type == VAR_NAME) {
						 if (statement.varMap.size() <= 0) {
							 AtpFunctor* f = new AtpFunctor();
							 f->arity = 0;
							 f->name = skolemNamePre + std::to_string(kb.skolemCount++);
							 f->type = CONSTANT;
							 f->value = kb.counter++;
							 statement.varMap[e.valueToken->value] = f;
						 }
						 else {
							 AtpFunctor* f = new AtpFunctor();
							 f->arity = statement.varMap.size();
							 f->name = skolemNamePre + std::to_string(kb.skolemCount++);
							 f->type = FUNCTOR;
							 f->value = kb.counter++;
							 for (auto& it : statement.varMap) {
								 f->functors.push_back(it.second);
							 }
							 statement.varMap[e.valueToken->value] = f;
						 }
					 }
					 e = elements[++idx];
				 }
				 n = idx - first + 1;
				 while (n > 0) {
					 elements.erase(std::next(elements.begin(), first));
					 n--;
				 }
				 idx = first;
			 }
		}
		idx++;
	}

	resolveVariablesInPredicate(statement, elements);
}

void convertCNFForm(AtpStatement& statement, std::vector<AtpParsingElement>& elements) {

}

AtpStatement* getParsedStatement(AtpKnBase& kb, std::vector<AtpParsingElement> elements) {
	resolveMultiCharOperators(elements);

	// print statement
	std::vector<AtpParsingElement>::iterator it = elements.begin();
	while (it != elements.end()) {
		std::cout << (*it).valueToken->value;
		it++;
	}
	std::cout << std::endl;

	AtpStatement *statement = new AtpStatement();

	// resolve equality
	resolveEquality(kb, elements);
	
	// resolve predicates
	resolvePredicatesAndFunctions(kb, elements);

	// resolve variables
	resolveVariables(kb, *statement, elements);
	
	// convert to cnf form (and of ors) (conjunctive normal form)
	convertCNFForm(*statement, elements);

	return statement;
}