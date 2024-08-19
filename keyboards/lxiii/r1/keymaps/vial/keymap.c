// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

enum layers{
    _LAYER_ZERO,
    _LAYER_ONE,
    _LAYER_TWO,
    _LAYER_THREE
};

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER_ZERO] = LAYOUT(
          QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
          KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,          KC_BSLS,
          KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,                    KC_ENT,
KC_LCTL,  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_SLSH, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
      MO(1), KC_LALT, KC_LGUI,          KC_SPC,         MO(2),                    KC_SPC,           MO(2),            KC_LEFT, KC_DOWN, KC_RGHT 
  ),

  [_LAYER_ONE] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______, _______,
             _______, UG_TOGG, UG_NEXT, UG_PREV, UG_HUEU, UG_HUED,                UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD,          _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, KC_MUTE, _______, _______, KC_VOLU, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_LAYER_TWO] = LAYOUT(
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, KC_RBRC,         _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, KC_SCLN,                  _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, KC_PGUP, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          KC_HOME, KC_PGDN, KC_END
  ),

  [_LAYER_THREE] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,         _______,
             _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,                  _______,
    _______, _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,          _______,          _______,                _______,          _______,          _______, _______, _______
  )
};

// #define OLED_ENABLE

#ifdef OLED_ENABLE
// OLED is rotated 90 to the vertical
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_90;  // flips the display 180 degrees if offhand

    return rotation;
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}


void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("lxiii"), false);
}

void render_layer_state(void) {
    static const char PROGMEM layer_zero[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM layer_one[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM layer_two[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    switch (get_highest_layer(layer_state)) {
        case _LAYER_ZERO:
            oled_write_P(layer_zero, false);
            break;
        case _LAYER_ONE:
            oled_write_P(layer_one, false);
            break;
        case _LAYER_TWO:
            oled_write_P(layer_two, false);
            break;
        case _LAYER_THREE:
            oled_write_P(layer_zero, false);
            break;
        default:
            oled_write_P(layer_zero, false);
    }
}

bool oled_task_user(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods());
    render_mod_status_ctrl_shift(get_mods());

    return false;
}

#endif