#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define FILENAME "scores.txt"

void addition();
void multiplication(); 
void permuter(int *a, int *b);
void soustraction();
void multi();
int point = 0;
int main(){
    int jour;
    int reelpoint;
    char nom[50];
    printf("Entrez votre nom : ");
    scanf("%49s", nom);
    FILE *fichier2 = fopen(FILENAME, "r");
    char ligne[100];
    char nom_lu[50];
    int trouve = 0;
    int trouvep = 0;
    int scoretmp;

    if (fichier2 != NULL) {
        while (fgets(ligne, sizeof(ligne), fichier2)) { 
            if (sscanf(ligne, "Votre nom:%s Heure:%*[^N] Nombre de point:%d", nom_lu, &scoretmp) == 2) {
                if (strcmp(nom, nom_lu) == 0) { 
                    printf("Votre dernier score enregistrer : %d\n", scoretmp);
                    trouve = 1;
                    
                    point=scoretmp;
                    break; 
                }
            }
        }
        fclose(fichier2);
    }
    
    if (!trouve) {
        printf("Aucun score trouver pour %s.\n", nom);
    }
    
    srand(time(NULL));
    do {
        printf("Point du joueur : %d\n", point);
        printf("+-----------------------------------+\n");
        printf("|1 : Addition                       |\n");
        printf("|2 : Soustraction                   |\n");
        printf("|3 : Multiplication                 |\n");
        printf("|4 : Tables des multiplications     |\n");
        printf("|5 : Divisions                      |\n");
        printf("|0 : Sortir du jeu                  |\n");
        printf("+-----------------------------------+\n");
        printf("Quel est votre choix ?\n");
        scanf("%d", &jour); printf("\n");

        switch (jour) {
            case 1 : addition(); break;
            case 2 : soustraction(); break;
            case 3 : multiplication(); break;
            case 4 : multi(); break;
            case 5 : printf("Divisions\n"); break;
            case 0 : printf("Sortir du jeu\n"); break;
            default : printf("Choisi un nombre dans le jeu\n"); break;
        }
    } while (jour != 0);

    if (jour == 0) {
        printf("Merci de votre visite\n");
    }
    
    // mémorisation
if (trouve == 1) {
    FILE *fichier_lecture = fopen(FILENAME, "r");
    FILE *fichier_temp = fopen("temp.txt", "w");
    char ligne_mod[100];
    time_t now = time(NULL);
    struct tm tm_now = *localtime(&now);
    char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];
    strftime(s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);
    
    if (fichier_lecture == NULL || fichier_temp == NULL) {
         perror("Erreur lors de l'ouverture d'un fichier");
        return 1;
    }
    
    while (fgets(ligne_mod, sizeof(ligne_mod), fichier_lecture)) {
        char nom_temp[50];
        int ancien_score;
    
        if (sscanf(ligne_mod, "Votre nom:%s Heure:%*[^N] Nombre de point:%d", nom_temp, &ancien_score) == 2 && strcmp(nom_temp, nom) == 0) {
            // Ligne à modifier : on remplace par la nouvelle ligne
             fprintf(fichier_temp, "Votre nom:%s Heure:%s Nombre de point:%d\n", nom, s_now, point);
        } else {
             // Autres lignes : on les recopie telles quelles
            fputs(ligne_mod, fichier_temp);
        }
    }
    
    fclose(fichier_lecture);
    fclose(fichier_temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}
    
    
if (trouve == 0){
    FILE *fichier = fopen("scores.txt", "a+"); // Mode écriture
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
    return 1;
    }
       /* lire l'heure courante */
   time_t now = time (NULL);

   /* la convertir en heure locale */
   struct tm tm_now = *localtime (&now);

   /* Creer une chaine JJ/MM/AAAA HH:MM:SS */
   char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];

   strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);
    fprintf(fichier,"Votre nom:%s Heure:%s Nombre de point:%d\n",nom , s_now , point);
    fclose(fichier);
}

    
    return 0;

}

