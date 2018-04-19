using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

/*------------兼容ZLG的数据类型---------------------------------*/

//1.ZLGCAN系列接口卡信息的数据类型。
public struct VCI_BOARD_INFO 
{ 
	public UInt16 hw_Version;
    public UInt16 fw_Version;
    public UInt16 dr_Version;
    public UInt16 in_Version;
    public UInt16 irq_Num;
    public byte   can_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst=20)] public byte []str_Serial_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
    public byte[] str_hw_Type;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public byte[] Reserved;
}

/////////////////////////////////////////////////////
//2.定义CAN信息帧的数据类型。
unsafe public struct VCI_CAN_OBJ  //使用不安全代码
{
    public uint ID;
    public uint TimeStamp;        //时间标识
    public byte TimeFlag;         //是否使用时间标识
    public byte SendType;         //发送标志。保留，未用
    public byte RemoteFlag;       //是否是远程帧
    public byte ExternFlag;       //是否是扩展帧
    public byte DataLen;          //数据长度
    public fixed byte Data[8];    //数据
    public fixed byte Reserved[3];//保留位

}

//3.定义初始化CAN的数据类型
public struct VCI_INIT_CONFIG 
{
    public UInt32 AccCode;
    public UInt32 AccMask;
    public UInt32 Reserved;
    public byte Filter;   //0或1接收所有帧。2标准帧滤波，3是扩展帧滤波。
    public byte Timing0;  //波特率参数，具体配置，请查看二次开发库函数说明书。
    public byte Timing1;
    public byte Mode;     //模式，0表示正常模式，1表示只听模式,2自测模式
}

/*------------其他数据结构描述---------------------------------*/
//4.USB-CAN总线适配器板卡信息的数据类型1，该类型为VCI_FindUsbDevice函数的返回参数。
public struct VCI_BOARD_INFO1
{
    public UInt16 hw_Version;
    public UInt16 fw_Version;
    public UInt16 dr_Version;
    public UInt16 in_Version;
    public UInt16 irq_Num;
    public byte can_Num;
    public byte Reserved;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst=8)] public byte []str_Serial_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] str_hw_Type;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] str_Usb_Serial;
}

/*------------数据结构描述完成---------------------------------*/

public struct CHGDESIPANDPORT 
{
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
    public byte[] szpwd;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
    public byte[] szdesip;
    public Int32 desport;

    public void Init()
    {
        szpwd = new byte[10];
        szdesip = new byte[20];
    }
}


