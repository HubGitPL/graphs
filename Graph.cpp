//
// Created by Mateusz on 28/05/2024.
//


#include "Graph.h"

Graph* createGraph(long long int numberOfVertices) {
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    graph->vertices = createList();
    graph->numberOfVertices = numberOfVertices;
    return graph;
}

Vertex* createVertex() {
    Vertex* vertex = (Vertex*)calloc(1, sizeof(Vertex));
    vertex->neighbours = createList();
    return vertex;
}

listOfInt *createListOfInt() {
    return nullptr;
}

void pushBackListOfInt(listOfInt** list, long long int value) {
    listOfInt* newNode = (listOfInt*)calloc(1, sizeof(listOfInt));
    newNode->value = value;
    newNode->next = nullptr;

    if (*list == NULL) {
        *list = newNode;
    } else {
        listOfInt* node = *list;
        while(node->next != NULL) {
            node = node->next;
        }
        node->next = newNode;
    }
}

void printListOfInt(listOfInt* list) {
    listOfInt* node = list;
    while(node != NULL) {
        printf("%lld ", node->value);
        node = node->next;
    }
    free(node);
}

void clearListOfInt(listOfInt* list) {
    listOfInt* node = list;
    while(node != NULL) {
        listOfInt* next = node->next;
        free(node);
        node = next;
    }
}

void addVertex(Graph* graph, long long int numberOfNeighbours){
    Vertex* vertex = createVertex();
    pushBack(graph->vertices, vertex);
    vertex->numberOfNeighbours = numberOfNeighbours;
}

void addNeighbour(Vertex* vertex, long long int neighbour) {
    pushBack(vertex->neighbours, (void*)neighbour);
}

void deleteGraph(Graph* graph) {
    ListNode* node = graph->vertices->first;
    while(node != NULL) {
        Vertex* vertex = (Vertex*)node->value;
        clearList(vertex->neighbours);
        free(vertex->neighbours);
        free(vertex);
        node = node->next;
    }
    clearList(graph->vertices);
    free(graph->vertices);
    free(graph);
    free(node);

}