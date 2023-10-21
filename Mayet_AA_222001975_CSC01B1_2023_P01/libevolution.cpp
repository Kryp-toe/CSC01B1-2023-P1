#include "libevolution.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

namespace EvolutionSpace
{
    TwoDimArray alloc(int intRows, int intCols)
    {
        // Create a 1D array of Cell*.
        TwoDimArray arrWorld = new OneDimArray[intRows];
        
        // For each Cell*...
        for(int r = 0; r < intRows; r++)
        {
            // Create a 1D array of Cell.
            arrWorld[r] = new Cell[intCols];
            {
                // For each Cell.
                for(int c = 0; c < intCols; c++)
                {
                    // Initialise to default values.
                    arrWorld[r][c].intRow = r;
                    arrWorld[r][c].intCol = c;
                    arrWorld[r][c].blnLive = false;
                }
            }
        }
        return arrWorld;
    }
    
    TwoDimArray clone(TwoDimArray arrOriginal, int intRows, int intCols)
    {
        // Allocate memory for a new 2D array.
        TwoDimArray arrClone = alloc(intRows, intCols);
        
        // Copy the values from the old array to the new array.
        for(int r = 0; r < intRows; r++)
        {
            for(int c = 0; c < intCols; c++)
            {
                arrClone[r][c] = arrOriginal[r][c];
            }
        }
        return arrClone;
    }
    
    void destroyWorldImp(stcGameWorld*& objWorld)
    {
        // Deallocate each pointer individually (each pointer points to an array of values).
        for(int r = 0; r < objWorld->intRows; r++)
            delete [] objWorld->arrWorld[r];
        
        // Deallocate the the array of pointers.
        delete [] objWorld->arrWorld;
        
        // Set the array of pointers to point to invalid memory.
        objWorld->arrWorld = nullptr;
    }
    
    bool isInWorldImp(stcGameWorld* objWorld, int intRow, int intCol)
    {
        if(intRow < 0)
            return false;
        
        if(intRow >= objWorld->intRows)
            return false;
        
        if(intCol < 0)
            return false;
        
        if(intCol >= objWorld->intCols)
            return false;
        
        return true;
    }
    
    int numLiveNeighboursImp(int intRow, int intCol, stcGameWorld* objWorld)
    {
        int intCount = 0;
        for(int r = intRow - 1; r <= intRow + 1; r++)
        {
            for(int c = intCol - 1; c <= intCol + 1; c++)
            {
                // Avoid counting self as a neighbour.
                if((r != intRow) &&
                    (c != intCol) &&
                    isInWorldImp(objWorld, r, c) &&
                    objWorld->arrWorld[r][c].blnLive)
                {
                    ++intCount;
                }
            }
        }
        
        return intCount;
    }
    
    void evolveWorldImp(stcGameWorld*& objWorld)
    {
        ++objWorld->intGeneration;
        TwoDimArray arrNew = clone(objWorld->arrWorld, objWorld->intRows, objWorld->intCols);
        
        for(int r = 0; r < objWorld->intRows; r++)
        {
            for(int c = 0; c < objWorld->intCols; c++)
            {
               int intNumLiveNeighbours = numLiveNeighboursImp(r, c, objWorld);
                
                // For every live cell:
                if(objWorld->arrWorld[r][c].blnLive)
                {
                    // Case 1: Death by underpopulation.
                    if(intNumLiveNeighbours < 2)
                        arrNew[r][c].blnLive = false;
                    
                    // Case 3: Death by overpopulation.
                    else if(intNumLiveNeighbours > 3)
                        arrNew[r][c].blnLive = false;
                
                /* If none of the above cases are true, Case 2 is automatically true,
                * which means the cell should remain live.*/
                }
                // For every dead cell (Case 4):
                else if(intNumLiveNeighbours == 3)
                    arrNew[r][c].blnLive = true;
            }
        }
        
        destroyWorldImp(objWorld); // Deallocate the old memory.
        objWorld->arrWorld = arrNew; // Point to the new memory.
    }
    
    void displayWorldImp(stcGameWorld* objWorld)
    {
        system("clear");
        for(int r = 0; r < objWorld->intRows; r++)
        {
            for(int c = 0; c < objWorld->intCols; c++)
                cout << chEntities[objWorld->arrWorld[r][c].blnLive] << ' ';
            
            cout << endl;
        }
        cout << "Generation: " << objWorld->intGeneration << endl;
    }
    
    int rangedRandom(int intLB, int intUB)
    {
        return rand() % (intUB - intLB + 1) + intLB;
    }
    
    int convToInt(string strArg)
    {
        stringstream ssConv;
        int intResult;
        ssConv << strArg;
        ssConv >> intResult;
        
        if(ssConv.fail())
        {
            stringstream ssErrorMessage;
            ssErrorMessage << strArg << " is not an integer." << endl;
            terminate(ssErrorMessage.str(), ERROR_CONV);
        }
        
        return intResult;
    }
    
    void terminate(string strMessage, ErrorCode eCode)
    {
        cerr << strMessage;
        exit(eCode);
    }
    
    stcGameWorld* initWorld(int intRows, int intCols, int intLiveProb)
    {
        // Allocate memory and initialise the game state.
        stcGameWorld* objWorld = new stcGameWorld;
        
        TwoDimArray arrWorld = alloc(intRows, intCols);
        
        objWorld->arrWorld = arrWorld;
        objWorld->intRows = intRows;
        objWorld->intCols = intCols;
        
        for(int r = 0; r < objWorld->intRows; r++)
        {
            for(int c = 0; c < objWorld->intCols; c++)
            {
                if(rangedRandom(0, 100) <= intLiveProb)
                    objWorld->arrWorld[r][c].blnLive = true;
            }
        }
        
        objWorld->evolveWorld = &evolveWorldImp;
        objWorld->numLiveNeighbours = &numLiveNeighboursImp;
        objWorld->displayWorld = &displayWorldImp;
        objWorld->isInWorld = &isInWorldImp;
        objWorld->destroyWorld = &destroyWorldImp;
        
        return objWorld;
    }
    
}










