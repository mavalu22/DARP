#define MAX_VIA 1440
#define MAX_ESP 1440
#define CARROS 6

int locais;

typedef struct input
{
    int req;
    int durMaxRot;
    int vetNumAss[CARROS];
    int vetNumAssLoc[locais];
    int vetTempServ[];
    int vetIniTemp[];
    int vetTermTemp[];
    int matTemp[][];
    int funObj;
} input;