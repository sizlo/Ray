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
    
    mDebugLightsOn = false;
    
    mResetTooltip = CToolTip("Press " + CGlobals::resetInput.AsString() + " to reset the level", 100.0f);
    mResetTooltip.SetInfinite(true);
    
    mLevelWinToolTip = CToolTip("Ray turned on the lights\nPress Esc to return to level select", 10.0f);
    mLevelWinToolTip.SetInfinite(true);
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
    FREE_LIST_CONTENTS(mHazards);
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
    
    if (CGlobals::resetInput.WasPressedInEvent(e))
    {
        if (PlayerIsDead())
        {
            mResetTooltip.SetState(kExiting);
        }
        if (mLightsOn)
        {
            mLevelWinToolTip.SetState(kExiting);
        }
        StartLevel();
        
        messageEaten = true;
    }
    
    if (e.type == CEvent::KeyPressed)
    {
        if (e.key.code == CKeyboard::Escape)
        {
            CRayGame::Get()->PopGameLocation();
            messageEaten = true;
        }
#if TGL_DEBUG
        else if (e.key.code == CKeyboard::L)
        {
            mDebugLightsOn = !mDebugLightsOn;
            messageEaten = true;
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
    bool playerWasDead = mPlayer->IsDead();
    
    if (!PlayerIsOutOfBounds())
    {
        mPlayer->Update(elapsedTime);
        
        for (auto p: mPlatforms)
        {
            p->Update(elapsedTime);
        }
    
        // Handle collisions before updating the torch so the player isn't inside a platform
        HandleCollisions();
        
        mTorch->Update(elapsedTime);
    }
    
    if (PlayerIsDead())
    {
        if (mResetTooltip.IsDone() || mResetTooltip.IsExiting())
        {
            mResetTooltip.SetState(kEntering);
        }
    }
    if (PlayerIsDead() || mResetTooltip.IsExiting())
    {
        mResetTooltip.Update(elapsedTime);
    }
    
    if (mLightsOn || mLevelWinToolTip.IsExiting())
    {
        mLevelWinToolTip.Update(elapsedTime);
    }
    
    if (!playerWasDead && mPlayer->IsDead())
    {
        mResetTooltip.SetText("Ray " + mPlayer->GetDeathReason() + "\nPress " + CGlobals::resetInput.AsString() + " to reset level");
    }
}

void CLevel::Draw(CWindow *theWindow)
{
    for (auto p: mPlatforms)
    {
        p->Draw(theWindow);
    }
    for (auto h: mHazards)
    {
        h->Draw(theWindow);
    }
    
    mSwitch->Draw(theWindow);
    
    // Draw the darkness over the level but make sure the player and torch are visible
    if (!(mLightsOn || mDebugLightsOn))
    {
        mTorch->DrawDarkness(theWindow);
    }
    
    mPlayer->Draw(theWindow);
    mTorch->Draw(theWindow);
    
    mResetTooltip.Draw(theWindow);
    mLevelWinToolTip.Draw(theWindow);
}

void CLevel::AddPlatform(CPlatform *p)
{
    mPlatforms.push_back(p);
}

void CLevel::AddHazard(CHazard *h)
{
    mHazards.push_back(h);
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
    if (!mLightsOn)
    {
        mLevelWinToolTip.SetState(kEntering);
    }
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
            p->ReactToCollisionWith(mPlayer, cv);
        }
    }
    for (auto h: mHazards)
    {
        if (CollisionHandler::AreColliding(mPlayer->GetHitbox(), h->GetHitbox(), &cv))
        {
            mPlayer->ReactToCollisionWith(h, cv);
            h->ReactToCollisionWith(mPlayer, cv);
        }
    }
    
    if (CollisionHandler::AreColliding(mPlayer->GetHitbox(), mSwitch->GetHitbox(), &cv))
    {
        mSwitch->ReactToCollisionWith(mPlayer, cv);
    }
}

bool CLevel::PlayerIsDead()
{
    return PlayerIsOutOfBounds() || mPlayer->IsDead();
}

bool CLevel::PlayerIsOutOfBounds()
{
    CFloatRect bounds(-GameOptions::viewWidth/2.0f, -GameOptions::viewHeight/2.0f, GameOptions::viewWidth * 2.0f, GameOptions::viewHeight * 2.0f);
    bool outOfBounds = !bounds.intersects(mPlayer->GetHitbox().getGlobalBounds());
    
    if (outOfBounds && !mPlayer->IsDead())
    {
        mPlayer->Kill("fell into the void");
    }
    
    return outOfBounds;
}