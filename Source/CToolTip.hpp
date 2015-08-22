#ifndef __Ray__CToolTip__
#define __Ray__CToolTip__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "Tweening/CTweener.hpp"

enum EToolTipState
{
    kEntering,
    kLingering,
    kExiting,
    kDone
};

class CToolTip : public CUpdateable, public CRenderable
{
public:
    CToolTip();
    CToolTip(std::string theText, float yCoord);
    ~CToolTip();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Reset();
    void SetState(int state);
    bool IsEntering();
    bool IsLingering();
    bool IsExiting();
    bool IsDone();
    void SetInfinite(bool isInfinite);
    
private:
    void UpdatePosition();
    std::string GetStateString();
    
    CBoundedText mText;
    CConvexShape mShape;
    float mWidth;
    float mXCoord;
    float mYCoord;
    float mTextMargin;
    float mMargin;
    CTweener mTweener;
    
    int mState;
    CTime mLingerTimeCounter;
    CTime mLingerTime;
    
    bool mIsInfinite;
};

#endif // __Ray__CToolTip__
