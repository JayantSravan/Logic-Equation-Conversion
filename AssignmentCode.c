#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <strings.h>
#define max 1000000

//*********************************************************************DECLARATION OF VARIBLES AND FUNCTIONS*****************************************************************************************

//Varible Declarations
char stack_ini[max];

int store_arr[59];

//definition of the node structure
struct node {
   char data;
   int value;
   struct node* rc;
   struct node* lc;
};

struct node* stack[1000000];
struct node* temp;
struct node* root;
char prefix[1000000];//prefix array
char infix[1000000];//infix array
char truthValue;

int store_arr[59];

int top=-1;
int selection, choice;
//char q[1000000000];
int n;
int count=0;

//Function Declarations
void infixToPrefix(char infix[1000000],char prefix[1000000]); //storing infix ,prefix

void reverse(char entry[1000000]);//function to reverse the input

char pop();   //removing last entered element from s101000000
void push(char c); //input element to stack

int precedence(char c); // check for precedence of operators to find prefix order

int operatorCheck(char c);  // check that the operator is only among the 6
                            // operators (including parenthesis).

void pushStack(struct node* t); //push the node into the stack(for task 2)

struct node* popStack(); //pop the node from the stack

void buildTree();   // creating the parse tree

void inOrderTraversal(struct node *a); // inOrderTraversal of parse tree created using build tree

int height(struct node *root);  // height of parse Tree

void create(char infix[]);      // generate a random infix expression

void initialise_store_arr(int store_arr[]);  // initialise all elements of the array to value 2

void reset();     // converts to prefix and builds the parse tree

void input_truth(struct node *a);   // inputing valuations of the atoms in the parse tree

int evaluate(struct node *node);    //evaluating the expression  using the truth values , enterred using input_truth function.

int find(int left_val,char operator,int right_val);  // contains truth table of basic natural deduction laws(and,or,implication,negation),a

int choiceOfInput();            //Interface related

void convertToPrefix();         //Interface related

void proceed();                 //Interface related

int menu();	                //Interface related

void getInput(int selection);	//Interface related


//******************************************************************************MAIN FUNCTION************************************************************************************************

int main()
{

selection=choiceOfInput();
getInput(selection);


while(1)
	{
	choice= menu();
  proceed(choice);
	if(choice==0)
	break;
	}


printf("Thank you for visiting\n");
printf("See you soon\n");
return 0;
}


//**************************************************************************END OF MAIN FUNCTION*******************************************************************************************

//*********************************************************************************TASK 1**************************************************************************************************
void convertToPrefix()
{
	infixToPrefix(infix,prefix); // Conversion of infix-
	reverse(prefix);             //- statement to prefix statement.
}

void reset()
{
  convertToPrefix();
  buildTree();

}

void infixToPrefix(char infix[101000000], char prefix[101000000]){
    int i=0,j=0;
    char token;
    stack_ini[++top]='#';
    reverse(infix);

    for(i=0;i<strlen(infix);i++){
        token=infix[i];
        if(operatorCheck(token)==0){//if not operator
            prefix[j]=token;
            j++;
        } else{ //if it is one of the 6 operators
            if(token==')'){
                push(token);
            }
            else if(token=='('){
                while (stack_ini[top]!=')'){
                    prefix[j]=pop();
                    j++;
                }
                pop();
            }
            else{
                if(precedence(stack_ini[top])<=precedence(token)){
                    push(token);
                }
                else{
                    while (precedence(stack_ini[top])>=precedence(token)){
                        prefix[j]=pop();
                        j++;
                    }
                    push(token);
                }
            }
        }
    }

    while (stack_ini[top]!='#'){
        prefix[j]=pop();
        j++;

    }
    prefix[j]='\0';
}


void reverse(char entry[1000000]){

    char temp[1000000];
    int i,j;

    for(i=strlen(entry)-1,j=0;i>=0;i--,j++){
        temp[j]=entry[i];
    }

    temp[j]='\0';
    strcpy(entry,temp);
}

char pop(){

    char c;
    c=stack_ini[top];
    top--;
    return c;
}


void push(char c){

    top++;
    stack_ini[top]=c;
}


