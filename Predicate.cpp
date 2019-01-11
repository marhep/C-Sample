

#include "Predicate.h"
string Predicate::ToString(){
    stringstream ss;
    ss << id << "(";
    for (int i = 0; (unsigned) i < paramVec.size(); i++) {
        ss<< paramVec.at(i).GetValue();
        if ((unsigned)  i < paramVec.size() - 1) {
            ss << ",";
        }
    }
    ss << ")";
    return ss.str();
}


