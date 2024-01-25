#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <regex>
#include <filesystem>

#include "AtpParser.h"
#include "AtpToken.h"
#include "AtpKnBase.h"

#define THEOREM 1
#define UNSATISFIABLE 2

extern int mode;
extern void errorLog(std::string msg);

const std::string axiomDir = "tptp\\Axioms";
const std::string problemDir = "tptp\\Problems";

AtpKnBase knowledgeBase;

std::string joinFilePath(std::string a, std::string b) {
	return a + '\\' + b;
}

void readAxioms(std::string fileName) {
	AtpParser parser;
	std::string filePath;
	// START { process string
	std::string temp = "";
	std::regex rgx("[A-Z]+[0-9]+\\+[0-9]+\\.ax");
	std::smatch match;
	if (std::regex_search(fileName , match, rgx) && !match.str(0).empty()) {
		std::cout << "reading axioms from " << match.str(0) << std::endl;
		filePath = joinFilePath(axiomDir, match.str(0));
	}
	else {
		errorLog("not a valid file path inclusion " + fileName + "...");
	}

	// process string } END
	parser.setFileName(filePath);

	// parsing axioms
	AtpToken token(ANY, "");
	bool endOfFile = false;
	while (parser.haveNextToken()) {
		token = parser.getNextToken();
		std::vector<AtpToken> tokens;
		switch (token.type) {
		case END_OF_FILE:
			endOfFile = true;
			break;

		case LANGUAGE_NAME:
			tokens.push_back(token);
			token = parser.getNextToken();
			while (token.type != END_SENTENCE) {
				tokens.push_back(token);
				token = parser.getNextToken();
			}
			tokens.push_back(token);

			knowledgeBase.parseFormula(tokens);
			break;
		}

		if (endOfFile) {
			break;
		}
	}

	parser.close();
}

/*
we are only considering the problem which are already theorem or are unsatisfiable
*/
void startTPTPtests() {
	AtpParser parser;
	std::map<std::string, int> statusMap = {
		{"Theorem", THEOREM},
		{"Unsatisfiable", UNSATISFIABLE}
	};
	
	for (auto& entry : std::filesystem::directory_iterator(problemDir)) {
		std::string problem = entry.path().string();
		int slashIdx = problem.find_last_of("\\");
		problem = problem.substr(slashIdx + 1);

		// these problems were deleted due to invalid state
		if (problem.contains(".rm")) {
			continue;
		}

		knowledgeBase.init();

		std::cout << "problem: " << problem << std::endl;
		parser.setFileName(joinFilePath(problemDir, problem));
		AtpToken token(ANY, "");

		bool statusFound = false;
		int status = 1000; // to check status of the problem (should be either THEOREM or UNSATISFIABLE)
		bool isFof = true; // to check if the problem is written in first order syntax

		bool endOfFile = false;
		while (parser.haveNextToken()) {
			token = parser.getNextToken();
			std::vector<AtpToken> tokens;
			switch (token.type) {
			case COMMENT:
				if (!statusFound && token.value.contains("Status   :")) {
					// getting the status of the problem
					std::string st = "";
					for (int i = 0; i < token.value.size(); i++) {
						if (token.value[i] == ':') {
							for (int j = i + 2; j < token.value.size() && 
								token.value[j] != '\n'; j++) {
								st += token.value[j];
							}
							break;
						}
					}
					statusFound = true;
					if (statusMap.find(st) != statusMap.end()) {
						status = statusMap[st];
					}
					else {
						status = 0;
					}
				}
				else if (token.value.contains("SPC      :")) {
					// getting the SPC of the problem
					std::string st = "";
					for (int i = 0; i < token.value.size(); i++) {
						if (token.value[i] == ':') {
							for (int j = i + 2; j < token.value.size() &&
								token.value[j] != '\n'; j++) {
								st += token.value[j];
							}
							break;
						}
					}
					if (!st.contains("FOF")) {
						isFof = false;
					}
				}
				else {
					std::cout <<
						escapeCharNames.find(token.type)->second
						<< " : " << token.value << std::endl;
				}
				break;

			case FILE_INCLUDE:
				token = parser.getNextToken();
				if (token.type == BRACKET_ROUND_START) {
					token = parser.getNextToken();
					if (token.type == FILE_NAME) {
						if (token.value.empty()) {
							errorLog("invalid filename...");
						}
						readAxioms(token.value);
						token = parser.getNextToken();
						if (token.type != BRACKET_ROUND_END) {
							errorLog("( expected...");
							exit(7);
						}
						token = parser.getNextToken();
						if (token.type != END_SENTENCE) {
							errorLog("end of sentence (.) expected...");
							exit(7);
						}
					}
					else {
						errorLog("error in token parsing...");
						exit(7);
					}
				}
				else {
					errorLog("error in token parsing...");
					exit(7);
				}
				break;

			case END_OF_FILE:
				endOfFile = true;
				break;

			case LANGUAGE_NAME:
				tokens.push_back(token);
				token = parser.getNextToken();
				while (token.type != END_SENTENCE) {
					tokens.push_back(token);
					token = parser.getNextToken();
				}
				tokens.push_back(token);

				knowledgeBase.parseFormula(tokens);
				break;
			}

			if (endOfFile) {
				break;
			}
		
			if ((statusFound && !status) || !isFof) {
				std::cout << "this should be skipped" << std::endl;
				break;
			}
		}

		std::cout << "status of the problem is " << status << std::endl;
		parser.close();
		return;
	}

}