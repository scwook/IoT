#define raon_symbol_width 130
#define raon_symbol_height 34
static unsigned char raon_symbol_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x01, 0x00, 0x00, 0x00,
  0x00, 0xc0, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x18, 0x00, 0x00, 0x00, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xf0, 0x01, 0x00, 0xf8, 0x7f, 0x00,
  0x7e, 0x00, 0xfc, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xf0,
  0x03, 0x00, 0xfe, 0xff, 0x00, 0x7e, 0x00, 0xfc, 0x00, 0xfe, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0xf8, 0x07, 0x00, 0xff, 0xff, 0x03, 0xfe, 0x00,
  0xfc, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x07, 0xc0,
  0xff, 0xff, 0x07, 0xfe, 0x01, 0xfc, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x03, 0xfc, 0x07, 0xc0, 0xff, 0xff, 0x0f, 0xfe, 0x03, 0xfc, 0x00,
  0xfc, 0xff, 0x01, 0x00, 0x00, 0xfc, 0x03, 0xfc, 0x0f, 0xe0, 0xff, 0xff,
  0x0f, 0xfe, 0x07, 0xfc, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00, 0xf8, 0x03,
  0xfc, 0x0f, 0xf0, 0x3f, 0xf0, 0x1f, 0xfe, 0x07, 0xfc, 0x00, 0xf8, 0xff,
  0x00, 0x00, 0x00, 0xf0, 0x03, 0xfe, 0x1f, 0xf0, 0x0f, 0xe0, 0x1f, 0xfe,
  0x0f, 0xfc, 0x00, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xfe, 0x1f,
  0xf8, 0x07, 0xc0, 0x3f, 0xfe, 0x1f, 0xfc, 0x00, 0xc0, 0x1f, 0x00, 0x00,
  0x00, 0xf0, 0x03, 0xff, 0x3f, 0xf8, 0x03, 0x80, 0x3f, 0xfe, 0x3f, 0xfc,
  0x00, 0x80, 0x0f, 0x00, 0x00, 0x00, 0xf8, 0x03, 0xff, 0x3f, 0xf8, 0x03,
  0x80, 0x3f, 0xfe, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
  0x83, 0x3f, 0x7f, 0xfc, 0x01, 0x00, 0x7f, 0xfe, 0x7f, 0xfc, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0x83, 0x3f, 0x7f, 0xfc, 0x01, 0x00, 0x7f,
  0x7e, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc1, 0x1f,
  0xfe, 0xfc, 0x01, 0x00, 0x7f, 0x7e, 0xfe, 0xfd, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xfe, 0xff, 0xc0, 0x1f, 0xfe, 0xfc, 0x01, 0x00, 0x7f, 0x7e, 0xfc,
  0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x7f, 0xe0, 0x0f, 0xfe, 0xf9,
  0x03, 0x00, 0x7f, 0x7e, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
  0x1f, 0xe0, 0xff, 0xff, 0xf9, 0x03, 0x80, 0x7f, 0x7e, 0xf8, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xf0, 0xff, 0xff, 0xf9, 0x07, 0x80,
  0x3f, 0x7e, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0xf0,
  0xff, 0xff, 0xf3, 0x07, 0xc0, 0x3f, 0x7e, 0xe0, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x1f, 0xf0, 0xff, 0xff, 0xf3, 0x0f, 0xe0, 0x1f, 0x7e,
  0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0xf8, 0xff, 0xff,
  0xf7, 0x3f, 0xf8, 0x1f, 0x7e, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xc0, 0x7f, 0xf8, 0x03, 0xf0, 0xe7, 0xff, 0xff, 0x0f, 0x7e, 0x80, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xfc, 0x01, 0xe0, 0xcf, 0xff,
  0xff, 0x07, 0x7e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xfd, 0x01, 0xe0, 0x8f, 0xff, 0xff, 0x07, 0x7e, 0x00, 0xfe, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0xe0, 0x1f, 0xff, 0xff, 0x01,
  0x7e, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x00,
  0xc0, 0x1f, 0xfe, 0xff, 0x00, 0x7e, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfc, 0xff, 0x00, 0xc0, 0x1f, 0xf8, 0x3f, 0x00, 0x7e, 0x00,
  0xf8, 0x00
};

#define wifi_s0_width 14
#define wifi_s0_height 12
static unsigned char wifi_s0_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define wifi_s1_width 14
#define wifi_s1_height 12
static unsigned char wifi_s1_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00
};

#define wifi_s2_width 14
#define wifi_s2_height 12
static unsigned char wifi_s2_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x33, 0x00, 0x33, 0x00, 0x33, 0x00
};

#define wifi_s3_width 14
#define wifi_s3_height 12
static unsigned char wifi_s3_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03,
  0x30, 0x03, 0x30, 0x03, 0x30, 0x03, 0x33, 0x03, 0x33, 0x03, 0x33, 0x03
};

