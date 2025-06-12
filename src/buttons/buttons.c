#include "buttons/buttons.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"

void InitButtonStyle(void)
{
	GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x7A1C4BFF);
	GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x1B0326FF);
	GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x1B0326FF);
	GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x1B0326FF);
	GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x1B0326FF);
	GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xEFF9D6FF);
	GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xEFF9D6FF);
	GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x1B0326FF);
	GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0x1B0326FF);
}

void DrawTitleScreenButtons(void)
{
	if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 50, 200, 100}, "PLAY")){GameplayScreen();}
	if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 170, 200, 100}, "EXIT")){game=0;}
}
