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
    public partial class StageLocation : UserControl
    {
        #region Constants

        const int POINT_DIAMETER = 15;
        #endregion

        #region Fields

        private Color pointColor;
        private string pointLabelStr;

        #endregion

        #region Properties
        //TODO Figure out how to get properties to show on designer.
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
        #endregion

        public StageLocation()
        {
            InitializeComponent();
        }

        private void Point_Paint(object sender, PaintEventArgs e)
        {
            pointLabel.Text = pointLabelStr;
            int pointDiameter = POINT_DIAMETER;
            if (this.Width < pointDiameter)
            {
                pointDiameter = this.Width;
            }
            if (this.Height < pointDiameter)
            {
                pointDiameter = this.Height;
            }

            int pointTop = (this.Height / 2) - (pointDiameter / 2);
            pointLabel.Left = (this.Width / 2) - (pointLabel.Width / 2);
            pointLabel.Top = pointTop - pointLabel.Height - 5;

            Graphics g = e.Graphics;
            SolidBrush brush = new System.Drawing.SolidBrush(pointColor);
            g.Clear(this.BackColor);
            g.FillEllipse(brush, (this.Width / 2) - (pointDiameter / 2), pointTop, pointDiameter, pointDiameter);  
        }
    }
}
