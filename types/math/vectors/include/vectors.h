#ifndef VECTORS_H
#define VECTORS_H

#define EPSILON 0.001

#include "custom_math.h"
#include <stdint.h>
#include <math.h>

// Type definitions
// 32-bit float vectors
typedef union {
    struct { float x, y; };
    float v[2]; // Allows indexing like v[0], v[1] and readability with v.x/v.y
} vec2f; // 8 bytes

typedef union
{
    struct { float x, y, z; };
    float v[3]; // Allows indexing like v[0], v[1], v[2] and readability with v.x/v.y/v.z
} vec3f; // 12 bytes

// 16-bit integer vectors
typedef union {
    struct { int16_t x, y; };
    int16_t v[2]; // Allows indexing like v[0], v[1] and readability with v.x/v.y
} vec2s; // 4 bytes

typedef union
{
    struct { int16_t x, y, z; };
    int16_t v[3]; // Allows indexing like v[0], v[1], v[2] and readability with v.x/v.y/v.z
} vec3s; // 6 bytes

#pragma region vec2f_fn_def
// General vec2 values
static inline vec2f vec2f_zero() { return (vec2f){0, 0}; }
static inline vec2f vec2f_one() { return (vec2f){1, 1}; }

/** Returns the reverse of a vec2. */
static inline vec2f vec2f_reverse(const vec2f u) { return (vec2f){-u.x, -u.y}; }

// X-axis
static inline vec2f vec2f_right() { return (vec2f){1, 0}; }
static inline vec2f vec2f_left() { return vec2f_reverse(vec2f_right()); }

// Y-axis
static inline vec2f vec2f_up() { return (vec2f){0, 1}; }
static inline vec2f vec2f_down() { return vec2f_reverse(vec2f_up()); }

/** Adds two vec2s together and returns the result. */
static inline vec2f vec2f_add(const vec2f u, const vec2f v) { return (vec2f){u.x + v.x, u.y + v.y}; }

/** Multiplies a vec2 with a constant and returns the result. */
static inline vec2f vec2f_scale(const vec2f u, const float k) { return (vec2f){u.x * k, u.y * k}; }

/** Checks whether a vec2 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec2f_equals(const vec2f u, const vec2f v, const float epsilon) {
    return f32_abs(u.x - v.x) < epsilon && f32_abs(u.y - v.y) < epsilon;
}

/** 
 * Computes the squared magnitude of a vec2 and returns the result. 
 * (|u| = a² + b²)
 */
static inline float vec2f_magnitude_squared(const vec2f u) { return u.x * u.x + u.y * u.y; }

/** 
 * Computes the dot product between two vec2s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1..N}, where N is the vector size) 
 */
static inline float vec2f_dot_product(const vec2f u, const vec2f v) { return u.x * v.x + u.y * v.y; }

/** Normalizes a vec2 to a unit vector of length 1. */
static inline vec2f vec2f_normalize(const vec2f u) {
    float mag_sqr = vec2f_magnitude_squared(u);
    if (mag_sqr == 0.0f) return vec2f_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1.0f / sqrtf(mag_sqr); 
    return (vec2f){ u.x * inv_mag, u.y * inv_mag };
}

/** Casts a vec2 to a vec3. Z component is set to 0. */
static inline vec3f vec2f_to_vec3f(const vec2f u) { return (vec3f){u.x, u.y, 0}; }
#pragma endregion

#pragma region vec3f_fn_def
// General vec3 values
static inline vec3f vec3f_zero() { return (vec3f){0, 0, 0}; }
static inline vec3f vec3f_one() { return (vec3f){1, 1, 1}; }

/** Returns the reverse of a vec3. */
static inline vec3f vec3f_reverse(const vec3f u) { return (vec3f){-u.x, -u.y, -u.z}; }

// X-axis
static inline vec3f vec3f_right() { return (vec3f){1, 0, 0}; }
static inline vec3f vec3f_left() { return vec3f_reverse(vec3f_right()); }

// Y-axis
static inline vec3f vec3f_up() { return (vec3f){0, 1, 0}; }
static inline vec3f vec3f_down() { return vec3f_reverse(vec3f_up()); }

// Z-axis
static inline vec3f vec3f_forward() { return (vec3f){0, 0, 1}; }
static inline vec3f vec3f_back() { return vec3f_reverse(vec3f_forward()); }

/** Adds two vec3s together and returns the result. */
static inline vec3f vec3f_add(const vec3f u, const vec3f v) { return (vec3f){u.x + v.x, u.y + v.y, u.z + v.z}; }

/** Multiplies a vec3 with a constant and returns the result. */
static inline vec3f vec3f_scale(const vec3f u, const float k) { return (vec3f){u.x * k, u.y * k, u.z * k}; }

/** Checks whether a vec3 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec3f_equals(const vec3f u, const vec3f v, const float epsilon) {
    return f32_abs(u.x - v.x) < epsilon &&
           f32_abs(u.y - v.y) < epsilon &&
           f32_abs(u.z - v.z) < epsilon;
}

/** 
 * Computes the squared magnitude of a vec3 and returns the result. 
 * (|u|² = a² + b²)
 */
static inline float vec3f_magnitude_squared(const vec3f u) { return u.x * u.x + u.y * u.y + u.z * u.z; }

/** Produces a vec3 perpendicular to two vec3s. */
static inline vec3f vec3f_cross_product(const vec3f u, const vec3f v) {
    return (vec3f){
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x 
    };
}

/** 
 * Computes the dot product between two vec3s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1..N}, where N is the vector size) 
 */
