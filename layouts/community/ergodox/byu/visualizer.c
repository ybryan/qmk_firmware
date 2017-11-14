/*
Note: this is a modified copy of ../default/visualizer.c, originally licensed GPL.
*/

#include "simple_visualizer.h"

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    // LCD_COLOR(  0,   0, 255); // White  <> RGB(255,255,255)                   
    // LCD_COLOR( 85, 255, 255); // Green  <> RGB(  0,255,255)                   
    // LCD_COLOR(  0, 255, 255); // Red    <> RGB(255,  0,255)                   
    // LCD_COLOR(170, 255, 255); // Blue   <> RGB(  0,  0,255)                   
    // LCD_COLOR(213, 255, 255); // Purple <> RGB(255,  0,255)                   
    // LCD_COLOR( 42, 255, 255); // Yellow <> RGB(255,  0,255)                   
    // LCD_COLOR(128, 255, 255); // Aqua   <> RGB(  0,255,255)    
    uint8_t saturation = 0;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 60;
    }
    if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(42, saturation, 255);
        state->layer_text = "3 - MOVEMENT";
    } else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(170, 255, 255);
        state->layer_text = "2 - MOUSE";
    } else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(85, 255, 255);
        state->layer_text = "1 - FUNCTIONS";
    } else {
        state->target_lcd_color = LCD_COLOR(0, 0, 255);
        state->layer_text = "DEFAULT";
    }
}
