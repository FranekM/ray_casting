#include "../headers/geometry.h"


Vector3d vector_new(double v1, double v2, double v3) {
    Vector3d vector = malloc(VECTOR3D_SIZE);
    vector->v1 = v1;
    vector->v2 = v2;
    vector->v3 = v3;
    return vector;
}

double vector_dotProduct(Vector3d vector1, Vector3d vector2) {
    return
        vector1->v1 * vector2->v1 +
        vector1->v2 * vector2->v2 +
        vector1->v3 * vector2->v3;
}

Vector3d vector_crossProduct(Vector3d vector1, Vector3d vector2) {
    double v1, v2, v3;
    v1 = (vector1->v2 * vector2->v3) - (vector1->v3 * vector2->v2);
    v2 = (vector1->v3 * vector2->v1) - (vector1->v1 * vector2->v3);
    v3 = (vector1->v1 * vector2->v2) - (vector1->v2 * vector2->v1);
    return vector_new(v1, v2, v3);
}

Vector3d vector_scalarMultiplication(double scalar, Vector3d vector) {
    double v1, v2, v3;
    v1 = vector->v1 * scalar;
    v2 = vector->v2 * scalar;
    v3 = vector->v3 * scalar;
    return vector_new(v1, v2, v3);
}

void vector_scalarMultiply(double scalar, Vector3d vector){
    vector->v1 *= scalar;
    vector->v2 *= scalar;
    vector->v3 *= scalar;
}

Vector3d vector_sum(Vector3d vector1, Vector3d vector2) {
    double v1, v2, v3;
    v1 = vector1->v1 + vector2->v1;
    v2 = vector1->v2 + vector2->v2;
    v3 = vector1->v3 + vector2->v3;
    return vector_new(v1, v2, v3);
}

Vector3d vector_difference(Vector3d vector1, Vector3d vector2) {
    double v1, v2, v3;
    v1 = vector1->v1 - vector2->v1;
    v2 = vector1->v2 - vector2->v2;
    v3 = vector1->v3 - vector2->v3;
    return vector_new(v1, v2, v3);
}

double vector_length(Vector3d vector) {
    return sqrt(vector->v1 * vector->v1 +
            vector->v2 * vector->v2 +
            vector->v3 * vector->v3);
}

void vector_normalize(Vector3d vector) {
    double length = vector_length(vector);
    vector_scalarMultiply(1/length, vector);
}
