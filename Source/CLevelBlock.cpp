#include "CLevelBlock.hpp"

CLevelBlock::CLevelBlock(CVector2f topLeft, float width, float height, CColour colour)
{
    std::list<CVector2f> points;
    points.push_back(CVector2f(0.0f, 0.0f));
    points.push_back(CVector2f(width, 0.0f));
    points.push_back(CVector2f(width, height));
    points.push_back(CVector2f(0.0f, height));
    mShape = CConvexShape(points);
    mShape.setPosition(topLeft);
    mShape.setFillColor(colour);
}

CLevelBlock::~CLevelBlock()
{
    
}

void CLevelBlock::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}

CConvexShape & CLevelBlock::GetHitbox()
{
    return mShape;
}

CVector2f CLevelBlock::GetPosition()
{
    return mShape.getPosition();
}

void CLevelBlock::ReactToCollisionWith(CPlayer *player, CVector2f cv)
{
    // Do nothing
}