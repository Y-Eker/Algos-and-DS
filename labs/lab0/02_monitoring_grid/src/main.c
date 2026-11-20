#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MAX_RC 50

typedef enum {
    Horizontal,
    Vertical,
    Right_Down,
    Right_Up,
} Direction;

typedef struct {
    int start_row;
    int start_col;
    Direction direction;
    int length;
    int end_row;
    int end_col;
} Anomalous_Sequence;

int read_data(char* filename, char mat[MAX_RC][MAX_RC], int* rows, int* cols, int* min_len);
void start_search(char mat[MAX_RC][MAX_RC], int i, int j, int rows, int cols, int min_len, Direction dir, int* anomalous_seqs_index, Anomalous_Sequence seqs[MAX_RC*MAX_RC]);
int is_subsequence(Anomalous_Sequence Seq, Anomalous_Sequence seqs[MAX_RC*MAX_RC], int seqs_len);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error! file name should be given as a CLA.\n");
        return 1;
    }

    char *filename = argv[1];
    char mat[MAX_RC][MAX_RC];
    int rows, cols, min_len;
    int res = read_data(filename, mat, &rows, &cols, &min_len);
    if (res != 0) return res;

    Anomalous_Sequence sequences[MAX_RC*MAX_RC] = {0};
    int anomalous_seqs_index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == 'X') {
                start_search(mat, i, j, rows, cols, min_len, Horizontal, &anomalous_seqs_index, sequences);
                start_search(mat, i, j, rows, cols, min_len, Vertical, &anomalous_seqs_index, sequences);
                start_search(mat, i, j, rows, cols, min_len, Right_Down, &anomalous_seqs_index, sequences);
                start_search(mat, i, j, rows, cols, min_len, Right_Up, &anomalous_seqs_index, sequences);
            }
        }
    }

    printf("Anomaly Sequences\n");
    printf("Start row | Start column | End row | End column | Direction | Length\n");
    for (int i = 0; i < anomalous_seqs_index; i++) {
        printf("%d | %d | %d | %d | %d | %d\n", sequences[i].start_row+1,
            sequences[i].start_col+1, sequences[i].end_row+1, sequences[i].end_col+1, sequences[i].direction, sequences[i].length);
    }
    printf("STATS\n");
    printf("Grid size: %d rows x %d cols\n", rows, cols);
    printf("Minimum sequence length: %d\n", min_len);
    printf("Sequences found: %d\n", anomalous_seqs_index);

    return 0;
}

int read_data(char* filename, char mat[MAX_RC][MAX_RC], int *rows, int *cols, int *min_len) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        fprintf(stderr, "Error while accessing input file.\n");
        return 2;
    }

    if (fscanf(fin, " %d %d %d ", rows, cols, min_len) != 3) {
        fprintf(stderr, "Input file format is wrong.\n");
        fclose(fin);
        return 3;
    }
    if (*rows < 1 || *rows > MAX_RC || *cols < 1 || *cols > MAX_RC || *rows + *cols < 3 || *min_len < 2 || *min_len > MAX(*rows, *cols)) {
        fprintf(stderr, "Rows, cols, or min len is invalid.\n");
        fclose(fin);
        return 4;
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(fin, " %c ", &mat[i][j]);
            if (mat[i][j] != '.' && mat[i][j] != 'X') {
                printf("Unidentified element '%c' in indexes R:%d C:%d in the file content.\n", mat[i][j], i, j);
                fclose(fin);
                return 5;
            }
        }
    }
    fclose(fin);
    return 0;
}
void start_search(char mat[MAX_RC][MAX_RC], int i, int j, int rows, int cols, int min_len, Direction dir,
    int* anomalous_seqs_index, Anomalous_Sequence seqs[MAX_RC*MAX_RC]) {

    int len = 0, start_row = i, start_col = j;
    int end_row, end_col;
    if (dir == Horizontal) {
        while (j < cols) {
            if (mat[i][j] == 'X') len++;
            else break;
            j++;
        }
        end_row = i; end_col = j - 1;
    }
    else if (dir == Vertical) {
        while (i < rows) {
            if (mat[i][j] == 'X') len++;
            else break;
            i++;
        }
        end_row = i - 1; end_col = j;
    }
    else if (dir == Right_Down) {
        while (i < rows && j < cols) {
            if (mat[i][j] == 'X') len++;
            else break;
            i++; j++;
        }
        end_row = i - 1; end_col = j - 1;
    }
    else if (dir == Right_Up) {
        while (i >= 0 && j < cols) {
            if (mat[i][j] == 'X') len++;
            else break;
            i--; j++;
        }
        end_row = i + 1; end_col = j - 1;
    }

    if (len >= min_len) {
        Anomalous_Sequence Seq = {start_row, start_col, dir, len, end_row, end_col};
        if (!is_subsequence(Seq, seqs, *anomalous_seqs_index)) {
            seqs[(*anomalous_seqs_index)++] = Seq;
        }
    }
}

int is_subsequence(Anomalous_Sequence Seq, Anomalous_Sequence seqs[MAX_RC*MAX_RC], int seqs_len) {
    for (int i = 0; i < seqs_len; i++) {
        if (seqs[i].direction == Seq.direction) {
            if (seqs[i].direction == Horizontal && seqs[i].start_row == Seq.start_row && Seq.start_col <= seqs[i].end_col && Seq.start_col >= seqs[i].start_col) {
                return 1;
            }
            if (seqs[i].direction == Vertical && seqs[i].start_col == Seq.start_col && Seq.start_row <= seqs[i].end_row && Seq.start_row >= seqs[i].start_row) {
                return 1;
            }
            if (seqs[i].direction == Right_Down && (Seq.start_row - Seq.start_col == seqs[i].start_row - seqs[i].start_col) && Seq.start_row >= seqs[i].start_row && Seq.start_row <= seqs[i].end_row) {
                return 1;
            }
            if (seqs[i].direction == Right_Up && (Seq.start_row + Seq.start_col == seqs[i].start_row + seqs[i].start_col)) {
                if (Seq.start_row <= seqs[i].start_row && Seq.start_row >= seqs[i].end_row) {
                    return 1;
                }
                if (Seq.start_row > seqs[i].start_row && Seq.end_row <= seqs[i].end_row) {
                    seqs[i] = Seq;
                    return 1;
                }
            }
        }
    }
    return 0;
}
