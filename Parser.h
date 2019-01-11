

#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H
#include "Token.h"
#include <vector>
#include "Parameter.h"
#include <string>
#include "Predicate.h"
#include "DataLogProgram.h"
#include <set>
class Parser {
public:
Parser(vector<Token> tokens){
    
    
    tokenVec = tokens;
   
}
~Parser(){}
    void Parse();
    Predicate ParseHeadPredicate();
    void ParseIDList(vector<Parameter> &paramVec);
    void ParseFactList();
    Predicate ParseFact(string value);
    void Match(TokenType inType);
    void ParseStringList(vector<string>& PredVec);
    void ParseSchemeList();
    void ParseQueryList(vector<Predicate>& PredVec);
    Predicate ParsePredicate();
    void ParsePredicateList(vector<Predicate>& PredVec);
    string ParseParameter();
    void ParseParameterList(vector<Parameter> &PredicateVecs);
    Predicate ParseQuery();
    void ParseDataLogProgram();
    void ParseScheme();
    void ParseRuleList();
    void ParseRule();
    string ParseOperator();
    string ParseExpression();
    set<string> DomainSet;
    DatalogProgram DLP;
    bool IsConstant();
private:
    int index = 0;
    vector<Token> tokenVec;
    
    
};


