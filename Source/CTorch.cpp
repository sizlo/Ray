#include "CTorch.hpp"
#include "CPlayer.hpp"
#include "SystemUtilities.hpp"

CTorch::CTorch(CPlayer *theHolder)
{
    mShape = CRectangleShape(20.0f, 5.0f);
    mShape.setOrigin(0.0f, 2.5f);
    mShape.setFillColor(CColour::Black);
    
    mHolder = theHolder;
}

CTorch::~CTorch()
{
    
}

void CTorch::Update(CTime elapsedTime)
{
    // Move to the players "arm"
    CVector2f pos = mHolder->GetMidPoint();
    mShape.setPosition(pos);
    
    // Rotate to point to the mouse
    CVector2f mousePos = SystemUtilities::GetMousePosition();
    CVector2f toMouse = mousePos - pos;
    float rotation = CVector2f(1.0f, 0.0f).AngleTo(toMouse);
    mShape.setRotation(rotation);
}

void CTorch::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}