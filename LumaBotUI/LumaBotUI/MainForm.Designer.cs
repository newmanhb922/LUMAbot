
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
            this.batteryLabel = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.positionLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.stageGrid = new System.Windows.Forms.TableLayoutPanel();
            this.stageLocationF = new LumaBotUI.StageLocation();
            this.stageLocationA = new LumaBotUI.StageLocation();
            this.stageLocationB = new LumaBotUI.StageLocation();
            this.stageLocationH = new LumaBotUI.StageLocation();
            this.stageLocationG = new LumaBotUI.StageLocation();
            this.stageLocationI = new LumaBotUI.StageLocation();
            this.stageLocationC = new LumaBotUI.StageLocation();
            this.stageLocationE = new LumaBotUI.StageLocation();
            this.stageLocationD = new LumaBotUI.StageLocation();
            this.stagePanel = new System.Windows.Forms.Panel();
            this.stageGrid.SuspendLayout();
            this.stagePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // pointLabel
            // 
            this.pointLabel.AutoSize = true;
            this.pointLabel.Location = new System.Drawing.Point(448, 45);
            this.pointLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.pointLabel.Name = "pointLabel";
            this.pointLabel.Size = new System.Drawing.Size(94, 13);
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
            "I"});
            this.pointSelectionCombo.Location = new System.Drawing.Point(565, 45);
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
            this.goButton.Location = new System.Drawing.Point(460, 86);
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
            this.eStopButton.Location = new System.Drawing.Point(460, 392);
            this.eStopButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.eStopButton.Name = "eStopButton";
            this.eStopButton.Size = new System.Drawing.Size(222, 142);
            this.eStopButton.TabIndex = 3;
            this.eStopButton.Text = "Emergency Stop";
            this.eStopButton.UseVisualStyleBackColor = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(448, 161);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Status:";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(562, 161);
            this.statusLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(24, 13);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Idle";
            // 
            // batteryLabel
            // 
            this.batteryLabel.AutoSize = true;
            this.batteryLabel.Location = new System.Drawing.Point(562, 204);
            this.batteryLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.batteryLabel.Name = "batteryLabel";
            this.batteryLabel.Size = new System.Drawing.Size(33, 13);
            this.batteryLabel.TabIndex = 7;
            this.batteryLabel.Text = "100%";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(448, 204);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Battery Health:";
            // 
            // positionLabel
            // 
            this.positionLabel.AutoSize = true;
            this.positionLabel.Location = new System.Drawing.Point(562, 250);
            this.positionLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.positionLabel.Name = "positionLabel";
            this.positionLabel.Size = new System.Drawing.Size(22, 13);
            this.positionLabel.TabIndex = 9;
            this.positionLabel.Text = "0,0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(448, 250);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(84, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Current Position:";
            // 
            // stageGrid
            // 
            this.stageGrid.ColumnCount = 3;
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.Controls.Add(this.stageLocationF, 2, 1);
            this.stageGrid.Controls.Add(this.stageLocationA, 0, 0);
            this.stageGrid.Controls.Add(this.stageLocationB, 1, 0);
            this.stageGrid.Controls.Add(this.stageLocationH, 0, 2);
            this.stageGrid.Controls.Add(this.stageLocationG, 0, 2);
            this.stageGrid.Controls.Add(this.stageLocationI, 0, 2);
            this.stageGrid.Controls.Add(this.stageLocationC, 1, 0);
            this.stageGrid.Controls.Add(this.stageLocationE, 1, 1);
            this.stageGrid.Controls.Add(this.stageLocationD, 0, 1);
            this.stageGrid.Location = new System.Drawing.Point(2, 2);
            this.stageGrid.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageGrid.Name = "stageGrid";
            this.stageGrid.RowCount = 3;
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.Size = new System.Drawing.Size(405, 439);
            this.stageGrid.TabIndex = 10;
            // 
            // stageLocationF
            // 
            this.stageLocationF.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationF.Location = new System.Drawing.Point(272, 148);
            this.stageLocationF.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationF.Name = "stageLocationF";
            this.stageLocationF.PointColor = System.Drawing.Color.Black;
            this.stageLocationF.PointLabelStr = "F";
            this.stageLocationF.Size = new System.Drawing.Size(130, 141);
            this.stageLocationF.TabIndex = 7;
            // 
            // stageLocationA
            // 
            this.stageLocationA.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationA.Location = new System.Drawing.Point(2, 2);
            this.stageLocationA.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationA.Name = "stageLocationA";
            this.stageLocationA.PointColor = System.Drawing.Color.Black;
            this.stageLocationA.PointLabelStr = "A";
            this.stageLocationA.Size = new System.Drawing.Size(130, 141);
            this.stageLocationA.TabIndex = 6;
            // 
            // stageLocationB
            // 
            this.stageLocationB.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationB.Location = new System.Drawing.Point(272, 2);
            this.stageLocationB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationB.Name = "stageLocationB";
            this.stageLocationB.PointColor = System.Drawing.Color.Black;
            this.stageLocationB.PointLabelStr = "C";
            this.stageLocationB.Size = new System.Drawing.Size(130, 141);
            this.stageLocationB.TabIndex = 5;
            // 
            // stageLocationH
            // 
            this.stageLocationH.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationH.Location = new System.Drawing.Point(137, 294);
            this.stageLocationH.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationH.Name = "stageLocationH";
            this.stageLocationH.PointColor = System.Drawing.Color.Black;
            this.stageLocationH.PointLabelStr = "H";
            this.stageLocationH.Size = new System.Drawing.Size(130, 141);
            this.stageLocationH.TabIndex = 3;
            // 
            // stageLocationG
            // 
            this.stageLocationG.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationG.Location = new System.Drawing.Point(2, 294);
            this.stageLocationG.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationG.Name = "stageLocationG";
            this.stageLocationG.PointColor = System.Drawing.Color.Black;
            this.stageLocationG.PointLabelStr = "G";
            this.stageLocationG.Size = new System.Drawing.Size(130, 141);
            this.stageLocationG.TabIndex = 2;
            // 
            // stageLocationI
            // 
            this.stageLocationI.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationI.Location = new System.Drawing.Point(272, 294);
            this.stageLocationI.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationI.Name = "stageLocationI";
            this.stageLocationI.PointColor = System.Drawing.Color.Black;
            this.stageLocationI.PointLabelStr = "I";
            this.stageLocationI.Size = new System.Drawing.Size(130, 141);
            this.stageLocationI.TabIndex = 1;
            // 
            // stageLocationC
            // 
            this.stageLocationC.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationC.Location = new System.Drawing.Point(137, 2);
            this.stageLocationC.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationC.Name = "stageLocationC";
            this.stageLocationC.PointColor = System.Drawing.Color.Black;
            this.stageLocationC.PointLabelStr = "B";
            this.stageLocationC.Size = new System.Drawing.Size(130, 141);
            this.stageLocationC.TabIndex = 0;
            // 
            // stageLocationE
            // 
            this.stageLocationE.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationE.Location = new System.Drawing.Point(137, 148);
            this.stageLocationE.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationE.Name = "stageLocationE";
            this.stageLocationE.PointColor = System.Drawing.Color.Black;
            this.stageLocationE.PointLabelStr = "E";
            this.stageLocationE.Size = new System.Drawing.Size(130, 141);
            this.stageLocationE.TabIndex = 4;
            // 
            // stageLocationD
            // 
            this.stageLocationD.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationD.Location = new System.Drawing.Point(2, 148);
            this.stageLocationD.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stageLocationD.Name = "stageLocationD";
            this.stageLocationD.PointColor = System.Drawing.Color.Black;
            this.stageLocationD.PointLabelStr = "D";
            this.stageLocationD.Size = new System.Drawing.Size(130, 141);
            this.stageLocationD.TabIndex = 8;
            // 
            // stagePanel
            // 
            this.stagePanel.Controls.Add(this.stageGrid);
            this.stagePanel.Location = new System.Drawing.Point(9, 10);
            this.stagePanel.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.stagePanel.Name = "stagePanel";
            this.stagePanel.Size = new System.Drawing.Size(435, 580);
            this.stagePanel.TabIndex = 11;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(736, 612);
            this.Controls.Add(this.stagePanel);
            this.Controls.Add(this.positionLabel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.batteryLabel);
            this.Controls.Add(this.label3);
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
            this.stagePanel.ResumeLayout(false);
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
        private System.Windows.Forms.Label batteryLabel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label positionLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TableLayoutPanel stageGrid;
        private System.Windows.Forms.Panel stagePanel;
        private StageLocation stageLocationC;
        private StageLocation stageLocationD;
        private StageLocation stageLocationF;
        private StageLocation stageLocationA;
        private StageLocation stageLocationB;
        private StageLocation stageLocationE;
        private StageLocation stageLocationH;
        private StageLocation stageLocationG;
        private StageLocation stageLocationI;
    }
}

