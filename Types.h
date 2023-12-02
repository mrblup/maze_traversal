
#ifndef COSC_ASS_ONE_TYPES
#define COSC_ASS_ONE_TYPES

#include <math.h> 

#define ENV_DIM                     20
#define NODE_LIST_ARRAY_MAX_SIZE    4*(ENV_DIM * ENV_DIM)

// A 2D array to represent the maze or observations

typedef char Env[ENV_DIM][ENV_DIM];

#define SYMBOL_WALL     '='
#define SYMBOL_EMPTY    '.'
#define SYMBOL_GOAL     'G'
#define SYMBOL_START    'S'

#endif
