
#include "Scanner.h"
using namespace std;

int Scanner::FindBasicTokens(){
    switch(stringToScan[index]) {
        case ',': tokens.push_back(Token(COMMA, ",", lineCount));
            index++;
            return 1;
        case '.': tokens.push_back(Token(PERIOD, ".", lineCount));
            index++;
            return 1;
        case '?': tokens.push_back(Token(Q_MARK, "?", lineCount));
            index++;
            return 1;
        case '(': tokens.push_back(Token(LEFT_PAREN, "(", lineCount));
            index++;
            return 1;
        case ')': tokens.push_back(Token(RIGHT_PAREN, ")", lineCount));
            index++;
            return 1;
        case ':':
            if (stringToScan[index + 1] == '-') {
                tokens.push_back(Token(COLON_DASH, ":-", lineCount));
                index++;
            }
            else {
                tokens.push_back(Token(COLON, ":", lineCount));
            }
            index++;
            return 1;
        case '*': tokens.push_back(Token(MULTIPLY, "*", lineCount));
            index++;
            return 1;
        case '+': tokens.push_back(Token(ADD, "+", lineCount));
            index++;
            return 1;
    }
    return 0;
}

int Scanner::FindFacts(){
    string facts = "Facts";
    if (stringToScan.substr(index, facts.size()) == "Facts"){
        tokens.push_back(Token(FACTS, "Facts", lineCount));
        index += facts.size();
        keywordCount++;
        return 1;
    }
    return 0;

}
int Scanner::FindRules(){
    string rules = "Rules";
    if (stringToScan.substr(index, rules.size()) == "Rules"){
        tokens.push_back(Token(RULES, "Rules", lineCount));
        index += rules.size();
        keywordCount++;
        return 1;
    }
    return 0;
}
int Scanner::FindSchemes(){
    string schemes = "Schemes";
    if (stringToScan.substr(index, schemes.size()) == "Schemes"){
        tokens.push_back(Token(SCHEMES, "Schemes", lineCount));
        index += schemes.size();
        keywordCount++;
        return 1;
    }
    return 0;
}
int Scanner::FindQueries(){
    string queries = "Queries";
    if (stringToScan.substr(index, queries.size()) == "Queries"){
        tokens.push_back(Token(QUERIES, "Queries", lineCount));
        index += queries.size();
        keywordCount++;
        return 1;
    }
    return 0;
}


int Scanner::FindID(){
    int i = index;
    if (isalpha(stringToScan[i])) {
        stringstream ss;
        ss << stringToScan[i];
        i++;
        while (isalnum(stringToScan[i])) {
            ss << stringToScan[i];
            i++;
        }
        if (ss.str() == "Facts") {
            return FindFacts();
        }
        else if (ss.str() == "Rules") {
            return FindRules();
        }
        else if (ss.str() == "Schemes") {
            return FindSchemes();
        }
        else if (ss.str() == "Queries") {
            return FindQueries();
        }
        index = i;
        tokens.push_back(Token(ID, ss.str(), lineCount));
        return 1;
    }
    return 0;
}
int Scanner::FindString(){
    int i = index;
    int originalLineCount = lineCount;
    if (stringToScan[i] == '\'') {
        stringstream ss;
        ss << stringToScan[i];
        i++;
        while ((unsigned) i != stringToScan.size()) {
            if (stringToScan[i] == '\'' && stringToScan[i + 1] != '\'') {
                ss << stringToScan[i];
                i++;
                index = i;
                tokens.push_back(Token(STRING, ss.str(), originalLineCount));
                return 1;
            }

            else if (stringToScan[i] == '\'' && stringToScan[i + 1] == '\'') {
                ss << stringToScan[i];
                ss << stringToScan[i + 1];
                i += 2;
            }
            else if (stringToScan[i] == '\n') {
                ss << stringToScan[i];
                i++;
                lineCount++;
            }
            else {
                ss << stringToScan[i];
                i++;
            }

        }
        index = i;
        tokens.push_back(Token(UNDEFINED, ss.str(), originalLineCount));
        return 1;
    }
    return 0;
}

bool Scanner::BlockComment() {
    int originalLineCount = lineCount;
    int i = index;
    stringstream ss;
    ss << stringToScan[i];
    ss << stringToScan[i + 1];
    i+= 2;
    while ((unsigned) i != stringToScan.size()) { // index < string to scan
        if ((stringToScan[i]) == '|') {
            if ((stringToScan[i + 1]) == '#'){
                ss << stringToScan[i] << stringToScan[i+1];
                i +=2;
                index = i;
                return true;
            }
        }
        if (stringToScan[i] == '\n') {
            lineCount++;
        }
        ss << stringToScan[i];
        i++;
    }
    index = i;
    tokens.push_back(Token(UNDEFINED, ss.str(), originalLineCount));
    return true;

}
bool Scanner::SingleComment() {
    int i = index;
    stringstream ss;
    ss << stringToScan[i];
    ++i;
    while ((stringToScan[i]) != '\n') {
        ss << stringToScan[i];
        i++;
    }
    index = i;
    return true;

}
int Scanner::FindComment(){
    int i = index;

    if (stringToScan[i] == '#') {
        if (stringToScan[i + 1] ==  '|') {
            if (BlockComment()){

                return 1;
            }
            return 0;
        }
        else {
            if (SingleComment()){
                return 1;
            }
            return 0;
        }
    }
    else {
        return 0;
    }
}

void Scanner::ParseFile() {
    index = 0;
    stringstream ss;
    while ((unsigned) index < stringToScan.size()) {
        int foundItem = 0;
        keywordCount = 0;
        if (stringToScan[index] == '\n') {
            index++;
            lineCount++;
            continue;
        }
        if (isspace(stringToScan[index])) {
            index++;
        }

        foundItem += FindBasicTokens();
        foundItem += FindID();
        foundItem += FindString();
        foundItem += FindComment();
        if (foundItem == 0 && !isspace(stringToScan[index]))  {
            string s;
            s += stringToScan[index];
            if (!s.empty()) {
                tokens.push_back(Token(UNDEFINED, s, lineCount));
            }
            index++;
        }
    }
    tokens.push_back(Token(EOF_TYPE,"",lineCount));
}
void Scanner::TokentoString() {
    for (int i = 0; (unsigned) i < tokens.size(); i++) {
        tokens.at(i).TokenString();
    }
    cout << "Total Tokens = " << tokens.size() << endl;;
}
 vector<Token> Scanner::GetVec() {
     return tokens;
 }