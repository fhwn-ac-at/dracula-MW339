#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Colors for prints
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

typedef struct {
    int from;
    int to;
} Jump;

typedef struct {
    int* transitions;  // dyn. allocation for each dice face
} Node;

// Default Values
int board_size = 100; int dice_sides = 6; int max_steps = 1000; int simulations = 10000;

Jump* snakes; Jump* ladders; int num_snakes = 0; int num_ladders = 0;

Node* graph;
int* snake_usage; int* ladder_usage; int total_rolls = 0; int total_wins = 0; int min_rolls = 0;
int* min_sequence; int min_sequence_len = 0;

void sleep_timer(int milliseconds) {
    usleep(milliseconds * 1000);
}

void print_slow(const char* text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; ++i) {
        putchar(text[i]);
        fflush(stdout);
        sleep_timer(delay_ms);
    }
}

void dots(int count, int delay_ms) {
    for (int i = 0; i < count; ++i) {
        printf(".");
        fflush(stdout);
        sleep_timer(delay_ms);
    }
    printf("\n");
}

int is_jump_start(int pos, Jump* jumps, int count) {
    for (int i = 0; i < count; ++i)
        if (jumps[i].from == pos) return jumps[i].to;
    return -1;
}

void build_graph() {
    for (int i = 0; i < board_size; ++i) {
        graph[i].transitions = malloc(dice_sides * sizeof(int));
        if (graph[i].transitions == NULL) {
            fprintf(stderr, RED "Malloc failed on Graph Building.\n" RESET);
            exit(EXIT_FAILURE);
        }
        for (int d = 1; d <= dice_sides; ++d) {
            int next = i + d;
            if (next >= board_size) {
                graph[i].transitions[d - 1] = i;
                continue;
            }

            int jump_to = is_jump_start(next, snakes, num_snakes);
            if (jump_to != -1) {
                graph[i].transitions[d - 1] = jump_to;
                continue;
            }

            jump_to = is_jump_start(next, ladders, num_ladders);
            if (jump_to != -1) {
                graph[i].transitions[d - 1] = jump_to;
                continue;
            }

            graph[i].transitions[d - 1] = next;
        }
    }
}

void simulate_game() {
    int pos = 0, steps = 0;
    int* roll_sequence = malloc(max_steps * sizeof(int));
    if (roll_sequence == NULL) {
        fprintf(stderr, RED "Malloc failed on Simulating game.\n" RESET);
    }

    while (pos < board_size - 1 && steps < max_steps) {
        int roll = (rand() % dice_sides) + 1;
        roll_sequence[steps++] = roll;

        int next = graph[pos].transitions[roll - 1];

        if (next != pos + roll) {
            if (is_jump_start(pos + roll, snakes, num_snakes) != -1)
                snake_usage[pos + roll]++;
            else if (is_jump_start(pos + roll, ladders, num_ladders) != -1)
                ladder_usage[pos + roll]++;
        }

        pos = next;
    }

    if (pos == board_size - 1) {
        total_wins++;
        total_rolls += steps;

        if (min_rolls == 0 || steps < min_rolls) {
            min_rolls = steps;
            min_sequence_len = steps;
            for (int i = 0; i < steps; ++i) {
                min_sequence[i] = roll_sequence[i];
            }
        }
    }

    free(roll_sequence);
}

void run_simulations() {
    for (int i = 0; i < simulations; ++i)
        simulate_game();
}

void print_stats() {
    printf(RED"\n --->Simulation Stats<---\n"RESET);
    printf("Board size: %d, Amount of Die sides: %d\n", board_size, dice_sides);
    printf("Number of Simulations run: %d\n", simulations);
    printf("Number of Wins: %d (%.2f%%)\n", total_wins, 100.0 * total_wins / simulations);
    printf(RED"\n --->Dice Stats<---\n"RESET);
    if (total_wins > 0) {
        printf("Average rolls to win the game: %.2f\n", (double)total_rolls / total_wins);
        printf("Shortest win in this simulation in %d rolls: ", min_rolls);
        for (int i = 0; i < min_sequence_len; ++i) {
            printf("%d ", min_sequence[i]);
        }
        printf("\n");
    }

    printf(RED"\n --->Snakes / Ladders Stats<---\n"RESET);
    printf("Snakes Used:\n");
    for (int i = 0; i < board_size; ++i) {
        if (snake_usage[i] > 0)
            printf("  >>> Snake at field " GREEN"%d "RESET "used "GREEN"%d "RESET"times in total\n", i, snake_usage[i]);
    }

    printf("Ladders Used:\n");
    for (int i = 0; i < board_size; ++i) {
        if (ladder_usage[i] > 0)
            printf("  >>> Ladder at field " GREEN"%d "RESET "used " GREEN"%d "RESET "times in total\n", i, ladder_usage[i]);
    }
}

