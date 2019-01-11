#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_TYPE};
static const map<TokenType, string> TokenMap = {
        {COMMA, "COMMA"}, {PERIOD, "PERIOD"}, {Q_MARK, "Q_MARK"},
        {LEFT_PAREN, "LEFT_PAREN"},{RIGHT_PAREN, "RIGHT_PAREN"},
        {COLON, "COLON"},{COLON_DASH, "COLON_DASH"},{MULTIPLY, "MULTIPLY"},
        {ADD, "ADD"},{SCHEMES, "SCHEMES"},{FACTS, "FACTS"},{RULES, "RULES"},
        {QUERIES, "QUERIES"},{ID, "ID"},{STRING, "STRING"},{COMMENT, "COMMENT"},
        {UNDEFINED, "UNDEFINED"},{EOF_TYPE, "EOF"}
};
class Token {
private:

    

   
public:
            Token (TokenType tokenName, string tokenInfo, int lineNum) {
                type = tokenName;
                lineNumber = lineNum;
                value = tokenInfo;
            }
            ~Token() {}
            void TokenString();
            TokenType type;
             string value;
            int lineNumber;
};