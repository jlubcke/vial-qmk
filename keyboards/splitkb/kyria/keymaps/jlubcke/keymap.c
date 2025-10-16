#include QMK_KEYBOARD_H
#include <stdio.h>
#include <math.h>


void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

enum layers {
    _QWERTY = 0,
    _LOWER,
    _UPPER,
    _ADJUST,
};

#define QWERTY   DF(_QWERTY)
#define LWR_ENT  LT(_LOWER, KC_ENT)
#define UPR_SPC  LT(_UPPER, KC_SPC)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)

// Home row modifiers
#define HRM_A    LSFT_T(KC_A)
#define HRM_S    LCTL_T(KC_S)
#define HRM_D    LALT_T(KC_D)
#define HRM_F    LGUI_T(KC_F)
#define HRM_J    RGUI_T(KC_J)
#define HRM_K    RALT_T(KC_K)
#define HRM_L    RCTL_T(KC_L)
#define HRM_SCLN RSFT_T(KC_SCLN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Modifiers
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Ctrl | Shift| Ctrl | Alt  | Cmd  |      |                              |      | Cmd  | Alt  | Ctrl |Shift |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Upper|  | Lower|      |      |      |      |      |      |Shift |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |Adjust| Alt  | Cmd  | Lower|  | Upper| Cmd  |AltGr |      |      |
 *                      |      |---------------------------'  `---------------------------|      |
 *                      `------'                                                          `------'
 */

/*
 * Upper layer
 *
 * ,------------------------------------------.                              ,------------------------------------------.
 * |  Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |                              | PgUp | Home |  Up  |  End |  Ins | Space |
 * |-------+------+------+------+------+------|                              |------+------+------+------+------+-------|
 * |  Esc  |  F6  |  F7  |  F8  |  F9  |  F10 |                              | PgDn | Left | Down | Right|   [  |   [   |
 * |-------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
 * |  ` ~  |  F11 |  F12 |      |      |      |      | #### |  |      |      | Bksp |   (  |   )  |   {  |   }  | Shift |
 * `---------------------+------+------+------+------+------|  |------+------+------+------+------+---------------------'
 *                       | Tab  |      |      |      |      |  | #### |      |      |      | PgUp |
 *                       | ShTab|----------------------------------------------------------| PgDn |
 *                       `------'                                                          `------'
 */
    [_UPPER] = LAYOUT(
     KC_TAB,  KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5 ,                                    KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,  KC_SPC,
     CTL_ESC, LSFT_T(KC_F6), LCTL_T(KC_F7), LALT_T(KC_F8), LGUI_T(KC_F9), KC_F10,                                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC,
     KC_TRNS, KC_F1,         KC_F12,        KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_BSPC, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS,
                                            ADJUST,        ADJUST,        KC_LALT, KC_LGUI, KC_ENT, KC_SPC, KC_RGUI, KC_RALT, KC_SPC,  ADJUST
    ),

/*
 * Base Layer: QWERTY
 *
 * ,------------------------------------------.                              ,------------------------------------------.
 * |  Tab  |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  \ |  |
 * |-------+------+------+------+------+------|                              |------+------+------+------+------+-------|
 * |  Esc  |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "  |
 * |-------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
 * |  ` ~  |   Z  |   X  |   C  |   V  |   B  |  Del | Space|  | Enter| Bksp |   N  |   M  | ,  < | . >  | /  ? | Shift |
 * `---------------------+------+------+------+------+------|  |------+------+------+------+------+---------------------'
 *                       | Left |      |      |      | Enter|  | Space|      |      | Space| Up   |
 *                       | Right|----------------------------------------------------------| Down |
 *                       `------'                                                          `------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB,         KC_Q,  KC_W,  KC_E,   KC_R ,  KC_T,                                        KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,     KC_BSLS,
     CTL_ESC,        HRM_A, HRM_S, HRM_D,  HRM_F,  KC_G,                                        KC_H,    HRM_J,  HRM_K,   HRM_L,  HRM_SCLN, KC_QUOT,
     LSFT_T(KC_GRV), KC_Z,  KC_X,  KC_C,   KC_V,   KC_B,    KC_DEL,  UPR_SPC, LWR_ENT, KC_BSPC, KC_N,    KC_M ,  KC_COMM, KC_DOT, KC_SLSH , KC_RSFT,
                                   ADJUST, ADJUST, KC_LALT, KC_LGUI, LWR_ENT, UPR_SPC, KC_RGUI, KC_RALT, KC_SPC, ADJUST
    ),

/*
 * Lower layer
 *
 * ,-------------------------------------------.                              ,------------------------------------------.
 * |  Tab   |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |       |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+-------|
 * |Ctrl/Esc|   !  |   @  |   #  |   $  |   %  |                              |   ^  |   4  |   5  |   6  |   &  |       |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
 * |  ` ~   |   +  |   =  |   _  |   -  |  DEL |      |      |  | #### |      |   0  |   1  |   2  |   3  |   *  | Shift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+---------------------'
 *                        |  +   |      |      |      | #### |  |      |      |      |   0  | Left |
 *                        |   -  |----------------------------------------------------------| Right|
 *                        `------'                                                          `------'
 */
    [_LOWER] = LAYOUT(
    KC_TAB,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                                      KC_6,    KC_7,   KC_8,  KC_9, KC_0,    KC_TRNS,
    CTL_ESC, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                                   KC_CIRC, KC_4,   KC_5,  KC_6, KC_AMPR, KC_TRNS,
    KC_TRNS, KC_PLUS, KC_EQL, KC_UNDS, KC_MINS, KC_DEL,  KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_0,    KC_1,   KC_2,  KC_3, KC_ASTR, KC_RSFT,
                              ADJUST,  ADJUST,  KC_LALT, KC_LGUI, KC_ENT, KC_SPC, KC_RGUI, KC_RALT, KC_0,   ADJUST
    ),

