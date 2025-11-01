 /* Copyright 2021 projectcain
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  q
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * */

#include QMK_KEYBOARD_H
enum layers {
  _DVORAK,
  _LRAISE,
  _RRAISE,
  _SYSTEM,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT(
        KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,         KC_Y,    KC_F,    KC_G,   KC_C,     KC_R,     KC_L,   KC_BSPC,
        KC_ESC,   KC_A,     KC_O,     KC_E,     KC_U,         KC_I,    KC_D,    KC_H,   KC_T,     KC_N,     KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,         KC_X,    KC_B,    KC_M,   KC_W,     KC_V,     KC_Z,   KC_RSFT,
        KC_LCTL,  KC_LALT,  KC_LGUI,  MO(_LRAISE),    KC_SPC, KC_SPC,   KC_SPC,  MO(_RRAISE),  KC_LEFT, KC_DOWN,  KC_UP
    ),

    [_LRAISE] = LAYOUT(
        RCS(KC_TAB),  LGUI(KC_R),  KC_3,     KC_2,     KC_1,     LCTL(KC_TAB), KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
        KC_DEL,       LGUI(KC_C),  KC_6,     KC_5,     KC_4,     KC_NO,         KC_NO,    KC_EQL,  KC_LBRC,  KC_RBRC,  KC_SLSH,  KC_TRNS,
        KC_TRNS,      LGUI(KC_V),  KC_9,     KC_8,     KC_7,     KC_0,          KC_NO,    KC_LT,   KC_GT,    KC_BSLS,  KC_PIPE,  KC_TRNS,
        KC_TRNS,      LGUI(KC_W),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,  MO(_SYSTEM),   KC_MNXT,  KC_VOLD, KC_TRNS
    ),

    [_RRAISE] = LAYOUT(
        KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_PERC,  KC_LCBR,     KC_RCBR,  KC_AMPR,  KC_CIRC,  LSFT(KC_8),  KC_QUES, KC_NO,
        KC_DEL,   KC_QUOT,  KC_LPRN,  KC_RPRN,  KC_UNDS,  KC_MINS,     KC_DLR,   KC_EQL,   KC_LBRC,  KC_RBRC,     KC_SLSH,  KC_TRNS,
        KC_TRNS,  KC_PPLS,  KC_NO,    KC_NO,    KC_NO,    LALT(KC_E),     KC_TILD,  KC_LT,    KC_GT,    KC_BSLS,     KC_PIPE,  KC_TRNS,
        LCTL(KC_GRV),     KC_TRNS,  KC_TRNS,  KC_TRNS,  MO(_SYSTEM),    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_MNXT,  KC_VOLD,
    ),

    [_SYSTEM] = LAYOUT(
        QK_BOOT,  UG_TOGG,  UG_HUEU,  UG_SATU,  UG_VALU,  DF(_DVORAK),  KC_TRNS,  KC_F7,    KC_F8,  KC_F9,  KC_F10,
        KC_TRNS,   UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  KC_TRNS,  KC_TRNS,  KC_F4,    KC_F5,  KC_F6,  KC_F11,  UC_LINX,
        KC_TRNS,  UG_PREV,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_F1,    KC_F2,  KC_F3,  KC_F12,  UC_NEXT,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_MRWD,  KC_TRNS, KC_TRNS, KC_TRNS
    ),


};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DVORAK] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_LRAISE] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),   ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_RRAISE] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),   ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_SYSTEM] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};
#endif

enum combos {
  KL_SLSH,
  JK_MINUS
};

const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL_SLSH] = COMBO(kl_combo, S(KC_SLSH)),
  [JK_MINUS] = COMBO(jk_combo, KC_MINUS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("kc: %s\n", get_keycode_string(keycode));
    uprintf("col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
