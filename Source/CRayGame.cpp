#include "CRayGame.hpp"
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
    // Default to 4xAA
    GameOptions::antiAliasingLevel = 4;
    
    // Then perform any generic initialisation (reads config)
    CGame::InitialiseOptions();
}