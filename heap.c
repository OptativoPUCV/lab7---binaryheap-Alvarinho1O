#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if (pq == NULL || pq->size == 0)
    return NULL;
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
  if (pq == NULL || pq->size == 0)
    return;

  if (pq->size == pq->capac) 
  {
    int nueva_capacidad = (2 * pq->capac) + 1;
    pq->heapArray = realloc(pq->heapArray, nueva_capacidad * sizeof(heapElem));
    pq->capac = nueva_capacidad;
  }

  int i = pq->size;
  pq->heapArray[i].data = data;
  pq->heapArray[i].priority = priority;
  while (i > 0 && pq->heapArray[i].priority > pq->heapArray[(i - 1) / 2].priority)
  {
    heapElem temp = pq->heapArray[i];
    pq->heapArray[i] = pq->heapArray[(i - 1) / 2];
    pq->heapArray[(i - 1) / 2] = temp;
    i = (i - 1)/2;
  }
  pq->size++;
}


void heap_pop(Heap* pq){
  if (pq == NULL || pq->size == 0)
    return;
  pq->size--;
  pq->heapArray[0] = pq->heapArray[pq->size];

  int padre =0;

  while((2*padre)+1 < pq->size ) 
  {
    int hijo = 2*padre+1;
    if(hijo+1 < pq->size && pq->heapArray[hijo + 1].priority > pq->heapArray[hijo].priority) 
    {
      hijo++;
    }

     if (pq->heapArray[padre].priority < pq->heapArray[hijo].priority)
     {
       heapElem temp = pq->heapArray[padre];
       pq->heapArray[padre] = pq->heapArray[hijo];
       pq->heapArray[hijo] = temp;
       padre = hijo;
     }else{
       break;
     }
  }
}

Heap* createHeap(){
  Heap *dato = malloc(sizeof(Heap));
  dato->capac = 3;
  dato->size = 0;
  dato->heapArray = malloc(3 * sizeof(heapElem));
  return dato;
  }
