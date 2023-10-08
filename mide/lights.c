int sleep_count;
int sleep(void) {
	int x;
	x = 0;
	while (x < sleep_count) {
		x = x + 1;
	}
	return x;
}

int set_sleep_count(int ms) {
	sleep_count = ms * 1310;
	return sleep_count;
}

int sleep_ms(int ms) {
	int count;
	int x;
	count = ms * 1310;
	x = 0;
	while (x < count) {
		x = x + 1;
	}
}

/* Helpers for LED, tested. */
int set_led_value(int value) {
  $(0xfffffc60) = value;
  return value;
}

int get_led_value(void) {
  int x;
  x = $(0xfffffc60);
  return x;
}

/* Helpers for Digits. TESTED. */
int set_digital_higher_value(int a, int b, int c, int d) {
  int x;
  a = a & 0xF;
  b = b & 0xF;
  c = c & 0xF;
  d = d & 0xF;
  x = a;
  x = (x << 4) | b;
  x = (x << 4) | c;
  x = (x << 4) | d;
  $(0xFFFFFC00) = x;
}
int set_digital_lower_value(int a, int b, int c, int d) {
  int x;
  a = a & 0xF;
  b = b & 0xF;
  c = c & 0xF;
  d = d & 0xF;
  x = a;
  x = (x << 4) | b;
  x = (x << 4) | c;
  x = (x << 4) | d;
  $(0xFFFFFC02) = x;
}

int set_digital_status(int enable_lower, int enable_higher) {
  int x;
  x = 0;
  enable_lower = enable_lower & 255;
  enable_lower = enable_lower * 256;
  enable_higher = enable_higher & 255;
  enable_higher = enable_higher * 4096;
  x = enable_lower + enable_higher + 255;
  $(0XFFFFFC04) = x;
}

/* Helpers for switch, tested. */
int get_switch_value(void) {
  int x;
  x = $(0XFFFFFC70);
  return x;
}

/* (Tested) Helper for keyboard: 0-D for 0~D. E for star, F for # */
int extract(int x, int d) {
	return (x >> d) & 1;
}
int keyboard_is_pressed(int required) {
  int x;
  int retval;
  retval = 0;
  x = $(0xFFFFFC10);
  retval = x & 0xFFFF;
  if (required == 0) {
	retval = extract(x, 8);
  }
  if (required == 1) {
	retval = extract(x, 15);
  }
  if (required == 2) {
	retval = extract(x, 11);
  }
  if (required == 3) {
	retval = extract(x, 7);
  }
  if (required == 4) {
	retval = extract(x, 14);
  }
  if (required == 5) {
	retval = extract(x, 10);
  }
  if (required == 6) {
	retval = extract(x, 6);
  }
  if (required == 7) {
	retval = extract(x, 13);
  }
  if (required == 8) {
	retval = extract(x, 9);
  }
  if (required == 9) {
	retval = extract(x, 5);
  }
  if (required == 10) {
	retval = extract(x, 3);
  }
  if (required == 11) {
	retval = extract(x, 2);
  }
  if (required == 12) {
	retval = extract(x, 1);
  }
  if (required == 13) {
	retval = extract(x, 0);
  }
  if (required == 14) {
	retval = extract(x, 12);
  }
  if (required == 15) {
	retval = extract(x, 4);
  }
  return retval;
}

/* Helper for buzzer TESTED. */
int set_buzzer_freq(int freq) {
  int cnt;
  if (freq == 0) {
    cnt = 0;
  } else {
    cnt = 0x1400000 / freq;
  }
  $(0xFFFFFD10) = cnt;
}

int has_keyboard_down(void) {
	int temp;
	temp = keyboard_is_pressed(0xFF);
	if (temp == 0) {
		temp = 0;
	} else {
		temp = 1;
	}
	return temp;
}


int x;

int update_buzzer(void) {
	int x;
	
}

int dec_to_hex(int in_x) {
	int ret;
	ret = 0;
	while (in_x > 0) {
		ret = ret << 4;
		ret = ret + (in_x - (in_x / 10) * 10);
		in_x = in_x / 10;
	}
	return ret;
}

int value[10];

int update_from_keyboard(void) {
	x = 0;
	if (keyboard_is_pressed(1)) {
		x = 261;
	}
	if (keyboard_is_pressed(2)) {
		x = 293;
	}
	if (keyboard_is_pressed(3)) {
		x = 329;
	}
	if (keyboard_is_pressed(4)) {
		x = 350;
	}
	if (keyboard_is_pressed(5)) {
		x = 392;
	}
	if (keyboard_is_pressed(6)) {
		x = 440;
	}
	if (keyboard_is_pressed(7)) {
		x = 494;
	}
	if (keyboard_is_pressed(8)) {
		x = 523;
	}


}

int y;

int main(void) {
	value[10] = 0;
	set_digital_status(15, 15);
	y = 0xAAAAAAAA;
	while (1) {
		update_from_keyboard();
		value[16] = get_switch_value();
		set_digital_higher_value(value[16] >> 12, value[16] >> 8, value[16] >> 4, value[16]);
		sleep_ms(value[16] * 30 + 20);
		x = value[16] * x;
		set_buzzer_freq(x * value[16]);
		set_digital_lower_value(x >> 12, x >> 8, x >> 4, x);
		value[10] = value[10] + 1;
		if (value[10] == 20) {
			value[10] = 0;
			y = 0xFFFFFFFF ^ y;
			set_led_value(y);
		}

	}
	return 0;
}
