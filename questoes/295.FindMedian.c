#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50005

typedef struct {
    int data[MAX_SIZE];
    int size;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->size = 0;
    return mf;
}

// Busca binária para achar posição de inserção
int binarySearchInsertPos(MedianFinder* mf, int num) {
    int l = 0, r = mf->size;
    while (l < r) {
        int mid = (l + r) / 2;
        if (mf->data[mid] < num)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
// inserçao:
void medianFinderAddNum(MedianFinder* mf, int num) {
    if (mf->size >= MAX_SIZE) return;
    
    int pos = binarySearchInsertPos(mf, num);

    // Desloca à direita
    for (int i = mf->size; i > pos; i--)
        mf->data[i] = mf->data[i - 1];

    mf->data[pos] = num;
    mf->size++;
}
// 0(n)
double medianFinderFindMedian(MedianFinder* mf) {
    if (mf->size == 0) return 0.0;
    int n = mf->size;
    if (n % 2 == 1)
        return (double)mf->data[n / 2];
    else
        return ((double)mf->data[n / 2 - 1] + (double)mf->data[n / 2]) / 2.0;
}

void medianFinderFree(MedianFinder* mf) {
    free(mf);
}

