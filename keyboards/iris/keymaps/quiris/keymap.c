#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _NUM 3

enum custom_keycodes {
  // Layers
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,

  // Pinky buttons
  KC_CLPN, // h: ctrl, t: (
  KC_CRPN, // h: ctrl, t: )
  KC_SLSQ = SFT_T(KC_LBRC), // h: shift, t: [
  KC_SRSQ = SFT_T(KC_RBRC), // h: shift, t: ]

  // Thumb buttons
  KC_SPFN = LT(_LOWER, KC_SPC),
  KC_ENFN = LT(_LOWER, KC_ENT),
  KC_ALTTAB = ALT_T(KC_TAB),
  KC_RASEBSPC = LT(_RAISE, KC_BSPC),
  KC_GUIDEL = GUI_T(KC_DEL),
  KC_ALTESC = ALT_T(KC_ESC),
  
  // Others
  KC_NUMZ = LT(_NUM, KC_Z),
  KC_DBLQ = RSFT(KC_QUOT),
  KC_KVM, // define in process hook
  KC_AGRV,
  KC_ATAB,
  KC_CAPC = LCTL(LALT(LSFT(KC_4)))
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)
#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_ALTT KC_ALTTAB
#define KC_RBSP KC_RASEBSPC
#define KC_GDEL KC_GUIDEL
#define KC_ALTE KC_ALTESC

// random Iris keycodes
#define KC_BL_S BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

// Ctrl + number
#define KC_CTL1 LCTL(KC_1)
#define KC_CTL2 LCTL(KC_2)
#define KC_CTL3 LCTL(KC_3)
#define KC_CTL4 LCTL(KC_4)
#define KC_CTL5 LCTL(KC_5)
#define KC_CTL6 LCTL(KC_6)
#define KC_CTL7 LCTL(KC_7)
#define KC_CTL8 LCTL(KC_8)
#define KC_CTL9 LCTL(KC_9)
#define KC_CTL0 LCTL(KC_0)

// GUI + number
#define KC_GUI1 LGUI(KC_1)
#define KC_GUI2 LGUI(KC_2)
#define KC_GUI3 LGUI(KC_3)
#define KC_GUI4 LGUI(KC_4)
#define KC_GUI5 LGUI(KC_5)
#define KC_GUI6 LGUI(KC_6)
#define KC_GUI7 LGUI(KC_7)
#define KC_GUI8 LGUI(KC_8)
#define KC_GUI9 LGUI(KC_9)
#define KC_GUI0 LGUI(KC_0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     LABK, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,RABK,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCBR, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,RCBR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CLPN, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,CRPN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SLSQ,NUMZ, X  , C  , V  , B  ,LGUI,     RASE, N  , M  ,COMM,DOT ,SLSH,SRSQ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       ALTT,RBSP,SPFN,         ENFN,GDEL,ALTE
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,MINS, EQL,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,HOME,PGUP,PGDN,END ,               LEFT,DOWN, UP ,RGHT,DBLQ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,SLCK,NLCK, KVM,AGRV,ATAB,    ,         ,    ,UNDS,    ,    ,BSLS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,   
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,GUI1,GUI2,GUI3,GUI4,GUI5,               GUI6,GUI7,GUI8,GUI9,GUI0,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,CTL1,CTL2,CTL3,CTL4,CTL5,               CTL6,CTL7,CTL8,CTL9,CTL0,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,CAPC,    ,    ,MPRV,VOLD,    ,     MPLY,VOLU,MNXT,MUTE,    , RST,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUM] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , 7  , 8  , 9  ,EQL ,CIRC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , 4  , 5  , 6  ,MINS,PLUS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , 1  , 2  , 3  ,SLSH,ASTR,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             , 0  , DOT
  //                  `----+----+----'        `----+----+----'
  //),

  //[_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //     ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  // RTOG,RMOD,RHUI,RSAI,RVAI,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //     ,DBUG,RHUD,RSAD,RVAD,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  // BL_S,RST ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,   ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                       ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};

static uint16_t mod_tap_timers[2] = {0,0};
static uint16_t alt_holding = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Check if we're still faux-holding the alt key down, and release it
  // Only stay holding when pressing KC_AGRV or KC_ATAB
  if (keycode != KC_AGRV && keycode != KC_ATAB && !record->event.pressed && alt_holding) {
    unregister_mods(MOD_BIT(KC_LALT));
    alt_holding = 0;
  }
  
  switch (keycode) {
    case KC_CLPN: {
      if (record->event.pressed) {
        mod_tap_timers[0] = timer_read();
        register_mods(MOD_BIT(KC_LCTRL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTRL));
        if (timer_elapsed(mod_tap_timers[0]) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    }

    case KC_CRPN: {
      if (record->event.pressed) {
        mod_tap_timers[1] = timer_read();
        register_mods(MOD_BIT(KC_LCTRL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTRL));
        if (timer_elapsed(mod_tap_timers[1]) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(KC_0);
          unregister_code(KC_0);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    }

    case KC_KVM: {
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_SCROLLLOCK)SS_TAP(X_SCROLLLOCK)SS_TAP(X_ENTER));
      }
      return false;
    }
                 
    case KC_ATAB: {
      if (record->event.pressed) {
        if (!alt_holding) {
          register_mods(MOD_BIT(KC_LALT));
          alt_holding = 1;
        }
        register_code(KC_TAB);
        unregister_code(KC_TAB);
      }
      return false;
    }
                 
    case KC_AGRV: {
      if (record->event.pressed) {
        if (!alt_holding) {
          register_mods(MOD_BIT(KC_LALT));
          alt_holding = 1;
        }
        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);
      }
    }
    return false;
  }
  return true;
}
