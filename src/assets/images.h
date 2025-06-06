#include <stdint.h>

static const uint8_t reboot_img[20] = {
    // ∙∙∙∙∙∙∙∙∙∙
    // ∙████████∙
    // ∙████████∙
    // ∙██∙∙∙∙∙∙∙
    // ∙██∙∙∙∙██∙
    // ∙██∙∙∙████
    // ∙██∙∙∙∙██∙
    // ∙████████∙
    // ∙████████∙
    // ∙∙∙∙∙∙∙∙∙∙
    0x00, 0x00, 
    0x7f, 0x80, 
    0x7f, 0x80, 
    0x60, 0x00, 
    0x61, 0x80, 
    0x63, 0xc0, 
    0x61, 0x80, 
    0x7f, 0x80, 
    0x7f, 0x80, 
    0x00, 0x00
};

static const uint8_t rotate_img[20] = {
    // ∙∙∙∙∙█∙∙∙∙
    // ∙██∙█████∙
    // ∙██∙█████∙
    // ∙██∙∙█∙██∙
    // ∙██∙∙∙∙██∙
    // ∙██∙∙∙∙██∙
    // ∙██∙█∙∙██∙
    // ∙█████∙██∙
    // ∙█████∙██∙
    // ∙∙∙∙█∙∙∙∙∙
    0x04, 0x00, 
    0x6f, 0x80, 
    0x6f, 0x80, 
    0x65, 0x80, 
    0x61, 0x80, 
    0x61, 0x80, 
    0x69, 0x80, 
    0x7d, 0x80, 
    0x7d, 0x80, 
    0x08, 0x00
};


static const uint8_t battery0_img[30] = {
    // ∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    // ∙∙∙████████████████∙
    // ∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙
    // ∙∙∙████████████████∙
    // ∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xe0, 
    0x10, 0x00, 0x20, 
    0x70, 0x00, 0x20, 
    0x70, 0x00, 0x20, 
    0x70, 0x00, 0x20, 
    0x70, 0x00, 0x20, 
    0x10, 0x00, 0x20, 
    0x1f, 0xff, 0xe0, 
    0x00, 0x00, 0x00
};

static const uint8_t battery1_img[30] = {
    // ∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    // ∙∙∙████████████████∙
    // ∙∙∙█∙∙∙∙∙∙∙∙∙██████∙
    // ∙███∙∙∙∙∙∙∙∙∙██████∙
    // ∙███∙∙∙∙∙∙∙∙∙██████∙
    // ∙███∙∙∙∙∙∙∙∙∙██████∙
    // ∙███∙∙∙∙∙∙∙∙∙██████∙
    // ∙∙∙█∙∙∙∙∙∙∙∙∙██████∙
    // ∙∙∙████████████████∙
    // ∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xe0, 
    0x10, 0x07, 0xe0, 
    0x70, 0x07, 0xe0, 
    0x70, 0x07, 0xe0, 
    0x70, 0x07, 0xe0, 
    0x70, 0x07, 0xe0, 
    0x10, 0x07, 0xe0, 
    0x1f, 0xff, 0xe0, 
    0x00, 0x00, 0x00
};

static const uint8_t bluetooth_img[20] = {
    // ∙∙∙∙██∙∙∙∙
    // ∙∙∙∙█∙█∙∙∙
    // ∙∙∙∙█∙∙█∙∙
    // ∙∙█∙█∙█∙∙∙
    // ∙∙∙███∙∙∙∙
    // ∙∙█∙█∙█∙∙∙
    // ∙∙∙∙█∙∙█∙∙
    // ∙∙∙∙█∙█∙∙∙
    // ∙∙∙∙██∙∙∙∙
    // ∙∙∙∙∙∙∙∙∙∙
    0x0c, 0x00, 
    0x0a, 0x00, 
    0x09, 0x00, 
    0x2a, 0x00, 
    0x1c, 0x00, 
    0x2a, 0x00, 
    0x09, 0x00, 
    0x0a, 0x00, 
    0x0c, 0x00, 
    0x00, 0x00
};

static const uint8_t brit_img[20] = {
    // ∙∙∙∙██∙∙∙∙
    // ∙█∙∙██∙∙█∙
    // ∙∙██∙∙██∙∙
    // ∙∙█∙██∙█∙∙
    // ██∙████∙██
    // ██∙████∙██
    // ∙∙█∙██∙█∙∙
    // ∙∙██∙∙██∙∙
    // ∙█∙∙██∙∙█∙
    // ∙∙∙∙██∙∙∙∙
    0x0c, 0x00, 
    0x4c, 0x80, 
    0x33, 0x00, 
    0x2d, 0x00, 
    0xde, 0xc0, 
    0xde, 0xc0, 
    0x2d, 0x00, 
    0x33, 0x00, 
    0x4c, 0x80, 
    0x0c, 0x00
};

static const uint8_t silent[20] = {
    // ∙∙∙∙∙∙∙∙∙∙
    // ∙█∙∙██∙∙█∙
    // ∙∙██████∙∙
    // ∙█∙∙∙∙∙∙█∙
    // █∙∙∙██∙∙∙█
    // █∙∙∙██∙∙∙█
    // ∙█∙∙∙∙∙∙█∙
    // ∙∙██████∙∙
    // ∙∙∙∙∙∙∙∙∙∙
    // ∙∙∙∙∙∙∙∙∙∙
    0x00, 0x00, 
    0x4c, 0x80, 
    0x3f, 0x00, 
    0x40, 0x80, 
    0x8c, 0x40, 
    0x8c, 0x40, 
    0x40, 0x80, 
    0x3f, 0x00, 
    0x00, 0x00, 
    0x00, 0x00
};