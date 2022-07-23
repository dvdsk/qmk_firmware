#include QMK_KEYBOARD_H
#include "quantum_keycodes.h"
#include "action_layer.h"
#include "version.h"
#include "dvdsk.h"
#include "functions.h"

#define VERSION_STRING QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Colemak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  | A(7) |           | A(5) |   6  |   7  |   8  |   9  |   0  | reset  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |shftwtgl|   q  |   w  |   f  |   p  |   g  | tab  |           | A(3) |   j  |   l  |   u  |   y  |   ?  | A(4)   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  mov_W |   a  |   r  |   s  |   t  |   d  |------|           |------|   h  |   n  |   e  |   i  |   o  | alt-tab|
 * |--------+------+------+------+------+------| del  |           |  \   |------+------+------+------+------+--------|
 * | shift  |   z  |   x  |   c  |   v  |   b  |      |           |      |   k  |   m  |   ,  |   .  |   ;  | shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ctrl | alt  | gui  | Left | Right|                                       |  Up  |  Down| S-Tab| vol+ | vol- |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,------------.
 *                                        | A(8) | QWRT |       | ANSI | A(2)|
 *                                 ,------|------|------|       |------+-----+-------.
 *                                 |      |      | A(6) |       | A(1) |     | Esc   |
 *                                 |      |      |------|       |------|     |  or   |
 *                                 | Space| BkSp | save |       | A(0) |enter| PROG  |
 *                                 `--------------------'       `--------------------'
 *
 * shift:   small to caps 
 *          left/right/up/down to home/end/pageup/pagedown
 *          (done via custom layer)
 * mov_W:  moves windows around and gives access to function keys
 * S-TAB:  shift tab
 *
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[COLEMAK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand 
        KC_ESC,        KC_1,       KC_2,   KC_3,     KC_4,   KC_5,   LALT(KC_7),
        M_ARUN,        KC_Q,       KC_W,   KC_F,     KC_P,   KC_G,   KC_TAB,
        TT(MOVEMODE),  KC_A,       KC_R,   KC_S,     KC_T,   KC_D,
        KC_LSFT,       KC_Z,       KC_X,   KC_C,     KC_V,   KC_B,   KC_DEL,
        KC_LCTRL,      KC_RALT,    KC_LGUI,KC_LEFT,  KC_RGHT,
                                                                       LALT(KC_8),   TG(QWERTY),
                                                                                     LALT(KC_6),
                                                                  KC_SPC, KC_BSPC,   LCTL(KC_S),
        // right hand
             LALT(KC_5),  KC_6,   KC_7,   KC_8,   KC_9,          KC_0,      LALT(KC_4),
             LALT(KC_3),  KC_J,   KC_L,   KC_U,   KC_Y,          KC_SLSH,   LALT(KC_2),
                          KC_H,   KC_N,   KC_E,   KC_I,          KC_O,      M_BAT,
             KC_BSLASH,   KC_K,   KC_M,   KC_COMM,KC_DOT,        KC_SCLN,   KC_RSHIFT,
                                  KC_UP,  KC_DOWN,LSFT(KC_TAB),  KC_VOLD,   KC_VOLU,
             TG(ANSI),     M_RESET,
             LALT(KC_1),
             LALT(KC_0),   KC_ENT, LT(PROGRAMMER, KC_ESC)
    ),

