#include "CToolTip.hpp"
#include "TextUtilties.hpp"
#include "Tweening/Easings/Elastic.hpp"

CToolTip::CToolTip() : CToolTip("", 100.0f)
{
    
}

CToolTip::CToolTip(std::string theText, float yCoord)
{
    float width = 500.0f;
    mTextMargin = 10.0f;
    mMargin = 100.0f;
    float maxTextWidth = width - (2*mTextMargin);
    mText = CBoundedText(theText, maxTextWidth, *TextUtilities::GetFont(kFontTypeDefault), 30.0f);
    mShape = CRectangleShape(width, mText.getGlobalBounds().height + (2*mTextMargin));
    mShape.setFillColor(CColour::Blue);
    mYCoord = yCoord;
    mTweener = CTweener(Easings::Elastic::easeOut, -width, mMargin, CTime::Seconds(2.0f));
}

CToolTip::~CToolTip()
{
    
}

void CToolTip::Update(CTime elapsedTime)
{
    mTweener.Advance(elapsedTime);
    UpdatePosition();
}

void CToolTip::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
    theWindow->draw(mText);
}

void CToolTip::Reset()
{
    mTweener.Reset();
}

void CToolTip::UpdatePosition()
{
    float xCoord = mTweener.GetCurrentValue();
    CVector2f pos(xCoord, mYCoord);
    mShape.setPosition(pos);
    
    // We need to do some shenanigans to get the text positioned right, since
    // there seems to already be a margin on the object
    CVector2f textPos(mText.getGlobalBounds().left, mText.getGlobalBounds().top);
    mText.move(pos - textPos);
    mText.move(mTextMargin, mTextMargin);
}