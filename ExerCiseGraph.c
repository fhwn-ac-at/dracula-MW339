//
// Created by manuel on 15.05.25.
//

#include <stdio.h>
#include <stdlib.h>

#define NoEdges 0
#define VERTICES_LIMIT 100

typedef struct {
  int from;
  int to;
  int weight;
} Edge;

void createMatrix(int n, Edge* edges, int edgesAmount, int matrix[VERTICES_LIMIT][VERTICES_LIMIT]) {
    for (int i = 0; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = NoEdges;
  }
}

for (int i = 0; i < edgesAmount; i++) {
  int from = edges[i].from;
  int to = edges[i].to;
  int weight = edges[i].weight;

 matrix[from][to] = weight;
 matrix[to][from] = weight;
}
}


void showMatrix(int n, int matrix[VERTICES_LIMIT][VERTICES_LIMIT]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        printf("%d ", matrix[i][j]);
      }
      printf("\n");
    }
  }



int main (void) {

Edge edges[] = {
  {0, 1, 8},
  {1, 2, 12},
  {2, 0, 8},
  {2, 1, 5},
  {3, 1, 2},
  {4, 1, 5},
  {1, 1, 9},


};
int n = 7;
int edgesAmount = sizeof(edges) / sizeof(edges[0]);
//int** matrix = createMatrix(n, edges, edgesAmount);
int matrix[VERTICES_LIMIT][VERTICES_LIMIT];

createMatrix(n, edges, edgesAmount, matrix);
showMatrix(n, matrix);


}