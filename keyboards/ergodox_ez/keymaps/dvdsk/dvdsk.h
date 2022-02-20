#include "config.h"
#include "print.h"
#include "keycode.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#define NOR_MOD TO(NORMAL_MODE)
#define INS_MOD TO(INSERT_MODE)

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define PREVENT_STUCK_MODIFIERS


#define CLOSE_WIN_INTERVAL 300
enum macroKeycodes {
  M_BAT = SAFE_RANGE, //begin alt tab
  M_EAT,              //end alt-tab
  MAIL_END,
  WIN_MM,
  TAPP,
  SPSHFT,
  M_RESET,
  M_ARUN
};
