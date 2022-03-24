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

const char* linkedin_nl_yes = "Beste <name>,\n"
"\n"
"Leuk! Ik ben nu vrij ver in een sollicitatie voor een functie die 6k pm oplevert. Indien jullie een voor mij competitief salaris bieden maak ik graag tijd voor je vrij. En anders wens ik je veel succes met je zoektocht.\n"
"\n"
"Vriendelijke groet,\n"
"David Kleingeld\n"
"http://davidsk.dev/about";

const char* linkedin_nl_no = ""
"Ik vrees dat deze functie niet bij mij past. Ik wens je veel succes met het vinden van geschikte kandidaten.\n"
"\n"
"Vriendelijke groet,\n"
"David Kleingeld\n"
"http://davidsk.dev/about";

#define CLOSE_WIN_INTERVAL 300
enum macroKeycodes {
  M_BAT = SAFE_RANGE, //begin alt tab
  M_EAT,              //end alt-tab
  M_LIN_NLY,
  M_LIN_NLN,
  MAIL_END,
  WIN_MM,
  TAPP,
  SPSHFT,
  M_RESET,
  M_ARUN
};
