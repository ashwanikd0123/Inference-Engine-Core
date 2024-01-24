#pragma once
#include <string>
#include <fstream>
#include <queue>
#include "AtpToken.h"
#include <iostream>

class AtpParser
{
private:
	std::string filename;
	std::ifstream stream;
	std::queue<AtpToken> tokenBuffer;
	TokenType expectedToken;
	TokenType expectedTokenBuffer;
	int lineNo;
public:
	void setFileName(std::string name);
	AtpToken getNextToken();
	bool haveNextToken();
	void close();
	void error();
};

