/*
	the approach that was taken for this impletation of this project, was to read in lines of text via the Standard input
	and read in each the characters from each line into a 2d array. after i checked for all of the reachable nodes in the array using the algorithm 
	given in the specifications, and found the path from the Starting node to the Goal node and stored it into a node list.  
	After finding the path, i changed all the nodes in the 2d array into arrows based on the nodes in the node list and printed it out.
	issues that arised in this assessment was dealing with memory management.
*/
#include <iostream>
#include <fstream>

#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
//
#define ENV_FILE_ARG_ARRAY_NUMBER  1
#define START_OF_LIST  0
//the characters that replace empty spaces in the env when running getReachableNodes or getPath 
#define SYMBOL_REACHABLE 'O'
#define SYMBOL_UP '^'
#define SYMBOL_RIGHT '>'
#define SYMBOL_DOWN 'V'
#define SYBMOL_LEFT '<'

//
//valgrind --leak-check=full -v ./your_program  , for checking memory leaks

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
// env is a character array
void readEnvStdin(Env env);

void readEnvTerminal(Env env, int argc, char** argv);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);

void printReachablePositions(Env env, NodeList* reachable);

// for testing environment input
void printEnv(Env env);

int main(int argc, char** argv){

    //testing code
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl ;
    // Load Environment 

    Env env;
    
    readEnvStdin(env); // run code via '<./tests/file_name's

   
    //for testing env via ifstream
    //readEnvTerminal(env,argc, argv); reads file through the standard input
    //printEnv(env);
    //std::cout<<env<<std::endl;

    // Solve using forwardSearch
    

    
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);

    //testing reachableNodes method

    //Env reachable;
    //  std::copy(&env[0][0], &env[0][0]+20*20,&reachable[0][0]);
    // visualises all nodes that can be reached
    // NodeList* reachablePositions = nullptr;
    // reachablePositions = pathplanner->getReachableNodes();
    // printReachablePositions(reachable, reachablePositions);
    // printEnv(reachable);
    // delete reachablePositions;//
    
    
    NodeList* solution = pathplanner->getPath();
    
    //print the path
    printPath(env, solution);

    // //cleans up memory
    delete pathplanner;
    
    delete solution;
    
}

// reads the maze in line by line, when one line is read it, it takes tha character array and places each character in corrosponding ENV slot
void readEnvStdin(Env env){
    int row_num = START_OF_LIST;
    std::string line = "";
    while(row_num<ENV_DIM){
        line = "";
        std::getline(std::cin, line);

        for( int col_num = START_OF_LIST; col_num<ENV_DIM; col_num++){
            env[row_num][col_num] = line[col_num];
        }
        row_num++;

    }

}

// code for reading in environment via the commandline
void readEnvTerminal(Env env, int argc, char** argv){
    std::string test_file_input = ""; // initialises a string to read in file
    std::string arg_test = argv[ENV_FILE_ARG_ARRAY_NUMBER]; // from terminal, user enters in file they want, and it is stored at argv[1]
    test_file_input = "./tests/"+arg_test ;  // prepares the string 
    std::cout<< test_file_input<<std::endl; 
    std::ifstream fileToRead(test_file_input); // reads in file
    int row_number = START_OF_LIST; 
    if (fileToRead.is_open()) {
		std::string line = "";
		while (!fileToRead.eof()) {
            //gets line, need to change to character or just seperate into characters
			std::getline(fileToRead, line);
            //prints out the file for testing

            for( int column_number = START_OF_LIST; column_number<ENV_DIM; column_number++){
                env[row_number][column_number] = line[column_number];
            }
            row_number++;
		}
	}
	else {
		std::cout << "\n    File Not Found. \n";
	}
	fileToRead.close();
}
// prints the environment
void printEnv(Env env){
        for (int i = START_OF_LIST; i < ENV_DIM; ++i){
            for (int j = START_OF_LIST; j < ENV_DIM; ++j){
                std::cout << env[i][j] ;
             }
            std::cout << std::endl;
        }
}
// replaces all positions the robot can reach with the 'SYMBOL_REACHABLE' character
void printReachablePositions(Env env, NodeList* reachable){
    int length = reachable->getLength();
    Node* currentNode = new Node();
    for(int i = START_OF_LIST; i< length; i++){
        currentNode = reachable->get(i);
        env[currentNode->getRow()][currentNode->getCol()] = SYMBOL_REACHABLE;
    }
}

