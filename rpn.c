#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Linked list based stack */

// functions are self-explanatory 

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Stack {
	Node *top;
} Stack;

void push(Stack *stack, int value) {
	Node *node = malloc(sizeof(Node));
	node->data = value;
	node->next = stack->top;
	stack->top = node;
}

int pop(Stack *stack) {
	if (stack->top == NULL) {
		exit(1); // the program will halt if there are not enough operands to perform an operation
	}
	Node *node = stack->top;
	stack->top = node->next;
	int value = node->data;
	free(node);
	return value;
}

// provided code
void pstack(Node *top, int first) {
    if (top == NULL) {
        if (first)
            puts ("[ ]");
        return; 
    }
    pstack(top->next, 0);
    printf("%c %d", (top->next ? ',' : '['), top->data);
    if (first)
        puts(" ]");
}

/* end of stack implementation */

int operate(int o1, int o2, char operation) {
	// takes two operands and returns the the result of specified operation
	switch(operation) {
		case '+':
			return o1 + o2;
		case '-':
			return o1 - o2;
		case '*':
			return o1 * o2;
		case '%':
			return o1 % o2;
		default:
			exit(1); // halts if operator is not recognized
	}
}

int main() {
	Stack stack = {NULL};
	char input[3000];
	while (fgets(input, 3000, stdin) != NULL) { // read line
		char* token = strtok(input, " \t\n"); // identifies first token, ignores whitespace
		while (token != NULL) {
			if (isdigit(token[0]) || isdigit(token[1])) { // checks if token is a positive number
				int value = atoi(token);
				push(&stack, value);
			}
			else if (strlen(token) == 1 && strchr("+-*%", token[0]) != NULL) { // check if token is an operation
				int op2 = pop(&stack);
				int op1 = pop(&stack);
				int res = operate(op1, op2, token[0]); // perform operation
				push(&stack, res); // push result
			}
			else {
				exit(1); // halts if token is not recognized
			}
			token = strtok(NULL, " \t\n");
			Node *top = stack.top;
                	pstack(top, 1); // intermediate stack printing
		}
	}
	return 0;
}
