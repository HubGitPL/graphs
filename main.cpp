#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Graph.h"

#define NOT_VISITED 0
#define ALREADY_VISITED 1

#define UNCOLORED 0
#define RED 1
#define BLUE 2

#define BIG_INT 2147483646

using namespace std;

/*
 * Learn C the Hard Way: Practical Exercises on the Computational Subjects You Keep Avoiding (Like C) Zed A. Shaw
 * Thomas H Cormen Introducing to Alghorithms
 * https://medium.com/@arifimran5/fast-and-slow-pointer-pattern-in-linked-list-43647869ac99
 * lecture slides: bubble sort and merge sort algorithms
 */

void task1(Graph* graphs);
void task2(Graph* graphs);
void task3(Graph* graphs);
void task4(Graph* graphs);
void task5(Graph* graphs);
void task6(Graph* graphs);
void task7(Graph* graphs);
void task8(Graph* graphs);
void task9(Graph* graphs);
void task10(Graph* graphs);
int main() {
    long long int numberOfGraphs, numberOfVertices, numberOfNeighbours, neighbour;
    //vector w vectorze
    scanf("%lld", &numberOfGraphs);
    for (long long int i = 0; i < numberOfGraphs; i++) {
        scanf("%lld", &numberOfVertices);
        Graph* graph = createGraph(numberOfVertices);
        for (long long int j = 0; j < numberOfVertices; j++) {
            scanf("%lld", &numberOfNeighbours);
            addVertex(graph, numberOfNeighbours);
            Vertex* vertex = (Vertex*) getLastElement(graph->vertices);
            for (long long int k = 0; k < numberOfNeighbours; k++) {
                scanf("%lld", &neighbour);
                addNeighbour(vertex, neighbour-1);
            }
        }
        task1(graph); //the degree sequence
        task2(graph); //the number of components
        task3(graph); //bipartiteness
        task4(graph); //the eccentricity of the vertices
        task5(graph); //planarity
        //vertices colours - VC
        task6(graph); //greedy (VC)
        task7(graph); //LF method (VC)
        task8(graph); //SLF method (VC)
        task9(graph); //the number of different C4 subgraphs
        task10(graph); //the number of the graph complements edges
        deleteGraph(graph);
    }
}

void sortOflistOfIntBubbleSort(listOfInt** list) {
    listOfInt* node = *list;
    while(node != nullptr) {
        listOfInt* next = node->next;
        while(next != nullptr) {
            if(node->value < next->value) {
                long long int temp = node->value;
                node->value = next->value;
                next->value = temp;
            }
            next = next->next;
        }
        node = node->next;
    }
}


void task1(Graph* graphs) {
    //lista long long int
    listOfInt* list = createListOfInt();

    ListNode* node = graphs->vertices->first;
    while(node != nullptr) {
        Vertex* vertex = (Vertex*)(node->value);
        pushBackListOfInt(&list, vertex->neighbours->counter);
        node = node->next;
    }
    //odwrotnie
    sortOflistOfIntBubbleSort(&list);
    printListOfInt(list);
    printf("\n");
    clearListOfInt(list);
}
void bfs(Graph* graph, long long int vertex, int* visited) {
    if(visited[vertex] == NOT_VISITED) {
        visited[vertex] = ALREADY_VISITED;
        // Casts the vertex at the given index in the graph's vertices list to a Vertex pointer.
        // This is done using the getElementVoid function, which retrieves an element from a list at a given index.
        // The retrieved element is a void pointer, so it needs to be cast to a Vertex pointer before it can be used.
        Vertex* vertexPtr = (Vertex*)(getElementVoid(graph->vertices, vertex));
        ListNode* node = vertexPtr->neighbours->first;
        while(node != nullptr) {
            long long int neighbour = (long long int)(node->value);
            if(visited[neighbour] == NOT_VISITED) {
                bfs(graph, neighbour, visited);
            }
            node = node->next;
        }
    }
}
void task2(Graph* graphs) {
    //bfs nNależy więc puścić algorytm przechodzący po grafie z pierwszego wierzchołka, następnie z innego, który nie został jeszcze odwiedzony, i tak dalej.

        long long int numberOfComponents = 0;
        //dynamic table
        long long int numberOfVertices = graphs->vertices->counter;
        int* visited = new int[numberOfVertices];
        for (long long int j = 0; j < numberOfVertices; j++) {
            visited[j] = NOT_VISITED;
        }
        for (long long int j = 0; j < numberOfVertices; j++) {
            //bfs
            if(visited[j] == NOT_VISITED){
                numberOfComponents++;
                bfs(graphs, j, visited);
            }
        }
        printf("%lld\n", numberOfComponents);
        delete[] visited;
}
bool colouring(Graph* graphs, int vertex, int* colors, int color) {
    if(colors[vertex] == UNCOLORED) {
        colors[vertex] = color;
        Vertex* vertexPtr = (Vertex*)(getElementVoid(graphs->vertices, vertex));
        ListNode* node = vertexPtr->neighbours->first;
        while(node != nullptr) {
            int neighbour = (int)(long long int)(node->value);
            if(colors[neighbour] == UNCOLORED) {
                if (!colouring(graphs, neighbour, colors, color == RED ? BLUE : RED)) {
                    return false;
                }
            }
            else if(colors[neighbour] == color) {
                return false;
            }
            node = node->next;
        }
    }
    return true;
}