int precedence(char c){

    switch (c){//checking for precedence
        case '~':
            return 5;
            break;
        case '*':
            return 4;
            break;
        case '+':
                  return 3;
                  break;
        case '>':
                return 2;
                break;
        case '(':
        case ')':return 1;
                  break;
        case '#':
                  return 0;
                  break;
    }
}


int operatorCheck(char c){

    switch (c){
        case '~':case '*':case '+':case '>':case '(': case ')'://if operator return 1 else 0
                return 1;
                break;
        default:
                return 0;
    }
}





//*************************************************************************************TASK 2************************************************************************************************

void pushStack(struct node* t){
    stack[++top]=t;
}


struct node* popStack(){
    return (stack[top--]);
}

void buildTree(){
    int i=strlen(prefix)-1;

    while (i>=0){

        switch (prefix[i]){
            case '+':
            case '*':
            case '>'://case for +,*,>
                temp=(struct node*)malloc(sizeof(struct node));
                temp->data=prefix[i];
                temp->lc=popStack();
                temp->rc=popStack();
                pushStack(temp);
                break;

            case '~'://case for ~
                temp=(struct node*)malloc(sizeof(struct node));
                temp->data=prefix[i];
                temp->lc=NULL;
                temp->rc=popStack();
                pushStack(temp);
                break;

            default://case for non-operators
                temp=(struct node*)malloc(sizeof(struct node));
                temp->data=prefix[i];
                temp->lc=NULL;
                temp->rc=NULL;
                pushStack(temp);

        }
        i--;
    }
    root=stack[top];//storing top of stack in root
}

//*************************************************************************************TASK 3*************************************************************************************************

void inOrderTraversal(struct node *a) {
    if (a == NULL) return;

    printf("(");

    inOrderTraversal(a->lc);
    printf("%c",a->data);
    inOrderTraversal(a->rc);

    printf(")");

}

//*************************************************************************************TASK 4**************************************************************************************************

int height(struct node *temp){         // implementation of the height function

  if(temp==NULL){return 0;}

  else {                               //calculate height of left subtree and right subtree separately
       int left = height(temp->lc);
       int right = height(temp->rc);

       if(left>right){                 // choose max of height of(left subtree ,right subtree)

                     return(left+1);
		     }

       else {
            return (right+1);
            }

   }
}


//*************************************************************************************TASK 5**************************************************************************************************

void initialise_store_arr(int store_arr[])   // initialise truth values of all possible leaves of the parse tree to -1
                                             //   ie no truth value has been enterred
	{
	     int i;

             for(i=0;i<59;i++)
	     {

                   store_arr[i]=2;
             }
	}


void input_truth(struct node *a)
{

         if (a == NULL) return;

         input_truth(a->lc);

         if( (a->lc==NULL && a->rc==NULL))
		{

                       int x,i;
                       char input;

                       i=a->data;
                       i=i-64;            // index of the corresponding leaf in the array

	               if(store_arr[i]==2)
				{
			        printf("%c : ",a->data);
                 		scanf(" %c",&input);      // prompt user input
                   		x = (input=='T')?1:0;
                  		store_arr[i]=x;         // store truth value at the corresponding in the store_array
				}

       		      else{
    			  x=store_arr[i];
			  }

         	      a->value=x;

 		 }

         input_truth(a->rc);

}


void random_input(struct node *a)
{

         if (a == NULL) return;

         random_input(a->lc);

         if( (a->lc==NULL && a->rc==NULL))
		{
            int x = (rand() % 2);      // randomly choose truth value of the leaf
            int i;
            char ch = (x==1)?'T':'F';

            i=a->data;
            i=i-64;

                if(store_arr[i]==2){

                      store_arr[i]=x;                    // store truth value at the corresponding in the store_array
                      printf("%c  :  %c\n",a->data,ch);
                }

                else{
                      x=store_arr[i];
                }

                a->value=x;
    }
                random_input(a->rc);
}



int evaluate(struct node *node)
{

     if(node->lc!=NULL || node->rc!=NULL )     // condition for the node to be aa leaf
	  {

          int left_val;

          if(node->lc!=NULL)
		{
		left_val = evaluate(node->lc);
	        }

          else{
              left_val = 0;
              }

          int right_val = evaluate(node->rc);

          int val = find(left_val,node->data,right_val);     // evaluate sub expression using the find dunction

          return val;
    	  }

     else {
          return node->value;
     	  }
}


