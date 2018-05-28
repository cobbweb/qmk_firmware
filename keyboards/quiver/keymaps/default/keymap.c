/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "quiver.h"


#define _BL 0
#define _L0 1
#define _L1 2
#define _L2 3
#define _L3 4

#define LCPO_KEY KC_9
#define RCPC_KEY KC_0


enum my_keycodes {
  KC_LCPO, // Left control, paren open
  KC_RCPC, // Right control, paren close
  KC_ALTTAB,
  KC_ALTGRV,
  KC_ENTFN = LT(_L0, KC_ENT),
  KC_SPCFN = LT(_L0, KC_SPC),
  KC_LCBRFN,
  KC_RCBRFN,
  KC_NUMA = LT(_L1, KC_Z)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_BL] = KEYMAP( /* Base */ \
  KC_LCBRFN,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,    KC_O,   KC_P,     KC_RCBRFN, \
  KC_LCPO,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,    KC_L,   KC_SCLN,  KC_RCPC, \
 SFT_T(KC_LBRC), KC_NUMA,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM, KC_DOT, KC_SLSH,  SFT_T(KC_RBRC), \
                ALT_T(KC_TAB), GUI_T(KC_BSPC), KC_SPCFN,                KC_ENTFN,   GUI_T(KC_DEL),   ALT_T(KC_ESC) \
),

[_L0] = KEYMAP( /* ENTFN Layer */ \
  KC_GRAVE,   KC_EXLM,    KC_AT,  KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR, KC_MINS, KC_EQL,     KC_QUOT, \
  _______,    _______,  KC_HOME,  KC_PGUP, KC_PGDN,   KC_END,   KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT, RSFT(KC_QUOT), _______, \
  _______,    _______,  _______,  _______, KC_ALTGRV, KC_ALTTAB, _______, KC_UNDS,  _______, _______, KC_BSLASH,  _______, \
                                  /* _______, _______, MO(_L3),        _______, _______, _______ \ */
                                  _______, _______, _______,        _______, _______, _______ \
),

/* [_L02] = KEYMAP( /1* SPCFN Layer *1/ \ */
/*   KC_GRAVE,   KC_EXLM,    KC_AT,  KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR, KC_MINS, KC_EQL,     KC_QUOT, \ */
/*   _______,    _______,  KC_HOME,  KC_PGUP, KC_PGDN,   KC_END,   KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT, RSFT(KC_QUOT), _______, \ */
/*   _______,    _______,  _______,  _______, KC_ALTGRV, KC_ALTTAB, _______, KC_UNDS,  _______, _______, KC_BSLASH,  _______, \ */
                                  /* _______, _______, _______,        MO(_L3), _______, _______ \ */
/* ), */

[_L1] = KEYMAP( /* Fn1 Layer */ \
  _______, _______,  _______,  _______,  _______,  _______,  _______,     KC_7,     KC_8,     KC_9,   KC_EQL,     KC_CIRC, \
  _______, _______,  _______,  _______,  _______,  KC_LPRN,  KC_RPRN,     KC_4,     KC_5,     KC_6,   KC_MINS,    KC_PLUS, \
  _______, _______,  _______,  _______,    KC_F11,  KC_F12,     KC_0,     KC_1,     KC_2,     KC_3,   KC_SLSH,    KC_ASTR, \
                              _______, _______, _______,            KC_0, KC_DOT, _______ \
),

[_L2] = KEYMAP( /* Fn1 Layer */ \
  _______, LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5), LCTL(KC_6), LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), LCTL(KC_0), _______, \
  _______,      KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,     KC_F10, _______, \
  _______, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), _______, \
                              KC_MPRV, KC_MUTE, KC_VOLD,            KC_VOLU, KC_MPLY, KC_MNXT \
)
};


static uint16_t scs_timer[2] = {0, 0};
static uint16_t ltcb_timer[2] = {0, 0};
static uint16_t alt_holding = 0;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_ENTFN: {
       if (!record->event.pressed && alt_holding) {
         unregister_mods(MOD_BIT(KC_LALT));
         alt_holding = 0;
         
       }
       return true;
    }
                   
    case KC_SPCFN: {
       if (!record->event.pressed && alt_holding) {
         unregister_mods(MOD_BIT(KC_LALT));
         alt_holding = 0;
       }
       return true;
    }
                   
    case KC_LCBRFN: {
       if (!record->event.pressed && alt_holding) {
         unregister_mods(MOD_BIT(KC_LALT));
         alt_holding = 0;
       }
      
       if (record->event.pressed) {
         ltcb_timer[0] = timer_read();
         layer_on(_L2);
       } else {
         layer_off(_L2);
         if (timer_elapsed(ltcb_timer[0]) < TAPPING_TERM) {
           register_mods(MOD_BIT(KC_LSFT));
           register_code(KC_LBRC);
           unregister_code(KC_LBRC);
           unregister_mods(MOD_BIT(KC_LSFT));
         }
       }
       
       return false;
    }
                   
    case KC_RCBRFN: {
       if (!record->event.pressed && alt_holding) {
         unregister_mods(MOD_BIT(KC_LALT));
         alt_holding = 0;
         
       }
      
       if (record->event.pressed) {
         ltcb_timer[1] = timer_read();
         layer_on(_L2);
       } else {
         layer_off(_L2);
         if (timer_elapsed(ltcb_timer[1]) < TAPPING_TERM) {
           register_mods(MOD_BIT(KC_LSFT));
           register_code(KC_RBRC);
           unregister_code(KC_RBRC);
           unregister_mods(MOD_BIT(KC_LSFT));
         }
       }
       
       return false;
    }
                   
    case KC_ALTTAB: { 
      if (!alt_holding) {
        register_mods(MOD_BIT(KC_LALT));
        alt_holding = 1;
      }
      if (record->event.pressed) {
        register_code(KC_TAB);
        unregister_code(KC_TAB);
      }
      return false;
    }
                   
    case KC_ALTGRV: { 
      if (!alt_holding) {
        register_mods(MOD_BIT(KC_LALT));
        alt_holding = 1;
      }
      if (record->event.pressed) {
        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);
      }
      return false;
    }
                    
    case KC_LCPO: {
      if (record->event.pressed) {
        scs_timer[0] = timer_read();
        register_mods(MOD_BIT(KC_LCTRL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTRL));
        if (timer_elapsed(scs_timer[0]) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(LCPO_KEY);
          unregister_code(LCPO_KEY);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    }

    case KC_RCPC: {
      if (record->event.pressed) {
        scs_timer[1] = timer_read();
        register_mods(MOD_BIT(KC_LCTRL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTRL));
        if (timer_elapsed(scs_timer[1]) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(RCPC_KEY);
          unregister_code(RCPC_KEY);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    }
                  
    default: {
      break;
    }
  }
  
  return true;
}

