#ifndef __Ray__CPlatform__
#define __Ray__CPlatform__

#include "CRenderable.hpp"

class CPlatform : public CRenderable
{
public:
    CPlatform(CVector2f topLeft, float width, float height);
    ~CPlatform();
    
    void Draw(CWindow *theWindow);
    
    CConvexShape & GetHitbox();
    
private:
    CConvexShape mShape;
};

#endif // __Ray__CPlatform__