void task3(Graph* graphs) {
    int numberOfVertices = graphs->numberOfVertices;
    int* colors = new int[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
        colors[i] = UNCOLORED;
    }
    for (int i = 0; i < numberOfVertices; i++) {
        if(colors[i] == UNCOLORED) {
            if (!colouring(graphs, i, colors, RED)) {
                printf("F\n");
                delete [] colors;
                return;
            }
        }
    }
    printf("T\n");
    delete [] colors;
}
void bfs(Graph* graph, int vertex, int* distances) {
    int numberOfVertices = graph->numberOfVertices;
    int* visited = new int[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        visited[i] = NOT_VISITED;
        distances[i] =  BIG_INT;
    }

    int* queue = new int[numberOfVertices];
    int front = 0, back = 0;

    queue[back++] = vertex;
    visited[vertex] = ALREADY_VISITED;
    distances[vertex] = 0;

    while(front != back) {
        int current = queue[front++];
        Vertex* vertexPtr = (Vertex*)(getElementVoid(graph->vertices, current));
        ListNode* node = vertexPtr->neighbours->first;

        while(node != nullptr) {
            int neighbour = (int)(long long int)(node->value);
            if(!visited[neighbour]) {
                queue[back++] = neighbour;
                visited[neighbour] = ALREADY_VISITED;
                distances[neighbour] = distances[current] + 1;
            }
            node = node->next;
        }
    }

    delete [] visited;
    delete [] queue;
}

int* my_max_element(int* first, int* last) {
    if(first == last) {
        return last;
    }

    int* largest = first;
    while(++first != last) {
        if(*largest < *first) {
            largest = first;
        }
    }
    return largest;
}

