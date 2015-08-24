#include "CGlobals.hpp"

float CGlobals::playerSize = 50.0f;
float CGlobals::switchSize = 40.0f;
CVector2f CGlobals::gravity = CVector2f(0.0f, 3000.0f);

CInput CGlobals::leftInput = CInput(CKeyboard::A);
CInput CGlobals::rightInput = CInput(CKeyboard::D);
CInput CGlobals::jumpInput = CInput(CKeyboard::Space);
CInput CGlobals::resetInput = CInput(CKeyboard::R);