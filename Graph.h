

#pragma once
#include <vector> 
#include <string>
#include <iostream>
#include <sstream>
#include "Node.h"
#include <stack>
#include <algorithm> 
#include <set>


using namespace std;

class Graph{
    public:
    Graph() {};
    Graph(int numNodes) {
        for (int i = 0; i < numNodes; ++i){
            BuildEmptyTree();
        }
    };
    int Nodenum = 0;
    stack<int> pos_num;
    vector<Node> NodeVec;
    stack<int> tmpNodeInts;
    stack<int> DFSForest();
    void BuildEmptyTree();
    void AddEdge(int source, int edgewith);
    bool FindEdge(int Node1, int Node2);
    Graph Reverse();
    void ToString();
    void NotFound(int inNode);
    void DFS(int inNode);
    void DFSStack(int inNode, set<int>& tmpSet);
    vector<set<int>> SCC();
    int postOrderNum;
    
    
    void Explore(int inNode, stack<int>& SCCStack, set<int>& tmpSet);
    
    
    
};