/* Keymap 1: Programmer 
 *
*  ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  '   |   /  |   +  |  "   |      |           |      |  _   |  -   |  *   |  ~   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   [  |   {  |  ESC |  (   |  <   |------|           |------|  >   |  )   |   =  |   }  |   ]  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |   |  |  `   |      |      |           |      |      |      |   &  |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                          ,-------------.       ,-------------.
 *                                          |      |      |       |      |      |
 *                                 ,--------|------|------|       |------+------+----------.
 *                                 |        |      |      |       |      |      |          |
 *                                 |--------|------|------|       |------|------|----------|
 *                                 | tab    | del  | save |       |      |      |          |
 *                                 `----------------------'       `------------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[PROGRAMMER] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_QUOT, KC_SLSH, LSFT(KC_EQL), KC_DQUO, KC_TRNS,
       KC_TRNS, KC_LBRC, KC_LCBR, KC_ESC,  KC_LPRN,      KC_LT,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_PIPE, KC_GRV,       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS,      KC_TRNS,
                                                         KC_TRNS,
                                  KC_TAB,  KC_DEL,       KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_UNDS, KC_MINS, LSFT(KC_8), KC_TILD, KC_TRNS, KC_TRNS,
                 KC_GT,   KC_RPRN, KC_EQL,     KC_RCBR, KC_RBRC, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_AMPR,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 2: Qwerty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |------|------|------|       |------|--------|------|
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_TRNS,      KC_1,        KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_TRNS,      KC_Q,        KC_W,   KC_E,   KC_R,   KC_T,   KC_TRNS,
        KC_TRNS,     KC_A,        KC_S,   KC_D,   KC_F,   KC_G,
        KC_TRNS,      KC_Z,        KC_X,   KC_C,   KC_V,   KC_B,   KC_TRNS,
        KC_TRNS,      KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,
                                                            KC_TRNS, KC_TRNS,
                                                                     KC_TRNS,
                                                  KC_TRNS,  KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_TRNS,
             KC_TRNS,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_TRNS,
                          KC_H,   KC_J,   KC_K,   KC_L,   KC_TRNS,  KC_TRNS,
             KC_TRNS,     KC_N,   KC_M,   KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,
                                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,
             KC_TRNS,KC_TRNS,
             KC_TRNS,
             KC_TRNS,KC_TRNS, KC_TRNS
    ),

/* Keymap 3: ANSI_MODIFIERS 
 *
* ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  esc   |      |      |      |      |      |      |           |      |      |      |      |      |      | backsp |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  tab   |      |      |      |      |      |      |           |      |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  caps  |      |      |      |      |      |------|           |------|      |      |      |      |      |  entr  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | lshift |      |      |      |      |      |      |           |      |      |      |      |      |      | rshift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | lctl | lgui | lalt |      |      |                                       |      |      | ralt | rgui | rctl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+----------.
 *                                 |      |      |      |       |      |      |          |
 *                                 |------|------|------|       |------|------|----------|
 *                                 |      |      |      |       |      |      |          |
 *                                 `--------------------'       `------------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[ANSI] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
       KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
								                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,
                          KC_TRNS, KC_TRNS, KC_RALT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 4: Move window and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |guiNp7|guiNp8|guiNp9|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------| m/cls|guiNp4|guiNp5|guiNp6|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |guiNp1|guiNp2|guiNp3|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       | MsAc2| MsAc1| MsAc0|      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |------|------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * TODO implement another layer from this layer to do normal numpad, add minimise and close window (movement to other workspaces)
 */
// MEDIA AND MOUSE
[MOVEMODE] = LAYOUT_ergodox(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
								                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_F7,    KC_F8,   KC_F9,      KC_F10,     KC_F11,     KC_F12,  KC_TRNS,
       KC_TRNS,  KC_TRNS, LGUI(KC_P7),LGUI(KC_P8),LGUI(KC_P9),KC_TRNS, KC_TRNS,
                 WIN_MM,  LGUI(KC_P4),LGUI(KC_P5),LGUI(KC_P6),KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, LGUI(KC_P1),LGUI(KC_P2),LGUI(KC_P3),KC_TRNS, KC_TRNS,
                          KC_ACL2,    KC_ACL1,    KC_ACL0,    KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS
),
};


// returns true if this did nothing and QMK should process the press/release events
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	if (!shift_remapped(keycode, record->event.pressed)) {
		return false;
	}
	if (!auto_run(keycode, record->event.pressed)) {
		return false;
	}
	if (!reset(keycode, record->event.pressed)) {
		return false;
	}

    return true;
};


// Runs on any layer change
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case COLEMAK:
            break;
        case PROGRAMMER:
            ergodox_right_led_1_on();
            break;
        case QWERTY:
            ergodox_right_led_2_on();
            break;
        case ANSI:
            ergodox_right_led_3_on();
            break;
        case MOVEMODE:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

	return state;
};
