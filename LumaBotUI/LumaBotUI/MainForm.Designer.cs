
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
            this.pointLabel.Location = new System.Drawing.Point(598, 55);
            this.pointLabel.Name = "pointLabel";
            this.pointLabel.Size = new System.Drawing.Size(123, 17);
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
            this.pointSelectionCombo.Location = new System.Drawing.Point(753, 55);
            this.pointSelectionCombo.Name = "pointSelectionCombo";
            this.pointSelectionCombo.Size = new System.Drawing.Size(72, 24);
            this.pointSelectionCombo.TabIndex = 1;
            // 
            // goButton
            // 
            this.goButton.BackColor = System.Drawing.Color.LimeGreen;
            this.goButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.goButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.goButton.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.goButton.Location = new System.Drawing.Point(614, 106);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(210, 54);
            this.goButton.TabIndex = 2;
            this.goButton.Text = "Go";
            this.goButton.UseVisualStyleBackColor = false;
            // 
            // eStopButton
            // 
            this.eStopButton.BackColor = System.Drawing.Color.OrangeRed;
            this.eStopButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.eStopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.eStopButton.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.eStopButton.Location = new System.Drawing.Point(614, 482);
            this.eStopButton.Name = "eStopButton";
            this.eStopButton.Size = new System.Drawing.Size(296, 175);
            this.eStopButton.TabIndex = 3;
            this.eStopButton.Text = "Emergency Stop";
            this.eStopButton.UseVisualStyleBackColor = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(598, 198);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "Status:";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(750, 198);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(30, 17);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Idle";
            // 
            // batteryLabel
            // 
            this.batteryLabel.AutoSize = true;
            this.batteryLabel.Location = new System.Drawing.Point(750, 251);
            this.batteryLabel.Name = "batteryLabel";
            this.batteryLabel.Size = new System.Drawing.Size(44, 17);
            this.batteryLabel.TabIndex = 7;
            this.batteryLabel.Text = "100%";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(598, 251);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "Battery Health:";
            // 
            // positionLabel
            // 
            this.positionLabel.AutoSize = true;
            this.positionLabel.Location = new System.Drawing.Point(750, 308);
            this.positionLabel.Name = "positionLabel";
            this.positionLabel.Size = new System.Drawing.Size(28, 17);
            this.positionLabel.TabIndex = 9;
            this.positionLabel.Text = "0,0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(598, 308);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(113, 17);
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
            this.stageGrid.Location = new System.Drawing.Point(3, 3);
            this.stageGrid.Name = "stageGrid";
            this.stageGrid.RowCount = 3;
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.stageGrid.Size = new System.Drawing.Size(540, 540);
            this.stageGrid.TabIndex = 10;
            // 
            // stageLocationF
            // 
            this.stageLocationF.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationF.Location = new System.Drawing.Point(363, 183);
            this.stageLocationF.Name = "stageLocationF";
            this.stageLocationF.PointColor = System.Drawing.Color.Black;
            this.stageLocationF.PointLabelStr = "F";
            this.stageLocationF.Size = new System.Drawing.Size(174, 174);
            this.stageLocationF.TabIndex = 7;
            // 
            // stageLocationA
            // 
            this.stageLocationA.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationA.Location = new System.Drawing.Point(3, 3);
            this.stageLocationA.Name = "stageLocationA";
            this.stageLocationA.PointColor = System.Drawing.Color.Black;
            this.stageLocationA.PointLabelStr = "A";
            this.stageLocationA.Size = new System.Drawing.Size(174, 174);
            this.stageLocationA.TabIndex = 6;
            // 
            // stageLocationB
            // 
            this.stageLocationB.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationB.Location = new System.Drawing.Point(363, 3);
            this.stageLocationB.Name = "stageLocationB";
            this.stageLocationB.PointColor = System.Drawing.Color.Black;
            this.stageLocationB.PointLabelStr = "C";
            this.stageLocationB.Size = new System.Drawing.Size(174, 174);
            this.stageLocationB.TabIndex = 5;
            // 
            // stageLocationH
            // 
            this.stageLocationH.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationH.Location = new System.Drawing.Point(183, 363);
            this.stageLocationH.Name = "stageLocationH";
            this.stageLocationH.PointColor = System.Drawing.Color.Black;
            this.stageLocationH.PointLabelStr = "H";
            this.stageLocationH.Size = new System.Drawing.Size(174, 174);
            this.stageLocationH.TabIndex = 3;
            // 
            // stageLocationG
            // 
            this.stageLocationG.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationG.Location = new System.Drawing.Point(3, 363);
            this.stageLocationG.Name = "stageLocationG";
            this.stageLocationG.PointColor = System.Drawing.Color.Black;
            this.stageLocationG.PointLabelStr = "G";
            this.stageLocationG.Size = new System.Drawing.Size(174, 174);
            this.stageLocationG.TabIndex = 2;
            // 
            // stageLocationI
            // 
            this.stageLocationI.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationI.Location = new System.Drawing.Point(363, 363);
            this.stageLocationI.Name = "stageLocationI";
            this.stageLocationI.PointColor = System.Drawing.Color.Black;
            this.stageLocationI.PointLabelStr = "I";
            this.stageLocationI.Size = new System.Drawing.Size(174, 174);
            this.stageLocationI.TabIndex = 1;
            // 
            // stageLocationC
            // 
            this.stageLocationC.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationC.Location = new System.Drawing.Point(183, 3);
            this.stageLocationC.Name = "stageLocationC";
            this.stageLocationC.PointColor = System.Drawing.Color.Black;
            this.stageLocationC.PointLabelStr = "B";
            this.stageLocationC.Size = new System.Drawing.Size(174, 174);
            this.stageLocationC.TabIndex = 0;
            // 
            // stageLocationE
            // 
            this.stageLocationE.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationE.Location = new System.Drawing.Point(183, 183);
            this.stageLocationE.Name = "stageLocationE";
            this.stageLocationE.PointColor = System.Drawing.Color.Black;
            this.stageLocationE.PointLabelStr = "E";
            this.stageLocationE.Size = new System.Drawing.Size(174, 174);
            this.stageLocationE.TabIndex = 4;
            // 
            // stageLocationD
            // 
            this.stageLocationD.BackColor = System.Drawing.SystemColors.Control;
            this.stageLocationD.Location = new System.Drawing.Point(3, 183);
            this.stageLocationD.Name = "stageLocationD";
            this.stageLocationD.PointColor = System.Drawing.Color.Black;
            this.stageLocationD.PointLabelStr = "D";
            this.stageLocationD.Size = new System.Drawing.Size(174, 174);
            this.stageLocationD.TabIndex = 8;
            // 
            // stagePanel
            // 
            this.stagePanel.Controls.Add(this.stageGrid);
            this.stagePanel.Location = new System.Drawing.Point(12, 12);
            this.stagePanel.Name = "stagePanel";
            this.stagePanel.Size = new System.Drawing.Size(580, 714);
            this.stagePanel.TabIndex = 11;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(982, 753);
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
            this.Name = "MainForm";
            this.Text = "LumaBot";
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

