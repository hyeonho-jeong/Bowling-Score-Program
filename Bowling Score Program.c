#include <stdio.h>

typedef struct {
    int firstRoll, secondRoll;
    int score;
    int total;
    int bonus;
} Frame;

void printFrameResult(int firstRoll, int secondRoll);

int main() {
    int frameIndex;

    Frame frames[12] = {{0, },};

    printf("Welcome to the Bowling Score Program!\n");

    for (frameIndex = 1; frameIndex < 12; frameIndex++) {
        printf("Enter the score for frame %d, 1st chance: ", frameIndex);
        scanf("%d", &frames[frameIndex].firstRoll);

        if (frames[frameIndex].firstRoll < 10) {
            if (frameIndex == 11 && frames[10].firstRoll != 10) {}
            else {
                printf("Enter the score for frame %d, 2nd chance: ", frameIndex);
                scanf("%d", &frames[frameIndex].secondRoll);
            }
        }

        if (frameIndex == 11)
            frames[frameIndex].bonus = 0;
        else if (frames[frameIndex].firstRoll == 10)
            frames[frameIndex].bonus = 2; // strike
        else if (frames[frameIndex].firstRoll + frames[frameIndex].secondRoll == 10)
            frames[frameIndex].bonus = 1; // spare
        else
            frames[frameIndex].bonus = 0;

        if (frames[frameIndex].bonus == 0)
            frames[frameIndex].score = frames[frameIndex].firstRoll + frames[frameIndex].secondRoll;

        if (frames[frameIndex - 1].bonus == 1) {
            frames[frameIndex - 1].score = frames[frameIndex - 1].firstRoll +
                                            frames[frameIndex - 1].secondRoll + frames[frameIndex].firstRoll;
            frames[frameIndex - 1].bonus = 0;
        } else if (frames[frameIndex - 1].bonus == 2 && frames[frameIndex].bonus != 2) {
            frames[frameIndex - 1].score = frames[frameIndex - 1].firstRoll +
                                            frames[frameIndex - 1].secondRoll + frames[frameIndex].firstRoll +
                                            frames[frameIndex].secondRoll;
            frames[frameIndex - 1].bonus = 0;
        }

        if (frames[frameIndex - 2].bonus == 2) {
            frames[frameIndex - 2].score = frames[frameIndex - 2].firstRoll +
                                            frames[frameIndex - 2].secondRoll + frames[frameIndex - 1].firstRoll +
                                            frames[frameIndex - 1].secondRoll + frames[frameIndex].firstRoll;
            frames[frameIndex - 2].bonus = 0;
        }

        for (int i = 1; i <= frameIndex; i++)
            frames[i].total = frames[i - 1].total + frames[i].score;

        printf("\n%-9s", "Frames:");

        for (int j = 1; j < 12; j++)
            printf("%10d", j);

        printf("\n%-9s", "Rolls:");

        for (int j = 1; j <= frameIndex; j++)
            printFrameResult(frames[j].firstRoll, frames[j].secondRoll);

        printf("\n%-9s", "Total:");

        for (int j = 1; j <= frameIndex; j++)
            printf("%10d", frames[j].total);

        printf("\n");

        if (frameIndex == 10 && frames[frameIndex].firstRoll + frames[frameIndex].secondRoll < 10)
            break;
    }

    return 0;
}

void printFrameResult(int firstRoll, int secondRoll) {
    char resultSymbol = ' ';
    if (firstRoll == 10)
        resultSymbol = 'X';
    else if (firstRoll + secondRoll == 10)
        resultSymbol = '/';
    else if (firstRoll + secondRoll == 0)
        resultSymbol = 'G';

    printf("    %2d %c %2d ", firstRoll,  resultSymbol, secondRoll);
}