int find(int left_val,char operator,int right_val){    // truth implementation using bitwise operators

             if(operator == '~'){
               return ((~right_val)+2);
             }

             else if(operator == '*' ){
               return left_val & right_val;
             }

             else if(operator == '+'){
               return left_val | right_val;
             }

             else if(operator == '>'){
               return ((~left_val) | (right_val));
             }
}

//*******************************************************************************INTERFACING FUNCTIONS******************************************************************************************

int choiceOfInput()
{
	int c;
	printf("Select the type of input:\n 1.Custom                2.Random\n");
        do
		{
		scanf("%d",&c);
		if(c!= 1 && c!= 2)
		printf("Invalid selection. Press 1 or 2.\n");
		}
	while(c!=1 && c!=2);

	if(c==1||c==2)
	return c;
}

int menu()
{
	printf("What do you want to do with the formula??\n");
	printf("1. Print the prefix formula\n");
	printf("2. Print the infix formula from the parse tree\n");
	printf("3. Find the height of the Parse Tree\n");
	if(selection==1)printf("4. Evaluate truth value of the formula\n");
  else printf("4. Evaluate truth value of the formula(randomly generated inputs)\n");
	printf("5. Input another formula\n");
	printf("0. EXIT\n");
	printf("Select any option to proceed: ");
        printf("\n");
	scanf("%d",&choice);
	return choice;
}

void proceed()
{
	switch(choice)
	{
		case 2: inOrderTraversal(root);
			printf("\n");
			printf("\n");
			break;
		case 1: printf("%s",prefix);
			printf("\n");
			printf("\n");
			break;
		case 3: printf("\nHEIGHT OF PARSE Tree : %d\n",height(root));
			printf("\n");
			break;
		case 4:
              if(selection==1){
                        printf("Enter 'T' for true  and 'F' for false\n");
                        initialise_store_arr(store_arr);

                        input_truth(root);

			if(evaluate(root)==1){
        truthValue = 'T';
    }
			else{
        truthValue = 'F';

      }

  }
	         else{
             initialise_store_arr(store_arr);
             random_input(root);

             if(evaluate(root)==1){

               truthValue = 'T';

             }
              else{

                truthValue = 'F';
              }
  }


			printf("Truth value of expression : %c \n",truthValue);
			printf("\n");
			break;
		case 5: selection=choiceOfInput();
            getInput(selection);

			break;
		case 0: return;
			break;
		default: printf("Please enter a valid choice\n");
			 printf("\n");
	}
}

void getInput(int selection)
{
if(selection==1)
	{
	printf("ENTER AN INFIX STATEMENT :\n");
        scanf("%s",infix);
        reset();
	}
else    {
	printf("Enter number of Literals\n");

  scanf("%d",&n);
  char d;
  int y;
  bzero(infix,1000000);

  create(infix);
  reset();
	}
}



void create(char infix[])
{
int v=(rand() % 26)+97;
int w=(rand() % 4)+1;
char bb[2];
bb[1]='\0';
switch(w)
{
  case 1: bb[0]='+';
          break;

  case 2: bb[0]='*';
          break;

  case 3: bb[0]='>';
          break;

  case 4: bb[0]='~';
          break;
}
char aa[2]={(char)(v),'\0'};

char l[2]; l[0]='(';l[1]='\0';
char r[2]; r[0]=')';r[1]='\0';
if(count==n)
 {
 infix= strcat(infix, aa);

 return;
 }
 else
 {

  if(w==1||w==2||w==3)
  {
   infix= strcat(infix,aa);
   infix= strcat(infix,bb);
   infix= strcat(infix,l);

   count++;
   create(infix);
   infix= strcat(infix,r);
  }
  else
  {
    infix = strcat(infix,bb);
    infix = strcat(infix,l);

    count++;
    create(infix);
    infix= strcat(infix,r);
  }
 }
}



//********************************************************************************END OF PROGRAM**************************************************************************************************
