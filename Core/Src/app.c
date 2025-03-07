#include "gpio.h"
#include "rgb.h"
#include "buttons.h"
#include "adc.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 2)
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 100)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 150)

static uint32_t blinkyTaskNextRun = 0;
static uint32_t buttonTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;

static uint16_t raw_adc[2];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

void joystick_task_execute() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void blinky_task_execute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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

void app_main(void) {
	uint32_t ticks = HAL_GetTick();

	if (ticks > blinkyTaskNextRun) {
		blinky_task_execute();
		blinkyTaskNextRun += BLINKY_TASK_PERIOD_TICKS;
	}

	if (ticks > buttonTaskNextRun) {
		button_task_execute();
		buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
	}

	if (ticks > joystickTaskNextRun) {
		joystick_task_execute();
		joystickTaskNextRun += JOYSTICK_TASK_PERIOD_TICKS;
	}
}

void app_setup(void) {
	rgb_led_all_off();
	rgb_colour_all_on();
	buttons_init();

	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
}
