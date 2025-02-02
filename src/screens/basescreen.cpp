#include "basescreen.h"
#include "../dethgame.h"
#include "../player.h"
#include <iostream>

using namespace oxygine;
//dont use
BaseScreen::BaseScreen(bool debugging)
{
    setName("Base screen");
    setSize(DethGame::instance()->getMainStage()->getSize());
    show();
    setDebugging(debugging);
}

void BaseScreen::show() {}

void BaseScreen::setDebugging(bool b)
{
    if(m_debug_mode == b)
        return;

    m_debug_mode = b;

    if(m_debug_mode) {
        m_screenNameField = new TextField();
        m_screenNameField->setText(getName());
        setPosition(10, 10);
        addChild(m_screenNameField);
    } else {
        removeChild(m_screenNameField);
    }
}
