#ifndef __Ray__CInputOptions__
#define __Ray__CInputOptions__

#include "GUIMenu/CGUIMenu.hpp"
#include "GUIMenu/CInputWidget.hpp"

class CInputOptions : public CGUIMenu
{
public:
    CInputOptions();
    ~CInputOptions();
    
    void Update(CTime elapsedTime);
    
private:
    void HandleSaveButton();
    void HandleBackButton();
    void HandleExitButton();
    
    CInputWidget *mLeftWidget;
    CInputWidget *mRightWidget;
    CInputWidget *mJumpWidget;
    CInputWidget *mResetWidget;
    
    float mXPos;
    float mYPos;
    float mWidgetWidth;
    float mWidgetHeight;
    float mYOffset;
};

#endif /* defined(__Ray__CInputOptions__) */
