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
   StartUpPosition =   3  '窗口缺省
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
    If Command1.Caption = "打开串口" Then
        MSComm1.CommPort = Val(Text1.Text)               ' 设置通讯串口
        MSComm1.PortOpen = True
        Command1.Caption = "关闭串口"
    Else
        MSComm1.PortOpen = False
        Command1.Caption = "打开串口"
    End If
'errorline:
   ' MsgBox ("请查看串口号是否正确")
End Sub

Private Sub Command2_Click()
    MSComm1.OutBufferCount = 0  '清空输出寄存器
    MSComm1.InBufferCount = 0   '清空接收缓冲区
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
        MSComm1.Output = data_send '将数据用串口发送出去
    Else
        MsgBox ("请先打开串口")
    End If
End Sub

Private Sub Command3_Click()
    MSComm1.OutBufferCount = 0  '清空输出寄存器
    MSComm1.InBufferCount = 0   '清空接收缓冲区
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
        MSComm1.Output = data_send '将数据用串口发送出去
    Else
        MsgBox ("请先打开串口")
    End If
End Sub

Private Sub Form_Load()
  MSComm1.Settings = "9600,n,8,1"   ' 设置波特率和发送字符格式 ，无校验，数据位8位，一个停止位
  MSComm1.InputMode = comInputModeBinary  '按2进制接收方式
  MSComm1.InputLen = 0              ' 设置或返回一次从接收缓冲区中读取字节数，0表示一次读取所有数据
  MSComm1.InBufferSize = 512        ' 设置接收缓冲区512Byte
  MSComm1.InBufferCount = 0         ' 清空接收缓冲区
  MSComm1.OutBufferSize = 512       ' 设置发送缓冲区512Byte
  MSComm1.OutBufferCount = 0        ' 清空发送缓冲区
  MSComm1.RThreshold = 2            ' 每个字符到接收缓冲区都触发接收事件
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
            
  Open App.Path & "\扫描数据.txt" For Append As #1
                        Print #1, "phi角度:" & phi; "   theta角度:" & theta, "   电压值:" & volt
                        MsgBox ("写入成功")
                    Close #1
End Sub

Private Sub Frame3_DragDrop(Source As Control, X As Single, Y As Single)

End Sub

Private Sub MSComm1_OnComm()
    Dim crc() As Byte
    Dim data() As Byte
    Dim data_rec() As Byte
    Dim data_sol() As Byte
    Select Case MSComm1.CommEvent  ' 设置oncomm事件，读取片机内存的值
    Case comEvReceive
        intinputlen = MSComm1.InBufferCount
        ReDim crc(2) As Byte
        ReDim data(5) As Byte
        ReDim data_rec(7) As Byte
        ReDim data_sol(7) As Byte
        data_rec = MSComm1.Input
        For i = 0 To UBound(data_rec)
            If data_rec(i) = 255 Or data_rec(i) = 254 Then
            
                '0xff表示发送的是普通检测的数据，不需要写入文件中
                '0xfe表示发送的是扫描检测的数据，需要写入文件中
                
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
            'MsgBox ("CRC校验错误")
        Else
            '===========================CRC校验成功，进行数据处理=========================================
            
            Dim phi As Integer
            Dim theta As Integer
            Dim volt As Integer
            
            phi = data_sol(1) * 256 + data_sol(2)
            theta = data_sol(3)
            volt = data_sol(4) * 256 + data_sol(5)
            
            Call fun1(phi)          'phi角度
            Call fun2(theta)        'theta角度
            Call fun3(volt)         '电压
            
            If data_sol(0) = 254 Then
                '--------------------将数据写入文件中-----------------
                Open App.Path & "\扫描数据.txt" For Append As #1
                    Print #1, "phi角度:" & phi; "   theta角度:" & theta, "   电压值:" & volt
                    MsgBox ("写入成功")
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
' MODBUS RTU      CRC校验
'==============================================================================================================
Function CRC16(data() As Byte) As String
      Dim CRC16Lo As Byte, CRC16Hi As Byte  'CRC寄存器
      Dim CL As Byte, CH As Byte            '多项式码&HA001
      Dim SaveHi As Byte, SaveLo As Byte
      Dim i As Integer
      Dim flag As Integer
      CRC16Lo = &HFF
      CRC16Hi = &HFF
      CL = &H1
      CH = &HA0
      For i = 0 To UBound(data)
        CRC16Lo = CRC16Lo Xor data(i)      '每一个数据与CRC寄存器进行异或
        For flag = 0 To 7
          SaveHi = CRC16Hi
          SaveLo = CRC16Lo
          CRC16Hi = CRC16Hi \ 2            '高位右移一位
          CRC16Lo = CRC16Lo \ 2            '低位右移一位
          If ((SaveHi And &H1) = &H1) Then '如果高位字节最后一位为1
            CRC16Lo = CRC16Lo Or &H80      '则低位字节右移后前面补1
          End If                           '否则自动补0
          If ((SaveLo And &H1) = &H1) Then '如果LSB为1，则与多项式码进行异或
            CRC16Hi = CRC16Hi Xor CH
            CRC16Lo = CRC16Lo Xor CL
          End If
        Next flag
      Next i
      Dim ReturnData(1) As Byte
      ReturnData(0) = CRC16Hi              'CRC高位
      ReturnData(1) = CRC16Lo              'CRC低位
      CRC16 = ReturnData
End Function



