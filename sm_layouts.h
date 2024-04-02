#pragma once

#include QMK_KEYBOARD_H
#include "sm_layouts_keycodes.h"

#define NOT_INIT MATRIX_ROWS + MATRIX_COLS
#define NOT_FOUND NOT_INIT + 1

static uint16_t sm_layouts_keycode_to_shortcut_row[SM_LAYOUTS_SIZE] = {
    #ifdef SM_LAYOUTS_CYR_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT,
    #endif

    #ifdef SM_LAYOUTS_CYR_MAC_SYMBOLS_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT,
    #endif

    #ifdef SM_LAYOUTS_CYR_WIN_SYMBOLS_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT,
    #endif
};

static uint16_t sm_layouts_keycode_to_shortcut_col[SM_LAYOUTS_SIZE] = {
    #ifdef SM_LAYOUTS_CYR_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT, NOT_INIT,
    #endif

    #ifdef SM_LAYOUTS_CYR_MAC_SYMBOLS_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT,
    #endif

    #ifdef SM_LAYOUTS_CYR_WIN_SYMBOLS_ENABLED
    NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT, NOT_INIT,
    NOT_INIT, NOT_INIT,
    #endif
};

#ifdef CAPS_WORD_ENABLE
#define SM_L_CW_CHECK is_caps_word_on()
#else
#define SM_L_CW_CHECK false
#endif

#define CASE_UC_LU(key, uc_l, uc_u)                         \
        case key: {                                         \
            uint8_t mods = get_mods()                       \
                | get_oneshot_mods()                        \
                | get_weak_mods();                          \
            if (mods == 0) {                                \
                register_unicode(                           \
                    SM_L_CW_CHECK ? uc_u : uc_l);           \
            } else if (mods & ~MOD_MASK_SHIFT) {            \
                sm_layouts_keycode_to_shortcut_tap(keycode);\
            } else {                                        \
                register_unicode(                           \
                    SM_L_CW_CHECK ? uc_l : uc_u);           \
            }                                               \
            return false;                                   \
        }


#define CASE_UC_L(key, uc_l, kc_u)                          \
        case key: {                                         \
            uint8_t mods = get_mods()                       \
                | get_oneshot_mods()                        \
                | get_weak_mods();                          \
            if (mods == 0) {                                \
                register_unicode(uc_l);                     \
            } else if (mods & ~MOD_MASK_SHIFT) {            \
                sm_layouts_keycode_to_shortcut_tap(keycode);\
            } else {                                        \
                unregister_mods(mods);                      \
                tap_code16(kc_u);                           \
                register_mods(mods);                        \
            }                                               \
            return false;                                   \
        }


#define CASE_UC_U(key, kc_l, uc_u)                          \
        case key: {                                         \
            uint8_t mods = get_mods()                       \
                | get_oneshot_mods()                        \
                | get_weak_mods();                          \
            if (mods == 0) {                                \
                tap_code16(kc_l);                           \
            } else if (mods & ~MOD_MASK_SHIFT) {            \
                sm_layouts_keycode_to_shortcut_tap(keycode);\
            } else {                                        \
                register_unicode(uc_u);                     \
            }                                               \
            return false;                                   \
        }


#define CASE_BASIC(key, kc_l, kc_u)                         \
        case key: {                                         \
            uint8_t mods = get_mods()                       \
                | get_oneshot_mods()                        \
                | get_weak_mods();                          \
            if (mods == 0) {                                \
                tap_code16(kc_l);                           \
            } else if (mods & ~MOD_MASK_SHIFT) {            \
                sm_layouts_keycode_to_shortcut_tap(keycode);\
            } else {                                        \
                unregister_mods(mods);                      \
                tap_code16(kc_u);                           \
                register_mods(mods);                        \
            }                                               \
            return false;                                   \
        }


void sm_layouts_make_shortcut_tap(uint8_t row, uint8_t col) {
    uint8_t return_layer = get_highest_layer(layer_state);
    layer_move(SM_LAYOUTS_SHORTCUT_LAYER);
    keyevent_t  event  = MAKE_KEYEVENT(row, col, true);
    keyrecord_t record = {.event = event};
    process_record(&record);
    event.pressed = false;
    record.event = event;
    process_record(&record);
    layer_move(return_layer);
 }

void sm_layouts_keycode_to_shortcut_tap(uint16_t sm_layouts_keycode) {
    uint8_t idx = sm_layouts_keycode % SM_LAYOUTS_SIZE;
    uint16_t row = sm_layouts_keycode_to_shortcut_row[idx];
    uint16_t col = sm_layouts_keycode_to_shortcut_col[idx];

    if (row != NOT_INIT || col != NOT_INIT) {
        sm_layouts_make_shortcut_tap(row, col);
        return;
    }

    if (sm_layouts_keycode <= SM_LAYOUTS_BEGIN || sm_layouts_keycode >= SM_LAYOUTS_END) {
        return;
    }

    int layers = sizeof(keymaps) / sizeof(keymaps[0]);
    for(int layer = 0; layer < layers; layer++) {
        for(int row = 0; row < MATRIX_ROWS; row++) {
            for(int col = 0; col < MATRIX_COLS; col++) {
                 if (keymaps[layer][row][col] == sm_layouts_keycode) {
                      sm_layouts_keycode_to_shortcut_row[idx] = row;
                      sm_layouts_keycode_to_shortcut_col[idx] = col;
                      sm_layouts_make_shortcut_tap(row, col);
                      return;
                 }
            }
        }
    }

    sm_layouts_keycode_to_shortcut_row[idx] = NOT_FOUND;
    sm_layouts_keycode_to_shortcut_col[idx] = NOT_FOUND;
}


