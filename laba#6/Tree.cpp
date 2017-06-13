//---------------------------------------------------------------------------


#pragma hdrstop

#include "Tree.h"
#include "Main.h"


Tree::~Tree()
{
	Clear(TreeRoot);
}

Node *leftRotate(Node *n)         //������� ����������� �������
{                                 //���� ������
	if ( n->right != NULL )
	{
		Node *right     = n->right ;
		n->right        = right->right;
		right->right    = right->left;
		right->left     = n->left;
		n->left         = right;
		int    tempKey  = n->key;
		Data tempData   = n->x;
		n->key          = n->left->key;
		n->x            = n->left->x;
		n->left->key    = tempKey;
		n->left->x      = tempData;
	}
	return n;
}

Node *rightRotate(Node *n)        //������� ����������� �������
{                                 //���� �������
	if ( n->left != NULL )
	{
		Node *left      = n->left;
		n->left         = left->left;
		left->left      = left->right;
		left->right     = n->right;
		n->right        = left;
		int tempKey     = n->key;
		Data tempData   = n->x;
		n->key          = n->right->key;
		n->x            = n->right->x;
		n->right->key   = tempKey;
		n->right->x     = tempData;
	}
	return n;
}

Node *createRightVine(Node *root) //������, ��������� "�����"
{                                 //�� ������������������ ������
	while ( root->left != NULL )
	{
		root = rightRotate(root);
	}
	if ( root->right != NULL )
	{
		root->right = createRightVine(root->right);
	}
	return root;
}

int getNodeCount(Node *root)      //������� ��� �������� �������� ���� root
{
	if ( root == NULL )
	{
		return 0;
	}
	int i = 1;
	while ( root->right != NULL )
	{
		root = root->right;
		i++;
	}
	return i;
}

Node *balanceVine(Node *root)     //�������, ��������� ��������������� ������
{                                 //�� "�����"
	int nodeCount = getNodeCount(root),
		times     = (int)(log(nodeCount) / log(2));
	Node *newRoot = root,
		 *temp;
	for (int i = 0; i < times; i++)
	{
		newRoot  = leftRotate(newRoot);
		root = newRoot->right;
		temp     = newRoot->right;
		for (int j = 0; j < nodeCount / 2 - 1; j++)
		{
			root = leftRotate(root);
			root = root->right;
		}
		nodeCount >>= 1;
		newRoot->right = temp;
	}
	return newRoot;
}
void Tree::Balance()                  //����� ��� ������������ ������
{
	if ( TreeRoot == NULL )
	{
    	return;
	}
	TreeRoot = balanceVine(createRightVine(TreeRoot));
}

void Tree::Clear(Node *temp)          //����� ������� ������
{
	if (temp == NULL)
	{
		return;
	}
	Clear(temp->left);
	Clear(temp->right);
	if (temp == TreeRoot)
	{
	  size = 0;
	  TreeRoot = NULL;
	}
	delete temp;
}

Node *Tree::GetRoot()                 //����� ��������� ��������� �� ������ ������
{
	return TreeRoot;
}

void Tree::Insert(int X, String V)    // ����� ��� ����������  ���� � ������
{                                     // ��� ��� ������ ���������� �� ����
	Node *NewNode  = new Node,        // X - ���� �����. ����, V - ������ �����. ����
		 *temp     = TreeRoot,
		 *PrevNode = NULL;
	int  level     = 0;
	char brunch    = 'n';
	NewNode->key   = X;
	NewNode->x.data  = V;
	NewNode->left  = NULL;
	NewNode->right = NULL;
	while (1)
	{
		if ( temp == NULL )
		{
			size++;
			temp = NewNode;
			if ( level == 0 )
			{
				TreeRoot = temp;
				return;
			} else
			{
				if ( brunch == 'l' )
				{
					PrevNode->left  = temp;
				}
				if ( brunch == 'r' )
				{
					PrevNode->right = temp;
				}
				return;
			}

		}
		if ( temp->key < X )
		{
			PrevNode = temp;
			temp     = temp->right;
			brunch   = 'r';
			level++;
			continue;
		}
		if ( temp->key > X )
		{
			PrevNode = temp;
			brunch   = 'l';
			temp     = temp->left;
			level++;
			continue;
		}
		if ( temp->key == X )
		{
			temp->x.data = V;
			return;
		}
	}
}

