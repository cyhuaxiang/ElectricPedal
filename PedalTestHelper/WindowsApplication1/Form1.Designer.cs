namespace WindowsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBox_devtype = new System.Windows.Forms.ComboBox();
            this.label14 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.comboBox_BaudRate = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox_Mode = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.comboBox_CANIndex = new System.Windows.Forms.ComboBox();
            this.comboBox_DevIndex = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.button_StartCAN = new System.Windows.Forms.Button();
            this.timer_Test = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.button_RearRight = new System.Windows.Forms.Button();
            this.button_FrontRight = new System.Windows.Forms.Button();
            this.button_RearLeft = new System.Windows.Forms.Button();
            this.button_FrontLeft = new System.Windows.Forms.Button();
            this.comboBox_Year = new System.Windows.Forms.ComboBox();
            this.label15 = new System.Windows.Forms.Label();
            this.comboBox_CarType = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.comboBox_TestMode = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button_Test = new System.Windows.Forms.Button();
            this.statusStrip_Bottom = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel_TestTimes = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_LeftPedalSta = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_RightPedalSta = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_SysTime = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.statusStrip_Bottom.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBox_devtype);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.comboBox_CANIndex);
            this.groupBox1.Controls.Add(this.comboBox_DevIndex);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(425, 110);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设备参数";
            // 
            // comboBox_devtype
            // 
            this.comboBox_devtype.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_devtype.FormattingEnabled = true;
            this.comboBox_devtype.Items.AddRange(new object[] {
            "3",
            "4"});
            this.comboBox_devtype.Location = new System.Drawing.Point(51, 19);
            this.comboBox_devtype.MaxDropDownItems = 15;
            this.comboBox_devtype.Name = "comboBox_devtype";
            this.comboBox_devtype.Size = new System.Drawing.Size(121, 20);
            this.comboBox_devtype.TabIndex = 5;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(10, 23);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(35, 12);
            this.label14.TabIndex = 4;
            this.label14.Text = "类型:";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.comboBox_BaudRate);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.comboBox_Mode);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Location = new System.Drawing.Point(10, 50);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(269, 51);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "初始化CAN参数";
            // 
            // comboBox_BaudRate
            // 
            this.comboBox_BaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_BaudRate.FormattingEnabled = true;
            this.comboBox_BaudRate.Items.AddRange(new object[] {
            "1000K",
            "800K",
            "500K",
            "250K",
            "125K",
            "100K",
            "50K"});
            this.comboBox_BaudRate.Location = new System.Drawing.Point(61, 20);
            this.comboBox_BaudRate.Name = "comboBox_BaudRate";
            this.comboBox_BaudRate.Size = new System.Drawing.Size(70, 20);
            this.comboBox_BaudRate.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "波特率:";
            // 
            // comboBox_Mode
            // 
            this.comboBox_Mode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Mode.FormattingEnabled = true;
            this.comboBox_Mode.Items.AddRange(new object[] {
            "正常",
            "只听",
            "自测"});
            this.comboBox_Mode.Location = new System.Drawing.Point(192, 20);
            this.comboBox_Mode.Name = "comboBox_Mode";
            this.comboBox_Mode.Size = new System.Drawing.Size(70, 20);
            this.comboBox_Mode.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(151, 25);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "模式:";
            // 
            // comboBox_CANIndex
            // 
            this.comboBox_CANIndex.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_CANIndex.FormattingEnabled = true;
            this.comboBox_CANIndex.Items.AddRange(new object[] {
            "0",
            "1"});
            this.comboBox_CANIndex.Location = new System.Drawing.Point(368, 23);
            this.comboBox_CANIndex.Name = "comboBox_CANIndex";
            this.comboBox_CANIndex.Size = new System.Drawing.Size(47, 20);
            this.comboBox_CANIndex.TabIndex = 1;
            // 
            // comboBox_DevIndex
            // 
            this.comboBox_DevIndex.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_DevIndex.FormattingEnabled = true;
            this.comboBox_DevIndex.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.comboBox_DevIndex.Location = new System.Drawing.Point(238, 23);
            this.comboBox_DevIndex.Name = "comboBox_DevIndex";
            this.comboBox_DevIndex.Size = new System.Drawing.Size(41, 20);
            this.comboBox_DevIndex.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(297, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "第几路CAN:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(185, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "索引号:";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(452, 39);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "连接";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // button_StartCAN
            // 
            this.button_StartCAN.Location = new System.Drawing.Point(452, 87);
            this.button_StartCAN.Name = "button_StartCAN";
            this.button_StartCAN.Size = new System.Drawing.Size(75, 23);
            this.button_StartCAN.TabIndex = 5;
            this.button_StartCAN.Text = "启动CAN";
            this.button_StartCAN.UseVisualStyleBackColor = true;
            this.button_StartCAN.Click += new System.EventHandler(this.button_StartCAN_Click);
            // 
            // timer_Test
            // 
            this.timer_Test.Tick += new System.EventHandler(this.timer_Test_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label13);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.button_RearRight);
            this.groupBox4.Controls.Add(this.button_FrontRight);
            this.groupBox4.Controls.Add(this.button_RearLeft);
            this.groupBox4.Controls.Add(this.button_FrontLeft);
            this.groupBox4.Controls.Add(this.comboBox_Year);
            this.groupBox4.Controls.Add(this.label15);
            this.groupBox4.Controls.Add(this.comboBox_CarType);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Location = new System.Drawing.Point(12, 128);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(425, 91);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "模拟开关门";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(287, 55);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(47, 12);
            this.label13.TabIndex = 11;
            this.label13.Text = "右后门:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(287, 20);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(47, 12);
            this.label12.TabIndex = 10;
            this.label12.Text = "右前门:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(155, 55);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(47, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "左后门:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(155, 20);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 8;
            this.label10.Text = "左前门:";
            // 
            // button_RearRight
            // 
            this.button_RearRight.Location = new System.Drawing.Point(340, 50);
            this.button_RearRight.Name = "button_RearRight";
            this.button_RearRight.Size = new System.Drawing.Size(75, 23);
            this.button_RearRight.TabIndex = 7;
            this.button_RearRight.Text = "关闭";
            this.button_RearRight.UseVisualStyleBackColor = true;
            this.button_RearRight.Click += new System.EventHandler(this.button_RearRight_Click);
            // 
            // button_FrontRight
            // 
            this.button_FrontRight.Location = new System.Drawing.Point(340, 16);
            this.button_FrontRight.Name = "button_FrontRight";
            this.button_FrontRight.Size = new System.Drawing.Size(75, 23);
            this.button_FrontRight.TabIndex = 6;
            this.button_FrontRight.Text = "关闭";
            this.button_FrontRight.UseVisualStyleBackColor = true;
            this.button_FrontRight.Click += new System.EventHandler(this.button_FrontRight_Click);
            // 
            // button_RearLeft
            // 
            this.button_RearLeft.Location = new System.Drawing.Point(208, 50);
            this.button_RearLeft.Name = "button_RearLeft";
            this.button_RearLeft.Size = new System.Drawing.Size(75, 23);
            this.button_RearLeft.TabIndex = 5;
            this.button_RearLeft.Text = "关闭";
            this.button_RearLeft.UseVisualStyleBackColor = true;
            this.button_RearLeft.Click += new System.EventHandler(this.button_RearLeft_Click);
            // 
            // button_FrontLeft
            // 
            this.button_FrontLeft.Location = new System.Drawing.Point(208, 15);
            this.button_FrontLeft.Name = "button_FrontLeft";
            this.button_FrontLeft.Size = new System.Drawing.Size(75, 23);
            this.button_FrontLeft.TabIndex = 4;
            this.button_FrontLeft.Text = "关闭";
            this.button_FrontLeft.UseVisualStyleBackColor = true;
            this.button_FrontLeft.Click += new System.EventHandler(this.button_FrontLeft_Click);
            // 
            // comboBox_Year
            // 
            this.comboBox_Year.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Year.FormattingEnabled = true;
            this.comboBox_Year.Items.AddRange(new object[] {
            "11+",
            "12+",
            "13+",
            "14+",
            "15+",
            "16+",
            "17+"});
            this.comboBox_Year.Location = new System.Drawing.Point(46, 47);
            this.comboBox_Year.Name = "comboBox_Year";
            this.comboBox_Year.Size = new System.Drawing.Size(56, 20);
            this.comboBox_Year.TabIndex = 3;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(12, 50);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(35, 12);
            this.label15.TabIndex = 2;
            this.label15.Text = "年份:";
            // 
            // comboBox_CarType
            // 
            this.comboBox_CarType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_CarType.FormattingEnabled = true;
            this.comboBox_CarType.Items.AddRange(new object[] {
            "路虎揽胜运动版",
            "传祺GS8",
            "凯迪拉克凯雷德",
            "哈弗H6",
            "荣威X5"});
            this.comboBox_CarType.Location = new System.Drawing.Point(46, 17);
            this.comboBox_CarType.Name = "comboBox_CarType";
            this.comboBox_CarType.Size = new System.Drawing.Size(98, 20);
            this.comboBox_CarType.TabIndex = 1;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(10, 20);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(35, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "车型:";
            // 
            // comboBox_TestMode
            // 
            this.comboBox_TestMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_TestMode.FormattingEnabled = true;
            this.comboBox_TestMode.Items.AddRange(new object[] {
            "正常",
            "遥控"});
            this.comboBox_TestMode.Location = new System.Drawing.Point(71, 22);
            this.comboBox_TestMode.Name = "comboBox_TestMode";
            this.comboBox_TestMode.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.comboBox_TestMode.Size = new System.Drawing.Size(70, 20);
            this.comboBox_TestMode.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "测试模式:";
            // 
            // button_Test
            // 
            this.button_Test.Location = new System.Drawing.Point(173, 245);
            this.button_Test.Name = "button_Test";
            this.button_Test.Size = new System.Drawing.Size(75, 23);
            this.button_Test.TabIndex = 12;
            this.button_Test.Text = "测试关";
            this.button_Test.UseVisualStyleBackColor = true;
            this.button_Test.Click += new System.EventHandler(this.button_Test_Click);
            // 
            // statusStrip_Bottom
            // 
            this.statusStrip_Bottom.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel_TestTimes,
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel_LeftPedalSta,
            this.toolStripStatusLabel3,
            this.toolStripStatusLabel_RightPedalSta,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel_SysTime});
            this.statusStrip_Bottom.Location = new System.Drawing.Point(0, 288);
            this.statusStrip_Bottom.Name = "statusStrip_Bottom";
            this.statusStrip_Bottom.Size = new System.Drawing.Size(551, 22);
            this.statusStrip_Bottom.TabIndex = 10;
            this.statusStrip_Bottom.Text = "statusStrip1";
            // 
            // toolStripStatusLabel_TestTimes
            // 
            this.toolStripStatusLabel_TestTimes.Name = "toolStripStatusLabel_TestTimes";
            this.toolStripStatusLabel_TestTimes.Size = new System.Drawing.Size(75, 17);
            this.toolStripStatusLabel_TestTimes.Text = "连续测试0次";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(11, 17);
            this.toolStripStatusLabel1.Text = "|";
            // 
            // toolStripStatusLabel_LeftPedalSta
            // 
            this.toolStripStatusLabel_LeftPedalSta.Name = "toolStripStatusLabel_LeftPedalSta";
            this.toolStripStatusLabel_LeftPedalSta.Size = new System.Drawing.Size(104, 17);
            this.toolStripStatusLabel_LeftPedalSta.Text = "左侧踏板动作正常";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(11, 17);
            this.toolStripStatusLabel3.Text = "|";
            // 
            // toolStripStatusLabel_RightPedalSta
            // 
            this.toolStripStatusLabel_RightPedalSta.Name = "toolStripStatusLabel_RightPedalSta";
            this.toolStripStatusLabel_RightPedalSta.Size = new System.Drawing.Size(104, 17);
            this.toolStripStatusLabel_RightPedalSta.Text = "右侧踏板动作正常";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(11, 17);
            this.toolStripStatusLabel2.Text = "|";
            // 
            // toolStripStatusLabel_SysTime
            // 
            this.toolStripStatusLabel_SysTime.Name = "toolStripStatusLabel_SysTime";
            this.toolStripStatusLabel_SysTime.Size = new System.Drawing.Size(32, 17);
            this.toolStripStatusLabel_SysTime.Text = "时间";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.comboBox_TestMode);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(12, 225);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(245, 57);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "踏板测试";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(551, 310);
            this.Controls.Add(this.button_Test);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.statusStrip_Bottom);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.button_StartCAN);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "电动踏板测试";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.statusStrip_Bottom.ResumeLayout(false);
            this.statusStrip_Bottom.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.ComboBox comboBox_CANIndex;
        private System.Windows.Forms.ComboBox comboBox_DevIndex;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox_Mode;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button_StartCAN;
        private System.Windows.Forms.Timer timer_Test;
        private System.Windows.Forms.ComboBox comboBox_devtype;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ComboBox comboBox_Year;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.ComboBox comboBox_CarType;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button button_RearRight;
        private System.Windows.Forms.Button button_FrontRight;
        private System.Windows.Forms.Button button_RearLeft;
        private System.Windows.Forms.Button button_FrontLeft;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox comboBox_BaudRate;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_Test;
        private System.Windows.Forms.StatusStrip statusStrip_Bottom;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_TestTimes;
        private System.Windows.Forms.ComboBox comboBox_TestMode;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_LeftPedalSta;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_RightPedalSta;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_SysTime;
    }
}

