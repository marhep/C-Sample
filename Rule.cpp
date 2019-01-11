
#include "Rule.h"
string Rule::ToString() {
    stringstream ss;
    ss  << HeadPredicate.ToString()<< " :- " ;
    for (int i = 0; (unsigned)  i < PredVec.size(); i++) {
        ss<< PredVec.at(i).ToString();
        if ((unsigned)  i < PredVec.size() - 1){
           ss<< ",";
        }
    }
   
    return ss.str();
}