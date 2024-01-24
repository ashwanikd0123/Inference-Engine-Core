#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>

#define MODE_USER_INPUT 0
#define MODE_TPTP_TEST 1

int mode;

extern void startTPTPtests();

int main()
{
    std::cout << "*******Inference Engine Core V 1.0*******\n\n\n\n" << std::endl;
    std::cout << "starting program..." << std::endl;

    std::cout << "please enter mode of program\n" <<
        "0: user input test file\n" <<
        "1: run Standard TPTP test cases" << std::endl;

    std::cin >> mode;

    switch (mode) {
    case MODE_USER_INPUT:
        break;
    case MODE_TPTP_TEST:
        startTPTPtests();
        break;
    default:
        std::cout << "invalid mode selected!\n" <<
            "exiting program...";
        exit(1);
    }
    std::cout << "Process ended..." << std::endl;
}
