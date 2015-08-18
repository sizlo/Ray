#include "CPlayer.hpp"
#include "CGlobals.hpp"

CVector2f upDir = CVector2f(0.0f, -1.0f);
CVector2f downDir = CVector2f(0.0f, 1.0f);
CVector2f leftDir = CVector2f(-1.0f, 0.0f);
CVector2f rightDir = CVector2f(1.0f, 0.0f);

CPlayer::CPlayer()
{
    mShape = CRectangleShape(CGlobals::playerSize, CGlobals::playerSize);
    mShape.setFillColor(CColour::Blue);
    mMoveSpeed = 500.0f;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Init(CVector2f startPos)
{
    mShape.setPosition(startPos);
}

void CPlayer::Update(CTime elapsedTime)
{
    CVector2f moveDir(0.0f, 0.0f);
    if (CKeyboard::isKeyPressed(CKeyboard::W))
    {
        moveDir += upDir;
    }
    if (CKeyboard::isKeyPressed(CKeyboard::S))
    {
        moveDir += downDir;
    }
    if (CKeyboard::isKeyPressed(CKeyboard::A))
    {
        moveDir += leftDir;
    }
    if (CKeyboard::isKeyPressed(CKeyboard::D))
    {
        moveDir += rightDir;
    }
    
    mShape.move(moveDir * mMoveSpeed * elapsedTime.asSeconds());
}

void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
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