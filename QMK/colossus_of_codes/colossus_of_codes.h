#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

// I2C aliases and register addresses for PCA9555
#define I2C0_ADDR        0b01000010 // schematic U2 = I2C0 (it just needs that extra 0 on the end)
#define I2C1_ADDR        0b01000100 // schematic U3 = I2C1
#define IODIRA          0x06            // i/o direction register
#define IODIRB          0x07
#define OUTPUTA         0x02            // register to set the value of output pins
#define OUTPUTB         0x03
#define INPUTA			0x00			// read only registers to read incoming values
#define INPUTB			0x01
#define INVERTA			0x04			// set pins as inverted logic (for inputs)
#define INVERTB			0x05

extern i2c_status_t pca9555_status;
#define PCA_I2C_TIMEOUT 100u

i2c_status_t init_pca9555(void);

