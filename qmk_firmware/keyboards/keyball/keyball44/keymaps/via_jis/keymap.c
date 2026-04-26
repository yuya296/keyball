/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"
#include "keymap_japanese.h"
#include "process_key_override.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_QUOT  , KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  , KC_SCLN  , KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , KC_2     ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// ---- Auto Mouse Layer を起動時から ON にする ----
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif

// ---- Remap (VIA) で割り当てたキーが JIS Windows 環境でラベル通りに出るようにする ----
// Remap UI は US 配列前提で表示・送信する。Windows を JIS のままで使いたいので、
// ファーム側で全記号キーを「JIS 環境で同じ記号を生む keymap_japanese.h のキー」に置換する。
// JP_* マクロは内部で必要に応じて Shift を含むため、suppressed_mods (= trigger_mods) で
// 元の Shift を消した上で送り直す ko_make_basic の挙動でちょうど整合する。

// shift ありの override が先に評価されるよう、shift なしの override は
// physical Shift 同時押し時にはマッチしないようにする。
#define KO_UNSHIFTED(trigger_key, replacement_key) \
    ko_make_with_layers_and_negmods(0, trigger_key, replacement_key, ~0, MOD_MASK_SHIFT)

// shift なし (記号そのものを送りたいキー)
const key_override_t ko_grv  = KO_UNSHIFTED(KC_GRV,  JP_GRV);
const key_override_t ko_mins = KO_UNSHIFTED(KC_MINS, JP_MINS);
const key_override_t ko_eql  = KO_UNSHIFTED(KC_EQL,  JP_EQL);
const key_override_t ko_lbrc = KO_UNSHIFTED(KC_LBRC, JP_LBRC);
const key_override_t ko_rbrc = KO_UNSHIFTED(KC_RBRC, JP_RBRC);
const key_override_t ko_bsls = KO_UNSHIFTED(KC_BSLS, JP_BSLS);
const key_override_t ko_scln = KO_UNSHIFTED(KC_SCLN, JP_SCLN);
const key_override_t ko_quot = KO_UNSHIFTED(KC_QUOT, JP_QUOT);

// shift あり (US で Shift+X として表現される記号)
const key_override_t ko_s_grv  = ko_make_basic(MOD_MASK_SHIFT, KC_GRV,  JP_TILD);
const key_override_t ko_s_2    = ko_make_basic(MOD_MASK_SHIFT, KC_2,    JP_AT);
const key_override_t ko_s_6    = ko_make_basic(MOD_MASK_SHIFT, KC_6,    JP_CIRC);
const key_override_t ko_s_7    = ko_make_basic(MOD_MASK_SHIFT, KC_7,    JP_AMPR);
const key_override_t ko_s_8    = ko_make_basic(MOD_MASK_SHIFT, KC_8,    JP_ASTR);
const key_override_t ko_s_9    = ko_make_basic(MOD_MASK_SHIFT, KC_9,    JP_LPRN);
const key_override_t ko_s_0    = ko_make_basic(MOD_MASK_SHIFT, KC_0,    JP_RPRN);
const key_override_t ko_s_mins = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);
const key_override_t ko_s_eql  = ko_make_basic(MOD_MASK_SHIFT, KC_EQL,  JP_PLUS);
const key_override_t ko_s_lbrc = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR);
const key_override_t ko_s_rbrc = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR);
const key_override_t ko_s_bsls = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE);
const key_override_t ko_s_scln = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN);
const key_override_t ko_s_quot = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO);

const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_grv, &ko_mins, &ko_eql, &ko_lbrc, &ko_rbrc, &ko_bsls, &ko_scln, &ko_quot,
    &ko_s_grv, &ko_s_2, &ko_s_6, &ko_s_7, &ko_s_8, &ko_s_9, &ko_s_0,
    &ko_s_mins, &ko_s_eql, &ko_s_lbrc, &ko_s_rbrc, &ko_s_bsls, &ko_s_scln, &ko_s_quot,
    NULL
};
