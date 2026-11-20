#include <stdio.h>
#include <stdlib.h>

#define ORGANISM_SIZE 19

typedef struct {
    char sequence[ORGANISM_SIZE + 1];
    int is_alive;
    int generation;
} Organism;

Organism *read_data(char *fin_name, int* n);
void print_data(Organism *organisms, int num_of_organisms, int generation);
int evlove(Organism *organisms, int num_of_organisms, int global_generation);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("argc must be 2\n");
        return 1;
    }
    char *fin_name = argv[1];
    int num_of_organisms;
    Organism *organisms = read_data(fin_name, &num_of_organisms);
    int global_generation = 0;
    print_data(organisms, num_of_organisms, global_generation);
    while (evolve(organisms, num_of_organisms, global_generation)) {
        print_data(organisms, num_of_organisms, global_generation);
        global_generation++;
    }
    return 0;
}

Organism* read_data(char *fin_name, int *n) {
    FILE *fin = fopen(fin_name, "r");
    if (!fin) {
        printf("Error while accessing input file.\n");
        exit(2);
    }
    int num_of_organisms;
    fscanf(fin, "%d", &num_of_organisms);
    *n = num_of_organisms;
    Organism *organisms = (Organism *) malloc(num_of_organisms * sizeof(*organisms));

    for (int i = 0; i < num_of_organisms; i++) {
        fscanf(fin, "%s", organisms[i].sequence);
        organisms[i].is_alive = 1;
        organisms[i].generation = 0;
    }

    fclose(fin);
    return organisms;
}

void print_data(Organism *organisms, int num_of_organisms, int generation) {
    printf("Generation %d:\n", generation);
    for (int i = 0; i < num_of_organisms; i++) {
        if (organisms[i].generation == generation) {
            printf("%s\n", organisms[i].sequence);
        }
    }
}

int evlove(Organism *organisms, int num_of_organisms, int global_generation) {
    for (int i = 0; i < num_of_organisms; i++) {
        int index_of_max_similarity = 0;
        for (int j = 0; j 
    }
}

int calculate_similarity(Organism o1, Organism o2) {
    int result = 0;
    for (int i = 0; i < ORGANISM_SIZE, i++) {
        if (o1.sequence[i] == o2.sequence[i]) result++;
    }
    return result;
}
