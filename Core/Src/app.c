#include "gpio.h"
#include "rgb.h"

void app_main(void) {
  HAL_Delay(200);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
  {
	rgb_led_on(RGB_UP);
  }
  else
  {
	rgb_led_off(RGB_UP);
  }

  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
    {
  	rgb_led_on(RGB_DOWN);
    }
    else
    {
  	rgb_led_off(RGB_DOWN);
    }

  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10))
    {
  	rgb_led_on(RGB_RIGHT);
    }
    else
    {
  	rgb_led_off(RGB_RIGHT);
    }

  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
    {
  	rgb_led_off(RGB_LEFT);
    }
    else
    {
  	rgb_led_on(RGB_LEFT);
    }
}

void app_setup(void) {
	rgb_led_all_off();
	rgb_colour_all_on();
}
