#ifndef __Ray__CRayGame__
#define __Ray__CRayGame__

#include "CGame.hpp"

class CLevel;

enum EDMGameLocation
{
    kGameLocationLevel = kGameLocationDummy + 1,
    kGameLocationTutorial
};

class CRayGame : public CGame
{
public:
    static CRayGame * Get();
    
    CRayGame();
    
    void InitialiseOptions();
    void GoToLocation(int theLocation, std::string filename);
};

#endif // __Ray__CRayGame__
