#include "CTutorialLevel.hpp"

CTutorialLevel::CTutorialLevel() : CLevel()
{
    // Walls
    float wallWidth = 50.0f;
    AddPlatform(new CPlatform(CVector2f(0.0f, 0.0f), wallWidth, GameOptions::viewHeight));
    AddPlatform(new CPlatform(CVector2f(GameOptions::viewWidth - wallWidth, 0.0f), wallWidth, GameOptions::viewHeight));
    AddPlatform(new CPlatform(CVector2f(0.0f, 0.0f), GameOptions::viewWidth, wallWidth));
    AddPlatform(new CPlatform(CVector2f(0.0f, GameOptions::viewHeight - wallWidth), GameOptions::viewWidth, wallWidth));
    
}

CTutorialLevel::~CTutorialLevel()
{
    
}