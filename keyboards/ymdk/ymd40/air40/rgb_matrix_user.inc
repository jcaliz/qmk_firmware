#include "info_config.h"
RGB_MATRIX_EFFECT(SINGLE_COLOR_RAINDROPS)
RGB_MATRIX_EFFECT(STARLIGHT)
RGB_MATRIX_EFFECT(MATRIX_SCREEN)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* This effect has been partially derived from quantum/rgb_matrix/animations/pixel_rain_anim.h and raindrops_anim.h
It sets random LEDs to matrix color (with very slight hue variation) but random intensity */
static bool SINGLE_COLOR_RAINDROPS(effect_params_t* params) {
    static uint32_t wait_timer = 0;

    // interval function and timing in general taken from pixel rain animation
    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    void single_color_raindrops_set_color(uint8_t i, effect_params_t * params) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) {
            return;
        }

        // Take matrix color, add between -5 and +5 to hue, random brightness between 0 and val, set to 0 if val between 0 and 5, then write to LED
        hsv_t hsv = rgb_matrix_get_hsv();
        hsv.h = rgb_matrix_get_hue() - 2 + random8() % 5;
        hsv.v = random8() % rgb_matrix_get_val();
        if (hsv.v < 5) {
            hsv.v = 0;
        }
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        wait_timer = g_rgb_timer + interval();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (!params->init) {
        if (g_rgb_timer > wait_timer) {
            single_color_raindrops_set_color(mod8(random8(), RGB_MATRIX_LED_COUNT), params);
        }
    } else {
        for (int i = led_min; i < led_max; i++) {
            single_color_raindrops_set_color(i, params);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static void set_starlight_color(uint8_t i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;

    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv_t    hsv  = rgb_matrix_config.hsv;
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    rgb_t rgb     = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool STARLIGHT(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;


    // Periodic trigger for LED change
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 5)) % 5 == 0)) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            set_starlight_color(i, params);
        }
    }
    // Change LED once and set index out of range till next trigger
    else if (led_min <= index && index < led_max) {
        set_starlight_color(index, params);
        index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}


bool MATRIX_SCREEN(effect_params_t* params) {

    static uint16_t last_change = 0;
    static uint16_t last_pick = 0;
    static uint8_t col_min = 0;
    static uint8_t col_max = MATRIX_COLS / 2 - 1;

    static uint8_t last_row[MATRIX_COLS];
    static uint16_t column_period[MATRIX_COLS];
    static uint16_t column_last_update[MATRIX_COLS];
    static uint16_t next_pick_interval = 0;

    static bool init = false;
    uint16_t elapsed = timer_elapsed(last_change);

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (!init) {
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            last_row[i] = MATRIX_ROWS + 1;
        }
        for (int i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }

        init = true;
    }


    // uprintf("Elapsed: %u\n", elapsed);
    // Clear columns where last_row[column] == MATRIX_COLS + 1
    if (elapsed > 200){
        for (uint8_t column = 0; column < MATRIX_COLS; column++) {
            if (last_row[column] == MATRIX_ROWS){
                for (uint8_t row = 0; row < MATRIX_ROWS; row++){
                    uint8_t led_index = g_led_config.matrix_co[row][column];
                    rgb_matrix_set_color(led_index, 0, 0, 0);
                    // uprintf("Turning led to 0, %u, %u\n", row, column);
                }
                last_row[column] = MATRIX_ROWS + 1;
            }

        }
        last_change = timer_read();
    }


    if (timer_elapsed(last_pick) > next_pick_interval) {
        uint8_t c = rand() % (col_max - col_min + 1) + col_min;

        if (last_row[c] == MATRIX_ROWS + 1){
            column_period[c] =  rand() % (200 - 50 + 1) + 50;
            column_last_update[c] = timer_read();
            last_row[c] = 0;

            if (col_min == 0){
                col_min = MATRIX_COLS / 2;
                col_max = MATRIX_COLS - 1;
            }
            else {
                col_min = 0;
                col_max = MATRIX_COLS / 2 - 1;
            }
            next_pick_interval = 100 + rand() % 300;  // next pick in 300–700ms
        }
        last_pick = timer_read();
    }

    for (uint8_t column = 0; column < MATRIX_COLS; column++) {
        if (last_row[column] >= MATRIX_ROWS) continue;

        // uprintf("Column: %u, last_row: %u, total_rows %u\n", column, last_row[column], MATRIX_ROWS);
        uint8_t led_index = g_led_config.matrix_co[last_row[column]][column];
            if (timer_elapsed(column_last_update[column]) > column_period[column]){
                if (led_index != NO_LED) {
                    rgb_matrix_set_color(led_index, 0, 50, 0); // Dark green
                    column_last_update[column] = timer_read();
                }
                last_row[column]++;
        }

    }


    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
