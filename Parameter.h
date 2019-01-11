

#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H
#include <string>
using namespace std;


class Parameter {
    public:
    Parameter(string inParameter, string inType) {
        value  = inParameter;
        type = inType;
    }
    Parameter() {
        
    }
    ~ Parameter(){}
    string ToString();
    string GetType();
    string GetValue();
    bool IsConstant();
    string value;
    string type;
};


#endif //LAB2_PARAMETER_H
