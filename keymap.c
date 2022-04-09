#include QMK_KEYBOARD_H
#include <quantum/pointing_device.h>
#include "version.h"
#include "raw_hid.h"

#include "arbitrary_keycode/include.h"

#define CUSTOM_SAFE_RANGE ML_SAFE_RANGE
#include "lang_shift/include.h"
#include "combo/include.h"
#include "color/include.h"
#include "tt/include.h"
#include "repeat/include.h"

extern bool mcp23018_leds[3];

enum custom_keycodes {
  KEYCODES_START = CUSTOM_SAFE_RANGE,

  // Wow, such empty

  NEW_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE NEW_NEW_SAFE_RANGE
};

#define MY_layout( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35,      \
    k40, k41, k42, k43, k44,           \
    k53, \
    k50, k51, k52, \
    \
    k60, k61, k62, k63, k64, k65, k66, \
    k70, k71, k72, k73, k74, k75, k76, \
    k80, k81, k82, k83, k84, k85, k86, \
    k91, k92, k93, k94, k95, k96, \
    ka2, ka3, ka4, ka5, ka6, \
    kb3,\
    kb4, kb5, kb6 \
) \
LAYOUT_moonlander( \
    k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
    k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
    k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
    k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
    k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                        k50, k51, k52,   kb4, kb5, kb6 \
)

// Shift keys
#define SH_TAB S(KC_TAB)

// Ctrl+Shift keys
#define CS_T LCTL(S(KC_T))
#define CS_K LCTL(S(KC_K))
#define CS_M LCTL(S(KC_M))
#define CS_P LCTL(S(KC_P))

// Alt keys
#define AL_UP LALT(KC_UP)
#define AL_PSCR LALT(KC_PSCR)

// Gui keys
#define WN_1 LGUI(KC_1)
#define WN_2 LGUI(KC_2)
#define WN_3 LGUI(KC_3)
#define WN_4 LGUI(KC_4)
#define WN_5 LGUI(KC_5)
#define WN_6 LGUI(KC_6)
#define WN_7 LGUI(KC_7)
#define WN_8 LGUI(KC_8)
#define WN_9 LGUI(KC_9)
#define WN_F1 LGUI(KC_F1)
#define WN_F2 LGUI(KC_F2)
#define WN_F3 LGUI(KC_F3)
#define WN_Q LGUI(KC_Q)
#define WN_L LGUI(KC_L)

// Ctrl keys
#define CT_LEFT LCTL(KC_LEFT)
#define CT_UP LCTL(KC_UP)
#define CT_DOWN LCTL(KC_DOWN)
#define CT_RGHT LCTL(KC_RGHT)
#define CT_ENT LCTL(KC_ENT)
#define CT_BSPC LCTL(KC_BSPC)
#define CT_1 LCTL(KC_1)
#define CT_2 LCTL(KC_2)
#define CT_T LCTL(KC_T)
#define CT_W LCTL(KC_W)
#define CT_J LCTL(KC_J)
#define CT_G LCTL(KC_G)
#define CT_S LCTL(KC_S)
#define CT_F LCTL(KC_F)
#define CT_A LCTL(KC_A)
#define CT_S LCTL(KC_S)
#define CT_F5 LCTL(KC_F5)
#define CT_PGUP LCTL(KC_PGUP)
#define CT_PGDN LCTL(KC_PGDN)
#define CT_X LCTL(KC_X)
#define CT_C LCTL(KC_C)
#define CT_V LCTL(KC_V)
#define CT_PLUS LCTL(KC_EQL)
#define CT_MINS LCTL(KC_MINS)
#define CT_BSLS LCTL(KC_BSLS)

#define RGB_LYR TOGGLE_LAYER_COLOR

// Chords
// Left Index
#define CMB_CTC CMB_000
#define CMB_CTV CMB_001

// Shifted index keys
#define CMB_CAC CMB_002
#define CMB_CAV CMB_003

// Right Index
#define CMB_CTS CMB_004
#define CMB_CMSP CMB_005

// Left Thumb
#define CMB_SFT CMB_006
#define CMB_BSP CMB_007
#define CMB_ENT CMB_008
#define CMB_CTL CMB_009

// Left Left Thumb
#define CMB_LYV CMB_010
#define CMB_LYG CMB_011

// Right Thumb
#define CMB_LAN CMB_012
#define CMB_DOT CMB_013
#define CMB_SPC CMB_014
#define CMB_ALT CMB_015

// Russian index keys on letters
#define CMS_O CMB_016
#define CMS_MZ CMB_017
#define CMS_S_O CMB_018
#define CMS_S_MZ CMB_019

// Left number-row
#define CMB_PLS CMB_020
#define CMB_SCL CMB_021
#define CMB_GRV CMB_022
#define CMB_EXL CMB_023
#define CMB_ASR CMB_024

// Right number-row
#define CMB_EQL CMB_025
#define CMB_CLN CMB_026
#define CMB_CMM CMB_027
#define CMB_QUE CMB_028
#define CMB_SLS CMB_029

// Brackets on red layer, order: 1 - (), 2 - [], 3 - {}, 4 - <>
#define CMB_LB1 CMB_030
#define CMB_RB1 CMB_031
#define CMB_LB2 CMB_032
#define CMB_RB2 CMB_033
#define CMB_LB3 CMB_034
#define CMB_RB3 CMB_035
#define CMB_LB4 CMB_036
#define CMB_RB4 CMB_037

// Brackets on XCompose layer
#define CMB_LTR CMB_038
#define CMB_RTR CMB_039
#define CMB_LCR CMB_040
#define CMB_RCR CMB_041

// Russian index keys on letters
#define CMS_A CMB_042
#define CMS_S_A CMB_044
//#define CMS_S_K CMB_045
#define CMS_ZH CMB_046
#define CMS_SEMICOLN CMB_047
#define CMS_S_ZH CMB_048
#define CMS_S_COLN CMB_049
//#define CMS_N CMB_050
//#define CMS_S_N CMB_051
#define CMS_MINS CMB_052
#define CMS_R CMB_053
#define CMS_T CMB_054
#define CMS_S_R CMB_055
#define CMS_S_T CMB_056

