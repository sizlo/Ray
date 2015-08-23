#include "CVideoOptions.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CRayGame.hpp"
#include <math.h>

CVideoOptions::CVideoOptions() : CGUIMenu()
{
    mWidgetWidth = GameOptions::viewWidth / 2.0f;
    mWidgetHeight = 50.0f;
    
    mXPos = (GameOptions::viewWidth - mWidgetWidth) / 2.0f;
    mYPos = 200.0f;
    mYOffset = 70.0f;
    
    mFullscreenWidget = new CToggleWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Fullscreen", GameOptions::fullscreen);
    AddWidget(mFullscreenWidget);
    mYPos += mYOffset;
    mVsyncWidget = new CToggleWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Vsync", GameOptions::doVsync);
    AddWidget(mVsyncWidget);
    mYPos += mYOffset;
    mPreserveAspectWidget = new CToggleWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Preserve Aspect Ratio", GameOptions::preserveAspect);
    AddWidget(mPreserveAspectWidget);
    mYPos += mYOffset;
    
    int aaIndex;
    switch (GameOptions::antiAliasingLevel)
    {
        case 0: aaIndex = 0; break;
        case 2: aaIndex = 1; break;
        case 4: aaIndex = 2; break;
        case 8: aaIndex = 3; break;
        default: aaIndex = 0; break;
    }
    mAAWidget = new CPickerWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "AA Level", aaIndex);
    mAAWidget->AddOption("0");
    mAAWidget->AddOption("2");
    mAAWidget->AddOption("4");
    mAAWidget->AddOption("8");
    AddWidget(mAAWidget);
    mYPos += mYOffset;
    
    mResolutionWidget = new CPickerWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Resolution", 0);
    std::set<CVideoMode> modes = CVideoMode::GetModes();
    int i = 0;
    for (auto m : modes)
    {
        mResolutionWidget->AddOption(m.AsString());
        if (m.width == GameOptions::windowWidth && m.height == GameOptions::windowHeight)
        {
            mResolutionWidget->SetCurrentIndex(i);
        }
        i++;
    }
    AddWidget(mResolutionWidget);
    mYPos += mYOffset;
    
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Save", std::bind(&CVideoOptions::HandleSaveButton, this)));
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Back", std::bind(&CVideoOptions::HandleBackButton, this)));
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Exit", std::bind(&CVideoOptions::HandleExitButton, this)));
    mYPos += mYOffset;
}

CVideoOptions::~CVideoOptions()
{
    
}

void CVideoOptions::HandleSaveButton()
{
    DEBUG_LOG("Save button pressed");
    bool optionsChanged = false;
    
    if (mFullscreenWidget->GetValue() != GameOptions::fullscreen)
    {
        GameOptions::fullscreen = mFullscreenWidget->GetValue();
        optionsChanged = true;
    }
    if (mVsyncWidget->GetValue() != GameOptions::doVsync)
    {
        GameOptions::doVsync = mVsyncWidget->GetValue();
        optionsChanged = true;
    }
    if (mPreserveAspectWidget->GetValue() != GameOptions::preserveAspect)
    {
        GameOptions::preserveAspect = mPreserveAspectWidget->GetValue();
        optionsChanged = true;
    }
    
    int aaIndex = mAAWidget->GetCurrentIndex();
    int aaLevel;
    switch (aaIndex)
    {
        case 0: aaLevel = 0; break;
        case 1: aaLevel = 2; break;
        case 2: aaLevel = 4; break;
        case 3: aaLevel = 8; break;
    }
    if (aaLevel != GameOptions::antiAliasingLevel)
    {
        GameOptions::antiAliasingLevel = aaLevel;
        optionsChanged = true;
    }
    
    std::set<CVideoMode> modes = CVideoMode::GetModes();
    int i = 0;
    for (auto m: modes)
    {
        if (i == mResolutionWidget->GetCurrentIndex())
        {
            if (m.width != GameOptions::windowWidth || m.height != GameOptions::windowHeight)
            {
                GameOptions::windowWidth = m.width;
                GameOptions::windowHeight = m.height;
                optionsChanged = true;
            }
        }
        i++;
    }
    
    if (optionsChanged)
    {
        DEBUG_LOG("Updating");
        CRayGame::Get()->CreateWindow();
        GameOptions::WriteConfig();
    }
}

void CVideoOptions::HandleBackButton()
{
    DEBUG_LOG("Back button pressed");
    CRayGame::Get()->PopGameLocation();
}

void CVideoOptions::HandleExitButton()
{
    DEBUG_LOG("Exit button pressed");
    CRayGame::Get()->ExitGame();
}