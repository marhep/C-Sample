#include "Token.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;


class Scanner {
private:
    
    string stringToScan;
    int lineCount = 1;
    int numTokens = 0;
    int index;
    int keywordCount = 0;
public:
    Scanner(string file) {
        stringToScan = file;
    }
    ~Scanner() {}
    string tokenScanner(string token);
    int FindBasicTokens(); 
    int FindFacts();
    int FindRules();
    int FindSchemes();
    int FindQueries();
    int FindID();
    int FindString();
    bool BlockComment();
    bool SingleComment();
    int FindComment();
    void ParseFile();
    void TokentoString();
    vector<Token> GetVec();
    vector<Token> tokens;

};




