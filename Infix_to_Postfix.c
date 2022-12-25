#include <stdio.h>
#include <ctype.h>

#define STACKSIZE 100

struct stack
{
    int items[100];
    int top;
};

void push(struct stack *s, char x)
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

char pop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("STACK UNDERFLOW\n");
        return '$';
    }

    char x = s->items[s->top];
    s->top--;

    return x;
}

char stackTop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("STACK UNDERFLOW\n");
        return '$';
    }

    return s->items[s->top];
}

int isEmpty(struct stack *s)
{
    return s->top == -1;
}

// Precedence Order for operators on stack
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

// Precedence Order for current operator
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
    int i = 0; // For infix iteration
    int j = 0; // For postfix iteration
    char symb, topsymb;

    struct stack s; // Stack to store operators
    s.top = -1;

    // Scanning Left to Right
    while (infix[i] != '\0')
    {
        symb = infix[i++];

        if ((symb >= 'a' && symb <= 'z') ||
            (symb >= 'A' && symb <= 'Z')) // Operand (a, b, etc.)
        {
            postfix[j++] = symb;
        }

        else if (symb == '(')
        {
            push(&s, symb); // Directly push
        }

        else if (symb == ')')
        {
            // Pop everything till '('
            while (!isEmpty(&s) && stackTop(&s) != '(')
            {
                // Pop and store in postfix
                postfix[j++] = pop(&s);
            }
            pop(&s); // Discard '('
        }

        else // Operator
        {
            while (!isEmpty(&s))
            {
                topsymb = stackTop(&s);

                if (topsymb == '(')
                    break;

                if (ISP(topsymb) > ICP(symb))
                {
                    // Pop and store in postfix
                    postfix[j++] = pop(&s);
                }
                else
                    break;
            }
            push(&s, symb); // Push current operator on stack
        }
    }

    // Pop remaining operators from stack and store in postfix
    while (!isEmpty(&s))
    {
        // Pop and store in postfix
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0'; // Add null literal
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