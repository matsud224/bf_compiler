#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <map>

using namespace std;


int main(void)
{
	int label_id = 0;
    char c;
    stack<int> lbrackets;

	fprintf(stdout,	".comm tape,120000\n"
					".text\n"
					".globl main\n"
					"main:\n"
					"mov $tape, %%r8\n");
	fprintf(stdout, "mov $0x1, %%rdx\n");

	int32_t ptradd = 0;
    map<int32_t,int8_t> tape_mod;

    while((c=getchar()) != EOF){
		if(c!='>' && c!='<' && c!='+' && c!='-'){
			for(map<int32_t,int8_t>::iterator iter = tape_mod.begin(); iter != tape_mod.end(); iter++){
				if((*iter).second==1)
					fprintf(stdout, "incb %d(%%r8)\n", (*iter).first);
				else if ((*iter).second==-1)
					fprintf(stdout, "decb %d(%%r8)\n", (*iter).first);
				else if ((*iter).second>0)
					fprintf(stdout, "addb $0x%x, %d(%%r8)\n", (*iter).second, (*iter).first);
				else if ((*iter).second<0)
					fprintf(stdout, "subb $0x%x, %d(%%r8)\n", -((*iter).second), (*iter).first);
			}
			if(ptradd==1)
				fprintf(stdout, "inc %%r8\n");
			else if (ptradd==-1)
				fprintf(stdout, "dec %%r8\n");
			else if (ptradd>0)
				fprintf(stdout, "add $0x%x, %%r8\n", ptradd);
			else if (ptradd<0)
				fprintf(stdout, "sub $0x%x, %%r8\n", -ptradd);

			ptradd=0;
			tape_mod.clear();
		}

		switch(c){
		case '>':
			ptradd++;
			break;
		case '<':
			ptradd--;
			break;
		case '+':
			tape_mod[ptradd]++;
			break;
		case '-':
			tape_mod[ptradd]--;
			break;
		case ',':
			fprintf(stdout, "mov $0x0, %%rax\n");
			fprintf(stdout, "mov $0x0, %%rdi\n");
			fprintf(stdout, "mov %%r8, %%rsi\n");
			fprintf(stdout, "syscall\n");
			break;
		case '.':
			fprintf(stdout, "mov $0x1, %%rax\n");
			fprintf(stdout, "mov $0x1, %%rdi\n");
			fprintf(stdout, "mov %%r8, %%rsi\n");
			fprintf(stdout, "syscall\n");
			break;
		case '[':
			fprintf(stdout, "cmpb $0x0, 0(%%r8)\n");
			fprintf(stdout, "jz label%d\n", label_id++);
			fprintf(stdout, "label%d:\n", label_id++);
			lbrackets.push(label_id);
			break;
		case ']':
			if(lbrackets.empty()){
				fprintf(stderr, "\nerror: no matching rbracket!\n");
				return -1;
			}
			fprintf(stdout, "cmpb $0x0, 0(%%r8)\n");
			fprintf(stdout, "jnz label%d\n", lbrackets.top()-1);
			fprintf(stdout, "label%d:\n", lbrackets.top()-2);
			lbrackets.pop();
			break;
		}
    }


    fprintf(stdout, "ret\n");

    if(!lbrackets.empty()){
		fprintf(stderr, "\nerror: no matching lbracket!\n");
		return -1;
	}

    return 0;
}
