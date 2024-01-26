#pragma once
#include <set>
#include "AtpTerm.h"
using namespace std;

enum AtpActorType {
	PREDICATE,
	FUNCTION
};

class AtpActor
{
public:
	bool polarity;
	AtpActorType type;
	int value;
	std::set<AtpTerm> terms;
	std::set<AtpActor> actors;

    // operator overloading
    bool operator ==(const AtpActor& actor) const
    {
        if (this->polarity != actor.polarity) {
            return false;
        }

        if (this->terms.size() != actor.terms.size() ||
            this->actors.size() != actor.actors.size()) {
            return false;
        }

        for (auto& t : this->terms) {
            if (actor.terms.find(t) == actor.terms.end()) {
                return false;
            }
        }

        for (auto& a : this->actors) {
            if (actor.actors.find(a) == actor.actors.end()) {
                return false;
            }
        }

        return true;
    }

    bool operator<(const AtpActor& actor) const
    {
        return this->value < actor.value;
    }

    bool operator>(const AtpActor& actor) const
    {
        return this->value < actor.value;
    }
};

