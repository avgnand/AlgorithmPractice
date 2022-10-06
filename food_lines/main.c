#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This small program is my attempt at solving an algorithm problem (called "Food Lines") presented in the book 
 * "Algorithmic Thinking" by Daniel Zingaro (No Starch Press). The prompt for the problem can be summarized as follows:
 * There are N-number of lines of people waiting to get food, and M-number of people about to join the lines. 
 * The goal of this program is to determine the length of the shortest line for each of the M people about to line up. 
 * As each new person joins a line, the next person must find the shortest line. 
 * An example case is given below to test for accuracy, however the prompt for this problem states that 
 * the number of lines as well as the number of new people to line up will not exceed 100 each. 
 * Also, a successful program for this problem should produce output in less than 3 seconds. 
 * Output is in the form of a number printed on a line for each person lining up.
 * 
 * * Note: This program is only meant to follow the algorithmic aspect of the problem, with less focus on the input and output format.
 * 
 * * Example: 3 4 | 3 2 5 -> 2 3 3 4
 * * N = 3, M = 4; Line lengths are 3, 2, 5; The shortest lines joined are given
*/

#define PROB_N 3
#define PROB_M 4
#define PROB_MAX 100

int get_shortest_line_len(const int* lines, const int sz) {
    int low = *lines;
    for (int i = 0; i < sz; i++) {
        int x = *(lines + i);
        if (x < low) {
            low = x;
        }
    }
    return low;
}

int get_shortest_line_first_index(const int val, const int* lines, const int sz) {
    for (int i = 0; i < sz; i++) {
        int x = *(lines + i);
        if (x != val) {
            continue;
        } else { // found first match
            return i;
        }
    }
    return -1;
}

void queue_people(int* results, const int amt, int* lines, const int sz) {
    for (int i = 0; i < amt; i++) {
        int shortest  = get_shortest_line_len(lines, sz);
        int place     = get_shortest_line_first_index(shortest, lines, sz);
        *(results + i)    = shortest;
        *(lines + place) += 1;
    }
}

void produce_output(int* results) {
    int* start = results;
    while (*results != 0) {
        printf("%d\n", *results);
        results++;
    }
    results = start;
    puts("End of output...\n");
}

int main() {
    int lines[]   = {3,2,5};
    int results[PROB_MAX] = {0};
    queue_people(results, PROB_M, lines, PROB_N);
    produce_output(results);
    printf("%d, %d, %d", lines[0], lines[1], lines[2]);
    return 0;
}