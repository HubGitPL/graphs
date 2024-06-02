//
// Created by Mateusz on 29/05/2024.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#endif //GRAPHS_GRAPH_H

#include <stdlib.h>
#include <cstdio>

//
// Created by Mateusz on 28/05/2024.
//


#include "myList.h"

typedef struct Vertex {
    List* neighbours;
    long long int numberOfNeighbours;
} Vertex;

typedef struct Graph {
    List* vertices;
    long long int numberOfVertices;
} Graph;

typedef struct listOfInt {
    long long int value;
    struct listOfInt* next;
} listOfInt;

Graph* createGraph(long long int numberOfVertices);
Vertex* createVertex();
listOfInt *createListOfInt();
void pushBackListOfInt(listOfInt** list, long long int value);
void printListOfInt(listOfInt* list);
void clearListOfInt(listOfInt* list);
void addVertex(Graph* graph, long long int numberOfNeighbours);
void addNeighbour(Vertex* vertex, long long int neighbour);
void deleteGraph(Graph* graph);