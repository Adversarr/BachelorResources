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
	set_sleep_count(ms);
	sleep();
  return 0;
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

/* Helper for buzzer, input param `freq` is linear to real frequency */
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

int main(void) {
	/* each stage will cost some time... */
	set_sleep_count(2000);
	/* Stage 0: Init ditigals display*/
	set_digital_higher_value(1, 2, 3, 4);
	set_digital_lower_value(5, 6, 7, 8);
	set_digital_status(15, 15);
	sleep();

	/* Stage 1: Init buzzer, */
	set_buzzer_freq(200);
	sleep();
	set_buzzer_freq(4000);
	sleep();
	set_buzzer_freq(1000);
	sleep();
	set_buzzer_freq(0);
	
	/* Stage 2: Init LED.*/
	set_led_value(0x55555555);
	sleep();
	set_led_value(0xAAAAAAAA);
	sleep();
	set_led_value(0xFFFFFFFF);
	sleep();
	set_led_value(0x00000000);

	/* Stage 3: Wait for keyboard input. */
	while (has_keyboard_down() != 1) {
		sleep();
		set_led_value(0xAAAAAAAA);
		sleep();
		set_led_value(0x55555555);
	}
	/* Stage 4: Turn off all the lights.*/
	set_led_value(0);
	set_digital_lower_value(0, 0, 0, 0);
	set_digital_higher_value(0, 0, 0, 0);
	set_sleep_count(1000);
	sleep();
	set_digital_status(0, 0);
	return 0;
}
