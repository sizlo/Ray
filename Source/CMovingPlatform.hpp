#ifndef __Ray__CMovingPlatform__
#define __Ray__CMovingPlatform__

#include "CPlatform.hpp"
#include "Tweening/CTweener.hpp"
#include "CPlayer.hpp"

class CMovingPlatform : public CPlatform
{
public:
    CMovingPlatform(CVector2f topLeft,
                    float width,
                    float height,
                    float startX,
                    float endX,
                    CTime period);
    ~CMovingPlatform();
    
    void Update(CTime elapsedTime);
    void Move(CVector2f offset);
    void ReactToCollisionWith(CPlayer *player, CVector2f cv);
    
private:
    bool IsPlayerStillOnPlatform();
    
    CTweener mTweener;
    CPlayer *mAttachedPlayer;
    float mWidth;
};

#endif // __Ray__CMovingPlatform__
