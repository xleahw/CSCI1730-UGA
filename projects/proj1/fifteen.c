#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define BOARD_MIN 3
#define BOARD_MAX 9

int tileRow;
int tileCol;
int dimension;
int newRow = -1;
int newCol = -1;

int board[BOARD_MIN][BOARD_MAX];

// Function Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
int move(int tile);
int won(void);

int main(int argc, char* argv[]) {

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dimension = atoi(argv[1]);
    if (dimension < BOARD_MIN || dimension > BOARD_MAX) {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            BOARD_MIN, BOARD_MIN, BOARD_MAX, BOARD_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL) {
        return 3;
    }

    // Greet user
    greet();

/**
 * Call function to initialize board
 */
    init();

    // Accepts moves until game is won
    while (1) {
        clear();
        draw();

        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                fprintf(file, "%i", board[i][j]);
                if (j < dimension - 1) {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // Check for win
        if (won())
        {
            printf("win!\n");
            break;
        }

        // Prompt for move
        printf("Tile to move (0 to exit): ");
        int tile;
                scanf("%d", &tile);
                getchar();

        // Quit if user inputs 0
        if (tile == 0)
        {
            break;
        }

        // Log move
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // Sleep thread
        usleep(50000);
    }

    // Close log
    fclose(file);

    return 0;
}

//Clears screen using ANSI escape sequences.
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * This function intiializes the game board. It will fill the game board with the value of tiles.
 *
 */
void init(void) {
    int tiles = (dimension * dimension)-1;

        for (int i = 0; i < dimension; i++){
                for(int j = 0;j < dimension; j++){
                        board[i][j] = tiles--;
                }
        }

    /**
     * In case the board contains an odd number of tiles,
     * The position of tiles numbered 1 through 2 are swapped. This
     * ensures even tile dimensions.
     */
        if(!((dimension * dimension) %2 == 0)){
                board[dimension - 1][dimension-2] = 2;
                board[dimension - 1][dimension - 3] = 1;
        }

}

void draw(void) {
    // Prints current state of board
  for(int i=0;i < dimension;i++) {

        for(int j=0;j < dimension;j++){
                if(board[i][j] == 0){printf(" _ ");}
                else{printf(" %d ", board[i][j]);}
        }

    printf("\n");

  }
}

/**
 * The function will first check the value of tile the player wants to move to
 * and if it is a valid spot, the program will move accordingly.
 *
 */
int move(int tile) {

        if(tile <= 0 || tile > (dimension * dimension)) {
        return 0;
    }

        for (int i=0; i < dimension; i++) {
                for (int j=0;j < dimension; j++) {
                        if(board[i][j] == tile) {
                                tileRow = i;
                                tileCol = j;
                        }
                }
        }

    if (newRow == -1 || newCol == -1) {
        return 0;
    }

    if(tileCol+1 <= dimension - 1 && board[tileRow][tileCol+1] == 0) {
        newRow = tileRow;
        newCol = tileCol+1;
    }

    if(tileCol-1 >= 0 && board[tileRow][tileCol-1] == 0) {
        newRow = tileRow;
        newCol = tileCol -1;

    }

        if(tileRow-1 >= 0 && board[tileRow-1][tileCol] == 0){
                newRow = tileRow-1;
                newCol = tileCol;
        }

        if(tileRow+1 <= dimension - 1 && board[tileRow+1][tileCol] == 0){
                newRow = tileRow+1;
                newCol = tileCol;
        }

        board[newRow][newCol] = board[tileRow][tileCol];
        board[tileRow][tileCol] = 0;

        return 1;
}


/**
 * Checks if the winning board configurations are met
 *
 */
int won(void) {
    int correct = 0;
    for(int i = 0, j= 0; i<dimension; i++, j++) {
        for(int j= 0; j<dimension-1; j++) {

            if(board[i][j] > board[i][j+1]) {
                  correct++;
                  if ((j== dimension-2)) {
 if(i < dimension -1) {
                          if(board[i][j+1] > board[i-1][j]) {
                            correct++;
                          }
                      }
                  }
            }
        }
    }
    return 0;
}