/*
 * Adjust Layer: Media, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |M Prev|M Play|M Next| VolDn| VolUp|                              |      |      |      |      |      | Power  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | CapsLk |ScolLk| NumLk|      |      | Mute |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |ScrlLk| Pause|      | Reset|  | Reset|      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Vol+ |      |      |      |      |  |      |      |      |      | Dsp+ |
 *                        | Vol- |      |      |      |      |  |      |      |      |      | Dsp- |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______ , KC_MPRV , KC_MPLY , KC_MNXT , KC_VOLD , KC_VOLU ,                                         _______ , _______ , _______ , _______ , _______ , KC_PWR  ,
      KC_CAPS , KC_SCRL , KC_NUM  , _______ , _______ , KC_MUTE ,                                         RGB_TOG , RGB_SAI , RGB_HUI , RGB_VAI , RGB_MOD , _______ ,
      _______ , _______ , _______ , _______ , KC_SCRL , KC_PAUS , _______ , QK_BOOT , QK_BOOT , _______ , _______ , RGB_SAD , RGB_HUD , RGB_VAD , RGB_RMOD, _______ ,
                                    KC_NO   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_NO
    ),
};

#ifdef KEYBOARD_splitkb_kyria_rev1
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_UPPER]  = { ENCODER_CCW_CW(KC_TAB,   S(KC_TAB)), ENCODER_CCW_CW(KC_PGDN,  KC_PGUP ) },
    [_QWERTY] = { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT  ), ENCODER_CCW_CW(KC_DOWN,  KC_UP   ) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_PPLS,  KC_PMNS  ), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT ) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLU,  KC_VOLD  ), ENCODER_CCW_CW(KC_PAUS,  KC_SCRL ) },
};
#else
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_UPPER]  = { ENCODER_CCW_CW(S(KC_TAB), KC_TAB  ), ENCODER_CCW_CW(KC_PGUP, KC_PGDN  ) },
    [_QWERTY] = { ENCODER_CCW_CW(KC_LEFT,   KC_RIGHT), ENCODER_CCW_CW(KC_UP,   KC_DOWN  ) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_PMNS,   KC_PPLS ), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT ) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLD,   KC_VOLU ), ENCODER_CCW_CW(KC_SCRL, KC_PAUS  ) },
};
#endif

#define X_SIZE 128
#define Y_SIZE 64
#define N 20
#define ZOOM 0.7
#define N_FRAMES 50
#define FRAME_TIMEOUT (1000/30)

#define FRAME_SIZE (Y_SIZE * X_SIZE / 8)

char frames[N_FRAMES][FRAME_SIZE] = {{0}};
static uint16_t anim_timer = 0;
static int frame_cnt = 0;

void plot(char frame[FRAME_SIZE], int x, int y) {
    frame[(y / 8) * X_SIZE + x] |= 1 << y % 8;
}

void render_frame(char frame[FRAME_SIZE], int cnt) {
    double phi = 2.0 * M_PI * cnt / N_FRAMES;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            double x = (i - N / 2.0) * 2 / N;
            double y = (j - N / 2.0) * 2 / N;
            double d = sqrt(x * x + y * y);
            double z = (sqrt(2) - d) * sin(phi - d * 5) * ZOOM;
            double rotation = phi / 4;
            int xp = X_SIZE * (1 + (x * sin(rotation) + y * cos(rotation)) * ZOOM) / 2;
            int yp = Y_SIZE * (1 + (z + (x * cos(rotation) - y * sin(rotation)) / 2) * ZOOM) / 2;
            plot(frame, xp, yp);
        }
    }
}

static void render_anim(void) {
    if (timer_elapsed(anim_timer) > FRAME_TIMEOUT) {
        anim_timer = timer_read();
        if (is_oled_on()) {
            oled_write_raw(frames[frame_cnt], FRAME_SIZE);
            if (++frame_cnt == N_FRAMES) {
                frame_cnt = 0;
            };
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    for (int i=0; i < N_FRAMES; i++) {
        render_frame(frames[i], i);
    }
    anim_timer = timer_read();
    return rotation;
}

bool oled_task_user(void)
{
    if (is_keyboard_master()) {
         // QMK Logo and version information
        // clang-format off
        static const char qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write(qmk_logo, false);
        oled_write("\nDon't panic!\n", false);

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write(led_usb_state.caps_lock   ? "CAPSLCK" : "       ", false);
        oled_write(led_usb_state.scroll_lock ? "SCRLCK " : "       ", false);
        oled_write(led_usb_state.num_lock    ? "NUMLCK " : "       ", false);
        oled_write("\n", false);

        // Host Keyboard Layer Status
        oled_write("Layer: ", false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write("Vanilla", false);
                break;
            case _LOWER:
                oled_write("Lower  ", false);
                break;
            case _UPPER:
                oled_write("Upper  ", false);
                break;
            case _ADJUST:
                oled_write("Adjust ", false);
                break;
            default:
                oled_write("WUT?   ", false);
        }

    } else {
        render_anim();
    }

    return false;
}

