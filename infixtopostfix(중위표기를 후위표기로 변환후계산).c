//20190924������ 

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int stack_top;

//�����ʱ�ȭ�Լ� 
void init_stack(void)
{
    stack_top = -1;
}

//��ȭ���� �˻� 
int get_stack_top(void)
{
    return (stack_top < 0) ? -1 : stack[stack_top];
}


//������� �˻� 
int is_stack_empty(void)
{
    return (stack_top < 0);
}


//�����Լ� 
int push(int t)
{
    if (stack_top >= MAX - 1)
        {
        printf("���� ��ȭ ����\n");
        exit(1);
        }
    stack[++stack_top] = t;
    return t;
}

//�����Լ� 
int pop(void)
{
    if (stack_top < 0)
        {
        printf("���� ���� ����\n");
        exit(1);
        }
    return stack[stack_top--];
}

// ��ũ�Լ�
int peek(void)
{
	if (stack_top < 0) {
		printf("���� ���� ����\n");
		exit(1);
	}
	return stack[stack_top];
}



//���������� Ȯ�� 
int is_operator(int op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

 
//������ �켱���� ��ȯ 
int precedence(int op)
{
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// ���� ǥ�� ���� -> ���� ǥ�� ���� 
void postfix(char *dst, char *src) 
{
    init_stack();		// ���� �ʱ�ȭ 
    while (*src)
        {
        if (*src == '(')
            {
            push(*src);
            src++;
            }
        else if (*src == ')') 
            {
            while (get_stack_top() != '(')	// ���� ��ȣ�� ���������� ���
                {
                *dst++ = pop();
                *dst++ =' ';
            	}
        	pop();
        	src++;
        	}
        else if (is_operator(*src))    //�����ڶ�� 
            {
            while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src))
                {                       //�켱���������ͺ��� 
                *dst++ = pop();
                *dst++ =' ';
                }
            push(*src);
            src++;
        	}
        else if (*src >= '0' && *src <= '9')    //�ǿ����ڶ��
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
    while (!is_stack_empty())   // ���ÿ� ����� �����ڵ� ���
        {
        *dst++ = pop();
        *dst++ =' ';
        }
    dst--;
    *dst = 0;
}

 
//����ǥ��� ��� 
int eval(char *post)
{
    int i;
    init_stack();
    while (*post)
        {
        if (*post >= '0' && *post <= '9')     //�ǿ����ڶ��
            {
            i = 0;
            do
            	{
                i = i * 10 + *post - '0';
                post++;
                } while (*post >= '0' && *post <= '9');
            push(i);
            }
        else if (*post == '+')     //�����ڶ�� 
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
      
    printf("������ �Է��ϼ���: ");          
    scanf("%s", &infix);
    
    postfix(exp, infix);

    result = eval(exp);   
    printf("��� : %d", result);
        
    return 0;
}

/*
    if(scanf("%s", &infix)==EOF)
        {
        printf("\n");
        exit(0);
        }
        */