// Digit combos
#define CMS_1 CMB_057
#define CMS_2 CMB_058
#define CMS_3 CMB_059
#define CMS_4 CMB_060
#define CMS_5 CMB_061
#define CMS_6 CMB_062
#define CMS_7 CMB_063
#define CMS_8 CMB_064
#define CMS_9 CMB_065
#define CMS_0 CMB_066

#define CMS_EN_Q CMB_067
#define CMS_EN_W CMB_068
#define CMS_EN_E CMB_069
#define CMS_EN_R CMB_070
#define CMS_EN_T CMB_071
#define CMS_EN_Y CMB_072
#define CMS_EN_U CMB_073
#define CMS_EN_I CMB_074
#define CMS_EN_O CMB_075
#define CMS_EN_P CMB_076

#define CMS_S_EN_Q CMB_077
#define CMS_S_EN_W CMB_078
#define CMS_S_EN_E CMB_079
#define CMS_S_EN_R CMB_080
#define CMS_S_EN_T CMB_081
#define CMS_S_EN_Y CMB_082
#define CMS_S_EN_U CMB_083
#define CMS_S_EN_I CMB_084
#define CMS_S_EN_O CMB_085
#define CMS_S_EN_P CMB_086

#define CMS_RU_J CMB_087
#define CMS_RU_TS CMB_088
#define CMS_RU_U CMB_089
#define CMS_RU_K CMB_090
#define CMS_RU_JE CMB_091
#define CMS_RU_N CMB_092
#define CMS_RU_G CMB_093
#define CMS_RU_SH CMB_094
#define CMS_RU_SC CMB_095
#define CMS_RU_Z CMB_096

#define CMS_S_RU_J CMB_097
#define CMS_S_RU_TS CMB_098
#define CMS_S_RU_U CMB_099
#define CMS_S_RU_K CMB_100
#define CMS_S_RU_JE CMB_101
#define CMS_S_RU_N CMB_102
#define CMS_S_RU_G CMB_103
#define CMS_S_RU_SH CMB_104
#define CMS_S_RU_SC CMB_105
#define CMS_S_RU_Z CMB_106

#define TT_CTJ TT_000

// Add custom keycode processing
#include "xcompose.h"
#include "custom_lang.h"
#include "custom_hotkeys.h"
#include "moonlander_leds.h"
#include "mouse_pixel_move.h"
#include "song_keys.h"

enum Layers {
  L_EN = 0,
  L_EN_S,

  L_RU,
  L_RU_S,

  L_RED,
  L_GREN,
  L_VIOL,
  L_GRAY,
  L_CYAN,
  L_YELW,

  L_GAME,
  L_NUCL,
};

#define TG_RED TG(L_RED)
#define TG_GREN TG(L_GREN)
#define TG_VIOL TG(L_VIOL)
#define TG_GRAY TG(L_GRAY)
#define TG_CYAN TG(L_CYAN)
#define TG_YELW TG(L_YELW)
#define TG_GAME TG(L_GAME)
#define TG_NUCL TG(L_NUCL)

#define MO_RED MO(L_RED)
#define MO_GREN MO(L_GREN)
#define MO_VIOL MO(L_VIOL)
#define MO_GRAY MO(L_GRAY)
#define MO_CYAN MO(L_CYAN)
#define MO_YELW MO(L_YELW)
#define MO_GAME MO(L_GAME)
#define MO_NUCL MO(L_NUCL)

#define TT_RED (TT_000 + L_RED)
#define TT_GREN (TT_000 + L_GREN)
#define TT_VIOL (TT_000 + L_VIOL)
#define TT_GRAY (TT_000 + L_GRAY)
#define TT_CYAN (TT_000 + L_CYAN)
#define TT_YELW (TT_000 + L_YELW)
#define TT_GAME (TT_000 + L_GAME)
#define TT_NUCL (TT_000 + L_NUCL)

