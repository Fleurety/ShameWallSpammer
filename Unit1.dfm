object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Shame Wall Spammer'
  ClientHeight = 349
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    492
    349)
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 136
    Top = 316
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Start'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 232
    Top = 316
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Stop'
    Enabled = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 8
    Width = 476
    Height = 302
    Anchors = [akLeft, akTop, akRight, akBottom]
    ScrollBars = ssBoth
    TabOrder = 2
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 48
    Top = 8
  end
  object IdHTTP1: TIdHTTP
    MaxAuthRetries = 1
    AllowCookies = False
    ProtocolVersion = pv1_0
    ProxyParams.BasicAuthentication = True
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.Accept = 'text/html, */*'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    HTTPOptions = [hoForceEncodeParams]
    Left = 8
    Top = 8
  end
end
