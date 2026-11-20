![La Settimana Algoritmica](data/la_settimana_algoritmica_banner.png)

## Problem

The new issue of *La Settimana Algoritmica* is ready!

**La Pagina della Ricorsione** contains four challenges. The reader chooses one
from the page index, the magazine prepares the challenge, and the submitted
algorithm tries to win it.

**Che film è?** asks who will win the sorting race by performing the
fewest comparisons. Quick Sort, Merge Sort, and a freely chosen My Sort receive
the same data. The comparisons recorded by the magazine determine their place
in each race, while the points earned across all races determine the final
winner. In verbose mode, the accompanying story is the plot of a movie to
identify.

## Verbose mode

Pass `--verbose` as a program argument to include the narrative. Running without the option gives the technical presentation. The option
does not change algorithm execution, result checks, or error reporting.

See the Getting Started document for how to set program arguments in CLion.
From a terminal opened in the exercise directory, for example:

```powershell
.\cmake-build-debug\la_settimana_algoritmica.exe --verbose
```

During typewriter output, ENTER displays the rest of the current block at once.
At a pause, another ENTER continues execution; the next narrative block starts
with the typewriter effect again.

**Pauses also occur without `--verbose`. If the console appears to have stopped
at a pause, or only a blinking cursor is visible, press ENTER to continue.**

## Material supplied by the magazine

The project contains the following student-facing files:

```text
src/main.c               magazine index and page navigation
src/recursion.h          contract for the recursion page
src/recursion.c          recursion algorithms to complete
src/sorting.h            contract for the sorting column
src/sorting.c            sorting algorithms to complete
src/rules.h              shared types and ready-to-use framework functions
```

Complete only the operations marked with `TODO` in `src/recursion.c` and
`src/sorting.c`. The declarations and their Doxygen documentation define the
interface used by the magazine and by the tests. Keep the supplied signatures
unchanged.

You may add any helper functions you need in the implementation. Keep helpers
used only within one `.c` file `static`, with their prototypes and definitions
in that file; no header declaration is needed.

The functions declared in `rules.h` are already implemented by the supplied
framework; do not implement or redefine them. Add `#include "rules.h"` to
`src/sorting.c` to use the supplied comparison function. The project already
includes its implementation.

The code under `framework/` manages the issue, prepares the challenges,
loads the datasets, checks the results, and produces the standings. It is
supplied infrastructure, outside the work to complete. Leave it unchanged; its
implementation is not required reading.

## La Pagina della Ricorsione

The reader selects one challenge at a time. After it ends, the magazine
returns to the recursion index. Guess the Card and Towers of Hanoi prepare
a new random challenge each time they are selected.

### The Palindrome Challenge

The magazine presents five real words and sentences. Some are palindromes
and some are not; letter case, spaces, and punctuation may vary.

Only letters participate in the comparison. They must be considered without
case differences, while spaces and punctuation are ignored. A text that does
not contain any letter is not a valid palindrome. The challenge is won only if
every proposed text is classified correctly by a recursive check. The first
wrong or invalid verdict ends the challenge. If memory for text normalization
cannot be allocated, report an error.

### The Secret Code

The magazine provides a decimal access key.
The magazine's secret code is the minimal binary representation of the
decimal access key. The code is written as text, contains no unnecessary
leading zeroes, and is generated recursively. The decimal value zero, which is
also covered by the tests, is represented by `0`.

The door opens only if the generated code exactly matches the expected one:

```text
42 -> 101010
```

### Guess the Card

Cards are first ordered by value:

```text
A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
```

Cards with the same value are ordered by suit:

```text
Hearts > Diamonds > Clubs > Spades
```

Use recursive search to find any secret card within six proposals.
The card interaction is already implemented by the magazine. Call it for every
proposal: it answers whether the secret card is lower, equal to, or higher than
the proposal. The complete deck representation and the organization of the
recursive search remain free choices.

An invalid card or six unsuccessful proposals loses the challenge. Stop when
the interaction rejects a proposal. At the end, the magazine reveals
the secret card and reports the outcome.

### Towers of Hanoi

