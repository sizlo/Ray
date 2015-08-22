#ifndef __Ray__CTutorialLevel__
#define __Ray__CTutorialLevel__

#include "CLevel.hpp"
#include "CToolTip.hpp"

class CTutorialLevel: public CLevel
{
public:
    CTutorialLevel();
    ~CTutorialLevel();
    
    void StartLevel();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
private:
    CToolTip mToolTips[5];
    int mCurrentToolTip;
};

#endif // __Ray__CTutorialLevel__
