oled_rotation_t oled_init_user(oled_rotation_t rotation) {
 return 3;
}

#ifdef WPM_ENABLE
	int current_wpm = 0;
	uint8_t get_current_wpm(void);
	#define WPM "WPM:"
	uint32_t anim_sleep = 0;



	void render_wpm(void) {
		uint8_t n = get_current_wpm();
		current_wpm = get_current_wpm();
		char wpm_counter[6];
		wpm_counter[5] = '\0';
		wpm_counter[4] = '0' + n % 10;
		wpm_counter[3] = ( n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
		wpm_counter[2] = n / 10 ? '0' + n / 10 : ' ';
		wpm_counter[1] = ' ';
		wpm_counter[0] = ' ';
		oled_write_P(PSTR(WPM), false);
		oled_write(wpm_counter, false);
	if (current_wpm > 0) {
			oled_on();
			anim_sleep = timer_read32();
		} else if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) { oled_off(); }

	}
#endif
	
void render_mod_status(void) {
    bool blink = (timer_read() % 1000) < 500;
    uint8_t modifiers = get_mods() | get_oneshot_mods();
        if (modifiers & MOD_MASK_CTRL) {
            oled_write_ln_P(blink ? PSTR("$ctl_") : PSTR("$ctl "), false);
        } else if (modifiers & MOD_MASK_SHIFT) {
            oled_write_ln_P(blink ? PSTR("$sft_") : PSTR("$sft "), false);
		} else if (modifiers & MOD_MASK_ALT) {
            oled_write_ln_P(blink ? PSTR("$alt_") : PSTR("$alt "), false);
        } else if (modifiers & MOD_MASK_GUI) {
            oled_write_ln_P(blink ? PSTR("$gui_") : PSTR("$gui "), false);
        } else {
            oled_write_ln_P(blink ? PSTR("$_  ") : PSTR("$    "), false);
        }
}

void render_layer_state(void) {
    bool blink = (timer_read() % 1000) < 500;
        switch (get_highest_layer(layer_state)){
			case _ART_BASE:
				oled_write_ln_P(blink ? PSTR(">_ ") : PSTR(">  "), false);
			break;
			case _ART_NUM:
				oled_write_ln_P(blink ? PSTR(">num_") : PSTR(">num "), false);
			break;
			case _ART_PUNC:
				oled_write_ln_P(blink ? PSTR(">punc_") : PSTR(">punc "), false);
			break;
			case _ART_CUS:
				oled_write_ln_P(blink ? PSTR(">cus_") : PSTR(">cus "), false);
			break;
			case _ART_SYM:
				oled_write_ln_P(blink ? PSTR(">sym_") : PSTR(">sym "), false);
			break;
			case _ART_MOU:
				oled_write_ln_P(blink ? PSTR(">mou_") : PSTR(">mou "), false);
			break;
			case _ART_NAV:
				oled_write_ln_P(blink ? PSTR(">nav_") : PSTR(">nav "), false);
			break;
			default:
			oled_write_ln_P(blink ? PSTR(">_ ") : PSTR(">  "), false);
		}

}
			

void render_map(void) {
	switch (get_highest_layer(layer_state)) {
        case _ART_BASE:
			if (get_mods() & MOD_BIT(KC_LSFT)) {
				oled_write(shifted_base_map, false);
			} 
			else if (get_oneshot_mods() & MOD_BIT(KC_LSFT)){
				oled_write(shifted_base_map, false);
			} else{
            oled_write(base_map, false);}
            break;
        case _ART_NUM:
            if (get_mods() & MOD_BIT(KC_LSFT)) {
				oled_write(shifted_num_map, false);
			} 
			else if (get_oneshot_mods() & MOD_BIT(KC_LSFT)){
				oled_write(shifted_num_map, false);
			} else {
            oled_write(num_map, false);}
            break;
        case _ART_NAV:
            oled_write_P(nav_map, false);
            break;
		case _ART_SYM:
			if (get_mods() & MOD_BIT(KC_LSFT)) {
				oled_write(shifted_sym_map, false);
			} 
			else if (get_oneshot_mods() & MOD_BIT(KC_LSFT)){
				oled_write(shifted_sym_map, false);
			} else {
            oled_write(sym_map, false);}
			break;
		case _ART_PUNC:
		    if (get_mods() & MOD_BIT(KC_LSFT)) {
				oled_write(shifted_punc_map, false);
			} 
			else if (get_oneshot_mods() & MOD_BIT(KC_LSFT)){
				oled_write(shifted_punc_map, false);
			} else {
            oled_write(punc_map, false);}
            break;
		case _ART_MOU:
			oled_write_P(mou_map, false);
			break;
		case _ART_CUS:
			    oled_write_ln_P(PSTR("Undefined"), false); //I didn't create a map for the custom layer. If you do, you would change this line.
			break;
        default:
            oled_clear();
    }
}



bool oled_task_user(void) {
	
	render_map();
	oled_set_cursor(0,3);
	render_layer_state();
	oled_set_cursor(0,5);
	render_mod_status();
	oled_set_cursor(0,7);
	oled_set_cursor(0,13);
	#ifdef WPM_ENABLE 
	render_wpm();
	#endif
    return false;

}



