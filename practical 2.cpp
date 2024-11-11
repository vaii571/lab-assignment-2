//Problem statment:
Implement stack as an abstract data type using singly linked list and use this ADT for conversion of infix 
expression to postfix, prefix and evaluation of postfix and prefix expression.*/
#include<stdlib.h>              //Header Files
#include<iostream>
#include<string.h>
#define max 30                 //Max 30 characters
using namespace std;
struct node                    //Creation of node
{
    char data;                 //value
    struct node* next;         //Address of the next node
};
class stack
{
    node* top;
    char x;                    //Top Value
public:
    stack()                    //constructor
    {
        top = NULL;           //Stack kept empty initially
    }
    int empty()
    {
        if (top == NULL)        //Empty stack condition
        {
            return(1);
        }
        else                   //Stack not empty
        {
            return(0);
        }
    }
    void push(char x)       //Insert element into stack in the form of linked list
    {
        node* p;
        p = new node;
        p->data = x;
        p->next = top;
        top = p;
    }
    char pop()       //Deletion of a node
    {
        if (!empty())
        {
            node* p;
            p = new node;      //top node
            p = top;
            top = top->next;    //Reaching to the top if stack contains multiple nodes
            x = p->data;        //the value of top node gets stored into x
            delete p;           //delete p i.e. top node
            return(x);         //return the value of the deleted node
        }
        else
        {
            cout << "Stack is empty" << endl;
            return(0);
        }
    }
    char pop1()            //Used when there is only one element in the stack
    {
        if (!empty())
        {
            node* p;
            p = new node;
            p = top;
            x = p->data;
            return(x);
        }
        else
        {
            cout << "Stack is empty" << endl;
            return(0);
        }
    }
};
int precedence(char x);                                    //Operation 1: Check Precedence/Priority
void infix_to_prefix(char infix[], char prefix[]);         //Operation 2: Infix to Prefix
void infix_to_postfix(char infix[], char postfix[]);       //Operation 3: Infix to Postfix
void eval_prefix(char prefix[]);                           //Operation 4: Evaluation of Prefix expression
void eval_postfix(char postfix[]);                         //Operation 5: Evaluation of Postfix expression
int evaluate(char x, int op1, int op2);                    //Operation 6: Evaluation of Basic Operation

