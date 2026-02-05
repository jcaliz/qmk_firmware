/* Copyright 2015-2021 Jack Humbert
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

#include QMK_KEYBOARD_H

// #ifdef AUDIO_ENABLE
// #    include "muse.h"
//   float imperial[][2] = IMPERIAL_SOUND;
// #endif

enum custom_layers {
  _DVORAK,
  _QWERTY,
  _LRAISE,
  _RRAISE,
  _SYSTEM,
};

enum planck_keycodes {
  PLOVER = SAFE_RANGE,
  BACKLIT,
  EXT_PLV,
  KC_TEST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define COLEMAK PDF(_COLEMAK)
#define DVORAK PDF(_DVORAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT_ortho_4x12(
        KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,         KC_Y,    KC_F,    KC_G,   KC_C,     KC_R,     KC_L,   KC_BSPC,
        KC_ESC,   KC_A,     KC_O,     KC_E,     KC_U,         KC_I,    KC_D,    KC_H,   KC_T,     KC_N,     KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,         KC_X,    KC_B,    KC_M,   KC_W,     KC_V,     KC_Z,   KC_RSFT,
        KC_LCTL,  KC_GRV,   KC_LALT,  KC_LGUI,  MO(_LRAISE),  KC_SPC,  KC_SPC,  MO(_RRAISE),  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT
    ),

    [_LRAISE] = LAYOUT_ortho_4x12(
        RCS(KC_TAB),  LGUI(KC_R),  KC_3,     KC_2,     KC_1,     LCTL(KC_TAB),  KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_BSPC,
        KC_DEL,       LGUI(KC_C),  KC_6,     KC_5,     KC_4,     KC_NO,         KC_NO,    KC_EQL,  KC_LBRC,  KC_RBRC,  KC_SLSH,  KC_TRNS,
        KC_TRNS,      LGUI(KC_V),  KC_9,     KC_8,     KC_7,     KC_0,          KC_NO,    KC_LT,   KC_GT,    KC_BSLS,  KC_BSLS,  KC_TRNS,
        KC_TRNS,      LGUI(KC_W),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,  MO(_SYSTEM),   KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
    ),

    [_RRAISE] = LAYOUT_ortho_4x12(
        KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_PERC,  KC_LCBR,     KC_RCBR,  KC_AMPR,  KC_CIRC,  LSFT(KC_8),  KC_QUES,  KC_TRNS,
        KC_DEL,   KC_QUOT,  KC_LPRN,  KC_RPRN,  KC_UNDS,  KC_MINS,     KC_DLR,   KC_EQL,   KC_LBRC,  KC_RBRC,     KC_SLSH,  KC_TRNS,
        KC_TRNS,  KC_PPLS,  KC_NO,    KC_NO,    KC_NO,    LALT(KC_E),     KC_TILD,  KC_LT,    KC_GT,    KC_BSLS,     KC_PIPE,  KC_TRNS,
        KC_1,     KC_TRNS,  KC_TRNS,  KC_TRNS,  MO(_SYSTEM),    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_MNXT,  KC_VOLD,     KC_VOLU,  KC_MPLY
    ),

    [_SYSTEM] = LAYOUT_ortho_4x12(
        QK_BOOT,  UG_TOGG,  UG_HUEU,  UG_SATU,  UG_VALU,  KC_TRNS,      KC_TRNS,  KC_F7,    KC_F8,  KC_F9,  KC_F10,  DB_TOGG,
        PLOVER,   UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  KC_TRNS,      KC_TRNS,  KC_F4,    KC_F5,  KC_F6,  KC_F11,  UC_LINX,
        KC_TEST,  UG_PREV,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_F1,    KC_F2,  KC_F3,  KC_F12,  UC_NEXT,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_MRWD,  KC_TRNS,  KC_TRNS,  KC_MFFD
    ),

};


// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//     case _DVORAK:
//         // rgblight_sethsv (0x00,  0x00, 0xFF);
//         break;
//     case _LRAISE:
//         // rgblight_sethsv (0x00,  0xFF, 0x00);
//         rgblight_mode(RGB_MATRIX_SOLID_COLOR);
//         break;
//     case _RRAISE:
//         // rgblight_sethsv (0x7A,  0x00, 0xFF);
//         // rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
//         break;
//     default: //  for any other layers, or the default layer
//         // rgblight_sethsv (0x00,  0xFF, 0xFF);
//         break;
//     }
//   return state;
// }


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case BACKLIT:
//       if (record->event.pressed) {
//         register_code(KC_RSFT);
//         #ifdef BACKLIGHT_ENABLE
//           backlight_step();
//         #endif
//         #ifdef KEYBOARD_planck_rev5
//           gpio_write_pin_low(E6);
//         #endif
//       } else {
//         unregister_code(KC_RSFT);
//         #ifdef KEYBOARD_planck_rev5
//           gpio_write_pin_high(E6);
//         #endif
//       }
//       return false;
//       break;
//     case PLOVER:
//       if (record->event.pressed) {
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//           audio_set_tempo(30);
//           rgb_matrix_mode(RGB_MATRIX_CUSTOM_star_wars);
//           PLAY_SONG(imperial);
//         #endif
//       }
//       return false;
//       break;
//     case KC_TEST:
//       if (record->event.pressed) {
//         #ifdef AUDIO_ENABLE
//           // stop_all_notes();
//           // audio_set_tempo(30);
//           rgb_matrix_mode(RGB_MATRIX_CUSTOM_star_wars);
//           // PLAY_SONG(imperial);
//         #endif
//       }
//       return false;
//       break;
//    }
//   return true;
// }

// bool muse_mode = false;
// uint8_t last_muse_note = 0;
// uint16_t muse_counter = 0;
// uint8_t muse_offset = 70;
// uint16_t muse_tempo = 50;

// bool encoder_update_user(uint8_t index, bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_RAISE)) {
//       if (clockwise) {
//         muse_offset++;
//       } else {
//         muse_offset--;
//       }
//     } else {
//       if (clockwise) {
//         muse_tempo+=1;
//       } else {
//         muse_tempo-=1;
//       }
//     }
//   } else {
//     if (clockwise) {
//       #ifdef MOUSEKEY_ENABLE
//         tap_code(KC_MS_WH_DOWN);
//       #else
//         tap_code(KC_PGDN);
//       #endif
//     } else {
//       #ifdef MOUSEKEY_ENABLE
//         tap_code(KC_MS_WH_UP);
//       #else
//         tap_code(KC_PGUP);
//       #endif
//     }
//   }
//     return true;
// }

// bool dip_switch_update_user(uint8_t index, bool active) {
//     switch (index) {
//         case 0: {
// #ifdef AUDIO_ENABLE
//             static bool play_sound = false;
// #endif
//             if (active) {
// #ifdef AUDIO_ENABLE
//                 if (play_sound) { PLAY_SONG(plover_song); }
// #endif
//                 layer_on(_ADJUST);
//             } else {
// #ifdef AUDIO_ENABLE
//                 if (play_sound) { PLAY_SONG(plover_gb_song); }
// #endif
//                 layer_off(_ADJUST);
//             }
// #ifdef AUDIO_ENABLE
//             play_sound = true;
// #endif
//             break;
//         }
//         case 1:
//             if (active) {
//                 muse_mode = true;
//             } else {
//                 muse_mode = false;
//             }
//     }
//     return true;
// }

// void matrix_scan_user(void) {
// #ifdef AUDIO_ENABLE
//     if (muse_mode) {
//         if (muse_counter == 0) {
//             uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
//             if (muse_note != last_muse_note) {
//                 stop_note(compute_freq_for_midi_note(last_muse_note));
//                 play_note(compute_freq_for_midi_note(muse_note), 0xF);
//                 last_muse_note = muse_note;
//             }
//         }
//         muse_counter = (muse_counter + 1) % muse_tempo;
//     } else {
//         if (muse_counter) {
//             stop_all_notes();
//             muse_counter = 0;
//         }
//     }
// #endif
// }

// bool music_mask_user(uint16_t keycode) {
//   switch (keycode) {
//     case RAISE:
//     case LOWER:
//       return false;
//     default:
//       return true;
//   }
// }
