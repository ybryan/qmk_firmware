#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
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
};

enum custom_macros {
  VERSION,
  EEPROM,

  OSX_PS_ALL,
  OSX_PS_APP,
};

// NOTE: Cells marked with ACCESS must remain transparent, they're the keys that actually get to that layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | PgDn |           | PgUp |   6  |   7  |   8  |   9  |   0  |  CAPS  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |LT3, Y|   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|Hyper |           | Meh  |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |LT3, F|   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  L1  |           |  L2  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL | LAFT | LGUI | LED  |L1MUTE|                                       | Left | Down |  Up  | Right|  L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | VolD | VolU |       | TabP | TabN |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  F3  |       |  F4  |        |      |
 *                                 | Bcksp| Del/ |------|       |------|  Ent   |Space |
 *                                 |      | Gui  |  -   |       |  =   |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,        KC_1,   KC_2,   KC_3,   KC_4,             KC_5,         KC_PGDN,
        KC_TAB,        KC_Q,   KC_W,   KC_E,   KC_R,             KC_T,         ALL_T(KC_LBRC),
        KC_ESC,        KC_A,   KC_S,   KC_D,   LT(MOVE, KC_F),   KC_G,
        KC_LSPO,       KC_Z,   KC_X,   KC_C,   KC_V,             KC_B,         TT(SYMB),
        KC_LCTL,       KC_LALT,KC_LGUI,BL_STEP,LT(SYMB, KC_MUTE),
                                                                 KC_VOLD,      KC_VOLU,
                                                                               KC_F3,
                                               KC_BSPC,          GUI_T(KC_DEL),KC_MINS,
        // right hand
        KC_PGUP,       KC_6,          KC_7,   KC_8,   KC_9,  KC_0,KC_CAPS,
        MEH_T(KC_RBRC),LT(MOVE, KC_Y),KC_U,   KC_I,   KC_O,  KC_P,KC_BSLS,
                       KC_H,          KC_J,   KC_K,   KC_L,  KC_SCLN,     KC_QUOT,
        TT(MOUS),      KC_N,          KC_M,   KC_COMM,KC_DOT,KC_SLSH,     KC_RSPC,
                                      KC_LEFT,KC_DOWN,KC_UP, KC_RIGHT,    MO(MOUS),
        TABPREV,       TABNEXT,
        KC_F4,
        KC_EQL,        KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   (  |   )  |   |  |      |           |      |      |   7  |   8  |   9  |   \  |  F12   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   {  |   }  |   `  |------|           |------|      |   4  |   5  |   6  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |      |   1  |   2  |   3  |   -  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |   &  |   *  |      |      |                                       |   0  |   0  |   .  |   +  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |APScr |       |PrScr |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LPRN,KC_RPRN,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LCBR,KC_RCBR,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_AMPR,KC_ASTR,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               M(OSX_PS_APP),
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_TRNS,KC_7,   KC_8,    KC_9,    KC_BSLS, KC_F12,
                KC_TRNS,KC_4,   KC_5,    KC_6,    KC_ASTR, KC_TRNS,
       KC_TRNS, KC_TRNS,KC_1,   KC_2,    KC_3,    KC_MINS, KC_TRNS,
                        KC_0,   KC_0,    KC_DOT,  KC_PLUS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       M(OSX_PS_ALL),
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Mouse
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |ScrolD|ScrolU|      |      |        |
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
                 KC_TRNS, KC_WH_U,    KC_WH_D,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Movement
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |PrevSC|NextSC|      |      |------|           |------| Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
       RESET,   KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        PREVSC,         NEXTSC,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_EJCT, KC_TRNS,        KC_WAKE,        KC_SLEP, KC_TRNS, 
                                             KC_TRNS, KC_TRNS,
                                                      KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   RESET,
       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
                 KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
)
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case VERSION:
          if (record->event.pressed) {
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
          }
          break;
        case EEPROM:
          if (record->event.pressed) { // For resetting EEPROM
            eeconfig_init();
          }
          break;
        case OSX_PS_ALL:
          if (record->event.pressed) {
            return MACRO(D(LSFT), D(LGUI), T(3), U(LGUI), U(LSFT), END);
          }
          break;
        case OSX_PS_APP:
          if (record->event.pressed) {
            return MACRO(D(LSFT), D(LGUI), T(4), U(LGUI), U(LSFT), END);
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
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    ergodox_board_led_on();
    ergodox_led_all_on();
};