void PrintNode(Node *root, TTreeNode *x, char brunch)
{
	if ( root == NULL)
	{
		return;
	}
	TTreeNode *temp;
	if ( brunch == 'f' )
	{
		 temp = FMain->TreeView->Items->Add(NULL, IntToStr(root->key));
	}
	if ( brunch == 'l' )
	{
		 temp = FMain->TreeView->Items->AddChild(x, IntToStr(root->key));
	}
	if ( brunch == 'r' )
	{
		 temp = FMain->TreeView->Items->AddChildFirst(x, IntToStr(root->key));
	}
	root->x.index = temp;
	PrintNode(root->left,  temp , 'l');
	PrintNode(root->right, temp , 'r');
}

void Tree::PrintIntoTreeView()
{
	FMain->TreeView->Items->Clear();
	PrintNode(TreeRoot, NULL, 'f');

}

void Tree::Delete(int X)  //����� ��� �������� ����� �� ������
{                         //X - ���� ���������� ����
	if ( TreeRoot == NULL ) return;
	if ( TreeRoot->key == X )
	{
		Clear(TreeRoot);
		return;
	}
	Node *temp     = TreeRoot,
		 *PrevNode = NULL,
		 *CurNode  = NULL,
		 *LeftMost = NULL;
	char brunch = 'n';
	while ( temp != NULL )
	{
		if ( temp->key < X )
		{
			PrevNode = temp;
			temp     = temp->right;
			brunch   = 'r';
			continue;
		}
		if ( temp->key > X )
		{
			PrevNode = temp;
			temp     = temp->left;
			brunch   = 'l';
			continue;
		}
		if ( temp->key == X)
		{
			if ( temp->left  == NULL
			&&   temp->right == NULL)
			{
					if ( brunch == 'l' )
					{
						PrevNode->left = NULL;
					}
					if ( brunch == 'r' )
					{
						PrevNode->right = NULL;
					}
				delete temp;
				return;
			} else
			if ( temp->left  != NULL
			&&   temp->right != NULL)
			{
				if ( temp->right->left == NULL )
				{
					temp->right->left = temp->left;
					if ( brunch == 'l' )
					{
						PrevNode->left = temp->right;
					}
					if ( brunch == 'r' )
					{
						PrevNode->right = temp->right;
					}
					delete temp;
					return;
				}  else
				{
					CurNode = temp;
					temp = temp->right;
					while (temp != NULL)
					{
						LeftMost = temp;
						temp     = temp->left;
					}
					int Key          = LeftMost->key;
					CurNode->x    = LeftMost->x;
					Delete(Key);
					CurNode->key     = Key ;

					return;
				}
			} else
			{
				if ( temp->left  != NULL )
				{
					if (brunch == 'l')
					{
						PrevNode->left  = temp->left;
					}
					if (brunch == 'r')
					{
						PrevNode->right = temp->left;
					}
					delete temp;
					return;
				}
				if ( temp->right != NULL )
				{
					if (brunch == 'l')
					{
						PrevNode->left  = temp->right;
					}
					if (brunch == 'r')
					{
						PrevNode->right = temp->right;
					}

					delete temp;
					return;
				}
			}

		}
	}
}

Data Tree::Find(int Key)                  //����� ��� ���������� ����������
{                                         //�� ��������� �����
	Node *temp = TreeRoot;
	while ( temp != NULL && temp->key != Key )
	{
		if ( Key > temp->key )
		{
			temp = temp->right;
			continue;
		}
		if ( Key < temp->key )
		{
			temp = temp->left;
			continue;
		}
	}
	if ( temp == NULL )
	{
		temp = new Node;
		temp->x.index = NULL;
	}
	return temp->x;
}


void Tree::PrintInPreOrder(Node *root)    //������ ������ ��������
{
	if ( root == NULL )
	{
		return;
	}
	FMain->Memo->Lines->Add(root->x.data);
	PrintInPreOrder(root->left);
	PrintInPreOrder(root->right);
}

void Tree::PrintInPostOrder(Node *root)   //������ �������� ��������
{
	if ( root == NULL )
	{
		return;
	}
	PrintInPostOrder(root->left);
	PrintInPostOrder(root->right);
	FMain->Memo->Lines->Add(root->x.data);
}

void Tree::PrintAscending(Node *root)     //������ �� �����������
{
	if ( root == NULL )
	{
		return;
	}
	if ( root->left )
	{
		PrintAscending(root->left);
	}
	FMain->Memo->Lines->Add(root->x.data);
	if ( root->right )
	{
		PrintAscending(root->right);
	}
}

#pragma package(smart_init)
