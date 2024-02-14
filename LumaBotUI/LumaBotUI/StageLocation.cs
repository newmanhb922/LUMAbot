using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LumaBotUI
{
    public partial class StageLocation : Control
    {
        #region Constants

        const int POINT_DIAMETER = 15;
        #endregion

        #region Fields

        private Color pointColor;
        private string pointLabelStr;
        private string coordLabelStr;
        #endregion

        #region Properties
        [Category("Custom Properties")]
        [Description("Color of the point.")]
        [Browsable(true)]
        public Color PointColor
        {
            get
            {
                return pointColor;
            }
            set
            {
                pointColor = value;
            }
        }

        [Category("Custom Properties")]
        [Description("Label for the point.")]
        public string PointLabelStr
        {
            get
            {
                return pointLabelStr;
            }
            set
            {
                pointLabelStr = value;
            }
        }
        [Category("Custom Properties")]
        [Description("Coordinate of the point.")]
        [Browsable(true)]
        public string CoordLabelStr
        {
            get
            {
                return coordLabelStr;
            }
            set
            {
                coordLabelStr = value;
            }
        }
        #endregion

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
            //base.OnPaintBackground(e);
        }
        protected override void OnPaint(PaintEventArgs e)
        {    
            int pointDiameter = POINT_DIAMETER;
            if (this.Width < pointDiameter)
            {
                pointDiameter = this.Width;
            }
            if (this.Height < pointDiameter)
            {
                pointDiameter = this.Height;
            }
            
            Graphics g = e.Graphics;
            int pointTop = (this.Height / 2) - (pointDiameter / 2);
            SizeF strSize = g.MeasureString(pointLabelStr, this.Font);
            PointF pointLabelPos = new PointF((this.Width / 2) - (strSize.Width / 2), pointTop - strSize.Height - 5);

            int pointBottom = pointTop + pointDiameter;
            strSize = g.MeasureString(coordLabelStr, this.Font);
            PointF coordLabelPos = new PointF((this.Width / 2) - (strSize.Width / 2), pointBottom + 5);
            
            SolidBrush brush = new System.Drawing.SolidBrush(pointColor);
            SolidBrush textBrush = new SolidBrush(this.ForeColor);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            g.FillEllipse(brush, (this.Width / 2) - (pointDiameter / 2), pointTop, pointDiameter, pointDiameter);
            g.DrawString(pointLabelStr, this.Font, textBrush, pointLabelPos);
            g.DrawString(CoordLabelStr, this.Font, textBrush, coordLabelPos);
                
        }
    }
}
