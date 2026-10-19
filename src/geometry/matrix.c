#include "../headers/geometry.h"
#include "../headers/utils.h"

Matrix44d matrix_new(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44) {
    Matrix44d matrix = malloc(MATRIX44D_SIZE);
    matrix->m11 = m11;
    matrix->m12 = m12;
    matrix->m13 = m13;
    matrix->m14 = m14;
    matrix->m21 = m21;
    matrix->m22 = m22;
    matrix->m23 = m23;
    matrix->m24 = m24;
    matrix->m31 = m31;
    matrix->m32 = m32;
    matrix->m33 = m33;
    matrix->m34 = m34;
    matrix->m41 = m41;
    matrix->m42 = m42;
    matrix->m43 = m43;
    matrix->m44 = m44;
    return matrix;
}

Matrix44d matrix_newEmpty() {
    return matrix_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Matrix44d matrix_newDiagonal(double diagonalValue) {
    return matrix_new(diagonalValue, 0, 0, 0, 0, diagonalValue, 0, 0, 0, 0, diagonalValue, 0, 0, 0, 0, diagonalValue);
}

Matrix44d matrix_newTranslate(double x, double y, double z) {
    Matrix44d m = matrix_newDiagonal(1);
    m->m41 = x;
    m->m42 = y;
    m->m43 = z;
    return m;
}

Matrix44d matrix_newRotateX(double xDeg) {
    Matrix44d m = matrix_newDiagonal(1);
    xDeg = xDeg * M_PI / 180;
    m->m22 = cos(xDeg);
    m->m23 = -sin(xDeg);
    m->m32 = sin(xDeg);
    m->m33 = cos(xDeg);
    return m;
}

Matrix44d matrix_newRotateY(double yDeg) {
    Matrix44d m = matrix_newDiagonal(1);
    yDeg = yDeg * M_PI / 180;
    m->m11 = cos(yDeg );
    m->m13 = sin(yDeg);
    m->m31 = -sin(yDeg);
    m->m33 = cos(yDeg);
    return m;
}

Matrix44d matrix_newRotateZ(double zDeg) {
    Matrix44d m = matrix_newDiagonal(1);
    zDeg = zDeg * M_PI / 180;
    m->m11 = cos(zDeg);
    m->m12 = -sin(zDeg);
    m->m21 = sin(zDeg);
    m->m22 = cos(zDeg);
    return m;
}

void matrix_multiplyVector(Vector3d vector, Matrix44d matrix) {
    double v1 = vector->v1 * matrix->m11 + vector->v2 * matrix->m21 + vector->v3 * matrix->m31 + 1 * matrix->m41;
    double v2 = vector->v1 * matrix->m12 + vector->v2 * matrix->m22 + vector->v3 * matrix->m32 + 1 * matrix->m42;
    double v3 = vector->v1 * matrix->m13 + vector->v2 * matrix->m23 + vector->v3 * matrix->m33 + 1 * matrix->m43;
    vector->v1 = v1;
    vector->v2 = v2;
    vector->v3 = v3;
}

Matrix44d matrix_multiply(Matrix44d matrix1, Matrix44d matrix2) {
    Matrix44d m = matrix_newEmpty();
    m->m11 = matrix1->m11 * matrix2->m11 + matrix1->m12 * matrix2->m21 + matrix1->m13 * matrix2->m31 + matrix1->m14 * matrix2->m41;
    m->m12 = matrix1->m11 * matrix2->m12 + matrix1->m12 * matrix2->m22 + matrix1->m13 * matrix2->m32 + matrix1->m14 * matrix2->m42;
    m->m13 = matrix1->m11 * matrix2->m13 + matrix1->m12 * matrix2->m23 + matrix1->m13 * matrix2->m33 + matrix1->m14 * matrix2->m43;
    m->m14 = matrix1->m11 * matrix2->m14 + matrix1->m12 * matrix2->m24 + matrix1->m13 * matrix2->m34 + matrix1->m14 * matrix2->m44;
    m->m21 = matrix1->m21 * matrix2->m11 + matrix1->m22 * matrix2->m21 + matrix1->m23 * matrix2->m31 + matrix1->m24 * matrix2->m41;
    m->m22 = matrix1->m21 * matrix2->m12 + matrix1->m22 * matrix2->m22 + matrix1->m23 * matrix2->m32 + matrix1->m24 * matrix2->m42;
    m->m23 = matrix1->m21 * matrix2->m13 + matrix1->m22 * matrix2->m23 + matrix1->m23 * matrix2->m33 + matrix1->m24 * matrix2->m43;
    m->m24 = matrix1->m21 * matrix2->m14 + matrix1->m22 * matrix2->m24 + matrix1->m23 * matrix2->m34 + matrix1->m24 * matrix2->m44;
    m->m31 = matrix1->m31 * matrix2->m11 + matrix1->m32 * matrix2->m21 + matrix1->m33 * matrix2->m31 + matrix1->m34 * matrix2->m41;
    m->m32 = matrix1->m31 * matrix2->m12 + matrix1->m32 * matrix2->m22 + matrix1->m33 * matrix2->m32 + matrix1->m34 * matrix2->m42;
    m->m33 = matrix1->m31 * matrix2->m13 + matrix1->m32 * matrix2->m23 + matrix1->m33 * matrix2->m33 + matrix1->m34 * matrix2->m43;
    m->m34 = matrix1->m31 * matrix2->m14 + matrix1->m32 * matrix2->m24 + matrix1->m33 * matrix2->m34 + matrix1->m34 * matrix2->m44;
    m->m41 = matrix1->m41 * matrix2->m11 + matrix1->m42 * matrix2->m21 + matrix1->m43 * matrix2->m31 + matrix1->m44 * matrix2->m41;
    m->m42 = matrix1->m41 * matrix2->m12 + matrix1->m42 * matrix2->m22 + matrix1->m43 * matrix2->m32 + matrix1->m44 * matrix2->m42;
    m->m43 = matrix1->m41 * matrix2->m13 + matrix1->m42 * matrix2->m23 + matrix1->m43 * matrix2->m33 + matrix1->m44 * matrix2->m43;
    m->m44 = matrix1->m41 * matrix2->m14 + matrix1->m42 * matrix2->m24 + matrix1->m43 * matrix2->m34 + matrix1->m44 * matrix2->m44;
    return m;
}

Matrix44d matrix_compound(int count, ...) {
    va_list matrices;
    Matrix44d matrix = matrix_newDiagonal(1);
    va_start(matrices, count);
    while (count-- > 0) {
        Matrix44d arg = va_arg(matrices, Matrix44d);
        Matrix44d m = matrix_multiply(matrix, arg);
        free(matrix);
        matrix = m;
    }
    va_end(matrices);
    return matrix;
}

void matrix_add(Matrix44d matrix1, Matrix44d matrix2) {
    matrix1->m11 += matrix2->m11;
    matrix1->m12 += matrix2->m12;
    matrix1->m13 += matrix2->m13;
    matrix1->m14 += matrix2->m14;
    matrix1->m21 += matrix2->m21;
    matrix1->m22 += matrix2->m22;
    matrix1->m23 += matrix2->m23;
    matrix1->m24 += matrix2->m24;
    matrix1->m31 += matrix2->m31;
    matrix1->m32 += matrix2->m32;
    matrix1->m33 += matrix2->m33;
    matrix1->m34 += matrix2->m34;
    matrix1->m41 += matrix2->m41;
    matrix1->m42 += matrix2->m42;
    matrix1->m43 += matrix2->m43;
    matrix1->m44 += matrix2->m44;
}
