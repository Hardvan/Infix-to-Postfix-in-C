#include <stdio.h>
#include <ctype.h>

#define STACKSIZE 100

struct stack
{
    int items[100];
    int top;
};

void push(struct stack *s, int x)
{
    if (s->top == STACKSIZE - 1)
    {
        printf("STACK OVERFLOW\n");
        return;
    }

    s->top++;
    s->items[s->top] = x;

    return;
}

int pop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("STACK UNDERFLOW\n");
        return;
    }

    int x = s->items[s->top];
    s->top--;

    return x;
}

int stackTop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("STACK UNDERFLOW\n");
        return;
    }

    return s->items[s->top];
}

int ISP(char opr)
{
    switch (opr)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 4;
    case '^':
        return 5;
    default:
        printf("Wrong operator.\n");
    }
}

int ICP(char opr)
{
    switch (opr)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 3;
    case '^':
        return 6;
    default:
        printf("Wrong operator.\n");
    }
}

void InfixToPostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    char symb, topsymb;

    struct stack s;
    s.top = -1;

    while (infix[i] != '\0')
    {
        symb = infix[i++];

        if (isalpha(symb))
        {
            postfix[j++] = symb;
        }

        else if (symb == '(')
        {
            push(&s, symb);
        }

        else if (symb == ')')
        {
            topsymb = pop(&s);

            while (topsymb != '(')
            {
                postfix[j++] = topsymb;
                topsymb = pop(&s);
            }
        }

        else
        {
            while (s.top != -1 && ISP(stackTop(&s)) > ICP(symb))
            {
                topsymb = pop(&s);
                postfix[j++] = topsymb;
            }
            push(&s, symb);
        }
    }

    while (s.top != -1)
    {
        topsymb = pop(&s);
        postfix[j++] = topsymb;
    }
    postfix[j] = '\0';
}

int main()
{
    char infix[100], postfix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    InfixToPostfix(infix, postfix); // Arrays are passed by reference

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}