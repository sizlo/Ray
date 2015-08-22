#ifndef __Ray__CToolTip__
#define __Ray__CToolTip__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "Tweening/CTweener.hpp"

class CToolTip : public CUpdateable, public CRenderable
{
public:
    CToolTip();
    CToolTip(std::string theText, float yCoord);
    ~CToolTip();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Reset();
    
private:
    void UpdatePosition();
    
    CBoundedText mText;
    CConvexShape mShape;
    float mYCoord;
    float mTextMargin;
    float mMargin;
    CTweener mTweener;
};

#endif // __Ray__CToolTip__
