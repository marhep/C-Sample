//
// Created by marhep5 on 5/14/2018.
//

#include "Parser.h"

void Parser::Parse(){
    try{
        
        ParseDataLogProgram();
    }
    catch (Token error) {
        //it goes no matter what
        cout << "Failure!" << endl << "  ";
        error.TokenString();

    };
    
}
Predicate Parser::ParseHeadPredicate(){
    
    string id = tokenVec[index].value;
        Match(ID);
        Match(LEFT_PAREN);
        string value = tokenVec[index].value;
        string Paramtype = to_string(tokenVec[index].type);
        
        Match(ID);
        Parameter ParameterforVec(value, Paramtype);
        vector<Parameter> paramVec; 
        paramVec.push_back(ParameterforVec);
        ParseIDList(paramVec);
        Predicate Pred(id, paramVec);
        Match(RIGHT_PAREN);    
        return Pred;
}
void Parser::ParseIDList(vector<Parameter> &paramVec) {
    if (tokenVec[index].type == COMMA) {
    Match(COMMA);
    string value = tokenVec[index].value;
    string Paramtype = to_string(tokenVec[index].type);
    Match(ID);
    Parameter ParameterforVec(value, Paramtype);
    paramVec.push_back(ParameterforVec);
    ParseIDList(paramVec);
    }
}



void Parser::ParseFactList() {
    
if (tokenVec[index].type == ID) {
    string value = tokenVec[index].value;

    
   Predicate Pred = ParseFact(value);
  DLP.addFact(Pred);
    ParseFactList();
    
  
}

}
Predicate Parser::ParseFact(string value) {
        string id = tokenVec[index].value;
        Match(ID);
        Match(LEFT_PAREN);
        vector<string> StringVec;
        string Instring = tokenVec[index].value;
        StringVec.push_back(Instring);
        string Type = to_string(tokenVec[index].type);
        Match(STRING);
        vector<Parameter> ParamVector;
        ParseStringList(StringVec);
        for (int i = 0; (unsigned) i < StringVec.size(); ++i) {
            Parameter Param(StringVec.at(i), Type);
            DomainSet.insert(StringVec.at(i));
            ParamVector.push_back(Param);
        }
        vector<Parameter> temp = ParamVector;
      
        
        Predicate Pred(value, ParamVector);
        

        Match(RIGHT_PAREN);
        Match(PERIOD);
        
        return Pred;
        
    
}
void Parser::Match(TokenType inType) {
    Token error= tokenVec[index];
     if (tokenVec[index].type == inType) {
        index++;
        throw tokenVec[index];
    } else {
        throw tokenVec[index];
    }
}

void Parser::ParseStringList(vector<string>& StringVec) {
    if(tokenVec[index].type == COMMA) {
        Match(COMMA);
        string Instring = tokenVec[index].value;
        StringVec.push_back(Instring);
        
        Match(STRING);
        ParseStringList(StringVec);
    }
}
void Parser::ParseSchemeList() {
    if(tokenVec[index].type == ID) {
        ParseScheme();
        ParseSchemeList();
    }


}

void Parser::ParseQueryList(vector<Predicate>& PredVec) {
    if(tokenVec[index].type == ID) {
        Predicate InPred = ParseQuery();
        PredVec.push_back(InPred);
        ParseQueryList(PredVec);
    }
}
void Parser::ParsePredicateList(vector<Predicate>& PredVec) {
    if (tokenVec[index].type == COMMA) {
        Match(COMMA);
         Predicate InPred = ParsePredicate();
         PredVec.push_back(InPred);
         ParsePredicateList(PredVec);

    
    }
}
Predicate Parser::ParsePredicate() {
    //match ID and hold onto its value
        string PredID = tokenVec[index].value;
        Match(ID);
        Match(LEFT_PAREN);
        string Param = ParseParameter();
        string Paramtype = to_string(tokenVec[index].type);
        Parameter ParamtoVec(Param, Paramtype);
        vector<Parameter> paramVec;
        
        
        paramVec.push_back(ParamtoVec);
        ParseParameterList(paramVec);
        Predicate PredObj(PredID, paramVec);
        Match(RIGHT_PAREN);
        
    return PredObj;
}


void Parser::ParseParameterList(vector<Parameter> &paramVec) {
    if(tokenVec[index].type == COMMA) {
        Match(COMMA);
        string Param = ParseParameter();
        string Paramtype = to_string(tokenVec[index].type);
        Parameter ParamtoVec(Param, Paramtype);
        paramVec.push_back(ParamtoVec);
        ParseParameterList(paramVec);
    }
}
string Parser::ParseParameter() {
    string value;
    if (tokenVec[index].type == STRING) {
        value = tokenVec[index].value;
        Match(STRING);
        return value;
    }
    else if (tokenVec[index].type == ID) {
        value = tokenVec[index].value;
        Match(ID);
        return value;
    }
    else if (tokenVec[index].type == LEFT_PAREN) {
        return ParseExpression();
    }
    else {
        return "";
    }
}

Predicate Parser::ParseQuery() {
    
        Predicate PredicateReturn = ParsePredicate();
        DLP.addQuery(PredicateReturn);
        Match(Q_MARK);
        return PredicateReturn;
    
}

void Parser::ParseDataLogProgram() {

        Match(SCHEMES);
        Match(COLON);
        ParseScheme();
        ParseSchemeList();

        Match(FACTS);
        Match(COLON);
        ParseFactList();

        Match(RULES);
        Match(COLON);
        ParseRuleList();
    
        Match(QUERIES);
        Match(COLON);
        Predicate InPred = ParseQuery();
        vector<Predicate> predVec; 
        predVec.push_back(InPred);
        ParseQueryList(predVec);
        
        if(tokenVec[index].value != "") {
            throw tokenVec[index];
        }
        DLP.ToString();
        DLP.MakeDomain(DomainSet);
        
        
}
void Parser::ParseScheme() {
    
        
        Predicate OutPred = ParseHeadPredicate();
        
        DLP.addScheme(OutPred);
    
}
void Parser::ParseRuleList() {
    if (tokenVec[index].type == ID) {
        ParseRule();
        ParseRuleList();
    }

}
void Parser::ParseRule() {
    
        Predicate HeadPred = ParseHeadPredicate();
        Match(COLON_DASH);
        Predicate InPred = ParsePredicate();
        vector<Predicate> RuleVec;
        RuleVec.push_back(InPred);
        
        ParsePredicateList(RuleVec);
        
        Match(PERIOD);
        
        Rule RuleObj(HeadPred, RuleVec);
    
        DLP.addRule(RuleObj);
}
string Parser::ParseOperator() {
    if (tokenVec[index].type == ADD) {
        Match(ADD);
        return "+";
    }
    else if (tokenVec[index].type == MULTIPLY) {
        Match(MULTIPLY);
        return "*";
    }
    else {
        throw tokenVec[index];
    }
}
string Parser::ParseExpression() {
        stringstream ss;
        Match(LEFT_PAREN);
        ss << "(" <<ParseParameter();
        ss <<ParseOperator();
        ss << ParseParameter();
        ss << ")";
        Match(RIGHT_PAREN);
    return ss.str();

}
bool Parser::IsConstant() {
    return true;
}


