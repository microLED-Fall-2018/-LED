using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace SequenceApp.View
{
    class DataGridViewCustomCell : DataGridViewImageCell
    {
        private bool is_odd = false;

        public int rate { get; set; } = 0;
        public int mode { get; set; } = 0;
        public int channel { get; set; } = -1;

        public DataGridViewCustomCell()
        {
            //this.Style = FlatStyle.Popup;
            this.ImageLayout = DataGridViewImageCellLayout.Zoom;
        }

    }

    class DataGridViewCustomColumn: DataGridViewImageColumn
    {
        public DataGridViewCustomColumn()
        {
            this.CellTemplate = new DataGridViewCustomCell();
        }
    }
}
