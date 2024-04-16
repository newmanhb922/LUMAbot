
namespace LumaBotUI
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pointLabel = new System.Windows.Forms.Label();
            this.pointSelectionCombo = new System.Windows.Forms.ComboBox();
            this.goButton = new System.Windows.Forms.Button();
            this.eStopButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.statusLabel = new System.Windows.Forms.Label();
            this.positionLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.stageGrid = new System.Windows.Forms.TableLayoutPanel();
            this.stageLocationE = new LumaBotUI.StageLocation();
            this.stageLocationD = new LumaBotUI.StageLocation();
            this.stageLocationK = new LumaBotUI.StageLocation();
            this.stageLocationJ = new LumaBotUI.StageLocation();
            this.stageLocationQ = new LumaBotUI.StageLocation();
            this.stageLocationP = new LumaBotUI.StageLocation();
            this.stageLocationH = new LumaBotUI.StageLocation();
            this.stageLocationL = new LumaBotUI.StageLocation();
            this.stageLocationN = new LumaBotUI.StageLocation();
            this.stageLocationB = new LumaBotUI.StageLocation();
            this.stageLocationA = new LumaBotUI.StageLocation();
            this.stageLocationM = new LumaBotUI.StageLocation();
            this.stageLocationG = new LumaBotUI.StageLocation();
            this.stageLocationF = new LumaBotUI.StageLocation();
            this.stageLocationC = new LumaBotUI.StageLocation();
            this.setOriginButton = new System.Windows.Forms.Button();
            this.launchDebugButton = new System.Windows.Forms.Button();
            this.robotPositionBox = new LumaBotUI.RobotPositionBox();
            this.initControllerButton = new System.Windows.Forms.Button();
            this.stageGrid.SuspendLayout();
            this.SuspendLayout();
            // 
            // pointLabel
            // 
            this.pointLabel.AutoSize = true;
            this.pointLabel.Location = new System.Drawing.Point(21, 480);
            this.pointLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.pointLabel.Name = "pointLabel";
            this.pointLabel.Size = new System.Drawing.Size(105, 15);
            this.pointLabel.TabIndex = 0;
            this.pointLabel.Text = "Move to this point:";
            // 
            // pointSelectionCombo
            // 
            this.pointSelectionCombo.FormattingEnabled = true;
            this.pointSelectionCombo.Items.AddRange(new object[] {
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "J",
            "K",
            "L",
            "M",
            "N",
            "P",
            "Q"});
            this.pointSelectionCombo.Location = new System.Drawing.Point(138, 480);
            this.pointSelectionCombo.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pointSelectionCombo.Name = "pointSelectionCombo";
            this.pointSelectionCombo.Size = new System.Drawing.Size(55, 21);
            this.pointSelectionCombo.TabIndex = 1;
            // 
            // goButton
            // 
            this.goButton.BackColor = System.Drawing.Color.LimeGreen;
            this.goButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.goButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.goButton.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.goButton.Location = new System.Drawing.Point(23, 516);
            this.goButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(158, 44);
            this.goButton.TabIndex = 2;
            this.goButton.Text = "Go";
            this.goButton.UseVisualStyleBackColor = false;
            this.goButton.Click += new System.EventHandler(this.goButton_Click);
            // 
            // eStopButton
            // 
            this.eStopButton.BackColor = System.Drawing.Color.OrangeRed;
            this.eStopButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.eStopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.eStopButton.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.eStopButton.Location = new System.Drawing.Point(505, 461);
            this.eStopButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.eStopButton.Name = "eStopButton";
            this.eStopButton.Size = new System.Drawing.Size(222, 142);
            this.eStopButton.TabIndex = 3;
            this.eStopButton.Text = "Stop";
            this.eStopButton.UseVisualStyleBackColor = false;
            this.eStopButton.Click += new System.EventHandler(this.eStopButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(249, 480);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 15);
            this.label1.TabIndex = 4;
            this.label1.Text = "Status:";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(318, 480);
            this.statusLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(27, 15);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Idle";
            // 
            // positionLabel
            // 
            this.positionLabel.AutoSize = true;
            this.positionLabel.Location = new System.Drawing.Point(363, 509);
            this.positionLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.positionLabel.Name = "positionLabel";
            this.positionLabel.Size = new System.Drawing.Size(24, 15);
            this.positionLabel.TabIndex = 9;
            this.positionLabel.Text = "0,0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(249, 509);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 15);
            this.label4.TabIndex = 8;
            this.label4.Text = "Current Position:";
            // 
            // stageGrid
            // 
            this.stageGrid.ColumnCount = 5;
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.stageGrid.Controls.Add(this.stageLocationE, 4, 2);
            this.stageGrid.Controls.Add(this.stageLocationD, 3, 2);
            this.stageGrid.Controls.Add(this.stageLocationK, 4, 1);
            this.stageGrid.Controls.Add(this.stageLocationJ, 3, 1);
            this.stageGrid.Controls.Add(this.stageLocationQ, 4, 0);
            this.stageGrid.Controls.Add(this.stageLocationP, 3, 0);
            this.stageGrid.Controls.Add(this.stageLocationH, 2, 1);
            this.stageGrid.Controls.Add(this.stageLocationL, 0, 0);
            this.stageGrid.Controls.Add(this.stageLocationN, 2, 0);
            this.stageGrid.Controls.Add(this.stageLocationB, 1, 2);
            this.stageGrid.Controls.Add(this.stageLocationA, 0, 2);
            this.stageGrid.Controls.Add(this.stageLocationM, 1, 0);
            this.stageGrid.Controls.Add(this.stageLocationG, 1, 1);
            this.stageGrid.Controls.Add(this.stageLocationF, 0, 1);
            this.stageGrid.Controls.Add(this.stageLocationC, 2, 2);
            this.stageGrid.Location = new System.Drawing.Point(9, 9);
            this.stageGrid.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageGrid.Name = "stageGrid";
            this.stageGrid.RowCount = 3;
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33334F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33334F));
            this.stageGrid.Size = new System.Drawing.Size(698, 447);
            this.stageGrid.TabIndex = 10;
            // 
            // stageLocationE
            // 
            this.stageLocationE.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationE.CoordLabelStr = "-14,0";
            this.stageLocationE.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationE.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationE.Location = new System.Drawing.Point(558, 299);
            this.stageLocationE.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationE.Name = "stageLocationE";
            this.stageLocationE.PointColor = System.Drawing.Color.Black;
            this.stageLocationE.PointLabelStr = "E";
            this.stageLocationE.Size = new System.Drawing.Size(138, 146);
            this.stageLocationE.TabIndex = 14;
            // 
            // stageLocationD
            // 
            this.stageLocationD.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationD.CoordLabelStr = null;
            this.stageLocationD.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationD.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationD.Location = new System.Drawing.Point(419, 299);
            this.stageLocationD.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationD.Name = "stageLocationD";
            this.stageLocationD.PointColor = System.Drawing.Color.Black;
            this.stageLocationD.PointLabelStr = "D";
            this.stageLocationD.Size = new System.Drawing.Size(135, 146);
            this.stageLocationD.TabIndex = 13;
            // 
            // stageLocationK
            // 
            this.stageLocationK.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationK.CoordLabelStr = null;
            this.stageLocationK.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationK.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationK.Location = new System.Drawing.Point(558, 150);
            this.stageLocationK.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationK.Name = "stageLocationK";
            this.stageLocationK.PointColor = System.Drawing.Color.Black;
            this.stageLocationK.PointLabelStr = "K";
            this.stageLocationK.Size = new System.Drawing.Size(138, 145);
            this.stageLocationK.TabIndex = 12;
            // 
            // stageLocationJ
            // 
            this.stageLocationJ.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationJ.CoordLabelStr = null;
            this.stageLocationJ.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationJ.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationJ.Location = new System.Drawing.Point(419, 150);
            this.stageLocationJ.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationJ.Name = "stageLocationJ";
            this.stageLocationJ.PointColor = System.Drawing.Color.Black;
            this.stageLocationJ.PointLabelStr = "J";
            this.stageLocationJ.Size = new System.Drawing.Size(135, 145);
            this.stageLocationJ.TabIndex = 11;
            // 
            // stageLocationQ
            // 
            this.stageLocationQ.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationQ.CoordLabelStr = "-14,-14";
            this.stageLocationQ.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationQ.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationQ.Location = new System.Drawing.Point(558, 2);
            this.stageLocationQ.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationQ.Name = "stageLocationQ";
            this.stageLocationQ.PointColor = System.Drawing.Color.Black;
            this.stageLocationQ.PointLabelStr = "Q";
            this.stageLocationQ.Size = new System.Drawing.Size(138, 144);
            this.stageLocationQ.TabIndex = 10;
            // 
            // stageLocationP
            // 
            this.stageLocationP.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationP.CoordLabelStr = null;
            this.stageLocationP.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationP.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationP.Location = new System.Drawing.Point(419, 2);
            this.stageLocationP.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationP.Name = "stageLocationP";
            this.stageLocationP.PointColor = System.Drawing.Color.Black;
            this.stageLocationP.PointLabelStr = "P";
            this.stageLocationP.Size = new System.Drawing.Size(135, 144);
            this.stageLocationP.TabIndex = 9;
            // 
            // stageLocationH
            // 
            this.stageLocationH.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationH.CoordLabelStr = null;
            this.stageLocationH.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationH.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationH.Location = new System.Drawing.Point(280, 150);
            this.stageLocationH.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationH.Name = "stageLocationH";
            this.stageLocationH.PointColor = System.Drawing.Color.Black;
            this.stageLocationH.PointLabelStr = "H";
            this.stageLocationH.Size = new System.Drawing.Size(135, 145);
            this.stageLocationH.TabIndex = 7;
            // 
            // stageLocationL
            // 
            this.stageLocationL.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationL.CoordLabelStr = "14,-14";
            this.stageLocationL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationL.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationL.Location = new System.Drawing.Point(2, 2);
            this.stageLocationL.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationL.Name = "stageLocationL";
            this.stageLocationL.PointColor = System.Drawing.Color.Black;
            this.stageLocationL.PointLabelStr = "L";
            this.stageLocationL.Size = new System.Drawing.Size(135, 144);
            this.stageLocationL.TabIndex = 6;
            // 
            // stageLocationN
            // 
            this.stageLocationN.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationN.CoordLabelStr = null;
            this.stageLocationN.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationN.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationN.Location = new System.Drawing.Point(280, 2);
            this.stageLocationN.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationN.Name = "stageLocationN";
            this.stageLocationN.PointColor = System.Drawing.Color.Black;
            this.stageLocationN.PointLabelStr = "N";
            this.stageLocationN.Size = new System.Drawing.Size(135, 144);
            this.stageLocationN.TabIndex = 5;
            // 
            // stageLocationB
            // 
            this.stageLocationB.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationB.CoordLabelStr = null;
            this.stageLocationB.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationB.Location = new System.Drawing.Point(141, 299);
            this.stageLocationB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationB.Name = "stageLocationB";
            this.stageLocationB.PointColor = System.Drawing.Color.Black;
            this.stageLocationB.PointLabelStr = "B";
            this.stageLocationB.Size = new System.Drawing.Size(135, 146);
            this.stageLocationB.TabIndex = 3;
            // 
            // stageLocationA
            // 
            this.stageLocationA.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationA.CoordLabelStr = "14,0";
            this.stageLocationA.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationA.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationA.Location = new System.Drawing.Point(2, 299);
            this.stageLocationA.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationA.Name = "stageLocationA";
            this.stageLocationA.PointColor = System.Drawing.Color.Black;
            this.stageLocationA.PointLabelStr = "A";
            this.stageLocationA.Size = new System.Drawing.Size(135, 146);
            this.stageLocationA.TabIndex = 2;
            // 
            // stageLocationM
            // 
            this.stageLocationM.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationM.CoordLabelStr = null;
            this.stageLocationM.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationM.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationM.Location = new System.Drawing.Point(141, 2);
            this.stageLocationM.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationM.Name = "stageLocationM";
            this.stageLocationM.PointColor = System.Drawing.Color.Black;
            this.stageLocationM.PointLabelStr = "M";
            this.stageLocationM.Size = new System.Drawing.Size(135, 144);
            this.stageLocationM.TabIndex = 0;
            // 
            // stageLocationG
            // 
            this.stageLocationG.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationG.CoordLabelStr = null;
            this.stageLocationG.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationG.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationG.Location = new System.Drawing.Point(141, 150);
            this.stageLocationG.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationG.Name = "stageLocationG";
            this.stageLocationG.PointColor = System.Drawing.Color.Black;
            this.stageLocationG.PointLabelStr = "G";
            this.stageLocationG.Size = new System.Drawing.Size(135, 145);
            this.stageLocationG.TabIndex = 4;
            // 
            // stageLocationF
            // 
            this.stageLocationF.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationF.CoordLabelStr = null;
            this.stageLocationF.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationF.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationF.Location = new System.Drawing.Point(2, 150);
            this.stageLocationF.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationF.Name = "stageLocationF";
            this.stageLocationF.PointColor = System.Drawing.Color.Black;
            this.stageLocationF.PointLabelStr = "F";
            this.stageLocationF.Size = new System.Drawing.Size(135, 145);
            this.stageLocationF.TabIndex = 8;
            // 
            // stageLocationC
            // 
            this.stageLocationC.CoordLabelStr = "0,0";
            this.stageLocationC.Dock = System.Windows.Forms.DockStyle.Fill;
            this.stageLocationC.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stageLocationC.Location = new System.Drawing.Point(280, 299);
            this.stageLocationC.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationC.Name = "stageLocationC";
            this.stageLocationC.PointColor = System.Drawing.Color.Black;
            this.stageLocationC.PointLabelStr = "C";
            this.stageLocationC.Size = new System.Drawing.Size(135, 146);
            this.stageLocationC.TabIndex = 15;
            // 
            // setOriginButton
            // 
            this.setOriginButton.Location = new System.Drawing.Point(335, 655);
            this.setOriginButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.setOriginButton.Name = "setOriginButton";
            this.setOriginButton.Size = new System.Drawing.Size(171, 30);
            this.setOriginButton.TabIndex = 12;
            this.setOriginButton.Text = "Set Origin";
            this.setOriginButton.UseVisualStyleBackColor = true;
            this.setOriginButton.Click += new System.EventHandler(this.setOriginButton_Click);
            // 
            // launchDebugButton
            // 
            this.launchDebugButton.Location = new System.Drawing.Point(528, 655);
            this.launchDebugButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.launchDebugButton.Name = "launchDebugButton";
            this.launchDebugButton.Size = new System.Drawing.Size(127, 80);
            this.launchDebugButton.TabIndex = 13;
            this.launchDebugButton.Text = "Launch Debugging";
            this.launchDebugButton.UseVisualStyleBackColor = true;
            this.launchDebugButton.Click += new System.EventHandler(this.launchDebugButton_Click);
            // 
            // robotPositionBox
            // 
            this.robotPositionBox.DrawBorder = true;
            this.robotPositionBox.Location = new System.Drawing.Point(75, 81);
            this.robotPositionBox.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.robotPositionBox.Name = "robotPositionBox";
            this.robotPositionBox.Size = new System.Drawing.Size(75, 81);
            this.robotPositionBox.TabIndex = 11;
            this.robotPositionBox.Text = "robotPositionBox1";
            // 
            // initControllerButton
            // 
            this.initControllerButton.Location = new System.Drawing.Point(337, 705);
            this.initControllerButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.initControllerButton.Name = "initControllerButton";
            this.initControllerButton.Size = new System.Drawing.Size(171, 30);
            this.initControllerButton.TabIndex = 14;
            this.initControllerButton.Text = "Controller Connected";
            this.initControllerButton.UseVisualStyleBackColor = true;
            this.initControllerButton.Click += new System.EventHandler(this.initControllerButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(981, 753);
            this.Controls.Add(this.initControllerButton);
            this.Controls.Add(this.launchDebugButton);
            this.Controls.Add(this.setOriginButton);
            this.Controls.Add(this.robotPositionBox);
            this.Controls.Add(this.stageGrid);
            this.Controls.Add(this.positionLabel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.statusLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.eStopButton);
            this.Controls.Add(this.goButton);
            this.Controls.Add(this.pointSelectionCombo);
            this.Controls.Add(this.pointLabel);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "MainForm";
            this.Text = "LumaBot";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.stageGrid.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label pointLabel;
        private System.Windows.Forms.ComboBox pointSelectionCombo;
        private System.Windows.Forms.Button goButton;
        private System.Windows.Forms.Button eStopButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label statusLabel;
        private System.Windows.Forms.Label positionLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TableLayoutPanel stageGrid;
        private StageLocation stageLocationE;
        private StageLocation stageLocationD;
        private StageLocation stageLocationK;
        private StageLocation stageLocationJ;
        private StageLocation stageLocationQ;
        private StageLocation stageLocationP;
        private StageLocation stageLocationH;
        private StageLocation stageLocationL;
        private StageLocation stageLocationN;
        private StageLocation stageLocationB;
        private StageLocation stageLocationA;
        private StageLocation stageLocationM;
        private StageLocation stageLocationG;
        private StageLocation stageLocationF;
        private StageLocation stageLocationC;
        private RobotPositionBox robotPositionBox;
        private System.Windows.Forms.Button setOriginButton;
        private System.Windows.Forms.Button launchDebugButton;
        private System.Windows.Forms.Button initControllerButton;
    }
}

