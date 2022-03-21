/* Copyright 2020 Victor Lucachi
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY,
  _APEX,
  _RAISE,
  _LOWER,
  _ADJUST
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_planck_mit(KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, OSM(MOD_LCTL), OSM(MOD_LGUI), KC_F24, OSM(MOD_LALT), OSL(_LOWER), KC_SPC, OSL(_RAISE), KC_LEFT, KC_UP, KC_DOWN, KC_RGHT),
	[_APEX] = LAYOUT_planck_mit(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_1, KC_3, KC_LALT, KC_4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[_RAISE] = LAYOUT_planck_mit(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_F11, KC_F12, KC_NO, TG(_APEX), KC_NO, KC_NO, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[_LOWER] = LAYOUT_planck_mit(KC_TRNS, KC_NO, KC_PLUS, KC_AT, KC_HASH, KC_DLR, KC_CIRC, KC_RPRN, KC_RBRC, KC_RCBR, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_EQL, KC_MINS, KC_ASTR, KC_BSLS, KC_PERC, KC_LPRN, KC_LBRC, KC_LCBR, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_AMPR, KC_PIPE, KC_EXLM, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END),
	[_ADJUST] = LAYOUT_planck_mit(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EEP_RST, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_MPLY, KC_TRNS, KC_MPRV, KC_VOLU, KC_VOLD, KC_MNXT)
};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(keycode == KC_F24 && record->event.pressed){
        uint8_t mods = 0;
        if ((mods = get_oneshot_mods()) && !has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
            unregister_mods(mods);
        }
        if ((mods = get_oneshot_locked_mods())) {
            clear_oneshot_locked_mods();
            unregister_mods(mods);
        }
        if (is_oneshot_layer_active()) {
            layer_clear();
        }
        return false;
    }
    if ((get_oneshot_locked_mods() & MOD_MASK_SHIFT)) {
        if (((KC_A <= keycode) && (keycode <= KC_Z))) {
            if (record->event.pressed) {
                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);

                register_code(keycode);

                add_mods(MOD_MASK_SHIFT);
                add_oneshot_mods(MOD_MASK_SHIFT);
            } else {
                unregister_code(keycode);
            }

            return false;
        }
    }
    return true;
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
    if ((mods & MOD_MASK_SHIFT)) {
        if (!host_keyboard_led_state().caps_lock) {
            tap_code(KC_CAPS);
        }
    } else if (!(mods & MOD_MASK_SHIFT)) {
        if (host_keyboard_led_state().caps_lock) {
            tap_code(KC_CAPS);

            clear_oneshot_locked_mods();
            del_oneshot_mods(MOD_MASK_SHIFT);
            unregister_mods(MOD_MASK_SHIFT);
        }
    }
}
