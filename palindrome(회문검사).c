//20190924������ 

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
		printf("������ ��á���ϴ�.\n"); 
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
		printf("������ ������ϴ�.\n"); 
		return 0; 
		} 

	re = st->base[st->top]; 
	st->top--; 

	return re; 
	} 

int  palindrome(char str[]) 
{ 
	StackType s; //�迭�� ����� ���, ���Ḯ��Ʈ�� ����ϸ� LinkedStackType s; 
	int i;//�ʿ��� ������ ���� 
	init(&s);//���� �ʱ�ȭ 


		
	char ch, chs;
	int len=strlen(str);
	
	for(i=0;i<len;i++){
		ch=str[i];
		if(ch==' '|| ch==',' || ch=="'") continue;	//ch�� �����̽��ų� ������ 
		ch=tolower(ch);	//ch�� �ҹ��ڷ� ���� 
		push(&s, ch);	//���ÿ� �����Ѵ�. 
	}
	
	for(i=0;i<len;i++){
		ch=str[i];
		if (ch==' '|| ch==',' || ch=="'") continue;
		ch=tolower(ch);
		chs=pop(&s);	//���ÿ��� ���ڸ� ������. 
		if (ch!=chs) return 0;	//���� 
	}
	return 1;
} 

int main(void) 

{ 
	char word[MAX_STRING]; 
	printf("���ڿ��� �Է��Ͻÿ�: "); 
	scanf("%s", word); 
	if (palindrome(word)) 
		printf("ȸ���Դϴ�.\n"); 
	else 
		printf("ȸ���� �ƴմϴ�.\n"); 

	return 0; 
} 