// This macros is needed for defining equal layers (including Shift layer) for English and Russian languages. At the end their differences will be only in letters
#define LANG_TWO_LAYERS(\
  L_DEFAULT, L_SHIFT,\
  \
  /* Left hand */ \
       LU1, LU2, LU3, LU4, LU5, \
       LH1, LH2, LH3, LH4, LH5, \
  LD0, LD1, LD2, LD3, LD4, LD5, \
  /* Right hand */ \
  RU1, RU2, RU3, RU4, RU5, \
  RH1, RH2, RH3, RH4, RH5, RH6, \
  RD1, RD2, RD3, RD4, RD5, RD6, \
  \
  /* ---------------------------- Shift layer ---------------------------- */ \
  /* Left hand */ \
        SLU1, SLU2, SLU3, SLU4, SLU5, \
        SLH1, SLH2, SLH3, SLH4, SLH5, \
  SLD0, SLD1, SLD2, SLD3, SLD4, SLD5, \
  /* Right hand */ \
  SRU1, SRU2, SRU3, SRU4, SRU5, \
  SRH1, SRH2, SRH3, SRH4, SRH5, SRH6, \
  SRD1, SRD2, SRD3, SRD4, SRD5, SRD6 \
) \
  /*-------------------------------------------------------------------------*/ \
  [L_DEFAULT] = MY_layout( \
    /* LEFT HALF */ \
    KC_ESC,  CMS_1,   CMS_2,   CMS_3,   CMS_4,   CMS_5, EN_GRV, \
    AG_UNDS, LU1,     LU2,     LU3,     LU4,     LU5,     CMB_CTC, \
    AG_DQUO, LH1,     LH2,     LH3,     LH4,     LH5,     CMB_CTV, \
    EN_QUOT, LD1,     LD2,     LD3,     LD4,     LD5, \
    EN_PIPE, XXXXXXX, XXXXXXX, CMB_LYG, CMB_LYV, \
    CMB_CTL, /* LEFT RED THUMB KEY */ \
    CMB_SFT, CMB_BSP, CMB_ENT, /* LEFT THUMB KEYS */ \
    \
    /* RIGHT HALF */ \
    AC_TILD,    CMS_6,   CMS_7,   CMS_8,   CMS_9,   CMS_0,   CT_Z, \
    CMB_CTS,    RU1,     RU2,     RU3,     RU4,     RU5,     CMS_MINS, \
    CMB_CMSP,   RH1,     RH2,     RH3,     RH4,     RH5,     AG_SCLN, \
                RD1,     RD2,     RD3,     RD4,     CMB_QUE, CMB_CLN, \
                         TT_RED,  KC_RCTL, TT_NUCL, TT_GAME, AG_SLSH, \
                      CMB_ALT, /* RIGHT RED THUMB KEY */ \
                      CMB_LAN, CMB_DOT, CMB_SPC /* RIGHT THUMB KEYS */ \
  ), \
  \
  /*-------------------------------------------------------------------------*/ \
  [L_SHIFT] = MY_layout( \
    /* LEFT HALF */ \
    _______, CMS_1,   CMS_2,   CMS_3,   CMS_4,   CMS_5,    _______, \
    _______, SLU1,    SLU2,    SLU3,    SLU4,    SLU5,    CMB_CAC, \
    _______, SLH1,    SLH2,    SLH3,    SLH4,    SLH5,    CMB_CAV, \
    _______, SLD1,    SLD2,    SLD3,    SLD4,    SLD5, \
    _______, _______, _______, _______, _______, \
    _______, /* LEFT RED THUMB KEY */ \
    _______, _______, _______, /* LEFT THUMB KEYS */ \
    \
    /* RIGHT HALF */ \
    _______, CMS_6,   CMS_7,   CMS_8,   CMS_9,   CMS_0,    CT_Y, \
    _______, SRU1,    SRU2,    SRU3,    SRU4,    SRU5,    _______, \
    _______, SRH1,    SRH2,    SRH3,    SRH4,    SRH5,    _______, \
             SRD1,    SRD2,    SRD3,    SRD4,    _______, _______, \
                      _______, _______, _______, _______, _______, \
                      _______, /* RIGHT RED THUMB KEY */ \
                      _______, _______, _______ /* RIGHT THUMB KEYS */ \
  ),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //---------------------------------------------------------------------------
  LANG_TWO_LAYERS(
    L_EN, L_EN_S,

    /* Left hand */
             CMS_EN_Q, CMS_EN_W,   CMS_EN_E,   CMS_EN_R,   CMS_EN_T,
             EN_A,     EN_S,       EN_D,       EN_F,       EN_G,
    XXXXXXX, EN_Z,     EN_X,       EN_C,       EN_V,       EN_B,

    /* Right hand */
    CMS_EN_Y,   CMS_EN_U,   CMS_EN_I,   CMS_EN_O,   CMS_EN_P,
    EN_H,       EN_J,       EN_K,       EN_L,       EN_SCLN,    _______,
    EN_N,       EN_M,       EN_COMM,    EN_DOT,     EN_SLSH,    _______,

    /* ---------------------------- Shift layer ---------------------------- */
    /* Left hand */
             CMS_S_EN_Q,   CMS_S_EN_W,  CMS_S_EN_E,  CMS_S_EN_R,  CMS_S_EN_T,
             EN_S_A,       EN_S_S,      EN_S_D,      EN_S_F,      EN_S_G,
    _______, EN_S_Z,       EN_S_X,      EN_S_C,      EN_S_V,      EN_S_B,

    /* Right hand */
    CMS_S_EN_Y, CMS_S_EN_U, CMS_S_EN_I, CMS_S_EN_O, CMS_S_EN_P,
    EN_S_H,     EN_S_J,     EN_S_K,     EN_S_L,     EN_COLN,  _______,
    EN_S_N,     EN_S_M,     EN_LT,      EN_GT,      EN_QUES,  _______
  )

  //---------------------------------------------------------------------------
  LANG_TWO_LAYERS(
    L_RU, L_RU_S,

    /* Left hand */
             CMS_RU_J,    CMS_RU_TS,   CMS_RU_U,    CMS_RU_K,   CMS_RU_JE,
             RU_F,        RU_Y,        RU_V,        CMS_A,      RU_P,
    XXXXXXX, RU_JA,       RU_CH,       RU_S,        RU_M,       RU_I,

    /* Right hand */
    CMS_RU_N,    CMS_RU_G,    CMS_RU_SH,   CMS_RU_SC,   CMS_RU_Z,
    CMS_R,       CMS_O,       RU_L,        RU_D,        RU_ZH,   XXXXXXX,
    CMS_T,       CMS_MZ,      RU_B,        RU_JU,       XXXXXXX, XXXXXXX,

    /* ---------------------------- Shift layer ---------------------------- */
    /* Left hand */
             CMS_S_RU_J,  CMS_S_RU_TS, CMS_S_RU_U,  CMS_S_RU_K, CMS_S_RU_JE,
             RU_S_F,      RU_S_Y,      RU_S_V,      CMS_S_A,    RU_S_P,
    _______, RU_S_JA,     RU_S_CH,     RU_S_S,      RU_S_M,     RU_S_I,

    /* Right hand */
    CMS_S_RU_N,  CMS_S_RU_G,   CMS_S_RU_SH, CMS_S_RU_SC, CMS_S_RU_Z,
    CMS_S_R,     CMS_S_O,      RU_S_L,      RU_S_D,      RU_S_ZH,   XXXXXXX,
    CMS_S_T,     CMS_S_MZ,     RU_S_B,      RU_S_JU,     XXXXXXX,   XXXXXXX
  )

  //---------------------------------------------------------------------------
  [L_RED] = MY_layout(
    // LEFT HALF
    TG_RED,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    CT_G,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CT_J,    _______,
    CS_M,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, CS_K,    _______,
    _______, CT_LEFT, CT_DOWN, CT_UP,   CT_RGHT, CT_F,
    _______, _______, _______, _______, TT_CYAN,
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    CT_PLUS, EN_MACR, CMB_LB2, CMB_RB2, EN_ARR2, EN_ARR1, CT_ENT,
    CT_MINS, KC_TAB,  CMB_LB1, CMB_RB1, CMB_LB4, CMB_RB4, SH_TAB,
             EN_FISH, CMB_LB3, CMB_RB3, EN_LTEQ, EN_GTEQ, EN_CLTG,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
    ),

  //---------------------------------------------------------------------------
  [L_GREN] = MY_layout(
    // LEFT HALF
    TG_GREN, _______, _______, _______, _______,  _______,  _______,
    KC_MUTE, KC_F5,   CS_T,    CT_T,    CT_W,     F6_CT_C,  _______,
    KC_VOLU, KC_MPRV, KC_MNXT, CT_PGUP, CT_PGDN,  KC_MPLY,  _______,
    KC_VOLD, CT_F5,   CS_P,    CT_1,    CT_2,     AL_PSCR,
    _______, _______, _______, _______, _______,  
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, RESET,
    _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),

  //---------------------------------------------------------------------------
  [L_VIOL] = MY_layout(
    // LEFT HALF
    TG_VIOL, _______, _______, _______, _______, _______, _______,
    AL_UP,   WN_8,    WN_7,    WN_6,    WN_5,    _______, _______,
    WN_Q,    WN_4,    WN_3,    WN_2,    WN_1,    _______, _______,
    KC_F2,   KC_LGUI, _______, WN_5,    WN_9,    _______,
    _______, _______, _______, _______, _______,
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, _______,
    _______, AC_SUB,  AG_7,    AG_8,    AG_9,    _______, _______,
    _______, AC_SUP,  AG_4,    AG_5,    AG_6,    AG_0,    _______,
             AC_CRCL, AG_1,    AG_2,    AG_3,    _______, _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),

  //---------------------------------------------------------------------------
  [L_GRAY] = MY_layout(
    // LEFT HALF
    TG_GRAY, _______, _______, _______, _______, _______,  _______,
    _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,  _______,
    KC_BTN1, RP_001,  RP_003,  RP_002,  RP_004,  KC_BTN2,  _______,
    _______, RP_005,  RP_007,  RP_006,  RP_008,  KC_BTN3,
    _______, _______, _______, _______, _______,  
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),

  //---------------------------------------------------------------------------
  [L_CYAN] = MY_layout(
    // LEFT HALF
    TG_CYAN, _______, _______, _______, _______, _______,  _______,
    XC_NIN,  XC_IN,   XC_SBST, XC_DEGR, XC_PLMN, XC_MU,    _______,
    XC_MUSC, XC_LEFT, XC_DOWN, XC_UP,   XC_RGHT, XC_LMBD,  _______,
    XC_ANGL, XC_IFAI, XC_EXST, XC_ALL,  XC_THEN, XC_PI,
    _______, _______, _______, _______, _______,  
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, _______,
    _______, XC_CRSS, CMB_LCR, CMB_RCR, XC_APRX, XC_EMPT, XC_TM,
    _______, XC_DONE, CMB_LTR, CMB_RTR, XC_DASH, XC_TIMS, XC_NEQ,
             XC_SPRK, XC_TMBU, XC_TMBD, XC_BULL, XC_INF, XC_COPY,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),
  
  //---------------------------------------------------------------------------
  [L_YELW] = MY_layout(
    // LEFT HALF
    TG_YELW, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD, RGB_TOG,
    RGB_PRT, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_RMOD,RGB_LYR,
    RGB__0,  RGB__1,  RGB__2,  RGB__25, RGB__28, RGB__36, RGB__27,
    RGB__7,  RGB__13, RGB__15, RGB__16, RGB__17, _______,
    _______, _______, AU_TOG,  MU_TOG,  MU_MOD,
    RGB_PRT, // LEFT RED THUMB KEY
    PIC_0,   PIC_1,   PIC_2, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, LED_1,   LED_2,   LED_3,   LED_4,   LED_5,   LED_6,
             _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),


  //---------------------------------------------------------------------------
  [L_GAME] = MY_layout(
    // LEFT HALF
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_7,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_8,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CS_M,
    KC_LGUI, // LEFT RED THUMB KEY
    KC_SPC,  KC_LALT, KC_ENT, // LEFT THUMB KEYS

    // RIGHT HALF
    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG_GAME,
    XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
    XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, XXXXXXX,
             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, // RIGHT RED THUMB KEY
                      XXXXXXX, XXXXXXX, XXXXXXX // RIGHT THUMB KEYS
    ),

  //---------------------------------------------------------------------------
  [L_NUCL] = MY_layout(
    // LEFT HALF
    TG_NUCL, KC_SLCK, KC_CAPS, KC_INS,  KC_PAUS, KC_PSCR, KC_APP,
    _______, _______, _______, _______, _______, _______, _______,
    _______, MU_LAN1, MU_LAN2, MU_LAN3, MU_LAN4, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______,
    KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, KC_RGUI,
    _______, // LEFT RED THUMB KEY
    KC_RCTL, KC_RSFT, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, RESET,
    _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
    _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PENT, _______,
             _______, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, _______,
                      KC_P0,   KC_PDOT, KC_PCMM, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),
};

