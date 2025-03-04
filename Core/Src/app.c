#include "gpio.h"
#include "rgb.h"
#include "buttons.h"

void app_main(void) {
	buttons_update();

	HAL_Delay(10);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	if (buttons_checkButton(UP) == PUSHED)
		rgb_led_toggle(RGB_UP);

	if (buttons_checkButton(DOWN) == PUSHED)
			rgb_led_toggle(RGB_DOWN);

	if (buttons_checkButton(LEFT) == PUSHED)
			rgb_led_toggle(RGB_LEFT);

	if (buttons_checkButton(RIGHT) == PUSHED)
			rgb_led_toggle(RGB_RIGHT);
}

void app_setup(void) {
	rgb_led_all_off();
	rgb_colour_all_on();
	buttons_init();
}
