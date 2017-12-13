VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3030
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   ScaleHeight     =   10950
   ScaleWidth      =   20250
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   1215
      Left            =   2520
      TabIndex        =   0
      Top             =   2400
      Width           =   1935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim datarec() As Byte

Private Sub Command1_Click()
'On Error GoTo errorline
    If Command1.Caption = "�򿪴���" Then
        MSComm1.CommPort = Val(Text1.Text)               ' ����ͨѶ����
        MSComm1.PortOpen = True
        Command1.Caption = "�رմ���"
    Else
        MSComm1.PortOpen = False
        Command1.Caption = "�򿪴���"
    End If
'errorline:
   ' MsgBox ("��鿴���ں��Ƿ���ȷ")
End Sub

Private Sub Command2_Click()
    MSComm1.OutBufferCount = 0  '�������Ĵ���
    MSComm1.InBufferCount = 0   '��ս��ջ�����
    Dim crc() As Byte
    Dim data() As Byte
    Dim data_send() As Byte
    ReDim data_send(7) As Byte
    ReDim crc(2) As Byte
    ReDim data(5) As Byte
    
    data(0) = Combo1.Text
    data(1) = &H8
    data(2) = &H11
    data(3) = 0
    data(4) = Val(Text2.Text) / 256
    data(5) = Val(Text2.Text) Mod 256
    For i = 0 To 5 Step 1
        data_send(i) = data(i)
    Next i
    crc = CRC16(data)
    data_send(6) = crc(1)
    data_send(7) = crc(0)
    If MSComm1.PortOpen = True Then
        MSComm1.Output = data_send '�������ô��ڷ��ͳ�ȥ
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub Command3_Click()
    MSComm1.OutBufferCount = 0  '�������Ĵ���
    MSComm1.InBufferCount = 0   '��ս��ջ�����
    Dim crc() As Byte
    Dim data() As Byte
    Dim data_send() As Byte
    ReDim data_send(7) As Byte
    ReDim crc(2) As Byte
    ReDim data(5) As Byte
    
    data(0) = Combo1.Text
    data(1) = &H8
    data(2) = &H11
    data(3) = &H1
    data(4) = 0
    data(5) = 0
    For i = 0 To 5 Step 1
        data_send(i) = data(i)
    Next i
    crc = CRC16(data)
    data_send(6) = crc(1)
    data_send(7) = crc(0)
    If MSComm1.PortOpen = True Then
        MSComm1.Output = data_send '�������ô��ڷ��ͳ�ȥ
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub Form_Load()
  MSComm1.Settings = "9600,n,8,1"   ' ���ò����ʺͷ����ַ���ʽ ����У�飬����λ8λ��һ��ֹͣλ
  MSComm1.InputMode = comInputModeBinary  '��2���ƽ��շ�ʽ
  MSComm1.InputLen = 0              ' ���û򷵻�һ�δӽ��ջ������ж�ȡ�ֽ�����0��ʾһ�ζ�ȡ��������
  MSComm1.InBufferSize = 512        ' ���ý��ջ�����512Byte
  MSComm1.InBufferCount = 0         ' ��ս��ջ�����
  MSComm1.OutBufferSize = 512       ' ���÷��ͻ�����512Byte
  MSComm1.OutBufferCount = 0        ' ��շ��ͻ�����
  MSComm1.RThreshold = 2            ' ÿ���ַ������ջ����������������¼�
  MSComm1.SThreshold = 1
  
  Combo1.AddItem ("1")
  Combo1.AddItem ("2")
  Combo1.Text = 1
  Line9.X1 = Shape1.Left + Shape1.Height / 2
  Line9.X2 = Shape1.Left + Shape1.Height / 2
  Line10.X1 = Shape2.Left + Shape2.Height / 2
  Line10.X2 = Shape2.Left + Shape2.Height / 2
  
  Call fun1(0)
  Call fun2(0)
  Call fun3(0)
  
  Dim phi As Integer
            Dim theta As Integer
            Dim volt As Integer
            
            phi = &HE4
            theta = &H56
            volt = &H709
            
  Open App.Path & "\ɨ������.txt" For Append As #1
                        Print #1, "phi�Ƕ�:" & phi; "   theta�Ƕ�:" & theta, "   ��ѹֵ:" & volt
                        MsgBox ("д��ɹ�")
                    Close #1
End Sub

Private Sub Frame3_DragDrop(Source As Control, X As Single, Y As Single)

End Sub

