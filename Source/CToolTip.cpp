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
    float maxTextWidth = mWidth - (2*mTextMargin);
    mText = CBoundedText(theText, maxTextWidth, *TextUtilities::GetFont(kFontTypeDefault), 30.0f);
    mShape = CRectangleShape(mWidth, mText.getGlobalBounds().height + (2*mTextMargin));
    mShape.setFillColor(CColour::Blue);
    mYCoord = yCoord;
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
            mState++;
        }
    }
    else if (mState == kLingering)
    {
        mLingerTimeCounter += elapsedTime;
        if (mLingerTimeCounter > mLingerTime)
        {
            // Advance state
            mState++;
            // We're now exiting, create the exit tweener
            mTweener = CTweener(Easings::Sine::easeIn, mMargin, -mWidth, CTime::Seconds(1.0f));
        }
    }
}

void CToolTip::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
    theWindow->draw(mText);
}

void CToolTip::Reset()
{
    mTweener = CTweener(Easings::Back::easeOut, -mWidth, mMargin, CTime::Seconds(1.0f));
    mTweener.Reset();
    mState = kEntering;
    mLingerTimeCounter = CTime::Zero;
    mLingerTime = CTime::Seconds(5.0f);
}

bool CToolTip::IsDone()
{
    return mState == kDone;
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