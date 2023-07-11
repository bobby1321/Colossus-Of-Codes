/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "colossus_of_codes.h"

/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_COLS];      // debounced values
extern matrix_row_t raw_matrix[MATRIX_COLS];  // raw values

static matrix_row_t read_rows(void);
static void         select_col(uint8_t row);

static uint8_t pca9555_reset_loop = 0;

void matrix_init_custom(void) {
    // initialize row and col

    pca9555_status = init_pca9555();
}


// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_col(uint8_t index) {
	print("in matrix comparing\n");
    matrix_row_t temp = 0x3F & read_rows();
	print("a\n");
    if (raw_matrix[index] != temp) {
        raw_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
	wait_ms(50);
	print("starting scan\n");
	wait_ms(50);
    if (pca9555_status) {  // if there was an error
        if (++pca9555_reset_loop == 0) {
            print("trying to reset pca9555\n");
			wait_ms(50);
            pca9555_status = init_pca9555();
            if (pca9555_status) {
                print("expanders not responding\n");
				wait_ms(50);
            } else {
                print("expanders responding\n");
				wait_ms(50);
            }
        }
    }
	
	wait_ms(50);
    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        uint8_t col_index  = i;
        select_col(col_index);
		print("reading the matrix\n");
        changed |= store_raw_matrix_col(col_index);
		wait_ms(50);
    }
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
	print("scan done\n");
    return changed;
}

/* Column pin configuration
 *
 * Expander 1 (U3)
 * col:  H  G  F  E  D  C  B  A
 * pin:  A0 A1 A2 A3 A4 A5 A6 A7
 *
 * Expander 0 (U2)
 * col:  Y  X  T  S  R  >  J  K  L  M  N  P  Q  <
 * pin:  A2 A3 A4 A5 A6 A7 B0 B1 B2 B3 B4 B5 B6 B7
 *
 */

static matrix_row_t read_rows() {
    print("reading rows........\n");
	if (pca9555_status) {  // if there was an error
		return 0;
	} else {
		uint8_t data = 0;
		//pca9555_status = i2c_start(I2C0_ADDR_READ);    if (pca9555_status) goto out;
		pca9555_status = i2c_readReg(I2C1_ADDR, INPUTB, &data, 1, PCA_I2C_TIMEOUT);               	if (pca9555_status < 0) goto out;
	out:
		i2c_stop();
		return data;
	}
}

static void select_col(uint8_t col) {

	// select on pca9555
	if (!pca9555_status) {
		uprintf("col %d\n", col);
		wait_ms(50);
		if (col < 8) {
			//pca9555_status = i2c_start(I2C1_ADDR_WRITE);        if (pca9555_status) goto out;
			print("b\n");
			wait_ms(50);
			uint8_t temp_data = 0x00 & (1 << (7-col));
			print("c\n");
			wait_ms(50);
    		pca9555_status = i2c_writeReg(I2C1_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT); if (pca9555_status) goto out;
			print("d\n");
			wait_ms(50);
		} else if (col >=8 && col < 16) {
			//pca9555_status = i2c_start(I2C0_ADDR_WRITE);        if (pca9555_status) goto out;
			print("b\n");
			wait_ms(50);
			uint8_t temp_data = 0x00 & (1 << (col));
			print("c\n");
			wait_ms(50);
    		pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTB, &temp_data, 1, PCA_I2C_TIMEOUT); if (pca9555_status) goto out;
			print("d\n");
			wait_ms(50);
		} else if (col >= 16) { 
			//pca9555_status = i2c_start(I2C0_ADDR_WRITE);        if (pca9555_status) goto out;
			print("b\n");
			wait_ms(50);
			uint8_t temp_data = 0x00 & (1 << (7-(col-16)));
			print("c\n");
			wait_ms(50);
    		pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT); if (pca9555_status) goto out;
			print("d\n");
			wait_ms(50);
		}
		
			
	out:
		if (pca9555_status) uprintf("Status1: %d\n",pca9555_status);
		print("e\n");
		wait_ms(50);
		i2c_stop();
		print("f\n");
		wait_ms(50);
	} else {
		uprintf("Status2: %d\n",pca9555_status);
	}
	print("g\n");
	wait_ms(50);
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    pca9555_status = init_pca9555();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }

}