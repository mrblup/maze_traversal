
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:



   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // 
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // 
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   


    // takes the env given to contructor and places the variables in that env to the private variable env
   void assignEnv(Env env);
   //sets goalRow and goalCol to values given
   void initialPositionGoal(int row, int col);


private:
    //the number of rows an columns
    int rows;
    int cols;
    //the environment the pathplanner will work with
    Env env;
    //x&y value of start
    int startRow;
    int startCol;
    //x&y values of goal
    int goalRow;
    int goalCol;



    
};

#endif 
