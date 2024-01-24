#include "AtpParser.h"

void errorLog(std::string msg) {
	std::cout << "ERROR: " << msg << std::endl;
}

bool isEscapeChar(char c) {
	return escapeCharSet.find(c) != escapeCharSet.end();
}

void AtpParser::setFileName(std::string name) {
	this->filename = name;
	this->stream.close();
	this->stream.open(this->filename);
	this->lineNo = 0;
	this->expectedToken = ANY;
}

AtpToken AtpParser::getNextToken() {
	if (!this->tokenBuffer.empty()) {
		AtpToken token = this->tokenBuffer.front();
		this->tokenBuffer.pop();
		return token;
	}

	char c;
	if (this->haveNextToken()) {
		this->stream.get(c);

		while (c == '\n' || c == '\t')
		{
			if (c < 0 || this->stream.eof()) {
				return AtpToken(END_OF_FILE, "");
			}
			this->stream.get(c);
		}

		if (c < 0 || this->stream.eof()) {
			return AtpToken(END_OF_FILE, "");
		}

		if (this->expectedToken == ANY && c == '%') {
			// line is a comment
			std::string val = "";
			while (c != '\n') { // parsing till end of line
				this->stream.get(c);
				val = val + c;
			}
			this->tokenBuffer.push(AtpToken(COMMENT, val));
			this->expectedToken = ANY;
		}
		else if (this->expectedToken == ANY && c == 'i') {
			stream.get(c);
			if (c == 'n') {
				stream.get(c);
				if (c == 'c') {
					stream.get(c);
					if (c == 'l') {
						stream.get(c);
						if (c == 'u') {
							stream.get(c);
							if (c == 'd') {
								stream.get(c);
								if (c == 'e') {
									// we found include file
									this->tokenBuffer.push(AtpToken(FILE_INCLUDE, "include"));
									this->expectedTokenBuffer = FILE_INCLUDE;
									this->expectedToken = BRACKET_ROUND_START;
								}
								else {
									this->error();
								}
							}
							else {
								this->error();
							}
						} 
						else {
							this->error();
						}
					}
					else {
						this->error();
					}
				}
				else {
					this->error();
				}
			}
			else {
				this->error();
			}
		}
		else if (this->expectedToken == BRACKET_ROUND_START && c == '(') {
			//this is bracket round start
			this->tokenBuffer.push(AtpToken(BRACKET_ROUND_START, "("));
			if (this->expectedTokenBuffer == FILE_INCLUDE) {
				this->expectedTokenBuffer = this->expectedToken;
				this->expectedToken = FILE_NAME;
			}
			else {
				this->expectedTokenBuffer = this->expectedToken;
				// the bracket belongs to a formula hence a new formula needs to be parsed
				
				// reading formula name
				this->stream.get(c);
				std::string name = "";
				while (c != ',')
				{
					name = name + c;
					this->stream.get(c);
				}
				this->tokenBuffer.push(AtpToken(FORMULA_NAME, name));
				this->tokenBuffer.push(AtpToken(COMMA, ","));
				name = "";
				
				// reading formula type
				this->stream.get(c);
				while (c != ',')
				{
					name = name + c;
					this->stream.get(c);
				}
				this->tokenBuffer.push(AtpToken(FORMULA_TYPE, name));
				this->tokenBuffer.push(AtpToken(COMMA, ","));
				
				// parsing formula
				this->stream.get(c);
				bool stringMode = false;
				name = "";
				while (c != '.') {
					// skipping space/tab/newline character
					while (c == ' ' || c == '\n' || c == '\t') {
						this->stream.get(c);
					}

					if (isEscapeChar(c)) {
						if (stringMode && std::strcmp(name.c_str(), "") != 0 && !name.empty()) {
							this->tokenBuffer.push(AtpToken(VAR_NAME, name));
						}
						stringMode = false;
						this->tokenBuffer.push(AtpToken(tokenMap.find(c)->second, std::string(1, c)));
					}
					else {
						std::string val = std::string(1, c);
						if (stringMode) {
							name = name + val;
						}
						else {
							stringMode = true;
							name = val;
						}
					}

					this->stream.get(c);
				}
				if (stringMode && std::strcmp(name.c_str(), "") != 0) {
					this->tokenBuffer.push(AtpToken(VAR_NAME, name));
				}
				this->tokenBuffer.push(AtpToken(END_SENTENCE, "."));
				this->expectedToken = ANY;
			}
		}
		else if (this->expectedToken == FILE_NAME) {
			std::string name = "" + c;
			while (c != ')') {
				this->stream.get(c);
				if (!isEscapeChar(c) || (isEscapeChar(c) && (c == ')' || c == '.' || c == '\''))) {
					name = name + c;
				}
				else {
					std::string msg = "unexpected token " + 
						std::string(1, c) + 
						" at line " + 
						std::to_string(this->lineNo) + "\n";
					errorLog(msg);
					exit(7);
				}
			}
			this->tokenBuffer.push(AtpToken(FILE_NAME, name));
			this->tokenBuffer.push(AtpToken(BRACKET_ROUND_END, ")"));
			this->expectedToken = END_SENTENCE;
		}
		else if ((this->expectedToken == END_SENTENCE || this->expectedToken == ANY)
			&& c == '.') {
			this->tokenBuffer.push(AtpToken(END_SENTENCE, "."));
			this->expectedToken = ANY;
		}
		else if (expectedToken == ANY && c == 'f') {
			this->stream.get(c);
			if (c == 'o') {
				this->stream.get(c);
				if (c == 'f') {
					// language name has been found fof
					this->tokenBuffer.push(AtpToken(LANGUAGE_NAME, "fof"));
					this->expectedToken = BRACKET_ROUND_START;
				}
				else {
					error();
				}
			}
			else {
				error();
			}
		}
		else {
			error();
		}
	}
	else {
		errorLog("UNEXPECTED END OF FILE...");
		exit(6);
	}

	AtpToken token(ANY,"");
	if (!this->tokenBuffer.empty()) {
		token = this->tokenBuffer.front();
		tokenBuffer.pop();
	}
	lineNo++;
	return token;
}

bool AtpParser::haveNextToken() {
	return !(this->stream.eof());
}

void AtpParser::close() {
	this->stream.close();
}

void AtpParser::error() {
	std::cout << "system have got ann error at line " << this->lineNo << std::endl;
	exit(5);
}