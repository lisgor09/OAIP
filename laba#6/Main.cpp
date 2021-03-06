//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFMain *FMain;

bool GridChanged = false;
int ChangedRow   = -1,
	ChangedCol   = -1,
	SelectedCol    = 1;

//---------------------------------------------------------------------------
__fastcall TFMain::TFMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFMain::AddClick(TObject *Sender)
{
	String Str = KeyToAdd->Text;
	Str.Delete(1,1);
	if ( Str.Pos('-') != 0 || KeyToAdd->Text == "" )
	{
		ShowMessage("�������� ����!");
		return;
	}
	tree.Insert(StrToInt(KeyToAdd->Text), DataToAdd->Text);
	tree.PrintIntoTreeView();
}
//---------------------------------------------------------------------------

void SellCheck()
{
	GridChanged = false;
	TStringGrid *Grid = FMain->StringGrid;
	if ( ChangedRow == Grid->RowCount-1 )
	{
		if ( Grid->Cells[0][ChangedRow] !=""
		||	 Grid->Cells[1][ChangedRow] !="" )
		{
			Grid->RowCount++;
		}
		return;
	}
	if ( Grid->Cells[0][ChangedRow] == ""
	&&   Grid->Cells[1][ChangedRow] == "" )
	{
		int i = ChangedRow;
		Grid->Cells[0][i] = Grid->Cells[0][i+1];
		Grid->Cells[1][i] = Grid->Cells[1][i+1];
		i++;
		while ( Grid->Cells[0][i] != "" )
		{
			Grid->Cells[0][i] = Grid->Cells[0][i+1];
			Grid->Cells[1][i] = Grid->Cells[1][i+1];
			i++;
		}

		Grid->RowCount--;
	}
}

void __fastcall TFMain::DeleteClick(TObject *Sender)
{
	String Str = KeyToDelete->Text;
	Str.Delete(1,1);
	if ( Str.Pos('-') != 0 || KeyToDelete->Text == "" )
	{
		ShowMessage("�������� ����!");
		return;
	}
	tree.Delete(StrToInt(KeyToDelete->Text));
	tree.PrintIntoTreeView();
}
//---------------------------------------------------------------------------

void __fastcall TFMain::FormCreate(TObject *Sender)
{
	StringGrid->Cells[0][0] = "����";
	StringGrid->Cells[1][0] = "��������";
	TStringList *KeyList    = new TStringList,
				*DataList   = new TStringList;
	DataList -> LoadFromFile("DataList.txt");
	KeyList  -> LoadFromFile("KeyList.txt");

	if (KeyList->Count != 0)
	{
		int i;
		for (i = 0; i < KeyList->Count; i++)
		{
			StringGrid->Cells[0][i+1] = KeyList  -> Strings[i];
			StringGrid->Cells[1][i+1] = DataList -> Strings[i];
			StringGrid->RowCount++;
		}
	}
	delete KeyList;
	delete DataList;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::AddFromSGClick(TObject *Sender)
{

	int i = 1;
	String Str;
	while ( StringGrid->Cells[0][i] != "" )
	{
		Str = StringGrid->Cells[0][i];
		Str.Delete(1,1);
		if ( Str.Pos('-') != 0 )
		{
			ShowMessage("�������� ����!");
			return;
		}
		i++;
    }

	tree.Clear(tree.GetRoot());
	i = 1;
	while ( StringGrid->Cells[0][i] != "" )
	{
		tree.Insert( StrToInt(StringGrid->Cells[0][i]),
					 StringGrid->Cells[1][i] );
		i++;
	}
	tree.PrintIntoTreeView();
}
//---------------------------------------------------------------------------


void __fastcall TFMain::ClearTreeClick(TObject *Sender)
{
	TreeView->Items->Clear();
	Memo->Clear();
	tree.Clear(tree.GetRoot());
}
//---------------------------------------------------------------------------


void __fastcall TFMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	TStringList *KeyList  = new TStringList,
				*DataList = new TStringList;
	int i = 1;
	while ( StringGrid->Cells[0][i] != "" )
	{
	   KeyList  ->Add(StringGrid->Cells[0][i]);
	   DataList ->Add(StringGrid->Cells[1][i]);
	   i++;
	}
	DataList -> SaveToFile("DataList.txt");
	KeyList  -> SaveToFile("KeyList.txt");
	delete KeyList;
	delete DataList;
}

