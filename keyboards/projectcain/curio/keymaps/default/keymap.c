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

#include "keycodes.h"
#include QMK_KEYBOARD_H

#define HSV_GRAY 0, 0, 128

#ifdef RGBLIGHT_LAYERS
/* Curio has 12 LEDs; use literal to avoid RGBLED_NUM being undefined in keymap_introspection build */
const rgblight_segment_t PROGMEM _blink_linux[] = RGBLIGHT_LAYER_SEGMENTS( {0, 12, HSV_ORANGE} );
const rgblight_segment_t PROGMEM _blink_mac[] = RGBLIGHT_LAYER_SEGMENTS( {0, 12, HSV_GRAY} );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _blink_linux, _blink_mac );
#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = _rgb_layers;
#endif
}


enum layers {
  _DVORAK_MAC,
  _DVORAK_LIN,
  _LRAISE,
  _RRAISE,
  _RRAISE2,
  _SYSTEM,
};

enum my_keycodes {
    KC_CUSTOM_TAB = SAFE_RANGE,
    KC_REFRESH,
    KC_CPY,
    KC_PST,
    KC_CLOSE,
    TOGGLE_SO,
    KC_PRINT_KEYMAP_URL,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK_MAC] = LAYOUT(
        KC_CUSTOM_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,         KC_Y,    KC_F,    KC_G,   KC_C,     KC_R,     KC_L,   KC_BSPC,
        KC_ESC,   KC_A,     KC_O,     KC_E,     KC_U,         KC_I,    KC_D,    KC_H,   KC_T,     KC_N,     KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,         KC_X,    KC_B,    KC_M,   KC_W,     KC_V,     KC_Z,   KC_RSFT,
        KC_LCTL,  KC_LALT,  KC_LGUI,  MO(_LRAISE),    KC_SPC, KC_SPC,   KC_SPC,  MO(_RRAISE),  MO(_RRAISE2), KC_NO,  KC_GRV
    ),

    [_DVORAK_LIN] = LAYOUT(
        KC_CUSTOM_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,         KC_Y,    KC_F,    KC_G,   KC_C,     KC_R,     KC_L,   KC_BSPC,
        KC_ESC,   KC_A,     KC_O,     KC_E,     KC_U,         KC_I,    KC_D,    KC_H,   KC_T,     KC_N,     KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,         KC_X,    KC_B,    KC_M,   KC_W,     KC_V,     KC_Z,   KC_RSFT,
        KC_LGUI,  KC_LALT,  KC_LCTL,  MO(_LRAISE),    KC_SPC, KC_SPC,   KC_SPC,  MO(_RRAISE),  MO(_RRAISE2), KC_NO,  KC_GRV
    ),

    [_LRAISE] = LAYOUT(
        RCS(KC_TAB),  KC_REFRESH,  KC_3,     KC_2,     KC_1,     LCTL(KC_TAB), KC_NO,     ALGR(KC_I),   ALGR(KC_C),    KC_NO,    KC_NO,  KC_BSPC,
        KC_DEL,       KC_CPY,      KC_6,     KC_5,     KC_4,     KC_NO,         KC_NO,    KC_EQL,  KC_LBRC,  KC_RBRC,  KC_SLSH,  KC_TRNS,
        KC_TRNS,      KC_PASTE,    KC_9,     KC_8,     KC_7,     KC_0,          KC_NO,    KC_LT,   KC_GT,    KC_BSLS,  KC_PIPE,  KC_TRNS,
        KC_TRNS,      KC_CLOSE,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,  MO(_SYSTEM),   KC_MNXT,  KC_VOLD, KC_TRNS
    ),

    [_RRAISE] = LAYOUT(

        KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_PERC,  KC_LCBR,     KC_RCBR,  KC_AMPR,  KC_CIRC,  LSFT(KC_8),  KC_QUES, KC_BSPC,
        KC_DEL,   KC_QUOT,  KC_LPRN,  KC_RPRN,  KC_UNDS,  KC_MINS,     KC_DLR,   KC_EQUAL,   KC_LBRC,  KC_RBRC,     KC_SLSH,  KC_TRNS,
        KC_TRNS,  KC_PPLS,  KC_NO,    KC_NO,    ALGR(KC_N),    ALGR(KC_E),     KC_TILD,  KC_LT,    KC_GT,    KC_BSLS,     KC_PIPE,  KC_TRNS,
        LCTL(KC_GRV),     KC_TRNS,  KC_TRNS,    MO(_SYSTEM),  KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_MNXT,  KC_VOLD,
    ),

    [_RRAISE2] = LAYOUT(

        KC_CALC,   KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,     KC_NO,  KC_NO,  KC_UP,  KC_NO,  KC_NO,  KC_BSPC,
        KC_DEL,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,     KC_NO,   KC_LEFT,   KC_DOWN,  KC_RIGHT,     KC_NO,  KC_NO,
        KC_TRNS,   KC_NO,    KC_NO,    KC_NO,   KC_NO,     KC_NO,  KC_MPRV,    KC_MNXT,    KC_VOLD,     KC_VOLU, KC_MPLY, KC_NO,
        KC_NO,     KC_TRNS,  KC_TRNS,  MO(_SYSTEM),  KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_MNXT,  KC_VOLD,
    ),

    [_SYSTEM] = LAYOUT(
        QK_BOOT,  UG_TOGG,  UG_HUEU,  UG_SATU,  UG_VALU,  TOGGLE_SO,  KC_TRNS,  KC_F7,    KC_F8,  KC_F9,  KC_F10, DB_TOGG,
        KC_PRINT_KEYMAP_URL,  UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  KC_TRNS,  KC_TRNS,  KC_F4,    KC_F5,  KC_F6,  KC_F11,  UC_LINX,
        KC_TRNS,  UG_PREV,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_F1,    KC_F2,  KC_F3,  KC_F12,  UC_NEXT,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_MRWD,  KC_TRNS, KC_TRNS
    ),


};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DVORAK_MAC] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_DVORAK_LIN] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_LRAISE] =       { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_RRAISE] =       { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_RRAISE2] =      { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_SYSTEM] =       { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("kc: %s\n", get_keycode_string(keycode));
    uprintf("col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->event.time, record->tap.interrupted, record->tap.count);
#endif

    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    switch (keycode) {
        case KC_CUSTOM_TAB:
            if (record->event.pressed) {
                if (mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
                    // Alt held: send Cmd + `
                    del_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT));
                    register_code(KC_LGUI);
                    tap_code(KC_GRV);
                    unregister_code(KC_LGUI);
                    set_mods(mods);
                    return false;
                } else {
                    // No Alt: hold Tab normally
                    register_code(KC_TAB);
                    return false;
                }
            } else {
                // Release Tab normally
                unregister_code(KC_TAB);
                return false;
            }
            return true;
            break;
        case TOGGLE_SO:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DVORAK_MAC) {
                    // Switching to Linux — blink all LEDs orange (2 times)
                    #ifdef RGBLIGHT_LAYER_BLINK
                    rgblight_blink_layer_repeat(0, 500, 2);
                    #endif
                    set_single_persistent_default_layer(_DVORAK_LIN);
                } else {
                    // Switching to Mac — blink all LEDs gray (2 times)
                    #ifdef RGBLIGHT_LAYER_BLINK
                    rgblight_blink_layer_repeat(1, 500, 2);
                    #endif
                    set_single_persistent_default_layer(_DVORAK_MAC);
                }
            }
            return false;
            break;
        case KC_REFRESH:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DVORAK_MAC) {
                    tap_code16(LGUI(KC_R));
                } else {
                    tap_code16(LCTL(KC_R));
                }
            }
            return false;
            break;
        case KC_CPY:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DVORAK_MAC) {
                    tap_code16(LGUI(KC_C));
                } else {
                    tap_code16(LCTL(KC_C));
                }
            }
            return false;
            break;
        case KC_PST:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DVORAK_MAC) {
                    tap_code16(LGUI(KC_V));
                } else {
                    tap_code16(LCTL(KC_V));
                }
            }
            return false;
            break;
        case KC_CLOSE:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DVORAK_MAC) {
                    tap_code16(LGUI(KC_W));
                } else {
                    tap_code16(LCTL(KC_W));
                }
            }
            return false;
            break;
        case KC_PRINT_KEYMAP_URL:
            if (record->event.pressed) {
                SEND_STRING("https://github.com/jcaliz/qmk_firmware/blob/master/keyboards/projectcain/curio/keymaps/default/keymap.c");
            }
            return false;
            break;
    }
    return true;
}