#define wifi_s4_width 14
#define wifi_s4_height 12
static unsigned char wifi_s4_bits[] = {
  0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x33, 0x00, 0x33, 0x00, 0x33,
  0x30, 0x33, 0x30, 0x33, 0x30, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33
};

#define wifi_width 14
#define wifi_height 12
static unsigned char *wifi_bits[][5] = {
  {wifi_s0_bits}, {wifi_s1_bits}, {wifi_s2_bits}, {wifi_s3_bits}, {wifi_s4_bits}
};

#define temperature_image_width 13
#define temperature_image_height 20
static unsigned char temperature_image_bits[] = {
  0x00, 0x00, 0xe0, 0x00, 0x10, 0x01, 0x90, 0x01, 0x10, 0x01, 0x90, 0x01,
  0x10, 0x01, 0x10, 0x01, 0x90, 0x01, 0x10, 0x01, 0x18, 0x03, 0x0c, 0x06,
  0x04, 0x04, 0x02, 0x08, 0x02, 0x08, 0x06, 0x0c, 0x04, 0x04, 0x0c, 0x06,
  0xf8, 0x01, 0x00, 0x00
};

#define battery_16x10_width 16
#define battery_16x10_height 10
static unsigned char battery_empty_bits[] = {
  0xfe, 0xff, 0x02, 0x80, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
  0x01, 0x80, 0x03, 0x80, 0x02, 0x80, 0xfe, 0xff
};

static unsigned char battery_low_bits[] = {
  0xfe, 0xff, 0x02, 0x80, 0x03, 0xb8, 0x01, 0xb8, 0x01, 0xb8, 0x01, 0xb8,
  0x01, 0xb8, 0x03, 0xb8, 0x02, 0x80, 0xfe, 0xff
};

static unsigned char battery_high_bits[] = {
  0xfe, 0xff, 0x02, 0x80, 0x83, 0xbb, 0x81, 0xbb, 0x81, 0xbb, 0x81, 0xbb,
  0x81, 0xbb, 0x83, 0xbb, 0x02, 0x80, 0xfe, 0xff
};

static unsigned char battery_full_bits[] = {
  0xfe, 0xff, 0x02, 0x80, 0xbb, 0xbb, 0xb9, 0xbb, 0xb9, 0xbb, 0xb9, 0xbb,
  0xb9, 0xbb, 0xbb, 0xbb, 0x02, 0x80, 0xfe, 0xff
};

#define battery_width   16
#define battery_height  10
static unsigned char *battery_bits[][4] = {
  {battery_empty_bits}, {battery_low_bits}, {battery_high_bits}, {battery_full_bits}
};

#define wifi_symbole_width 42
#define wifi_symbole_height 14
static unsigned char wifi_symbol_bits[] = {
  0xfc, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfe, 0xff, 0x7f, 0x00, 0x80, 0x01,
  0xff, 0xff, 0x3f, 0x00, 0x00, 0x03, 0xf3, 0x9e, 0x1c, 0xfc, 0x0c, 0x02,
  0xf3, 0x9e, 0x1c, 0xfc, 0x0c, 0x02, 0x77, 0xdc, 0x1f, 0x0c, 0x00, 0x02,
  0x67, 0xcd, 0x1c, 0x0c, 0x0c, 0x02, 0x27, 0xc9, 0x1c, 0xfc, 0x0c, 0x02,
  0x2f, 0xe9, 0x1c, 0xfc, 0x0c, 0x02, 0x8f, 0xe3, 0x1c, 0x0c, 0x0c, 0x02,
  0x9f, 0xf3, 0x1c, 0x0c, 0x0c, 0x02, 0xdf, 0xf7, 0x0c, 0x0c, 0x0c, 0x03,
  0xfe, 0xff, 0x07, 0x00, 0x80, 0x01, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x00
};

#define epics_new_width 34
#define epics_new_height 14
static unsigned char epics_new_bits[] = {
  0xff, 0xff, 0xc7, 0xff, 0x03, 0xff, 0xff, 0xc7, 0xff, 0x03, 0xff, 0xff,
  0xc7, 0xff, 0x03, 0xff, 0xff, 0xc7, 0xff, 0x03, 0xff, 0x8f, 0xc7, 0xff,
  0x03, 0xff, 0x8f, 0xc7, 0xff, 0x03, 0xff, 0x8f, 0xc7, 0xff, 0x03, 0xff,
  0x8f, 0xc7, 0xff, 0x03, 0xff, 0x8f, 0xc7, 0xff, 0x03, 0xff, 0x8f, 0xc7,
  0xff, 0x03, 0xff, 0x8f, 0xff, 0xff, 0x03, 0xff, 0x8f, 0xff, 0xff, 0x03,
  0xff, 0x8f, 0xff, 0xff, 0x03, 0xff, 0x8f, 0xff, 0xff, 0x03
};

