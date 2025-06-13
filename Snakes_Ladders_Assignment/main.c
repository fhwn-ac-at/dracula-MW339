#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Limits for now, might be removed later
#define MAX_SIZE 1000
#define MAX_DIE 20
#define MAX_STEPS 10000
#define MAX_JUMPS 100
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

typedef struct {
    int from;
    int to;
} Jump;

typedef struct {
    int transitions[MAX_DIE];  // one for each die face
} Node;

// Default Values
int board_size = 100;
int die_sides = 6;
int max_steps = 1000;
int simulations = 10000;


Jump snakes[MAX_JUMPS];
Jump ladders[MAX_JUMPS];
int num_snakes = 0;
int num_ladders = 0;

Node graph[MAX_SIZE];

int snake_usage[MAX_SIZE] = {0};
int ladder_usage[MAX_SIZE] = {0};
int total_rolls = 0;
int total_wins = 0;
int min_rolls = MAX_STEPS;
int min_sequence[MAX_STEPS];
int min_sequence_len = 0;

/// Print functions for main ///
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
/// end of print functions for main ///

// Helpers
int is_jump_start(int pos, Jump* jumps, int count) {
    for (int i = 0; i < count; ++i)
        if (jumps[i].from == pos) return jumps[i].to;
    return -1;
}

void build_graph() {
    for (int i = 0; i < board_size; ++i) {
        for (int d = 1; d <= die_sides; ++d) {
            int next = i + d;
            if (next >= board_size) {
                graph[i].transitions[d - 1] = i;  // cant move
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

/*void printgraph() {
    printf("\n++++ Board Graph Visualization ++++\n");
    for (int i = 0; i < board_size; ++i) {
        printf("Square %d:\n", i);
        for (int d = 0; d < die_sides; ++d) {
            int destination = graph[i].transitions[d];
            printf("  On roll %d → %d", d + 1, destination);

            // Optional: mark jump types
            if (destination < i + d + 1)
                printf(" (Snake)");
            else if (destination > i + d + 1)
                printf(" (Ladder)");

            printf("\n");
        }
    }
} */ //Commented out for now, maybe used in future usage. Just too bloated at the moment with the simulation showing.



void simulate_game() {
    int pos = 0, steps = 0;
    int roll_sequence[MAX_STEPS];

    while (pos < board_size - 1 && steps < max_steps) {
        int roll = (rand() % die_sides) + 1;
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

        if (steps < min_rolls) {
            min_rolls = steps;
            min_sequence_len = steps;
            for (int i = 0; i < steps; ++i) {
                min_sequence[i] = roll_sequence[i];
            }
        }
    }
}

void run_simulations() {
    for (int i = 0; i < simulations; ++i)
        simulate_game();
}

void print_stats() {
    printf(RED"\n --->Simulation Stats<---\n"RESET);
    printf("Board size: %d, Amount of Die sides: %d\n", board_size, die_sides);
    printf("Number of Simulations run: %d\n", simulations);
    printf("Number of Wins: %d (%.2f%%)\n", total_wins, 100.0 * total_wins / simulations);
    printf(RED"\n --->Dice Roll Statistics<---\n"RESET);
    if (total_wins > 0) {
        printf("Average rolls to win the game: %.2f\n", (double)total_rolls / total_wins);
        printf("Shortest win in this simulation in %d rolls: ", min_rolls);
        for (int i = 0; i < min_sequence_len; ++i) {
            printf("%d ", min_sequence[i]);
        }
        printf("\n");
    }

    printf(RED"\n --->Snakes / Ladders Stats<---\n"RESET);

    printf("Snake Usage:\n");
    for (int i = 0; i < board_size; ++i) {
        if (snake_usage[i] > 0)
            printf("  Snake at field %d used %d times in total\n", i, snake_usage[i]);
    }

    printf("Ladder Usage:\n");
    for (int i = 0; i < board_size; ++i) {
        if (ladder_usage[i] > 0)
            printf("  Ladder at field %d used %d times in total\n", i, ladder_usage[i]);
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


/* Hardcoded Snakes and Ladders to test, deprecated for now

void add_default_jumps() {
    // Example configuration
    snakes[num_snakes++] = (Jump){97, 78};
    snakes[num_snakes++] = (Jump){95, 56};
    snakes[num_snakes++] = (Jump){88, 24};

    ladders[num_ladders++] = (Jump){3, 51};
    ladders[num_ladders++] = (Jump){6, 27};
    ladders[num_ladders++] = (Jump){20, 70};
}
*/

void parse_args(int argc, char* argv[]) {
    int SnakeLadderErrorFlag = 0; //flag to set if provided ladders and snakes are not within the size boundaries to terminate program

    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--size") == 0)
            board_size = atoi(argv[++i]);
        else if (strcmp(argv[i], "--sides") == 0)
            die_sides = atoi(argv[++i]);
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
                    printf("Invalid Snake positions at %d to %d - conflict or invalid input. Please check your inputs\n", from, to);
                    SnakeLadderErrorFlag = 1;
                }
            }
        }
        else if (strcmp(argv[i], "--ladders") == 0) {
            while (i + 2 < argc && argv[i + 1][0] != '-' && argv[i + 2][0] != '-') {
                int from = atoi(argv[++i]);
                int to = atoi(argv[++i]);

                if (!conflicting(from, to)) {
                    ladders[num_ladders++] = (Jump){from, to};
                } else {
                    printf("Invalid Ladder positions at %d to %d - conflict or invalid input. Please check your inputs\n", from, to);
                    SnakeLadderErrorFlag = 1;
                }
            }
        }
    }

    if ((num_snakes == 0 && num_ladders == 0) || SnakeLadderErrorFlag) {
        printf("Error: Snakes and or Ladders provided are invalid. Terminating Simulation.\n");
        exit(1);
    }

    if (board_size > MAX_SIZE || die_sides > MAX_DIE || max_steps > MAX_STEPS) {
        printf("Error - not within limits.\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    print_slow("Command Line Interface Inputs are being processed", 50);
    dots(5, 300);
    parse_args(argc, argv);
    print_slow("Processed arguments:\n", 40);

    char buffer[100];
    sprintf(buffer, "  -> Board size (Amount of Squares): %d\n", board_size);
    print_slow(buffer, 30);
    sprintf(buffer, "  -> Dice side amount (Amount of Dice Sides): %d\n", die_sides);
    print_slow(buffer, 30);
    sprintf(buffer, "  -> Maximum number of steps (Number of allowed rolls): %d\n", max_steps);
    print_slow(buffer, 30);
    sprintf(buffer, "  -> Amount of Simulations to run: %d\n", simulations);
    print_slow(buffer, 30);
    print_slow("Snakes:\n", 30);
    for (int i = 0; i < num_snakes; ++i) {
        sprintf(buffer, "  -> Snake from %d to %d\n", snakes[i].from, snakes[i].to);
        print_slow(buffer, 20);
    }
    print_slow("Ladders:\n", 30);
    for (int i = 0; i < num_ladders; ++i) {
        sprintf(buffer, "  -> Ladder from %d to %d\n", ladders[i].from, ladders[i].to);
        print_slow(buffer, 20);
    }

    print_slow("Assembling Graph", 50);
    dots(5, 300);
    build_graph();

    print_slow("Running Simulations", 50);
    dots(5, 300);
    run_simulations();
    //printgraph();

    print_slow("Retrieving Simulation Results and Values", 50);
    dots(5, 300);
    print_stats();

    return 0;
}
