#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100         //����Ԫ�ظ���
typedef char TreeType;     //char�����е�Ԫ������
typedef struct TreeNode     //���������ṹ��
{
	TreeType data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

typedef TreeNode* ElemType;    //�����ָ���Ƕ����е�Ԫ��

typedef struct       //������нṹ��
{
	ElemType* data;
	int front;
	int rear;
}Queue;

Queue* initQueue()    //���г�ʼ������̬����
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	q->front = 0;
	q->rear = 0;
	return q;
}

int isEmpty(Queue* q)
{
	if (q->front == q->rear)
		return 1;
	return 0;
}

int equeue(Queue* q, ElemType e)     //ѭ�����У����
{
	if ((q->rear + 1) % MAXSIZE == q->front)
	{
		printf("full");
		return 0;
	}
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return 1;
}

int dequeue(Queue* q, ElemType* e)
{
	if (isEmpty(q))
		return 0;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return 1;
}

char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;   
void createTree(ElemType* T)       //ǰ������
{
	TreeType ch = str[idx++];
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (TreeNode*)malloc(sizeof(TreeNode));
		(*T)->data = ch;
		createTree(&(*T)->lchild);
		createTree(&(*T)->rchild);
	}
}
 
void preOrder(TreeNode* T)
{
	if (T == NULL)
		return;
	printf("%c ", T->data);
	preOrder(T->lchild);
	preOrder(T->rchild);

}
  
int QueueSize(Queue* q)
{
	return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}
int maxDepth(TreeNode* T,Queue* q)     //��������
{
	if (T == NULL)
		return 0;
	equeue(q, T);
	int depth = 0;
	int count = 0;
	ElemType curr;
	while (!isEmpty(q))
	{
		count = QueueSize(q);
		while (count > 0)
		{
			dequeue(q, &curr);
			count--;
			if (curr->lchild)
				equeue(q, curr->lchild);
			if (curr->rchild)
				equeue(q, curr->rchild);
			
		}
		depth++;
	}
	return depth;
}


void depthOrder(TreeNode* T, Queue* q)     //�������
{
	if (T == NULL)
	{
		printf("������Ϊ��");
		return;
	}
	equeue(q, T);
	int count = 0;
	ElemType curr;
	while (!isEmpty(q))
	{
		count = QueueSize(q);
		while (count > 0)
		{
			dequeue(q, &curr);
			printf("%c ", curr->data);
			count--;
			if (curr->lchild)
				equeue(q, curr->lchild);
			if (curr->rchild)
				equeue(q, curr->rchild);
		}
		printf("\n");
	}
}
int main()
{
	TreeNode t;
	TreeNode* T = &t;
	Queue* q = initQueue();
	createTree(&T);
	printf("%d", maxDepth(T, q));
	depthOrder(T, q);
	return 0;
}
