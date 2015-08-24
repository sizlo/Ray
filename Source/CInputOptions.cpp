#include "CInputOptions.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CRayGame.hpp"
#include "CGlobals.hpp"
#include "CInputListInterpreter.hpp"

CInputOptions::CInputOptions() : CGUIMenu()
{
    mWidgetWidth = GameOptions::viewWidth / 2.0f;
    mWidgetHeight = 50.0f;
    
    mXPos = (GameOptions::viewWidth - mWidgetWidth) / 2.0f;
    mYPos = 200.0f;
    mYOffset = 70.0f;
    
    mLeftWidget = new CInputWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Move Left", CGlobals::leftInput);
    AddWidget(mLeftWidget);
    mYPos += mYOffset;
    mRightWidget = new CInputWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Move Right", CGlobals::rightInput);
    AddWidget(mRightWidget);
    mYPos += mYOffset;
    mJumpWidget = new CInputWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Jump", CGlobals::jumpInput);
    AddWidget(mJumpWidget);
    mYPos += mYOffset;
    mResetWidget = new CInputWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight, "Reset Level", CGlobals::resetInput);
    AddWidget(mResetWidget);
    mYPos += mYOffset;
    
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Save", std::bind(&CInputOptions::HandleSaveButton, this)));
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Back", std::bind(&CInputOptions::HandleBackButton, this)));
    mYPos += mYOffset;
    AddWidget(new CButtonWidget(mXPos, mYPos, mWidgetWidth, mWidgetHeight,
                                "Exit", std::bind(&CInputOptions::HandleExitButton, this)));
    mYPos += mYOffset;
}

CInputOptions::~CInputOptions()
{
    
}

void CInputOptions::Update(CTime elapsedTime)
{
    CGUIMenu::Update(elapsedTime);
    
    std::list<CInput> disallowedInputs;
    disallowedInputs.push_back(mLeftWidget->GetCurrentInput());
    disallowedInputs.push_back(mRightWidget->GetCurrentInput());
    disallowedInputs.push_back(mJumpWidget->GetCurrentInput());
    disallowedInputs.push_back(mResetWidget->GetCurrentInput());
    mLeftWidget->SetDisallowedInputs(disallowedInputs);
    mRightWidget->SetDisallowedInputs(disallowedInputs);
    mJumpWidget->SetDisallowedInputs(disallowedInputs);
    mResetWidget->SetDisallowedInputs(disallowedInputs);
}

void CInputOptions::HandleSaveButton()
{
    DEBUG_LOG("Save button pressed");
    
    bool optionsChanged = false;
    
    if (CGlobals::leftInput != mLeftWidget->GetCurrentInput())
    {
        CGlobals::leftInput = mLeftWidget->GetCurrentInput();
        optionsChanged = true;
    }
    if (CGlobals::rightInput != mRightWidget->GetCurrentInput())
    {
        CGlobals::rightInput = mRightWidget->GetCurrentInput();
        optionsChanged = true;
    }
    if (CGlobals::jumpInput != mJumpWidget->GetCurrentInput())
    {
        CGlobals::jumpInput = mJumpWidget->GetCurrentInput();
        optionsChanged = true;
    }
    if (CGlobals::resetInput != mResetWidget->GetCurrentInput())
    {
        CGlobals::resetInput = mResetWidget->GetCurrentInput();
        optionsChanged = true;
    }
    
    if (optionsChanged)
    {
        SInputListEntry left;
        left.name = "left";
        left.input = CGlobals::leftInput;
        SInputListEntry right;
        right.name = "right";
        right.input = CGlobals::rightInput;
        SInputListEntry jump;
        jump.name = "jump";
        jump.input = CGlobals::jumpInput;
        SInputListEntry reset;
        reset.name = "reset";
        reset.input = CGlobals::resetInput;
        
        std::list<SInputListEntry> theList;
        theList.push_back(left);
        theList.push_back(right);
        theList.push_back(jump);
        theList.push_back(reset);
        
        CInputListInterpreter i("inputs.xml");
        i.Write(theList);
    }
}

void CInputOptions::HandleBackButton()
{
    DEBUG_LOG("Back button pressed");
    CRayGame::Get()->PopGameLocation();
}

void CInputOptions::HandleExitButton()
{
    DEBUG_LOG("Exit button pressed");
    CRayGame::Get()->ExitGame();
}