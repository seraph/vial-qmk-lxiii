// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

enum layers{
    _QWERTY,
    _MO1,
    _MO2,
    _MO3
};

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
          QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
          KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,          KC_BSLS,
          KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,                    KC_ENT,
KC_LCTL,  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_SLSH, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
      MO(1), KC_LALT, KC_LGUI,          KC_SPC,         MO(2),                    KC_SPC,           MO(2),            KC_LEFT, KC_DOWN, KC_RGHT 
  ),

  [_MO1] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______, _______,
             _______, UG_TOGG, UG_NEXT, UG_PREV, UG_HUEU, UG_HUED,                UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD,          _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, KC_MUTE, _______, _______, KC_VOLU, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_MO2] = LAYOUT(
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, KC_RBRC,         _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, KC_SCLN,                  _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, KC_PGUP, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          KC_HOME, KC_PGDN, KC_END
  ),

  [_MO3] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,         _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,                  _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          _______, _______, _______
  )
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_90;  // flips the display 180 degrees if offhand

    return rotation;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_ln_P(PSTR("LXIII"), false);
    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _MO1:
            oled_write_ln_P(PSTR("MODE1"), false);
            break;
        case _MO2:
            oled_write_ln_P(PSTR("MODE2"), false);
            break;
        case _MO3:
            oled_write_ln_P(PSTR("MODE3"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("UNDEF"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUMLK") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPLK") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCRLK") : PSTR("    "), false);
    
    return false;
}
#endif