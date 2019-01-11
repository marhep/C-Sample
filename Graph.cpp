#include "Graph.h"

void Graph::BuildEmptyTree() {
    NodeVec.push_back(Node());
}
void Graph::AddEdge(int source, int edgewith) {
    NodeVec[source].addNode(edgewith);
    
}
bool Graph::FindEdge(int Node1, int Node2) {
    bool found = false;
    for (unsigned int i = 0; i < NodeVec.at(Node1).Branches.size(); i++){
        if (NodeVec.at(Node1).Branches.at(i) == Node2) {
            found = true;
        }
    }
    return found;
}
Graph Graph::Reverse() {
    Graph g(NodeVec.size());
    for (unsigned int i = 0; i < NodeVec.size(); i++){
        g.NodeVec[i].Visited = false;
        int k;
        for (unsigned int j = 0; j < NodeVec.at(i).Branches.size(); j++){
            k = NodeVec.at(i).Branches.at(j);
            
            g.AddEdge(k,i);
        }
    }
    return g;
    
}
void Graph::ToString(){
    cout << "Dependency Graph" <<  endl;
    for (unsigned int i = 0; i < NodeVec.size(); i++){
        cout << "R" << NodeVec.at(i).number << ":";
        for (unsigned int j = 0; j < NodeVec.at(i).Branches.size(); j++){
            
            cout  << "R" <<NodeVec.at(i).Branches.at(j);
            if(j <  NodeVec.at(i).Branches.size() - 1){
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void Graph::NotFound(int inNode){
    NodeVec.at(inNode).Visited = true;
        for (unsigned int j = 0; j < NodeVec.at(inNode).Branches.size(); j++){
            if (!NodeVec[NodeVec[inNode].Branches[j]].Visited){
                NotFound(NodeVec[inNode].Branches[j]);
            }
        }
    NodeVec[inNode].number = Nodenum;
    Nodenum++;
    tmpNodeInts.push(inNode);
}
void Graph::DFS(int inNode) {
    NodeVec[inNode].Visited = true;
    for (unsigned int i = 0; i < NodeVec[inNode].Branches.size(); i++){
        if (!NodeVec[NodeVec[inNode].Branches[i]].Visited){
            
            DFS(NodeVec[inNode].Branches[i]);
        }
    }
    Nodenum++;
    tmpNodeInts.push(inNode);
}
void Graph::DFSStack(int inNode, set<int>& tmpSet) {
    NodeVec[inNode].Visited = true;
    for (unsigned int i = 0; i < NodeVec[inNode].Branches.size(); i++){
        if (!NodeVec[NodeVec[inNode].Branches[i]].Visited){
            DFSStack(NodeVec[inNode].Branches[i], tmpSet);
        }
    }
    tmpSet.insert(inNode);
}
stack<int> Graph::DFSForest() {
    tmpNodeInts.empty();
     Nodenum = 0;
    for (unsigned int i = 0; i < NodeVec.size(); i++){
        if (!NodeVec.at(i).Visited){
            NotFound(i);
        }
    }
    return tmpNodeInts;
}
void Graph::Explore(int inNode, stack<int>& SCCStack, set<int>& tmpSet) {
    NodeVec.at(inNode).Visited = true;
    SCCStack.pop();
    tmpSet.insert(inNode);
    while (SCCStack.size() > 0){
        if (NodeVec.at(SCCStack.top()).Visited == false){
            Explore(SCCStack.top(), SCCStack, tmpSet);
        }
        else {
            SCCStack.pop();
        }
    }
}
vector<set<int>> Graph::SCC(){
    vector<set<int>> SCCSetVec;
    stack<int> SCCStack;
    Graph grev = Reverse();
    SCCStack = grev.DFSForest();
    set<int> FinalSet;
    for (unsigned int i = 0; i < grev.NodeVec.size(); i++){
        grev.NodeVec[i].Visited = false;
        NodeVec[i].Visited = false;
    }
    while(SCCStack.size() > 0) {
        set<int> tmpSet;
        if (!NodeVec.at(SCCStack.top()).Visited){
            DFSStack(SCCStack.top(), tmpSet);
           SCCStack.pop();
            SCCSetVec.push_back(tmpSet);
           while (SCCStack.size() > 0 && NodeVec.at(SCCStack.top()).Visited){
               SCCStack.pop();
            }
        }
    }
    return SCCSetVec;
}
