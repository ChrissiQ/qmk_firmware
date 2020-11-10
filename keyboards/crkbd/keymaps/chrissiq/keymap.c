/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WORKMAN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _XCV 4

#define CTRLESC LCTL(KC_ESC)
#define H_XCV LT(_XCV, KC_H)
#define KC_COPY LGUI(KC_C)
#define KC_CUT LGUI(KC_X)
#define KC_PASTE LGUI(KC_V)
#define S_SAVE TD(_S_SAVE)
#define A_ALL TD(_A_ALL)
#define Z_UNDO TD(_Z_UNDO)
#define R_REDO TD(_R_REDO)
#define F_FIND TD(_F_FIND)
#define K_MD1 MT(MOD_LALT | MOD_LSFT, KC_K)
#define L_MD2 MT(MOD_LALT | (MOD_LCTL | MOD_LSFT), KC_L)

bool is_alt_tab_active = false;

enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  ALTTAB,
  SLTTAB
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    DOUBLE_HOLD,
    DOUBLE_TAP
};

// Tap dance enums
enum {
    _S_SAVE,
    _A_ALL,
    _Z_UNDO,
    _R_REDO,
    _F_FIND
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WORKMAN] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_D,  R_REDO,    KC_W,    KC_B,                         KC_J,  F_FIND,    KC_U,    KC_P, KC_SCLN, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,   A_ALL,  S_SAVE,   H_XCV,    KC_T,    KC_G,                         KC_Y,    KC_N,    KC_E,    KC_O,  KC_I,   KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  Z_UNDO,    KC_X,    KC_M,    KC_C,    KC_V,                        K_MD1,   L_MD2, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            LOWER,  KC_ENT, KC_LSFT,    KC_LGUI,  KC_SPC,   RAISE \
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE,  KC_DEL, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, XXXXXXX,                      XXXXXXX, KC_RPRN, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, CTRLESC, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, XXXXXXX,                      XXXXXXX, KC_RCBR, KC_MINS,  KC_EQL, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, XXXXXXX,                      XXXXXXX, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  ALTTAB,  SLTTAB,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_XCV] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_CUT, KC_COPY, _______,KC_PASTE, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef SSD1306OLED
      set_keylog(keycode, record);
    #endif
    // set_timelog();
  }

  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        if (is_alt_tab_active) {
          is_alt_tab_active = false;
          unregister_code(KC_LGUI);
        }
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case ALTTAB:
        if (record->event.pressed) {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LGUI);
          }
          register_code(KC_TAB);
        } else {
          unregister_code(KC_TAB);
        }
        return false;
    case SLTTAB: // shift alt tab
        if (record->event.pressed) {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LGUI);
          }
          register_code(KC_LSFT);
          register_code(KC_TAB);
        } else {
          unregister_code(KC_TAB);
          unregister_code(KC_LSFT);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

// TAP DANCES
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    return SINGLE_TAP;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  } else return 4; // Any number higher than the maximum state value you return above
}

// S TAP DANCE
static tap s_tap_state = {
    .is_press_action = true,
    .state = 0
};
void s_finished(qk_tap_dance_state_t *state, void *user_data) {
    s_tap_state.state = cur_dance(state);
    switch (s_tap_state.state) {
        case SINGLE_TAP: register_code(KC_S); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_S)); break;
        case DOUBLE_TAP: tap_code(KC_S); register_code(KC_S); break;
    }
}
void s_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (s_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_S); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_S)); break;
        case DOUBLE_TAP: unregister_code(KC_S); break;
    }
    s_tap_state.state = 0;
}

// A TAP DANCE
static tap a_tap_state = {
    .is_press_action = true,
    .state = 0
};
void a_finished(qk_tap_dance_state_t *state, void *user_data) {
    a_tap_state.state = cur_dance(state);
    switch (a_tap_state.state) {
        case SINGLE_TAP: register_code(KC_A); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_A)); break;
        case DOUBLE_TAP: tap_code(KC_A); register_code(KC_A); break;
    }
}
void a_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (a_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_A); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_A)); break;
        case DOUBLE_TAP: unregister_code(KC_A); break;
    }
    a_tap_state.state = 0;
}

// Z TAP DANCE
static tap z_tap_state = {
    .is_press_action = true,
    .state = 0
};
void z_finished(qk_tap_dance_state_t *state, void *user_data) {
    z_tap_state.state = cur_dance(state);
    switch (z_tap_state.state) {
        case SINGLE_TAP: register_code(KC_Z); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_Z)); break;
        case DOUBLE_TAP: tap_code(KC_Z); register_code(KC_Z); break;
    }
}
void z_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (z_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Z); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_Z)); break;
        case DOUBLE_TAP: unregister_code(KC_Z); break;
    }
    z_tap_state.state = 0;
}

// R TAP DANCE
static tap r_tap_state = {
    .is_press_action = true,
    .state = 0
};
void r_finished(qk_tap_dance_state_t *state, void *user_data) {
    r_tap_state.state = cur_dance(state);
    switch (r_tap_state.state) {
        case SINGLE_TAP: register_code(KC_R); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: tap_code(KC_R); register_code(KC_R); break;
    }
}
void r_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (r_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_R); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: unregister_code(KC_R); break;
    }
    r_tap_state.state = 0;
}

// F TAP DANCE
static tap f_tap_state = {
    .is_press_action = true,
    .state = 0
};
void f_finished(qk_tap_dance_state_t *state, void *user_data) {
    f_tap_state.state = cur_dance(state);
    switch (f_tap_state.state) {
        case SINGLE_TAP: register_code(KC_F); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: tap_code(KC_F); register_code(KC_F); break;
    }
}
void f_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (f_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_F); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: unregister_code(KC_F); break;
    }
    f_tap_state.state = 0;
}

// TAP DANCE ACTIONS
qk_tap_dance_action_t tap_dance_actions[] = {
    [_S_SAVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),
    [_A_ALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_finished, a_reset),
    [_Z_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, z_finished, z_reset),
    [_R_REDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_finished, r_reset),
    [_F_FIND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset)
};
