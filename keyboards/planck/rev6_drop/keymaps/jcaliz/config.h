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

#pragma once

#ifdef AUDIO_ENABLE
#define TEMPO_DEFAULT 220
// #define STARTUP_SONG SONG(NO_SOUND)

#define IMPERIAL_SOUND SONG(Q__NOTE(_A4), Q__NOTE(_A4), Q__NOTE(_A4), ED_NOTE(_F4), S__NOTE(_C5), Q__NOTE(_A4),  ED_NOTE(_F4), S__NOTE(_C5), H__NOTE(_A4), Q__NOTE(_E5), Q__NOTE(_E5), Q__NOTE(_E5), ED_NOTE(_F5), S__NOTE(_C5), Q__NOTE(_GS4), ED_NOTE(_F4), S__NOTE(_C5), Q__NOTE(_A4), ED_NOTE(_F4), S__NOTE(_C5), H__NOTE(_A4))
#define MAC_SOUND SONG(E__NOTE(_C5), E__NOTE(_D5), E__NOTE(_E5), E__NOTE(_G5), E__NOTE(_C6), E__NOTE(_AS5), E__NOTE(_C6), E__NOTE(_DS6), E__NOTE(_E6), E__NOTE(_G6), E__NOTE(_AS6), E__NOTE(_C7), E__NOTE(_B6), E__NOTE(_AS5), E__NOTE(_D6), E__NOTE(_F6), E__NOTE(_AS6), E__NOTE(_D7), E__NOTE(_F7), E__NOTE(_G7), E__NOTE(_F7))
#define LINUX_SOUND SONG(E__NOTE(_F7), E__NOTE(_G7), E__NOTE(_F7), E__NOTE(_D7), E__NOTE(_AS6), E__NOTE(_F6), E__NOTE(_D6), E__NOTE(_AS5), E__NOTE(_B6), E__NOTE(_C7), E__NOTE(_AS6), E__NOTE(_G6), E__NOTE(_E6), E__NOTE(_DS6), E__NOTE(_C6), E__NOTE(_AS5), E__NOTE(_C6), E__NOTE(_G5), E__NOTE(_E5), E__NOTE(_D5), E__NOTE(_C5))
#define AUDIO_DAC_SAMPLE_MAX 2048U
#endif

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4


// RGB
// #define RGBLIGHT_MODE_RAINBOW_MOOD
// #define RGBLIGHT_EFFECT_CHRISTMAS
// #define RGBLIGHT_EFFECT_BREATHING