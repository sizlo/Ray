#include "CLevel.hpp"
#include "CRayGame.hpp"
#include "GameOptions.hpp"
#include "CGlobals.hpp"
#include "CollisionHandler.hpp"
#include "CMessageBroadcaster.hpp"

CLevel * CLevel::smCurrentLevel = NULL;

float wallSize = 50.0f;

CLevel::CLevel()
{
    // Walls/floors
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, GameOptions::viewHeight - wallSize), GameOptions::viewWidth, wallSize));
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, 0.0f), GameOptions::viewWidth, wallSize));
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, 0.0f), wallSize, GameOptions::viewHeight));
    mPlatforms.push_back(new CPlatform(CVector2f(GameOptions::viewWidth - wallSize, 0.0f), wallSize, GameOptions::viewHeight));
    
    // Lower 2 platforms
    float width = (GameOptions::viewWidth - (2 * wallSize)) / 5.0f;
    float hSpacing = width;
    float height = wallSize;
    float vSpacing = (GameOptions::viewHeight - (2 * wallSize) - (2 * height)) / 3.0f;
    
    float x = wallSize + hSpacing;
    float y = wallSize + vSpacing + height + vSpacing;
    mPlatforms.push_back(new CPlatform(CVector2f(x, y), width, height));
    x += width + hSpacing;
    mPlatforms.push_back(new CPlatform(CVector2f(x, y), width, height));
    x = wallSize + hSpacing + width;
    y = wallSize + vSpacing;
    mPlatforms.push_back(new CPlatform(CVector2f(x, y), width, height));
    
    mPlayer = new CPlayer();
    mTorch = new CTorch(mPlayer);
}

CLevel::~CLevel()
{
    FREE_LIST_CONTENTS(mPlatforms);
    SAFE_DELETE(mPlayer);
    SAFE_DELETE(mTorch);
}

void CLevel::Enter()
{
    CRayGame::Get()->RegisterUpdateable(this);
    CRayGame::Get()->RegisterRenderable(this);
    
    CRayGame::Get()->SetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Subscribe(mTorch);
    
    smCurrentLevel = this;
    
    StartLevel();
}

void CLevel::Exit()
{
    CRayGame::Get()->UnregisterUpdateable(this);
    CRayGame::Get()->UnregisterRenderable(this);
    
    CRayGame::Get()->UnsetGameState(kGameStateInGame);
    
    CMessageBroadcaster<CEvent>::Unsubscribe(mTorch);
    
    smCurrentLevel = NULL;
}

void CLevel::StartLevel()
{
    float playerX = (GameOptions::viewWidth / 2.0f) - (CGlobals::playerSize / 2.0f);
    float playerY = GameOptions::viewHeight - wallSize - CGlobals::playerSize;
    mPlayer->Init(CVector2f(playerX, playerY));
}

void CLevel::Update(CTime elapsedTime)
{
    mPlayer->Update(elapsedTime);
    
    // Handle collisions before updating the torch so the player isn't inside a platform
    HandleCollisions();
    
    mTorch->Update(elapsedTime);
}

void CLevel::Draw(CWindow *theWindow)
{
    for (auto p: mPlatforms)
    {
        p->Draw(theWindow);
    }
    
    // Draw the darkness over the level but make sure the player and torch are visible
    mTorch->DrawDarkness(theWindow);
    
    mPlayer->Draw(theWindow);
    mTorch->Draw(theWindow);
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

CLevel * CLevel::GetCurrent()
{
    return smCurrentLevel;
}

void CLevel::HandleCollisions()
{
    for (auto p: mPlatforms)
    {
        CVector2f cv;
        if (CollisionHandler::AreColliding(mPlayer->GetHitbox(), p->GetHitbox(), &cv))
        {
            CollisionHandler::Seperate(mPlayer->GetHitbox(), p->GetHitbox(), cv, kCRMoveLeft);
        }
    }
}