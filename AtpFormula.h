#pragma once
#include "AtpLiteral.h"

enum AtpConnector {
	CONN_AND,
	CONN_OR
};

class AtpFormula
{
public:
	int value;
	AtpConnector connector;
	std::vector<AtpLiteral> literals;
};

