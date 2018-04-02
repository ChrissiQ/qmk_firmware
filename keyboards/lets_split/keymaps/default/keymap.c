#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _WORKMAN 3
#define _LOWER 4
#define _RAISE 5
#define _NAV 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  WORKMAN,
  LOWER,
  RAISE,
  NAV,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |  Alt |Adjust|Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_LCTRL,KC_LGUI, KC_LALT, ADJUST,  LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = KEYMAP( \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Adjust|Lower |Enter |Space |Raise | Nav  |RShift| RGUI | Caps |
 * |      |      |      |      |      |(Shft)|      |      |      |      |      | Lock |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,          KC_J,    KC_F,    KC_U,      KC_P,    KC_SCLN, KC_BSLS, \
  KC_BSPC, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,          KC_Y,    KC_N,    KC_E,      KC_O,    KC_I,    KC_QUOT, \
  KC_TAB,  KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,          KC_K,    KC_L,    KC_COMM,   KC_DOT,  KC_SLSH, KC_DEL, \
  KC_LCTL, KC_LGUI, KC_LALT, ADJUST,  LOWER,   SFT_T(KC_ENT), KC_SPC,  RAISE,   TT(_NAV),  KC_RSFT, KC_RGUI, KC_LCAP \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   |  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Bksp |      |      |      |   (  |      |      |   )  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      |Enter |Space |      | Next | Vol- | Vol+ | Play |
 * |      |      |      |      |      |(Shft)|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR,    KC_ASTR, KC_PIPE, _______, _______, \
  KC_BSPC, _______, _______, _______, KC_LPRN, _______,       _______, KC_RPRN,    _______, _______, _______, _______, \
  KC_TAB,  _______, _______, _______, _______, SFT_T(KC_ENT), KC_SPC,  _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |      |   _  |   +  |   {  |      |      |   }  |   -  |   =  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |      |      |      |   [  |      |      |   ]  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Enter |Space |      |      |      |      |      |
 * |      |      |      |      |      |(Shft)|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  KC_BSPC, _______, KC_UNDS, KC_PLUS, KC_LCBR, _______,        _______, KC_RCBR, KC_MINS, KC_EQL,  _______, _______, \
  KC_TAB,  _______, _______, _______, KC_LBRC, _______,        _______, KC_RBRC, _______, _______, _______, _______, \
  _______,  _______, _______, _______, _______, SFT_T(KC_ENT), KC_SPC,  _______, _______, _______, _______, _______ \
),

/* Navigate
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |R Clck|L Clck|      |      |L Clck|R Clck|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Ms Lft|Ms Dn |Ms Up |Ms Rgt|      |      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |MsW Lt|MsW Dn|MsW Up|MsW Rt|      |      | Home | PgDn | PgUp | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Enter |Space |      |      |      |      |      |
 * |      |      |      |      |      |(Shft)|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] =  KEYMAP( \
  _______, _______, _______, KC_BTN2, KC_BTN1, _______,       _______, KC_BTN1, KC_BTN2, _______, _______, _______, \
  _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
  _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,       _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, \
  _______, _______, _______, _______, _______, SFT_T(KC_ENT), KC_SPC,  _______, _______, _______, _______, _______ \
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|      |      |Qwerty|Colemk|Dvorak|Workmn|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, AU_ON,   AU_OFF,  _______, _______, QWERTY,  COLEMAK, DVORAK,  WORKMAN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_workman[][2]    = SONG(ZELDA_TREASURE);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_workman);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
