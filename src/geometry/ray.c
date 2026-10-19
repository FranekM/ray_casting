#include "../headers/geometry.h"

Ray ray_new(Vector3d origin, Vector3d direction) {
    Ray ray = malloc(RAY_SIZE);
    ray->origin = origin;
    ray->direction = direction;
    return ray;
}

bool ray_intersect(Ray ray, Triangle triangle, double *distance) {
    Vector3d normal = triangle_normal(triangle);
    double a = vector_dotProduct(normal, ray->direction);
    if (fabs(a) < EPSYLON || a > 0)
        return false;

    double d = vector_dotProduct(normal, triangle->vertex1);
    double t = (vector_dotProduct(normal, ray->origin) + d) / a;
    if (t < 0)
        return false;

    Vector3d multi = vector_scalarMultiplication(t, ray->direction);
    Vector3d point = vector_sum(ray->origin, multi);

    Vector3d edge1 = vector_difference(triangle->vertex2, triangle->vertex1);
    Vector3d edge2 = vector_difference(triangle->vertex3, triangle->vertex2);
    Vector3d edge3 = vector_difference(triangle->vertex1, triangle->vertex3);
    Vector3d a1 = vector_difference(point, triangle->vertex1);
    Vector3d a2 = vector_difference(point, triangle->vertex2);
    Vector3d a3 = vector_difference(point, triangle->vertex3);
    Vector3d b1 = vector_crossProduct(edge1, a1);
    Vector3d b2 = vector_crossProduct(edge2, a2);
    Vector3d b3 = vector_crossProduct(edge3, a3);

    bool inside = true;
    inside &= (vector_dotProduct(normal, b1) >= 0);
    inside &= (vector_dotProduct(normal, b2) >= 0);
    inside &= (vector_dotProduct(normal, b3) >= 0);

    *distance = t;

    utils_freeAll(11, normal, multi, edge1, edge2, edge3, a1, a2, a3, b1, b2, b3);

    return inside;
}

Ray ray_cameraRay(int x, int y, double width, double height, double fov) {
    double aspectRatio = width / height;
    double px = (2 * ((x + 0.5) / width) - 1) * tan(fov / 2 * M_PI / 180) * aspectRatio;
    double py = (1 - 2 * ((y + 0.5) / height) * tan(fov / 2 * M_PI / 180));

    Vector3d origin = vector_new(0, 0, 0);
    Vector3d dir = vector_new(px, py, -1);
    Vector3d direction = vector_difference(dir, origin);
    vector_normalize(direction);
    free(dir);
    return ray_new(origin, direction);
}
