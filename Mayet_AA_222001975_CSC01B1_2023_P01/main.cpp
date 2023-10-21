#include "libevolution.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;
using namespace EvolutionSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    
    // Process command line arguments.
    if(argc != 4)
    {
        stringstream ssError;
        ssError << "Usage: " << argv[0]
                << " <NumRows> <NumCols> <LiveProbability>" << endl;
        EvolutionSpace::terminate(ssError.str(), ERROR_ARG_COUNT);
    }
    
    int intRows = convToInt(argv[1]);
    int intCols = convToInt(argv[2]);
    int intLiveProb = convToInt(argv[3]);
    
    // Create a the game world.
    stcGameWorld* objWorld = initWorld(intRows, intCols, intLiveProb);
    
    // User interaction:
    bool blnContinue = true;
    char chOption = '\0';
    
    do
    {
        system("clear");
        
        objWorld->displayWorld(objWorld);
        cin >> chOption;
        
        switch(tolower(chOption))
        {
            case 'q':
            {
                blnContinue = false;
                break;
            }
            default:
            {
                // Any key except 'q' triggers evolution to the next generation.
                objWorld->evolveWorld(objWorld);
            }
            
        }
        
    }while(blnContinue);
    
    // Deallocate memory.
    objWorld->destroyWorld(objWorld);
    
    // Return 0.
    return SUCCESS;
}




