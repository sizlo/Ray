#ifndef __Ray__CSwitch__
#define __Ray__CSwitch__

#include "CRenderable.hpp"
#include "CPlayer.hpp"

class CSwitch : public CRenderable
{
public:
    CSwitch();
    ~CSwitch();
    
    void Draw(CWindow *theWindow);
    
    CConvexShape & GetHitbox();
    void SetPosition(CVector2f pos);
    
    void ReactToCollisionWith(CPlayer *player, CVector2f cv);
    
private:
    CConvexShape mOuterShape;
    CConvexShape mInnerShape;
};

#endif // __Ray__CSwitch__
