#ifndef MATRICES_H
#define MATRICES_H

#include "custom_int.h"
#include <stdlib.h>
#include <string.h>

/** 32-bit float 4x4 matrix for CPU math and physics */
typedef union {
    float m_flat[16]; // Flat array for hardware / DMA / OpenGL-style passing
    float m[4][4]; // 2D array for readable index-based math (row/col)
} mat4f; // 64 bytes

/** Signed 16.16 fixed-point 4x4 matrix for N64 hardware / RSP pipelines */
typedef union {
    int16_16 m_flat[16];
    int16_16 m[4][4];
} mat4; // 64 bytes

/** 
 * Creates a 4x4 matrix and initializes its contents.
 * Returns a pointer to the created matrix, or NULL if any allocation failed.
 */
mat4f* mat4f_create();

/** Multiplies a matrix with another and puts the result into a destination matrix. */
void mat4f_multiply(mat4f* dest, const mat4f* a, const mat4f* b);

/** Turns an existing matrix into the identity matrix. */
static inline void mat4f_identity(mat4f* mtx) {
    if (!mtx) return;

    #pragma GCC unroll 4
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mtx->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

/** Scales a matrix by a constant factor k. */
static inline void mat4f_scale(mat4f* mtx, const float k) {
    if (!mtx) return;

    #pragma GCC unroll 4
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mtx->m[i][j] *= k;
        }
    }
}

/** Sets each of a matrix slots to 0. */
static inline void mat4f_clear(mat4f* mtx) { memset(mtx, 0, sizeof(*mtx)); }

//#ifdef MTX_IMPL
mat4f* mat4f_create() {
    mat4f* mtx = malloc(sizeof(*mtx)); // Allocate space for matrix struct
    if (!mtx) return NULL;

    mat4f_clear(mtx); // Initialize all slots to 0
    return mtx;
}

void mat4f_multiply(mat4f* dest, const mat4f* a, const mat4f* b) {
    if (!dest || !a || !b) return;

    const float b00 = b->m[0][0], b01 = b->m[0][1], b02 = b->m[0][2], b03 = b->m[0][3];
    const float b10 = b->m[1][0], b11 = b->m[1][1], b12 = b->m[1][2], b13 = b->m[1][3];
    const float b20 = b->m[2][0], b21 = b->m[2][1], b22 = b->m[2][2], b23 = b->m[2][3];
    const float b30 = b->m[3][0], b31 = b->m[3][1], b32 = b->m[3][2], b33 = b->m[3][3];

    #pragma GCC unroll 4
    for (int i = 0; i < 4; i++) {
        // 4 loads of A's row i, then 16 mul + 12 add, then 4 stores
        const float a0 = a->m[i][0], a1 = a->m[i][1], a2 = a->m[i][2], a3 = a->m[i][3];

        dest->m[i][0] = a0*b00 + a1*b10 + a2*b20 + a3*b30;
        dest->m[i][1] = a0*b01 + a1*b11 + a2*b21 + a3*b31;
        dest->m[i][2] = a0*b02 + a1*b12 + a2*b22 + a3*b32;
        dest->m[i][3] = a0*b03 + a1*b13 + a2*b23 + a3*b33;
    }
}

//#endif // MTX_IMPL

#endif // MATRICES_H
