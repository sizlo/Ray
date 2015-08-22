#include "CRayGame.hpp"
#include "CTutorialLevel.hpp"

int main(int argc, char **argv)
{
    CRayGame theGame;
    theGame.Init(new CTutorialLevel());
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
