#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#define PORT_MATRIX             PORTA
#define PIN_MATRIX              PINA
#define KEY_MATRIX_COM          3

#define KEY_R1                  100

#define KEYS_COUNT              8
#define KEYS_ENC_COUNT          2

#define BUTTON_ENC_LEFT         0
#define BUTTON_ENC_RIGHT        1
#define BUTTON_0                2
#define BUTTON_1                3
#define BUTTON_2                4
#define BUTTON_3                5
#define BUTTON_4                6
#define BUTTON_5                7
#define BUTTON_6                8
#define BUTTON_7                9

#define BUTTON_HOME             0
#define BUTTON_MEDIA            1
#define BUTTON_PREV             2
#define BUTTON_ENCODER          3
#define BUTTON_NEXT             4
#define BUTTON_ONE              5
#define BUTTON_TWO              6
#define BUTTON_THREE            7

#define KEY_CODE_SEARCH_UP      0//430
#define KEY_CODE_SEARCH_DOWN    1//1110
#define KEY_CODE_MODE           2//2110
#define KEY_CODE_MUTE           3//3110
#define KEY_CODE_PLAY           4//3110
#define KEY_CODE_VOLUME_UP      5//4610
#define KEY_CODE_VOLUME_DOWN    8//6810
#define KEY_CODE_VOICE          13//10710
#define KEY_CODE_CALL_OFF       24//18910
#define KEY_CODE_CALL_ON        52//40910

#define BUTTON_FILTER_COUNT     5
#define BUTTON_LONG_COUNT       50

void buttons_routine(void);
unsigned char buttons_get_button_pressed(unsigned char button);
unsigned char buttons_get_button_long(unsigned char button);
unsigned char buttons_get_button_release(unsigned char button);
void buttons_clear_button(unsigned char button);
void buttons_clear_all_buttons(void);

#endif /* _BUTTONS_H_ */
