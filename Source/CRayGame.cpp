#include "CRayGame.hpp"
#include "CTutorialLevel.hpp"
#include "CInputListInterpreter.hpp"
#include "CGlobals.hpp"

CRayGame * CRayGame::Get()
{
    return static_cast<CRayGame *>(CGame::Get());
}

CRayGame::CRayGame() : CGame("Ray v" RAY_VERSION_STRING)
{
    mClearColour = CColour::White;
}

void CRayGame::InitialiseOptions()
{
    // Default to 4xAA
    GameOptions::antiAliasingLevel = 4;
    
    // Set up keybindings
    CInputListInterpreter i("inputs.xml");
    if (i.LoadFile())
    {
        std::list<SInputListEntry> bindings = i.Parse();
        for (auto entry: bindings)
        {
            if (entry.name == "left")
            {
                CGlobals::leftInput = entry.input;
            }
            else if (entry.name == "right")
            {
                CGlobals::rightInput = entry.input;
            }
            else if (entry.name == "jump")
            {
                CGlobals::jumpInput = entry.input;
            }
            else if (entry.name == "reset")
            {
                CGlobals::resetInput = entry.input;
            }
        }
    }
    
    // Then perform any generic initialisation (reads config)
    CGame::InitialiseOptions();
    
    // If we're in fullscreen force ourselves to native resolution
    if (GameOptions::fullscreen)
    {
        GameOptions::windowWidth = CVideoMode::getDesktopMode().width;
        GameOptions::windowHeight = CVideoMode::getDesktopMode().height;
    }
}