The magazine randomly chooses from 4 through 8 disks. They initially form a
complete stack on the Tower of Wisdom and must reach the Tower of
Enlightenment, using the Tower of Inner Peace as the auxiliary tower.

The rules are:

- move one disk at a time;
- move only the top disk of a tower;
- never place a larger disk on a smaller disk.

The magazine announces the minimum number of moves, `2^n - 1`.

Your recursive algorithm chooses the sequence of moves. The supplied Hanoi
interaction is already implemented: call it to execute each move. It maintains
the tower state, counts accepted steps, and rejects illegal moves. Stop the
recursive process when a move is rejected.

The challenge is won only if every move is legal and the complete stack reaches
the Tower of Enlightenment in the minimum number of moves. Legal moves beyond
the minimum remain accepted: a complete solution with more moves is reported
as valid but non-optimal. The framework remains silent while solving. On
failure, it explains the rejection or incomplete solution and shows the last
valid state; a larger-on-smaller attempt also shows the attempted configuration.

The algorithm itself must also support the smaller cases from 1 through 3 disks
used by the tests.

## Che film è?

Quick Sort and Merge Sort must use their recursive forms. My Sort may use any
sorting strategy, including a variation of one of the other competitors.

The magazine supplies four datasets:

| File | Data presented to the competitors |
| --- | --- |
| `data/random.txt` | unordered values |
| `data/sorted.txt` | values already in ascending order |
| `data/reverse.txt` | values in descending order |
| `data/duplicates.txt` | values with many repetitions |

Every competitor receives an independent copy of the same dataset. At the end
of a run, the magazine checks the entire resulting array. Failure, incorrect
ascending order, or changed input values or multiplicities disqualifies the
competitor from that round. This validation does not affect the comparison
count.

The official comparison function is already implemented by the magazine.
Call it for every comparison between sortable values. The magazine counts only
the calls made through that function.
For each correct result, this count determines the competitor's position in
the current round: the valid algorithm
with the fewest recorded comparisons wins that race. A competitor with zero
recorded comparisons is disqualified from the round.

### Standings

Valid competitors are ranked by increasing comparison count:

```text
1st place -> 3 points
2nd place -> 2 points
3rd place -> 1 point
```

Equal counts share the same position and points, and the following positions
may be skipped. The final standings add the points obtained on all four
datasets. Equal final totals share the same position and, at the top of the
standings, share the victory.

If all competitors are disqualified in one race, the competition ends without
running later datasets. Otherwise, results and cumulative standings follow
each round.

The result describes this particular competition: its datasets, its chosen
implementations, and the comparisons recorded by the magazine.

## Tests

The supplied Unity tests check the observable behavior of every algorithm on
normal and boundary cases. Card proposals and Hanoi moves are evaluated by the
same interactions used by the magazine. Sorting tests inspect the complete
resulting arrays without imposing a private decomposition.

One test checks that the operations that acquire memory release every block
they acquired.

Run the tests incrementally while completing the two modules. The prepared test
procedure is described in the Getting Started document.

## Behind the standings

The sorting race is also an invitation to modify one decision at a time and
observe how the standings change while the datasets remain fixed.

For Quick Sort, useful variants include:

- choosing the first, last, central, random, or median-of-three value as pivot;
- organizing the partition using Lomuto's or Hoare's scheme;
- deciding how values equal to the pivot are distributed;
- comparing the effect of ordered, reverse-ordered, and duplicate-heavy data.

For Merge Sort, the results may be influenced by:

- reusing one work area or preparing temporary storage during each merge;
- the amount of data copied between the original and temporary arrays;
- how equal values are selected from the two ordered portions;
- avoiding work that is unnecessary for portions already in the desired order.

My Sort can be used as a control algorithm, as a different sorting family, or
as a variation designed for one particular kind of dataset. Comparisons remain
meaningful only when every variant receives the same values and reports each
value comparison through the magazine's official interaction.

The number of recorded comparisons is not an absolute performance benchmark.
It deliberately isolates one aspect of the algorithms and does not measure,
for example, elapsed time, memory use, assignments, or data movement. This
magazine uses it as a common reference parameter so that the experiments remain
focused and comparable.
