
#pragma once
#include <string>
#include <list>
#include <set>
#include "Header.h"
#include "Tuple.h"
#include "Parameter.h"
using namespace std;


class Relation {
    public:
    Relation(string inName, Header inHeader) {
        Name= inName;
        RelHeader = inHeader;
    }
    Relation () {
        
    }

    ~ Relation(){}
    void ToString();
    void addTuple(Tuple t);
    Relation Select(string inString, int ColNum);
    Relation Select(int ColNum1, int ColNum2);
    Relation Project(vector<int> inVec);
    Relation ProjectwithParams(vector<Parameter>& paramVector);
    Relation Unionite(Relation& RelUnion);
    Relation joinRelations(Relation& r1, Relation& r2);
    Header joinHeaders(Header h1, Header h2);
    Tuple joinTuples(Header& h1, Header& h2, Tuple& t1, Tuple& t2);
    bool joinable(Header& h1, Header& h2, Tuple& t1, Tuple& t2);
    
    
    void Rename(Header newHeader);

    
    
    set<Tuple> Tuples;
    string Name;
    Header RelHeader;
    int NumTuples;
    
};





