// we take: ID OMM station, Pression station
//output file:   x  y  min y  max y



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
typedef struct chainon{
	int id;
    float vitesse;
    float NScoor;
    float OEcoor;
    float angle;
	struct chainon* pNext;
}Chainon;

typedef Arbre *pArbre;


pArbre creerArbre(int id, float pres)
{
	pArbre pnew = malloc(sizeof(Arbre));
	if (pnew == NULL)
	{
		exit(1);
	}
	pnew->id = id;
    pnew->angle = pres;
    pnew->vitesse = pres;
    pnew->NScoor = pres;
    pnew->OEcoor = 0;
	pnew->fg = NULL;
	pnew->fd = NULL;
	pnew->eq = 0;
	return pnew;
}

void traiter(pArbre a, FILE* outputfile, int* i)
{


	// add counter at start of every line in outfile to replace station id
	fprintf(outputfile,"%d",*i);

	// add data to output file with modification
	// x :a->id  y:a->angle  -y : a->vitesse +y : a->NScoor

	fprintf(outputfile, " %f %f %f\n", a->angle, a->vitesse, a->NScoor);
}

void traiterList(Chainon* list, FILE* outputfile){
	// add data to output file with modification
	// x :a->id  y:a->angle -y : a->vitesse  +y : a->NScoor
	int i = 1;
	while(list!=NULL){
		fprintf(outputfile, "%d %f %f %f\n", i, list->angle, list->vitesse ,list->NScoor );
		list = list->pNext;
		i++;
	}
}

typedef Arbre *pArbre;

//FCT LIST

Chainon* creationChainon(int id, float pres){
	Chainon* pnew = malloc(sizeof(Chainon));
	
	if(pnew == NULL){
		exit(1);
	}
	pnew->id = id;
    pnew->angle = pres;
    pnew->vitesse = pres;
    pnew->NScoor = pres;
    pnew->OEcoor = 0;
	pnew->pNext = NULL;
	return pnew;
}

void AddList(Chainon* pPlace, Chainon* pAddChainon) {
	if(pPlace == NULL){
		exit(1);
	}
	if(pAddChainon == NULL){
		exit(1);
	}
	pAddChainon->pNext = pPlace->pNext;
	pPlace -> pNext = pAddChainon;
	
}

Chainon* insertList(Chainon* pHead, char* list_champ[]){
	int data = atoi(list_champ[0]);
	Chainon* pAddChainon = creationChainon(data,atof(list_champ[1]));
	Chainon* p1 = malloc(sizeof(Chainon));
	Chainon* p2 = malloc(sizeof(Chainon));
	if (p1==NULL || p2 == NULL){
		exit(1);
	}
	//empty list
	if (pHead == NULL){
		return pAddChainon;
	}
	//one node list
	if (pHead->pNext == NULL){
		if (pHead->id <= data){
			pHead->pNext = pAddChainon;
			return pHead;
		}
		else{
			pAddChainon->pNext = pHead;
			return pAddChainon;
		}
		
	}
	//add start
	if (pHead->id > data){
		pAddChainon->pNext = pHead;
		return pAddChainon;
	}


	p1 = pHead;
	p2 = pHead->pNext;
	while (p2!=NULL){
		//update node
		if (p1->id == data){
			//update max
			if(atof(list_champ[1]) > p1->NScoor){
				p1->NScoor = atof(list_champ[1]);
			}
			//update min
			if (atof(list_champ[1]) < p1->vitesse){
				p1->angle =atof(list_champ[1]);
			}
			//update moy
			p1->angle = (p1->angle + atof(list_champ[1])) / 2;
			return pHead;
		}
		//insert node
		if (data > p1->id && data<p2->id){	
			AddList(p1,pAddChainon);
			return pHead;
		}
		else {
			p1 = p1->pNext;
			p2 = p2->pNext;
		}
	}
	//end of list ADD END
	if(data == p1->id){
		//update max
		if(atof(list_champ[1]) > p1->NScoor){
			p1->NScoor = data;
		}
		//update min
		if (atof(list_champ[1]) < p1->vitesse){
			p1->angle =atof(list_champ[1]);
		}
		//update moy
		p1->angle = (p1->angle + atof(list_champ[1])) / 2;
	}
	else{
		p1->pNext = pAddChainon;
	}
	return pHead;
	
	
}

