#ifndef __Ray__CPlayer__
#define __Ray__CPlayer__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"

enum EPlayerState
{
    kGrounded,
    kInAir,
    kOnWall,
    kStateCount
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
    bool IsGroundBeneathUs();
    void AssignCorrectState();
    void DoHorizontalMovement(CTime elapsedTime);
    
    CConvexShape mShape;
    EPlayerState mState;
    float mTopHSpeed[kStateCount];
    float mHAcceleration[kStateCount];
    float mHSpeed;
    float mVSpeed;
};

#endif // __Ray__CPlayer__