void addition() {
    int add1, add2, resultatadd, tentatives = 0;
    printf("Addition\n");
    add1 = rand() % 101;
    add2 = rand() % 101;
    printf("%d + %d = ?\n", add1, add2);

    do {
        printf("Entrez le resultat : ");
        scanf("%d", &resultatadd);
        tentatives++;

        if (add1 + add2 == resultatadd) {
            if (tentatives == 1) {
                printf("Bravo du premier coup !\n");
                point += 10;
            } else if (tentatives == 2) {
                printf("Bravo du deuxième coup!\n");
                point += 5;
            } else if (tentatives == 3) {
                printf("Bof!\n");
                point += 1;
            }
            break;
        } else {
            printf("Mauvaise reponse. Essayez encore.\n");
        }
    } while (tentatives < 3);

    if (tentatives == 3 && add1 + add2 != resultatadd) {
        printf("La bonne reponse etait %d.\n", add1 + add2);
    }
}

void multiplication() {
    int mul1, mul2, resultatmul, tentatives = 0;
    printf("Multiplication\n");
    mul1 = rand() % 11;
    mul2 = rand() % 11;
    printf("%d x %d = ?\n", mul1, mul2);

    do {
        printf("Entrez le resultat : ");
        scanf("%d", &resultatmul);
        tentatives++;

        if (mul1 * mul2 == resultatmul) {
            if (tentatives == 1) {
                printf("Bravo du premier coup !\n");
                point += 10;
            } else if (tentatives == 2) {
                printf("Bravo du deuxième coup!\n");
                point += 5;
            } else if (tentatives == 3) {
                printf("Bof!\n");
                point += 1;
            }
            break;
        } else {
            printf("Mauvaise réponse. Essayez encore.\n");
        }
    } while (tentatives < 3);

    if (tentatives == 3 && mul1 * mul2 != resultatmul) {
        printf("La bonne reponse etait %d.\n", mul1 * mul2);
    }
}

void soustraction() {
    int sou1, sou2, resultatsou, tentatives = 0;
    printf("Soustraction\n");
    sou1 = rand() % 101;
    sou2 = rand() % 101;
    if (sou1 < sou2) {
        permuter(&sou1, &sou2);
    }
    printf("%d - %d = ?\n", sou1, sou2);

    do {
        printf("Entrez le resultat : ");
        scanf("%d", &resultatsou);
        tentatives++;

        if (sou1 - sou2 == resultatsou) {
            if (tentatives == 1) {
                printf("Bravo du premier coup !\n");
                point += 10;
            } else if (tentatives == 2) {
                printf("Bravo du deuxième coup!\n");
                point += 5;
            } else if (tentatives == 3) {
                printf("Bof!\n");
                point += 1;
            }
            break;
        } else {
            printf("Mauvaise reponse. Essayez encore.\n");
        }
    } while (tentatives < 3);

    if (tentatives == 3 && sou1 - sou2 != resultatsou) {
        printf("La bonne reponse etait %d.\n", sou1 - sou2);
    }
}

void permuter(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void multi() {
    int x, nombre, tentatives;
    printf("Tables de multiplication\n");
    printf("Choisissez la table de multiplication comprise entre 1 et 10\n");
    scanf("%d", &x);

    for (int i = 0; i <= 10; i++) {
        tentatives = 0;
        printf("%d x %d = ?\n", x, i);

        do {
            scanf("%d", &nombre);
            tentatives++;

            if (i * x == nombre) {
                if (tentatives == 1) {
                    printf("Bravo du premier coup !\n");
                    point += 10;
                } else if (tentatives == 2) {
                    printf("Bravo du deuxième coup!\n");
                    point += 5;
                } else if (tentatives == 3) {
                    printf("Bof!\n");
                    point += 1;
                }
                break;
            } else {
                printf("Mauvaise reponse. Essayez encore.\n");
            }
        } while (tentatives < 3);

        if (tentatives == 3 && i * x != nombre) {
            printf("La bonne reponse etait %d.\n", i * x);
        }
    }
}


    