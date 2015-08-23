#include "CLevelBlock.hpp"

CLevelBlock::CLevelBlock(CVector2f topLeft, float width, float height, CColour colour)
{
    std::list<CVector2f> points;
    points.push_back(topLeft);
    points.push_back(topLeft + CVector2f(width, 0.0f));
    points.push_back(topLeft + CVector2f(width, height));
    points.push_back(topLeft + CVector2f(0.0f, height));
    mShape = CConvexShape(points);
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
