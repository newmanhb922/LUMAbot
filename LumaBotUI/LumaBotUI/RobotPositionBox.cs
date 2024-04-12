using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LumaBotUI
{
    class RobotPositionBox : Control
    {
        private bool drawBorder;

        [Category("Custom Properties")]
        [Description("If true, the control will draw a border.")]
        [Browsable(true)]
        public bool DrawBorder
        {
            get
            {
                return drawBorder;
            }
            set
            {
                drawBorder = value;
            }
        }
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams CP = base.CreateParams;
                CP.ExStyle |= 0x20;
                return CP;
            }
        }
        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // base.OnPaintBackground(e);
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            Pen pen = new Pen(Color.Red, 4);
            float dotWidth = pen.Width * 2;
            if (this.drawBorder)
            {
                e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                e.Graphics.DrawRectangle(pen, 0, 0, this.Width - 1, this.Height - 1);
            }
            SolidBrush brush = new SolidBrush(pen.Color);
            e.Graphics.FillEllipse(brush, this.Width / 2 - dotWidth / 2, this.Height / 2 - dotWidth / 2, dotWidth, dotWidth);
        }
    }
}
