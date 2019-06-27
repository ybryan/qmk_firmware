#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // functions
#define MOUS 2 // mouse keys
#define MOVE 3 // movement layer
  
#define TABPREV LSFT(LGUI(KC_LBRC))
#define TABNEXT LSFT(LGUI(KC_RBRC))
#define PREVSC LCTL(KC_LEFT)
#define NEXTSC LCTL(KC_RIGHT)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// NOTE: Cells marked with ACCESS must remain transparent, they're the keys that actually get to that layer
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  =     |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  | LT3, \ |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Cmd/Esc |   A  |   S  |   D  |LT3, F|   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |LAlt/`|  [   |    ]  | L1   |                                       | Left | Down |  Up  | Right|  L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,--------------.       ,-------------.
 *                                      |  Cmd  |  `   |       | VolD | VolU |
 *                               ,------|-------|------|       |------+--------+------.
 *                               |      |       | Caps |       | Mute |        |      |
 *                               | Bcksp|  Tab  |------|       |------|  Ent   |Space |
 *                               |      |       | Hyper|       | Meh  |        |      |
 *                               `---------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,        KC_1,         KC_2,   KC_3,         KC_4,          KC_5,   KC_TRNS,
        KC_DEL,        KC_Q,         KC_W,   KC_E,         KC_R,          KC_T,   KC_TRNS,
        GUI_T(KC_ESC), KC_A,         KC_S,   KC_D,         LT(MOVE, KC_F),KC_G,
        KC_LSPO,       KC_Z,         KC_X,   KC_C,         KC_V,          KC_B,   KC_TRNS, 
        KC_LCTL,       ALT_T(KC_GRV),KC_LBRC,KC_RBRC,      TT(SYMB),
                                                              KC_LGUI,KC_GRV,
                                                                      KC_CAPS,
                                               KC_BSPC,       KC_TAB, KC_HYPR,
        // right hand
        KC_TRNS,       KC_6,   KC_7,         KC_8,         KC_9,       KC_0,        KC_MINS,
        KC_TRNS,       KC_Y,   KC_U,         KC_I,         KC_O,       KC_P,        LT(MOVE, KC_BSLS),
                       KC_H,   KC_J,         KC_K,         KC_L,       KC_SCLN,     KC_QUOT,
        KC_TRNS,       KC_N,   KC_M,         KC_COMM,      KC_DOT,     KC_SLSH,     KC_RSPC,
                               KC_LEFT,      KC_DOWN,      KC_UP,      KC_RIGHT,    TT(MOUS),
        KC_VOLD,       KC_VOLU,
        KC_MUTE,
        KC_MEH,        KC_ENT, KC_SPC
),

/* Keymap 1: Function Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   1  |   2  |   3  |   4  |   5  |------|           |------|   6  |   7  |   8  |   9  |   0  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  F11 | F12  |      |      |      |      |           |      |   `  |  [   |    ]  |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

// SYMBOLS
[SYMB] = LAYOUT_ergodox(
// left hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_TRNS,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   
    KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS,KC_TRNS,
                                                    KC_TRNS,
                                                    KC_TRNS,KC_TRNS,KC_TRNS,
    
// right hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS, KC_GRV,  KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,      KC_TRNS,
    KC_TRNS,       
    KC_TRNS,      KC_TRNS, KC_TRNS
),

/* Keymap 2: Mouse
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MOUSE
[MOUS] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_MS_U,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L,     KC_MS_D,    KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,
                                                           KC_TRNS, KC_TRNS,
                                                                    KC_TRNS,
                                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Movement
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET | VRSN |EEPROM|      |      |      |      |           |      |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | PgDn | PgUp |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |PrevSC|NextSC|      |      |------|           |------| Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | TabP | TabN | Home | End  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |EJECT |      |POWER | WAKE |SLEEP |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MOVEMENT
[MOVE] = LAYOUT_ergodox(
       RESET,   VRSN,           EPRM,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        PREVSC,         NEXTSC,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_EJCT, KC_TRNS,        KC_WAKE,        KC_SLEP, KC_TRNS, 
                                             KC_TRNS, KC_TRNS,
                                                      KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   RESET,
       KC_TRNS,  KC_TRNS,   KC_PGDN, KC_PGUP, KC_TRNS, KC_TRNS,   KC_TRNS,
                 KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,   TABPREV, TABNEXT, KC_HOME, KC_END,    KC_TRNS,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
)
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