const ComboWithKeycode combos[] PROGMEM = {
  // Left Index
  CHORD(CT_C,    /* <- */ CMB_CTC),
  CHORD(CT_V,    /* <- */ CMB_CTV),
  CHORD(CT_X,    /* <- */ CMB_CTC, CMB_CTV),

  // Right Index
  CHORD(CT_S,    /* <- */ CMB_CTS),
  CHORD(AG_CMSP, /* <- */ CMB_CMSP),
  CHORD(AG_COMM, /* <- */ CMB_CTS, CMB_CMSP),

  // Left Thumb
  //IMMEDIATE_CHORD(SFT_N, SFT_N,     /* <-! */ CMB_SFT),
  CHORD(SFT_N, /* <- */ CMB_SFT),
  CHORD(KC_BSPC, /* <- */ CMB_BSP),
  CHORD(KC_ENT,  /* <- */ CMB_ENT),
  IMMEDIATE_CHORD(CTRL_EN, CTRL_EN, /* <-! */ CMB_CTL),
  CHORD(CT_A,    /* <- */ CMB_SFT, CMB_CTL),
  CHORD(SFT_N_O, /* <- */ CMB_SFT, CMB_BSP),
  IMMEDIATE_CHORD(TT_GRAY, TT_UNDO, /* <-! */ CMB_SFT, CMB_BSP),
  CHORD(KC_DEL,  /* <- */ CMB_BSP, CMB_CTL),
  CHORD(CT_BSPC, /* <- */ CMB_BSP, CMB_ENT),
  CHORD(CTSH_EN, /* <- */ CMB_SFT, CMB_BSP, CMB_CTL),
  //CHORD(MU_SCR,  /* <- */ CMB_BSP, CMB_ENT, CMB_CTL),

  // Left Left Thumb
  IMMEDIATE_CHORD(TT_VIOL, TT_UNDO, /* <-! */ CMB_LYV),
  IMMEDIATE_CHORD(TT_GREN, TT_UNDO, /* <-! */ CMB_LYG),
  IMMEDIATE_CHORD(TT_RED,  TT_UNDO, /* <-! */ CMB_LYV, CMB_LYG),

  // Right Thumb
  CHORD(LA_CHNG, /* <- */ CMB_LAN),
  CHORD(AG_DOT,  /* <- */ CMB_DOT),
  CHORD(KC_SPC,  /* <- */ CMB_SPC),
  CHORD(ALT_EN,  /* <- */ CMB_ALT),
  CHORD(AG_SDOT, /* <- */ CMB_DOT, CMB_SPC),
  CHORD(LA_SYNC, /* <- */ CMB_LAN, CMB_DOT),
  CHORD(CTAL_EN, /* <- */ CMB_SPC, CMB_ALT),
  //CHORD(SHAL_EN, /* <- */ CMB_DOT, CMB_ALT),
  CHORD(KC_TAB, /* <- */ CMB_DOT, CMB_ALT),
  CHORD(WIN_EN,  /* <- */ CMB_SPC, CMB_DOT, CMB_ALT),
  //CHORD(MU_WNL,  /* <- */ CMB_LAN, CMB_DOT, CMB_ALT),

  // -------------------------------------------------------------------------
  // Shifted index keys

  // Left Index
  CHORD(CT_A_C,  /* <- */ CMB_CAC),
  CHORD(CT_A_V,  /* <- */ CMB_CAV),
  CHORD(CT_A_X,  /* <- */ CMB_CAC, CMB_CAV),

  // -------------------------------------------------------------------------
  // Russian combos on letters
  CHORD(RU_O,    /* <- */ CMS_O),
  CHORD(RU_SF,   /* <- */ CMS_MZ),
  CHORD(RU_A,    /* <- */ CMS_A),
  //CHORD(RU_K,   /* <- */ CMS_RU_K),
  CHORD(RU_R,   /* <- */ CMS_R),
  CHORD(RU_S_R,   /* <- */ CMS_S_R),
  CHORD(RU_T,   /* <- */ CMS_T),
  CHORD(RU_S_T,   /* <- */ CMS_S_T),
  CHORD(RU_S_A,  /* <- */ CMS_S_A),
  //CHORD(RU_S_K, /* <- */ CMS_S_RU_K),
  CHORD(RU_HD,   /* <- */ CMS_O, CMS_MZ),
  CHORD(RU_S_SF,  /* <- */ CMS_S_MZ),
  CHORD(RU_S_O, /* <- */ CMS_S_O),
  CHORD(RU_S_HD, /* <- */ CMS_S_O, CMS_S_MZ),
  CHORD(RU_JO,   /* <- */ CMS_A, CMS_RU_K),
  CHORD(RU_S_JO,   /* <- */ CMS_S_A, CMS_S_RU_K),
  CHORD(RU_ZH,    /* <- */ CMS_ZH),
  CHORD(RU_S_ZH,    /* <- */ CMS_S_ZH),
  CHORD(AG_SCLN,    /* <- */ CMS_SEMICOLN),
  CHORD(AG_COLN,    /* <- */ CMS_S_COLN),
  CHORD(RU_E,   /* <- */ CMS_R, CMS_T),
  CHORD(RU_S_E,   /* <- */ CMS_S_R, CMS_S_T),
  //CHORD(RU_N,   /* <- */ CMS_RU_N),
  //CHORD(RU_S_N,  /* <- */ CMS_S_RU_N),
  CHORD(AG_MINS,   /* <- */ CMS_MINS),
  CHORD(RU_H,   /* <- */ CMS_RU_N, CMS_R),
  CHORD(RU_S_H,   /* <- */ CMS_S_RU_N, CMS_S_R),

  // -------------------------------------------------------------------------
  // Number row
  CHORD(AG_1,    /* <- */ CMS_1),
  CHORD(AG_2,    /* <- */ CMS_2),
  CHORD(AG_3,    /* <- */ CMS_3),
  CHORD(AG_4,    /* <- */ CMS_4),
  CHORD(AG_5,    /* <- */ CMS_5),
  CHORD(AG_6,    /* <- */ CMS_6),
  CHORD(AG_7,    /* <- */ CMS_7),
  CHORD(AG_8,    /* <- */ CMS_8),
  CHORD(AG_9,    /* <- */ CMS_9),
  CHORD(AG_0,    /* <- */ CMS_0),

  // Left english upper row
  CHORD(EN_Q,    /* <- */ CMS_EN_Q),
  CHORD(EN_W,    /* <- */ CMS_EN_W),
  CHORD(EN_E,    /* <- */ CMS_EN_E),
  CHORD(EN_R,    /* <- */ CMS_EN_R),
  CHORD(EN_T,    /* <- */ CMS_EN_T),

  // Left english upper row with shift
  CHORD(EN_S_Q,    /* <- */ CMS_S_EN_Q),
  CHORD(EN_S_W,    /* <- */ CMS_S_EN_W),
  CHORD(EN_S_E,    /* <- */ CMS_S_EN_E),
  CHORD(EN_S_R,    /* <- */ CMS_S_EN_R),
  CHORD(EN_S_T,    /* <- */ CMS_S_EN_T),

  // Right english upper row
  CHORD(EN_Y,    /* <- */ CMS_EN_Y),
  CHORD(EN_U,    /* <- */ CMS_EN_U),
  CHORD(EN_I,    /* <- */ CMS_EN_I),
  CHORD(EN_O,    /* <- */ CMS_EN_O),
  CHORD(EN_P,    /* <- */ CMS_EN_P),

  // Right english upper row with shift
  CHORD(EN_S_Y,    /* <- */ CMS_S_EN_Y),
  CHORD(EN_S_U,    /* <- */ CMS_S_EN_U),
  CHORD(EN_S_I,    /* <- */ CMS_S_EN_I),
  CHORD(EN_S_O,    /* <- */ CMS_S_EN_O),
  CHORD(EN_S_P,    /* <- */ CMS_S_EN_P),

  // Left russian upper row
  CHORD(RU_J,    /* <- */ CMS_RU_J),
  CHORD(RU_TS,    /* <- */ CMS_RU_TS),
  CHORD(RU_U,    /* <- */ CMS_RU_U),
  CHORD(RU_K,    /* <- */ CMS_RU_K),
  CHORD(RU_JE,    /* <- */ CMS_RU_JE),

  // Left russian upper row with shift
  CHORD(RU_S_J,    /* <- */ CMS_S_RU_J),
  CHORD(RU_S_TS,    /* <- */ CMS_S_RU_TS),
  CHORD(RU_S_U,    /* <- */ CMS_S_RU_U),
  CHORD(RU_S_K,    /* <- */ CMS_S_RU_K),
  CHORD(RU_S_JE,    /* <- */ CMS_S_RU_JE),

  // Right russian upper row
  CHORD(RU_N,    /* <- */ CMS_RU_N),
  CHORD(RU_G,    /* <- */ CMS_RU_G),
  CHORD(RU_SH,    /* <- */ CMS_RU_SH),
  CHORD(RU_SC,    /* <- */ CMS_RU_SC),
  CHORD(RU_Z,    /* <- */ CMS_RU_Z),

  // Right russian upper row with shift
  CHORD(RU_S_N,    /* <- */ CMS_S_RU_N),
  CHORD(RU_S_G,    /* <- */ CMS_S_RU_G),
  CHORD(RU_S_SH,    /* <- */ CMS_S_RU_SH),
  CHORD(RU_S_SC,    /* <- */ CMS_S_RU_SC),
  CHORD(RU_S_Z,    /* <- */ CMS_S_RU_Z),

  // Combos for upper punctuation signs for English layer
  CHORD(AG_EXCL, /* <- */ CMS_1, CMS_EN_Q),
  CHORD(EN_AT, /* <- */ CMS_2, CMS_EN_W),
  CHORD(EN_HASH, /* <- */ CMS_3, CMS_EN_E),
  CHORD(EN_DLR, /* <- */ CMS_4, CMS_EN_R),
  CHORD(AG_PERC, /* <- */ CMS_5, CMS_EN_T),

  CHORD(EN_CIRC, /* <- */ CMS_6, CMS_EN_Y),
  CHORD(EN_AMPR, /* <- */ CMS_7, CMS_EN_U),
  CHORD(EN_ASTR, /* <- */ CMS_8, CMS_EN_I),
  CHORD(AG_EQL, /* <- */ CMS_9, CMS_EN_O),
  CHORD(AG_PLUS, /* <- */ CMS_0, CMS_EN_P),

  // Combos for upper punctuation signs for English layer with Shift
  CHORD(AG_EXCL, /* <- */ CMS_1, CMS_S_EN_Q),
  CHORD(EN_AT, /* <- */ CMS_2, CMS_S_EN_W),
  CHORD(EN_HASH, /* <- */ CMS_3, CMS_S_EN_E),
  CHORD(EN_DLR, /* <- */ CMS_4, CMS_S_EN_R),
  CHORD(AG_PERC, /* <- */ CMS_5, CMS_S_EN_T),

  CHORD(EN_CIRC, /* <- */ CMS_6, CMS_S_EN_Y),
  CHORD(EN_AMPR, /* <- */ CMS_7, CMS_S_EN_U),
  CHORD(EN_ASTR, /* <- */ CMS_8, CMS_S_EN_I),
  CHORD(AG_EQL, /* <- */ CMS_9, CMS_S_EN_O),
  CHORD(AG_PLUS, /* <- */ CMS_0, CMS_S_EN_P),

  // Combos for upper punctuation signs for Russian layer
  CHORD(AG_EXCL, /* <- */ CMS_1, CMS_RU_J),
  CHORD(EN_AT, /* <- */ CMS_2, CMS_RU_TS),
  CHORD(EN_HASH, /* <- */ CMS_3, CMS_RU_U),
  CHORD(EN_DLR, /* <- */ CMS_4, CMS_RU_K),
  CHORD(AG_PERC, /* <- */ CMS_5, CMS_RU_JE),

  CHORD(EN_CIRC, /* <- */ CMS_6, CMS_RU_N),
  CHORD(EN_AMPR, /* <- */ CMS_7, CMS_RU_G),
  CHORD(EN_ASTR, /* <- */ CMS_8, CMS_RU_SH),
  CHORD(AG_EQL, /* <- */ CMS_9, CMS_RU_SC),
  CHORD(AG_PLUS, /* <- */ CMS_0, CMS_RU_Z),

  // Combos for upper punctuation signs for Russian layer with Shift
  CHORD(AG_EXCL, /* <- */ CMS_1, CMS_S_RU_J),
  CHORD(EN_AT, /* <- */ CMS_2, CMS_S_RU_TS),
  CHORD(EN_HASH, /* <- */ CMS_3, CMS_S_RU_U),
  CHORD(EN_DLR, /* <- */ CMS_4, CMS_S_RU_K),
  CHORD(AG_PERC, /* <- */ CMS_5, CMS_S_RU_JE),

  CHORD(EN_CIRC, /* <- */ CMS_6, CMS_S_RU_N),
  CHORD(EN_AMPR, /* <- */ CMS_7, CMS_S_RU_G),
  CHORD(EN_ASTR, /* <- */ CMS_8, CMS_S_RU_SH),
  CHORD(AG_EQL, /* <- */ CMS_9, CMS_S_RU_SC),
  CHORD(AG_PLUS, /* <- */ CMS_0, CMS_S_RU_Z),

  // Left hand
  CHORD(AG_PLUS, /* <- */ CMB_PLS),
  CHORD(AG_SCLN, /* <- */ CMB_SCL),
  CHORD(EN_GRV,  /* <- */ CMB_GRV),
  CHORD(AG_EXCL, /* <- */ CMB_EXL),
  CHORD(AG_ASTR, /* <- */ CMB_ASR),
  CHORD(EN_TILD, /* <- */ CMB_PLS, CMB_EXL),
  CHORD(RU_NUME, /* <- */ CMB_PLS, CMB_ASR),
  CHORD(EN_QUOT, /* <- */ CMB_GRV, CMB_EXL),
  CHORD(AG_DQUO, /* <- */ CMB_SCL, CMB_GRV),
  CHORD(AG_PERC, /* <- */ CMB_SCL, CMB_EXL),
  CHORD(EN2QUOT, /* <- */ CMB_SCL, CMB_ASR),
  CHORD(AG2DQUO, /* <- */ CMB_SCL, CMB_GRV, CMB_EXL),

  // Right hand
  CHORD(AG_SLSH, /* <- */ CMB_SLS),
  CHORD(AG_QUES, /* <- */ CMB_QUE),
  CHORD(AG_CMSP, /* <- */ CMB_CMM),
  CHORD(AG_COLN, /* <- */ CMB_CLN),
  CHORD(AG_EQL,  /* <- */ CMB_EQL),
  CHORD(EN_DLR,  /* <- */ CMB_SLS, CMB_CLN),
  CHORD(EN_HASH, /* <- */ CMB_SLS, CMB_EQL),
  CHORD(EN_PIPE, /* <- */ CMB_CMM, CMB_CLN),
  CHORD(EN_AMPR, /* <- */ CMB_QUE, CMB_CMM),
  CHORD(AG_BSLS, /* <- */ CMB_QUE, CMB_CLN),
  CHORD(EN2PIPE, /* <- */ CMB_QUE, CMB_EQL),
  CHORD(EN2AMPR, /* <- */ CMB_QUE, CMB_CMM, CMB_CLN),

  // -------------------------------------------------------------------------
  // Brackets on red layer
  CHORD(AG_LPRN, /* <- */ CMB_LB1),
  CHORD(AG_RPRN, /* <- */ CMB_RB1),
  CHORD(EN_LBRC, /* <- */ CMB_LB2),
  CHORD(EN_RBRC, /* <- */ CMB_RB2),
  CHORD(EN_LCBR, /* <- */ CMB_LB3),
  CHORD(EN_RCBR, /* <- */ CMB_RB3),
  CHORD(EN_LT,   /* <- */ CMB_LB4),
  CHORD(EN_GT,   /* <- */ CMB_RB4),
  CHORD(AG_2B1,  /* <- */ CMB_LB1, CMB_RB1),
  CHORD(EN_2B2,  /* <- */ CMB_LB2, CMB_RB2),
  CHORD(EN_2B3,  /* <- */ CMB_LB3, CMB_RB3),
  CHORD(EN_2B4,  /* <- */ CMB_LB4, CMB_RB4),

  // -------------------------------------------------------------------------
  // Brackets on XCompose layer

  CHORD(XC_LTRE, /* <- */ CMB_LTR),
  CHORD(XC_RTRE, /* <- */ CMB_RTR),
  CHORD(XC_BTRE, /* <- */ CMB_LTR, CMB_RTR),

  CHORD(XC_LCRN, /* <- */ CMB_LCR),
  CHORD(XC_RCRN, /* <- */ CMB_RCR),
  CHORD(XC_BCRN, /* <- */ CMB_LCR, CMB_RCR),
};
const uint8_t combos_size = sizeof(combos)/sizeof(ComboWithKeycode);

