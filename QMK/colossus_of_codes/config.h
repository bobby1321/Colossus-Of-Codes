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
#define I2C0_SDA_PIN GP6
#define I2C0_SCL_PIN GP7

#define MATRIX_ROWS 7
#define MATRIX_COLS 22

//#define DEBUG_MATRIX_SCAN_RATE


