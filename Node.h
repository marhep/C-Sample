

#pragma once
#include <vector> 
#include <string>
#include <iostream>
#include <sstream>
#include <set>


using namespace std;

class Node{
   public:
   Node() {
       Visited = false;
       number = -1; //hasn't been visited yet
   }
   bool Visited;
 vector<int>Branches;
 int number;
   set<int> BranchesSet;
   void addNode(int inNumber);
   void UpdateBranches();
 
};