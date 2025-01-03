#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void dfs(uint32_t n, Graph *g, Path *p, Path *min) {
    graph_visit_vertex(g, n);
    path_add(p, n, g);
    if (graph_vertices(g) == (path_vertices(p) + 1)) {
        if (graph_get_weight(g, n, START_VERTEX)) {
            path_add(p, START_VERTEX, g);
            if (path_distance(min) > path_distance(p) || path_distance(min) == 0) {
                path_copy(min, p);
                //                path_print(min, stdout, g);
            }
            path_remove(p, g);
        }
    }
    uint32_t vertices = graph_vertices(g);
    for (uint32_t i = 0; i < vertices; i++) {
        if (graph_get_weight(g, n, i) > 0) {
            if (!graph_visited(g, i)) {
                //	fprintf(stderr, "%s", graph_get_vertex_name(g,i));
                dfs(i, g, p, min);
            }
        }
    }
    graph_unvisit_vertex(g, n);
    path_remove(p, g);
}

int main(int argc, char *argv[]) {
    int opt = 0;
    uint32_t num_vertices = 0;
    uint32_t num_edges = 0;
    char *input = NULL;
    char *output = NULL;
    char *str = calloc(1000, sizeof(char));
    extern char *optarg;
    bool dash_i = false;
    bool dash_o = false;
    bool directed = false;
    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch (opt) {
        case 'i':
            input = (optarg);
            dash_i = true;
            break;
        case 'o':
            output = (optarg);
            dash_o = true;
            break;
        case 'd': directed = true; break;
        case 'h': printf("Help Page"); return 0;
        default: break;
        }
    }
    FILE *infile = stdin;
    FILE *outfile = stdout;
    if (dash_i) {
        infile = fopen(input, "r");
        if (infile == NULL) {
            fprintf(stderr, "Input file could not be opened\n");
        }
        fseek(infile, 0, SEEK_SET);
    }
    if (dash_o) {
        outfile = fopen(output, "w");
        if (output == NULL) {
            fprintf(stderr, "Output file could not be opened\n");
        }
        fseek(outfile, 0, SEEK_SET);
    }
    if (fscanf(infile, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "tsp:  error reading number of vertices\n");
        exit(1);
    }
    Graph *g = graph_create(num_vertices + 1, directed);
    Path *p = path_create(num_vertices + 1);
    for (uint32_t i = 0; i < num_vertices; i++) {
        if (fgets(str, 1000, infile) != NULL) {
            //		puts(str);
            graph_add_vertex(g, str, i);
        }
    }
    if (fscanf(infile, "%u\n", &num_edges) != 1) {
        fprintf(stderr, "tsp:  error reading number of edges\n");
        exit(1);
    }
    uint32_t start = 0;
    uint32_t end = 0;
    uint32_t weight = 0;
    for (uint32_t i = 0; i < num_edges; i++) {
        if (fscanf(infile, "%u\n", &start) != 1) {
            fprintf(stderr, "tsp:  error reading edges\n");
            exit(1);
        }
        if (fscanf(infile, "%u\n", &end) != 1) {
            fprintf(stderr, "tsp:  error reading edges\n");
            exit(1);
        }
        if (fscanf(infile, "%u\n", &weight) != 1) {
            fprintf(stderr, "tsp:  error reading edges\n");
            exit(1);
        }
        graph_add_edge(g, start, end, weight);
    }
    //graph_print(g);
    Path *min = path_create(num_vertices + 1);
    dfs(START_VERTEX, g, p, min);
    //  graph_print(g);
    if (path_distance(min) == 0) {
        fprintf(stderr, "No path found! Alissa is lost!\n");
        return 0;
    }
    path_print(min, outfile, g);
    free(str);
    graph_free(&g);
    path_free(&p);
    path_free(&min);
    return 0;
}
