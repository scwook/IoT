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

const uint8_t Bat816[16] = {
  0x0F, 0xFE, 0x30, 0x02, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x30, 0x02, 0x0F, 0xFE
};
