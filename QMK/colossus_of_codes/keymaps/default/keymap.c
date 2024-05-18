#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE = 0,  // default layer
    ALT  = 1,   // contains joystick and debug buttons
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(

                        KC_MUTE,              KC_NO,            KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
      KC_MPRV, KC_MPLY, KC_MNXT,              KC_ESC,           KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,      KC_PSCR, KC_SCRL, KC_PAUS,
    KC_NUM, KC_KP_SLASH, KC_PAST, KC_PMNS,    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,                 KC_INS, KC_HOME, KC_PGUP,
    KC_P7, KC_P8, KC_P9, KC_PPLS,             KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                KC_DEL, KC_END, KC_PGDN,
    KC_P4, KC_P5, KC_P6,                      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
    KC_P1, KC_P2, KC_P3, KC_PENT,             KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
    KC_P0, KC_PDOT,                           KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APPLICATION, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
),
[1] = LAYOUT(

                        KC_NO,              KC_CALC,            JS_13, JS_14, JS_15, JS_16, JS_17, JS_18, JS_19, JS_20, JS_21, JS_22, JS_23, JS_24,
      KC_NO, KC_NO, KC_NO,              KC_NO,           JS_1, JS_2, JS_3, JS_4, JS_5, JS_6, JS_7, JS_8, JS_9, JS_10, JS_11, JS_12,      QK_BOOT, QK_RBT, DB_TOGG,
    KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] =   { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN)  },
    [ALT] =   { ENCODER_CCW_CW(KC_NO, KC_NO)  },
};
#endif
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
// #ifdef CONSOLE_ENABLE
//     uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
// #endif 
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  //debug_mouse=true;
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
};