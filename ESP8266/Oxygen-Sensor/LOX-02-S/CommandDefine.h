// Battery Level
#define BAT_EMPTY 0
#define BAT_LOW   1
#define BAT_HIGH  2
#define BAT_FULL  3

// ASCII CODE
#define HEX_M		0x4D
#define HEX_O		0x4F
#define HEX_PERCENT	0x25
#define HEX_T		0x54
#define HEX_P		0x50
#define HEX_A		0x41
#define HEX_HASH	0x23
#define HEX_e		0x65
#define HEX_0		0x30
#define HEX_1		0x31
#define HEX_2		0x32
#define HEX_BLANK	0x20
#define HEX_CR		0x0D
#define HEX_LF		0x0A

const uint8_t	STREAM_MODE[] 	= {HEX_M, HEX_BLANK, HEX_0, HEX_CR, HEX_LF};
const uint8_t	POLL_MODE[] 	= {HEX_M, HEX_BLANK, HEX_1, HEX_CR, HEX_LF};
const uint8_t	STOP_MODE[] 	= {HEX_M, HEX_BLANK, HEX_2, HEX_CR, HEX_LF};

const uint8_t	REQ_PPO2	= {HEX_O};
const uint8_t	REQ_O2		= {HEX_PERCENT};
const uint8_t	REQ_TEMP	= {HEX_T};
const uint8_t	REQ_PRES	= {HEX_P};
const uint8_t	REQ_ST		= {HEX_e};
const uint8_t	REQ_ALL		= {HEX_A};
const uint8_t	REQ_INFO	= {HEX_HASH};
