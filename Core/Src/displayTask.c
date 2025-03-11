#include "displayTask.h"
#include "joystickTask.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

#include <stdio.h>
#include <stdint.h>

void displayTaskSetup() {
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	//ssd1306_WriteString("Hello world!", Font_7x10, White);
}

void displayTaskExecute() {
	ssd1306_SetCursor(0, 0);
	char buf[10];
	snprintf(buf, 10, "X: %u ", getX());
	ssd1306_WriteString(buf, Font_7x10, White);

	ssd1306_SetCursor(0, 15);
	char buf2[10];
	snprintf(buf2, 10, "Y: %u ", getY());
	ssd1306_WriteString(buf2, Font_7x10, White);

	ssd1306_UpdateScreen();
}
