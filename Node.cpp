#include "Node.h"
//nodes pointers are all defined as NodePtr

#include <iostream> 
Node::Node(){
   
}

Node::Node(int row, int col, int distanceToS){

   this->row = row;
   this->col = col;
   this->distanceToS= distanceToS;

}

// Node::~Node()=default; // no need for deletes as no 'new' class was made
Node::~Node(){
   
}
Node::Node(Node& other){
   
   row = other.row;
   col = other.col;
   distanceToS = other.distanceToS;
}
// get functions return the value when called
int Node::getRow(){
   return row;
}

int Node::getCol(){
   return col;
}

int Node::getDistanceToS(){
   return distanceToS; 
}
void Node::setRow(int new_row){
   //sets the new row value
   row = new_row;   


}void Node::setCol(int new_col){
   // sets the new column value
   col = new_col;   

}
void Node::setDistanceToS(int distanceToS){
  //sets the distance from start
   this->distanceToS = distanceToS;   

   
}
//for testsing 
void Node::printVariables(){
   std::cout<<"row: "<<getRow()<<", column: "<<getCol()<<", distance from start: "<< getDistanceToS()<<std::endl;
}

