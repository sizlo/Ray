#include "CRay.hpp"
#include "CollisionHandler.cpp"

CRay::CRay()
{
    
}

CRay::CRay(CVector2f origin, CVector2f direction)
{
    float length = std::max(GameOptions::viewWidth, GameOptions::viewHeight) * 10.0f;
    mLine = CLine(origin, origin + (direction * length));
    mCalculated = false;
}

CRay::~CRay()
{
    
}

CVector2f CRay::GetClosestIntersection(std::list<CConvexShape> occluders)
{
    if (!mCalculated)
    {
        mClosestIntersection = mLine.GetEnd();
        float closestDistance = mLine.GetLength();
        
        for (auto o:occluders)
        {
            std::list<CVector2f> points;
            if (CollisionHandler::AreIntersecting(mLine, o, &points, false))
            {
                for (auto p: points)
                {
                    CVector2f toPoint = p - mLine.GetStart();
                    if (toPoint.GetMagnitude() < closestDistance)
                    {
                        mClosestIntersection = p;
                        closestDistance = toPoint.GetMagnitude();
                    }
                }
            }
        }
        mCalculated = true;
    }
    
    return mClosestIntersection;
}

CVector2f CRay::GetOrigin()
{
    return mLine.GetStart();
}

CVector2f CRay::GetEnd()
{
    return mLine.GetEnd();
}

float CRay::GetLength()
{
    return mLine.GetLength();
}