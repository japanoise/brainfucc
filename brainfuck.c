#include<stdlib.h>
#include<stdio.h>
struct bfcell{
	char data;
	struct bfcell *left;
	struct bfcell *right;
};

struct bfcell *newcell(struct bfcell *left,struct bfcell *right){
	struct bfcell *retval = malloc(sizeof(struct bfcell));
	retval->left = left;
	retval->right = right;
	retval->data = 0;
	return retval;
}

struct bfcell *here;

int run(char c, FILE *file){
	long pos;
	switch(c){
		case '+':
			here->data++;
			break;
		case '-':
			here->data--;
			break;
		case '.':
			putchar(here->data);
			break;
		case ',':
			here->data = getchar();
			break;
		case '>':
			if(here->right==NULL){
				here->right=newcell(here,NULL);
			}
			here=here->right;
			break;
		case '<':
			if(here->left==NULL){
				here->left=newcell(NULL,here);
			}
			here=here->left;
			break;
		case '[':
			if(here->data==0){
				int brackets=1;
				while(brackets!=0){
					c=getc(file);
					if(c==']')brackets--;
					if(c=='[')brackets++;
					if(c==EOF)return 1;
				}
			}else{
				pos = ftell(file);
				while(here->data!=0){
					fseek(file,pos,SEEK_SET);
					c=getc(file);
					while(c!=']' && c!=EOF){
						if(run(c,file)!=0)return 1;
						c=getc(file);
					}
				}
			}
			break;
	}
	return 0;
}

int main(int argc, char **argv){
	FILE *file = fopen(argv[1],"r");
	int retval = 0;
	here = newcell(NULL,NULL);
	if(file==NULL){
		fprintf(stderr,"%s: can't open file %s\n",argv[0],argv[1]);
		return 1;
	}
	char c = getc(file);
	while(c!=EOF){
		retval += run(c,file);
		c = getc(file);
	}
	return retval;
}