//---------------------------------------------------------------------------

void __fastcall TFMain::StringGridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	SelectedCol = ACol;
	if ( GridChanged ) SellCheck();


}

//---------------------------------------------------------------------------

void __fastcall TFMain::StringGridExit(TObject *Sender)
{
	if ( GridChanged )
	{
		SellCheck();
	}
}

//---------------------------------------------------------------------------

void __fastcall TFMain::StringGridGetEditText(TObject *Sender, int ACol, int ARow,
          UnicodeString &Value)
{
		ChangedCol = ACol;
		ChangedRow = ARow;
		GridChanged = true;
}

//---------------------------------------------------------------------------

void __fastcall TFMain::BalanceClick(TObject *Sender)
{
	tree.Balance();
	tree.PrintIntoTreeView();
}
//---------------------------------------------------------------------------


void __fastcall TFMain::TreeViewHint(TObject *Sender, const TTreeNode *Node, UnicodeString &Hint)

{
	Hint = tree.Find(StrToInt(Node->Text)).data;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::FindClick(TObject *Sender)
{
	String Str = KeyToFind->Text;
	Str.Delete(1,1);
	if ( Str.Pos('-') != 0
	||   KeyToFind->Text == "" )
	{
		ShowMessage("�������� ����!");
		return;
	}
	Data S = tree.Find(StrToInt(KeyToFind->Text));
	if ( S.index != NULL )
	{
		TreeView->SetFocus();
		S.index->Selected = true ;
	} else
	{
		ShowMessage("������ �������� � ������ ���!");
    }
}
//---------------------------------------------------------------------------




void __fastcall TFMain::TreeViewCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, bool &DefaultDraw)
{
	Node->Expanded = true;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::PreorderClick(TObject *Sender)
{
	Memo->Clear();
	tree.PrintInPreOrder(tree.GetRoot());
}
//---------------------------------------------------------------------------

void __fastcall TFMain::PostorderClick(TObject *Sender)
{
	Memo->Clear();
	tree.PrintInPostOrder(tree.GetRoot());
}
//---------------------------------------------------------------------------

void __fastcall TFMain::AscendingClick(TObject *Sender)
{
	Memo->Clear();
	tree.PrintAscending(tree.GetRoot());
}
//---------------------------------------------------------------------------

void __fastcall TFMain::SolveClick(TObject *Sender)
{
	ShowMessage("���������� �������� �� ���� �������, ����������� � ����� ������: "+
	IntToStr(tree.SolvePoroblem(tree.GetRoot())));
}
//---------------------------------------------------------------------------

void __fastcall TFMain::KeyToAddKeyPress(TObject *Sender, wchar_t &Key)
{
	if ( (Key >= '0'
	&&    Key <= '9')
	||    Key == VK_BACK
	||    Key == VK_RETURN
	||    Key == '-' ) {}
	else Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TFMain::KeyToDeleteKeyPress(TObject *Sender, wchar_t &Key)
{
	if ( (Key >= '0'
	&&    Key <= '9')
	||    Key == VK_BACK
	||    Key == VK_RETURN
	||    Key == '-' ) {}
	else  Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::KeyToFindKeyPress(TObject *Sender, wchar_t &Key)
{
	if ( (Key >= '0'
	&&    Key <= '9')
	||    Key == VK_BACK
	||    Key == VK_RETURN
	||    Key == '-' ) {}
	else  Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::StringGridKeyPress(TObject *Sender, wchar_t &Key)
{
	if ( SelectedCol != 0 )
	{
		return;
    }
	if ( (Key >= '0'
	&&    Key <= '9')
	||    Key == VK_BACK
	||    Key == VK_RETURN
	||    Key == '-' ) {}
	else  Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFMain::ExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

