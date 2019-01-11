#include "Interpreter.h"
void Interpreter::MakeDatabase() {
    string RelationName;
    for (unsigned int i = 0; i < schemes.size(); ++i) {
        RelationName = schemes.at(i).id;
        
        Header h;
        for (unsigned int j = 0; j < schemes.at(i).paramVec.size(); ++j) {
            h.push_back(schemes.at(i).paramVec.at(j).value);
        }
        Relation r = Relation(RelationName, h);
        DB.insert(pair<string, Relation> (RelationName, r));
    }
    for (unsigned int i = 0; i < facts.size(); ++i) {
        Tuple t;
        for (unsigned int j = 0; j < facts.at(i).paramVec.size(); ++j) {
            t.push_back(facts.at(i).paramVec.at(j).value);

        }
        DB[facts.at(i).id].addTuple(t);
    }
    EvaluateAllQueries();
       
}
Relation  Interpreter::EvaluateOneQuery(string RelID, vector<string> ParamVec, vector<string> foundString, vector<int> foundStringColNum, vector<int> dupVec, bool isRule){
   Relation r = DB[RelID];
    Header tmpNewHeader;
   Header oldHeader;
   oldHeader = DB[RelID].RelHeader;
   vector<int> Headerintvec;
   Header newHeader;
   for (unsigned int i = 0; i < ParamVec.size(); ++i) {
       if (ParamVec.at(i).substr(0,1) != "\'") {
           newHeader.push_back(ParamVec.at(i));
           Headerintvec.push_back(i);
       }

   }
   if (!dupVec.empty()){
       for (unsigned int i = 0; i < dupVec.size() - 1; i= i + 2) {
           r= r.Select(dupVec.at(i),dupVec.at(i+1));
       }
       FindWantedCols(newHeader, Headerintvec);
   }
   if (foundString.size() > 0){
       for (unsigned int i = 0; i < foundString.size(); ++i) {
          r= r.Select(foundString.at(i), foundStringColNum.at(i));
       }
   }
   r = r.Project(Headerintvec);
   r.Rename(newHeader);
   if (isRule == false) {
    Print(r);
   }
   return r;
 }
void Interpreter::Print(Relation r) {
    if (r.Tuples.size() > 0) {
       cout << "Yes(" << r.Tuples.size() << ")" << endl;
       r.ToString();
   }
    else {
        cout << "No" << endl;
    } 
 }
void Interpreter::OptimizeRule(Graph& g, Graph& ReverseGraph){
    int source = -1;
    int edgewith = -1;
    for (unsigned int j = 0; j < rule.size(); ++j){
        
    for (unsigned int i = 0; i < rule.at(j).PredVec.size(); ++i){
        
            int iterator = 0;
            
            for (unsigned int k = 0; k < RuleIDvec.size(); ++k){
                  source = j; 
               if (RuleIDvec[k] == rule[j].PredVec[i].id) {   
                  edgewith = iterator;
                  
                  g.AddEdge(source, edgewith);
              }
              iterator++;
            }
            
        }
    }
}
void Interpreter::EvalRule(int &index, set<int>& SCCVec){
     Header InparamVec;
     vector<string> foundString;
     vector<int> foundStringColNum;
     vector<string> renameCols;
    string RelID;
    string Name;
    Relation r;
    Relation r2;
    Relation finalR;
    bool AnotherRound = false;
    int prevRelSize = 0;
    int Iter = 0;

    Header insertHeader;
     vector<Parameter> dupchecker;
    
        for(int t: SCCVec){
            
            insertHeader.clear();
             
            Name = rule[t].HeadPredicate.id;
            
            
            cout << rule[t].ToString() << "." << endl;
            
            
            r = EvalRulePt2(t);
            
            for (unsigned int i = 0; i < schemes.size(); ++i){
                if (Name == schemes.at(i).id){
                    for (unsigned int l = 0; l < schemes.at(i).paramVec.size(); ++l) {
                        insertHeader.push_back(schemes.at(i).paramVec.at(l).value);
                    }
                }
            }
            r.Rename(insertHeader);
            prevRelSize = DB[Name].Tuples.size();
            for(Tuple myTuple : r.Tuples) {
                if(DB[Name].Tuples.count(myTuple) == 0){
                    DB[Name].addTuple(myTuple);
                    cout << myTuple.ToString(insertHeader) << endl;
                }
            }
            if ((unsigned) prevRelSize != (unsigned) DB[Name].Tuples.size()){
                AnotherRound = true;
            }
        }
        PossibleAnotherRound(AnotherRound, index, SCCVec);
        Iter++;
}
void Interpreter::SingleSCC(int i){
    Relation r;
    cout << rule[i].ToString() << "." << endl;
    string Name = rule[i].HeadPredicate.id;
    Header insertHeader = r.RelHeader;
            r = EvalRulePt2(i);
            for (unsigned int i = 0; i < schemes.size(); ++i){
                if (Name == schemes.at(i).id){
                    for (unsigned int l = 0; l < schemes.at(i).paramVec.size(); ++l) {
                        insertHeader.push_back(schemes.at(i).paramVec.at(l).value);
                    }
                }
            }
            for(Tuple myTuple : r.Tuples) {
                
                if(DB[Name].Tuples.count(myTuple) == 0){
                    DB[Name].addTuple(myTuple);
                    cout << myTuple.ToString(insertHeader) << endl;
                }
            }
}