#define epics_width 12
#define epics_height 13
static unsigned char epics_bits[] = {
  0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x08, 0x00,
  0xff, 0x0f, 0x00, 0x01, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07,
  0xc0, 0x07
};
#define scl_width 120
#define scl_height 43
static unsigned char scl_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xc0, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xc0, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define circle_frame_width 24
#define circle_frame_height 24
static unsigned char circle_frame_bits[] = {
  0x00, 0x7e, 0x00, 0xc0, 0xc3, 0x03, 0x70, 0x00, 0x0e, 0x18, 0x00, 0x18,
  0x0c, 0x7e, 0x30, 0x84, 0xc3, 0x21, 0xc6, 0x00, 0x63, 0x62, 0x00, 0x46,
  0x22, 0x3c, 0x44, 0x33, 0x66, 0xcc, 0x11, 0xc3, 0x88, 0x11, 0x81, 0x88,
  0x11, 0x81, 0x88, 0x31, 0xc3, 0x88, 0x33, 0x66, 0xcc, 0x22, 0x3c, 0x44,
  0x62, 0x00, 0x46, 0xc6, 0x00, 0x63, 0x84, 0xc3, 0x21, 0x0c, 0x7e, 0x30,
  0x18, 0x00, 0x18, 0x70, 0x00, 0x0e, 0xc0, 0xc3, 0x03, 0x00, 0x7e, 0x00
};

#define circle_read1_width 24
#define circle_read1_height 24
static unsigned char circle_read1_bits[] = {
  0x00, 0x7e, 0x00, 0xc0, 0xc3, 0x03, 0x70, 0x00, 0x0e, 0x18, 0x00, 0x18,
  0x0c, 0x7e, 0x30, 0x84, 0xc3, 0x21, 0xc6, 0x00, 0x63, 0x62, 0x00, 0x46,
  0x22, 0x3c, 0x44, 0x33, 0x7e, 0xcc, 0x11, 0xff, 0x88, 0x11, 0xff, 0x88,
  0x11, 0xff, 0x88, 0x31, 0xff, 0x88, 0x33, 0x7e, 0xcc, 0x22, 0x3c, 0x44,
  0x62, 0x00, 0x46, 0xc6, 0x00, 0x63, 0x84, 0xc3, 0x21, 0x0c, 0x7e, 0x30,
  0x18, 0x00, 0x18, 0x70, 0x00, 0x0e, 0xc0, 0xc3, 0x03, 0x00, 0x7e, 0x00
};

#define circle_read2_width 24
#define circle_read2_height 24
static unsigned char circle_read2_bits[] = {
  0x00, 0x7e, 0x00, 0xc0, 0xc3, 0x03, 0x70, 0x00, 0x0e, 0x18, 0x00, 0x18,
  0x0c, 0x7e, 0x30, 0x84, 0xff, 0x21, 0xc6, 0xff, 0x63, 0xe2, 0xff, 0x47,
  0xe2, 0xc3, 0x47, 0xf3, 0x81, 0xcf, 0xf1, 0x00, 0x8f, 0xf1, 0x00, 0x8f,
  0xf1, 0x00, 0x8f, 0xf1, 0x00, 0x8f, 0xf3, 0x81, 0xcf, 0xe2, 0xc3, 0x47,
  0xe2, 0xff, 0x47, 0xc6, 0xff, 0x63, 0x84, 0xff, 0x21, 0x0c, 0x7e, 0x30,
  0x18, 0x00, 0x18, 0x70, 0x00, 0x0e, 0xc0, 0xc3, 0x03, 0x00, 0x7e, 0x00
};

#define circle_read3_width 24
#define circle_read3_height 24
static unsigned char circle_read3_bits[] = {
  0x00, 0x7e, 0x00, 0xc0, 0xff, 0x03, 0xf0, 0xff, 0x0f, 0xf8, 0xff, 0x1f,
  0xfc, 0x81, 0x3f, 0x7c, 0x00, 0x3e, 0x3e, 0x00, 0x7c, 0x1e, 0x00, 0x78,
  0x1e, 0x3c, 0x78, 0x0f, 0x66, 0xf0, 0x0f, 0xc3, 0xf0, 0x0f, 0x81, 0xf0,
  0x0f, 0x81, 0xf0, 0x0f, 0xc3, 0xf0, 0x1f, 0x66, 0xf0, 0x1e, 0x3c, 0x78,
  0x1e, 0x00, 0x78, 0x3e, 0x00, 0x78, 0x7c, 0x00, 0x3e, 0xfc, 0x81, 0x3f,
  0xf8, 0xff, 0x1f, 0xf0, 0xff, 0x0f, 0xc0, 0xff, 0x03, 0x00, 0x7e, 0x00
};

#define data_reading_width    24
#define data_reading_height   24
static unsigned char *data_reading_bits[][4] = {
  {circle_frame_bits}, {circle_read1_bits}, {circle_read2_bits}, {circle_read3_bits}
};