const uint16_t tt_keys[][3] = {
  { TT_CTJ,  CT_J,    CT_BSLS }, // Program killing, if pressed 3 times then throws Ctrl+\, and it kills the program immediately
  { TT_RED,  MO_RED,  TG_RED },
  { TT_GREN, MO_GREN, TG_GREN },
  { TT_VIOL, MO_VIOL, TG_VIOL },
  { TT_GRAY, MO_GRAY, TG_GRAY },
  { TT_CYAN, MO_CYAN, TG_CYAN },
  { TT_YELW, MO_YELW, TG_YELW },
  { TT_GAME, MO_GAME, TG_GAME },
  { TT_NUCL, MO_NUCL, TG_NUCL },
};
const uint8_t tt_size = sizeof(tt_keys)/(sizeof(uint16_t) * 3);

const uint16_t repeat_keys[][2] = {
  { RP_000, AR_L5 },
  { RP_001, MS_LF_1 },
  { RP_002, MS_UP_1 },
  { RP_003, MS_DN_1 },
  { RP_004, MS_RG_1 },
  { RP_005, MS_LF10 },
  { RP_006, MS_UP10 },
  { RP_007, MS_DN10 },
  { RP_008, MS_RG10 },
};
const uint8_t repeat_size = sizeof(repeat_keys)/(sizeof(uint16_t) * 2);

