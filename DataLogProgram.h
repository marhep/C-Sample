
#pragma once
#include "Token.h"

#include "Predicate.h"
#include "Rule.h"
#include <set>

class DatalogProgram {
    public:
DatalogProgram(){}
~DatalogProgram(){}


void addFact(Predicate InPred);
void addScheme(Predicate InPred);
void addRule(Rule InRule);
void addQuery(Predicate InPred);
//void ParseDatalogProgram();
void ToString();
void MakeDomain(set<string> DomainSet);
set<string>::iterator it;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rule;
    vector<Predicate> query;
    vector<string> domain;
    //Token errorToken;

};



