#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 50

typedef struct {
    int hour;
    int minute;
    char title[MAX_TITLE_LENGTH];
} Task;

void printMenu() {
    printf("1) Hinzufügen\n");
    printf("2) Entfernen\n");
    printf("3) Liste\n");
    printf("4) Beenden\n");
}

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Maximale Anzahl von Aufgaben erreicht!\n");
        return;
    }

    int duration;
    printf("Wünschen Sie einen Vorschlag (1) oder möchten Sie selbst hinzufügen (2)? ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Wie lange dauert die Aufgabe (Stunde)? ");
        scanf("%d", &duration);
        // Implementieren Sie hier die Logik zur Berechnung des ersten verfügbaren Zeitfensters
        // und zeigen Sie es dem Benutzer an.
        // ...

        printf("OK (1), Selbst wählen (2)? ");
        scanf("%d", &choice);

        if (choice != 1) {
            // Implementieren Sie hier die Logik, um den Benutzer sein eigenes Zeitfenster wählen zu lassen.
            // ...
        }
    } else if (choice == 2) {
        // Implementieren Sie hier die Logik für den manuellen Hinzufügen von Aufgaben durch den Benutzer.
        // ...
    } else {
        printf("Ungültige Eingabe!\n");
    }
}

void removeTask(Task tasks[], int *taskCount) {
    // Implementieren Sie hier die Logik zum Entfernen von Aufgaben durch den Benutzer.
    // ...
}

void listTasks(Task tasks[], int taskCount) {
    // Implementieren Sie hier die Logik zum Anzeigen der Liste der Aufgaben.
    // ...
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;

    while (1) {
        printMenu();

        int choice;
        printf("$ ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                removeTask(tasks, &taskCount);
                break;
            case 3:
                listTasks(tasks, taskCount);
                break;
            case 4:
                // Implementieren Sie hier die Logik zum Speichern der Aufgaben in einer Textdatei.
                // ...
                printf("Aufgaben wurden gespeichert. Auf Wiedersehen!\n");
                exit(0);
            default:
                printf("Ungültige Eingabe! Bitte erneut versuchen.\n");
        }
    }

    return 0;
}
