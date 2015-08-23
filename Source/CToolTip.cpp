#include "CToolTip.hpp"
#include "TextUtilties.hpp"
#include "Tweening/Easings/Back.hpp"
#include "Tweening/Easings/Sine.hpp"

CToolTip::CToolTip() : CToolTip("", 100.0f)
{
    
}

CToolTip::CToolTip(std::string theText, float yCoord)
{
    mWidth = 500.0f;
    mTextMargin = 10.0f;
    mMargin = 100.0f;
    mMaxTextWidth = mWidth - (2*mTextMargin);
    SetText(theText);
    mYCoord = yCoord;
    mLingerTime = CTime::Seconds(5.0f);
    mIsInfinite = false;
    
    Reset();
}

CToolTip::~CToolTip()
{
    
}

void CToolTip::Update(CTime elapsedTime)
{
    if (mState == kEntering || mState == kExiting)
    {
        mTweener.Advance(elapsedTime);
        UpdatePosition();
        
        if (mTweener.IsDone())
        {
            // Advance state
            SetState(mState + 1);
        }
    }
    else if (mState == kLingering)
    {
        mLingerTimeCounter += elapsedTime;
        if (mLingerTimeCounter > mLingerTime && !mIsInfinite)
        {
            // Advance state
            SetState(mState + 1);
        }
    }
}

void CToolTip::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
    theWindow->draw(mText);
}

void CToolTip::SetText(std::string theText)
{
    mText = CBoundedText(theText, mMaxTextWidth, *TextUtilities::GetFont(kFontTypeDefault), 30.0f);
    mShape = CRectangleShape(mWidth, mText.getGlobalBounds().height + (2*mTextMargin));
    mShape.setFillColor(CColour::Blue);
    UpdatePosition();
}

void CToolTip::Reset()
{
    SetState(kEntering);
}

void CToolTip::SetState(int state)
{
    switch (state)
    {
        case kEntering:
            mTweener = CTweener(Easings::Back::easeOut, -mWidth, mMargin, CTime::Seconds(1.0f));
            UpdatePosition();
            break;
        case kLingering:
            mLingerTimeCounter = CTime::Zero;
            break;
        case kExiting:
            mTweener = CTweener(Easings::Sine::easeIn, mMargin, -mWidth, CTime::Seconds(1.0f));
            break;
        case kDone:
            break;
    }
    mState = state;
}

bool CToolTip::IsEntering()
{
    return mState == kEntering;
}

bool CToolTip::IsLingering()
{
    return mState == kLingering;
}

bool CToolTip::IsExiting()
{
    return mState == kExiting;
}

bool CToolTip::IsDone()
{
    return mState == kDone;
}

void CToolTip::SetInfinite(bool isInfinite)
{
    mIsInfinite = isInfinite;
}

void CToolTip::UpdatePosition()
{
    mXCoord = mTweener.GetCurrentValue();
    CVector2f pos(mXCoord, mYCoord);
    mShape.setPosition(pos);
    
    // We need to do some shenanigans to get the text positioned right, since
    // there seems to already be a margin on the object
    CVector2f textPos(mText.getGlobalBounds().left, mText.getGlobalBounds().top);
    mText.move(pos - textPos);
    mText.move(mTextMargin, mTextMargin);
}

std::string CToolTip::GetStateString()
{
    std::string theState;
    switch (mState)
    {
        case kEntering: theState = "Entering"; break;
        case kLingering: theState =  "Lingering"; break;
        case kExiting: theState =  "Exiting"; break;
        case kDone: theState =  "Done"; break;
    }
    return theState;
}