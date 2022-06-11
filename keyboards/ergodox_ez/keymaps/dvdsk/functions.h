#include "quantum_keycodes.h"

typedef struct RemappedPressed {
	bool left;
	bool right;
	bool up;
	bool down;
} RemappedPressed;


bool pressed_shift_remapped(uint16_t keycode, bool shift_held, RemappedPressed pressed) {
	switch (keycode) {
	case KC_LEFT:
		if (shift_held) {
			pressed.left = true;
			register_code(KC_HOME);
			return false;
		}
		break;
	case KC_RGHT:
		if (shift_held) {
			pressed.right = true;
			register_code(KC_END);
			return false;
		}
		break;
	case KC_UP:
		if (shift_held) {
			pressed.up = true;
			register_code(KC_PGUP);
			return false;
		}
		break;
	case KC_DOWN:
		if (shift_held) {
			pressed.down = true;
			register_code(KC_PGDN);
			return false;
		}
		break;
	}
	return true;
}

bool released_shift_remapped(uint16_t keycode, RemappedPressed pressed) {
	switch (keycode) {
	case KC_LEFT:
		if (pressed.left) {
			unregister_code(KC_HOME);
			return false;
		}
		break;
	case KC_RGHT:
		if (pressed.right) {
			unregister_code(KC_END);
			return false;
		}
		break;
	case KC_UP:
		if (pressed.up) {
			unregister_code(KC_PGUP);
			return false;
		}
		break;
	case KC_DOWN:
		if (pressed.down) {
			unregister_code(KC_PGDN);
			return false;
		}
		break;
	}
	return true;
}

bool shift_held = false;
RemappedPressed remapped_pressed = {
	.left = false,
	.right = false,
	.up = false,
	.down = false,
};

bool shift_remapped(uint16_t keycode, bool pressed) {
	switch (keycode) {
	case KC_RSFT:
	case KC_LSFT:
		shift_held = pressed;
		return true;
	}

	return true;
	if (pressed) {
		return pressed_shift_remapped(keycode, shift_held, remapped_pressed);
	} 

	return released_shift_remapped(keycode, remapped_pressed);
}

// returns true if this did nothing and QMK should 
// process the press/release events
bool running = false;
bool auto_run(uint16_t keycode, bool pressed) {
	if (pressed) {
		switch(keycode) {
		case M_ARUN:
			if (!running) {
				running = true;
				register_code(KC_LSFT);
				register_code(KC_W);
			}
			return false;
		case KC_R: //stop running if we press the back key
			if (running) {
				running = false;
				unregister_code(KC_LSFT);
				unregister_code(KC_W);
			}
			return true;
		}
	} else {
        if ((keycode == M_ARUN) && running) {
            running = false;
            unregister_code(KC_LSFT);
            unregister_code(KC_W);
			return false;
		}
	} // not pressed
	return true;
}

// returns true if this did nothing and QMK should process the press/release events
bool reset(uint16_t keycode, bool pressed) {
	if (!pressed) {
		return true;
	}

	if (keycode != M_RESET){
		return true;
	}

	shift_held = false;
	layer_clear();

	if (running) {
		running = false;
		unregister_code(KC_LSFT);
		unregister_code(KC_W);
	}
	return false;
}
