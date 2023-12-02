
#include "PathPlanner.h"

#include <iostream>

#define IMPOSSIBLE_VALUE  99

#define START_OF_LIST  0
#define DIRECTION_LEFT  -1
#define DIRECTION_UP  -1
#define DIRECTION_DOWN 1  
#define DIRECTION_RIGHT 1   


PathPlanner::PathPlanner(Env env, int rows, int cols){
   this->rows = rows;
   this->cols = cols;
   assignEnv(env);
}
// goes through the given environment and copies over values into classes private environent
void PathPlanner::assignEnv(Env env){
   for( int i = START_OF_LIST; i< ENV_DIM;i++){
      for(int j = START_OF_LIST; j< ENV_DIM;j++){
         this->env[i][j] = (env[i][j]);
      }
   }
   
}

PathPlanner::~PathPlanner(){
    //delete values that was used in path planner
    
}
//sets the initial position of the robot for finding reachable nodes
void PathPlanner::initialPosition(int row, int col){
   
   this->startRow = row;
   this->startCol = col;
}
// //sets the initial position of the robot for finding the path to the start 
void PathPlanner::initialPositionGoal(int row, int col){
   
   this->goalRow = row;
   this->goalCol = col;
}

NodeList* PathPlanner::getReachableNodes(){
   // use double for loop to find initial position
   for(int i = START_OF_LIST; i< rows ; i++){
      for(int j = START_OF_LIST; j<cols; j++){
         if(this->env[i][j]==SYMBOL_START){
            initialPosition(i,j); // sets the position the robot will start at
         }
      }
   }
   //creates two NodeLists
   //this stores all nodes that has been found
   NodeList* openList = new NodeList;
   //this stores all nodes that has been visited by program
   NodeList* closedList = new NodeList;
   // this is the node that will be used to search the environment
   Node* search_node = new Node(startRow, startCol, 0);
   openList->addBack(search_node);
   
   //tracks the current position of the search node in the open list
   int node_pos = START_OF_LIST;
   int length = openList->getLength();

   bool all_visited = false;

   while(all_visited == false){
      length = openList->getLength();
      //when node_pos hits the end of openList, 
      //then this becomes the last loop and closed list will have all nodes  from closed list
      if (node_pos >= length){ 
         all_visited = true;
      }
      // changes the searching node to the openlists node at node_pos
      search_node = openList->get(node_pos);
   //search up by getting the row -1 and column of the searching node, and checking that position 
   //in the ENV to see if it is either empty or the goal
     if( ((env[search_node->getRow()+DIRECTION_UP][search_node->getCol()] ==SYMBOL_EMPTY)
      ||(env[search_node->getRow()+DIRECTION_UP][search_node->getCol()] ==SYMBOL_GOAL ))
      ){
         //creates a new node with row-1, col and the distance of the current search node +1
         Node* new_node = new Node(search_node->getRow()+DIRECTION_UP, search_node->getCol(), search_node->getDistanceToS()+1);
         // checks to see if the open list does not contain the node
            if(openList->containsNode(new_node) == false){
               // adds node into open list if not already in list
               openList->addBack(new_node);
               delete new_node;
               }
               
            }
      //search right by getting the row  and column+1 of the searching node
      if( ((env[search_node->getRow()][search_node->getCol()+DIRECTION_RIGHT] ==SYMBOL_EMPTY )
      ||(env[search_node->getRow()][search_node->getCol()+DIRECTION_RIGHT] ==SYMBOL_GOAL ))
        ){
            Node* new_node = new Node(search_node->getRow(), search_node->getCol()+DIRECTION_RIGHT, search_node->getDistanceToS()+1);
            if(openList->containsNode(new_node)== false){
               openList->addBack(new_node);
               delete new_node;
               }
            }
     //search down by getting the row+1  and column of the searching node
      if( ((env[search_node->getRow()+DIRECTION_DOWN][search_node->getCol()] ==SYMBOL_EMPTY )
      ||(env[search_node->getRow()+DIRECTION_DOWN][search_node->getCol()] ==SYMBOL_GOAL ))
      ){
            Node* new_node = new Node(search_node->getRow()+DIRECTION_DOWN, search_node->getCol(), search_node->getDistanceToS()+1);
            if(openList->containsNode(new_node) == false){
               openList->addBack(new_node);
               delete new_node;
               }

            }
      //search left by getting the row  and column-1 of the searching node
      if(( (env[search_node->getRow()][search_node->getCol()+DIRECTION_LEFT] ==SYMBOL_EMPTY)
      ||(env[search_node->getRow()][search_node->getCol()+DIRECTION_LEFT] ==SYMBOL_GOAL ))
      ){
         Node* new_node = new Node(search_node->getRow(), search_node->getCol()+DIRECTION_LEFT, search_node->getDistanceToS()+1);
            if(openList->containsNode(new_node) == false){
               openList->addBack(new_node);
               delete new_node;
               }
 
            }
      // checks to see if the current search node is in the closed list
       if(closedList->containsNode(search_node) == false ){
          //if not in closed list, it get added
         closedList->addBack(search_node);
         }
      // increments the node_pos
      node_pos = node_pos+1;
      //changes search node to the next in the open list
      search_node = openList->get(node_pos+1);
      }
      
      delete openList;
   return closedList;
}



