object AEStestBed: TAEStestBed
  Left = 196
  Top = 719
  Width = 776
  Height = 213
  Caption = 'AES Test Bed'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object KeyLbl: TLabel
    Left = 8
    Top = 12
    Width = 18
    Height = 13
    Caption = 'Key'
    FocusControl = EncEdt
  end
  object KeyLen: TLabel
    Left = 710
    Top = 12
    Width = 6
    Height = 13
    Caption = '0'
    FocusControl = KeyEdt
  end
  object DatLbl: TLabel
    Left = 3
    Top = 48
    Width = 23
    Height = 13
    Caption = 'Data'
    FocusControl = DatEdt
  end
  object EncLbl: TLabel
    Left = 5
    Top = 84
    Width = 19
    Height = 13
    Caption = 'Enc'
    FocusControl = EncEdt
  end
  object DatLen: TLabel
    Left = 710
    Top = 48
    Width = 6
    Height = 13
    Caption = '0'
    FocusControl = DatEdt
  end
  object EncLen: TLabel
    Left = 710
    Top = 84
    Width = 6
    Height = 13
    Caption = '0'
  end
  object DecLbl: TLabel
    Left = 5
    Top = 116
    Width = 20
    Height = 13
    Caption = 'Dec'
    FocusControl = DecEdt
  end
  object DecLen: TLabel
    Left = 710
    Top = 116
    Width = 6
    Height = 13
    Caption = '0'
    FocusControl = DecEdt
  end
  object LibProb: TShape
    Left = 240
    Top = 144
    Width = 33
    Height = 33
    Brush.Color = clLime
    Pen.Color = clNavy
    Shape = stCircle
  end
  object DatEdt: TEdit
    Left = 32
    Top = 44
    Width = 670
    Height = 21
    AutoSize = False
    TabOrder = 1
    Text = '0000000000000000'
    OnChange = EdtChange
  end
  object KeyEdt: TEdit
    Left = 32
    Top = 8
    Width = 670
    Height = 21
    AutoSize = False
    TabOrder = 0
    Text = '0000000000000000'
    OnChange = EdtChange
  end
  object EncEdt: TEdit
    Left = 32
    Top = 80
    Width = 670
    Height = 21
    AutoSize = False
    TabOrder = 2
    OnChange = EdtChange
  end
  object RunAES: TButton
    Left = 152
    Top = 149
    Width = 75
    Height = 24
    Caption = 'Run AES DLL'
    TabOrder = 3
    OnClick = RunAESClick
  end
  object DecEdt: TEdit
    Left = 32
    Top = 112
    Width = 670
    Height = 21
    AutoSize = False
    TabOrder = 4
    OnChange = EdtChange
  end
  object Button1: TButton
    Left = 320
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 5
    OnClick = Button1Click
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 80
    Top = 144
  end
end
