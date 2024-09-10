#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "cmsis_os.h"


extern "C"
{
	extern osMessageQueueId_t buttonQueueHandle;
}

int maxDelay = 100;
bool jezmagovalec = false;
int currDelay = 0;
int test = 0;


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	checkzmagovalec();

	osStatus_t status = osMessageQueueGet(buttonQueueHandle, &pinstate, NULL, 0);
	if (status == osOK) {
		if (pinstate == 1) {
			modelListener->openWindow();
		}
	}
}

void Model::zmagovalec(int zmagovalec) {
	jezmagovalec = true;
	currDelay = maxDelay;
}

void Model::checkzmagovalec() {
	if (!jezmagovalec) {
		return;
	}
	if (currDelay > 0) {
		currDelay--;
		return;
	}
	jezmagovalec = false;
	test++;
	modelListener->pomagaj();
}


