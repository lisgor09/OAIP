//---------------------------------------------------------------------------


#pragma hdrstop

#include "Solution.h"

int Solution::SolvePoroblem(Node *root) //Метод для решения проблем
{
	if ( root == NULL )
	{
		return 0;
	}
	return root->x.data.Length() +
		   SolvePoroblem(root->left)+
		   SolvePoroblem(root->right);
}

#pragma package(smart_init)
