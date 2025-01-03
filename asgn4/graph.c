#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    // use calloc to initialize everything with zeroes
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    // allocate g->weights with a pointer for each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    // allocate each row in the adjacency matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}
void graph_free(Graph **gp) {
    Graph *g = *gp;
    free(g->visited);
    for (int i = 0; i < (int) g->vertices; i++) {
        free(g->names[i]);
    }
    free(g->names);
    for (int i = 0; i < (int) g->vertices; i++) {
        free(g->weights[i]);
    }
    free(g->weights);
    free(g);
    *gp = NULL;
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v]) {
        free(g->names[v]);
    }
    g->names[v] = strdup(name);
}
const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

char **graph_get_names(const Graph *g) {
    return (g->names);
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    g->weights[start][end] = weight;
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
}
uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}
void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}
void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}
bool graph_visited(Graph *g, uint32_t v) {
    if (g->visited[v] == true) {
        return true;
    }
    return false;
}

void graph_print(const Graph *g) {
    int num_cities = (int) graph_vertices(g);
    fprintf(stderr, "%d\n", num_cities);
    char **names = graph_get_names(g);
    for (int i = 0; i < num_cities; i++) {
        fprintf(stderr, "%s\n", names[i]);
        for (int j = 0; j < num_cities; j++) {
            if (graph_get_weight(g, i, j) > 0) {
                fprintf(stderr, "%u %s\n", graph_get_weight(g, i, j), graph_get_vertex_name(g, j));
            }
        }
    }
}
/*int main() {
    Graph *g = graph_create(10, true);
    char *n = "SF";
    graph_add_vertex(g, n, 1);
    printf("%u\n", graph_vertices(g));
    printf("%s\n", graph_get_vertex_name(g, 1));
    graph_add_edge(g, 0, 1, 2);
    printf("%u\n", graph_get_weight(g, 0, 1));
    graph_visit_vertex(g, 1);
    if (graph_visited(g, 1) == true) {
        printf("True");
    }
    graph_unvisit_vertex(g, 1);

}*/
