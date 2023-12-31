#include <stdint.h>

enum can_ids {
    CAN_JOYSTICK_ID,
    CAN_PRINTSRT_ID,
    CAN_DUMMY_ID,
    CAN_CALIBRATION_ID,
    CAN_STARTGAME_ID
};

typedef struct joystick_message {
    uint8_t x;
    uint8_t y;
    uint8_t btn;
} JOYSTICK_MSG;