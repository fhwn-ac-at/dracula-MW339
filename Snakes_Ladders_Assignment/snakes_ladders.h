

#ifndef SNAKES_LADDERS_H
#define SNAKES_LADDERS_H


#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

// struct for snake or ladder from pos square -> to pos square on the board
typedef struct {
    int from;
    int to;
} Jump;

typedef struct {
    int* transitions;
} Node;

extern int board_size, dice_sides, max_steps, simulations;
extern Jump* snakes, *ladders;
extern int num_snakes, num_ladders; //array for snakes / ladders jumps
extern Node* graph;
extern int* snake_usage, *ladder_usage;
extern int total_rolls, total_wins, min_rolls, *min_sequence, min_sequence_len;

void sleep_timer(int milliseconds); //output delay for prints
void print_slow(const char* text, int delay_ms); //slow printing char by char so it looks more "calculaty"
void dots(int count, int delay_ms); //just prints dots to simulate loading
int is_jump_start(int pos, Jump* jumps, int count); // checks if pos. is a beginning ladder or snake
void build_graph(); // creates graph with trans. and jumps
void simulate_game(); // simulates one game
void run_simulations(); // runs all games
void print_stats(); // prints all sim statistics at the end of the simulations
int conflicting(int from, int to); //check if any snakes or ladders are conflicting with existing or new ones
void parse_args(int argc, char* argv[]); // parses args from CLI and allocs memory



#endif //SNAKES_LADDERS_H
