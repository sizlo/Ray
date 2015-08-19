#include "CTorch.hpp"
#include "CPlayer.hpp"
#include "SystemUtilities.hpp"
#include "CLevel.hpp"
#include "CRay.hpp"

CTorch::CTorch(CPlayer *theHolder)
{
    mTorchLength = 20.0f;
    mShape = CRectangleShape(mTorchLength, 5.0f);
    mShape.setOrigin(0.0f, 2.5f);
    mShape.setFillColor(CColour::Black);
    mLightRadius = 30.0f;    
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
    
    mLightDirection = toMouse;
    mLightDirection.Normalise();
}

void CTorch::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}

void CTorch::DrawDarkness(CWindow *theWindow)
{
    std::list<CConvexShape> darknessShapes = GenerateDarkness(theWindow);
    for (auto s: darknessShapes)
    {
        s.setFillColor(CColour::Black);
        theWindow->DrawShape(s);
    }
}

std::list<CConvexShape> CTorch::GenerateDarkness(CWindow *theWindow)
{
    std::list<CConvexShape> darknessShapes;
    
    // Generate a list of rays
    CVector2f lightOrigin = mShape.getPosition() + (mLightDirection * mTorchLength);
    CVector2f direction = mLightDirection;
    direction.Rotate(-mLightRadius / 2.0f);
    int iterations = 200;
    float rotation = mLightRadius / (iterations - 1);
    std::list<CRay> rays;
    for (int i = 0; i < iterations; i++)
    {
        rays.push_back(CRay(lightOrigin, direction));
        direction.Rotate(rotation);
    }
    
    // Find the closest occlusion point for each ray and turn these into shapes
    std::list<CConvexShape> occluders = CLevel::GetCurrent()->GetOccluders();
    bool firstRay = true;
    CRay previous;
    for (auto r: rays)
    {
        if (!firstRay)
        {
            CConvexShape shape(4);
            shape.setPoint(0, previous.GetClosestIntersection(occluders));
            shape.setPoint(1, previous.GetEnd());
            shape.setPoint(2, r.GetEnd());
            shape.setPoint(3, r.GetClosestIntersection(occluders));
            darknessShapes.push_back(shape);
        }
        else
        {
            firstRay = false;
        }
        previous = r;
    }
    
    // Create boundary shapes from the first and final rays
    CRay first = rays.front();
    CConvexShape leftBoundaryShape(3);
    leftBoundaryShape.setPoint(0, first.GetOrigin());
    leftBoundaryShape.setPoint(1, first.GetEnd());
    leftBoundaryShape.setPoint(2, first.GetOrigin() - (mLightDirection * first.GetLength()));
    darknessShapes.push_back(leftBoundaryShape);
    
    CRay last = rays.back();
    CConvexShape rightBoundaryShape(3);
    rightBoundaryShape.setPoint(0, last.GetOrigin());
    rightBoundaryShape.setPoint(1, last.GetEnd());
    rightBoundaryShape.setPoint(2, last.GetOrigin() - (mLightDirection * last.GetLength()));
    darknessShapes.push_back(rightBoundaryShape);
    
    return darknessShapes;
}