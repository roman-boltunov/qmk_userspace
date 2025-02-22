/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,

    LAYER_NAVIGATION,
    LAYER_MOUSE,
    LAYER_MEDIA,

    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,

    LAYER_GAMING,
    LAYER_COLEMAK,

    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
// #define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define GAMING TG(LAYER_GAMING)
#define COLEMAK TG(LAYER_COLEMAK)
#define BASE TG(LAYER_BASE)

#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_MOU LT(LAYER_MOUSE, KC_TAB)

#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define DEL_FUN LT(LAYER_FUNCTION, KC_DEL)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#define NOOP XXXXXXX

#define DPI_UP POINTER_DEFAULT_DPI_FORWARD
#define DPI_DOWN POINTER_DEFAULT_DPI_REVERSE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#    define DPI_UP  KC_NO
#    define DPI_DOWN KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define ___________________DEAD_HALF_ROW___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define __________________HOME_ROW_GACS_L__________________ XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define __________________HOME_ROW_GACS_R__________________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX

// clang-format off

#define LAYOUT_LAYER_BASE                                                                                                   \
        NOOP,    NOOP,    NOOP,    NOOP,    NOOP,    NOOP,       NOOP,    NOOP,    NOOP,    NOOP,    NOOP,    NOOP,  \
        NOOP,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NOOP,  \
        NOOP,    LGUI_T(KC_A),    LALT_T(KC_S),    LCTL_T(KC_D),    LSFT_T(KC_F),    KC_G,       KC_H,    RSFT_T(KC_J),    RCTL_T(KC_K),    RALT_T(KC_L),  RGUI_T(KC_SCLN),   NOOP,  \
        NOOP,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_SLSH,   NOOP,  \
                                   ESC_MED, GAMING, COLEMAK,   DEL_FUN, BSP_NUM,                                    \
                                           SPC_NAV, TAB_MOU,    ENT_SYM

#define LAYOUT_LAYER_NAVIGATION                                                                                              \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________, \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________, \
        __________________HOME_ROW_GACS_L__________________,     NOOP,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT,    NOOP, \
        ___________________DEAD_HALF_ROW___________________,     KC_INS,  KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,  NOOP, \
                                   XXXXXXX, XXXXXXX, XXXXXXX,    DEL_FUN, BSP_NUM,                                    \
                                           _______,  XXXXXXX,    ENT_SYM

#define LAYOUT_LAYER_MOUSE                                                                                              \
        ___________________DEAD_HALF_ROW___________________,     NOOP,   NOOP,   NOOP,     NOOP,   EE_CLR,   QK_BOOT,   \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        __________________HOME_ROW_GACS_L__________________,     NOOP,  KC_BTN1,  KC_BTN2,  KC_BTN3, DPI_UP, DPI_DOWN,  \
        XXXXXXX, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,  NOOP,   \
                                   XXXXXXX, XXXXXXX, XXXXXXX,    DEL_FUN, BSP_NUM,                                      \
                                           XXXXXXX,  _______,    ENT_SYM

#define LAYOUT_LAYER_MEDIA                                                                                              \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        __________________HOME_ROW_GACS_L__________________,     KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE,  \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
                                   _______, XXXXXXX, XXXXXXX,    DEL_FUN, BSP_NUM,                                      \
                                            XXXXXXX, XXXXXXX,    ENT_SYM

#define LAYOUT_LAYER_NUMERAL                                                                                            \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,       ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_QUOT,    KC_4,    KC_5,    KC_6,  KC_EQL,       __________________HOME_ROW_GACS_R__________________,   \
        NOOP, KC_GRV,     KC_1,    KC_2,    KC_3, KC_BSLS,       ___________________DEAD_HALF_ROW___________________,   \
                                   KC_DOT, ESC_MED, ESC_MED,     XXXXXXX, _______,                                      \
                                           KC_0, KC_MINS,        XXXXXXX

#define LAYOUT_LAYER_SYMBOLS                                                                                           \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN,   KC_RCBR,     ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_DQT ,  KC_DLR, KC_PERC, KC_CIRC,   KC_PLUS,     __________________HOME_ROW_GACS_R__________________,   \
        NOOP, KC_TILD, KC_EXLM,   KC_AT, KC_HASH,   KC_PIPE,     ___________________DEAD_HALF_ROW___________________,   \
                                   KC_LPRN, ESC_MED, ESC_MED,   XXXXXXX, XXXXXXX,                                       \
                                           KC_RPRN, KC_UNDS,    _______

#define LAYOUT_LAYER_FUNCTION                                                                                           \
        ___________________DEAD_HALF_ROW___________________,     ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_F12,   KC_F7,   KC_F8,   KC_F9,  KC_PSCR,       ___________________DEAD_HALF_ROW___________________,   \
        NOOP, KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_SCRL,       __________________HOME_ROW_GACS_R__________________,   \
        NOOP, KC_F10,   KC_F1,   KC_F2,   KC_F3,  KC_PAUS,       ___________________DEAD_HALF_ROW___________________,   \
                                   KC_LPRN, ESC_MED, ESC_MED,    _______, XXXXXXX,                                      \
                                            KC_RPRN, KC_UNDS,    XXXXXXX

#define LAYOUT_LAYER_GAMING                                                                                  \
KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    NOOP,  \
KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_J,  \
KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_BTN1, KC_BTN2, KC_L,  KC_SCLN,   KC_K,  \
KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_SLSH,   NOOP,  \
                            KC_ESC, BASE,  COLEMAK,    DEL_FUN, BSP_NUM,                                     \
                                    KC_SPC, KC_TAB,    KC_ENT

#define LAYOUT_LAYER_COLEMAK                                                                                 \
NOOP,    NOOP,    NOOP,    NOOP,    NOOP,    NOOP,       NOOP,    NOOP,    NOOP,    NOOP,    NOOP,    NOOP,  \
NOOP,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, NOOP,  \
NOOP,    LGUI_T(KC_A),    LALT_T(KC_R),    LCTL_T(KC_S),    LSFT_T(KC_T),    KC_G,       KC_M,    RSFT_T(KC_N),    RCTL_T(KC_E),    RALT_T(KC_I),  RGUI_T(KC_O),   NOOP,  \
NOOP,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT,  KC_SLSH,   NOOP,  \
                           ESC_MED, GAMING,    BASE,    DEL_FUN, BSP_NUM,                                    \
                                   SPC_NAV, TAB_MOU,    ENT_SYM


// clang-format on

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 12-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 36 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, R11,        \
    L12, L13, L14, L15, L16, L17, R18, R19, R20, R21, R22, R23,        \
    L24, L25, L26, L27, L28, L29, R30, R31, R32, R33, R34, R35,        \
    ...)                                                               \
        L00,         L01,         L02,         L03,         L04,  L05  \
        R06,         R07,         R08,         R09,         R10,  R11  \
        L12,         L13,         L14,         L15,         L16,  L17  \
        R18,         R19,         R20,         R21,         R22,  R23  \
        L24,  LGUI_T(L25), LALT_T(L26), LCTL_T(L27), LSFT_T(L28), L29, \
        R30,  RSFT_T(R31), RCTL_T(R32), LALT_T(R33), RGUI_T(R34), R35, \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(LAYOUT_LAYER_BASE),
    [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
    [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
    [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
    [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
    [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
    [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
    [LAYER_GAMING] = LAYOUT_wrapper(LAYOUT_LAYER_GAMING),
    [LAYER_COLEMAK] = LAYOUT_wrapper(LAYOUT_LAYER_COLEMAK),
};

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
