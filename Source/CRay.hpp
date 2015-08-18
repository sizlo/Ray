#ifndef __Ray__Ray__
#define __Ray__Ray__

#include "SFMLIntegration/SFMLIntegration.hpp"
#include "CLine.hpp"
#include <list>

class CRay
{
public:
    CRay();
    CRay(CVector2f origin, CVector2f direction);
    ~CRay();
    
    CVector2f GetClosestIntersection(std::list<CConvexShape> occluders);
    CVector2f GetOrigin();
    CVector2f GetEnd();
    float GetLength();
    
private:
    CLine mLine;
    bool mCalculated;
    CVector2f mClosestIntersection;
};

#endif // __Ray__Ray__
