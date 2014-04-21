#ifndef OFX_GAMEPAD_CONFIGS
#define OFX_GAMEPAD_CONFIGS

#define PS3_NAME "Sony PLAYSTATION(R)3 Controller"

enum GAMEPAD_TYPE{
	GAMEPAD_UNKNOWN,
	GAMEPAD_PS3,
	GAMEPAD_XBOX,
	GAMEPAD_XBOX_WIRELESS,
	GAMEPAD_OUYA
};

enum PS3_CONFIG {
    PS3_STICK_L_X = 0,
    PS3_STICK_L_Y = 1,
    PS3_STICK_R_X = 2,
    PS3_STICK_R_Y = 3,
    PS3_THRUST_L2 = 12,
    PS3_THRUST_R2 = 13,
    PS3_BTN_CROSS = 14,
    PS3_BTN_CIRCLE = 13,
    PS3_BTN_SQUARE = 15,
    PS3_BTN_TRIANGLE = 12,
    PS3_BTN_R1 = 11,
    PS3_BTN_R2 = 9,
    PS3_BTN_L1 = 10,
    PS3_BTN_L2 = 8,
    PS3_BTN_SELECT = 0,
    PS3_BTN_START = 3,
    PS3_BTN_STICK_R = 2,
    PS3_BTN_STICK_L = 1,
    PS3_DIR_RIGHT = 5,
    PS3_DIR_UP = 4,
    PS3_DIR_LEFT = 7,
    PS3_DIR_DOWN = 6
};

#ifdef USE_OIS
#define XBOX_NAME "Microsoft Wireless 360 Controller"
#define XBOX_WIRELESS_NAME "Xbox 360 Wireless Receiver"

enum XBOX_CONFIG {
    XB_STICK_L_X = 2,
    XB_STICK_L_Y = 3,
    XB_STICK_R_X = 4,
    XB_STICK_R_Y = 5,
    XB_STICK_LT = 0,
    XB_STICK_RT = 1,
    XB_BTN_A = 11,
    XB_BTN_B = 12,
    XB_BTN_X = 13,
    XB_BTN_Y = 14,
    XB_BTN_BACK = 5,
    XB_BTN_START = 4,
    XB_BTN_LOGO = 10,
    XB_BTN_LB = 8,
    XB_BTN_RB = 9,
    XB_BTN_STICK_L = 6,
    XB_BTN_STICK_R = 7,
    XB_DIR_UP = 0,
    XB_DIR_DOWN = 1,
    XB_DIR_LEFT = 2,
    XB_DIR_RIGHT = 3
};

enum XBOX_WIRELESS_CONFIG {
    XB_STICK_L_X = 0,
    XB_STICK_L_Y = 1,
    XB_STICK_R_X = 3,
    XB_STICK_R_Y = 4,
    XB_STICK_LT = 2,
    XB_STICK_RT = 5,
    XB_BTN_A = 0,
    XB_BTN_B = 1,
    XB_BTN_X = 2,
    XB_BTN_Y = 3,
    XB_BTN_BACK = 6,
    XB_BTN_START = 7,
    XB_BTN_LOGO = 8,
    XB_BTN_LB = 4,
    XB_BTN_RB = 5,
    XB_BTN_STICK_L = 9,
    XB_BTN_STICK_R = 10,
    XB_DIR_UP = 13,
    XB_DIR_DOWN = 14,
    XB_DIR_LEFT = 11,
    XB_DIR_RIGHT = 12
};

#else //#elif defined(TARGET_LINUX)
#define XBOX_NAME "Microsoft X-Box 360 pad"
#define XBOX_WIRELESS_NAME "Xbox 360 Wireless Receiver"

enum XBOX_CONFIG {
    XB_STICK_L_X = 0,
    XB_STICK_L_Y = 1,
    XB_STICK_R_X = 6,
    XB_STICK_R_Y = 7,
    XB_STICK_LT = 4,
    XB_STICK_RT = 5,
    XB_BTN_A = 0,
    XB_BTN_B = 1,
    XB_BTN_X = 2,
    XB_BTN_Y = 3,
    XB_BTN_BACK = 6,
    XB_BTN_START = 7,
    XB_BTN_LOGO = 8,
    XB_BTN_LB = 4,
    XB_BTN_RB = 5,
    XB_BTN_STICK_L = 9,
    XB_BTN_STICK_R = 10,
    XB_DIR_X = 2,
    XB_DIR_Y = 3
};

enum XBOX_WIRELESS_CONFIG {
    XBW_STICK_L_X = 0,
    XBW_STICK_L_Y = 1,
    XBW_STICK_R_X = 3,
    XBW_STICK_R_Y = 4,
    XBW_STICK_LT = 2,
    XBW_STICK_RT = 5,
    XBW_BTN_A = 0,
    XBW_BTN_B = 1,
    XBW_BTN_X = 2,
    XBW_BTN_Y = 3,
    XBW_BTN_BACK = 6,
    XBW_BTN_START = 7,
    XBW_BTN_LOGO = 8,
    XBW_BTN_LB = 4,
    XBW_BTN_RB = 5,
    XBW_BTN_STICK_L = 9,
    XBW_BTN_STICK_R = 10,
    XBW_DIR_UP = 13,
    XBW_DIR_DOWN = 14,
    XBW_DIR_LEFT = 11,
    XBW_DIR_RIGHT = 12
};


#endif

#define OUYA_NAME "Ouya Wireless Controller"

// the sticks might be wrong here
enum OUYA_CONFIG {
    OUYA_STICK_L_X = 2,
    OUYA_STICK_L_Y = 3,
    OUYA_STICK_R_X = 4,
    OUYA_STICK_R_Y = 5,
    OUYA_STICK_LT = 0,
    OUYA_STICK_RT = 1,
    OUYA_BTN_O = 96,
    OUYA_BTN_U = 99,
    OUYA_BTN_Y = 100,
    OUYA_BTN_A = 97,
    OUYA_BTN_LOGO = 10,// logo is always home i think
    OUYA_BTN_LB = 102,
    OUYA_BTN_RB = 103,
    OUYA_BTN_LT = 104,
    OUYA_BTN_RT = 105,
    OUYA_BTN_STICK_L = 106,
    OUYA_BTN_STICK_R = 107,
    OUYA_DIR_UP = 19,
    OUYA_DIR_DOWN = 20,
    OUYA_DIR_LEFT = 21,
    OUYA_DIR_RIGHT = 22
};

extern char *KNOWN_CONTROLLER_NAMES[];
#endif
