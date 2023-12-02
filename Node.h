
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"
#include <string>




class Node {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // get row-co-ordinate
   int getRow();

   // get Column-co-ordinate
   int getCol();

   // getters and setters for distance to source
   int getDistanceToS();
   void setDistanceToS(int distanceToS);


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   
   // Constructor/Destructor
   Node();
   Node(int row, int col, int distanceToS);
   ~Node();


    //deep copy constructor
   Node(Node& other);
    // for setting row and col after copying 
   void setRow(int new_row);
   void setCol(int new_col);
    //prints variables to see what node contains, mainly for testing purposes
    void printVariables();


private:
    int row;
    int col;
    int distanceToS;
    

};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef Node* NodePtr;

#endif // COSC_ASS_ONE_NODE
