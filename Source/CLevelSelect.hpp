#ifndef __Ray__CLevelSelect__
#define __Ray__CLevelSelect__

#include "GUIMenu/CGUIMenu.hpp"

class CLevelSelect : public CGUIMenu
{
public:
    CLevelSelect();
    ~CLevelSelect();
private:
    void ProcessLevelFiles();
    
    void HandleLevelButton(std::string filename);
    void HandleTutorialButton();
    void HandleBackButton();
    void HandleExitButton();
    
    float mXPos;
    float mYPos;
    float mButtonWidth;
    float mButtonHeight;
    float mYOffset;
};

#endif /* defined(__Ray__CLevelSelect__) */
