#include "CLevelSelect.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CTutorialLevel.hpp"
#include "CRayGame.hpp"

CLevelSelect::CLevelSelect() : CGUIMenu()
{
    float width = GameOptions::viewWidth / 2.0f;
    float height = 50.0f;
    
    float xPos = (GameOptions::viewWidth - width) / 2.0f;
    float yPos = 200.0f;
    float yOffset = 70.0f;
    
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Tutorial", std::bind(&CLevelSelect::HandleTutorialButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Back", std::bind(&CLevelSelect::HandleBackButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Exit", std::bind(&CLevelSelect::HandleExitButton, this)));
    yPos += yOffset;
    
}

CLevelSelect::~CLevelSelect()
{
    
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