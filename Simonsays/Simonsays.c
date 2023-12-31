#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_ROUNDS 3

typedef struct {
    char name[50];
    int score;
} Highscore;

void display_highscores(Highscore highscores[]);
void save_highscores(Highscore highscores[], char name[], int score);
void display_sequence(int sequence[], int length);
void clear_screen();
int play_round(int round);

int main() {
    srand(time(NULL));

    Highscore highscores[MAX_ROUNDS];
    for (int i = 0; i < MAX_ROUNDS; ++i) {
        strcpy(highscores[i].name, "None");
        highscores[i].score = 0;
    }

    char choice;
    do {
        printf("TAU SAYS Highscore: %s (%d Runde)\n", highscores[0].name, highscores[0].score);
        printf("1) Spielen\n2) Highscores\nq: Beenden\n");

        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                int score = play_round(1);
                if (score > highscores[0].score) {
                    char name[50];
                    printf("Geben Sie Ihren Namen ein: ");
                    scanf("%s", name);
                    save_highscores(highscores, name, score);
                }
                break;
            }
            case '2':
                display_highscores(highscores);
                break;
        }

    } while (choice != 'q');

    return 0;
}

void display_highscores(Highscore highscores[]) {
    printf("Highscores:\n");
    for (int i = 0; i < MAX_ROUNDS; ++i) {
        printf("%d. %s: %d Runde(n)\n", i + 1, highscores[i].name, highscores[i].score);
    }
}

void save_highscores(Highscore highscores[], char name[], int score) {
    for (int i = MAX_ROUNDS - 1; i >= 0; --i) {
        if (i == 0 || score > highscores[i - 1].score) {
            strcpy(highscores[i].name, name);
            highscores[i].score = score;
            break;
        }
    }
}

void display_sequence(int sequence[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", sequence[i]);
        fflush(stdout);
        sleep(1);
        clear_screen();
        sleep(1);
    }
}

void clear_screen() {
    system("clear || cls");
}

int play_round(int round) {
    printf("Runde #%d: ", round);

    int sequence[MAX_ROUNDS];
    for (int i = 0; i < round; ++i) {
        sequence[i] = rand() % 4 + 1;
    }

    display_sequence(sequence, round);

    printf("Runde #%d: ", round);

    int user_input[MAX_ROUNDS];
    for (int i = 0; i < round; ++i) {
        scanf("%d", &user_input[i]);
    }

    for (int i = 0; i < round; ++i) {
        if (user_input[i] != sequence[i]) {
            printf("Falsch!\n");
            return round;
        }
    }

    printf("Richtig.\n");
    return play_round(round + 1);
}
