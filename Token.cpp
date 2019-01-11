#include "Token.h"
using namespace std;
void Token::TokenString() {
    cout <<  "(" << TokenMap.at(type) << ",\"" << value << "\"," << lineNumber << ")" << endl;
}