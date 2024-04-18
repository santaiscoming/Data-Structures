//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode {
  int item;
  struct _btnode *left;
  struct _btnode *right;
} BTNode;  // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode {
  BTNode *btnode;
  struct _stackNode *next;
} StackNode;

typedef struct _stack {
  StackNode *top;
} Stack;

///////////////////////// function prototypes
///////////////////////////////////////

// You should not change the prototypes of these functions
int countOneChildNodes(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stack, BTNode *node);
BTNode *pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main()
////////////////////////////////////////////////

int main() {
  char e;
  int c, s;
  BTNode *root;

  c = 1;
  root = NULL;

  printf("1: Create a binary tree.\n");
  printf("2: Count the number of nodes that have exactly one child node.\n");
  printf("0: Quit;\n");

  while (c != 0) {
    printf("Please input your choice(1/2/0): ");
    if (scanf("%d", &c) > 0) {
      switch (c) {
        case 1:
          removeAll(&root);
          root = createTree();
          printf("The resulting binary tree is: ");
          printTree(root);
          printf("\n");
          break;
        case 2:
          s = countOneChildNodes(root);
          printf(
              "The number of nodes that have exactly one child node is: %d.\n",
              s);
          removeAll(&root);
          break;
        case 0:
          removeAll(&root);
          break;
        default:
          printf("Choice unknown;\n");
          break;
      }
    } else {
      scanf("%c", &e);
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int countOneChildNodes(BTNode *node) {
  /* add your code here */
  // 깊이 탐색해도 종료되지않도록 수정됨
  //   if (node == NULL) {
  //     return 0;
  //   }

  //   int count = 0;

  //   if (((node->left) && !(node->right)) || (!(node->left) && (node->right)))
  //   {
  //     count = 1;
  //   }

  //   return count + countOneChildNodes(node->left) +
  //          countOneChildNodes(node->right);

  // 처음 만나는 OneChildNode가 있을때 종료됨
  //   if (!(node->left) && !(node->right)) return 0;

  //   Stack s;
  //   s.top = NULL;
  //   int count = 0;

  //   // left 와 right 둘중 하나만 있을때
  //   if ((!(node->left) && (node->right)) || ((node->left) && !(node->right)))
  //   {
  //     return 1;
  //   }

  //   return countOneChildNodes(node->right) + countOneChildNodes(node->left);

  //   using Stack struct
  Stack stack;
  stack.top = NULL;
  BTNode *cur = node;
  int count = 0;

  while (cur != NULL || stack.top != NULL) {
    if (cur != NULL) {
      if ((cur->left != NULL && cur->right == NULL) ||
          (cur->left == NULL && cur->right != NULL)) {
        count++;
      }
      if (cur->right != NULL) {
        push(&stack, cur->right);
      }
      cur = cur->left;
    } else {
      cur = pop(&stack);
    }
  }

  return count;
}

///////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item) {
  BTNode *newNode = malloc(sizeof(BTNode));
  newNode->item = item;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree() {
  Stack stack;
  BTNode *root, *temp;
  char s;
  int item;

  stack.top = NULL;
  root = NULL;
  printf(
      "Input an integer that you want to add to the binary tree. Any Alpha "
      "value will be treated as NULL.\n");
  printf("Enter an integer value for the root: ");
  if (scanf("%d", &item) > 0) {
    root = createBTNode(item);
    push(&stack, root);
  } else {
    scanf("%c", &s);
  }

  while ((temp = pop(&stack)) != NULL) {

    printf("Enter an integer value for the Left child of %d: ", temp->item);

    if (scanf("%d", &item) > 0) {
      temp->left = createBTNode(item);
    } else {
      scanf("%c", &s);
    }

    printf("Enter an integer value for the Right child of %d: ", temp->item);
    if (scanf("%d", &item) > 0) {
      temp->right = createBTNode(item);
    } else {
      scanf("%c", &s);
    }

    if (temp->right != NULL) push(&stack, temp->right);
    if (temp->left != NULL) push(&stack, temp->left);
  }
  return root;
}

void push(Stack *stack, BTNode *node) {
  StackNode *temp;

  temp = malloc(sizeof(StackNode));
  if (temp == NULL) return;
  temp->btnode = node;
  if (stack->top == NULL) {
    stack->top = temp;
    temp->next = NULL;
  } else {
    temp->next = stack->top;
    stack->top = temp;
  }
}

BTNode *pop(Stack *stack) {
  StackNode *temp, *top;
  BTNode *ptr;
  ptr = NULL;

  top = stack->top;
  if (top != NULL) {
    temp = top->next;
    ptr = top->btnode;

    stack->top = temp;
    free(top);
    top = NULL;
  }
  return ptr;
}

void printTree(BTNode *node) {
  if (node == NULL) return;

  printTree(node->left);
  printf("%d ", node->item);
  printTree(node->right);
}

void removeAll(BTNode **node) {
  if (*node != NULL) {
    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);
    *node = NULL;
  }
}
