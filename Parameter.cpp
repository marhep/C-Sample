

#include "Parameter.h"
string Parameter::ToString() {
    return value;
}
string Parameter::GetType() {
    return type;
}
string Parameter::GetValue() {
    return value;
}
bool Parameter::IsConstant(){
    if (value[0] != '\'') {
        return true;
    }
    return false;
}