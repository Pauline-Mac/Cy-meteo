#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(strcmp(argv[1],"avl") == 0){
		printf("%s AVL", argv[1]);
	}
	else if(strcmp(argv[1],"avl") == 0){
		printf("%s : ABR", argv[1]);
	}
	else if(strcmp(argv[1],"avl") == 0){
		printf("%s TAB", argv[1]);
	}
	else { return 911; }
	return 0;
}
