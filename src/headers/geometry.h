#ifndef GEOMETRY2_H
#define GEOMETRY2_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define EPSYLON 0.001


#define VECTOR3D_SIZE sizeof(struct vector3d)

typedef struct vector3d {
    double v1;
    double v2;
    double v3;
} vector3d, *Vector3d;

Vector3d vector_new(double v1, double v2, double v3);
double vector_length(Vector3d vector);
double vector_dotProduct(Vector3d vector1, Vector3d vector2);
Vector3d vector_crossProduct(Vector3d vector1, Vector3d vector2);
Vector3d vector_scalarMultiplication(double scalar, Vector3d vector);
Vector3d vector_sum(Vector3d vector1, Vector3d vector2);
Vector3d vector_difference(Vector3d vector1, Vector3d vector2);
void vector_normalize(Vector3d vector);
void vector_scalarMultiply(double scalar, Vector3d vector);


#define TRIANGLE_SIZE sizeof(struct triangle)

typedef struct triangle {
    Vector3d vertex1;
    Vector3d vertex2;
    Vector3d vertex3;
} triangle, *Triangle;

Triangle triangle_new(Vector3d vertex1, Vector3d vertex2, Vector3d vertex3);
void triangle_delete(Triangle triangle);
Vector3d triangle_normal(Triangle triangle);


#define MATRIX44D_SIZE sizeof(struct matrix44d)

typedef struct matrix44d {
    double m11;
    double m12;
    double m13;
    double m14;
    double m21;
    double m22;
    double m23;
    double m24;
    double m31;
    double m32;
    double m33;
    double m34;
    double m41;
    double m42;
    double m43;
    double m44;
} matrix44d, *Matrix44d;

Matrix44d matrix_new(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44);
Matrix44d matrix_newEmpty();
Matrix44d matrix_newDiagonal(double diagonalValue);
Matrix44d matrix_newTranslate(double x, double y, double z);
Matrix44d matrix_newRotateX(double xDeg);
Matrix44d matrix_newRotateY(double yDeg);
Matrix44d matrix_newRotateZ(double zDeg);
Matrix44d matrix_compound(int count, ...);
Matrix44d matrix_multiply(Matrix44d matrix1, Matrix44d matrix2);
void matrix_multiplyVector(Vector3d vector, Matrix44d matrix);
void matrix_add(Matrix44d matrix1, Matrix44d matrix2);


#define RAY_SIZE sizeof(struct ray)

typedef struct ray {
    Vector3d origin;
    Vector3d direction;
} ray, *Ray;

Ray ray_new(Vector3d origin, Vector3d direction);
bool ray_intersect(Ray ray, Triangle triangle, double *distance);
Ray ray_cameraRay(int x, int y, double width, double height, double fov);
Ray ray_lightRay(Vector3d point, Vector3d light);

#endif
