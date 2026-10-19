#include "../headers/objParser.h"
#include "../headers/gui.h"

#define BLACK 0.0
#define WHITE 1.0
#define GRAY(X) X

static Matrix44d createTransformation(double x, double y, double z, double xDeg, double yDeg, double zDeg);
static void applyTransformation(ArrayList vertices, Matrix44d transformation);
static double facingRation(Triangle triangle, Ray cameraRay);

bool load(char *filename) {
    if (filename != NULL && obj_parseFile(filename)) {
        ArrayList vertices = obj_getVertices();
        Matrix44d transformation = createTransformation(TRANSLATE_X,
                                                        TRANSLATE_Y,
                                                        TRANSLATE_Z,
                                                        ROTATE_X,
                                                        ROTATE_Y,
                                                        ROTATE_Z);
        applyTransformation(vertices, transformation);
        return true;
    }
    return false;
}

double *render(int imageWidth, int imageHeight) {
    int bufferSize = imageWidth * imageHeight;
    double *buffer = calloc(bufferSize, sizeof(double));
    ArrayList triangles = obj_getTriangles();

    for (int x = 0; x < imageWidth; x++) {
        for (int y = 0; y < imageHeight; y++) {
            Triangle triangle;
            Ray cameraRay = ray_cameraRay(x, y, imageWidth, imageHeight, FOV);

            bool inter = false;
            double dist = 0;
            for (int i = 0; i < arrayList_size(triangles); ++i) {
                bool intersects = ray_intersect(cameraRay, arrayList_get(triangles, i), &dist);
                if (intersects)
                    triangle = arrayList_get(triangles, i);
                inter |= intersects;
            }

            if (inter)
                buffer[bufferIndex(x, y, imageWidth)] = GRAY(facingRation(triangle, cameraRay));
            else
                buffer[bufferIndex(x, y, imageWidth)] = WHITE;

            free(cameraRay);
        }
    }
    return buffer;
}

int bufferIndex(int x, int y, int imageWidth) {
    return y * imageWidth + x;
}


Matrix44d createTransformation(double x, double y, double z, double xDeg, double yDeg, double zDeg) {
    Matrix44d t1 = matrix_newTranslate(x, y, z);
    Matrix44d t2 = matrix_newRotateX(xDeg);
    Matrix44d t0 = matrix_newRotateY(yDeg);
    Matrix44d t3 = matrix_newRotateZ(zDeg);
    Matrix44d transformation = matrix_compound(4, t0, t1, t2, t3);
    utils_freeAll(4, t0, t1, t2, t3);
    return transformation;
}

void applyTransformation(ArrayList vertices, Matrix44d transformation) {
    for (int i = 1; i < arrayList_size(vertices); ++i) {
        Vector3d vertex = arrayList_get(vertices, i);
        matrix_multiplyVector(vertex, transformation);
    }
}

double facingRation(Triangle triangle, Ray cameraRay) {
    Vector3d normal = triangle_normal(triangle);
    double facingRatio = -vector_dotProduct(normal, cameraRay->direction);
    free(normal);
    return facingRatio;
}