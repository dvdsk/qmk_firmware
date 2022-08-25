#include "quantum_keycodes.h"

typedef struct RemappedPressed {
	bool left;
	bool right;
	bool up;
	bool down;
	bool lshift;
	bool rshift;
	/// a remapped key has been pressed and shift has not yet
	/// been lifted
	bool active;
} RemappedPressed;

void lift_shift(RemappedPressed* pressed) {
	if (pressed->lshift) {
		unregister_code(KC_LSFT);
		pressed->lshift = false;
	} else { // right must be the one pressed
		unregister_code(KC_RSFT);
		pressed->rshift = false;
	}
}

bool pressed_shift_remapped(uint16_t keycode, RemappedPressed* pressed) {
	switch (keycode) {
	case KC_LEFT:
		if (pressed->rshift || pressed->lshift || pressed->active) {
			pressed->left = true;
			pressed->active = true;
			lift_shift(pressed);
			register_code(KC_HOME);
			return false;
		}
		break;
	case KC_RGHT:
		if (pressed->rshift || pressed->lshift || pressed->active) {
			pressed->right = true;
			pressed->active = true;
			lift_shift(pressed);
			register_code(KC_END);
			return false;
		}
		break;
	case KC_UP:
		if (pressed->rshift || pressed->lshift || pressed->active) {
			pressed->up = true;
			pressed->active = true;
			lift_shift(pressed);
			register_code(KC_PGUP);
			return false;
		}
		break;
	case KC_DOWN:
		if (pressed->rshift || pressed->lshift || pressed->active) {
			pressed->down = true;
			pressed->active = true;
			lift_shift(pressed);
			register_code(KC_PGDN);
			return false;
		}
		break;
	}
	return true;
}

bool released_shift_remapped(uint16_t keycode, RemappedPressed* pressed) {
	switch (keycode) {
	case KC_LEFT:
		if (pressed->left) {
			pressed->left = false;
			unregister_code(KC_HOME);
			return false;
		}
		break;
	case KC_RGHT:
		if (pressed->right) {
			pressed->right = false;
			unregister_code(KC_END);
			return false;
		}
		break;
	case KC_UP:
		if (pressed->up) {
			pressed->up = false;
			unregister_code(KC_PGUP);
			return false;
		}
		break;
	case KC_DOWN:
		if (pressed->down) {
			pressed->down = false;
			unregister_code(KC_PGDN);
			return false;
		}
		break;
	}
	return true;
}

RemappedPressed remapped_pressed = {
	.left = false,
	.right = false,
	.up = false,
	.down = false,
	.lshift = false,
	.rshift = false,
	.active = false,
};

bool shift_remapped(uint16_t keycode, bool pressed) {
	switch (keycode) {
	case KC_RSFT:
		remapped_pressed.rshift = pressed;
		if (!pressed) { // released
			remapped_pressed.active = false;
		}
		return true;
	case KC_LSFT:
		remapped_pressed.lshift = pressed;
		if (!pressed) { // released
			remapped_pressed.active = false;
		}
		return true;
	}

	if (pressed) {
		return pressed_shift_remapped(keycode, &remapped_pressed);
	} 

	return released_shift_remapped(keycode, &remapped_pressed);
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
				register_code(KC_W);
			} else {
				running = false;
				unregister_code(KC_W);
			}
			return false;
		case KC_R: //stop running if we press the back key
			if (running) {
				running = false;
				unregister_code(KC_W);
			}
			return true;
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

	layer_clear();
	if (running) {
		running = false;
		unregister_code(KC_LSFT);
		unregister_code(KC_W);
	}
	return false;
}
