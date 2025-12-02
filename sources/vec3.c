#include "minirt.h"

/* init */
t_vec3 t_vec3_new(double e0, double e1, double e2)
{
    t_vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

/* init to 0 */
t_vec3 vec3_zero(void)
{
    return t_vec3_new(0.0, 0.0, 0.0);
}

/* add by a fix value */
void vec3_add_inplace(t_vec3 *a, double t)
{
    a->e[0] += t;
    a->e[1] += t;
    a->e[2] += t;
}

/* subtract by a fix value */
void vec3_sub_inplace(t_vec3 *a, double t)
{
	vec3_add(a, -t);
}

/* multiply by a fix value */
void vec3_mul_inplace(t_vec3 *a, double t)
{
    a->e[0] *= t;
    a->e[1] *= t;
    a->e[2] *= t;
}

/* divide by a fix value */
void vec3_div_inplace(t_vec3 *a, double t)
{
	vec3_mul(a, 1.0/t);
}

/* printing */
void vec3_print(const vec3 *v) {
    printf("%f %f %f", v->e[0], v->e[1], v->e[2]);
}

/* addition */
vec3 vec3_add(const vec3 *u, const vec3 *v) {
    vec3 r = { u->e[0] + v->e[0],
               u->e[1] + v->e[1],
               u->e[2] + v->e[2] };
    return r;
}

/* subtraction */
vec3 vec3_sub(const vec3 *u, const vec3 *v) {
    vec3 r = { u->e[0] - v->e[0],
               u->e[1] - v->e[1],
               u->e[2] - v->e[2] };
    return r;
}

/* component‑wise multiplication */
vec3 vec3_mul(const vec3 *u, const vec3 *v) {
    vec3 r = { u->e[0] * v->e[0],
               u->e[1] * v->e[1],
               u->e[2] * v->e[2] };
    return r;
}

/* scalar multiplication */
vec3 vec3_scale(double t, const vec3 *v) {
    vec3 r = { t * v->e[0],
               t * v->e[1],
               t * v->e[2] };
    return r;
}

/* scalar division */
vec3 vec3_div(const vec3 *v, double t) {
    return vec3_scale(1.0/t, v);
}

/* dot product */
double vec3_dot(const vec3 *u, const vec3 *v) {
    return u->e[0]*v->e[0] + u->e[1]*v->e[1] + u->e[2]*v->e[2];
}

/* cross product */
vec3 vec3_cross(const vec3 *u, const vec3 *v) {
    vec3 r = { u->e[1]*v->e[2] - u->e[2]*v->e[1],
               u->e[2]*v->e[0] - u->e[0]*v->e[2],
               u->e[0]*v->e[1] - u->e[1]*v->e[0] };
    return r;
}

/* length */
double vec3_length(const vec3 *v) {
    return sqrt(v->e[0]*v->e[0] + v->e[1]*v->e[1] + v->e[2]*v->e[2]);
}

/* unit vector */
vec3 vec3_unit(const vec3 *v) {
    return vec3_div(v, vec3_length(v));
}