NodeList* PathPlanner::getPath(){
// gets the path from goal to start by searching through the avalaible nodes
   for(int i = START_OF_LIST; i< rows ; i++){
      for(int j = START_OF_LIST; j<cols; j++){
         if(this->env[i][j]==SYMBOL_GOAL){
            initialPositionGoal(i,j);
         }
      }
   }
   //the openList
   NodeList* allNodes = new NodeList;
   allNodes= getReachableNodes();
   //can only be called after reachable nodes has been found
   Node* start_node = new Node(startRow, startCol, 0);

   // stores the path from GOAL to START
   NodeList* currentPath = new NodeList;
   // the searching node that will iterate through allnodes
   Node* search_node = new Node();

   //starts at GOAl
   search_node = allNodes->getNode(goalRow, goalCol); 
   
   //stores nodes in directions around nodes.
   Node* upNode = new Node();
   Node* rightNode = new Node();
   Node* downNode = new Node();
   Node* leftNode = new Node();

   //adds search_node to path
   currentPath->addBack(search_node);

   // for checking if the path is completed
   int length = currentPath->getLength();
   int node_pos = START_OF_LIST;
   bool path_complete = false;

   while(path_complete == false){

      //the up node: has the coordinates of node above the search node, program will check if it is valid and in the list
      if((env[search_node->getRow()+DIRECTION_UP][search_node->getCol()] ==SYMBOL_EMPTY)
         ||(env[search_node->getRow()+DIRECTION_UP][search_node->getCol()] ==SYMBOL_START )){
            //stores the values into directional node
         upNode = allNodes->getNode(search_node->getRow()+DIRECTION_UP,search_node->getCol());
         }

      //the right node: has co-ords of node to the right of search node
      if((env[search_node->getRow()][search_node->getCol()+DIRECTION_RIGHT] ==SYMBOL_EMPTY)
         ||(env[search_node->getRow()][search_node->getCol()+DIRECTION_RIGHT] ==SYMBOL_START )){
         rightNode = allNodes->getNode(search_node->getRow(),search_node->getCol()+DIRECTION_RIGHT);
         }

      //the down node: has co-ords of node below
      if((env[search_node->getRow()+DIRECTION_DOWN][search_node->getCol()] ==SYMBOL_EMPTY)
         ||(env[search_node->getRow()+DIRECTION_DOWN][search_node->getCol()] ==SYMBOL_START )){
         downNode = allNodes->getNode(search_node->getRow()+DIRECTION_DOWN,search_node->getCol());
         }

      //the left node: has co-ords to the left      
      if((env[search_node->getRow()][search_node->getCol()+DIRECTION_LEFT] ==SYMBOL_EMPTY)
         ||(env[search_node->getRow()][search_node->getCol()+DIRECTION_LEFT] ==SYMBOL_START )){
         leftNode = allNodes->getNode(search_node->getRow(),search_node->getCol()+DIRECTION_LEFT);
         }
      

      // checks if directional node is in the openList,
      // if the distance of directional node is oneless than curent ndoe
      // and if the directional node is not in the path
      if((allNodes->containsNode(upNode) == true)
      &&(upNode->getDistanceToS() == (search_node->getDistanceToS() -1))
      &&(currentPath->containsNode(upNode) == false)){
         // adds the directional node into the path
         currentPath->addBack(upNode);
         // changes the searching node into the directional node
         search_node = upNode;
      
      }
      else if((allNodes->containsNode(rightNode) == true)
      &&(rightNode->getDistanceToS() == (search_node->getDistanceToS() -1))
      &&(currentPath->containsNode(rightNode) == false)){
         currentPath->addBack(rightNode);
         search_node = rightNode;
      }
      else if((allNodes->containsNode(downNode) == true)
      &&(downNode->getDistanceToS() == (search_node->getDistanceToS() -1))
      &&(currentPath->containsNode(downNode) == false)){
         currentPath->addBack(downNode);
         search_node = downNode;
      }
      else if((allNodes->containsNode(leftNode) == true)
      &&(leftNode->getDistanceToS() == (search_node->getDistanceToS() -1))
      &&(currentPath->containsNode(leftNode) == false)){
         currentPath->addBack(leftNode);
         search_node = leftNode;
      }
      // increments the node_pos and stops the loop if it is greater than the length of path list
      node_pos++;
      length = currentPath->getLength();
         if (node_pos >= length){ 
            path_complete = true;
         }
   }
   // returnedPath is the list that will be returned
   NodeList* returnedPath = new NodeList();
   // itterates from end of currentPath and stores the current node into returned path to return the reversed path
   for (int path_length = currentPath->getLength() -1; path_length >=START_OF_LIST; path_length = path_length -1){
      Node* addingNode = new Node(currentPath->get(path_length)->getRow(),currentPath->get(path_length)->getCol(),currentPath->get(path_length)->getDistanceToS());
      returnedPath->addBack(addingNode);
      delete addingNode;
   }
   
   
   //prints path for testing
   // std::cout<<"nodes that are in the path: "<<std::endl;
   // currentPath->printNodes();

   delete upNode;
   delete rightNode;
   delete downNode;
   delete leftNode;
   delete start_node;
   delete allNodes;
   delete currentPath;
   
return returnedPath;
}

