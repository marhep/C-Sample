#include <iostream>
#include <string>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"
#include <vector>
#include "Token.h"
#include "Interpreter.h"



using namespace std;
int main(int argc, char const *argv[])
{
    ifstream fin(argv[1]);
    string fileContent((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
    Scanner lexScan(fileContent);
    lexScan.ParseFile();
    lexScan.TokentoString();
    vector<Token> tokVec = lexScan.GetVec();
    Parser parsing(tokVec);
    parsing.Parse();
    
    Interpreter(parsing.DLP);
    
    return 0;
}

