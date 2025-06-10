#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNASSIGNED 0

int jeValidno(int** matrica, int n, int red, int kol, int broj) {
    for (int i = 0; i < n; i++) {
        if (matrica[red][i] == broj || matrica[i][kol] == broj) {
            return 0;
        }
    }

    int rDodaj = (n == 9) ? 3 : 2;
    int cDodaj = (n == 4) ? 2 : 3;
    int blokRed = red - red % rDodaj;
    int blokKol = kol - kol % cDodaj;

    for (int i = blokRed; i < blokRed + rDodaj; i++) {
        for (int j = blokKol; j < blokKol + cDodaj; j++) {
            if (matrica[i][j] == broj) {
                return 0;
            }
        }
    }

    return 1;
}

int pronadji_nepopunjeno(int** matrica, int n, int* red, int* kol) {
    for (*red = 0; *red < n; (*red)++) {
        for (*kol = 0; *kol < n; (*kol)++) {
            if (matrica[*red][*kol] == UNASSIGNED) {
                return 1;
            }
        }
    }
    return 0;
}

int generisi_sudoku(int** matrica, int n) {
    int red, kol;

    if (!pronadji_nepopunjeno(matrica, n, &red, &kol)) {
        return 1;
    }

    for (int broj = 1; broj <= n; broj++) {
        if (jeValidno(matrica, n, red, kol, broj)) {
            matrica[red][kol] = broj;

            if (generisi_sudoku(matrica, n)) { //rekurzivno poziva funkciju
                return 1;
            }

            matrica[red][kol] = UNASSIGNED;
        }
    }

    return 0;
}

void ukloni_elemente(int** matrica, int n, int broj_praznih) {
    for (int i = 0; i < broj_praznih; i++) {
        int red = rand() % n;
        int kol = rand() % n;
        while (matrica[red][kol] == 0) {
            red = rand() % n;
            kol = rand() % n;
        }
        matrica[red][kol] = 0;
    }
}

void ispisi_matricu(int** matrica, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != n - 1) {
                printf("%d ", matrica[i][j]);
            }
            else {
                printf("%d", matrica[i][j]);
            }
        }
        printf("\n");
    }
}

void sudokuIgra(int n) {
    int** matrica = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrica[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrica[i][j] = UNASSIGNED;
        }
    }

    generisi_sudoku(matrica, n);

    int broj_praznih = (n == 9) ? 40 : (n == 6) ? 20 : 8;
    ukloni_elemente(matrica, n, broj_praznih);

    printf("Pocetna matrica:\n");
    ispisi_matricu(matrica, n);

    int popunjeno = 0;
    while (!popunjeno) {
        int red, kolona, broj;

        printf("Unesi red: ");
        scanf("%d", &red);
        printf("Unesi kolonu: ");
        scanf("%d", &kolona);
        printf("Unesi broj: ");
        scanf("%d", &broj);

        if (red < 0 || red >= n || kolona < 0 || kolona >= n || broj < 1 || broj > n) {
            printf("KRAJ IGRE\n");
            break;
        }

        if (matrica[red][kolona] != 0) {
            printf("Polje vec popunjeno!\n");
            continue;
        }

        if (!jeValidno(matrica, n, red, kolona, broj)) {
            printf("NEVALIDNO STANJE\n");
        }
        else {
            matrica[red][kolona] = broj;
            printf("VALIDNO STANJE\n");
        }

        ispisi_matricu(matrica, n);

        popunjeno = 1;
        for (int i = 0; i < n && popunjeno; i++) {
            for (int j = 0; j < n && popunjeno; j++) {
                if (matrica[i][j] == 0) {
                    popunjeno = 0;
                }
            }
        }
    }

    printf("Resavanje zavrseno!\n");

    for (int i = 0; i < n; i++) {
        free(matrica[i]);
    }
    free(matrica);
}

int main() {
    srand((unsigned)time(NULL));

    int n;
    printf("Izaberi dimenzije Sudoku matrice:\n");
    printf("1. 4x4\n");
    printf("2. 6x6\n");
    printf("3. 9x9\n");
    printf("Unos: ");
    scanf("%d", &n);

    if (n == 1) {
        n = 4;
    }
    else if (n == 2) {
        n = 6;
    }
    else if (n == 3) {
        n = 9;
    }
    else {
        printf("NEVALIDNA DIMENZIJA\n");
        return 0;
    }

    sudokuIgra(n);
    return 0;
}


