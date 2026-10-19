#ifndef OBJ_H
#define OBJ_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "collections.h"
#include "geometry.h"
#include "utils.h"
#include "utf8.h"


#define CONFIG_LINE(condition, tag, action) &(configLine){condition, tag, action}
#define CHAR_NUMBER_TO_VALUE(x) ((x) - 0x30)

#define COMMENT_TAG AS_UCS4STR('#', ' ', '\0')
#define VERTEX_TAG  AS_UCS4STR('v', ' ', '\0')
#define FACE_TAG    AS_UCS4STR('f', ' ', '\0')
#define GROUP_TAG   AS_UCS4STR('g', ' ', '\0')

#define CONFIG_SIZE 4
#define MINUS '-'
#define COMMA '.'

typedef bool (*Condition)(Ucs4str, Ucs4str);
typedef void (*Action)(Ucs4str);

typedef struct configLine {
    Condition condition;
    Ucs4str tag;
    Action action;
} configLine, *ConfigLine;

bool obj_parseFile(const char *filename);
ArrayList obj_getVertices();
ArrayList obj_getTriangles();


#endif
