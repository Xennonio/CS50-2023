#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int pair_count,
candidate_count,
first;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool nocycles_check(int los);
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
      preferences[i][j] = 0;
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
  bool vote_check = false;

  for(int i = 0; i < candidate_count; i++)
  {
    if(strcmp(candidates[i], name) == 0)
    {
      ranks[rank] = i;
      vote_check = true;
    }
  }

  return vote_check;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
  for(int i = 0; i < candidate_count; i++)
  {
    for(int j = 0; j < candidate_count; j++)
    {
      preferences[ranks[i]][j] += 1;
    }
    // j != ranks[0] && j != ranks[1] && ... && j != ranks[i]
    for(int k = 0; k <= i; k++)
    {
      preferences[ranks[i]][ranks[k]] += -1;
    }
  }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
  for(int i = 0; i < candidate_count; i++)
  {
    for(int j = i; j < candidate_count; j++)
    {
      if(preferences[i][j] > preferences[j][i])
      {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
      if(preferences[j][i] > preferences[i][j])
      {
        pairs[pair_count].winner = j;
        pairs[pair_count].loser = i;
        pair_count++;
      }
    }
  }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
  for(int i = 0; i < pair_count - 2; i++)
  {
    for(int j = 0; j < pair_count - i; j++)
    {
      int tmpwin1 = pairs[j].winner;
      int tmplos1 = pairs[j].loser;
      int tmpwin2 = pairs[j + 1].winner;
      int tmplos2 = pairs[j + 1].loser;
      int strenght1 = preferences[tmpwin1][tmplos1] - preferences[tmplos1][tmpwin1];
      int strenght2 = preferences[tmpwin2][tmplos2] - preferences[tmplos2][tmpwin2];
      if(strenght1 <= strenght2)
      {
        int tmpwin = pairs[j].winner;
        int tmplos = pairs[j].loser;
        pairs[j].winner = pairs[j + 1].winner;
        pairs[j].loser = pairs[j + 1].loser;
        pairs[j + 1].winner = tmpwin;
        pairs[j + 1].loser = tmplos;
      }
    }
  }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
  for(int i = 0; i < pair_count; i++)
  {
    first = pairs[i].winner;
    if(nocycles_check(pairs[i].loser))
    {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }
}

// Print the winner of the election
void print_winner(void)
{
  int winner;

  for(int i = 0; i < candidate_count; i++)
  {
    bool winner_check = false;

    for(int j = 0; j < candidate_count; j++)
    {
      if(locked[j][i] == true)
      {
        winner_check = true;
      }

      if(winner_check == false)
      {
        winner = i;
      }
    }
  }

  printf("%s\n", candidates[winner]);
}

bool nocycles_check(int los)
{
/*
(win, los):
first := win

nocycles_check(los)
  if(∃next s.t. los -> next)
    for(next, los -> next)
      if x == first
        return false
      else
        nocycles_check(next)
  else
    return true
*/

  int *nexts = malloc(sizeof(int)*candidate_count);
  int k = 0,
  v_wo_cycle = 0;

  bool exist_check = false;
  for(int i = 0; i < candidate_count; i++)
  {
    if(locked[los][i] == true)
    {
      exist_check = true;
      *(nexts + k) = i;
      k++;
    }
  }

  if(exist_check)
  {
    for(int i = 0; i < k; i++)
    {
      // If you find at least one cycle, then you can return false
      if(*(nexts + i) == first)
      {
        return false;
      }
      // Count the number of nexts that doesn't make a cycle
      if(nocycles_check(*(nexts + i)))
      {
        v_wo_cycle++;
      }
    }
    // If every next doesn't make a cycle, return true, else false
    return v_wo_cycle == k;
  }
  // For vertices that doesn't have a next
  return true;
}