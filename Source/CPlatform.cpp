#include "CPlatform.hpp"

CPlatform::CPlatform(CVector2f topLeft, float width, float height)
: CLevelBlock(topLeft, width, height, CColour::Black)
{
    
}

CPlatform::~CPlatform()
{
    
}

void CPlatform::Update(CTime elapsedTime)
{
    // Do nothing
}