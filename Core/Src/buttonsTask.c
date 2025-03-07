#include "buttonsTask.h"
#include "buttons.h"
#include "rgb.h"

void buttonsTaskSetup() {
	buttons_init();
}

void button_task_execute() {
	buttons_update();

	if (buttons_checkButton(UP) == PUSHED)
		rgb_led_toggle(RGB_UP);

	if (buttons_checkButton(DOWN) == PUSHED)
		rgb_led_toggle(RGB_DOWN);

	if (buttons_checkButton(LEFT) == PUSHED)
		rgb_led_toggle(RGB_LEFT);

	if (buttons_checkButton(RIGHT) == PUSHED)
		rgb_led_toggle(RGB_RIGHT);
}
