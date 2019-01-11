

#pragma once
#include "Predicate.h"
#include <vector>
#include <sstream>
#include <fstream>


class Rule {
    public:
Rule(Predicate& InHeadPred, vector<Predicate>& InPredvec){
    HeadPredicate = InHeadPred;
    PredVec = InPredvec;
    
}
~Rule(){
}
string ToString();
Predicate HeadPredicate;
vector<Predicate> PredVec;
};