static inline float vec3f_dot_product(const vec3f u, const vec3f v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

/** Normalizes a vec3 to a unit vector of length 1. */
static inline vec3f vec3f_normalize(const vec3f u) {
    float mag_sqr = vec3f_magnitude_squared(u);
    if (mag_sqr == 0.0f) return vec3f_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1.0f / sqrtf(mag_sqr);
    return (vec3f){ u.x * inv_mag, u.y * inv_mag, u.z * inv_mag };
}

/** Casts a vec3 to a vec2. Z component is stripped. */
static inline vec2f vec3f_to_vec2f(const vec3f u) { return (vec2f){u.x, u.y}; }
#pragma endregion

#pragma region vec2s_fn_def
// General vec2 values
static inline vec2s vec2s_zero() { return (vec2s){0, 0}; }
static inline vec2s vec2s_one() { return (vec2s){1, 1}; }

/** Returns the reverse of a vec2. */
static inline vec2s vec2s_reverse(const vec2s u) { return (vec2s){-u.x, -u.y}; }

// X-axis
static inline vec2s vec2s_right() { return (vec2s){1, 0}; }
static inline vec2s vec2s_left() { return vec2s_reverse(vec2s_right()); }

// Y-axis
static inline vec2s vec2s_up() { return (vec2s){0, 1}; }
static inline vec2s vec2s_down() { return vec2s_reverse(vec2s_up()); }

/** Adds two vec2s together and returns the result. */
static inline vec2s vec2s_add(const vec2s u, const vec2s v) { return (vec2s){u.x + v.x, u.y + v.y}; }

/** Multiplies a vec2 with a constant and returns the result. */
static inline vec2s vec2s_scale(const vec2s u, const int16_t k) { return (vec2s){u.x * k, u.y * k}; }

/** Checks whether a vec2 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec2s_equals(const vec2s u, const vec2s v) {
    return u.x == v.x && u.y == v.y;
}

/** 
 * Computes the squared magnitude of a vec2 and returns the result. 
 * (|u| = a² + b²)
 */
static inline float vec2s_magnitude_squared(const vec2s u) { return u.x * u.x + u.y * u.y; }

/** 
 * Computes the dot product between two vec2s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1..N}, where N is the vector size) 
 */
static inline float vec2s_dot_product(const vec2s u, const vec2s v) { return u.x * v.x + u.y * v.y; }

/** Normalizes a vec2 to a unit vector of length 1. */
static inline vec2s vec2s_normalize(const vec2s u) {
    float mag_sqr = vec2s_magnitude_squared(u);
    if (mag_sqr == 0) return vec2s_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1 / sqrtf(mag_sqr); 
    return (vec2s){ u.x * inv_mag, u.y * inv_mag };
}

/** Casts a vec2 to a vec3. Z component is set to 0. */
static inline vec3f vec2s_to_vec3f(const vec2s u) { return (vec3f){u.x, u.y, 0}; }
#pragma endregion

#pragma region vec3s_fn_def
// General vec3 values
static inline vec3s vec3s_zero() { return (vec3s){0, 0, 0}; }
static inline vec3s vec3s_one() { return (vec3s){1, 1, 1}; }

/** Returns the reverse of a vec3. */
static inline vec3s vec3s_reverse(const vec3s u) { return (vec3s){-u.x, -u.y, -u.z}; }

// X-axis
static inline vec3s vec3s_right() { return (vec3s){1, 0, 0}; }
static inline vec3s vec3s_left() { return vec3s_reverse(vec3s_right()); }

// Y-axis
static inline vec3s vec3s_up() { return (vec3s){0, 1, 0}; }
static inline vec3s vec3s_down() { return vec3s_reverse(vec3s_up()); }

// Z-axis
static inline vec3s vec3s_forward() { return (vec3s){0, 0, 1}; }
static inline vec3s vec3s_back() { return vec3s_reverse(vec3s_forward()); }

/** Adds two vec3s together and returns the result. */
static inline vec3s vec3s_add(const vec3s u, const vec3s v) { return (vec3s){u.x + v.x, u.y + v.y, u.z + v.z}; }

/** Multiplies a vec3 with a constant and returns the result. */
static inline vec3s vec3s_scale(const vec3s u, const int16_t k) { return (vec3s){u.x * k, u.y * k, u.z * k}; }

/** Checks whether a vec3 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec3s_equals(const vec3s u, const vec3s v) {
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

/** 
 * Computes the squared magnitude of a vec3 and returns the result. 
 * (|u|² = a² + b²)
 */
static inline float vec3s_magnitude_squared(const vec3s u) { return u.x * u.x + u.y * u.y + u.z * u.z; }

/** Produces a vec3 perpendicular to two vec3s. */
static inline vec3s vec3s_cross_product(const vec3s u, const vec3s v) {
    return (vec3s){
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x 
    };
}

/** 
 * Computes the dot product between two vec3s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1..N}, where N is the vector size) 
 */
static inline float vec3s_dot_product(const vec3s u, const vec3s v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

/** Normalizes a vec3 to a unit vector of length 1. */
static inline vec3s vec3s_normalize(const vec3s u) {
    float mag_sqr = vec3s_magnitude_squared(u);
    if (mag_sqr == 0) return vec3s_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1 / sqrtf(mag_sqr);
    return (vec3s){ u.x * inv_mag, u.y * inv_mag, u.z * inv_mag };
}

/** Casts a vec3 to a vec2. Z component is stripped. */
static inline vec2s vec3s_to_vec2s(const vec3s u) { return (vec2s){u.x, u.y}; }
#pragma endregion

#endif // VECTORS_H
