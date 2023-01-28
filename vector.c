// MULTIPLE VALUE AVL

// ADD ACCORDING TO FIRST VALUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SPACE puts("\n")

typedef struct arbre
{
    int id;
    float vitesse;
    float NScoor;
    float OEcoor;
    float angle;
    struct arbre *fg;
    struct arbre *fd;
    int eq;
} Arbre;

typedef Arbre *pArbre;

pArbre creerArbre(int id, float angle, float vitesse, float NScoor, float OEcoor)
{
	pArbre pnew = malloc(sizeof(Arbre));
	if (pnew == NULL)
	{
		exit(1);
	}
	pnew->id = id;
    pnew->angle = angle;
    pnew->vitesse = vitesse;
    pnew->NScoor = NScoor;
    pnew->OEcoor = OEcoor;
	pnew->fg = NULL;
	pnew->fd = NULL;
	pnew->eq = 0;
	return pnew;
}

typedef Arbre *pArbre;

void traiter(pArbre a, FILE* outputfile)
{

	// add data to output file with modification
	// x1 :a->OEcoor  y1:a->NScoor  x2 : a->OEcoor + a->vitesse*cos(a->angle) y2 : a->NScoor + a->vitesse*sin(a->angle)


	fprintf(outputfile, "%f %f %f %f\n", a->OEcoor, a->NScoor, a->OEcoor + a->vitesse*cos(a->angle) ,a->NScoor + a->vitesse*sin(a->angle) );
    puts("");
}

void parcoursInfixe(pArbre a, FILE* outputfile)
{
	if (a != NULL)
	{
		parcoursInfixe(a->fg, outputfile);
		traiter(a, outputfile);
		parcoursInfixe(a->fd, outputfile);
	}
}

int min2(int a, int b, int c)
{
	if (a <= b && a <= c)
	{
		return a;
	}
	else if (b <= a && b <= c)
	{
		return b;
	}
	else
	{
		return c;
	}
}

int max(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int min(int a, int b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int max2(int a, int b, int c)
{
	if (a >= b && a >= c)
	{
		return a;
	}
	else if (b >= a && b >= c)
	{
		return b;
	}
	else
	{
		return c;
	}
}

pArbre rotationGauche(pArbre a)
{
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->eq;
	eq_p = pivot->eq;
	a->eq = eq_a - max(eq_p, 0) - 1;
	pivot->eq = min2(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
	a = pivot;
	return pivot;
}

pArbre rotationDroite(pArbre a)
{
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->eq;
	eq_p = pivot->eq;
	a->eq = eq_a - min(eq_p, 0) + 1;
	pivot->eq = max2(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
	a = pivot;
	return pivot;
}

pArbre doubleRotationGauche(pArbre a)
{
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}

pArbre doubleRotationDroite(pArbre a)
{
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}


//reéquilibrage auto mais pas capt 
pArbre insert(pArbre root, char* list_champ[])

{
    int data = atoi(list_champ[0]);
    //data for code
	if (root == NULL)

	{

		pArbre new_node = creerArbre(data,atof(list_champ[1]), atof(list_champ[2]), atof(list_champ[3]), atof(list_champ[4]));

		if (new_node == NULL)

		{

			return NULL;
		}

		root = new_node;
	}
	// update node
	else if (data == root->id)

	{
		printf("update");
	}

	else if (data > root->id)

	{

		// insert the new node to the right

		root->fd = insert(root->fd, list_champ);

		// tree is unbalanced, then rotate it

		if (root->eq == -2)

		{

			if (data > root->fd->id)

			{

				root = rotationGauche(root);
			}

			else

			{

				root->fd = rotationDroite(root->fd);

				root = rotationGauche(root);
			}
		}
	}

	else

	{

		// insert the new node to the left

		root->fg = insert(root->fg, list_champ);

		// tree is unbalanced, then rotate it

		if (root->eq == 2)

		{

			if (data < root->fg->id)

			{

				root = rotationDroite(root);
			}

			else

			{

				root->fg = rotationGauche(root->fg);

				root = rotationDroite(root);
			}
		}
	}

	return root;
}


int main(int argc, char **argv)
{

    pArbre rootDat = NULL;

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
    puts("\n");

    FILE *outputFile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    outputFile = fopen("vectorOutput.txt", "w");
    if (outputFile == NULL)
    {
        puts("Cannot open file vectorOutput.txt");
        exit(0);
    }

    // column name flush
    read = getline(&line, &len, inputFile);
    // fprintf(outputFile, "%s", line);
    char *value;
    // double val;
    int colomn;
    char *champ[5] = {"0", "0", "0", "0", "0"};

    while ((read = getline(&line, &len, inputFile)) != -1)
    {
        colomn = 0;

        value = strtok(line, ";");
        while (value)
        {
            // printf("Réception d'une ligne de longueur %zu :\n", read);
            //fprintf(outputFile, "%s ", value);
            /*if (colomn == 0){

                val = atoi(value);
            }
            if (colomn == 1){
                val = atof(value);
            }*/

            champ[colomn] = value;

            printf("%s ", champ[colomn]);
            value = strtok(NULL, ";\n");
            colomn++;
        }
    //insertion dans AVL
        rootDat = insert(rootDat, champ);

        printf("\n");
        //fprintf(outputFile, "\n");
        
        // reinitializa champ for next line

        for (int i = 0; i < 5 ; i++){
            champ[i] = "0";
        }
    }
    if (line)
    {
        free(line);
    }

    // affichage AVL check tri
    puts("\n TRI \n");
    parcoursInfixe(rootDat, outputFile);


    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
