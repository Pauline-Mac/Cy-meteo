// we take: Date, Température
//output file:   x  y



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arbre
{
    int id;
	int counter;
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
	int counter;
    float vitesse;
    float NScoor;
    float OEcoor;
    float angle;
	struct chainon* pNext;
}Chainon;

typedef Arbre *pArbre;


pArbre creerArbre(int date, float hour, float temp)
{

	pArbre pnew = malloc(sizeof(Arbre));
	if (pnew == NULL)
	{
		exit(1);
	}
	pnew->counter = 1;
	pnew->id = date;
	pnew->angle = temp;
    pnew->vitesse = hour;
    pnew->NScoor = 0;
    pnew->OEcoor = 0;
	pnew->fg = NULL;
	pnew->fd = NULL;
	pnew->eq = 0;
	return pnew;
}

void traiter(pArbre a, FILE* outputfile)
{

	// add data to output file
	// x :a->id  y:a->angle
	char str[20];
	char str2[6];
	gcvt(a->vitesse,5,str2);
	sprintf(str,"%d",a->id);

	if (strlen(str2)==3){
		fprintf(outputfile, "%c%c%c%c-%c%c-%c%c %c:00 %0.5f\n", str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7],str2[0], a->angle/a->counter);
	}
	else{
		fprintf(outputfile, "%c%c%c%c-%c%c-%c%c %c%c:00 %0.5f\n", str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7],str2[0],str2[1], a->angle/a->counter);
	}
}

void traiterList(Chainon* list, FILE* outputfile){
	// add data to output file with modification
	// x :a->id  y:a->angle
	char str[20];
	char str2[6];
	while(list!=NULL){
		gcvt(list->vitesse,5,str2);
		sprintf(str,"%d",list->id);
		if (strlen(str2)==3){
			fprintf(outputfile, "%c%c%c%c-%c%c-%c%c %c:00 %0.5f\n", str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7],str2[0], list->angle/list->counter);
		}
		else{
			printf("%ld",strlen(str2));
			fprintf(outputfile, "%c%c%c%c-%c%c-%c%c %c%c:00 %0.5f\n", str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7],str2[0],str2[1], list->angle/list->counter);
		}
		list = list->pNext;
	}
}

typedef Arbre *pArbre;

//FCT LIST

Chainon* creationChainon(int date,float hour, float temp){
	Chainon* pnew = malloc(sizeof(Chainon));
	
	if(pnew == NULL){
		exit(1);
	}
	pnew->counter = 1;
	pnew->id = date;
    pnew->angle = temp;
    pnew->vitesse = hour;
    pnew->NScoor = 0;
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
	int date;
	int hour;
	int min;
	sscanf(list_champ[0], "%dT%d:%d", &date,&hour, &min);

	int data1 = date;
	int data2 = hour*100 + min;
	Chainon* pAddChainon = creationChainon(data1,data2,atof(list_champ[1]));
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
		if (pHead->id <= data1 || (pHead->id == data1 && pHead->vitesse <= data2)){
			pHead->pNext = pAddChainon;
			return pHead;
		}
		else{
			pAddChainon->pNext = pHead;
			return pAddChainon;
		}
		
	}
	//add start
	if (pHead->id > data1 || (pHead->id == data1 && pHead->vitesse > data2)){
		pAddChainon->pNext = pHead;
		return pAddChainon;
	}

	p1 = pHead;
	p2 = pHead->pNext;
	while (p2!=NULL){
		//update node
		if (p1->id == data1 && p1->vitesse == data2){
			// update temperature
			p1->angle = p1->angle + atof(list_champ[1]);
			//counter increase by one
			p1->counter = p1->counter +1;
			return pHead;
		}
		//insert node
		if ((data1 > p1->id || (data1 == p1->id && data2 > p1->vitesse)) && (data1<p2->id || (data1 == p2->id && data2 < p2->vitesse))){	
			AddList(p1,pAddChainon);
			return pHead;
		}
		else {
			p1 = p1->pNext;
			p2 = p2->pNext;
		}
	}
	//end of list ADD END
	if(data1 == p1->id && data2 == p1->vitesse){
		// update temperature
		p1->angle = p1->angle + atof(list_champ[1]);
		//counter increase by one
		p1->counter = p1->counter +1;
	}
	else{
		p1->pNext = pAddChainon;
	}
	return pHead;
	
	
}

// FCT ABR
pArbre recursive_insertABR(pArbre a, char* list_champ[])
{
	int date;
	int hour;
	int min;
	sscanf(list_champ[0], "%dT%d:%d", &date,&hour, &min);

	int data1 = date;
	int data2 = hour*100 + min;


	
	if (a == NULL)
	{
		return creerArbre(data1,data2,atof(list_champ[1]));
	}
	else if (data1 == a->id && data2 == a->vitesse){
		// update temperature
		a->angle = a->angle + atof(list_champ[1]);
		//counter increase by one
		a->counter = a->counter +1;
	}
	else if (data1 < a->id ||(data2 < a->vitesse && data1 == a->id))
	{
		a->fg = recursive_insertABR(a->fg, list_champ);
	}
	else if (data1 > a->id ||(data2 > a->vitesse && data1 == a->id))
	{
		a->fd = recursive_insertABR(a->fd, list_champ);
	}
	return a;
}


// FCT AVL

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

pArbre insert(pArbre root, char* list_champ[])

{
	int date;
	int hour;
	int min;
	sscanf(list_champ[0], "%dT%d:%d", &date,&hour, &min);

	int data1 = date;
	int data2 = hour*100 + min;


	if (root == NULL)

	{

		pArbre new_node = creerArbre(data1,data2,atof(list_champ[1]));

		if (new_node == NULL)

		{

			return NULL;
		}

		root = new_node;
	}
	// update node
	else if (data1 == root->id && data2 == root->vitesse)

	{
		// update temperature
		root->angle = root->angle + atof(list_champ[1]);
		//counter increase by one
		root->counter = root->counter +1;
	}

	else if (data1 > root->id ||(data2 > root->vitesse && data1 == root->id))

	{

		// insert the new node to the right

		root->fd = insert(root->fd, list_champ);

		// tree is unbalanced, then rotate it

		if (root->eq == -2)

		{

			if (data1 > root->fd->id ||(data2 > root->fd->vitesse && data1 == root->fd->id))

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

			if (data1 < root->fg->id ||(data2 < root->fg->vitesse && data1 == root->fg->id))

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

void SHOWavl(pArbre root){
	if(root!=NULL){
		SHOWavl(root->fg);
		printf("%d %.2f  \n", root->id, root->angle);
		SHOWavl(root->fd);
	}
}

int main(int argc, char **argv)
{
	int AVL = 0;
	int ABR = 0;
	int LIST = 0;

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
		if (line_regularity(line)== 1){
			value = strtok(line, ";\n");
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
		parcoursInfixe(rootDat, outputFile);
	}

	else{
		traiterList(ListDat, outputFile);
	}


    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
