/*
Copyright 2020 Oliver Gaskell <me@gaskell.tech>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_MUTE, KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,   KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,   KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,   KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_TAB,  KC_LCTL, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_SPC, MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

    [_NUMPAD] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7, KC_P8,   KC_P9,   KC_PSLS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PAST,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PMNS, KC_PPLS),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_VOLD, KC_EXLM,       KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,      KC_RPRN,       KC_INS,
        KC_NUM,  KC_F7,         KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LCBR, KC_RCBR, KC_UNDS,      KC_PLUS,       LSFT(KC_NUHS),
        KC_TRNS, LSFT(KC_NUBS), KC_GRAVE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_GRV), LSFT(KC_NUBS), KC_TRNS,
        KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN,      KC_PGUP,       KC_END),

    [_RAISE] = LAYOUT_ortho_4x12(
        KC_VOLU, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_NUHS,
        KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_NUBS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT),

    [_ADJUST] = LAYOUT_ortho_4x12(
        KC_TRNS, RGB_TOG,     RGB_MOD, RGB_HUD, RGB_HUI,  RGB_SAD,  RGB_SAI, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, QK_BOOT,
        KC_TRNS, RGB_M_P,     RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_TRNS, KC_TRNS,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

void keyboard_post_init_user(void) {
    // Uncomment for debug mode
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(_QWERTY, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(_NUMPAD, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_ADJUST, layer_state_cmp(state, _ADJUST));

    return state;
}

#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [_QWERTY] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
        [_NUMPAD] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_LOWER] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_RAISE] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_ADJUST] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    };
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    static const char PROGMEM tau4logo_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x00};
    static const char PROGMEM tau4logo_2[] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0x00};
    static const char PROGMEM tau4logo_3[] = {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0x00};

    static const char PROGMEM layers[][2] = {
        {0x20, 0x00},  // " "
        {0x89, 0x00},  // Numpad
        {0x87, 0x00},  // Lower
        {0x86, 0x00},  // Raise
        {0x88, 0x00},  // Adjust
    };

    oled_write_P(tau4logo_1, false);
    oled_write_P(PSTR("  Tau.4 v1.1\n"), false);

    oled_write_P(tau4logo_2, false); oled_write_P(PSTR("\n"), false);

    oled_write_P(tau4logo_3, false);
    oled_write_P(PSTR("Layout WPM RGB\n"), false);

    // LAYOUT: TODO
    oled_write_P(PSTR("      QRTY "), false);

    // Layer
    oled_write_P(layers[get_highest_layer(layer_state)], false);
    oled_write_P(PSTR(" "), false);

    // WPM
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_write_P(PSTR(" "), false);

    // RGB
    switch (rgblight_get_mode()) {
        case RGBLIGHT_MODE_STATIC_LIGHT :
            oled_write_P(PSTR("STAT"), false);
            break;
        case RGBLIGHT_MODE_BREATHING :
        case RGBLIGHT_MODE_BREATHING + 1:
        case RGBLIGHT_MODE_BREATHING + 2:
        case RGBLIGHT_MODE_BREATHING + 3:
            oled_write_P(PSTR("BRTH"), false);
            break;
        case RGBLIGHT_MODE_RAINBOW_MOOD :
        case RGBLIGHT_MODE_RAINBOW_MOOD + 1:
        case RGBLIGHT_MODE_RAINBOW_MOOD + 2:
            oled_write_P(PSTR("RNBW"), false);
            break;
        case RGBLIGHT_MODE_RAINBOW_SWIRL :
        case RGBLIGHT_MODE_RAINBOW_SWIRL + 1:
        case RGBLIGHT_MODE_RAINBOW_SWIRL + 2:
        case RGBLIGHT_MODE_RAINBOW_SWIRL + 3:
        case RGBLIGHT_MODE_RAINBOW_SWIRL + 4:
        case RGBLIGHT_MODE_RAINBOW_SWIRL + 5:
            oled_write_P(PSTR("SWRL"), false);
            break;
        case RGBLIGHT_MODE_SNAKE :
        case RGBLIGHT_MODE_SNAKE + 1:
        case RGBLIGHT_MODE_SNAKE + 2:
        case RGBLIGHT_MODE_SNAKE + 3:
        case RGBLIGHT_MODE_SNAKE + 4:
        case RGBLIGHT_MODE_SNAKE + 5:
            oled_write_P(PSTR("SNKE"), false);
            break;
        case RGBLIGHT_MODE_KNIGHT :
        case RGBLIGHT_MODE_KNIGHT + 1:
        case RGBLIGHT_MODE_KNIGHT + 2:
            oled_write_P(PSTR("KNGT"), false);
            break;
        case RGBLIGHT_MODE_CHRISTMAS :
            oled_write_P(PSTR("XMAS"), false);
            break;
        case RGBLIGHT_MODE_STATIC_GRADIENT :
        case RGBLIGHT_MODE_STATIC_GRADIENT + 1:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 2:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 3:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 4:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 5:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 6:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 7:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 8:
        case RGBLIGHT_MODE_STATIC_GRADIENT + 9:
            oled_write_P(PSTR("GRDT"), false);
            break;
        case RGBLIGHT_MODE_RGB_TEST :
            oled_write_P(PSTR("TEST"), false);
            break;
        default:
            oled_write_P(PSTR("????"), false);
            break;
    }

    return false;
}
#endif
