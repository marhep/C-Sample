
#pragma once
#include <string>
#include "Parameter.h"
#include "Token.h"
#include <fstream>
#include <sstream>
#include <vector>


class Predicate {
public:
Predicate(string inID, vector<Parameter> inparamVec){
    id = inID;
    paramVec =inparamVec;
}
Predicate() {
    
}
~Predicate(){}
string ToString();
string id;
vector<Parameter> paramVec;

    
};



