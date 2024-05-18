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

#ifndef MATRIX_COLS
#    define MATRIX_COLS 22
#endif

#ifndef MATRIX_ROWS
#    define MATRIX_ROWS 7
#endif

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];
matrix_row_t        better_matrix[MATRIX_COLS];

static matrix_row_t read_rows(void);
static void         select_col(uint8_t row);

static uint8_t pca9555_reset_loop = 0;

void matrix_init_user(void) {
    // matrix[15] = 0;
    //  initialize row and col
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        // uprintf("filling: %d\n", i);
        // wait_ms(50);
        better_matrix[i] = 0;
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        // uprintf("filling: %d\n", i);
        // wait_ms(50);
        raw_matrix[i] = 0;
    }
    // wait_ms(50);
    // uprintf("cols: %d  rows: %d\n", MATRIX_COLS, MATRIX_ROWS);
    // wait_ms(50);
    // pca9555_status = init_pca9555();
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
    // print("in matrix comparing\n");
    // wait_ms(50);
    matrix_row_t temp = read_rows();
    // uprintf("matrix length: %d\n", sizeof(matrix)/sizeof(matrix[0]));
    // wait_ms(50);
    //  if (raw_matrix[index] != temp) {
    //      raw_matrix[index] = temp;
    //      return true;
    //  }
    if (better_matrix[index] != temp) {
        // uprintf("insert anmial here; index: %d; temp: %ld\n", index, temp);
        // wait_ms(50);
        better_matrix[index] = temp;
        for (int i = 0; i < MATRIX_ROWS; i++) {
            raw_matrix[i] &= ~(1 << index);
            raw_matrix[i] |= (temp & (1 << i)) ? (1 << index) : 0;
        }
        //print("insert anmial2 here\n");
        //wait_ms(50);
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // wait_ms(50);
    // print("starting scan\n");
    // wait_ms(50);
    if (pca9555_status) { // if there was an error
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

    // wait_ms(50);
    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        uint8_t col_index = i;
        select_col(col_index);
        // print("reading the matrix\n");
        // wait_ms(50);
        changed |= store_raw_matrix_row(col_index);
        // wait_ms(50);
    }
    // uprintf("changed: %d\n", changed);
    // wait_ms(50);
    // changed = true;
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
    //  print("scan done\n");
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
    // print("reading rows........\n");
    if (pca9555_status) { // if there was an error
        return 0;
    } else {
        uint8_t data   = 0;
        pca9555_status = i2c_readReg(I2C1_ADDR, INPUTB, &data, 1, PCA_I2C_TIMEOUT);
        if (pca9555_status < 0) goto out;
        // uprintf("Row says: %X\n", data);
        // wait_ms(500);
    out:
        i2c_stop();
        return data;
    }
}

static void select_col(uint8_t col) {
    uint8_t zero = 0x00;
    // uint8_t temp_data = 0xFF;
    // pca9555_status = i2c_writeReg(I2C1_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT);
    // pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTB, &temp_data, 1, PCA_I2C_TIMEOUT);
    // pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT);
    // select on pca9555
    if (!pca9555_status) {
        // uprintf("col %d\n", col);
        // wait_ms(50);
        if (col < 8) {
            // pca9555_status = i2c_start(I2C1_ADDR_WRITE);        if (pca9555_status) goto out;
            //  print("b\n");
            //  wait_ms(50);
            uint8_t temp_data = 0x00 | (1 << (7 - col));
            // print("c\n");
            // wait_ms(50);
            pca9555_status = i2c_writeReg(I2C1_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT);            if (pca9555_status) goto out;
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTB, &zero, 1, PCA_I2C_TIMEOUT);
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTA, &zero, 1, PCA_I2C_TIMEOUT);
            // print("d\n");
            // wait_ms(50);
        } else if (col >= 8 && col < 16) {
            // pca9555_status = i2c_start(I2C0_ADDR_WRITE);        if (pca9555_status) goto out;
            //  print("b\n");
            //  wait_ms(50);
            uint8_t temp_data = 0x00 | (1 << (col - 8));
            // print("c\n");
            // wait_ms(50);
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTB, &temp_data, 1, PCA_I2C_TIMEOUT);            if (pca9555_status) goto out;
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTA, &zero, 1, PCA_I2C_TIMEOUT);
            pca9555_status = i2c_writeReg(I2C1_ADDR, OUTPUTA, &zero, 1, PCA_I2C_TIMEOUT);
            // print("d\n");
            // wait_ms(50);
        } else if (col >= 16) {
            // pca9555_status = i2c_start(I2C0_ADDR_WRITE);        if (pca9555_status) goto out;
            //  print("b\n");
            //  wait_ms(50);
            uint8_t temp_data = 0x00 | (1 << (7 - (col - 16)));
            // print("c\n");
            // wait_ms(50);
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTA, &temp_data, 1, PCA_I2C_TIMEOUT);            if (pca9555_status) goto out;
            pca9555_status = i2c_writeReg(I2C0_ADDR, OUTPUTB, &zero, 1, PCA_I2C_TIMEOUT);
            pca9555_status = i2c_writeReg(I2C1_ADDR, OUTPUTA, &zero, 1, PCA_I2C_TIMEOUT);
            // print("d\n");
            // wait_ms(50);
        }

    out:
        // if (pca9555_status) uprintf("Status1: %d\n",pca9555_status);
        //  print("e\n");
        //  wait_ms(50);
        i2c_stop();
        // print("f\n");
        // wait_ms(50);
    } else {
        uprintf("Status2: %d\n", pca9555_status);
    }
    // print("g\n");
    // wait_ms(50);
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    pca9555_status = init_pca9555();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

// void matrix_transpose(matrix_row_t matrix[]) {
//     int swap_width = sizeof(matrix_row_t)*8;
//     matrix_row_t swap_mask = ((matrix_row_t)(-1));
//     while (swap_width != 1) {
//         swap_width >>= 1;
//         swap_mask = swap_mask ^ (swap_mask >> swap_width);
//         matrix_swap(matrix, swap_width, swap_mask);
//     }
// }

// // Swap blocks within the bit matrix.
// void matrix_swap(matrix_row_t matrix[], int width, matrix_row_t mask) {
//     int inner, outer;
//     for (outer = 0; outer < (sizeof(matrix_row_t)*8)/(width*2); outer++) {
//         for (inner = 0; inner < width; inner++) {
//             matrix_row_t* x = &matrix[(inner) + (outer*width*2)];
//             matrix_row_t* y = &matrix[(inner+width) + (outer*width*2)];

//             *x = ((*y << width) & mask) ^ *x;
//             *y = ((*x & mask) >> width) ^ *y;
//             *x = ((*y << width) & mask) ^ *x;
//         }
//     }
// }