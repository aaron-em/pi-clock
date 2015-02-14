#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <bcm2835.h>
#include "pi-clock.h"

static int caughtSIGINT;

const int anodes[5] = {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5};
const int cathodes[7] = {PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G};
const int elements[5] = {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5};
const int digits[10] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9};

void catchINT(int dummy) {
    caughtSIGINT = 1;
}

void set(int pin, int value) {
    bcm2835_gpio_write(pin, value);
}

void set_element(int element, int character) {
    set(element, HIGH);
    set(PIN_A, (character & SEGMENT_A) ? LOW : HIGH);
    set(PIN_B, (character & SEGMENT_B) ? LOW : HIGH);
    set(PIN_C, (character & SEGMENT_C) ? LOW : HIGH);
    set(PIN_D, (character & SEGMENT_D) ? LOW : HIGH);
    set(PIN_E, (character & SEGMENT_E) ? LOW : HIGH);
    set(PIN_F, (character & SEGMENT_F) ? LOW : HIGH);
    set(PIN_G, (character & SEGMENT_G) ? LOW : HIGH);
}

void clear_element(int element) {
    set_element(element, BLANK);
    set(element, LOW);
}

void clear_all() {
    int i;
    for (i = 0; i < 5; i++) {
        clear_element(elements[i]);
    }
}

void setup_gpio() {
    int i;

    for (i = 0; i < 5; i++) {
        bcm2835_gpio_fsel(anodes[i], BCM2835_GPIO_FSEL_OUTP);
        set(anodes[i], LOW);
    }

    for (i = 0; i < 7; i++) {
        bcm2835_gpio_fsel(cathodes[i], BCM2835_GPIO_FSEL_OUTP);
        set(cathodes[i], HIGH);
    }
}

void usleep(int micros) {
    struct timespec nanotime, leftover;
    nanotime.tv_sec = 0;
    nanotime.tv_nsec = (1000 * micros);
    nanosleep(&nanotime, &leftover);

    if (DEBUG) {
        printf("Leftover time: %li μs\n", leftover.tv_nsec / 1000);
    }
}

int time_digit(int digit, struct tm* time) {
    if (digit == 0) return TENS(time->tm_hour);
    if (digit == 1) return ONES(time->tm_hour);
    if (digit == 2) return TENS(time->tm_min);
    if (digit == 3) return ONES(time->tm_min);
    return BLANK;
}

int main (int argc, char **argv) {
    int element;
    int n_seg;
    int digit;
    int qmin;
    
    time_t tm;
    struct tm* now;

    caughtSIGINT = 0;
    signal(SIGINT, catchINT);
    
    if (!bcm2835_init()) {
        fputs("Failed to initialize BCM2835 library\n", stderr);
        return 1;
    }

    setup_gpio();

    while (caughtSIGINT == 0) {
        time(&tm);
        now = localtime(&tm);
        
        for (n_seg = 0; n_seg < 5; n_seg++) {
            element = elements[n_seg];
            digit = (n_seg < 4 ? digits[time_digit(n_seg, now)] : COLON);

            if (LEADING_ZERO == false && n_seg == 0 && digit == (DIGIT_0)) {
                digit = BLANK;
            }

            if (QUARTER_MINUTES == true && n_seg == 4) {
                qmin = (int)(((float) now->tm_sec) / 15);
                switch (qmin) {
                case 0:
                    digit |= DECIMAL_2;
                    break;
                case 1:
                    digit |= DECIMAL_3;
                    break;
                case 2:
                    digit |= DECIMAL_4;
                    break;
                case 3:
                    digit |= DECIMAL_1;
                    break;
                }
            }

            set_element(element, digit);
            usleep(1000);
            clear_element(element);
        }
    }

    for (n_seg = 0; n_seg < 5; n_seg++) {
        clear_element(elements[n_seg]);
    }
    
    return 0;
}
