#ifndef __Ray__CPlayer__
#define __Ray__CPlayer__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CMessageListener.hpp"
#include "CPlatform.hpp"
#include "CHazard.hpp"

enum EPlayerState
{
    kGrounded,
    kInAir,
    kOnWall,
    kStateCount
};

class CPlayer : public CUpdateable, public CRenderable, public CMessageListener<CEvent>
{
public:
    CPlayer();
    ~CPlayer();
    
    void Init(CVector2f startPos);
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    void DrawDebugText(CWindow *theWindow);
    
    bool HandleMessage(CEvent e);
    
    CConvexShape & GetHitbox();
    CVector2f GetPosition();
    CVector2f GetMidPoint();
    
    void Kill();
    bool IsDead();
    
    void ReactToCollisionWith(CPlatform *platform, CVector2f cv);
    void ReactToCollisionWith(CHazard *hazard, CVector2f cv);
    
private:
    bool IsGroundBeneathUs();
    bool IsWallOnAttachedSide();
    void UpdateState();
    void TryStartJump();
    void ResetJumps();
    void DoHorizontalMovement(CTime elapsedTime);
    void DoVerticalMovement(CTime elapsedTime);
    void TryToDetach(CTime elapsedTime);
    
    CConvexShape mShape;
    EPlayerState mState;
    float mTopHSpeed[kStateCount];
    float mHAcceleration[kStateCount];
    float mInitialJumpSpeed;
    float mHSpeed;
    float mVSpeed;
    int mJumpsLeft;
    CVector2f mAttachedDirection;
    float mWallUpDeceleration;
    float mWallDownDeceleration;
    float mWallDownAcceleration;
    float mWallSlideSpeed;
    CTime mDetachTime;
    CTime mCurrentDetachTimeCounter;
    bool mIsDead;
};

#endif // __Ray__CPlayer__
