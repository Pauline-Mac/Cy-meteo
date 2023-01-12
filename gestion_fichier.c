#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define TAILLE 1000

//___________________TRI TABLEAU______________________________
void affichage_tableau(int tab[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("%d", tab[i]);
        printf("; ");
    }
}

int partition(int A[], int debut, int fin)
{
    int tmp;
    int inf = debut + 1;
    int sup = fin;
    while (inf <= sup)
    {
        while (A[sup] > A[debut])
        {
            sup = sup - 1;
        }
        while (A[inf] <= A[debut])
        {
            inf = inf + 1;
        }
        if (inf < sup)
        {
            tmp = A[sup];
            A[sup] = A[inf];
            A[inf] = tmp;
        }
    }
    tmp = A[debut];
    A[debut] = A[sup];
    A[sup] = tmp;
    return sup;
}

void triRapideRec(int A[], int debut, int fin)
{
    int pivot;
    if (debut < fin)
    {
        pivot = partition(A, debut, fin);
        triRapideRec(A, debut, pivot - 1);
        triRapideRec(A, pivot + 1, fin);
    }
}

void triRapide(int A[], int taille)
{
    triRapideRec(A, 0, taille - 1);
}
//_________________________________________________________________

int main(int argc, char *argv[])
{
    /*
    //_________________GESTION FICHIER ______________________

    FILE * inputFile;


    // take out ./exe argument in argument count and in argument list
    argc--;   argv++;

    if ( argc == 0 ) {
        printf( "Usage: sample filename...\n" );
        exit( 0 );
    }

    inputFile = fopen( argv[0], "a" );
    if ( inputFile == NULL ) {
        printf( "Cannot open file %s\n", argv[0] );
        exit( 0 );
    }

    puts("file is ok");
    //fprintf( inputFile, "Appending a new message in the file\n" );

    fclose( inputFile );

    //_________________________________________________________
    */

    FILE *inputFile;

    // take out ./exe argument in argument count and in argument list
    argc--;
    argv++;

    if (argc == 0)
    {
        printf("Usage: sample filename...\n");
        exit(0);
    }

    inputFile = fopen(argv[0], "r");
    if (inputFile == NULL)
    {
        printf("Cannot open file %s\n", argv[0]);
        exit(0);
    }

    puts("file is ok");
    // fprintf( inputFile, "Appending a new message in the file\n" );
    // fscanf(inputFile, "%s", str);
    puts("\n");

    FILE *outputFile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        puts("Cannot open file outputFile.txt");
        exit(0);
    }

    read = getline(&line, &len, inputFile);
    fprintf(outputFile, "%s", line);
    char *value;
    double val;

    while ((read = getline(&line, &len, inputFile)) != -1)
    {
        printf("\n");
        fprintf(outputFile, "\n");
        value = strtok(line, ";");
        while (value)
        {
            // printf("Réception d'une ligne de longueur %zu :\n", read);
            fprintf(outputFile, "%s ", value);
            val = atof(value);

            printf("%s %f", value, val);
            value = strtok(NULL, ";\n");
        }

        /*   int i1, i2;
        if (2 == sscanf(line, "%*[^0123456789]%d%*[^0123456789]%d", &i1, &i2))
        {
            printf("%d %d\n", i1, i2);
        }
        fprintf(outputFile, "%s", line);*/
    }
    if (line)
    {
        free(line);
    }

    fclose(inputFile);
    fclose(outputFile);

    // permet de récupérere des entiers

    /* Tab test______________________
    srand(time(NULL));
    int tableau[TAILLE] = {0};
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i] = rand() % 501;
    }
    affichage_tableau(tableau, TAILLE);
    triRapide(tableau, TAILLE);
    puts("");
    affichage_tableau(tableau, TAILLE);
    //_____________________________*/
    return 0;
}