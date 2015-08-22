#include "CTutorialLevel.hpp"
#include "CGlobals.hpp"

CTutorialLevel::CTutorialLevel() : CLevel()
{
    // Walls / roof
    float wallWidth = 50.0f;
    AddPlatform(new CPlatform(CVector2f(0.0f, 0.0f), wallWidth, GameOptions::viewHeight));
    AddPlatform(new CPlatform(CVector2f(GameOptions::viewWidth - wallWidth, 0.0f), wallWidth, GameOptions::viewHeight));
    AddPlatform(new CPlatform(CVector2f(0.0f, 0.0f), GameOptions::viewWidth, wallWidth));
    
    // Floor
    float floorHeight = 300.0f;
    AddPlatform(new CPlatform(CVector2f(0.0f, GameOptions::viewHeight - floorHeight), GameOptions::viewWidth, floorHeight));
    
    // Ceiling, leaving room for the exit chute
    float ceilingHeight = 400.0f;
    float chuteWidth = 300.0f;
    AddPlatform(new CPlatform(CVector2f(0.0f, 0.0f), GameOptions::viewWidth - wallWidth - chuteWidth, ceilingHeight));
    
    SetPlayerStartPosition(CVector2f(100.0f, GameOptions::viewHeight - floorHeight - CGlobals::playerSize));
    SetSwitchPosition(CVector2f(GameOptions::viewWidth - wallWidth - (chuteWidth/2.0f), wallWidth + CGlobals::switchSize));
}

CTutorialLevel::~CTutorialLevel()
{
    
}