namespace WindowsApplication1
{
    public partial class Form1 : Form
    {
        const int DEV_USBCAN = 3;
        const int DEV_USBCAN2 = 4;
         /// <summary>
        /// 
        /// </summary>
        /// <param name="DeviceType"></param>
        /// <param name="DeviceInd"></param>
        /// <param name="Reserved"></param>
        /// <returns></returns>
        /*------------兼容ZLG的函数描述---------------------------------*/
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_OpenDevice(UInt32 DeviceType, UInt32 DeviceInd, UInt32 Reserved);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_CloseDevice(UInt32 DeviceType, UInt32 DeviceInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_InitCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_INIT_CONFIG pInitConfig);

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ReadBoardInfo(UInt32 DeviceType, UInt32 DeviceInd, ref VCI_BOARD_INFO pInfo);

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_GetReceiveNum(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ClearBuffer(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_StartCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ResetCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_Transmit(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_CAN_OBJ pSend, UInt32 Len);

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_Receive(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_CAN_OBJ pReceive, UInt32 Len, Int32 WaitTime);
        
        /*------------其他函数描述---------------------------------*/

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ConnectDevice(UInt32 DevType,UInt32 DevIndex);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_UsbDeviceReset(UInt32 DevType,UInt32 DevIndex,UInt32 Reserved);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_FindUsbDevice(ref VCI_BOARD_INFO1 pInfo);

        //index从0开始 
        ////获取取第index位 
        //public static int GetBit(byte b, int index) { return ((b & (1 << index)) > 0) ? 1 : 0; }
        ////将第index位设为1 
        //public static void SetBit(byte b, int index) { b |= (byte)(1 << index); }
        ////将第index位设为0 
        //public static void ClearBit(byte b, int index) { b &= (byte)(~(1 << index)); }
        ////将第index位取反 
        //public static void ReverseBit(byte b, int index) { b ^= (byte)(1 << index); }
        //获取取第index位 
        public static int GetBit(byte b, int index) { return ((b & (1 << index)) > 0) ? 1 : 0; }
        //将第index位设为1 
        public static byte SetBit(byte b, int index) { return (byte)(b | (1 << index)); }
        //将第index位设为0 
        public static byte ClearBit(byte b, int index) { return (byte)(b & (byte.MaxValue - (1 << index))); }
        //将第index位取反 
        public static byte ReverseBit(byte b, int index) { return (byte)(b ^ (byte)(1 << index)); }
        /*------------函数描述结束---------------------------------*/

        static UInt32 m_devtype = 4;//USBCAN2

        byte m_bOpen = 0;
        UInt32 m_devind = 0;
        UInt32 m_canind = 0;

        byte TestIndex = 0;
        UInt32 TestCnt = 0;

        byte[] m_arrdevtype = new byte[20];

        UInt16 testTime = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox_DevIndex.SelectedIndex = 0;
            comboBox_CANIndex.SelectedIndex = 0;

            comboBox_BaudRate.SelectedIndex = 2; //500K
            comboBox_Mode.SelectedIndex = 0;    //正常模式
            //comboBox_FrameFormat.SelectedIndex = 0;
            //comboBox_FrameType.SelectedIndex = 0;
            //textBox_ID.Text = "00000123";
            //textBox_Data.Text = "00 01 02 03 04 05 06 07 ";

            comboBox_CarType.SelectedIndex = 0;//路虎揽胜运动版
            comboBox_Year.SelectedIndex = 6;//17款

            //
            Int32 curindex = 0;
            comboBox_devtype.Items.Clear();

            curindex = comboBox_devtype.Items.Add("DEV_USBCAN");
            m_arrdevtype[curindex] =  DEV_USBCAN;
            //comboBox_devtype.Items[2] = "VCI_USBCAN1";
            //m_arrdevtype[2]=  VCI_USBCAN1 ;

            curindex = comboBox_devtype.Items.Add("DEV_USBCAN2");
            m_arrdevtype[curindex] = DEV_USBCAN2 ;
            //comboBox_devtype.Items[3] = "VCI_USBCAN2";
            //m_arrdevtype[3]=  VCI_USBCAN2 ;

            comboBox_devtype.SelectedIndex = 1;
            comboBox_devtype.MaxDropDownItems = comboBox_devtype.Items.Count;
            comboBox_TestMode.SelectedIndex = 0;
            this.toolStripStatusLabel_SysTime.Text = "当前时间   " + System.DateTime.Now.ToString();
            
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_bOpen == 1)
            {
                VCI_CloseDevice(m_devtype, m_devind);
            }
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (m_bOpen==1)
            {
                VCI_CloseDevice(m_devtype, m_devind);
                button_StartCAN.Enabled = true;
                m_bOpen = 0;
            }
            else
            {
                m_devtype = m_arrdevtype[comboBox_devtype.SelectedIndex];

                m_devind=(UInt32)comboBox_DevIndex.SelectedIndex;
                m_canind = (UInt32)comboBox_CANIndex.SelectedIndex;
                if (VCI_OpenDevice(m_devtype, m_devind, 0) == 0)
                {
                    MessageBox.Show("打开设备失败,请检查设备类型和设备索引号是否正确", "错误",
                            MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }

                m_bOpen = 1;
                VCI_INIT_CONFIG init_config = new VCI_INIT_CONFIG();
                init_config.AccCode = 0;
                init_config.AccMask = 0xFFFFFFFF;
                switch (comboBox_BaudRate.Text)
                {
                    case "1000K": //1000

                        init_config.Timing0 = 0;
                        init_config.Timing1 = 0x14;
                        break;
                    case "800K": //800

                        init_config.Timing0 = 0;
                        init_config.Timing1 = 0x16;
                        break;
                    case "500K": //500

                        init_config.Timing0 = 0;
                        init_config.Timing1 = 0x1c;
                        break;
                    case "250K"://250

                        init_config.Timing0 = 0x01;
                        init_config.Timing1 = 0x1c;
                        break;
                    case "125K"://125

                        init_config.Timing0 = 0x03;
                        init_config.Timing1 = 0x1c;
                        break;
                    case "100K"://100

                        init_config.Timing0 = 0x04;
                        init_config.Timing1 = 0x1c;
                        break;
                    case "50K"://50

                        init_config.Timing0 = 0x09;
                        init_config.Timing1 = 0x1c;
                        break;

                }
                init_config.Filter = 0;
                init_config.Mode = (Byte)comboBox_Mode.SelectedIndex;
                VCI_InitCAN(m_devtype, m_devind, m_canind, ref init_config);
            }
            buttonConnect.Text = m_bOpen==1?"断开":"连接";
            comboBox_BaudRate.Enabled = m_bOpen == 0 ? true : false;
        }

        private void button_StartCAN_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;
            button_StartCAN.Enabled = false;
            VCI_StartCAN(m_devtype, m_devind, m_canind);
        }

