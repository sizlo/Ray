#ifndef __Ray__CLevelBlock__
#define __Ray__CLevelBlock__

#include "CRenderable.hpp"

struct SLevelBlockInfo
{
    CVector2f topLeft;
    float width;
    float height;
};

class CPlayer;

class CLevelBlock : public CRenderable
{
public:
    CLevelBlock(CVector2f topLeft, float width, float height, CColour colour);
    ~CLevelBlock();
    
    void Draw(CWindow *theWindow);
    
    CConvexShape & GetHitbox();    
    CVector2f GetPosition();
    
    virtual void ReactToCollisionWith(CPlayer *player, CVector2f cv);
    
private:
    CConvexShape mShape;
};

#endif // __Ray__CLevelBlock__
