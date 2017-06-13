object FMain: TFMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Tree'
  ClientHeight = 521
  ClientWidth = 606
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Key: TLabel
    Left = 19
    Top = 366
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object Information: TLabel
    Left = 55
    Top = 366
    Width = 56
    Height = 13
    Caption = 'Information'
  end
  object Label1: TLabel
    Left = 19
    Top = 412
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object Label2: TLabel
    Left = 19
    Top = 460
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object KeyToAdd: TEdit
    Left = 19
    Top = 385
    Width = 30
    Height = 21
    TabOrder = 0
    OnKeyPress = KeyToAddKeyPress
  end
  object Add: TButton
    Left = 123
    Top = 383
    Width = 75
    Height = 25
    Caption = 'Add'
    TabOrder = 2
    OnClick = AddClick
  end
  object TreeView: TTreeView
    Left = 16
    Top = 19
    Width = 249
    Height = 334
    Indent = 19
    ParentShowHint = False
    ReadOnly = True
    ShowButtons = False
    ShowHint = True
    ShowRoot = False
    TabOrder = 15
    OnCustomDrawItem = TreeViewCustomDrawItem
    OnHint = TreeViewHint
  end
  object KeyToDelete: TEdit
    Left = 19
    Top = 431
    Width = 98
    Height = 21
    TabOrder = 6
    OnKeyPress = KeyToDeleteKeyPress
  end
  object Delete: TButton
    Left = 123
    Top = 429
    Width = 75
    Height = 25
    Caption = 'Delete'
    TabOrder = 7
    OnClick = DeleteClick
  end
  object StringGrid: TStringGrid
    Left = 288
    Top = 19
    Width = 156
    Height = 334
    ColCount = 2
    DrawingStyle = gdsClassic
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goThumbTracking]
    ScrollBars = ssVertical
    TabOrder = 16
    OnExit = StringGridExit
    OnGetEditText = StringGridGetEditText
    OnKeyPress = StringGridKeyPress
    OnSelectCell = StringGridSelectCell
    ColWidths = (
      64
      68)
    RowHeights = (
      24
      24)
  end
  object AddFromSG: TButton
    Left = 224
    Top = 383
    Width = 75
    Height = 25
    Caption = 'Add from SG'
    TabOrder = 3
    OnClick = AddFromSGClick
  end
  object ClearTree: TButton
    Left = 224
    Top = 429
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 8
    OnClick = ClearTreeClick
  end
  object Balance: TButton
    Left = 224
    Top = 477
    Width = 75
    Height = 25
    Caption = 'Balance'
    TabOrder = 13
    OnClick = BalanceClick
  end
  object DataToAdd: TEdit
    Left = 55
    Top = 385
    Width = 62
    Height = 21
    TabOrder = 1
  end
  object KeyToFind: TEdit
    Left = 19
    Top = 479
    Width = 98
    Height = 21
    TabOrder = 11
    OnKeyPress = KeyToFindKeyPress
  end
  object Find: TButton
    Left = 123
    Top = 477
    Width = 75
    Height = 25
    Caption = 'Find'
    TabOrder = 12
    OnClick = FindClick
  end
  object Memo: TMemo
    Left = 464
    Top = 19
    Width = 121
    Height = 334
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 17
  end
  object Preorder: TButton
    Left = 414
    Top = 383
    Width = 75
    Height = 25
    Caption = 'Preorder'
    TabOrder = 4
    OnClick = PreorderClick
  end
  object Postorder: TButton
    Left = 414
    Top = 429
    Width = 75
    Height = 25
    Caption = 'Postorder'
    TabOrder = 9
    OnClick = PostorderClick
  end
  object Ascending: TButton
    Left = 510
    Top = 383
    Width = 75
    Height = 25
    Caption = 'Ascending'
    TabOrder = 5
    OnClick = AscendingClick
  end
  object Solve: TButton
    Left = 510
    Top = 429
    Width = 75
    Height = 25
    Caption = 'Solve'
    TabOrder = 10
    OnClick = SolveClick
  end
  object Exit: TButton
    Left = 510
    Top = 477
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 14
    OnClick = ExitClick
  end
end
