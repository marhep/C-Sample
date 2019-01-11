#include "Tuple.h"

string Tuple::ToString(Header inHeader) {
    stringstream ss;
    
    for (unsigned int i = 0; i < this->size(); ++i){
        if (i == 0){
            ss << "  ";
        }
        ss << inHeader.at(i) <<  "="<<  this->at(i);
        if (this->size() > 1 && i < this->size()-1) {
            ss << ", ";
        }
        
    }
    
    return ss.str();
}

