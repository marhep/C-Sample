
#pragma once
#include <vector> 
#include <string>
#include <iostream>
#include "Database.h"
#include "DataLogProgram.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Rule.h"
#include "Parameter.h"
#include "Graph.h"
#include <set>
using namespace std;

class Interpreter {
    public:
    Interpreter(DatalogProgram inDLP) {
    DLP = inDLP;
    schemes = DLP.schemes;
    facts = DLP.facts;
    query = DLP.query;
    rule = DLP.rule;
    MakeDatabase();
    }
    Interpreter() {}
    
    void MakeDatabase();
    Relation EvaluateOneQuery(string RelID, vector<string> ParamVec, vector<string> foundString, vector<int> foundStringColNum, vector<int> dupVec, bool isRule);
    void EvaluateAllQueries();
    void Print(Relation r);
    void LookForDups(Predicate query, int j);
    Database DB = Database();
    DatalogProgram DLP;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    void EvalRule(int& index, set<int>& SCCVec);
    Relation EvalRulePt2(int i);
    vector<Predicate> query;
    vector<Rule> rule;
    void OptimizeRule(Graph& g, Graph& ReverseGraph);
    void PossibleAnotherRound(bool AnotherRound, int &index, set<int>& SCCVec);
    void FindWantedCols(Header &inVec, vector<int> &intVec);
    set<string> RuleIDs;
    vector<string> RuleIDvec;
    void Optimization(Graph& ReverseGraph,  Graph& g);
    bool Looping(set<int> i);
    void SingleSCC(int i);
    void EvaluateAllRules();
    void PrintSCC(set<int>& SCCSet);
    
    vector<int> dupVec;
    private:
    
    
    
};