        unsafe private void button_FrontLeft_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;

            string text = this.button_FrontLeft.Text;
            this.button_FrontLeft.Text = text == "关闭" ? "打开" : "关闭";

            VCI_CAN_OBJ m_sendobj = new VCI_CAN_OBJ();

            if (this.button_FrontLeft.Text == "打开")
            {
                switch (this.comboBox_CarType.Text)
                { 
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        { 
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDD;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDD;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x12;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = SetBit(m_sendobj.Data[2],7);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x12;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[6] = SetBit(m_sendobj.Data[6],1);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (this.button_FrontLeft.Text == "关闭")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x10;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = ClearBit(m_sendobj.Data[2], 7);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X40;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[6] = ClearBit(m_sendobj.Data[6], 1);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }   
            }

        }

        unsafe private void button_RearLeft_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;

            string text = this.button_RearLeft.Text;
            this.button_RearLeft.Text = text == "关闭" ? "打开" : "关闭";

            VCI_CAN_OBJ m_sendobj = new VCI_CAN_OBJ();

            if (this.button_RearLeft.Text == "打开")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xD7;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xD7;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                               m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x18;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }  
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = SetBit(m_sendobj.Data[1], 2);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X48;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 6);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (this.button_RearLeft.Text == "关闭")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x10;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = ClearBit(m_sendobj.Data[1], 2);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X40;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 6);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }   
        }

        unsafe private void button_FrontRight_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;

            string text = this.button_FrontRight.Text;
            this.button_FrontRight.Text = text == "关闭" ? "打开" : "关闭";

            VCI_CAN_OBJ m_sendobj = new VCI_CAN_OBJ();

            if (this.button_FrontRight.Text == "打开")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDE;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDE;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = 0x42;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = SetBit(m_sendobj.Data[1], 0);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0XC0;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 0);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (this.button_FrontRight.Text == "关闭")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = 0x02;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = ClearBit(m_sendobj.Data[1], 0);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X40;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 0);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }     
        }

        unsafe private void button_RearRight_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;

            string text = this.button_RearRight.Text;
            this.button_RearRight.Text = text == "关闭" ? "打开" : "关闭";

            VCI_CAN_OBJ m_sendobj = new VCI_CAN_OBJ();

            if (this.button_RearRight.Text == "打开")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDB;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDB;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x14;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = SetBit(m_sendobj.Data[1], 1);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X50;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 2);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (this.button_RearRight.Text == "关闭")
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                m_sendobj.ID = 0x267;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            case "17+":
                                m_sendobj.ID = 0x110;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                break;
                            case "17+":
                                m_sendobj.ID = 0x375;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0x10;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        } 
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x12A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_RearLeft.Text == "关闭")
                                {
                                    m_sendobj.Data[1] = ClearBit(m_sendobj.Data[1], 1);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "哈弗H6":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x327;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[2] = 0X40;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "荣威X5":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":
                                m_sendobj.ID = 0x46A;
                                m_sendobj.RemoteFlag = 0;
                                m_sendobj.ExternFlag = 0;
                                m_sendobj.DataLen = 0x08;
                                if (this.button_FrontRight.Text == "关闭")
                                {
                                    m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 2);
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }     
        }

        private void button_Test_Click(object sender, EventArgs e)
        {
            if (button_Test.Text == "测试关")
            {
                button_Test.Text = "测试开";
                this.timer_Test.Enabled = true;
            }
            else
            {
                button_Test.Text = "测试关";
                this.timer_Test.Enabled = false;
                TestCnt = 0;
                toolStripStatusLabel_TestTimes.Text = string.Format("连续测试{0}次", TestCnt);
                toolStripStatusLabel_LeftPedalSta.Text = string.Format("左侧踏板动作正常");
                toolStripStatusLabel_RightPedalSta.Text = string.Format("右侧踏板动作正常");
            }
        }
        unsafe private void PedalAutoTest()
        {
            VCI_CAN_OBJ m_sendobj = new VCI_CAN_OBJ();

            if (this.comboBox_TestMode.SelectedIndex == 0)//正常模式
            {
                switch (this.comboBox_CarType.Text)
                {
                    case "路虎揽胜运动版":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":
                                if (TestIndex == 0)
                                {
                                    m_sendobj.ID = 0x267;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 0);
                                    m_sendobj.Data[2] = 0xDE;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 1;
                                }
                                else if (TestIndex == 1)
                                {
                                    m_sendobj.ID = 0x267;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 0);
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 2;
                                }
                                else if (TestIndex == 2)
                                {
                                    m_sendobj.ID = 0x267;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 1);
                                    m_sendobj.Data[2] = 0xDD;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 3;
                                }
                                else if (TestIndex == 3)
                                {
                                    m_sendobj.ID = 0x267;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 1);
                                    m_sendobj.Data[2] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 0;
                                    TestCnt++;
                                    toolStripStatusLabel_TestTimes.Text = string.Format("连续测试{0}次", TestCnt);
                                }
                                break;
                            case "17+":
                                if (TestIndex == 0)
                                {
                                    m_sendobj.ID = 0x110;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 0);
                                    m_sendobj.Data[5] = 0xDE;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 1;
                                }
                                else if (TestIndex == 1)
                                {
                                    m_sendobj.ID = 0x110;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 0);
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 2;
                                }
                                else if (TestIndex == 2)
                                {
                                    m_sendobj.ID = 0x110;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = ClearBit(m_sendobj.Data[5], 1);
                                    m_sendobj.Data[5] = 0xDD;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 3;
                                }
                                else if (TestIndex == 3)
                                {
                                    m_sendobj.ID = 0x110;
                                    m_sendobj.RemoteFlag = 0;
                                    m_sendobj.ExternFlag = 0;
                                    m_sendobj.DataLen = 0x08;
                                    //m_sendobj.Data[5] = SetBit(m_sendobj.Data[5], 1);
                                    m_sendobj.Data[5] = 0xDF;
                                    if (VCI_Transmit(m_devtype, m_devind, m_canind, ref m_sendobj, 1) == 0)
                                    {
                                        MessageBox.Show("发送失败", "错误",
                                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                                    }
                                    TestIndex = 0;
                                    TestCnt++;
                                    toolStripStatusLabel_TestTimes.Text = string.Format("连续测试{0}次", TestCnt);
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case "传祺GS8":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":

                                break;
                            default:
                                break;
                        }
                        break;
                    case "凯迪拉克凯雷德":
                        switch (this.comboBox_Year.Text)
                        {
                            case "15+":
                                break;
                            case "16+":

                                break;
                            case "17+":

                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (this.comboBox_TestMode.SelectedIndex == 1)//遥控模式
            { 
                
            } 
        }
        unsafe private void PedalStaDetect()
        {
            VCI_CAN_OBJ m_recobj = new VCI_CAN_OBJ();

            VCI_Receive(m_devtype, m_devind, m_canind, ref m_recobj, 1, 0);
            /*踏板测试协议*/
            if (m_recobj.Data[0] == 0x01)//左侧踏板信息
            {
                if (m_recobj.Data[1] == 0x01)//伸出状态
                {
                    if (m_recobj.Data[2] == 0x00)
                    {
                        toolStripStatusLabel_LeftPedalSta.Text = string.Format("左侧踏板伸出正常");
                    }
                    else if (m_recobj.Data[2] == 0x01)
                    {
                        toolStripStatusLabel_LeftPedalSta.Text = string.Format("左侧踏板伸出异常");
                    }
                }
                else if (m_recobj.Data[1] == 0x02)//缩回状态
                {
                    if (m_recobj.Data[2] == 0x00)
                    {
                        toolStripStatusLabel_LeftPedalSta.Text = string.Format("左侧踏板缩回正常");
                    }
                    else if (m_recobj.Data[2] == 0x01)
                    {
                        toolStripStatusLabel_LeftPedalSta.Text = string.Format("左侧踏板缩回异常");
                    }
                }
            }
            if (m_recobj.Data[0] == 0x02)//右侧踏板信息
            {
                if (m_recobj.Data[1] == 0x01)//缩回状态
                {
                    if (m_recobj.Data[2] == 0x00)
                    {
                        toolStripStatusLabel_RightPedalSta.Text = string.Format("右侧踏板伸出正常");
                    }
                    else if (m_recobj.Data[2] == 0x01)
                    {
                        toolStripStatusLabel_RightPedalSta.Text = string.Format("右侧踏板伸出异常");
                    }
                }
                else if (m_recobj.Data[1] == 0x02)//缩回状态
                {
                    if (m_recobj.Data[2] == 0x00)
                    {
                        toolStripStatusLabel_RightPedalSta.Text = string.Format("右侧踏板缩回正常");
                    }
                    else if (m_recobj.Data[2] == 0x01)
                    {
                        toolStripStatusLabel_RightPedalSta.Text = string.Format("右侧踏板缩回异常");
                    }
                }
            }   
        }
        private void timer_Test_Tick(object sender, EventArgs e)
        {
            this.toolStripStatusLabel_SysTime.Text = "当前时间   " + System.DateTime.Now.ToString();
            this.PedalStaDetect();
            if (++testTime >= 25)
            {
                testTime = 0;
                this.PedalAutoTest();
            } 
        }
    }
}