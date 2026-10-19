#include "../headers/objParser.h"

#define FACE_SIZE sizeof(struct face)

typedef struct face {
    int vertex1Id;
    int vertex2Id;
    int vertex3Id;
} face, *Face;

static ArrayList vertices;
static ArrayList triangles;
static Queue tempVertices;
static Queue tempFaces;

static void ignore(Ucs4str);
static void pushVertex(Ucs4str);
static void pushFace(Ucs4str);

static Action getActionForLine(Ucs4str line);
static double parseDouble(Stack stack);
static int parseInt(Stack stack);
static void createLists();

static Face face_new(int vertex1Id, int vertex2Id, int vertex3Id);

static ConfigLine config[] = {
        CONFIG_LINE(utf8_startsWith, COMMENT_TAG, ignore),
        CONFIG_LINE(utf8_startsWith, VERTEX_TAG, pushVertex),
        CONFIG_LINE(utf8_startsWith, FACE_TAG, pushFace),
        CONFIG_LINE(utf8_startsWith, GROUP_TAG, ignore)
};

bool obj_parseFile(const char *filename) {
    tempVertices = queue_new();
    tempFaces = queue_new();
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return false;
    Ucs4str line;
    while ((line = utf8_readLine(file)) != NULL) {
        line = utf8_trim(line);
        Action action = getActionForLine(line);
        if (action != NULL)
            action(line);
    }
    fclose(file);
    createLists();
    return true;
}

ArrayList obj_getVertices() {
    return vertices;
}

ArrayList obj_getTriangles() {
    return triangles;
}

void createLists() {
    //list size incremented by 1, because vertices ids starts from 1
    vertices = arrayList_new(tempVertices->size + 1);
    //also that is why list start with empty NULL vertex
    arrayList_add(vertices, NULL);
    Vector3d vertex;
    while ((vertex = queue_poll(tempVertices)) != NULL)
        arrayList_add(vertices, vertex);
    queue_clear(tempVertices);
    free(tempVertices);

    triangles = arrayList_new(tempFaces->size);
    Face face;
    while ((face = queue_poll(tempFaces)) != NULL) {
        Vector3d vertex1 = arrayList_get(vertices, face->vertex1Id);
        Vector3d vertex2 = arrayList_get(vertices, face->vertex2Id);
        Vector3d vertex3 = arrayList_get(vertices, face->vertex3Id);
        Triangle triangle = triangle_new(vertex1, vertex2, vertex3);
        arrayList_add(triangles, triangle);
        free(face);
    }
    queue_clear(tempFaces);
    free(tempFaces);
}

Action getActionForLine(Ucs4str line) {
    for (int i = 0; i < CONFIG_SIZE; ++i)
        if (config[i]->condition(line, config[i]->tag))
            return config[i]->action;
    return nullptr;
}

double parseDouble(Stack stack) {
    double sum = 0;
    int n = 0, z = 1, commaPos = 0;
    while (!stack_isEmpty(stack)) {
        long l = stack_poll(stack);
        if (l == MINUS)
            z = -1;
        else if (l == COMMA)
            commaPos = n;
        else
            sum += pow(10, n++) * CHAR_NUMBER_TO_VALUE(l);
    }
    stack_clear(stack);
    return z * (sum / pow(10, commaPos));
}

int parseInt(Stack stack) {
    int n = 0, sum = 0, z = 1;
    while (!stack_isEmpty(stack)) {
        long l = stack_poll(stack);
        if (l == MINUS)
            z = -1;
        else
            sum += pow(10, n++) * CHAR_NUMBER_TO_VALUE(l);
    }
    stack_clear(stack);
    return z * sum;
}


void ignore(Ucs4str line) {}

void pushVertex(Ucs4str line) {
    Stack coord = stack_new();
    Ucs4str s = utf8_substring(line, utf8_length(VERTEX_TAG), 0);
    Ucs4str t = utf8_trim(s);
    Ucs4str w;
    double xyz[3];
    bool hasNext = true;
    int offset = 0, ci = 0;
    while (hasNext) {
        w = utf8_nextWord(t, &offset, &hasNext);
        for (int i = 0; w[i] != '\0'; ++i)
            stack_push(coord, w[i]);
        xyz[ci++] = parseDouble(coord);
        printf("\n");
        free(w);
    }
    Vector3d vertex = vector_new(xyz[0], xyz[1], xyz[2]);
    queue_add(tempVertices, vertex);

    utils_freeAll(4, coord, line, s, t);
}

void pushFace(Ucs4str line) {
    Stack id = stack_new();
    Ucs4str s = utf8_substring(line, utf8_length(FACE_TAG), 0);
    Ucs4str t = utf8_trim(s);
    Ucs4str w;
    int ids[3];
    bool hasNext = true;
    int offset = 0, ci = 0;
    while (hasNext) {
        w = utf8_nextWord(t, &offset, &hasNext);
        for (int i = 0; w[i] != '\0'; ++i)
            stack_push(id, w[i]);
        ids[ci++] = parseInt(id);
        free(w);
    }
    Face face = face_new(ids[0], ids[1], ids[2]);
    queue_add(tempFaces, face);

    utils_freeAll(4, id, line, s, t);
}

static Face face_new(int vertex1Id, int vertex2Id, int vertex3Id) {
    Face face = malloc(FACE_SIZE);
    face->vertex1Id = vertex1Id;
    face->vertex2Id = vertex2Id;
    face->vertex3Id = vertex3Id;
    return face;
}
