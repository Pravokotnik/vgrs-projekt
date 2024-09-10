#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // moji funkciji
    virtual void botgamemode();
    virtual void prgamemode();

    virtual void function1();
    virtual void function2();
    virtual void function3();
    virtual void function4();
    virtual void function5();
    virtual void function6();
    virtual void function7();
    virtual void function8();
    virtual void function9();

    virtual void gumbfunkcija();
    void pomocpls();
    virtual void botigra();

    virtual void colorbutton1();
    virtual void colorbutton2();
    virtual void colorbutton3();
    virtual void colorbutton4();
    virtual void colorbutton5();
    virtual void colorbutton6();
    virtual void colorbutton7();
    virtual void colorbutton8();
    virtual void colorbutton9();

    virtual void netouchablegumbi();
    virtual void touchablegumbi();

    virtual void openWindow();

protected:
};

#endif // SCREEN1VIEW_HPP
