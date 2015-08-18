#ifndef __Ray__CPlayer__
#define __Ray__CPlayer__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"

enum EPlayerState
{
    kGrounded,
    kInAir,
    kOnWall
};

class CPlayer : public CUpdateable, public CRenderable
{
public:
    CPlayer();
    ~CPlayer();
    
    void Init(CVector2f startPos);
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    CConvexShape & GetHitbox();
    CVector2f GetPosition();
    CVector2f GetMidPoint();
    
private:
    CConvexShape mShape;
    float mMoveSpeed;
};

#endif // __Ray__CPlayer__
