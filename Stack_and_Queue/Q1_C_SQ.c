//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode {
  int item;
  struct _listnode *next;
} ListNode;  // You should not change the definition of ListNode

typedef struct _linkedlist {
  int size;
  ListNode *head;
} LinkedList;  // You should not change the definition of LinkedList

typedef struct _queue {
  LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes
///////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main()
/////////////////////////////////////////////////

int main() {
  int c, i;
  LinkedList ll;
  Queue q;

  c = 1;

  // Initialize the linked list as an empty linked list
  ll.head = NULL;
  ll.size = 0;

  // Initialize the Queue as an empty queue
  q.ll.head = NULL;
  q.ll.size = 0;

  printf("1: Insert an integer into the linked list:\n");
  printf("2: Create the queue from the linked list:\n");
  printf("3: Remove odd numbers from the queue:\n");
  printf("0: Quit:\n");

  while (c != 0) {
    printf("Please input your choice(1/2/3/0): ");
    scanf("%d", &c);

    switch (c) {
      case 1:
        printf("Input an integer that you want to insert into the List: ");
        scanf("%d", &i);
        insertNode(&ll, ll.size, i);
        printf("The resulting linked list is: ");
        printList(&ll);
        break;
      case 2:
        createQueueFromLinkedList(&ll, &q);  // You need to code this function
        printf("The resulting queue is: ");
        printList(&(q.ll));
        break;
      case 3:
        removeOddValues(&q);  // You need to code this function
        printf("The resulting queue after removing odd integers is: ");
        printList(&(q.ll));
        removeAllItemsFromQueue(&q);
        removeAllItems(&ll);
        break;
      case 0:
        removeAllItemsFromQueue(&q);
        removeAllItems(&ll);
        break;
      default:
        printf("Choice unknown;\n");
        break;
    }
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q) {
  /* add your code here */
  if (ll == NULL || q == NULL) return;

  ListNode *curLL = ll->head;
  ListNode **curQ = &(q->ll.head);

  while (curLL != NULL) {
    ListNode *copyNode = malloc(sizeof(ListNode));
    copyNode->item = curLL->item;
    copyNode->next = NULL;

    if (*curQ == NULL) {
      *curQ = copyNode;
      q->ll.size++;
      curLL = curLL->next;
      continue;
    }

    (*curQ)->next = copyNode;
    q->ll.size++;
    curQ = &((*curQ)->next);
    curLL = curLL->next;
  }
}

void removeOddValues(Queue *q) {
  if (q == NULL || isEmptyQueue(q)) return;

  ListNode **cur = (q->ll.head);

  while (*cur != NULL) {
    if ((*cur)->item % 2 != 0) {  // 현재 노드가 홀수일 때
      ListNode *toDelete = *cur;  // 현재 노드를 가리키는 포인터를 저장
      *cur = (*cur)->next;  // 현재 포인터가 가리키는 위치를 현재 노드의 다음
                            // 노드로 업데이트
      free(toDelete);  // 홀수 노드 메모리 해제
      q->ll.size--;    // 큐 크기 감소
    } else {
      cur = &((*cur)->next);  // 홀수가 아니면 다음 노드로 이동
    }
  }
}

// ------- TO DO -------
// while문 하단의 내용으로 구현
// ---------------------
// void removeOddValues(Queue *q) {
//   if (q == NULL || isEmptyQueue(q)) return;

//   ListNode *cur = (q->ll.head);

//   while (cur != NULL) {
//     // cur가 가르키는 메모리주소값과 head가 가르키는 주소(값 !)이 같은거다.
//     // 주소값의 주소가 아님 그렇기떄문에 cur를 바꿔줘도 q->ll.head는
//     // 변경되지않는다.

//     if ((cur)->item % 2 != 0) {  // 현재 노드가 홀수일 때
//       ListNode *toDelete = cur;  // 현재 노드를 가리키는 포인터를 저장
//       cur = (cur)->next;  // 현재 포인터가 가리키는 위치를 현재 노드의 다음
//                           // 노드로 업데이트
//       free(toDelete);  // 홀수 노드 메모리 해제
//       q->ll.size--;    // 큐 크기 감소
//     } else {
//       cur = ((cur)->next);  // 홀수가 아니면 다음 노드로 이동
//     }
//   }
// }

// void removeOddValues(Queue *q) {
//   /* add your code here */
//   if (q == NULL || isEmptyQueue(q)) return;

//   ListNode **cur, **prev, **temp;

//   cur = &(q->ll.head);
//   prev = &(q->ll.head);
//   temp = NULL;

//   while (*cur != NULL) {
//     // 홀수일때
//     if ((*cur)->item % 2 != 0) {
//       temp = cur;
//       *cur = (*cur)->next;
//       free(temp);
//       q->ll.size--;
//       continue;
//     }

//     prev = cur;
//     cur = &((*cur)->next);
//   }

//   if (q == NULL || isEmptyQueue(q)) return;

//   ListNode *cur = q->ll.head;
//   ListNode *prev = NULL;

//   while (cur != NULL) {
//     if (cur->item % 2 != 0) {  // 홀수일 때
//       if (prev == NULL) {  // 현재 노드가 첫 번째 노드가 아닐 때
//         q->ll.head = cur->next;
//       } else {  // 현재 노드가 첫 번째 노드일 때
//         prev->next = cur->next;
//       }

//       ListNode *nextNode = cur->next;  // 다음 노드를 임시로 저장
//       free(cur);                       // 현재 노드 메모리 해제
//       q->ll.size--;                    // 큐 크기 감소
//       cur = nextNode;                  // 다음 노드로 이동
//     } else {                           // 홀수가 아닐 때
//       prev = cur;
//       cur = cur->next;
//     }
//   }
// }

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) { insertNode(&(q->ll), q->ll.size, item); }

int dequeue(Queue *q) {
  int item;

  if (!isEmptyQueue(q)) {
    item = ((q->ll).head)->item;
    removeNode(&(q->ll), 0);
    return item;
  }
  return -1;
}

int isEmptyQueue(Queue *q) {
  if ((q->ll).size == 0) return 1;
  return 0;
}

void removeAllItemsFromQueue(Queue *q) {
  int count, i;
  if (q == NULL) return;
  count = q->ll.size;

  for (i = 0; i < count; i++) dequeue(q);
}

void printList(LinkedList *ll) {

  ListNode *cur;
  if (ll == NULL) return;
  cur = ll->head;
  if (cur == NULL) printf("Empty");
  while (cur != NULL) {
    printf("%d ", cur->item);
    cur = cur->next;
  }
  printf("\n");
}

void removeAllItems(LinkedList *ll) {
  ListNode *cur = ll->head;
  ListNode *tmp;

  while (cur != NULL) {
    tmp = cur->next;
    free(cur);
    cur = tmp;
  }
  ll->head = NULL;
  ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index) {

  ListNode *temp;

  if (ll == NULL || index < 0 || index >= ll->size) return NULL;

  temp = ll->head;

  if (temp == NULL || index < 0) return NULL;

  while (index > 0) {
    temp = temp->next;
    if (temp == NULL) return NULL;
    index--;
  }

  return temp;
}

int insertNode(LinkedList *ll, int index, int value) {

  ListNode *pre, *cur;

  if (ll == NULL || index < 0 || index > ll->size + 1) return -1;

  // If empty list or inserting first node, need to update head pointer
  if (ll->head == NULL || index == 0) {
    cur = ll->head;
    ll->head = malloc(sizeof(ListNode));
    if (ll->head == NULL) {
      exit(0);
    }
    ll->head->item = value;
    ll->head->next = cur;
    ll->size++;
    return 0;
  }

  // Find the nodes before and at the target position
  // Create a new node and reconnect the links
  if ((pre = findNode(ll, index - 1)) != NULL) {
    cur = pre->next;
    pre->next = malloc(sizeof(ListNode));
    if (pre->next == NULL) {
      exit(0);
    }
    pre->next->item = value;
    pre->next->next = cur;
    ll->size++;
    return 0;
  }

  return -1;
}

int removeNode(LinkedList *ll, int index) {

  ListNode *pre, *cur;

  // Highest index we can remove is size-1
  if (ll == NULL || index < 0 || index >= ll->size) return -1;

  // If removing first node, need to update head pointer
  if (index == 0) {
    cur = ll->head->next;
    free(ll->head);
    ll->head = cur;
    ll->size--;
    return 0;
  }

  // Find the nodes before and after the target position
  // Free the target node and reconnect the links
  if ((pre = findNode(ll, index - 1)) != NULL) {

    if (pre->next == NULL) return -1;

    cur = pre->next;
    pre->next = cur->next;
    free(cur);
    ll->size--;
    return 0;
  }

  return -1;
}
