#include "CSwitch.hpp"
#include "CLevel.hpp"
#include "CGlobals.hpp"

CSwitch::CSwitch(CVector2f position)
{
    float s = CGlobals::switchSize;
    mOuterShape = CRectangleShape(s, s, true);
    mInnerShape = CRectangleShape(s / 4.0f, s / 2.0f, true);
    mOuterShape.setPosition(position);
    mInnerShape.setPosition(position);
    mOuterShape.setFillColor(CColour::White);
    mOuterShape.setOutlineColor(CColour::Black);
    mOuterShape.setOutlineThickness(1.0f);
    mInnerShape.setFillColor(CColour::White);
    mInnerShape.setOutlineColor(CColour::Black);
    mInnerShape.setOutlineThickness(1.0f);
}

CSwitch::~CSwitch()
{
    
}

void CSwitch::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mOuterShape);
    theWindow->DrawShape(mInnerShape);
}

CConvexShape & CSwitch ::GetHitbox()
{
    return mOuterShape;
}

void CSwitch::ReactToCollisionWith(CPlayer *player, CVector2f cv)
{
    CLevel::GetCurrent()->TurnOnLights();
}