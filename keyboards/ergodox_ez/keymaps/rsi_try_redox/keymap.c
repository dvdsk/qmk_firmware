#include QMK_KEYBOARD_H
#include "quantum_keycodes.h"
#include "action_layer.h"
#include "version.h"
#include "rsi_try_redox.h"

#define VERSION_STRING QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
#define _______ KC_TRNS
#define X_____X KC_TRNS
#define KC_ATM LGUI(LSFT(KC_P))
#define KC_ATP LGUI(LCTL(KC_P))
#define TO_NORM TO(NORMAL_MODE)

bool altTabbing = false;
bool shiftIsOn = false;
bool running = false;
uint16_t shiftPressed;
uint16_t winManagmentPressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Colemak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  | lock   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Esc   |   q  |   w  |   f  |   p  |   g  | shift|           |reset |   j  |   l  |   u  |   y  |   ?  | tapp   |
 * |--------+------+------+------+------+------| w tgl|           |      |------+------+------+------+------+--------|
 * |   mov_W|   a  |   r  |   s  |   t  |   d  |------|           |------|   h  |   n  |   e  |   i  |   o  | alt-tab|
 * |--------+------+------+------+------+------| del  |           |  \   |------+------+------+------+------+--------|
 * | shift* |   z  |   x  |   c  |   v  |   b  |      |           |      |   k  |   m  |   ,  |   .  |   ;  | shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ctrl | alt  | gui  | Left | Right|                                       |  Up  |  Down| S-Tab| vol+ | vol- |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,------------.
 *                                        | ARRO | QWRT |       | ANSI |     |
 *                                 ,------|------|------|       |------+-----+-------.
 *                                 |      |      |MEH(c)|       |MEH(a)|     | Esc   |
 *                                 |      |      |------|       |------|     |  or   |
 *                                 | Space| BkSp | save |       |MEH(b)|enter| PROG  |
 *                                 `--------------------'       `--------------------'
 *
 * shift*: small to caps 
 *          left/right/up/down to home/end/pageup/pagedown
 *          numbers to F keys
 * mov_W:  moves windows around and gives access to function keys
 * S-TAB:  shift tab
 *
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[COLEMAK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand 
        KC_ESC,                    KC_1,       KC_2,   KC_3,     KC_4,   KC_5,   KC_NO,
        KC_ESC,                    KC_Q,       KC_W,   KC_F,     KC_P,   KC_G,   M_ARUN,
        TT(MOVEMODE),              KC_A,       KC_R,   KC_S,     KC_T,   KC_D,
        MO(COLEMAK_SHIFTED),       KC_Z,       KC_X,   KC_C,     KC_V,   KC_B,   KC_DEL,
        KC_LCTRL,                  KC_RALT,    KC_LGUI,KC_LEFT,  KC_RGHT,
                                                                          TG(ARROW), TG(QWERTY),
                                                                                     MEH_T(KC_C),
                                                                  KC_SPC, KC_BSPC,   LCTL(KC_S),
        // right hand
             KC_NO,     KC_6,   KC_7,   KC_8,   KC_9,          KC_0,             KC_NO,
             M_RESET,   KC_J,   KC_L,   KC_U,   KC_Y,          KC_SLSH,          KC_NO,
                        KC_H,   KC_N,   KC_E,   KC_I,          KC_O,             M_BAT,
             KC_BSLASH, KC_K,   KC_M,   KC_COMM,KC_DOT,        KC_SCLN,          KC_RSHIFT,
                                KC_UP,  KC_DOWN,LSFT(KC_TAB),  KC_VOLD,          KC_VOLU,
             TG(ANSI),      KC_NO,
             MEH_T(KC_A),
             MEH_T(KC_B),   KC_ENT, LT(PROGRAMMER, KC_ESC)
    ),
