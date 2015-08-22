#ifndef __Ray__CRayGame__
#define __Ray__CRayGame__

#include "CGame.hpp"

class CRayGame : public CGame
{
public:
    static CRayGame * Get();
    
    CRayGame();
    
    void InitialiseOptions();
};

#endif // __Ray__CRayGame__
