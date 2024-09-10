#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>


Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}


void Screen1Presenter::zmagovalec(int zmagovalec) {
	model->zmagovalec(zmagovalec);
}

void Screen1Presenter::pomagaj() {
	view.pomocpls();
}

void Screen1Presenter::openWindow() {
	view.openWindow();
}
