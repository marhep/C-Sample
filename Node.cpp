#include "Node.h"

void Node::addNode(int inNumber){
    bool found = false;
    int SetSize = BranchesSet.size();
    for(unsigned int i = 0; i < Branches.size(); ++i){
        if (inNumber == Branches.at(i)) {
            found = true;
        }
    }
    if (found == false){
        BranchesSet.insert(inNumber);
        if ((unsigned) BranchesSet.size() != (unsigned) SetSize){
            UpdateBranches();
        }
    }
}
void Node::UpdateBranches() {
    Branches.clear();
    for (auto t: BranchesSet){
        
        Branches.push_back(t);
    }
}
