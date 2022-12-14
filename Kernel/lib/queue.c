// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

typedef struct queueNode
{
  void *value;
  struct queueNode *next;
} queueNode;

typedef struct queueCDT
{
  uint64_t size;
  queueNode *first;
  queueNode *last;
} queueCDT;

typedef struct iteratorCDT
{
  queueNode *curr;
} iteratorCDT;

queueADT initQueue()
{
  queueADT queue = malloc(sizeof(queueCDT));
  if (queue == NULL)
  {
    return queue;
  }
  queue->first = queue->last = NULL;
  queue->size = 0;
  return queue;
}

// Esta funcion depende de que el valor dentro de tu queue no tenga mallocs anidados.
// Para limpiar mallocs anidados, usar dequeue y limpiarlo vos mismo.
int freeQueue(queueADT queue)
{
  if (queue == NULL)
    return -1;

  void *aux;
  while ((aux = dequeue(queue)) != NULL)
  {
    free(aux);
  }
  free(queue);
  return 0;
}

uint64_t getQueueSize(queueADT queue)
{
  return queue->size;
}

void *dequeue(queueADT queue)
{
  if (queue->size <= 0)
    return NULL;
  queueNode *aux = queue->first;
  queue->first = queue->first->next;
  queue->size -= 1;
  void *res = aux->value;
  free(aux);
  return res;
}

int enqueue(queueADT queue, void *value)
{
  queueNode *newNode = malloc(sizeof(queueNode));
  if (newNode == NULL)
  {
    return -1;
  }
  newNode->value = value;
  newNode->next = NULL;
  if (queue->size == 0)
  {
    queue->first = newNode;
    queue->last = newNode;
  }
  else
  {
    queue->last->next = newNode;
    queue->last = newNode;
  }
  queue->size += 1;
  return 0;
}

void *peek(queueADT queue)
{
  if (queue->size == 0)
    return NULL;
  return queue->first->value;
}

// Si no existe primero
iteratorADT toBegin(queueADT queue)
{
  if (queue == NULL)
    return NULL;

  iteratorADT it = malloc(sizeof(iteratorCDT));
  if (it == NULL)
    return NULL;
  it->curr = queue->first;
  return it;
}

int hasNext(iteratorADT it)
{
  if (it == NULL)
    return 0;
  return it->curr != NULL;
}

void *next(iteratorADT it)
{
  if (it == NULL || (!hasNext(it)))
    return NULL;
  void *aux = it->curr->value;
  it->curr = it->curr->next;
  return aux;
}

void *find(queueADT queue, int (*findCondition)(void *, void *), void *element)
{
  if (queue == NULL || findCondition == NULL)
    return NULL;

  iteratorADT it = toBegin(queue);
  void *aux;
  int found = 0;
  while (hasNext(it) && !found)
  {
    aux = next(it);
    found = findCondition(aux, element);
  }
  free(it);
  return (found) ? aux : NULL;
}

int includes(queueADT queue, int (*findCondition)(void *, void *), void *element)
{
  return find(queue, findCondition, element) != NULL;
}

int removeElement(queueADT queue, int (*removeCondition)(void *, void *), void *element)
{
  void *poppedElement = takeElement(queue, removeCondition, element);
  if (poppedElement != NULL)
  {
    free(poppedElement);
    return 1;
  }
  return 0;
}

void *takeElement(queueADT queue, int (*removeCondition)(void *, void *), void *element)
{
  if (queue == NULL || removeCondition == NULL || getQueueSize(queue) == 0)
    return NULL;
  queueNode *node = queue->first;
  queueNode *prev = NULL;
  while (node != NULL)
  {
    if (removeCondition(node->value, element))
    {
      if (prev == NULL)
      {
        queue->first = node->next;
      }
      else
      {
        prev->next = node->next;
      }
      if (node->next == NULL)
      {
        queue->last = prev;
      }
      void *nodeValue = node->value;
      free(node);
      queue->size -= 1;
      return nodeValue;
    }
    prev = node;
    node = node->next;
  }
  return NULL;
}