bool process_sm_layouts_tap(uint16_t keycode) {
    switch (keycode) {
        #ifdef SM_LAYOUTS_CYR_ENABLED
        CASE_UC_LU(CYR_YY, 0x0439, 0x0419);
        CASE_UC_LU(CYR_CC, 0x0446, 0x0426);
        CASE_UC_LU(CYR_U, 0x0443, 0x0423);
        CASE_UC_LU(CYR_K, 0x043A, 0x041A);
        CASE_UC_LU(CYR_E, 0x0435, 0x0415);
        CASE_UC_LU(CYR_F, 0x0444, 0x0424);
        CASE_UC_LU(CYR_YI, 0x044B, 0x042B);
        CASE_UC_LU(CYR_V, 0x0432, 0x0412);
        CASE_UC_LU(CYR_A, 0x0430, 0x0410);
        CASE_UC_LU(CYR_P, 0x043F, 0x041F);
        CASE_UC_LU(CYR_YA, 0x044F, 0x042F);
        CASE_UC_LU(CYR_CH, 0x0447, 0x0427);
        CASE_UC_LU(CYR_SS, 0x0441, 0x0421);
        CASE_UC_LU(CYR_M, 0x043C, 0x041C);
        CASE_UC_LU(CYR_I, 0x0438, 0x0418);
        CASE_UC_LU(CYR_N, 0x043D, 0x041D);
        CASE_UC_LU(CYR_G, 0x0433, 0x0413);
        CASE_UC_LU(CYR_SH, 0x0448, 0x0428);
        CASE_UC_LU(CYR_SCH, 0x0449, 0x0429);
        CASE_UC_LU(CYR_ZZ, 0x0437, 0x0417);
        CASE_UC_LU(CYR_H, 0x0445, 0x0425);
        CASE_UC_LU(CYR_R, 0x0440, 0x0420);
        CASE_UC_LU(CYR_O, 0x043E, 0x041E);
        CASE_UC_LU(CYR_YO, 0x0451, 0x0401);
        CASE_UC_LU(CYR_L, 0x043B, 0x041B);
        CASE_UC_LU(CYR_D, 0x0434, 0x0414);
        CASE_UC_LU(CYR_YE, 0x044D, 0x042D);
        CASE_UC_LU(CYR_T, 0x0442, 0x0422);
        CASE_UC_LU(CYR_SFT, 0x044C, 0x042C);
        CASE_UC_LU(CYR_B, 0x0431, 0x0411);
        CASE_UC_LU(CYR_YU, 0x044E, 0x042E);
        CASE_UC_LU(CYR_ZH, 0x0436, 0x0416);
        CASE_UC_LU(CYR_SLD, 0x044A, 0x042A);
        #endif

        #ifdef SM_LAYOUTS_CYR_WIN_SYMBOLS_ENABLED
        CASE_BASIC(CYR_W1, KC_1, KC_EXLM);
        CASE_BASIC(CYR_W2, KC_2, KC_DQUO);
        CASE_UC_U(CYR_W3, KC_3, 0x2116);
        CASE_BASIC(CYR_W4, KC_4, KC_SCLN);
        CASE_BASIC(CYR_W5, KC_5, KC_PERC);
        CASE_BASIC(CYR_W6, KC_6, KC_COLN);
        CASE_BASIC(CYR_W7, KC_7, KC_QUES);
        CASE_BASIC(CYR_W8, KC_8, KC_ASTR);
        CASE_BASIC(CYR_W9, KC_9, KC_LPRN);
        CASE_BASIC(CYR_W0, KC_0, KC_RPRN);
        CASE_BASIC(CYR_WDOT, KC_DOT, KC_COMMA);
        CASE_BASIC(CYR_WSLASH, KC_BSLS, KC_SLSH);
        #endif

        #ifdef SM_LAYOUTS_CYR_MAC_SYMBOLS_ENABLED
        CASE_BASIC(CYR_M1, KC_1, KC_EXLM);
        CASE_BASIC(CYR_M2, KC_2, KC_DQUO);
        CASE_UC_U(CYR_M3, KC_3, 0x2116);
        CASE_BASIC(CYR_M4, KC_4, KC_PERC);
        CASE_BASIC(CYR_M5, KC_5, KC_COLN);
        CASE_BASIC(CYR_M6, KC_6, KC_COMMA);
        CASE_BASIC(CYR_M7, KC_7, KC_DOT);
        CASE_BASIC(CYR_M8, KC_8, KC_SCLN);
        CASE_BASIC(CYR_M9, KC_9, KC_LPRN);
        CASE_BASIC(CYR_M0, KC_0, KC_RPRN);
        CASE_BASIC(CYR_MSLASH, KC_SLSH, KC_QUES);
        CASE_BASIC(CYR_MBRC, KC_LBRC, KC_RBRC);
        #endif

        default:
            return true;
    }

    return true;
}

bool process_sm_layouts(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    return process_sm_layouts_tap(keycode);
}



