#pragma once
#include "AtpActor.h"
using namespace std;
class AtpClause
{
public:
	std::set<AtpActor> actors;
	int value;

	void addActor(AtpActor actor);

	// operator overloading
	bool operator==(const AtpClause& clause) const
	{
		if (this->actors.size() != clause.actors.size()) {
			return false;
		}
		for (auto& actor : this->actors) {
			if (clause.actors.find(actor) == clause.actors.end()) {
				return false;
			}
		}
		return true;
	}

	bool operator<(const AtpClause& clause) const
	{
		return this->value < clause.value;
	}

	bool operator>(const AtpClause& clause) const
	{
		return  this->value > clause.value;
	}
};

