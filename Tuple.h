

#pragma once
#include <vector> 
#include <string>
#include <iostream>
#include <sstream>
#include "Header.h"

using namespace std;

class Tuple: public vector<string>{
    public:
    Tuple() {}
    ~Tuple() {}
    string ToString(Header inHeader);
    string ToString();
    
};