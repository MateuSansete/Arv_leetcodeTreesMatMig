#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // memcpy

typedef struct {
    int left;
    int right;
} Range;

typedef struct {
    Range *intervals;
    int count;
    int capacity;
} RangeModule;

int my_min(int a, int b) { return a < b ? a : b; }
int my_max(int a, int b) { return a > b ? a : b; }

RangeModule* rangeModuleCreate() {
    RangeModule* obj = (RangeModule*)malloc(sizeof(RangeModule));
    if (obj) {
        obj->intervals = NULL;
        obj->count = 0;
        obj->capacity = 0;
    }
    return obj;
}

void free_intervals_array(Range *arr) {
    if (arr) free(arr);
}


void rangeModuleAddRange(RangeModule* obj, int left, int right) {
    if (left >= right) return;

    int n = obj->count;
    // reservamos no máximo n+1 intervalos (mescla pode reduzir ou aumentar só em +1)
    Range *newarr = (Range*)malloc((n + 1) * sizeof(Range));
    int ni = 0;
    int i = 0;

    //  copiar intervals à esquerda
    while (i < n && obj->intervals[i].right < left) {
        newarr[ni++] = obj->intervals[i++];
    }

    //  fundir todos os que se sobrepõem
    int L = left;
    int R = right;
    while (i < n && obj->intervals[i].left <= R) {
        if (obj->intervals[i].left < L) L = obj->intervals[i].left;
        if (obj->intervals[i].right > R) R = obj->intervals[i].right;
        i++;
    }
    // inserir o intervalo fundido
    newarr[ni].left = L;
    newarr[ni].right = R;
    ni++;

    // copiar o restante
    while (i < n) {
        newarr[ni++] = obj->intervals[i++];
    }

    // substituir o array antigo
    free_intervals_array(obj->intervals);
    obj->intervals = newarr;
    obj->count = ni;
    obj->capacity = ni;
}

bool rangeModuleQueryRange(RangeModule* obj, int left, int right) {
    if (left >= right) return true;
    for (int i = 0; i < obj->count; ++i) {
        if (obj->intervals[i].left <= left && obj->intervals[i].right >= right) {
            return true;
        }
    }
    return false;
}

void rangeModuleRemoveRange(RangeModule* obj, int left, int right) {
    if (left >= right || obj->count == 0) return;

    int n = obj->count;
    // no pior caso podemos gerar n+1 intervalos (quando um intervalo é dividido)
    Range *newarr = (Range*)malloc((n + 1) * sizeof(Range));
    int ni = 0;

    for (int i = 0; i < n; ++i) {
        int l = obj->intervals[i].left;
        int r = obj->intervals[i].right;

        // sem sobreposição
        if (r <= left || l >= right) {
            newarr[ni++] = obj->intervals[i];
            continue;
        }

        // caso haja parte à esquerda que permanece
        if (l < left) {
            newarr[ni].left = l;
            newarr[ni].right = my_min(r, left);
            ni++;
        }

        // caso haja parte à direita que permanece
        if (r > right) {
            newarr[ni].left = my_max(l, right);
            newarr[ni].right = r;
            ni++;
        }
        // se o intervalo foi completamente removido, não copiamos nada
    }

    free_intervals_array(obj->intervals);
    obj->intervals = newarr;
    obj->count = ni;
    obj->capacity = ni;
}

void rangeModuleFree(RangeModule* obj) {
    if (!obj) return;
    if (obj->intervals) free(obj->intervals);
    free(obj);
}