// prints the paths retrieved from the getPath method, itterates through the nodelist retrieved and replaces characters directions
void printPath(Env env, NodeList* solution) {

    int length = solution->getLength();
    Node* currentNode = new Node();
    Node* nextNode = new Node;
    for (int i = 1; i< length-1; i++){
        currentNode = solution->get(i);
        nextNode = solution->get(i+1);
        //check up
        if(currentNode->getRow() == nextNode->getRow()-1){
            //change i in env to new character
            env[currentNode->getRow()][currentNode->getCol()] = SYMBOL_DOWN;
        }
        //check left
        else if(currentNode->getCol() == nextNode->getCol()+1){
            env[currentNode->getRow()][currentNode->getCol()] = SYBMOL_LEFT;
        }
        //check down
        else if(currentNode->getRow() == nextNode->getRow()+1){
            env[currentNode->getRow()][currentNode->getCol()] = SYMBOL_UP;
        }
        //check right
        else{
            env[currentNode->getRow()][currentNode->getCol()] = SYMBOL_RIGHT;

        }
        
    }
    printEnv(env);
}


void testNode() {
    std::cout << "TESTING Node" << std::endl;
    
    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    std::cout<<"node created"<<std::endl;
    nodeList->addBack(b1);
    std::cout<<"added"<<std::endl;
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
    
    //gets node at start of list
    std::cout<<"pointer at position 0 is: " <<nodeList->get(0)<<std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    nodeList->getLength();
    // gets node at 2nd position
    std::cout<<"pointer row at position 1 is: " <<nodeList->get(1)<<std::endl;
    Node* b3 = new Node(2, 2, 2);
    nodeList->addBack(b3);
    nodeList->getLength();

    

    //testing get functions for nodes in nodeList
    int x2 =nodeList->get(2)->getRow() ;
    int y2=nodeList->get(2)->getCol();
    int z2=nodeList->get(2)->getDistanceToS();
    std::cout<<"pointer at position 2 is: " <<x2<<y2<<z2<<std::endl;
    // same as code above, but simpler
    std::cout<<"pointer at position 2 is: " <<nodeList->get(2)<<std::endl;

    
    // Print out the NodeList
    nodeList->printNodes();
    //checking final length
    std::cout<<nodeList->getLength()<<std::endl;


    //testing clearing list
    std::cout<<"TESTING CLEAR"<<std::endl;
    nodeList->clear();
    //testing length after clear
    std::cout<<nodeList->getLength()<<std::endl;
    
    std::cout<<"LIST HAS BEEN CLEARED"<<std::endl;

    Node* clear_test = new Node(4,5,6);
    Node* buffer_check = new Node(7,8,9); // testing if this gets put in list, should not
    //adding only clear test after creating buffer_check node   
    nodeList->addBack(clear_test);
    //testing lenght
    std::cout<<"the length of the list is: "<<nodeList->getLength()<<std::endl;
    //testing containsNode function
    std::cout<<"checking if list contains specific node:"<<nodeList->containsNode(buffer_check)<<std::endl; // should print 0
    
    std::cout<<"checking if list contains specific node:"<<nodeList->containsNode(clear_test)<<std::endl; // should print 1


    // testing deep copy function
    NodeList* copyList = new NodeList(*nodeList);
    //prints nodes of first list
    nodeList->printNodes();
    std::cout<< nodeList->get(0)<<std::endl;
    std::cout<<"testing deep copy of nodeList"<<std::endl;
    //adds new node to the second list
    Node* copy_list_node_2 = new Node(10,11,12);
    copyList->addBack(copy_list_node_2);
    //prints copy of list
    copyList ->printNodes();
    std::cout<<copyList->getLength()<<std::endl;
    //gets first element of the copy list
    std::cout<< copyList->get(0)<<std::endl; // if memory adress is different deepcopy was successful
    
    
}
