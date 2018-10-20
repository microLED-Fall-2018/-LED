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

        public int rate { get; set; } = 5;
        public string mode { get; set; } = "flash";
        public char channel { get; set; } = 'U';

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