void Interpreter::PossibleAnotherRound(bool AnotherRound, int &index, set<int>& SCCVec) {
    if (AnotherRound == true) {
        ++index;
        EvalRule(index, SCCVec);
        
    }
}       
Relation Interpreter::EvalRulePt2(int index){ 
    bool isRule = true;
     Header InparamVec;
     vector<string> foundString;
     vector<int> foundStringColNum;
     vector<string> renameCols;
    string RelID;
    string Name;
    Relation r;
    Relation r2;
    Relation finalR;
    Header insertHeader;
         for(unsigned int j = 0; j < rule.at(index).PredVec.size(); ++j) {
             RelID = rule.at(index).PredVec.at(j).id;
             for (unsigned int k = 0; k < rule.at(index).PredVec.at(j).paramVec.size(); ++k) {
                 InparamVec.push_back(rule.at(index).PredVec.at(j).paramVec.at(k).value);
                 if (rule.at(index).PredVec.at(j).paramVec.at(k).value.substr(0,1) == "\'") {
                    foundString.push_back(rule.at(index).PredVec.at(j).paramVec.at(k).value);
                    foundStringColNum.push_back(k);
                 }
             }
             if (j == 0) {
                  r = EvaluateOneQuery(RelID, InparamVec, foundString, foundStringColNum, dupVec, isRule);
             }
             else {
                 r2 = EvaluateOneQuery(RelID, InparamVec, foundString, foundStringColNum, dupVec, isRule);
                 r = r.joinRelations(r, r2);
             }
            InparamVec.clear();  
            foundString.clear();
            foundStringColNum.clear();
         }
        r = r.ProjectwithParams(rule.at(index).HeadPredicate.paramVec);
return r;
}

void Interpreter::EvaluateAllQueries() {
    bool isRule = false;
     string inString;
     Header newHeader;
     vector<string> foundString;
     vector<int> foundStringColNum;
     vector<string> renameCols;
    string RelID;
     vector<Parameter> dupchecker;
    EvaluateAllRules();
	cout << endl << "Query Evaluation" << endl;
        dupVec.clear();
     for (unsigned int i = 0; i < query.size(); ++i) {
         cout << query.at(i).ToString() << "? ";
         RelID = query.at(i).id;
         vector<Parameter> dupChecker;
        for (unsigned int j = 0; j < query.at(i).paramVec.size(); ++j) {
            if (query.at(i).paramVec.at(j).value.substr(0,1) == "\'") {
                foundString.push_back(query.at(i).paramVec.at(j).value);
                foundStringColNum.push_back(j);
             
            }
                newHeader.push_back(query.at(i).paramVec.at(j).value);
                LookForDups(query.at(i), j);
                
        }

        EvaluateOneQuery(RelID, newHeader, foundString, foundStringColNum, dupVec, isRule);
        newHeader.clear();  
        foundString.clear();
        foundStringColNum.clear();
        dupVec.clear();
     }
 }
void Interpreter::LookForDups(Predicate query, int j) {
    
    
    
    for (unsigned int k = j; k < query.paramVec.size(); ++k) {
              if ((query.paramVec.at(k).value== query.paramVec.at(j).value)
              && (query.paramVec.at(k).value.substr(0,1) != "\'") 
              && (query.paramVec.at(j).value.substr(0,1) != "\'")
              && (unsigned) j < (unsigned) k
              ) {
                    dupVec.push_back(j);
                    dupVec.push_back(k);
                }
            }
}
 void Interpreter::FindWantedCols(Header &newHeader, vector<int> &vecIndex) {
      set<string> nodups;
      int prev;
      vector<int> newIndex;
      Header theHeader;
      for (unsigned int i = 0; i < newHeader.size(); ++i){
          prev = nodups.size();
          nodups.insert(newHeader.at(i));
          if ((unsigned) nodups.size() != (unsigned) prev){
              theHeader.push_back(newHeader.at(i));
              newIndex.push_back(vecIndex.at(i));
          }
      }
      newHeader = theHeader;
      vecIndex = newIndex;
  }
void Interpreter::Optimization(Graph& g,  Graph& ReverseGraph){
    RuleIDs.clear();
     RuleIDvec.clear();
    for (unsigned int i = 0; i < rule.size(); ++i){
        g.NodeVec[i].number = i;
        RuleIDs.insert(rule.at(i).HeadPredicate.id);
        RuleIDvec.push_back(rule.at(i).HeadPredicate.id);
    }
    OptimizeRule(g, ReverseGraph);
    g.ToString();
}
bool Interpreter::Looping(set<int> t){
    for(unsigned int j: t){
        for(unsigned int i = 0; i < rule[j].PredVec.size(); i++){
            if (rule[j].HeadPredicate.id == rule[j].PredVec[i].id){
                return true;
            
            }
        }   
    }
    return false;
}

void Interpreter::EvaluateAllRules() {
    Graph ReverseGraph(rule.size());
    Graph g(rule.size());
    Optimization(g, ReverseGraph);
    cout << "Rule Evaluation" << endl;
    vector<set<int>> SCCSetVec = g.SCC();
    int index = 1;
    for (unsigned int i = 0; i < SCCSetVec.size(); ++i){
        cout << "SCC: ";
        PrintSCC(SCCSetVec[i]);
        index = 1;
        if (SCCSetVec.at(i).size() > 1 || Looping(SCCSetVec.at(i))){
            EvalRule(index, SCCSetVec.at(i));
            cout << index << " passes: ";
        }
        else{
            for (auto t: SCCSetVec.at(i)){
                SingleSCC(t);   
            }
            cout << index << " passes: ";
        }
        PrintSCC(SCCSetVec[i]);
    }
}
void Interpreter::PrintSCC(set<int>& SCCSet){
    int iterator= 0;
        for (auto t: SCCSet){
            cout << "R" << t;
            if ((unsigned) iterator < (unsigned) SCCSet.size() - 1){
                cout << ",";
            }
            else {
                cout << endl;
            }
            ++iterator;
        } 
}