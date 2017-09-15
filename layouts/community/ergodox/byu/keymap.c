#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define MOVE 3 // movement layer

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
};

enum custom_macros {
  VERSION,
  EEPROM,

  LSFT_TAB,
  // MacOS macros
  OSX_COPY,
  OSX_PASTE,
  TMUX_VSPLIT,
  TMUX_HSPLIT,
  OSX_INVERT,
  OSX_PS_ALL,
  OSX_PS_APP,

  //1Password 
  ONEPASS_OPEN,
};

// NOTE: Cells marked with ACCESS must remain transparent, they're the keys that actually get to that layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | MUTE |           |   6  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------| Hyper|           | Hyper|------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |LT 3,F|   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL | LAFT | LGUI | LGUI |  L1  |                                       | Left | Down |  Up  | Right|  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Copy | Paste|       |Vsplit|Hsplit|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Bcksp| Del  |------|       |------|  Ent   |Space |
 *                                 |      | /LGUI| End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,        KC_1,         KC_2,   KC_3,   KC_4,          KC_5,   KC_MUTE,
        KC_TAB,        KC_Q,         KC_W,   KC_E,   KC_R,          KC_T,   ALL_T(KC_LBRC),
        KC_ESC,        KC_A,         KC_S,   KC_D,   LT(MOVE, KC_F),KC_G,
        KC_LSPO,       CTRL_T(KC_Z), KC_X,   KC_C,   KC_V,          KC_B,   TG(MDIA),
        OSM(MOD_LCTL), KC_LALT,      KC_LGUI,KC_LGUI,TG(SYMB),
                                                                            OSX_COPY,     OSX_PASTE,
                                                                                          KC_HOME,
                                                                    KC_BSPC,GUI_T(KC_DEL),KC_END,
        // right hand
             KC_6,       KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,        KC_EQL,
             ALL_T(KC_RBRC),   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,           KC_BSLS,
                         KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,        KC_QUOT,
             MO(MDIA),   KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH), KC_RSPC,
                                 KC_LEFT,KC_DOWN,KC_UP,  KC_RIGHT,       MO(SYMB),
             TMUX_VSPLIT,TMUX_HSPLIT,
             KC_PGUP,
             KC_PGDN,    KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   (  |   )  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   {  |   }  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |   0  |   0  |   .  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | Caps |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |APScr |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      | PScr |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LPRN,KC_RPRN,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LCBR,KC_RCBR,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_CAPS,
                                               LGUI(LSFT(KC_3)),
                               KC_TRNS,KC_TRNS,LGUI(LSFT(KC_4)),
       // right hand
       KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_0,   KC_0,    KC_DOT,  KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and mouse keys
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
 *   |      |      |      | Lclk | Rclk |                                       | Prev |      |      | Next |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Back+| Back-|       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |BackTg|       | Vol+ |      |      |
 *                                 |      |      |------|       |------|      | Pl/Ps|
 *                                 |      |      |      |       | Vol- |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           BL_INC,  BL_DEC,
                                                    BL_TOGG,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_MRWD, KC_TRNS, KC_TRNS, KC_MFFD, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_VOLU,
       KC_VOLD, KC_TRNS, KC_MPLY
),
/* Keymap 4: Movement
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |1POpen|      |      |      |      |      |           |      | Copy |      |      |      | Paste|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |DLeft |DRight|LCTRL |      |      |------|           |------| Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |SFT_TB| TAB  |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MOVE] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, M(ONEPASS_OPEN),KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, LCTL(KC_LEFT),  LCTL(KC_RIGHT),KC_TRNS, KC_TRNS,
       KC_TRNS, M(LSFT_TAB),    KC_TAB,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,
                                             KC_TRNS, KC_TRNS,
                                                      KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
       KC_TRNS,  OSX_COPY,  KC_TRNS, KC_TRNS, KC_TRNS, OSX_PASTE, KC_TRNS,
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
        case OSX_COPY:
          if (record->event.pressed) {
            return MACRO(D(LGUI), T(C), U(LGUI), END);
          }
          break;
        case OSX_PASTE:
          if (record->event.pressed) {
            return MACRO(D(LGUI), T(P), U(LGUI), END);
          }
          break;
        case OSX_PS_ALL:
          if (record->event.pressed) {
            return MACRO(D(LGUI), D(LSFT), T(3), U(LSFT), U(LGUI), END);
          }
          break;
        case OSX_PS_APP:
          if (record->event.pressed) {
            return MACRO(D(LGUI), D(LSFT), T(4), U(LSFT), U(LGUI), END);
          }
          break;
        case OSX_INVERT:
          if (record->event.pressed) {
            return MACRO(D(LGUI), D(LALT), D(LCTL), T(8), U(LGUI), U(LALT), U(LCTL), END);
          }
          break;
        case TMUX_VSPLIT:
          if (record->event.pressed) {
            return MACRO(D(LCTRL), T(B), U(LCTL), D(LSFT), T(5), U(LSFT), END);
          }
          break;
        case TMUX_HSPLIT:
          if (record->event.pressed) {
            return MACRO(D(LCTRL), T(B), U(LCTL), D(LSFT), T('), U(LSFT), END);
          }
          break;
        case LSFT_TAB:
          if (record->event.pressed) {
            return MACRO(D(LSFT), T(TAB), U(LSFT), END);
          }
          break;
        case ONEPASS_OPEN:
          if (record->event.pressed) { // 1Password open application
            return MACRO(D(LGUI), T(|), U(LCTL), END);
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

