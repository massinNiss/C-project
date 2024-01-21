// Main2.h
#ifndef MAIN2_H
#define MAIN2_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdint.h>

const char *Reclamation = "Reclamation.txt";

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void saveCurrentDateTime(const char* filename, int id) {
    // Get the current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Open the file for writing
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the date and time to the file
    fprintf(file, "client : %d || %d-%02d-%02d %02d:%02d:%02d\n",id,
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);

    fclose(file);
}
uint64_t hash_password(const char *password) {
    uint64_t hash = 5381;
    int c;

    while ((c = *password++) != 0)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}


void read_password(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();  // Lit un caractère sans l'afficher

        if (ch == 13) {  // Si la touche Entrée (caractère 13) est pressée
            password[i] = '\0';  // Termine la chaîne de caractères
            break;
        } else if (ch == 8) {  // Si la touche Backspace (caractère 8) est pressée
            if (i > 0) {
                i--;
                printf("\b \b");  // Efface l'étoile
            }
        } else {
            password[i++] = ch;
            printf("*");  // Affiche une étoile
        }
    }
}

void reclamations(int *id)
{
    system("cls");
    char reclam[50];

    printf("\n\n\n\n\n");
    printf("\t\tEntrez votre plainte: ");

    fgets(reclam, sizeof(reclam), stdin);
    FILE *pr = fopen(Reclamation, "at+");
    if(!pr)
    {
        printf("Une erreur s'est produite!!");
        return 1;
    }

    //int length = strlen(reclamation);
    //reclamation[length - 1] = '\0';

    //Write the reclam to the file
    fprintf(pr, "le client %d a une reclamation concernant : %s \n", (*id) ,reclam);
    fclose(pr);
    printf("\n\n\t\tLa reclamation a ete envoyer avec succes.");
    for(int i=0; i<3;i++)
    {
        printf(".");
        sleep(1);
    }
    Admin_Consulting();
}

#endif // MAIN2_H

