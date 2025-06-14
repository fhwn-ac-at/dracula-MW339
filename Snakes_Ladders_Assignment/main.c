#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snakes_ladders.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    print_slow("Processing CLI arguments", 50); dots(5, 300);
    parse_args(argc, argv);

    print_slow("Building graph", 50); dots(5, 300);
    build_graph();

    print_slow("Running simulations", 50); dots(5, 300);
    run_simulations();

    print_slow("Displaying results", 50); dots(5, 300);
    print_stats();

    // free all transitions for every square on the created game board
    for (int i = 0; i < board_size; ++i) {
        free(graph[i].transitions);
    }

    free(graph); free(snakes); free(ladders); free(snake_usage); free(ladder_usage); free(min_sequence);

    return 0;
}