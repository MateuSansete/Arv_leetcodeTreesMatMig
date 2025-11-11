#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50005

typedef struct {
    int data[MAX_SIZE];
    int size;
} Heap;

typedef struct {
    Heap lower_half; 
    Heap upper_half; 
} MedianFinder;


// Troca dois elementos em um array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}



void max_heapify(Heap* h, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->data[left] > h->data[largest]) {
        largest = left;
    }
    if (right < h->size && h->data[right] > h->data[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&h->data[i], &h->data[largest]);
        max_heapify(h, largest);
    }
}

void max_heap_insert(Heap* h, int val) {
    if (h->size >= MAX_SIZE) return;

    h->data[h->size] = val;
    int i = h->size;
    h->size++;

    while (i > 0 && h->data[(i - 1) / 2] < h->data[i]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int max_heap_extract_max(Heap* h) {
    if (h->size == 0) return 0;

    int max_val = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;

    max_heapify(h, 0); 
    return max_val;
}

int max_heap_top(Heap* h) {
    if (h->size == 0) return 0;
    return h->data[0];
}


void min_heapify(Heap* h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->data[left] < h->data[smallest]) {
        smallest = left;
    }
    if (right < h->size && h->data[right] < h->data[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&h->data[i], &h->data[smallest]);
        min_heapify(h, smallest);
    }
}

void min_heap_insert(Heap* h, int val) {
    if (h->size >= MAX_SIZE) return;

    h->data[h->size] = val;
    int i = h->size;
    h->size++;

    while (i > 0 && h->data[(i - 1) / 2] > h->data[i]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int min_heap_extract_min(Heap* h) {
    if (h->size == 0) return 0;

    int min_val = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;

    min_heapify(h, 0); 
    return min_val;
}

int min_heap_top(Heap* h) {
    if (h->size == 0) return 0;
    return h->data[0];
}


MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    if (mf == NULL) return NULL;

    mf->lower_half.size = 0;
    mf->upper_half.size = 0;

    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    max_heap_insert(&obj->lower_half, num);

    int max_of_lower = max_heap_extract_max(&obj->lower_half);
    min_heap_insert(&obj->upper_half, max_of_lower);

    if (obj->upper_half.size > obj->lower_half.size) {
        int min_of_upper = min_heap_extract_min(&obj->upper_half);
        max_heap_insert(&obj->lower_half, min_of_upper);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->lower_half.size > obj->upper_half.size) {
        return (double)max_heap_top(&obj->lower_half);
    }
    else {
        return ((double)max_heap_top(&obj->lower_half) + (double)min_heap_top(&obj->upper_half)) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    if (obj != NULL) {
        free(obj);
    }
}