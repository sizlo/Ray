#include "CMovingPlatform.hpp"
#include "Tweening/Easings/Sine.hpp"
#include "CollisionHandler.hpp"

CMovingPlatform::CMovingPlatform(CVector2f topLeft,
                                 float width,
                                 float height,
                                 float startX,
                                 float endX,
                                 CTime period)
:   CPlatform(topLeft, width, height)
{
    mTweener = CTweener(Easings::Sine::easeInOut, startX, endX, period);
    mTweener.SetReversible(true);
    
    mAttachedPlayer = NULL;
    mWidth = width;
}

CMovingPlatform::~CMovingPlatform()
{
    
}

void CMovingPlatform::Update(CTime elapsedTime)
{
    if (mAttachedPlayer != NULL)
    {
        if (!IsPlayerStillOnPlatform())
        {
            mAttachedPlayer = NULL;
        }
    }
    
    mTweener.Advance(elapsedTime);
    CVector2f pos(mTweener.GetCurrentValue(), GetPosition().y);
    CVector2f difference = pos - GetPosition();
    Move(difference);
}

void CMovingPlatform::Move(CVector2f offset)
{
    GetHitbox().move(offset);
    
    if (mAttachedPlayer != NULL)
    {
        mAttachedPlayer->Move(offset);
    }
}

void CMovingPlatform::ReactToCollisionWith(CPlayer *player, CVector2f cv)
{
    if (cv.GetDirection() == CVector2f(0.0f, -1.0f))
    {
        mAttachedPlayer = player;
    }
}

bool CMovingPlatform::IsPlayerStillOnPlatform()
{
    bool onPlatform = false;
    
    CRectangleShape sensor(mWidth, 1.0f);
    sensor.setPosition(GetPosition() - CVector2f(0.0f, 1.0f));
    CVector2f cv;
    if (CollisionHandler::AreColliding(sensor, mAttachedPlayer->GetHitbox(), &cv))
    {
        onPlatform = true;
    }
    
    return onPlatform;
}