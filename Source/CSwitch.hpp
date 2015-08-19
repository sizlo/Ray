#ifndef __Ray__CSwitch__
#define __Ray__CSwitch__

#include "CRenderable.hpp"
#include "CPlayer.hpp"

class CSwitch : public CRenderable
{
public:
    CSwitch(CVector2f position);
    ~CSwitch();
    
    void Draw(CWindow *theWindow);
    
    CConvexShape & GetHitbox();
    
    void ReactToCollisionWith(CPlayer *player, CVector2f cv);
    
private:
    CConvexShape mOuterShape;
    CConvexShape mInnerShape;
};

#endif // __Ray__CSwitch__
