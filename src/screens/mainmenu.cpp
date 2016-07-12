#include "mainmenu.h"
#include "../dethgame.h"

#define GAP_SIZE 50

MainMenu::MainMenu()
{
    setName("Menu");
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    // Background
    spSprite background = new Sprite();
    background->setResAnim(m_resources->getResAnim("main_menu_bg"));
    background->setSize(getSize());
    float scale_factor = getWidth() / m_resources->getResAnim("main_menu_bg")->getWidth();
    background->setScale(scale_factor);
    background->attachTo(this);

    //Buttons
    //start button
    spImageButton btn = new ImageButton(m_resources->getResAnim("start"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor, GAP_SIZE + getHeight()/2);
    btn->addEventListener(TouchEvent::CLICK, CLOSURE(DethGame::instance(),&DethGame::startGame));
    btn->attachTo(this);
    //rules button
    btn = new ImageButton(m_resources->getResAnim("rules"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor, GAP_SIZE + getHeight()/2 + btn->getHeight()*scale_factor);
    btn->attachTo(this);
    //options button
    btn = new ImageButton(m_resources->getResAnim("options"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor, GAP_SIZE + getHeight()/2 + 2*btn->getHeight()*scale_factor);
    btn->addEventListener(TouchEvent::CLICK, CLOSURE(DethGame::instance(), &DethGame::optionsScreen));
    btn->attachTo(this);
    //exit button
    btn = new ImageButton(m_resources->getResAnim("exit"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor, GAP_SIZE + getHeight()/2 + 3*btn->getHeight()*scale_factor);
    btn->attachTo(this);

    // Tmp
    // btn->addClickListener([](){ DethGame::instance()->quit(); });
}



MainMenu::~MainMenu()
{
    m_resources->free();
    delete m_resources;
}
