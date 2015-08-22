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
    
    // Little obstacle
    float smallObsHeight = 100.0f;
    AddPlatform(new CPlatform(CVector2f(385.0f, GameOptions::viewHeight - floorHeight - smallObsHeight), wallWidth, smallObsHeight));
    
    // Big obstacle
    float bigObsHeight = 300.0f;
    AddPlatform(new CPlatform(CVector2f(1200.0f, GameOptions::viewHeight - floorHeight - bigObsHeight), wallWidth, bigObsHeight));
    
    // Overhang
    float overhangHeight = 100.0f;
    AddPlatform(new CPlatform(CVector2f(GameOptions::viewWidth - 2*wallWidth - chuteWidth, ceilingHeight), wallWidth, overhangHeight));
    
    SetPlayerStartPosition(CVector2f(100.0f, GameOptions::viewHeight - floorHeight - CGlobals::playerSize));
    SetSwitchPosition(CVector2f(GameOptions::viewWidth - wallWidth - (chuteWidth/2.0f), wallWidth + CGlobals::switchSize));
    
    mToolTips[0] = CToolTip("Move the mouse to aim the torch", 100.0f);
    mToolTips[1] = CToolTip("Use keys A and D to move left and right", 100.0f);
    mToolTips[2] = CToolTip("Press Space to jump", 100.0f);
    mToolTips[3] = CToolTip("You can double jump and wall jump", 100.0f);
    mToolTips[4] = CToolTip("Turn on the lights to complete the level", 100.0f);
}

CTutorialLevel::~CTutorialLevel()
{
    
}

void CTutorialLevel::StartLevel()
{
    CLevel::StartLevel();
    mCurrentToolTip = 0;
    mToolTips[0].Reset();
    mToolTips[1].Reset();
    mToolTips[2].Reset();
    mToolTips[3].Reset();
    mToolTips[4].Reset();
}

void CTutorialLevel::Update(CTime elapsedTime)
{
    CLevel::Update(elapsedTime);
    
    if (mToolTips[mCurrentToolTip].IsDone() && mCurrentToolTip < 4)
    {
        mCurrentToolTip++;
    }
    mToolTips[mCurrentToolTip].Update(elapsedTime);
}

void CTutorialLevel::Draw(CWindow *theWindow)
{
    CLevel::Draw(theWindow);
    mToolTips[mCurrentToolTip].Draw(theWindow);
}