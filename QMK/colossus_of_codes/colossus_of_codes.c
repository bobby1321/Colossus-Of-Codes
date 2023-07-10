#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "colossus_of_codes.h"

bool         i2c_initialized = 0;
i2c_status_t pca9555_status = 0x0; // using the same status for both since if one isn't working, odds are the other isn't as well

void matrix_init_kb(void) {
    print("initing please work\n");
    pca9555_status = init_pca9555();
    matrix_init_user();
}

i2c_status_t init_pca9555(void) {
    pca9555_status = 0x0;
    
    // I2C subsystem

    if (i2c_initialized == 0) {
        i2c_init();  // on pins GP6&7
        i2c_initialized = true;
        wait_ms(1000);
    }

    print("initing i/o expanders\n");
    // set pin direction - cols are outputs, rows are inputs
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    pca9555_status = i2c_start(I2C1_ADDR); // I2C1

    uint8_t temp_data = 0b00000000;
    pca9555_status = i2c_writeReg(I2C1_ADDR, IODIRA, &temp_data, 1, PCA_I2C_TIMEOUT);
    if (pca9555_status) {
        print("111111111111\n");
        goto out;
    } 
    temp_data = 0b11111111;
    pca9555_status = i2c_writeReg(I2C1_ADDR, IODIRB, &temp_data, 1, PCA_I2C_TIMEOUT);
    if (pca9555_status) {
        print("22222222222\n");
        goto out;
    } 
	
    pca9555_status = i2c_start(I2C0_ADDR); // I2C0

    temp_data = 0b00000011;
    pca9555_status = i2c_writeReg(I2C0_ADDR, IODIRA, &temp_data, 1, PCA_I2C_TIMEOUT);
    if (pca9555_status) {
        print("333333333333\n");
        goto out;
    } 
    temp_data = 0b00000000;
    pca9555_status = i2c_writeReg(I2C0_ADDR, IODIRB, &temp_data, 1, PCA_I2C_TIMEOUT);
    if (pca9555_status) {
        print("444444444444\n");
        goto out;
    } 
    i2c_stop();
    print("Init worked????\n");

out:
    i2c_stop();

    return pca9555_status;
}

void matrix_scan_kb(void) {
    print("scanning??????\n");
    matrix_scan_user();
}