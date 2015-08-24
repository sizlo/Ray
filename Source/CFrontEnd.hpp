#ifndef __Ray__CFrontEnd__
#define __Ray__CFrontEnd__

#include "GUIMenu/CGUIMenu.hpp"

class CFrontEnd : public CGUIMenu
{
public:
    CFrontEnd();
    ~CFrontEnd();
private:
    void HandlePlayButton();
    void HandleVideoOptionsButton();
    void HandleInputOptionsButton();
    void HandleExitButton();
};

#endif /* defined(__Ray__CFrontEnd__) */
