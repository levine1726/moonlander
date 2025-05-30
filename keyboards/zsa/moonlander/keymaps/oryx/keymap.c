/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"

enum layers {
    BASE,  // default layer
    NAV, // navigation keys
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    KC_C_WITH_MOD_COPY = LT(0,KC_C),
    KC_X_WITH_MOD_CUT = LT(0,KC_X),
    KC_V_WITH_MOD_PASTE = LT(0,KC_V)
};

#define DEBOUNCE 1

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,           KC_RGHT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_RIGHT_BRACKET,  KC_LEFT_BRACKET, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    LSG(KC_SPC),           LSG(KC_J),  KC_H,    KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), LGUI_T(KC_QUOT),
        KC_LSFT, LCTL_T(KC_Z),KC_X_WITH_MOD_CUT, KC_C_WITH_MOD_COPY,   KC_V_WITH_MOD_PASTE,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
   KC_LEFT_ALT, WEBUSB_PAIR,A(KC_LSFT),KC_LEFT, KC_RGHT,  LT(NAV ,KC_ESC),    RGUI_T(KC_ESC),   KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MO(SYMB),
                                            KC_SPC,  KC_BSPC, KC_LGUI,           KC_LALT,  KC_TAB,  KC_ENT
    ),

    [NAV] = LAYOUT(
        _______, _______, _______,_______,_______, _______,   _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, A(KC_W),_______,_______, A(KC_T),   _______,           _______, _______, _______, _______, _______, A(KC_P), _______,
        _______, _______, A(KC_S),A(KC_D), A(KC_F), _______,  _______,           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, _______,A(KC_C), _______, _______,                             _______, A(KC_M),    _______,    _______,    _______, _______,
        KC_LEFT_ALT,  _______, _______, _______, _______,          KC_LEFT_ALT,           _______,          _______, _______,  _______,    _______,  _______,
                                            _______, _______, _______, _______,_______, _______
    ),

    [SYMB] = LAYOUT(
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______, _______,   KC_LEFT_BRACKET,    KC_RIGHT_BRACKET,    _______,    KC_ASTR, KC_F12,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_PLUS, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, _______,    _______,    _______,    KC_BSLS, _______,
        EE_CLR,  _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,_______, _______
    ),

    [MDIA] = LAYOUT(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case KC_X_WITH_MOD_CUT:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_X)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case KC_C_WITH_MOD_COPY:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_C)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case KC_V_WITH_MOD_PASTE:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_V)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;
        }
    }
    return true;
}
