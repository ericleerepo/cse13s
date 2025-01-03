#include "graph.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = calloc(1, sizeof(Path));
    p->vertices = stack_create(capacity);
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        if ((*pp)->vertices) {
            stack_free(&((*pp)->vertices));
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t w = 0;
    (stack_peek(p->vertices, &w));
    if (stack_size(p->vertices) > 0) {
        p->total_weight += graph_get_weight(g, w, val);
    }
    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed = 0;
    if (stack_pop(p->vertices, &removed)) {
    }
    uint32_t new_last = 0;
    stack_peek(p->vertices, &new_last);
    p->total_weight = p->total_weight - graph_get_weight(g, new_last, removed);
    return removed;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    //for (uint32_t i = 0; i< stack_size(src->vertices); i++){
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    fprintf(outfile, "Alissa starts at:\n");
    stack_print(p->vertices, outfile, graph_get_names(g));
    fprintf(outfile, "Total Distance: %u\n", p->total_weight);
}

/*int main(){
	Graph *g = graph_create(10, false);
	Path *p = path_create(10);
	graph_add_vertex(g, "san jose", 0);
	graph_add_vertex(g, "san francisco", 1);
	graph_add_vertex(g, "santa cruz", 2);
	graph_add_edge(g,0, 1, 2);
        graph_add_edge(g,1, 2, 2);	
	printf("%u\n", graph_get_weight(g,0,2));
	path_add(p, 0, g);
	path_print(p, stdout, g);
	path_add(p, 1, g);
	path_print(p, stdout, g);
	path_add(p, 2, g);
	path_print(p, stdout, g);
}*/
