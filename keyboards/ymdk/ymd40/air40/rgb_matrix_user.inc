RGB_MATRIX_EFFECT(SINGLE_COLOR_RAINDROPS)
RGB_MATRIX_EFFECT(STARLIGHT)

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


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
