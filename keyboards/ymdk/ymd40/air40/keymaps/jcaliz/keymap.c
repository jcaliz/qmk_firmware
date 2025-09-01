/* Copyright 2022 Dennis Kruyt (dennis@kruyt.org)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include "action.h"
#include "quantum.h"
#include "unicode.h"
#include QMK_KEYBOARD_H
#include "print.h"

enum custom_layers {
  _DVORAK,
  _LRAISE,
  _RRAISE,
  _SYSTEM,
};

enum custom_keycodes {
  PLOVER = SAFE_RANGE,
  BACKLIT,
  EXT_PLV,
  KC_TEST,
  KC_DEAD,
};

enum unicode_names {
    L_ACCENT_A,
    U_ACCENT_A,
    L_ACCENT_E,
    U_ACCENT_E,
    L_ACCENT_I,
    U_ACCENT_I,
    L_ACCENT_O,
    U_ACCENT_O,
    L_ACCENT_U,
    U_ACCENT_U,
    L_ACCENT_U_DIA,
    U_ACCENT_U_DIA,
    L_ACCENT_N_TILDE,
    U_ACCENT_N_TILDE,
    L_ACCENT_INVERTED_QUES,
    U_ACCENT_INVERTED_QUES,
};

const uint32_t unicode_map[] = {
    [L_ACCENT_A] = 0x00E1,
    [U_ACCENT_A] = 0x00C1,
    [L_ACCENT_E] = 0x00E9,
    [U_ACCENT_E] = 0x00C9,
    [L_ACCENT_I] = 0x00ED,
    [U_ACCENT_I] = 0x00CD,
    [L_ACCENT_O] = 0x00F3,
    [U_ACCENT_O] = 0x00D3,
    [L_ACCENT_U] = 0x00FA,
    [U_ACCENT_U] = 0x00DA,
    [L_ACCENT_U_DIA] = 0x00FC,
    [U_ACCENT_U_DIA] = 0x00DC,
    [L_ACCENT_N_TILDE] = 0x00F1,
    [U_ACCENT_N_TILDE] = 0x00D1,
    [L_ACCENT_INVERTED_QUES] = 0x00BF,
    [U_ACCENT_INVERTED_QUES] = 0x00BF,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define COLEMAK PDF(_COLEMAK)
#define DVORAK PDF(_DVORAK)

bool accent_enabled = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_ortho_4x12(
        KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,   KC_Y,    KC_F,    KC_G,   KC_C,     KC_R,     KC_L,   KC_BSPC,
        KC_ESC,   KC_A,     KC_O,     KC_E,     KC_U,   KC_I,    KC_D,    KC_H,   KC_T,     KC_N,     KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,   KC_X,    KC_B,    KC_M,   KC_W,     KC_V,     KC_Z,   KC_RSFT,
        KC_LGUI,  KC_GRV,   KC_LALT,  KC_LCTL,  MO(1),  KC_SPC,  KC_SPC,  MO(2),  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT
    ),

    [_LRAISE] = LAYOUT_ortho_4x12(
        RCS(KC_TAB),  LCTL(KC_R),  KC_3,     KC_2,     KC_1,     LCTL(KC_TAB),  KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_BSPC,
        KC_DEL,       LCTL(KC_C),  KC_6,     KC_5,     KC_4,     KC_NO,         KC_NO,    KC_EQL,  KC_LBRC,  KC_RBRC,  KC_SLSH,  KC_TRNS,
        KC_TRNS,      LCTL(KC_V),  KC_9,     KC_8,     KC_7,     KC_0,          KC_NO,    KC_LT,   KC_GT,    KC_BSLS,  KC_BSLS,  KC_TRNS,
        KC_TRNS,      LCTL(KC_W),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,  MO(3),   KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
    ),

    [_RRAISE] = LAYOUT_ortho_4x12(
        KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_PERC,  KC_LCBR,     KC_RCBR,  KC_AMPR,  KC_CIRC,  KC_PAST,  KC_QUES,  KC_TRNS,
        KC_DEL,   KC_QUOT,  KC_LPRN,  KC_RPRN,  KC_UNDS,  KC_MINS,     KC_DLR,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_SLSH,  KC_TRNS,
        KC_TRNS,  KC_PPLS,  KC_NO,    KC_NO,    KC_NO,    KC_DEAD,     KC_TILD,  KC_LT,    KC_GT,    KC_BSLS,  KC_PIPE,  KC_TRNS,
        KC_1,     KC_TRNS,  KC_TRNS,  KC_TRNS,  MO(3),    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
    ),

    [_SYSTEM] = LAYOUT_ortho_4x12(
        QK_BOOT,  UG_TOGG,  UG_HUEU,  UG_SATU,  UG_VALU,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  DB_TOGG,
        PLOVER,   UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  AG_NORM,  AG_SWAP,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  UC_LINX,
        KC_TEST,  UG_PREV,  RGB_SPD,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  UC_NEXT,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MRWD,  KC_TRNS,  KC_TRNS,  KC_MFFD
    ),
};

void send_accented(enum unicode_names lower, enum unicode_names upper) {
    bool shifted = get_mods() & MOD_MASK_SHIFT;
    uint32_t codepoint = shifted ? unicode_map[upper] : unicode_map[lower];
    register_unicode(codepoint);
    accent_enabled = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        #ifdef KEYCODE_STRING_ENABLE
            uprintf("kc: %s\n", get_keycode_string(keycode));
        #endif
    #endif

    if (accent_enabled) {
        switch (keycode) {
            case KC_A:
                send_accented(L_ACCENT_A, U_ACCENT_A);
                return false;

            case KC_E:
                send_accented(L_ACCENT_E, U_ACCENT_E);
                return false;

            case KC_I:
                send_accented(L_ACCENT_I, U_ACCENT_I);
                return false;

            case KC_O:
                send_accented(L_ACCENT_O, U_ACCENT_O);
                return false;

            case KC_U:
                send_accented(L_ACCENT_U, U_ACCENT_U);
                return false;

            case KC_N:
                send_accented(L_ACCENT_N_TILDE, U_ACCENT_N_TILDE);
                return false;

            case KC_QUES: // inverted question mark
                send_accented(L_ACCENT_INVERTED_QUES, U_ACCENT_INVERTED_QUES);
                return false;

            default:
                return true; // normal key
        }
    }

    switch (keycode) {
        case BACKLIT:
            return false;
            break;
        case PLOVER:
            #ifdef RGB_MATRIX_CUSTOM_USER
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_STARLIGHT);
            #endif
            return false;
        break;
            case KC_TEST:
            return false;
            break;
        case KC_DEAD:
            if (record->event.pressed) {
                accent_enabled = true;
                return false;
            }
            break;
    }
    return true;
}
