#include "colossus_of_codes.h"

bool         i2c_initialized = 0;
i2c_status_t pca9555_status = 0x20; // using the same status for both since if one isn't working, odds are the other isn't as well

void matrix_init_kb(void) {
    
    matrix_init_user();
}

uint8_t init_pca9555(void) {
    pca9555_status = 0x20;

    // I2C subsystem

    if (i2c_initialized == 0) {
        i2c_init();  // on pins GP6&7
        i2c_initialized = true;
        _delay_ms(1000);
    }
    // set pin direction - cols are outputs, rows are inputs
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    pca9555_status = i2c_start(I2C0_ADDR_WRITE, PCA_I2C_TIMEOUT); // I2C0
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(IODIRA, PCA_I2C_TIMEOUT);
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(0b00000000, PCA_I2C_TIMEOUT);
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(0b11111111, PCA_I2C_TIMEOUT); // next 8 bits written will automatically go to next register, so we don't need to define the register if they are neighbors
    if (pca9555_status) goto out;
    i2c_stop;
	
	pca9555_status = i2c_start(I2C1_ADDR_WRITE, PCA_I2C_TIMEOUT); // I2C1
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(IODIRA, PCA_I2C_TIMEOUT);
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(0b00000011, PCA_I2C_TIMEOUT);
    if (pca9555_status) goto out;
    pca9555_status = i2c_write(0b00000000, PCA_I2C_TIMEOUT); // next 8 bits written will automatically go to next register, so we don't need to define the register if they are neighbors
    if (pca9555_status) goto out;
    i2c_stop();

out:
    i2c_stop();

    return pca9555_status;
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}