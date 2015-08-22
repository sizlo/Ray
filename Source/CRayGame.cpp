#include "CRayGame.hpp"
#include "CLevel.hpp"
#include "CTutorialLevel.hpp"

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
    // Set up the next location
    switch (theLocation)
    {
        case kGameLocationLevel:
            DEBUG_LOG("Level requested");
            mNextLocation = new CLevel();
            break;
            
        case kGameLocationTutorial:
            DEBUG_LOG("Tutorial requested")
            mNextLocation = new CTutorialLevel();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mNextLocation = new CDummyGameLocation();
            break;
    }
}