#include "CRayGame.hpp"
#include "CFrontEnd.hpp"

int main(int argc, char **argv)
{
    CRayGame theGame;
    theGame.Init(new CFrontEnd());
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
