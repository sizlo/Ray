#ifndef __Ray__CTorch__
#define __Ray__CTorch__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"

class CPlayer;

class CTorch: public CUpdateable, public CRenderable
{
public:
    CTorch(CPlayer *theHolder);
    ~CTorch();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    void DrawDarkness(CWindow *theWindow);
        
private:
    std::list<CConvexShape> GenerateDarkness(CWindow *theWindow);
    CVector2f GetClosestIntersectionForRay(CLine ray, std::list<CConvexShape> occluders);
    
    CConvexShape mShape;
    CPlayer *mHolder;
    CVector2f mLightDirection;
    float mTorchLength;
};

#endif // __Ray__CTorch__
