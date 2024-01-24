#pragma once
enum TermType {
	CONSTANT,
	VARIABLE
};

class Term
{
	TermType type;
	int value;
};

