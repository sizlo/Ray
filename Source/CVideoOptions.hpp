#ifndef __Ray__CVideoOptions__
#define __Ray__CVideoOptions__

#include "GUIMenu/CGUIMenu.hpp"
#include "GUIMenu/CToggleWidget.hpp"
#include "GUIMenu/CPickerWidget.hpp"

class CVideoOptions : public CGUIMenu
{
public:
    CVideoOptions();
    ~CVideoOptions();
private:
    void HandleSaveButton();
    void HandleBackButton();
    void HandleExitButton();
    
    CToggleWidget *mFullscreenWidget;
    CToggleWidget *mVsyncWidget;
    CToggleWidget *mPreserveAspectWidget;
    CPickerWidget *mAAWidget;
    CPickerWidget *mResolutionWidget;
    
    float mXPos;
    float mYPos;
    float mWidgetWidth;
    float mWidgetHeight;
    float mYOffset;
};

#endif /* defined(__Ray__CVideoOptions__) */
