#include "CLevel.hpp"
#include "CRayGame.hpp"
#include "GameOptions.hpp"
#include "CGlobals.hpp"
#include "CollisionHandler.hpp"
#include "CMessageBroadcaster.hpp"
#include "CLevelInterpreter.hpp"

CLevel * CLevel::smCurrentLevel = NULL;

float wallSize = 50.0f;

CLevel::CLevel()
{
    mPlayer = new CPlayer();
    mTorch = new CTorch(mPlayer);
    mSwitch = new CSwitch();
    
    mResetTooltip = CToolTip("Press R to reset the level", 100.0f);
    mResetTooltip.SetInfinite(true);
}

CLevel::CLevel(std::string filename) : CLevel()
{
    CLevelInterpreter i(filename);
    if (i.LoadFile())
    {
        i.Parse(this);
    }
}

CLevel::~CLevel()
{
    FREE_LIST_CONTENTS(mPlatforms);
    SAFE_DELETE(mPlayer);
    SAFE_DELETE(mTorch);
    SAFE_DELETE(mSwitch);
}

void CLevel::Enter()
{
    CRayGame::Get()->RegisterUpdateable(this);
    CRayGame::Get()->RegisterRenderable(this);
    
    CRayGame::Get()->SetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Subscribe(mPlayer);
    CMessageBroadcaster<CEvent>::Subscribe(this);
    
    smCurrentLevel = this;
    
    StartLevel();
}

void CLevel::Exit()
{
    CRayGame::Get()->UnregisterUpdateable(this);
    CRayGame::Get()->UnregisterRenderable(this);
    
    CRayGame::Get()->UnsetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Unsubscribe(mPlayer);
    CMessageBroadcaster<CEvent>::Unsubscribe(this);
    
    smCurrentLevel = NULL;
}

bool CLevel::HandleMessage(CEvent e)
{
    bool messageEaten = false;
    
    if (e.type == CEvent::KeyPressed)
    {
        if (e.key.code == CKeyboard::R)
        {
            if (PlayerIsOutOfBounds())
            {
                mResetTooltip.SetState(kExiting);
            }
            StartLevel();
        }
#if TGL_DEBUG
        else if (e.key.code == CKeyboard::L)
        {
            mLightsOn = !mLightsOn;
        }
#endif
    }
    
    return messageEaten;
}

void CLevel::StartLevel()
{
    mLightsOn = false;
    mPlayer->Init(mPlayerStartPos);
    mSwitch->SetPosition(mSwitchPos);
}

void CLevel::Update(CTime elapsedTime)
{
    mPlayer->Update(elapsedTime);
    
    // Handle collisions before updating the torch so the player isn't inside a platform
    HandleCollisions();
    
    mTorch->Update(elapsedTime);
    
    if (PlayerIsOutOfBounds())
    {
        if (mResetTooltip.IsDone() || mResetTooltip.IsExiting())
        {
            mResetTooltip.SetState(kEntering);
        }
    }
    if (PlayerIsOutOfBounds() || mResetTooltip.IsExiting())
    {
        mResetTooltip.Update(elapsedTime);
    }
}

void CLevel::Draw(CWindow *theWindow)
{
    for (auto p: mPlatforms)
    {
        p->Draw(theWindow);
    }
    
    mSwitch->Draw(theWindow);
    
    // Draw the darkness over the level but make sure the player and torch are visible
    if (!mLightsOn)
    {
        mTorch->DrawDarkness(theWindow);
    }
    
    mPlayer->Draw(theWindow);
    mTorch->Draw(theWindow);
    
    mResetTooltip.Draw(theWindow);
}

void CLevel::AddPlatform(CPlatform *p)
{
    mPlatforms.push_back(p);
}

std::list<CConvexShape> CLevel::GetOccluders()
{
    std::list<CConvexShape> occluders;
    for (auto p: mPlatforms)
    {
        occluders.push_back(p->GetHitbox());
    }
    return occluders;
}

std::list<CPlatform *> CLevel::GetPlatforms()
{
    return mPlatforms;
}

void CLevel::SetPlayerStartPosition(CVector2f pos)
{
    mPlayerStartPos = pos;
}

void CLevel::SetSwitchPosition(CVector2f pos)
{
    mSwitchPos = pos;
}

void CLevel::TurnOnLights()
{
    mLightsOn = true;
}

CLevel * CLevel::GetCurrent()
{
    return smCurrentLevel;
}

void CLevel::HandleCollisions()
{
    CVector2f cv;
    for (auto p: mPlatforms)
    {
        if (CollisionHandler::AreColliding(mPlayer->GetHitbox(), p->GetHitbox(), &cv))
        {
            mPlayer->ReactToCollisionWith(p, cv);
        }
    }
    
    if (CollisionHandler::AreColliding(mPlayer->GetHitbox(), mSwitch->GetHitbox(), &cv))
    {
        mSwitch->ReactToCollisionWith(mPlayer, cv);
    }
}

bool CLevel::PlayerIsOutOfBounds()
{
    CFloatRect bounds(0.0f, 0.0f, GameOptions::viewWidth, GameOptions::viewHeight);
    return !bounds.intersects(mPlayer->GetHitbox().getGlobalBounds());
}