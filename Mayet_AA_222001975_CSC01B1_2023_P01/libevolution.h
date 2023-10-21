#ifndef LIBEVOLUTION_H_INCLUDED
#define LIBEVOLUTION_H_INCLUDED

#include <string>

namespace EvolutionSpace
{
    // Exit status/error codes.
    enum ErrorCode
    {
        ERROR_RANGE = -3,
        ERROR_CONV,
        ERROR_ARG_COUNT,
        SUCCESS
    };
    
    // A Cell is either live or dead.
    struct Cell
    {
        int intRow;
        int intCol;
        bool blnLive;
    };
    
    // Characters for the user interface aspect of the program.
    const char chEntities[2] = {' ', '*'};
    
    // The game world is a 2D array of Cells.
    typedef Cell* OneDimArray;
    typedef OneDimArray* TwoDimArray;
    
    // A record structure to track the game state.
    struct stcGameWorld
    {
        TwoDimArray arrWorld;
        
        int intRows;
        int intCols;
        int intGeneration;
        
        // The purpose of this function is to perform the evolutionary processes described in the question paper.
        void (*evolveWorld)(stcGameWorld*& World);
        
        // The purpose of this function is to count the number of live neighbour around a given cell.
        int (*numLiveNeighbours)(int intRow, int intCol, stcGameWorld* World);
        
        // The purpose of this function is to render the game world using ASCII characters.
        void (*displayWorld)(stcGameWorld* World);
        
        // The purpose of this function is to determine whether a location is in the game world.
        bool (*isInWorld)(stcGameWorld* World, int intRow, int intCol);
        
        // The purpose of this function is to deallocate memory.
        void (*destroyWorld)(stcGameWorld*& World);
    };
    
    // The purpose of this function is to allocate memory for the 2D array.
    TwoDimArray alloc(int intRows, int intCols);
    
    // The purpose of this function is to initialise the components of the 2D array and game state.
    stcGameWorld* initWorld(int intRows, int intCols, int intLiveProb);
    
    // The purpose of this function is to create an exact copy of a 2D array.
    TwoDimArray clone(TwoDimArray arrOriginal, int intRows, int intCols);
    
    // The purpose of this function is to generate a pseudorandom number within the provided bounds.
    int rangedRandom(int intLB, int intUB);
    
    // The purpose of this function is to convert a string to an integer.
    int convToInt(std::string strArg);
    
    // The purpose of this function is to terminate the program.
    void terminate(std::string strMessage, ErrorCode eCode);
}

#endif // LIBEVOLUTION_H




