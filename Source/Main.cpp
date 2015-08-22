#include "CRayGame.hpp"

int main(int argc, char **argv)
{
    CRayGame theGame;
    theGame.Init(kGameLocationTutorial);
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
