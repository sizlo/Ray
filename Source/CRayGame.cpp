#include "CRayGame.hpp"
#include "CLevel.hpp"

CRayGame * CRayGame::Get()
{
    return static_cast<CRayGame *>(CGame::Get());
}

CRayGame::CRayGame() : CGame("Ray v" RAY_VERSION_STRING)
{
    mClearColour = CColour::White;
}

void CRayGame::InitialiseOptions()
{
    GameOptions::antiAliasingLevel = 4;
}

void CRayGame::GoToLocation(int theLocation, std::string filename)
{
    // If we're already in a location leave it
    if (mCurrentLocation != NULL)
    {
        mCurrentLocation->Exit();
        SAFE_DELETE(mCurrentLocation);
    }
    
    switch (theLocation)
    {
        case kGameLocationLevel:
            DEBUG_LOG("Level requested");
            mCurrentLocation = new CLevel();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mCurrentLocation = new CDummyGameLocation();
            break;
    }
    
    mCurrentLocation->Enter();
}