enum ledmap_colors {
  COLOR_BLACK = COLOR_SAFE_RANGE,
  COLOR_ANYFN,
  COLOR_PINKY,
  COLOR_ANNUL,
  COLOR_MIDDL,
  COLOR_INDEX,
  COLOR_THUMB,
};

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL] = {
    [0] = {
      COLOR_ANYFN, COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_ANYFN,
      COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_ANYFN,
      COLOR_ANNUL, COLOR_ANNUL, COLOR_ANNUL, COLOR_ANNUL, COLOR_ANYFN,
      COLOR_MIDDL, COLOR_MIDDL, COLOR_MIDDL, COLOR_MIDDL, COLOR_THUMB,
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_THUMB,
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, 
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 

      COLOR_ANYFN, COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_ANYFN,
      COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_PINKY, COLOR_ANYFN,
      COLOR_ANNUL, COLOR_ANNUL, COLOR_ANNUL, COLOR_ANNUL, COLOR_ANYFN,
      COLOR_MIDDL, COLOR_MIDDL, COLOR_MIDDL, COLOR_MIDDL, COLOR_THUMB,
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_THUMB,
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, 
      COLOR_INDEX, COLOR_INDEX, COLOR_INDEX, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER
    },

    [1] = {
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 

      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER
    },

    [2] = {
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, 
      ___________, ___________, ___________, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER, 

      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, ___________,
      ___________, ___________, ___________, ___________, 
      ___________, ___________, ___________, 
      COLOR_LAYER,
      COLOR_LAYER, COLOR_LAYER, COLOR_LAYER
    },
};
const uint8_t ledmap_size = sizeof(ledmap)/(sizeof(uint8_t) * DRIVER_LED_TOTAL);

