#ifndef VECTORS_H
#define VECTORS_H

#define EPSILON 0.001
#include "custom_math.h"
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

#pragma region vec2f_fn_def
// General vec2 values
static inline vec2f vec2_zero() { return (vec2f){0, 0}; }
static inline vec2f vec2_one() { return (vec2f){1, 1}; }

/** Returns the reverse of a vec2. */
static inline vec2f vec2_reverse(const vec2f u) { return (vec2f){-u.x, -u.y}; }

// X-axis
static inline vec2f vec2_right() { return (vec2f){1, 0}; }
static inline vec2f vec2_left() { return vec2_reverse(vec2_right()); }

// Y-axis
static inline vec2f vec2_up() { return (vec2f){0, 1}; }
static inline vec2f vec2_down() { return vec2_reverse(vec2_up()); }

/** Adds two vec2s together and returns the result. */
static inline vec2f vec2_add(const vec2f u, const vec2f v) { return (vec2f){u.x + v.x, u.y + v.y}; }

/** Multiplies a vec2 with a constant and returns the result. */
static inline vec2f vec2_scale(const vec2f u, float k) { return (vec2f){u.x * k, u.y * k}; }

/** Checks whether a vec2 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec2_equals(const vec2f u, const vec2f v, float epsilon) {
    return f32_abs(u.x - v.x) < epsilon && f32_abs(u.y - v.y) < epsilon;
}

/** 
 * Computes the squared magnitude of a vec2 and returns the result. 
 * (|u| = a² + b²)
 */
static inline float vec2_magnitude_squared(const vec2f u) { return u.x * u.x + u.y * u.y; }

/** 
 * Computes the dot product between two vec2s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1..N}, where N is the vector size) 
 */
static inline float vec2_dot_product(const vec2f u, const vec2f v) { return u.x * v.x + u.y * v.y; }

/** Normalizes a vec2 to a unit vector of length 1. */
static inline vec2f vec2_normalize(const vec2f u) {
    float mag_sqr = vec2_magnitude_squared(u);
    if (mag_sqr == 0.0f) return vec2_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1.0f / sqrtf(mag_sqr); 
    return (vec2f){ u.x * inv_mag, u.y * inv_mag };
}

/** Casts a vec2 to a vec3. Z component is set to 0. */
static inline vec3f vec2_to_vec3(const vec2f u) { return (vec3f){u.x, u.y, 0}; }
#pragma endregion

#pragma region vec3f_fn_def
// General vec3 values
static inline vec3f vec3_zero() { return (vec3f){0, 0, 0}; }
static inline vec3f vec3_one() { return (vec3f){1, 1, 1}; }

/** Returns the reverse of a vec3. */
static inline vec3f vec3_reverse(const vec3f u) { return (vec3f){-u.x, -u.y, -u.z}; }

// X-axis
static inline vec3f vec3_right() { return (vec3f){1, 0, 0}; }
static inline vec3f vec3_left() { return vec3_reverse(vec3_right()); }

// Y-axis
static inline vec3f vec3_up() { return (vec3f){0, 1, 0}; }
static inline vec3f vec3_down() { return vec3_reverse(vec3_up()); }

// Z-axis
static inline vec3f vec3_forward() { return (vec3f){0, 0, 1}; }
static inline vec3f vec3_back() { return vec3_reverse(vec3_forward()); }

/** Adds two vec3s together and returns the result. */
static inline vec3f vec3_add(const vec3f u, const vec3f v) { return (vec3f){u.x + v.x, u.y + v.y, u.z + v.z}; }

/** Multiplies a vec3 with a constant and returns the result. */
static inline vec3f vec3_scale(const vec3f u, float k) { return (vec3f){u.x * k, u.y * k, u.z * k}; }

/** Checks whether a vec3 is equal to another.
 * (u_i == v_i with i in {1..N} where N is the vector size)
 * 
 * returns:
 *  - 1 if u equals v
 *  - 0 otherwise
 */
static inline int vec3_equals(const vec3f u, const vec3f v, float epsilon) {
    return f32_abs(u.x - v.x) < epsilon &&
           f32_abs(u.y - v.y) < epsilon &&
           f32_abs(u.z - v.z) < epsilon;
}

/** 
 * Computes the squared magnitude of a vec3 and returns the result. 
 * (|u|² = a² + b²)
 */
static inline float vec3_magnitude_squared(const vec3f u) { return u.x * u.x + u.y * u.y + u.z * u.z; }

/** Produces a vec3 perpendicular to two vec3s. */
static inline vec3f vec3_cross_product(const vec3f u, const vec3f v) {
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
static inline float vec3_dot_product(const vec3f u, const vec3f v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

/** Normalizes a vec3 to a unit vector of length 1. */
static inline vec3f vec3_normalize(const vec3f u) {
    float mag_sqr = vec3_magnitude_squared(u);
    if (mag_sqr == 0.0f) return vec3_zero();

    // Use square root to get real magnitude for normalization
    float inv_mag = 1.0f / sqrtf(mag_sqr);
    return (vec3f){ u.x * inv_mag, u.y * inv_mag, u.z * inv_mag };
}

/** Casts a vec3 to a vec2. Z component is stripped. */
static inline vec2f vec3_to_vec2(const vec3f u) { return (vec2f){u.x, u.y}; }
#pragma endregion



#endif // VECTORS_H