int conflicting(int from, int to) {
    if (from == to || from >= board_size - 1)
        return 1;

    for (int i = 0; i < num_snakes; ++i)
        if (snakes[i].from == from || snakes[i].to == to)
            return 1;

    for (int i = 0; i < num_ladders; ++i)
        if (ladders[i].from == from || ladders[i].to == to)
            return 1;

    return 0;
}

void parse_args(int argc, char* argv[]) {
    snakes = malloc(argc * sizeof(Jump));
    if (snakes == NULL) {
        fprintf(stderr, RED "Malloc failed on Snakes.\n" RESET);
        exit(EXIT_FAILURE);
    }
    ladders = malloc(argc * sizeof(Jump));
    if (ladders == NULL) {
        fprintf(stderr, RED "Malloc failed on Ladders.\n" RESET);
        exit(EXIT_FAILURE);
    }
    int SnakeLadderErrorFlag = 0;

    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--size") == 0)
            board_size = atoi(argv[++i]);
        else if (strcmp(argv[i], "--sides") == 0)
            dice_sides = atoi(argv[++i]);
        else if (strcmp(argv[i], "--steps") == 0)
            max_steps = atoi(argv[++i]);
        else if (strcmp(argv[i], "--runs") == 0)
            simulations = atoi(argv[++i]);
        else if (strcmp(argv[i], "--snakes") == 0) {
            while (i + 2 < argc && argv[i + 1][0] != '-' && argv[i + 2][0] != '-') {
                int from = atoi(argv[++i]);
                int to = atoi(argv[++i]);
                if (!conflicting(from, to)) {
                    snakes[num_snakes++] = (Jump){from, to};
                } else {
                    printf("Invalid Snake(s): %d -> %d\n", from, to);
                    SnakeLadderErrorFlag = 1;
                }
            }
        } else if (strcmp(argv[i], "--ladders") == 0) {
            while (i + 2 < argc && argv[i + 1][0] != '-' && argv[i + 2][0] != '-') {
                int from = atoi(argv[++i]);
                int to = atoi(argv[++i]);
                if (!conflicting(from, to)) {
                    ladders[num_ladders++] = (Jump){from, to};
                } else {
                    printf("Invalid Ladder(s): %d -> %d\n", from, to);
                    SnakeLadderErrorFlag = 1;
                }
            }
        }
    }

    if ((num_snakes == 0 && num_ladders == 0) || SnakeLadderErrorFlag || board_size <= 0 || dice_sides <= 0 || max_steps <= 0 || simulations <= 0) {
        printf(RED "Invalid inputs. Exiting Simulation.\n" RESET);
        exit(1);
    }

    graph = malloc(board_size * sizeof(Node));
    if (graph == NULL) {
        fprintf(stderr, RED "Malloc failed on Graph.\n" RESET);
        exit(EXIT_FAILURE);
    }
    snake_usage = calloc(board_size, sizeof(int));
    if (snake_usage == NULL) {
        fprintf(stderr, RED "Malloc failed on Snake Usage.\n" RESET);
        exit(EXIT_FAILURE);
    }
    ladder_usage = calloc(board_size, sizeof(int));
    if (ladder_usage == NULL) {
        fprintf(stderr, RED "Malloc failed on Ladder Usage.\n" RESET);
        exit(EXIT_FAILURE);
    }
    min_sequence = malloc(max_steps * sizeof(int));
    if (min_sequence == NULL) {
        fprintf(stderr, RED "Malloc failed on Steps.\n" RESET);
        exit (EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    print_slow("Processing CLI arguments", 50); dots(3, 300);
    parse_args(argc, argv);

    print_slow("Building graph", 50); dots(3, 300);
    build_graph();

    print_slow("Running simulations", 50); dots(3, 300);
    run_simulations();

    print_slow("Displaying results", 50); dots(3, 300);
    print_stats();

    for (int i = 0; i < board_size; ++i) {
        free(graph[i].transitions);
    }

    free(graph); free(snakes); free(ladders); free(snake_usage); free(ladder_usage); free(min_sequence);

    return 0;
}