/* Keymap 0: COLEMAK_SHIFTED
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   F  |   P  |   G  |      |           |      |   J  |   L  |   U  |   Y  |   ?  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |      |      |   :  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Home | End  |                                       | pagUp|paDown| pause| next | prev |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,------------.
 *                                        |      |      |       |      |     |
 *                                 ,------|------|------|       |------+-----+-------.
 *                                 |      |      |      |       |      |     |       |
 *                                 |------|------|------|       |------|-----|-------|
 *                                 |      |      |      |       |      |     |       |
 *                                 `--------------------'       `--------------------'
 * 
 * shift* small to caps and left/right/up/down to home/end/pageup/pagedown
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[COLEMAK_SHIFTED] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),   KC_TRNS,
        KC_TRNS, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_F), LSFT(KC_P), LSFT(KC_G),   KC_TRNS,
        KC_TRNS, LSFT(KC_A), LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_D),
        KC_TRNS, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B),   KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_HOME,    KC_END,
                                                            KC_TRNS,  KC_TRNS,
                                                                      KC_TRNS,
                                                  KC_TRNS,  KC_TRNS,  KC_TRNS,
        // right hand
             KC_TRNS, LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),    KC_TRNS,
             KC_TRNS, LSFT(KC_J), LSFT(KC_L), LSFT(KC_U), LSFT(KC_Y), LSFT(KC_QUES), KC_TRNS,
                      LSFT(KC_H), LSFT(KC_N), LSFT(KC_E), LSFT(KC_I), LSFT(KC_O),    KC_TRNS,
             KC_TRNS, LSFT(KC_K), LSFT(KC_M), KC_TRNS,    KC_TRNS,    LSFT(KC_SCLN), KC_TRNS,
                                  KC_PGUP,    KC_PGDN,    KC_MPLY,    KC_MPRV,       KC_MNXT,
             KC_TRNS,  KC_TRNS,
             KC_TRNS,  
             KC_TRNS,  KC_TRNS,   KC_TRNS
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
        KC_TRNS,                     KC_1,        KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_TRNS,                     KC_Q,        KC_W,   KC_E,   KC_R,   KC_T,   KC_TRNS,
        LT(COLEMAK_SHIFTED, KC_NO),  KC_A,        KC_S,   KC_D,   KC_F,   KC_G,
        KC_TRNS,                     KC_Z,        KC_X,   KC_C,   KC_V,   KC_B,   KC_TRNS,
        KC_TRNS,                     KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,
                                                            KC_TRNS, KC_TRNS,
                                                                     KC_TRNS,
                                                  KC_TRNS,  KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_TRNS,
             KC_TRNS,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_TRNS,
                          KC_H,   KC_J,   KC_K,   KC_L,   KC_TRNS,  LT(COLEMAK_SHIFTED, KC_NO),
             KC_TRNS,     KC_N,   KC_M,   KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,
                                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,
             KC_TRNS,KC_TRNS,
             KC_TRNS,
             KC_TRNS,KC_TRNS, KC_TRNS
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
[QWERTY_SHIFTED] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),   KC_TRNS,
        KC_TRNS, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T),   KC_TRNS,
        KC_TRNS, LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G),
        KC_TRNS, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B),   KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_HOME,    KC_END,
                                               KC_TRNS,  KC_TRNS,
                                                                  KC_TRNS,
                                               KC_TRNS,  KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS, LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),  KC_TRNS,
             KC_TRNS, LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I), LSFT(KC_O), LSFT(KC_P),  KC_TRNS,
                      LSFT(KC_H), LSFT(KC_J), LSFT(KC_K), LSFT(KC_L), KC_TRNS,     KC_TRNS,
             KC_TRNS, LSFT(KC_N), LSFT(KC_M), KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,
                                  KC_PGUP,    KC_PGDN,    KC_TRNS,    KC_TRNS,     KC_TRNS,
             KC_TRNS, KC_TRNS,
             KC_TRNS, 
             KC_TRNS, KC_TRNS, KC_TRNS
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
/* Keymap: Arrow 
 *
* ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
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
[ARROW] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TRNS, KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
								                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, 
       KC_TRNS, KC_TRNS, KC_TRNS
    ),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(COLEMAK)                // FN1 - Momentary Layer 1 (Symbols)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // MACRODOWN only works in this function
    if (record->event.pressed) {
      switch(keycode) {
        case M_BAT:
          if(altTabbing == false){ 
            altTabbing = true;
            SEND_STRING(SS_DOWN(X_LALT));
          }
          SEND_STRING(SS_TAP(X_TAB));
          return false; // Skip all further processing of this key
          break;
        case KC_ENT:
          if(altTabbing == true){
            SEND_STRING(SS_UP(X_LALT));
            altTabbing = false;
          }
          break;
        case MAIL_END:
          SEND_STRING("Vriendelijke groet,\nDavid Kleingeld");
          return false;
          break;
        case WIN_MM:
          winManagmentPressed = record->event.time;
          return false;
          break;
        case SPSHFT:
          if (shiftPressed == 0){
            shiftPressed = record->event.time;
            shiftIsOn = true;
            layer_on(COLEMAK_SHIFTED);
          } else if ((uint16_t)(record->event.time - shiftPressed) > 300){
            //SEND_STRING(SS_TAP(X_SPC));//FIXME
          }
          break;          
        case KC_R: //stop running if we press the back key
          if (running) {
            running = false;
            unregister_code(KC_LSFT);
            unregister_code(KC_W);
          }
          return true;
        case M_ARUN:
          if (running) {
            running = false;
            unregister_code(KC_LSFT);
            unregister_code(KC_W);
          }
          return false;
      } 
    } else {//must be key release
      switch(keycode) {
        case WIN_MM:
          if((uint16_t)record->event.time-winManagmentPressed > CLOSE_WIN_INTERVAL){
            SEND_STRING(SS_LALT(SS_TAP(X_F4)));
            return false;
          } else {
            
            SEND_STRING(SS_LGUI(SS_TAP(X_H)));
            return true;
          }
        case SPSHFT:
          if (shiftIsOn){
            shiftIsOn = false;
            layer_off(COLEMAK_SHIFTED);
          } else{
            //SEND_STRING(SS_TAP(X_SPC));//FIXME
          }
          return false;
        case M_RESET:
          layer_off(PROGRAMMER);
          layer_off(QWERTY);
          layer_off(ANSI);
          layer_off(MOVEMODE);
          layer_off(COLEMAK_SHIFTED);
          layer_off(QWERTY_SHIFTED);
          layer_off(ARROW);
          layer_on(COLEMAK);

          shiftIsOn = false;
          if(altTabbing == true){ 
            altTabbing = false;
            SEND_STRING(SS_DOWN(X_LALT));
          }
          if (running) {
            running = false;
            unregister_code(KC_LSFT);
            unregister_code(KC_W);
          }
          return false;
        case M_ARUN:
          if (!running) {
            running = true;
            register_code(KC_LSFT);
            register_code(KC_W);
          }
          return false;
        break;
      }
    }
    return true; // Let QMK send the enter press/release events
};

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
        case COLEMAK:
        case COLEMAK_SHIFTED:
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

};
