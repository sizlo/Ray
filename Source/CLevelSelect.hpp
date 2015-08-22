#ifndef __Ray__CLevelSelect__
#define __Ray__CLevelSelect__

#include "GUIMenu/CGUIMenu.hpp"

class CLevelSelect : public CGUIMenu
{
public:
    CLevelSelect();
    ~CLevelSelect();
private:
    void HandleTutorialButton();
    void HandleBackButton();
    void HandleExitButton();
};

#endif /* defined(__Ray__CLevelSelect__) */
