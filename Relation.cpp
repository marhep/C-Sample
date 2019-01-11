    #include "Relation.h"
    
    void Relation::ToString(){

        for (Tuple tuple: Tuples) {
            
            cout << tuple.ToString(RelHeader);
            if (tuple.ToString(RelHeader) != "") {
            cout<< endl;
        }
        }
    }
    
    Relation Relation::Select(string inString, int ColNum){
        Relation r(Name, RelHeader);
        for(Tuple myTuple : Tuples) { 
            if(myTuple.at(ColNum) == inString){
                r.addTuple(myTuple);
            }
        }
        return r;
        
        
    }
    Relation Relation::Select(int dupColNum1, int dupColNum2){
    Relation r(Name, RelHeader);
    
    
    if (dupColNum1 != dupColNum2){
        for(Tuple myTuple : Tuples) { 
            if(myTuple.at(dupColNum1) == myTuple.at(dupColNum2)){
                r.addTuple(myTuple);
            }
        }
    }
        return r;
    }
    Relation Relation::Project(vector<int> Headerintvec){
        Header h;
        
            for (unsigned int i = 0; i < Headerintvec.size(); ++i) {
                h.push_back(RelHeader.at(Headerintvec.at(i)));
                
            }
            
            Relation r(Name, h);
            Tuple t;
            for(Tuple myTuple : Tuples) { 
                for (unsigned int i = 0; i < Headerintvec.size(); ++i){
                   t.push_back(myTuple.at(Headerintvec.at(i)));
                   
                }
                
                r.addTuple(t);
                t.clear();
            }
        return r;
    }
   
    void Relation::Rename(Header newHeader){
        RelHeader = newHeader;
        
    }
    void Relation::addTuple(Tuple inTuple) {
        Tuples.insert(inTuple);
        ++NumTuples;
        
    }
    
Relation Relation::ProjectwithParams(vector<Parameter>& paramVector){
    
    vector<int> keepInts;
    set<string> nodups;
    int prev;
   
    for (unsigned int i = 0; i < paramVector.size(); ++i){
        
        for (unsigned int j = 0; j < RelHeader.size(); ++j){
           
            if(paramVector.at(i).value == RelHeader.at(j)){
                prev = nodups.size();
                nodups.insert(paramVector.at(i).value);
                if ((unsigned) nodups.size() != (unsigned) prev) {
                    keepInts.push_back(j);
                    
                }
                
            }
        }
    }
    return Project(keepInts);
     
    
}
Relation Relation::Unionite(Relation& RelUnion) {
    Tuple t;
            for(Tuple myTuple : Tuples) { 
                RelUnion.Tuples.insert(myTuple);
                   
            }
    return RelUnion;        
    
}
Relation Relation::joinRelations(Relation& r1, Relation& r2){
    Header h;
    
    Tuple t;
  
    h = joinHeaders(r1.RelHeader, r2.RelHeader);
     Relation r(Name, h);
    
    for(Tuple myTuple : r1.Tuples) { 
        
        Tuple t1 = myTuple;
        for(Tuple myTuple2 : r2.Tuples) {
            Tuple t2 = myTuple2;
            
            if (joinable(r1.RelHeader, r2.RelHeader, t1, t2)) {
          
                t = joinTuples(r1.RelHeader, r2.RelHeader, t1, t2);
                r.Tuples.insert(t);
                
            }
        }
    }
    
    return r;
    
}
Header Relation::joinHeaders(Header h1, Header h2){
    bool adding;
    
    for (unsigned int i = 0; i < h2.size(); ++i) {
        adding= true;
        for(unsigned int j = 0; j < h1.size(); ++j){
            if (h2.at(i) == h1.at(j)){
                adding = false;
                break;
            }
        }
        if (adding == true) {
            h1.push_back(h2.at(i));
        }
    }
    
  return h1;  
}

Tuple Relation::joinTuples(Header& h1, Header& h2, Tuple& t1, Tuple& t2) {
    bool adding;
    Tuple t;
    
    for (unsigned int i = 0; i < t1.size(); ++i) {
        t.push_back(t1.at(i));
    }
    
    for (unsigned int i = 0; i < t2.size(); ++i) {
        adding = true;
        for (unsigned int j = 0; j < h1.size(); ++j) {
            
            if (h1.at(j) == h2.at(i)) {
                
                adding = false;
                break;
            }
        }
        if (adding == true) {
            t.push_back(t2.at(i));
            
        
        }
    }
return t;
}

bool Relation::joinable(Header& h1, Header& h2, Tuple& t1, Tuple& t2){
    
	    for(unsigned int i = 0; i < h1.size(); ++i){
	        for(unsigned int j = 0; j < h2.size(); ++j) {
	            if((h1.at(i) == h2.at(j)) && (t1.at(i) != t2.at(j))){
	                
	                return false;
	            }
	        }
	    }
	    return true;
}