//20190924옥지원 

#include<stdio.h> 
#define MAX_STRING  100 

typedef struct{
	char base[MAX_STRING]; 
	int top; 
}StackType; 

void init(StackType *st) 
{
	st->top = -1; 
 } 

int full(StackType *st) 
{
	return (st->top+1) == MAX_STRING; 
} 

int empty(StackType *st) 
{ 
	return st->top == -1; 
} 

void push(StackType *st,char ch) 
{ 
	if(full(st)) 
	{ 
		printf("스택이 꽉찼습니다.\n"); 
	} 
	else 
	{ 
		st->top++; 
		st->base[st->top] = ch;        
	} 
} 

char pop(StackType *st) 
	{ 
	int re = 0; 
	if(empty(st)) 
		{ 
		printf("스택이 비었습니다.\n"); 
		return 0; 
		} 

	re = st->base[st->top]; 
	st->top--; 

	return re; 
	} 

int  palindrome(char str[]) 
{ 
	StackType s; //배열을 사용할 경우, 연결리스트를 사용하면 LinkedStackType s; 
	int i;//필요한 변수들 선언 
	init(&s);//스택 초기화 


		
	char ch, chs;
	int len=strlen(str);
	
	for(i=0;i<len;i++){
		ch=str[i];
		if(ch==' '|| ch==',' || ch=="'") continue;	//ch가 스페이스거나 구두점 
		ch=tolower(ch);	//ch를 소문자로 변경 
		push(&s, ch);	//스택에 삽입한다. 
	}
	
	for(i=0;i<len;i++){
		ch=str[i];
		if (ch==' '|| ch==',' || ch=="'") continue;
		ch=tolower(ch);
		chs=pop(&s);	//스택에서 문자를 꺼낸다. 
		if (ch!=chs) return 0;	//실패 
	}
	return 1;
} 

int main(void) 

{ 
	char word[MAX_STRING]; 
	printf("문자열을 입력하시오: "); 
	scanf("%s", word); 
	if (palindrome(word)) 
		printf("회문입니다.\n"); 
	else 
		printf("회문이 아닙니다.\n"); 

	return 0; 
} 
