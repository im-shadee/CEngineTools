#ifndef VECTORS_H
#define VECTORS_H

// Type definitions
typedef struct {
    float x, y;
} vec2; // 8 bytes

typedef struct
{
    float x, y, z;
} vec3; // 12 bytes

typedef struct
{
    float x, y, z, w;
} vec4; // 16 bytes

#pragma region vec2_fn_def
// General vec2 values
static inline vec2 vec2_zero() { return {0, 0}; }
static inline vec2 vec2_one() { return {1, 1}; }

// X-axis
static inline vec2 vec2_right() { return {1, 0}; }
static inline vec2 vec2_left() { return vec2_reverse(vec2_right()); }

// Y-axis
static inline vec2 vec2_up() { return {0, 1}; }
static inline vec2 vec2_down() { return vec2_reverse(vec2_up()); }

/** Adds two vec2s together and returns the result. */
static inline vec2 vec2_add(const vec2 u, const vec2 v) { return {u.x + v.x, u.y + v.y}; }

/** Returns the reverse of a vec2. */
static inline vec2 vec2_reverse(const vec2 u) { return {-u.x, -u.y}; }

/** Multiplies a vec2 with a constant and returns the result. */
static inline vec2 vec2_scale(const vec2 u, float k) { return {u.x * k, u.y * k}; }

/** 
 * Computes the squared magnitude of a vec2 and returns the result. 
 * (|u| = a² + b²)
 */
float vec2_magnitude_squared(const vec2 u) { return u.x * u.x + u.y * u.y; }

/** 
 * Computes the dot product between two vec2s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1...N}, where N is the vector size) 
 * 
 * remarks: If u == v, the result is simply |u|²
 */
float vec2_dot_product(const vec2 u, const vec2 v);

/** 
 * Computes and returns the unit vector (vector of length 1) of a specified vec2. 
 * (û = u / |u| = sum(u_i) / |u|, with i in {1...N}, where N is the vector size)
 */
vec2 vec2_normalize(const vec2 u);

/** Casts a vec2 to a vec3. Z component is set to 0. */
static inline vec3 vec2_to_vec3(const vec2 u) { return {u.x, u.y, 0}; }

/** Casts a vec2 to a vec4. Z/W components are set to 0. */
static inline vec4 vec2_to_vec4(const vec2 u) { return {u.x, u.y, 0, 0}; }
#pragma endregion

#pragma region vec3_fn_def
// General vec3 values
static inline vec3 vec3_zero() { return {0, 0, 0}; }
static inline vec3 vec3_one() { return {1, 1, 1}; }

// X-axis
static inline vec3 vec3_right() { return {1, 0, 0}; }
static inline vec3 vec3_left() { return vec3_reverse(vec3_right()); }

// Y-axis
static inline vec3 vec3_up() { return {0, 1, 0}; }
static inline vec3 vec3_down() { return vec3_reverse(vec3_up()); }

// Z-axis
static inline vec3 vec3_forward() { return {0, 0, 1}; }
static inline vec3 vec3_back() { return vec3_reverse(vec3_forward()); }

/** Adds two vec3s together and returns the result. */
static inline vec3 vec3_add(const vec3 u, const vec3 v) { return {u.x + v.x, u.y + v.y, u.z + v.z}; }

/** Returns the reverse of a vec3. */
static inline vec3 vec3_reverse(const vec3 u) { return {-u.x, -u.y, -u.z}; }

/** Multiplies a vec3 with a constant and returns the result. */
static inline vec3 vec3_scale(const vec3 u, float k) { return {u.x * k + u.y * k + u.z * k}; }

/** 
 * Computes the squared magnitude of a vec3 and returns the result. 
 * (|u| = a² + b²)
 */
static inline float vec3_magnitude_squared(const vec3 u) { return u.x * u.x + u.y * u.y + u.z * u.z; }

/** Produces a vec3 perpendicular to two vec3s. */
static inline vec3 vec3_cross_product(const vec3 u, const vec3 v) {
    return {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x 
    };
}

/** 
 * Computes the dot product between two vec3s and returns the result.
 * (u·v = sum(a_i * b_i), with i in {1...N}, where N is the vector size) 
 * 
 * remarks: If u == v, the result is simply |u|²
 */
float vec3_dot_product(const vec3 u, const vec3 v);

/** 
 * Computes and returns the unit vector (vector of length 1) of a specified vec3. 
 * (û = u / |u| = sum(u_i) / |u|, with i in {1...N}, where N is the vector size)
 */
vec3 vec3_normalize(const vec3 u);
#pragma endregion

#endif // VECTORS_H