Private Sub MSComm1_OnComm()
    Dim crc() As Byte
    Dim data() As Byte
    Dim data_rec() As Byte
    Dim data_sol() As Byte
    Select Case MSComm1.CommEvent  ' ����oncomm�¼�����ȡƬ���ڴ��ֵ
    Case comEvReceive
        intinputlen = MSComm1.InBufferCount
        ReDim crc(2) As Byte
        ReDim data(5) As Byte
        ReDim data_rec(7) As Byte
        ReDim data_sol(7) As Byte
        data_rec = MSComm1.Input
        For i = 0 To UBound(data_rec)
            If data_rec(i) = 255 Or data_rec(i) = 254 Then
            
                '0xff��ʾ���͵�����ͨ�������ݣ�����Ҫд���ļ���
                '0xfe��ʾ���͵���ɨ��������ݣ���Ҫд���ļ���
                
                For j = 0 To 7
                    data_sol(j) = data_rec((i + j) Mod 8)
                Next j
                GoTo a
            End If
        Next i
a:
        For k = 0 To 5
            data(k) = data_sol(k)
        Next k
        crc = CRC16(data)
        If (data_sol(6) <> crc(1)) Or (data_sol(7) <> crc(0)) Then
            'MsgBox ("CRCУ�����")
        Else
            '===========================CRCУ��ɹ����������ݴ���=========================================
            
            Dim phi As Integer
            Dim theta As Integer
            Dim volt As Integer
            
            phi = data_sol(1) * 256 + data_sol(2)
            theta = data_sol(3)
            volt = data_sol(4) * 256 + data_sol(5)
            
            Call fun1(phi)          'phi�Ƕ�
            Call fun2(theta)        'theta�Ƕ�
            Call fun3(volt)         '��ѹ
            
            If data_sol(0) = 254 Then
                '--------------------������д���ļ���-----------------
                Open App.Path & "\ɨ������.txt" For Append As #1
                    Print #1, "phi�Ƕ�:" & phi; "   theta�Ƕ�:" & theta, "   ��ѹֵ:" & volt
                    MsgBox ("д��ɹ�")
                Close #1
            End If
            
        End If
        
        For j = 0 To 4
            data(j) = 0
        Next j
         For k = 0 To UBound(data_rec)
            data_rec(k) = 0
        Next k
    End Select

End Sub

Private Sub fun1(s)
  r = 900
  X = Shape1.Left + Shape1.Height / 2
  Y = Shape1.Top + Shape1.Height / 2
  
    Label3.Caption = s
    s = (s + 270) Mod 360
    Me.Line1.X1 = X
    Me.Line1.Y1 = Y
    Me.Line1.X2 = X + r * Math.Cos(s * 3.1415 / 180)
    Me.Line1.Y2 = Y + r * Math.Sin(s * 3.1415 / 180)
End Sub

Private Sub fun2(s)
  r = 900
  X = Shape2.Left + Shape2.Height / 2
  Y = Shape2.Top + Shape2.Height / 2
  
    Label4.Caption = s
    s = (s + 270) Mod 360
    Me.Line2.X1 = X
    Me.Line2.Y1 = Y
    Me.Line2.X2 = X + r * Math.Cos(s * 3.1415 / 180)
    Me.Line2.Y2 = Y + r * Math.Sin(s * 3.1415 / 180)
End Sub

Private Sub fun3(s)
    Shape3.Top = Line6.Y1 + 1.21 * (1500 - s)
    Shape3.Height = 1.21 * s
    Label11.Caption = s
End Sub

'==============================================================================================================
' MODBUS RTU      CRCУ��
'==============================================================================================================
Function CRC16(data() As Byte) As String
      Dim CRC16Lo As Byte, CRC16Hi As Byte  'CRC�Ĵ���
      Dim CL As Byte, CH As Byte            '����ʽ��&HA001
      Dim SaveHi As Byte, SaveLo As Byte
      Dim i As Integer
      Dim flag As Integer
      CRC16Lo = &HFF
      CRC16Hi = &HFF
      CL = &H1
      CH = &HA0
      For i = 0 To UBound(data)
        CRC16Lo = CRC16Lo Xor data(i)      'ÿһ��������CRC�Ĵ����������
        For flag = 0 To 7
          SaveHi = CRC16Hi
          SaveLo = CRC16Lo
          CRC16Hi = CRC16Hi \ 2            '��λ����һλ
          CRC16Lo = CRC16Lo \ 2            '��λ����һλ
          If ((SaveHi And &H1) = &H1) Then '�����λ�ֽ����һλΪ1
            CRC16Lo = CRC16Lo Or &H80      '���λ�ֽ����ƺ�ǰ�油1
          End If                           '�����Զ���0
          If ((SaveLo And &H1) = &H1) Then '���LSBΪ1���������ʽ��������
            CRC16Hi = CRC16Hi Xor CH
            CRC16Lo = CRC16Lo Xor CL
          End If
        Next flag
      Next i
      Dim ReturnData(1) As Byte
      ReturnData(0) = CRC16Hi              'CRC��λ
      ReturnData(1) = CRC16Lo              'CRC��λ
      CRC16 = ReturnData
End Function



