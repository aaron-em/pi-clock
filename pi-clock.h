/*
 * Configurable values
 */

// Show debugging info (currently only the leftover from nanosleep)
#define DEBUG false

// Whether to show a leading zero on the hours value
#define LEADING_ZERO true

// Whether to use the decimals for quarter-minutes
#define QUARTER_MINUTES false

// NB these are pin #s on the J8 header, not BCM GPIO pin #s

// GPIO pins connected to LED display's anodes
#define PIN_1 RPI_BPLUS_GPIO_J8_24
#define PIN_2 RPI_BPLUS_GPIO_J8_07
#define PIN_3 RPI_BPLUS_GPIO_J8_32
#define PIN_4 RPI_BPLUS_GPIO_J8_18
#define PIN_5 RPI_BPLUS_GPIO_J8_26
// GPIO pins connected to LED display's cathodes
#define PIN_A RPI_BPLUS_GPIO_J8_37
#define PIN_B RPI_BPLUS_GPIO_J8_33
#define PIN_C RPI_BPLUS_GPIO_J8_15
#define PIN_D RPI_BPLUS_GPIO_J8_29
#define PIN_E RPI_BPLUS_GPIO_J8_31
#define PIN_F RPI_BPLUS_GPIO_J8_35
#define PIN_G RPI_BPLUS_GPIO_J8_13

// These get OR'd together to represent the elements lit for a given character
#define SEGMENT_A 1
#define SEGMENT_B 2
#define SEGMENT_C 4
#define SEGMENT_D 8
#define SEGMENT_E 16
#define SEGMENT_F 32
#define SEGMENT_G 64

#define BLANK 0

#define DECIMAL_1 SEGMENT_G
#define DECIMAL_2 SEGMENT_E
#define DECIMAL_3 SEGMENT_D
#define DECIMAL_4 SEGMENT_C
#define COLON SEGMENT_B | SEGMENT_F

#define DIGIT_0 SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F
#define DIGIT_1 SEGMENT_B | SEGMENT_C
#define DIGIT_2 SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G
#define DIGIT_3 SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G
#define DIGIT_4 SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G
#define DIGIT_5 SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G
#define DIGIT_6 SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G
#define DIGIT_7 SEGMENT_A | SEGMENT_B | SEGMENT_C
#define DIGIT_8 SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G
#define DIGIT_9 SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G

#define true 1
#define false 0

#define TENS(n) (n < 10 ? 0 : (int)((double) n / 10))
#define ONES(n) (n - (10 * TENS(n)))
