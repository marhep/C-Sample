//
// Created by marhep5 on 5/12/2018.
//

#include "DataLogProgram.h"



void DatalogProgram::addFact(Predicate InPred) {
facts.push_back(InPred);
}
void DatalogProgram::addScheme(Predicate InPred){
schemes.push_back(InPred);
}
void DatalogProgram::addRule(Rule InRule) {
rule.push_back(InRule);
    }
void DatalogProgram::addQuery(Predicate InPred) {
query.push_back(InPred);
}
void DatalogProgram::ToString() {
    call all of the other tostrings
    cout << "Success!" << endl;
    cout << "Schemes(" << schemes.size() << "):" << endl;
    for (int i = 0; (unsigned) i < schemes.size(); ++i) {
        cout << "  " << schemes.at(i).ToString() << endl;
    }
    cout << "Facts(" << facts.size() << "):" << endl;
    for (int i = 0; (unsigned) i < facts.size(); ++i) {
        cout << "  " << facts.at(i).ToString() << "." << endl;
    }
    cout << "Rules(" << rule.size() << "):" << endl ;
    for (int i = 0; (unsigned) i < rule.size(); ++i) {
        cout<< "  " << rule.at(i).ToString() << "." << endl;
    }
    cout << "Queries(" << query.size() << "):" << endl;
    for (int i = 0; (unsigned) i < query.size(); ++i) {
        cout<< "  " << query.at(i).ToString() << '?' << endl;
    }
    
}
void DatalogProgram::MakeDomain(set<string> DomainSet) {
    cout << "Domain(" << DomainSet.size() << "):"<<endl;
    for (it=DomainSet.begin(); it!=DomainSet.end(); ++it) {
        cout << "  " << *it << endl;
    }
}
