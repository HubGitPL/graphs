
#include "Graph.h"

#include "Defines.h"

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
void task4();
void task5();
void task6(Graph* graphs);
void task7(Graph* graphs);
void task8();
void task9();
void task10(Graph* graphs);
int main() {
    long long int numberOfGraphs, numberOfVertices, numberOfNeighbours, neighbour;
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
        task4(); //the eccentricity of the vertices
        task5(); //planarity
        //vertices colours - VC
        task6(graph); //greedy (VC)
        task7(graph); //LF method (VC)
        task8(); //SLF method (VC)
        task9(); //the number of different C4 subgraphs
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
    //list long long int
    listOfInt* list = createListOfInt();
    ListNode* node = graphs->vertices->first;
    while(node != nullptr) {
        Vertex* vertex = (Vertex*)(node->value);
        pushBackListOfInt(&list, vertex->neighbours->counter);
        node = node->next;
    }
    sortOflistOfIntBubbleSort(&list);
    printListOfInt(list);
    printf("\n");
    clearListOfInt(list);
}
void bfs(Graph* graph, long long int vertex, int* visited) {
    if(visited[vertex] == NOT_VISITED) {
        visited[vertex] = ALREADY_VISITED;
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
            long long int neighbour = (long long int)(node->value);
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
void task4() {
    printf("?\n");
}
void task5() {
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
        // go through all neighbours of this vertex
        while(node != nullptr) {
            int neighbour = (int)(long long int)(node->value);
            if(colors[neighbour] != 0) {
                //neigbour =colored --> color is not available
                availableColors[colors[neighbour] - 1] = false;
            }
            node = node->next;
        }
       //find the smallest available color
        int color = 0;
        for(color = 0; color < numberOfVertices; color++) {
            if(availableColors[color]) {
                break;
            }
        }
        // color the current vertex
        colors[i] = color + 1; // add one beacuse colors start from 1
        delete [] availableColors;
    }
    //print all colors
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
    //acts like vector <pair<int, int>> x;
    int* degrees = new int[numberOfVertices]; //degree of the vertex
    int* indices = new int[numberOfVertices]; //the index of the vertex.
    for(int i = 0; i < numberOfVertices; i++) {
        Vertex* vertex = (Vertex*)(getElementVoid(graphs->vertices, i));
        degrees[i] = vertex->neighbours->counter;
        indices[i] = i;
    }
    //bubble sort
    for(int i = 0; i < numberOfVertices - 1; i++) {
        for(int j = 0; j < numberOfVertices - i - 1; j++) {
            if(degrees[j] < degrees[j + 1]) {
                int tempDegree = degrees[j];
                degrees[j] = degrees[j + 1];
                degrees[j + 1] = tempDegree;
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
void task8() {
    printf("?\n");
}
void task9() {
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
