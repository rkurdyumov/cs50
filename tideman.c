#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            } else if (preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void merge(int first, int mid, int last) {
    int curr_left = first;
    int curr_right = mid + 1;
    int num_elems = last - first + 1;
    pair merged[num_elems];
    int i = 0;
    while (curr_left <= mid || curr_right <= last) {
        int left_pref = preferences[pairs[curr_left].winner][pairs[curr_left].loser];
        int right_pref = preferences[pairs[curr_right].winner][pairs[curr_right].loser];
        if (right_pref > left_pref) {
            merged[i].winner = pairs[curr_right].winner;
            merged[i].loser = pairs[curr_right].loser;
            curr_right++;
        } else {
            merged[i].winner = pairs[curr_left].winner;
            merged[i].loser = pairs[curr_left].loser;
            curr_left++;
        }
        i++;
    }
    for (int j = 0; j < num_elems; j++) {
        pairs[first + j] = merged[j];
    }
}

void merge_sort_recursive(int min, int max) {
    if (min == max) {
        return;
    } else {
        int mid = (min + max) / 2;
        merge_sort_recursive(min, mid);
        merge_sort_recursive(mid + 1, max);
        merge(min, mid, max);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort_recursive(0, pair_count - 1);
}

bool is_path(int origin, int dest) {
    if (locked[origin][dest]) {
        return true;
    }
    for (int i = 0; i < candidate_count; i++) {
        if (locked[origin][i] && is_path(i, dest)) {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        if (!is_path(pairs[i].loser, pairs[i].winner)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        int edges_to = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                edges_to++;
            }
        }
        if (edges_to == 0) {
            printf("%s\n", candidates[i]);
        }
    }
}
