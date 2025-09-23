RGB_MATRIX_EFFECT(star_wars)

#define INDICATOR_UPDATE_TIME 100  // set how often the indicator will change hue, in milliseconds

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef struct {
    int num;
    RGB color;  // For storing a single character (and null terminator)
} MyStruct;

static uint16_t list_index  = 0;
static uint16_t last_ind_update = 0;
static bool update_values;
static RGB color = {RGB_RED};

MyStruct myList[43] = {
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {343, {RGB_BLACK}},
    {32, {RGB_PINK}},
    {93, {RGB_BLACK}},
    {32, {RGB_BLUE}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {343, {RGB_BLACK}},
    {32, {RGB_PINK}},
    {93, {RGB_BLACK}},
    {32, {RGB_BLUE}},
    {968, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {343, {RGB_BLACK}},
    {32, {RGB_PINK}},
    {93, {RGB_BLACK}},
    {32, {RGB_BLUE}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {343, {RGB_BLACK}},
    {32, {RGB_PINK}},
    {93, {RGB_BLACK}},
    {32, {RGB_BLUE}},
    {468, {RGB_BLACK}},
    {32, {RGB_RED}},
    {343, {RGB_BLACK}},
    {32, {RGB_PINK}},
    {93, {RGB_BLACK}},
    {32, {RGB_BLUE}},
    {968, {RGB_BLACK}},
};

//  ED_NOTE(_F4), S__NOTE(_C5), H__NOTE(_A4), Q__NOTE(_E5), Q__NOTE(_E5), Q__NOTE(_E5), ED_NOTE(_F5), S__NOTE(_C5), Q__NOTE(_GS4), ED_NOTE(_F4), S__NOTE(_C5), Q__NOTE(_A4), ED_NOTE(_F4), S__NOTE(_C5), H__NOTE(_A4))


static void star_wars_init(effect_params_t* params) {
    // list_index = 0;
    // last_ind_update = timer_read();
}

static bool star_wars_run(effect_params_t* params) {
    // if (params->iter == 0) {
    update_values = timer_elapsed(last_ind_update) >= myList[list_index].num;
    color = myList[list_index].color;

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (update_values) {
        for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++) {
            for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++) {
                if (g_led_config.matrix_co[i_row][i_col] == NO_LED) { // skip as target key doesn't have an led position
                    continue;
                }
                rgb_matrix_set_color(g_led_config.matrix_co[i_row][i_col], color.r, color.g, color.b);
            }
        }
        last_ind_update = timer_read();
        color = myList[list_index].color;
        list_index++;
        if (list_index == 43){ list_index = 0;}
        return rgb_matrix_check_finished_leds(led_max);
    }
    return true;
}

static bool star_wars(effect_params_t* params) {
  if (params->init) star_wars_init(params);
  return star_wars_run(params);
}


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS