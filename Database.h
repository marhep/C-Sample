
#include <vector> 
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "Relation.h"

using namespace std;

class Database: public map<string, Relation>{};