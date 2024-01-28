#pragma once
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

enum TokenType {
	COMMENT,
	LANGUAGE_NAME,
	BRACKET_ROUND_START,
	BRACKET_ROUND_END,
	BRACKET_SQUARE_START,
	BRACKET_SQUARE_END,
	END_SENTENCE,
	FORMULA_NAME,
	FORMULA_TYPE,
	COMMA,
	COLON,
	OP_EQUALS,
	OP_AND,
	OP_OR,
	OP_NOT,
	OP_FOR_ALL,
	OP_THERE_EXIST,
	OP_LESS_THAN,
	OP_GREATER_THAN,
	FILE_INCLUDE,
	ANY,
	FILE_NAME,
	NEW_LINE,
	VAR_NAME,
	END_OF_FILE,

	// multi symbol tokens
	OP_IMPLICATION,
	OP_EQUIVALENCE,
	OP_XOR,
	OP_NOT_EQUALS,
};

const std::unordered_map<TokenType, std::string> escapeCharNames = {
	{COMMENT, "COMMENT"},
	{LANGUAGE_NAME, "LANGUAGE_NAME"},
	{BRACKET_ROUND_START, "BRACKET_ROUND_START"},
	{BRACKET_ROUND_END, "BRACKET_ROUND_END"},
	{BRACKET_SQUARE_START, "BRACKET_SQUARE_START"},
	{BRACKET_SQUARE_END, "BRACKET_SQUARE_END"},
	{END_SENTENCE, "END_SENTENCE"},
	{FORMULA_NAME, "FORMULA_NAME"},
	{FORMULA_TYPE, "FORMULA_TYPE"},
	{COMMA, "COMMA"},
	{COLON, "COLON"},
	{OP_EQUALS, "OP_EQUALS"},
	{OP_AND, "OP_AND"},
	{OP_OR, "OP_OR"},
	{OP_NOT, "OP_NOT"},
	{OP_FOR_ALL, "OP_FOR_ALL"},
	{OP_THERE_EXIST, "OP_THERE_EXIST"},
	{OP_LESS_THAN, "OP_LESS_THAN"},
	{OP_GREATER_THAN, "OP_GREATER_THAN"},
	{FILE_INCLUDE, "FILE_INCLUDE"},
	{ANY, "ANY"},
	{FILE_NAME, "FILE_NAME"},
	{NEW_LINE, "NEW_LINE"},
	{VAR_NAME, "VAR_NAME"},

	// multi symbol tokens
	{OP_NOT_EQUALS, "OP_NOT_EQUALS"},
	{OP_IMPLICATION, "OP_IMPLICATION"},
	{OP_EQUIVALENCE, "OP_EQUIVALENCE"},
	{OP_XOR, "OP_XOR"},
};

const std::set<char> escapeCharSet = {
	'(',
	')',
	'[',
	']',
	'.',
	',',
	':',
	'=',
	'!',
	'&',
	'|',
	'~',
	'?',
	'<',
	'>',
};

const std::unordered_map<char, TokenType> tokenMap = {
	{'(', BRACKET_ROUND_START},
	{')', BRACKET_ROUND_END},
	{'[', BRACKET_SQUARE_START},
	{']', BRACKET_SQUARE_END},
	{'.', END_SENTENCE},
	{',', COMMA},
	{':', COLON},
	{'=', OP_EQUALS},
	{'&', OP_AND},
	{'|', OP_OR},
	{'~', OP_NOT},
	{'!', OP_FOR_ALL},
	{'?', OP_THERE_EXIST},
	{'<', OP_LESS_THAN},
	{'>', OP_GREATER_THAN}
};

const std::unordered_map<TokenType, std::string> tokenTypeMap = {
	{BRACKET_ROUND_START, "("},
	{BRACKET_ROUND_END, ")"},
	{BRACKET_SQUARE_START, "["},
	{BRACKET_SQUARE_END, "]"},
	{END_SENTENCE, "."},
	{COMMA, ","},
	{COLON, ":"},
	{OP_EQUALS, "="},
	{OP_AND, "&"},
	{OP_OR, "|"},
	{OP_NOT, "~"},
	{OP_FOR_ALL, "!"},
	{OP_THERE_EXIST, "?"},
	{OP_LESS_THAN, "<"},
	{OP_GREATER_THAN, ">"},

	// multi symbol tokens
	{OP_IMPLICATION, "=>"},
	{OP_EQUIVALENCE, "<=>"},
	{OP_XOR, "<~>"},
	{OP_NOT_EQUALS, "!="},
};

class AtpToken
{
public:
	TokenType type;
	std::string value;

	AtpToken(TokenType type, std::string value) {
		this->type = type;
		this->value = value;
	}
};