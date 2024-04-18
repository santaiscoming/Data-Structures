//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode {
  int item;
  struct _bstnode *left;
  struct _bstnode *right;
} BSTNode;  // You should not change the definition of BSTNode

typedef struct _stackNode {
  BSTNode *data;
  struct _stackNode *next;
} StackNode;  // You should not change the definition of StackNode

typedef struct _stack {
  StackNode *top;
} Stack;  // You should not change the definition of Stack

///////////////////////// function prototypes
///////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main()
////////////////////////////////////////////////

int main() {
  int c, i;
  c = 1;

  // Initialize the Binary Search Tree as an empty Binary Search Tree
  BSTNode *root;
  root = NULL;

  printf("1: Insert an integer into the binary search tree;\n");
  printf("2: Print the post-order traversal of the binary search tree;\n");
  printf("0: Quit;\n");

  while (c != 0) {
    printf("Please input your choice(1/2/0): ");
    scanf("%d", &c);

    switch (c) {
      case 1:
        printf(
            "Input an integer that you want to insert into the Binary Search "
            "Tree: ");
        scanf("%d", &i);
        insertBSTNode(&root, i);
        break;
      case 2:
        printf(
            "The resulting post-order traversal of the binary search tree "
            "is: ");
        postOrderIterativeS1(root);  // You need to code this function
        printf("\n");
        break;
      case 0:
        removeAll(&root);
        break;
      default:
        printf("Choice unknown;\n");
        break;
    }
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root) {
  /* add your code here */
  Stack s;
  s.top = NULL;
  BSTNode *cur = NULL;

  push(&s, root);
  push(&s, root->right);
  push(&s, root->left);

  while (!isEmpty(&s)) {
    /* code */
    cur = pop(&s);

    if (root == cur) {
      printf("%d ", cur->item);
      break;
    }

    if (peek(&s)->item == cur->item) {
      printf("%d ", cur->item);
      pop(&s);
      continue;
    }

    if (cur->left || cur->right) {
      push(&s, cur);
      push(&s, cur);
      if (cur->right) push(&s, cur->right);
      if (cur->left) push(&s, cur->left);
    } else {
      printf("%d ", cur->item);
    }
  }

  // while (!isEmpty(&s)) {
  //   /* code */
  //   cur = pop(&s);

  //   if (root == cur) {
  //     printf("%d ", cur->item);
  //     break;
  //   }

  //   // 이미 방문한 노드
  //   if (peek(&s)->item == cur->item) {
  //     pop(&s);
  //     printf("%d ", cur->item);
  //     continue;
  //   }

  //   // cur가 leaf일때
  //   if (!cur->right && !cur->left) {
  //     printf("%d ", cur->item);
  //   } else {  // 자식이 하나라도 있을때
  //     push(&s, cur);
  //     push(&s, cur);
  //     if (cur->right) push(&s, cur->right);
  //     if (cur->left) push(&s, cur->left);
  //   }

  // while (cur || !isEmpty(&s)) {
  //   if (cur) {
  //     if (cur->right) push(&s, cur->right);

  //     push(&s, cur);
  //     cur = cur->left;
  //     continue;
  //   }

  //   if (!cur) {
  //     cur = pop(&s);

  //     // 아직 방문하지 않았따
  //     if (cur->right && cur->right == peek(&s)) {
  //       // right가 stack에 담겨있으므로 오른쪽으로 가야함
  //       pop(&s);
  //       push(&s, cur);
  //       cur = cur->right;
  //     } else {  // 오른쪽을 이미 방문한경우
  //       printf("%d ", cur->item);
  //       // 현재 노드를 방문했으니 Null로
  //       cur = NULL;
  //     }
  //   }
  // }
}

void postOrderIterativeS12(BSTNode *root) {

  if (root == NULL) return;

  Stack s;
  s.top = 0;

  BSTNode *cur = root;
  BSTNode *lastVisited = NULL;

  while (cur || !isEmpty(&s)) {
    // 가장 마지막에 돌아야하니까 먼저 넣어준다
    if (cur) {
      push(&s, cur);
      cur = cur->left;
      continue;
    }

    // 20, 15, 10까지 내려가니까 Null이됨
    // 이제 더이상 내려갈곳이 없으니 방문한다
    // 10인경우는 사라지고 15일때 s : [20, 15]
    if (!cur) {
      BSTNode *lastPrevNode = peek(&s);
      // 지금까지 왼쪽으로만 탐색했는데 오른족이 있으면 오른쪽을 보고나서
      // cur를 방문해야한다.
      if (lastPrevNode->right && lastVisited != lastPrevNode->right) {
        cur = lastPrevNode->right;
      } else {  // 현재는 왼쪽노드, 오른쪽 노드가 없다면 (왼 -> 오 -> 방) 에
                // 의해 오른쪽으로 가야한다.
        // **방문로직**
        printf("%d ", lastPrevNode->item);
        lastVisited = pop(&s);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value) {
  if (*node == NULL) {
    *node = malloc(sizeof(BSTNode));

    if (*node != NULL) {
      (*node)->item = value;
      (*node)->left = NULL;
      (*node)->right = NULL;
    }
  } else {
    if (value < (*node)->item) {
      insertBSTNode(&((*node)->left), value);
    } else if (value > (*node)->item) {
      insertBSTNode(&((*node)->right), value);
    } else
      return;
  }
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node) {
  StackNode *temp;

  temp = malloc(sizeof(StackNode));

  if (temp == NULL) return;
  temp->data = node;

  if (stack->top == NULL) {
    stack->top = temp;
    temp->next = NULL;
  } else {
    temp->next = stack->top;
    stack->top = temp;
  }
}

BSTNode *pop(Stack *s) {
  StackNode *temp, *t;
  BSTNode *ptr;
  ptr = NULL;

  t = s->top;
  if (t != NULL) {
    temp = t->next;
    ptr = t->data;

    s->top = temp;
    free(t);
    t = NULL;
  }

  return ptr;
}

BSTNode *peek(Stack *s) {
  StackNode *temp;
  temp = s->top;
  if (temp != NULL)
    return temp->data;
  else
    return NULL;
}

int isEmpty(Stack *s) {
  if (s->top == NULL)
    return 1;
  else
    return 0;
}

void removeAll(BSTNode **node) {
  if (*node != NULL) {
    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);
    *node = NULL;
  }
}