const uint8_t PROGMEM colormap[][3] = {
  [COLOR_BLACK] = { 0, 0, 0 },
  [COLOR_ANYFN] = { 0, 0, 255 },
  [COLOR_PINKY] = { 31, 255, 255 },
  [COLOR_ANNUL] = { 164, 255, 255 },  
  [COLOR_MIDDL] = { 76, 255, 255 },
  [COLOR_INDEX] = { 224, 255, 255 },
  [COLOR_THUMB] = { 8, 255, 255 },
};
const uint8_t colormap_size = sizeof(colormap)/(sizeof(uint8_t) * 3);

const uint8_t PROGMEM layermap[][3] = {
  [L_EN] = { 84, 33, 255 },
  [L_EN_S] = { 84, 33, 192 },

  [L_RU] = { 164, 255, 255 },
  [L_RU_S] = { 164, 255, 192 },

  [L_RED] = { 0, 255, 210 },
  [L_GREN] = { 76, 255, 255 },
  [L_VIOL] = { 188, 255, 255 },
  [L_GRAY] = { 0, 0, 128 },
  [L_CYAN] = { 128, 255, 255 },

  [L_YELW] = { 35, 255, 255 },
  [L_GAME] = { 228, 255, 255 },

  [L_NUCL] = { 8, 255, 255 },
};
const uint8_t layermap_size = sizeof(layermap)/(sizeof(uint8_t) * 3);

