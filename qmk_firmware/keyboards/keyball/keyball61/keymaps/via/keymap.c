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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_DEL   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_INT3  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,              KC_NUHS, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    _______  , KC_LCTL  , KC_LALT  , KC_LGUI,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),    KC_BSPC,LT(2,KC_ENT),LT(1,KC_LNG2),KC_RGUI, _______ , KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    S(KC_ESC), S(KC_1)  , KC_LBRC  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  KC_EQL   , S(KC_6)  ,S(KC_QUOT), S(KC_8)  , S(KC_9)  ,S(KC_INT1),
    S(KC_DEL), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_INT3),
    S(KC_TAB), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_QUOT  , S(KC_2)  ,
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),           S(KC_NUHS), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH),S(KC_RSFT),
    _______  ,S(KC_LCTL),S(KC_LALT),S(KC_LGUI), _______  , _______  , _______  ,            _______  , _______  , _______  ,S(KC_RGUI), _______  , S(KC_RALT), _______
  ),

  [2] = LAYOUT_universal(
    SSNP_FRE , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
    SSNP_HOR , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
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

// ---- JIS互換変換のON/OFFトグル ----
// Remap UI 上では `Kb 28` として割り当て可能。状態は eeconfig_user に永続化。
enum custom_keycodes {
    JIS_TGL = QK_KB_28,
};

typedef union {
    uint32_t raw;
    struct {
        bool    jis_compat_enabled : 1;
        uint8_t magic              : 7;  // 初期化済み判定用 (=0x55 を入れる)
    };
} user_config_t;

#define USER_CONFIG_MAGIC 0x55

static user_config_t user_config;

// 押下中の物理キー位置ごとに送り出した replacement を覚えておく。
// release が press と別経路 (JIS_TGL でON/OFFが切り替わる等) を通った場合でも
// 確実に同じ replacement を unregister してキー張り付きを防ぐため。
static uint16_t active_jis_replacement[MATRIX_ROWS][MATRIX_COLS];

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    // magic未一致 = 初回起動 or 別ファームの残骸。デフォルト(ON)で初期化＆保存。
    if (user_config.magic != USER_CONFIG_MAGIC) {
        user_config.raw = 0;
        user_config.magic = USER_CONFIG_MAGIC;
        user_config.jis_compat_enabled = true;
        eeconfig_update_user(user_config.raw);
    }
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.magic = USER_CONFIG_MAGIC;
    user_config.jis_compat_enabled = true;
    eeconfig_update_user(user_config.raw);
}

// ---- Remap (VIA) で割り当てたキーが JIS Windows 環境でラベル通りに出るようにする ----
// Remap UI は US 配列前提でキーラベルを表示・送信する。Windows を JIS のままで使いたいので、
// ファーム側で全記号キーを「JIS 環境で同じ記号を生む keymap_japanese.h のキー」に置換する。
//
// key_override では「物理Shift+物理キー」しか捕まえられず、Remap で `@` 等を選んで保存された
// `S(KC_2)` 形式の合成 keycode (QK_MODS|KC_x) は trigger 完全一致しないため発火しない。
// そのため process_record_user で「素の KC_x」と「合成された S(KC_x)」の両方を捕まえてテーブル変換する。

static void send_jis_replacement(uint16_t replacement, bool pressed) {
    if (pressed) {
        register_code16(replacement);
    } else {
        unregister_code16(replacement);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // JIS互換のON/OFFトグル
    if (keycode == JIS_TGL) {
        if (record->event.pressed) {
            user_config.jis_compat_enabled = !user_config.jis_compat_enabled;
            eeconfig_update_user(user_config.raw);
        }
        return false;
    }

    uint16_t *active_replacement = &active_jis_replacement[record->event.key.row][record->event.key.col];

    // release は press 時に採用した replacement で必ず閉じる。
    // (途中で OFF に切り替わっても張り付かないように)
    if (!record->event.pressed && *active_replacement != KC_NO) {
        const uint8_t real_mods  = get_mods();
        const uint8_t shift_mods = real_mods & MOD_MASK_SHIFT;
        if (shift_mods) {
            del_mods(shift_mods);
            send_keyboard_report();
        }
        send_jis_replacement(*active_replacement, false);
        *active_replacement = KC_NO;
        if (shift_mods) {
            set_mods(real_mods);
            send_keyboard_report();
        }
        return false;
    }

    // OFF時は素通し
    if (!user_config.jis_compat_enabled) return true;

    const uint8_t real_mods   = get_mods();
    const uint8_t shift_mods  = real_mods & MOD_MASK_SHIFT;

    // QK_MODS (S(KC_x) のような Shift合成キー) を basic に剥がす。
    // それ以外の高位 keycode (LT, MT, custom) は素通し。
    uint16_t basic = keycode;
    bool     synthetic_shift = false;
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        const uint8_t mod_bits = QK_MODS_GET_MODS(keycode);
        // 5bit 圧縮形式: 下位2bitsがmod種別、bit4がL/R。Shift だけ拾えれば充分。
        if ((mod_bits & 0x0F) == MOD_LSFT) {
            synthetic_shift = true;
            basic = QK_MODS_GET_BASIC_KEYCODE(keycode);
        } else {
            return true; // Shift 以外の修飾付き合成キーは素通し
        }
    } else if (keycode > 0xFF) {
        return true; // LT/MT/独自キーコードは素通し
    }

    const bool is_shifted = (shift_mods != 0) || synthetic_shift;
    uint16_t   replacement = 0;

    if (is_shifted) {
        switch (basic) {
            case KC_2:    replacement = JP_AT;   break;
            case KC_6:    replacement = JP_CIRC; break;
            case KC_7:    replacement = JP_AMPR; break;
            case KC_8:    replacement = JP_ASTR; break;
            case KC_9:    replacement = JP_LPRN; break;
            case KC_0:    replacement = JP_RPRN; break;
            case KC_MINS: replacement = JP_UNDS; break;
            case KC_EQL:  replacement = JP_PLUS; break;
            case KC_LBRC: replacement = JP_LCBR; break;
            case KC_RBRC: replacement = JP_RCBR; break;
            case KC_BSLS: replacement = JP_PIPE; break;
            case KC_SCLN: replacement = JP_COLN; break;
            case KC_QUOT: replacement = JP_DQUO; break;
            case KC_GRV:  replacement = JP_TILD; break;
            default:      return true;
        }
    } else {
        switch (basic) {
            case KC_GRV:  replacement = JP_GRV;  break;
            case KC_MINS: replacement = JP_MINS; break;
            case KC_EQL:  replacement = JP_EQL;  break;
            case KC_LBRC: replacement = JP_LBRC; break;
            case KC_RBRC: replacement = JP_RBRC; break;
            case KC_BSLS: replacement = JP_BSLS; break;
            case KC_QUOT: replacement = JP_QUOT; break;
            // KC_SCLN は素の `;` で JIS でも一致するため変換不要
            default:      return true;
        }
    }

    // press のみ: 物理 Shift を一時的に取り除いて replacement を register、
    // 同じ物理キー位置に紐付けて記憶しておく (release で同じ値を unregister するため)。
    if (record->event.pressed) {
        if (shift_mods) {
            del_mods(shift_mods);
            send_keyboard_report();
        }
        send_jis_replacement(replacement, true);
        *active_replacement = replacement;
        if (shift_mods) {
            set_mods(real_mods);
            send_keyboard_report();
        }
    }
    return false;
}