// FCT ABR
pArbre recursive_insertABR(pArbre a, char* list_champ[])
{
	int data = atoi(list_champ[0]);
	if (a == NULL)
	{
		return creerArbre(data,atof(list_champ[1]));
	}
	else if (data == a->id){
		//update max
		if(atof(list_champ[1]) > a->NScoor){
			a->NScoor = atof(list_champ[1]);
		}
		//update min
		if (atof(list_champ[1]) < a->vitesse){
			a->angle =atof(list_champ[1]);
		}
		//update moy
		a->angle = (a->angle + atof(list_champ[1])) / 2;
	}
	else if (data < a->id)
	{
		a->fg = recursive_insertABR(a->fg, list_champ);
	}
	else if (data > a->id)
	{
		a->fd = recursive_insertABR(a->fd, list_champ);
	}
	return a;
}


// FCT AVL

void parcoursInfixe(pArbre a, FILE* outputfile ,int i)
{
	if (a != NULL)
	{
		parcoursInfixe(a->fg, outputfile,i);
		traiter(a, outputfile,i);
		i++;
		parcoursInfixe(a->fd, outputfile,i);
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


pArbre insert(pArbre root, char* list_champ[])

{
    int data = atoi(list_champ[0]);
    //data for code
	if (root == NULL)

	{

		pArbre new_node = creerArbre(data,atof(list_champ[1]));

		if (new_node == NULL)

		{

			return NULL;
		}

		root = new_node;
	}
	// update node
	else if (data == root->id)

	{
		
		//update max
		if(atof(list_champ[1]) > root->NScoor){
			root->NScoor = atof(list_champ[1]);
		}
		//update min
		if (atof(list_champ[1]) < root->vitesse){
			root->angle = atof(list_champ[1]);
		}
		//update moy
		root->angle = (root->angle + atof(list_champ[1])) / 2;

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


int line_regularity(char* sample){
	// test if the line has empty column
	// return 1 if line is good 0 if not
	char* test1 = strstr( sample, ";\n");
	char* test2 = strstr( sample, ";;");
	char* test3 = strstr( sample, "; ;");
	if (test1 == NULL && test2 == NULL && test3 == NULL){
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int AVL = 0;
	int ABR = 0;
	int LIST =0;

	if(strcmp(argv[2],"--avl") == 0){
		AVL = 1;
	}
	else if(strcmp(argv[2],"--abr") == 0){
		ABR = 1;
	}
	else if(strcmp(argv[2],"--tab") == 0){
		LIST = 1;
	}
	else{
		AVL = 1;
	}
	
	
	int* i;
	*i = 1;


	pArbre rootDat = NULL;
	Chainon* ListDat = NULL;
   

    FILE *inputFile;

    // take out ./exe argument in argument count and in argument list
    argc--;
    argv++;

    if (argc == 0)
    {
        printf("Usage: sample filename...\n");
        exit(1);
    }

    inputFile = fopen(argv[0], "r");
    if (inputFile == NULL)
    {
        printf("Cannot open file %s\n", argv[0]);
        exit(1);
    }

    puts("file is ok");

    FILE *outputFile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    outputFile = fopen(argv[1], "w");
    if (outputFile == NULL)
    {
        printf("Cannot open file %s\n", argv[1]);
        exit(1);
    }

    // column name flush
    read = getline(&line, &len, inputFile);

    char *value;
    int colomn;
    char *champ[2] = {"0", "0"};

    while ((read = getline(&line, &len, inputFile)) != -1)
    {
        colomn = 0;

		if (line_regularity(line) ==  1){
			value = strtok(line, ";");
			while (value)
        	{
            
            	champ[colomn] = value;
            	value = strtok(NULL, ";\n");
            	colomn++;
        	}
    		//insertion dans AVL
			if(AVL){
				rootDat = insert(rootDat, champ);
			}
        
    		// insertion ABR
			else if (ABR){
				rootDat = recursive_insertABR(rootDat, champ);
			}

			//insertion list
			else if (LIST){
				ListDat = insertList(ListDat, champ);
			}

    		// reinit champ for next line
       		for (int i = 0; i < 2 ; i++){
            	champ[i] = "0";
        	}
		}
        
    }
    if (line)
    {
        free(line);
    }

    // Add sorted data to outputfile
	if (ABR || AVL){
		parcoursInfixe(rootDat, outputFile,i);
	}
	else{
		traiterList(ListDat, outputFile);
	}
 


    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
