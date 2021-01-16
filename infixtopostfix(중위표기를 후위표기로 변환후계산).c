#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int stack_top;

//스택초기화함수 
void init_stack(void)
{
    stack_top = -1;
}

//포화상태 검사 
int get_stack_top(void)
{
    return (stack_top < 0) ? -1 : stack[stack_top];
}


//공백상태 검사 
int is_stack_empty(void)
{
    return (stack_top < 0);
}


//삽입함수 
int push(int t)
{
    if (stack_top >= MAX - 1)
        {
        printf("스택 포화 에러\n");
        exit(1);
        }
    stack[++stack_top] = t;
    return t;
}

//삭제함수 
int pop(void)
{
    if (stack_top < 0)
        {
        printf("스택 공백 에러\n");
        exit(1);
        }
    return stack[stack_top--];
}

// 피크함수
int peek(void)
{
	if (stack_top < 0) {
		printf("스택 공백 에러\n");
		exit(1);
	}
	return stack[stack_top];
}



//연산자인지 확인 
int is_operator(int op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

 
//연산자 우선순위 반환 
int precedence(int op)
{
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// 중위 표기 수식 -> 후위 표기 수식 
void postfix(char *dst, char *src) 
{
    init_stack();		// 스택 초기화 
    while (*src)
        {
        if (*src == '(')
            {
            push(*src);
            src++;
            }
        else if (*src == ')') 
            {
            while (get_stack_top() != '(')	// 왼쪽 괄호를 만날때까지 출력
                {
                *dst++ = pop();
                *dst++ =' ';
            	}
        	pop();
        	src++;
        	}
        else if (is_operator(*src))    //연산자라면 
            {
            while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src))
                {                       //우선순위높은것부터 
                *dst++ = pop();
                *dst++ =' ';
                }
            push(*src);
            src++;
        	}
        else if (*src >= '0' && *src <= '9')    //피연산자라면
        	{
            do
            	{
                *dst++ = *src++;
                } while (*src >= '0' && *src <= '9');
            *dst++ =' ';
            }
        else
            src++;
        }
    while (!is_stack_empty())   // 스택에 저장된 연산자들 출력
        {
        *dst++ = pop();
        *dst++ =' ';
        }
    dst--;
    *dst = 0;
}

 
//후위표기법 계산 
int eval(char *post)
{
    int i;
    init_stack();
    while (*post)
        {
        if (*post >= '0' && *post <= '9')     //피연산자라면
            {
            i = 0;
            do
            	{
                i = i * 10 + *post - '0';
                post++;
                } while (*post >= '0' && *post <= '9');
            push(i);
            }
        else if (*post == '+')     //연산자라면 
            {
            push(pop() + pop());
            post++;
            }
        else if (*post == '*')
            {
            push(pop() * pop());
            post++;
            }
        else if (*post == '-')
            {
            i = pop();
            push(pop() - i);
            post++;
            }
        else if (*post == '/')
            {
            i = pop();
            push(pop() / i);
            post++;
            }
        else
            post++;
        }
    return pop();
}

 

int main()
{
    int result;
    char exp[256], infix[256];
      
    printf("수식을 입력하세요: ");          
    scanf("%s", &infix);
    
    postfix(exp, infix);

    result = eval(exp);   
    printf("결과 : %d", result);
        
    return 0;
}
