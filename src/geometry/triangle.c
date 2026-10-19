#include "../headers/geometry.h"


Triangle triangle_new(Vector3d vertex1, Vector3d vertex2, Vector3d vertex3) {
    Triangle triangle = malloc(TRIANGLE_SIZE);
    triangle->vertex1 = vertex1;
    triangle->vertex2 = vertex2;
    triangle->vertex3 = vertex3;
    return triangle;
}

Vector3d triangle_normal(Triangle triangle) {
    Vector3d edge1 = vector_difference(triangle->vertex2, triangle->vertex1);
    Vector3d edge2 = vector_difference(triangle->vertex3, triangle->vertex1);
    Vector3d cross = vector_crossProduct(edge1, edge2);
    vector_normalize(cross);
    utils_freeAll(2, edge1, edge2);
    return cross;
}