int main()                                                 //Main function
{
    char infix[30], prefix[30], postfix[30];              //three arrays for stored expressions
    int op;
    do {
        cout << "\n\n\nMenu:: \n1.)Infix to Prefix with Evaluation \n2.)Infix to Postfix with Evaluation \n3.)Quit \nEnter your choice: ";
        cin >> op;

        switch (op)                                   // switch case
        {
        case 1:
            cout << "\nEnter the infix expression::" << endl;
            cin >> infix;
            infix_to_prefix(infix, prefix);                          //calls infix_to_prefix function
            cout << "\nPrefix expression is " << prefix << endl;
            cout << "\n\nEvaluation of Prefix expression \n";
            eval_prefix(prefix);                                     //calls Evaluation of prefix function
            break;
        case 2:
            cout << "\nEnter the infix expression::" << endl;
            cin >> infix;
            infix_to_postfix(infix, postfix);                        //calls infix_to_postfix function
            cout << "\nPostfix expression is " << postfix << endl;
            cout << "\n\nEvaluation of Postfix expression \n";
            eval_postfix(postfix);                                  //calls Evaluation of postfix function
            break;
        }
    } while (op != 3);
    return 0;
}
void infix_to_prefix(char infix[], char prefix[])                 // prefix function
{
    int i, j;                                                     //Variable declaration
    char temp, in1[30];
    cout << "\n\n After step 1 Entered infix is:";
    for (i = 0; i <= strlen(infix) - 1; i++)                     //Reading the expression(0 to total strlen)
    {
        cout << infix[i];
    }
    for (i = strlen(infix) - 1, j = 0; i >= 0; i--, j++)        //Reversal of infix expression
        in1[j] = infix[i];                                      //Storing your reversed array in in1[j]
    in1[j] = '\0';                                              //Ending the array with null value

    cout << "\n\n After step 2:";                              //To make every '(' as ')' and ')' as '('
    for (i = 0; i <= strlen(in1) - 1; i++)
    {
        cout << in1[i];                                        //Traversing reverse string and stored into in1[]
    }

    for (i = 0; in1[i] != '\0'; i++)                           //After performing reverse, traverse 0 to'\0'
    {
        if (in1[i] == '(')
            in1[i] = ')';                                     //If '(',then convert to ')'
        else
            if (in1[i] == ')')                               //If ')', then convert to '('
                in1[i] = '(';
    }
    cout << "\n\n After step 3:";
    for (i = 0; i <= strlen(in1) - 1; i++)               //Storing the new expression after making the changes into int1[]
    {
        cout << in1[i];
    }
    cout << "\n\n After step 4:";                       //Print Final expressions
    cout << "\n\n Prefix is:";
    infix_to_postfix(in1, prefix);                     //calling the postfix function
    for (i = 0, j = strlen(prefix) - 1; i < j; i++, j--)             //Reversing the postfix expression
    {
        temp = prefix[i];                              //Perform Swapping functions
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
}



void infix_to_postfix(char infix[], char postfix[])    //Infix to postfix function
{
    stack s;                                          //Stack
    node* top;                                        //top with address of next node
    char x;                                           //Variable declaration
    int i, j;
    char token;                                       //Value stored in stacks
    j = 0;
    for (i = 0; infix[i] != '\0'; i++)               //Traversing the infix expression
    {
        token = infix[i];                           //Chars & Operators in infix exp gets stored into token
        if (isalnum(token))                         //Check if the char present is string
        {
            postfix[j++] = token;                  //Print into postfix[] & move to next location
        }
        else if (token == '(')                    //Check If '(' operator present
        {
            s.push('(');                          //push into stack
        }
        else if (token == ')')                 //Check If ')' operator present
        {
            while ((x = s.pop()) != '(')       //then pop Operators between '(' ')'
            {
                postfix[j++] = x;             //Storing pop Operators into postfix[]
            }
        }
        else
        {
            x = s.pop1();                    //If only one element is present in stack, call pop1() function
            while (precedence(token) < precedence(x) && !s.empty())        //token= operator in infix string, x= top of the stack
            {
                x = s.pop();                  //If top of the stack has higher precedence operator  than pop
                postfix[j++] = x;             //pop operator print into the output array
            }
            s.push(token);                    //Lower precedence operator push into Stack
        }
    }
    while (!s.empty())                     //If only one operator in Stack
    {
        x = s.pop();                       //pop the operator
        postfix[j++] = x;                  //print into postfix array
    }
    postfix[j] = '\0';                     //end of string
}


int precedence(char x)                      //To check the precedence of operator
{
    if (x == '(')
    {
        return(0);
    }
    if (x == '+' || x == '-')
    {
        return(1);
    }
    if (x == '*' || x == '/' || x == '%')
    {
        return(2);
    }
    return(3);
}

void eval_prefix(char prefix[])                 //Evaluation of prefix string
{
    stack s;
    char x;
    int op1, op2, val, i;                     //variable declaration
    for (i = strlen(prefix) - 1; i >= 0; i--)         //Traversal of the string
    {
        x = prefix[i];                             //Array of string gets stored into 'x'
        if (isalpha(x))                            // If expression has char
        {
            cout << "\nEnter the value of " << x << ":";     //enter the values
            cin >> val;                                     //read the value and store it in 'val'
            s.push(val);                                    //Push value into stack
        }
        else
        {
            op1 = s.pop();                                 //Pop top operands in Stack
            op2 = s.pop();
            val = evaluate(x, op1, op2);                   //call evaluate func
            s.push(val);                                   //push value into stack
        }
    }
    val = s.pop();                                        //pop final values
    cout << "\nValue of expression is " << val;           //Print values
}

void eval_postfix(char postfix[])
{
    stack s;
    char x;
    int op1, op2, val, i;
    for (i = 0; postfix[i] != '\0'; i++)
    {
        x = postfix[i];
        if (isalpha(x))
        {
            cout << "\nEnter the value of " << x << ":";
            cin >> val;
            s.push(val);
        }
        else
        {
            op2 = s.pop();
            op1 = s.pop();
            val = evaluate(x, op1, op2);
            s.push(val);
        }
    }
    val = s.pop();
    cout << "\nValue of expression is " << val;
}

int evaluate(char x, int op1, int op2)                   //evaluate function
{
    if (x == '+')                                        //If x='+' perform addition
        return(op1 + op2);
    if (x == '-')                                       //If x='-' perform subtraction
        return(op1 - op2);
    if (x == '*')                                      //If x= '*' perform multiplication
        return(op1 * op2);
    if (x == '/')                                      //if x= '/' perform division
        return(op1 / op2);
    if (x == '%')                                      //if x= '%' perform mod
        return(op1 % op2);
}
