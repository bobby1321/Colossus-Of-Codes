// Copyright 2023 bobby1321 (@bobby1321)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define MATRIX_ROWS 7
#define MATRIX_COLS 22

#define ENCODERS_PAD_A { GP3 } // these are reveresed to reverse the direction of the encoder
#define ENCODERS_PAD_B { GP4 }

#define ENCODER_RESOLUTION 2

//#define DEBUG_MATRIX_SCAN_RATE



