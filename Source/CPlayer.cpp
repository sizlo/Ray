#include "CPlayer.hpp"
#include "CGlobals.hpp"
#include "CLevel.hpp"
#include "CollisionHandler.hpp"

CVector2f upDir = CVector2f(0.0f, -1.0f);
CVector2f downDir = CVector2f(0.0f, 1.0f);
CVector2f leftDir = CVector2f(-1.0f, 0.0f);
CVector2f rightDir = CVector2f(1.0f, 0.0f);

CPlayer::CPlayer()
{
    mShape = CRectangleShape(CGlobals::playerSize, CGlobals::playerSize);
    mShape.setFillColor(CColour::Blue);
    
    mTopHSpeed[kGrounded] = 1000.0f;
    mTopHSpeed[kInAir] = mTopHSpeed[kGrounded];
    mTopHSpeed[kOnWall] = 0.0f;
    
    // We want to reach top speed in 1/5th of a second
    mHAcceleration[kGrounded] = mTopHSpeed[kGrounded] * 5.0f;
    mHAcceleration[kInAir] = mHAcceleration[kGrounded] / 2.0f;
    mHAcceleration[kOnWall] = 0.0f;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Init(CVector2f startPos)
{
    mHSpeed = 0.0f;
    mVSpeed = 0.0f;
    mShape.setPosition(startPos);
    AssignCorrectState();
}

void CPlayer::Update(CTime elapsedTime)
{
    switch (mState)
    {
        case kGrounded:
            DoHorizontalMovement(elapsedTime);
            break;
        case kInAir:
            break;
        case kOnWall:
            break;
        case kStateCount: // Do nothing
            break;
    }
    
    AssignCorrectState();
}

void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
    
    char buffer[32];
    sprintf(buffer, "mHSpeed: %f", mHSpeed);
    theWindow->DrawTextAt(buffer, 500.0f, 500.0f, CColour::Black, 24);
}

CConvexShape & CPlayer::GetHitbox()
{
    return mShape;
}

CVector2f CPlayer::GetPosition()
{
    return mShape.getPosition();
}

CVector2f CPlayer::GetMidPoint()
{
    CVector2f mid = mShape.getPosition();
    mid.x += CGlobals::playerSize / 2.0f;
    mid.y += CGlobals::playerSize / 2.0f;
    return mid;
}

bool CPlayer::IsGroundBeneathUs()
{
    bool groundBeneathUs = false;
    
    // Create a sensor to check beneath us
    float bottom = mShape.getGlobalBounds().top + mShape.getGlobalBounds().height;
    float left = mShape.getGlobalBounds().left;
    float width = mShape.getGlobalBounds().width;
    CConvexShape sensor = CRectangleShape(width, 1.0f);
    sensor.setPosition(left, bottom);
    
    // Check for a collision with all the platforms
    std::list<CPlatform *> platforms = CLevel::GetCurrent()->GetPlatforms();
    for (auto p: platforms)
    {
        CVector2f cv;
        if (CollisionHandler::AreColliding(sensor, p->GetHitbox(), &cv))
        {
            if (cv.GetDirection() == upDir)
            {
                groundBeneathUs = true;
            }
        }
    }
    
    
    return groundBeneathUs;
}

void CPlayer::AssignCorrectState()
{
    if (IsGroundBeneathUs())
    {
        mState = kGrounded;
    }
    else
    {
        mState = kInAir;
    }
}

void CPlayer::DoHorizontalMovement(CTime elapsedTime)
{
    CVector2f direction(0.0f, 0.0f);
    if (CKeyboard::isKeyPressed(CKeyboard::A))
    {
        direction += leftDir;
    }
    if (CKeyboard::isKeyPressed(CKeyboard::D))
    {
        direction += rightDir;
    }
    
    // If we're not trying to move in a direction decelerate
    bool decelerating = false;
    if (direction.x == 0.0f)
    {
        decelerating = true;
        if (mHSpeed > 0.0f) // Going right
        {
            direction = leftDir;
        }
        else if (mHSpeed < 0.0f) // Going left
        {
            direction = rightDir;
        }
    }
    
    mHSpeed += (direction.x * mHAcceleration[mState] * elapsedTime.asSeconds());
    
    // If we're decelerating make sure we don't cross 0
    if (decelerating)
    {
        if ((direction.x < 0.0f && mHSpeed < 0.0f)
            || (direction.x > 0.0f && mHSpeed > 0.0f))
        {
            mHSpeed = 0.0f;
        }
    }
    
    mHSpeed = std::max(mHSpeed, -mTopHSpeed[mState]);
    mHSpeed = std::min(mHSpeed, mTopHSpeed[mState]);
    mShape.move(mHSpeed * elapsedTime.asSeconds(), 0.0f);
}