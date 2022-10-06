#include <stdio.h>

/**
 * This program is made to solve the algorithm problem "Unique Snowflakes" from the book 
 * "Algorithmic Thinking" by Daniel Zingaro (No Starch Press). The current version does not attempt to 
 * handle formatted input/output, but focus on the algorithm itself. A summary of the problem is as follows:
 * You are presented with an integer N (equal to a number between 1~100,000) followed by N-number of lines of integers 
 * (each between 0~10,000,000). The original problem sets each line to have 6 integers, however this program allows 
 * for any number, via the NUM_ARMS macro. These integers represent lengths of each of the arms of a snowflake. 
 * The goal of the algorithm is to find at least two such snowflakes whose arms match given a rotation of one relative to the other. 
 * In other words, starting on one arm of a snowflake and noting each arm length going clockwise around will 
 * produce a series of numbers that can be compared to another snowflake, similarly starting on one arm 
 * and rotating either clockwise or vice versa.
 * 
 * * Example: A and B are 6-armed snowflakes
 * ____A_____ | _____B____
 *   5 - 6    |    3 - 2  
 * 4 - * - 1  |  4 - * - 1 
 *   3 - 2    |    5 - 6  
 * * Starting at arm '1' and rotating clockwise for A, counter-clockwise for B, produces the same series of arm lengths.
*/

int sum_snowflake(int* s, int sz) {
    int sum = 0;
    for (int i = 0; i < sz; i++) {
        int x = *(s + i);
        sum += x;
    }
    return sum;
}

int compare_sums(int* s1, int* s2, int sz) {
    int a = sum_snowflake(s1, sz);
    int b = sum_snowflake(s2, sz);
    return (a == b) ? 1 : 0;
}

// checks that set of numbers from s1 is within s2
int compare_sets_halfway(int* s1, int* s2, int sz1, int sz2) {
    for (int i = 0; i < sz1; i++) {
        int n = *(s1 + i);
        for (int j = 0; j < sz2; j++) {
            int m = *(s2 + j);
            if (m == n) { // a match
                break;
            }
            if (j == sz2 - 1 && m != n) {
                return 0; // no match possible
            }
        }
    }
    return 1; // all nums in s1 are in s2
}

// compares sets both ways
int compare_sets_full(int* sA, int* sB, int szA, int szB) {
    int p = compare_sets_halfway(sA, sB, szA, szB);
    int q = compare_sets_halfway(sB, sA, szB, szA);
    if (p && q) return 1;
    return 0;
}

// get the index in s2 of the value that matches the first value in s1
int get_offset(int* s1, int* s2, int sz) {
    int a = *s1;
    for (int i = 0; i < sz; i++) {
        int b = *(s2 + i);
        if (b == a) return i;
    }
    return -1; // failure
}

// given offset and direction as well as destination array, produce new array showing rotation
void create_rotation(int* dest, int* s, int sz, int offset, int clockwise) {
    int time = sz;
    while (time-- > 0) {
        int i = offset;
        int x = *(s + i);
        int j = 0;
        *(dest + j) = x;
        j++;
        if (clockwise) i = (i + 1) % sz;
        else i = (i - 1) % sz;
    }
}

// compare two "rotations" (int arrays), element per element, to check if they match
int compare_rotations(int* r1, int* r2, int sz) {
    for (int i = 0; i < sz; i++) {
        int a = *(r1 + i);
        int b = *(r2 + i);
        if (a != b) return 0;
    }
    return 1;
}

// for each combination of rotation directions of the two snowflakes, compare rotations
int compare_rotation_sets(int* s1, int* dest1, int* s2, int* dest2, int sz) {
    int offset = get_offset(s1, s2, sz);

    // LL
    create_rotation(dest1, s1, sz, 0, 1);
    create_rotation(dest2, s2, sz, offset, 1);
    if (compare_rotations(dest1, dest2, sz)) {
        return 1;
    }
    // LR
    create_rotation(dest1, s1, sz, 0, 1);
    create_rotation(dest2, s2, sz, offset, -1);
    if (compare_rotations(dest1, dest2, sz)) {
        return 1;
    }
    // RL
    create_rotation(dest1, s1, sz, 0, -1);
    create_rotation(dest2, s2, sz, offset, 1);
    if (compare_rotations(dest1, dest2, sz)) {
        return 1;
    }
    // RR
    create_rotation(dest1, s1, sz, 0, -1);
    create_rotation(dest2, s2, sz, offset, -1);
    if (compare_rotations(dest1, dest2, sz)) {
        return 1;
    }

    return 0;
}

int solve(int n, int** lines, int sz, int* dest1, int* dest2) {
    for (int i = 0; i < n; i++) {
        int* x = *(lines + i);
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            int* y = *(lines + j);
            int p = compare_sums(x, y, sz);
            int q = compare_sets_full(x, y, sz, sz);
            int r = compare_rotation_sets(x, dest1, y, dest2, sz);
            if (p && q && r) return 1;
        }
    }
    return 0;
}

#define NUM_ARMS 6

int main() {
    int count = 4;
    int* lines[4];
    int l1[] = {1,2,3,4,5,6};
    int l2[] = {3,1,2,4,5,6};
    int l3[] = {3,2,1,6,5,4}; // matches l1
    int l4[] = {2,4,6,3,2,1};
    lines[0] = l1;
    lines[1] = l2;
    lines[2] = l3;
    lines[3] = l4;
    int dst1[NUM_ARMS] = {0};
    int dst2[NUM_ARMS] = {0};
    int solution = solve(count, lines, NUM_ARMS, dst1, dst2);
    if (solution) puts("Match found!\n");
    else puts("No matches found.\n");
    return 0;
}