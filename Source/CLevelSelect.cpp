#include "CLevelSelect.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CTutorialLevel.hpp"
#include "CRayGame.hpp"
#include "SystemUtilities.hpp"
#include "CLevelInterpreter.hpp"

#if SG_WINDOWS
#include "Libraries/dirent.h"
#else
#include <dirent.h>
#endif

CLevelSelect::CLevelSelect() : CGUIMenu()
{
    mButtonWidth = GameOptions::viewWidth / 2.0f;
    mButtonHeight = 50.0f;
    
    mXPos = (GameOptions::viewWidth - mButtonWidth) / 2.0f;
    mYPos = 200.0f;
    mYOffset = 70.0f;
    
    AddWidget(new CButtonWidget(mXPos, mYPos, mButtonWidth, mButtonHeight,
                                "Tutorial", std::bind(&CLevelSelect::HandleTutorialButton, this)));
    mYPos += mYOffset;
    
    ProcessLevelFiles();

    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mButtonWidth, mButtonHeight,
                                "Back", std::bind(&CLevelSelect::HandleBackButton, this)));
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mButtonWidth, mButtonHeight,
                                "Exit", std::bind(&CLevelSelect::HandleExitButton, this)));
    mYPos += mYOffset;
    
}

CLevelSelect::~CLevelSelect()
{
    
}

void CLevelSelect::ProcessLevelFiles()
{
    // Build the list of level files
    std::string thePath = SystemUtilities::GetResourcePath() + "Levels/";
    std::string fileExtension = ".xml";
    DIR *simDir;
    struct dirent *currentEntry;
    
    simDir = opendir(thePath.c_str());
    if (simDir != NULL)
    {
        // Loop through all entries in this directory
        while ((currentEntry = readdir(simDir)) != NULL)
        {
            // If this entries name ends in .xml add it to the list
            std::string filename = currentEntry->d_name;
            if (filename.length() >= fileExtension.length()
                && filename.compare(filename.length() - fileExtension.length(),
                                    fileExtension.length(),
                                    fileExtension) == 0)
            {
                // Get the level name from the xml and add that to the menu list
                filename = "Levels/" + filename;
                CLevelInterpreter i(filename);
                if (i.LoadFile())
                {
                    
                    AddWidget(new CButtonWidget(mXPos, mYPos, mButtonWidth, mButtonHeight,
                                                i.GetLevelName(),
                                                std::bind(&CLevelSelect::HandleLevelButton, this, filename)));
                    mYPos += mYOffset;
                }
            }
        }
        closedir(simDir);
    }
    else
    {
        DEBUG_LOG("Problem opening directory %s", thePath.c_str());
    }
}

void CLevelSelect::HandleLevelButton(std::string filename)
{
    DEBUG_LOG("Tutorial button pressed");
    CRayGame::Get()->PushGameLocation(new CLevel(filename));
}


void CLevelSelect::HandleTutorialButton()
{
    DEBUG_LOG("Tutorial button pressed");
    CRayGame::Get()->PushGameLocation(new CTutorialLevel());
}

void CLevelSelect::HandleBackButton()
{
    DEBUG_LOG("Back button pressed");
    CRayGame::Get()->PopGameLocation();
}

void CLevelSelect::HandleExitButton()
{
    DEBUG_LOG("Exit button pressed");
    CRayGame::Get()->ExitGame();
}