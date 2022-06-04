#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _PROGRAMMER 1
#define _COLEMAK_SHIFTED 2
#define _QWERTY 3

// enum custom_keycodes {
//   COLEMAK = SAFE_RANGE,
//   PROGRAMMER,
//   COLEMAK_SHIFTED,
//   QWERTY,
// };

// Shortcut to make keymap more readable
#define KC_LA4 LALT(KC_4)
#define KC_LA3 LALT(KC_3)
#define KC_LA2 LALT(KC_2)

#define KC_LTPR LT(_PROGRAMMER, KC_ESC)
#define KC_LSTA LSFT(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_LA4  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G    ,KC_TAB  ,                          KC_LA3  ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SLSH ,KC_LA2  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D    ,KC_DEL  ,                          KC_BSLS ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_TRNS ,KC_TRNS,         KC_TRNS ,KC_TRNS ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SCLN ,KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTRL,KC_RALT ,KC_LGUI ,KC_LEFT ,     KC_RGHT,     KC_SPC , KC_BSPC,         KC_ENT  ,KC_LTPR,     KC_UP   ,     KC_DOWN ,KC_LSTA ,KC_VOLD ,KC_VOLU
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

#define KC_PLS LSFT(KC_EQL) // existing KC_PLUS does not work on all platforms
#define KC_MUL LSFT(KC_8)
  [_PROGRAMMER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_QUOTE,KC_SLSH ,KC_PLS  ,KC_DQUO ,_______ ,                          _______ ,KC_UNDS , KC_MINS, KC_MUL ,KC_TILD ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_LBRC , KC_LCBR, KC_ESC ,KC_LPRN , KC_LT  ,_______ ,                          _______ ,KC_GT   ,KC_RPRN , KC_EQL ,KC_RCBR ,KC_RBRC ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_PIPE ,KC_GRV  ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_AMPR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,     KC_TAB ,_______ ,        _______ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,_______ ,                          _______ ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,_______ ,                          _______ ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,_______ ,_______ ,        _______ ,_______ ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
};


static bool shift_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
            shift_held = record->event.pressed;
            break;
        case KC_RSFT:
            shift_held = record->event.pressed;
            break;
		
		case KC_LEFT:
			if (shift_held) {
				register_code(KC_HOME);
				unregister_code(KC_HOME);
				return false;
			}
			break;
		case KC_RGHT:
			if (shift_held) {
				register_code(KC_END);
				unregister_code(KC_END);
				return false;
			}
			break;
		case KC_UP:
			if (shift_held) {
				register_code(KC_PGUP);
				unregister_code(KC_PGUP);
				return false;
			}
			break;
		case KC_DOWN:
			if (shift_held) {
				register_code(KC_PGDN);
				unregister_code(KC_PGDN);
				return false;
			}
			break;
	}
	return true;
}
