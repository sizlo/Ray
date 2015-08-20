#include "CPlayer.hpp"
#include "CGlobals.hpp"
#include "CLevel.hpp"
#include "CollisionHandler.hpp"
#include "SystemUtilities.hpp"

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
    
    mInitialJumpSpeed = 1100.0f;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Init(CVector2f startPos)
{
    mHSpeed = 0.0f;
    mVSpeed = 0.0f;
    mShape.setPosition(startPos);
    
    mState = kGrounded;
    ResetJumps();
    
    UpdateState();
}

void CPlayer::Update(CTime elapsedTime)
{
    switch (mState)
    {
        case kGrounded:
            DoHorizontalMovement(elapsedTime);
            break;
        case kInAir:
            DoHorizontalMovement(elapsedTime);
            DoVerticalMovement(elapsedTime);
            break;
        case kOnWall:
            break;
        case kStateCount: // Do nothing
            break;
    }
    
    UpdateState();
}

void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
    
#if TGL_DEBUG
    DrawDebugText(theWindow);
#endif
}

void CPlayer::DrawDebugText(CWindow *theWindow)
{
    std::string stateString;
    switch (mState)
    {
        case kGrounded: stateString = "Grounded"; break;
        case kInAir: stateString = "In Air"; break;
        case kOnWall: stateString = "On Wall"; break;
        default: stateString = "Unknown"; break;
    }
    char buffer[1024];
    sprintf(buffer, "mHSpeed: %f\nmVSpeed: %f\nmState: %s",
            mHSpeed,
            mVSpeed,
            stateString.c_str());
    theWindow->DrawTextAt(buffer, 500.0f, 500.0f, CColour::Black, 24);
}

bool CPlayer::HandleMessage(CEvent e)
{
    bool messageEaten = false;
    
    if (e.type == CEvent::KeyPressed)
    {
        if (e.key.code == CKeyboard::Space)
        {
            messageEaten = true;
            TryStartJump();
        }
#if TGL_DEBUG
        else if (e.key.code == CKeyboard::LShift)
        {
            CVector2f newPos = SystemUtilities::GetMousePosition();
            Init(newPos);
        }
#endif
    }
    
    return messageEaten;
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

void CPlayer::ReactToCollisionWith(CPlatform *platform, CVector2f cv)
{
    // Seperate the player from the platform
    CollisionHandler::Seperate(mShape, platform->GetHitbox(), cv, kCRMoveLeft);
    
    CVector2f direction = cv.GetDirection();
    if (direction == upDir) // Collided with ground
    {
        ResetJumps();
        mState = kGrounded;
        mVSpeed = 0.0f;
    }
    else if (direction == downDir) // Collided with roof
    {
        mVSpeed = 0.0f;
    }
    else if (direction == leftDir || direction == rightDir) // Collided with wall
    {
        // Will eventually attach to wall, for now keep current state
        mHSpeed = 0.0f;
    }
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

void CPlayer::UpdateState()
{
    if (mState == kGrounded && !IsGroundBeneathUs())
    {
        mState = kInAir;
        // Remove a jump since we fell off a platform
        mJumpsLeft--;
    }
}

void CPlayer::TryStartJump()
{
    if (mJumpsLeft > 0)
    {
        mJumpsLeft--;
        CVector2f direction;
        switch (mState)
        {
            case kGrounded: // If we're on the ground jump directly up
                direction = upDir;
                mVSpeed = mInitialJumpSpeed * direction.y;
                break;
            case kInAir: // If we're in the air use the current input direction to decide which way to jump
                direction = upDir;
                if (CKeyboard::isKeyPressed(CKeyboard::A))
                {
                    direction += leftDir;
                }
                if (CKeyboard::isKeyPressed(CKeyboard::D))
                {
                    direction += rightDir;
                }
                mVSpeed = mInitialJumpSpeed * direction.y;
                mHSpeed = mInitialJumpSpeed * direction.x;
                break;
            case kOnWall:
                break;
            case kStateCount: // Do nothing
                break;
        }
        mState = kInAir;
    }
}

void CPlayer::ResetJumps()
{
    mJumpsLeft = 2;
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

void CPlayer::DoVerticalMovement(CTime elapsedTime)
{
    mVSpeed += CGlobals::gravity.y * elapsedTime.asSeconds();
    mShape.move(0.0f, mVSpeed * elapsedTime.asSeconds());
}