void task4(Graph* graphs) {
//    int numberOfVertices = graphs->numberOfVertices;
//    int* distances = new int[numberOfVertices];
//
//    for(int i = 0; i < numberOfVertices; i++) {
//        bfs(graphs, i, distances);
//        int eccentricity = *my_max_element(distances, distances + numberOfVertices);
//        printf("%d ", eccentricity);
//    }
//
//    printf("\n");
//    delete [] distances;
    printf("?\n");
}
void task5(Graph* graphs) {
    printf("?\n");
}
void task6(Graph* graphs) {
    long long int numberOfVertices = graphs->numberOfVertices;
    int* colors = new int[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        colors[i] = UNCOLORED;
    }
    for(int i = 0; i < numberOfVertices; i++) {
        Vertex* vertexPtr = (Vertex*)(getElementVoid(graphs->vertices, i));
        ListNode* node = vertexPtr->neighbours->first;

        int* availableColors = new int[numberOfVertices];

        for(int j = 0; j < numberOfVertices; j++) {
            availableColors[j] = true;
        }

        // Przejdź przez wszystkich sąsiadów bieżącego wierzchołka
        while(node != nullptr) {
            int neighbour = (int)(long long int)(node->value);
            if(colors[neighbour] != 0) {
                // Jeśli sąsiad jest już pokolorowany, jego kolor staje się niedostępny
                availableColors[colors[neighbour] - 1] = false;
            }
            node = node->next;
        }

        // Znajdź najmniejszy dostępny kolor
        int color = 0;
        for(color = 0; color < numberOfVertices; color++) {
            if(availableColors[color]) {
                break;
            }
        }

        // Pokoloruj bieżący wierzchołek
        colors[i] = color + 1; // Dodajemy 1, ponieważ kolory zaczynają się od 1
        delete [] availableColors;
    }

    // Wypisz kolory wszystkich wierzchołków
    for(int i = 0; i < numberOfVertices; i++) {
        printf("%d ", colors[i]);
    }
    printf("\n");

    delete [] colors;
}
void task7(Graph* graphs) {
    int numberOfVertices = graphs->numberOfVertices;
    int* colors = new int[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        colors[i] = UNCOLORED;
    }

    // Create an array of pairs. The first element of the pair is the degree of the vertex and the second element is the index of the vertex.
    int* degrees = new int[numberOfVertices];
    int* indices = new int[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        Vertex* vertex = (Vertex*)(getElementVoid(graphs->vertices, i));
        degrees[i] = vertex->neighbours->counter;
        indices[i] = i;
    }

    // Sort the vertices in descending order of their degree using stable sort.
    //name of this sort is: bubble sort
    for(int i = 0; i < numberOfVertices - 1; i++) {
        for(int j = 0; j < numberOfVertices - i - 1; j++) {
            if(degrees[j] < degrees[j + 1]) {
                // Swap degrees
                int tempDegree = degrees[j];
                degrees[j] = degrees[j + 1];
                degrees[j + 1] = tempDegree;
                // Swap indices
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }

    // Apply greedy coloring.
    for(int i = 0; i < numberOfVertices; i++) {
        int vertexIndex = indices[i];
        Vertex* vertex = (Vertex*)(getElementVoid(graphs->vertices, vertexIndex));
        ListNode* node = vertex->neighbours->first;

        int* availableColors = new int[numberOfVertices];
        for(int j = 0; j < numberOfVertices; j++) {
            availableColors[j] = RED; // true
        }

        // Go through all neighbours of the current vertex
        while(node != nullptr) {
            long long int neighbour = (long long int)(node->value);
            if(colors[neighbour] != UNCOLORED) {
                // If neighbour is already colored, its color becomes unavailable
                availableColors[colors[neighbour] - 1] = UNCOLORED; // false
            }
            node = node->next;
        }

        // Find the smallest available color
        int color = 0;
        for(color = 0; color < numberOfVertices; color++) {
            if(availableColors[color]) {
                break;
            }
        }

        // Color the current vertex
        colors[vertexIndex] = color + 1; // We add 1 because colors start from 1
        delete [] availableColors;
    }

    // Print the colors of all vertices
    for(int i = 0; i < numberOfVertices; i++) {
        printf("%d ", colors[i]);
    }
    printf("\n");
    delete [] colors;
    delete [] degrees;
    delete [] indices;
}


void task8(Graph* graphs) {
    printf("?\n");
}
void task9(Graph* graphs) {
    printf("?\n");
}
void task10(Graph* graphs) {
    long long int numberOfEdges = 0;
    long long int numberOfVertices = graphs->numberOfVertices;

    ListNode* vertexNode = graphs->vertices->first;
    for (long long int i = 0; i < numberOfVertices; i++) {
        Vertex* vertex = (Vertex*)(vertexNode->value);
        ListNode* neighbourNode = vertex->neighbours->first;
        while(neighbourNode != nullptr) {
            if((long long int)neighbourNode->value > i) {
                numberOfEdges++;
            }
            neighbourNode = neighbourNode->next;
        }
        vertexNode = vertexNode->next;
    }
    // n * (n-1) / 2 - m
    long long int result = (numberOfVertices * (numberOfVertices - 1) / 2) - numberOfEdges;
    printf("%lld\n", result);
}
