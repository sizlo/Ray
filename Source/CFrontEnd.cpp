#include "CFrontEnd.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CRayGame.hpp"
#include "CLevelSelect.hpp"
#include "CVideoOptions.hpp"
#include "CInputOptions.hpp"

CFrontEnd::CFrontEnd() : CGUIMenu()
{
    float width = GameOptions::viewWidth / 2.0f;
    float height = 50.0f;
    
    float xPos = (GameOptions::viewWidth - width) / 2.0f;
    float yPos = 200.0f;
    float yOffset = 70.0f;
    
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Play", std::bind(&CFrontEnd::HandlePlayButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Video Options", std::bind(&CFrontEnd::HandleVideoOptionsButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Input Options", std::bind(&CFrontEnd::HandleInputOptionsButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Exit", std::bind(&CFrontEnd::HandleExitButton, this)));
    yPos += yOffset;
    
}

CFrontEnd::~CFrontEnd()
{
    
}

void CFrontEnd::HandlePlayButton()
{
    DEBUG_LOG("Play button pressed");
    CRayGame::Get()->PushGameLocation(new CLevelSelect());
}

void CFrontEnd::HandleVideoOptionsButton()
{
    DEBUG_LOG("Video Options button pressed");
    CRayGame::Get()->PushGameLocation(new CVideoOptions());
}

void CFrontEnd::HandleInputOptionsButton()
{
    DEBUG_LOG("Input Options button pressed");
    CRayGame::Get()->PushGameLocation(new CInputOptions());
}

void CFrontEnd::HandleExitButton()
{
    DEBUG_LOG("Exit button pressed");
    CRayGame::Get()->ExitGame();
}