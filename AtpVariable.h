#pragma once
#include <string>

class AtpVariable
{
public:
	int value;
	std::string name;

	bool operator==(const AtpVariable& var) const {
		return this->value == var.value && std::strcmp(this->name.c_str(), var.name.c_str());
	}

	bool operator<(const AtpVariable& var) const {
		return this->value < var.value;
	}
};