bool initted_for_layer_state = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  if (initted_for_layer_state) {
    // Выключаем все леды, потому что они только просвечивают своим некрасивым цветом через прозрачные кейкапы, а для чего их использовать можно я не придумал
    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

    uint8_t layer = get_highest_layer(state);

    // Set up the current keyboard color the same as the current layer. It creates a beautiful effect for highlighting that use the current color
    rgb_matrix_sethsv_noeeprom(
      pgm_read_byte(&layermap[layer][0]),
      pgm_read_byte(&layermap[layer][1]),
      pgm_read_byte(&layermap[layer][2])
    );
  }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  initted_for_layer_state = true;

  if (!process_my_music_keys(keycode, record)) {
    return false;
  }

  if (!combo_process_record(keycode, record)) {
    return false;
  }

  if (!tt_process_record(keycode, record)) {
    return false;
  }

  if (!rp_process_record(keycode, record)) {
    return false;
  }

  if (!process_my_lang_keys(keycode, record)) {
    return false;
  }

  if (!process_my_xcompose(keycode, record)) {
    return false;
  }

  if (!lang_shift_process_record(keycode, record)) {
    return false;
  }

  if (!color_process_record(keycode, record)) {
    return false;
  }

  if (!process_my_hotkeys(keycode, record)) {
    return false;
  }

  if (!process_moonlander_leds(keycode, record)) {
    return false;
  }

  if (!process_mouse_pixel_move(keycode, record)) {
    return false;
  }

  return true;
}

float error_song1[][2] = SONG(MUSIC_OFF_SOUND);
void combo_max_count_error(void) {
  PLAY_SONG(error_song1);
  dprintf("COMBO ERROR: MAX COMBOS COUNT HAS REACHED\n");
}

float error_song2[][2] = SONG(VOICE_CHANGE_SOUND);
void combo_max_size_error(void) {
  PLAY_SONG(error_song2); 
  dprintf("COMBO ERROR: MAX COMBO SIZE HAS REACHED\n");
}

void repeated_key_error(void) {
  PLAY_SONG(error_song2); 
  dprintf("REPEATED KEY ERROR\n");
}

void language_server_timer(void)
{
  if (timer_read() - lang_timer >= LANG_SHIFT_LANG_WAIT_TIME)
  {
    temporarily_disable_server = false;
    dprintf("Enabled server\n");
	}
}

void user_timer(void) {
  combo_user_timer();
  lang_shift_user_timer();
  rp_timer();
  language_server_timer();
}

void matrix_scan_user(void) {
  user_timer();
}

// Need for color.h
void rgb_matrix_indicators_user(void) {
  color_rgb_matrix_indicators();
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  //debug_enable=true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    dprintf("Server state - %s\n", temporarily_disable_server ? "true" : "false");

    if (!temporarily_disable_server)
    {
        dprintf("Inside Server state");
        int current_lang = data[0];
        lang_should_be = current_lang;
        lang_current = current_lang;

        if (current_lang == 1) {
            layer_on(2);
        } else {
            layer_off(2);
        }
    }
}
