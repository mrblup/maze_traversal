#include "NodeList.h"
#include <iostream>
#include <string>


#define TEST_VALUE   2 //the 3rd node in the list

NodeList::NodeList(){
   this->nodes = new Node[NODE_LIST_ARRAY_MAX_SIZE];
   
}

NodeList::~NodeList(){
   
   //have to delete all elements list pointers then delete
   clear();
   
}

NodeList::NodeList(NodeList& other){
 //copy constructor
   this->length = other.getLength();
   NodePtr copyNodes = new Node[NODE_LIST_ARRAY_MAX_SIZE];
   for (int i =0; i<other.length;i++){
      Node currentNode = other.nodes[i];
      copyNodes[i] = *new Node(currentNode.getRow(), currentNode.getCol(), currentNode.getDistanceToS());
   }
   this->nodes = copyNodes;
}


int NodeList::getLength(){
   return this->length;
}

NodePtr NodeList::get(int i){
   //get pointer at placement i

   NodePtr getter_node  = new Node;
   *getter_node = this->nodes[i];
   return getter_node; 
}
//returns node where given numbers are equal
NodePtr NodeList::getNode(int node_row , int node_col){
   
   NodePtr getter_node  = new Node;
   for(int i = 0; i<=length; i++){
      int list_row = this->nodes[i].getRow();
      int list_col = this->nodes[i].getCol();
      if ((node_row == list_row) && (node_col == list_col) ){

         getter_node->setRow(this->nodes[i].getRow());
         getter_node->setCol(this->nodes[i].getCol());
         getter_node->setDistanceToS(this->nodes[i].getDistanceToS());
      }
  
   }  
 return getter_node; 
}

void NodeList::addBack(NodePtr newNode){
   // Add a COPY node element to the BACK of the nodelist
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance 
   //    is removed from the list
//
   this->nodes[length] = *newNode;
   ++this->length;
}

bool NodeList::containsNode(NodePtr node){
   // checks the row, column and distance variables of the two nodes and compares them to see if they equal
   Node* checking_node = node;

   int check_row = checking_node->getRow();
   int check_col = checking_node->getCol();
   
   bool check = false;
   for(int i = 0; i<=length; i++){

      int list_row = this->nodes[i].getRow();
      int list_col = this->nodes[i].getCol();
      if ((check_row == list_row) && (check_col == list_col) ){
         check = true;
      }
     

   // 0 if false, 1 if true
   }
   return check;
}
//prints all the nodes in the node list for testing if nodes are added.
void NodeList::printNodes(){
   for(int i = 0; i<this->length; i++){
      std::cout << this->nodes[i].getRow() << ",";
      std::cout << this->nodes[i].getCol() << ",";
      std::cout << this->nodes[i].getDistanceToS() << std::endl;}
}

void NodeList::clear(){

   delete[] nodes;
   this->length =0;

}