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
    public class Images
    {

        public static Bitmap FADE_IMAGE = new Bitmap(@"D:\Desktop\Active HW\Senior Project\Frontend Assets\sine_wave_small.png");
        public static Bitmap FLASH_IMAGE = new Bitmap(@"D:\Desktop\Active HW\Senior Project\Frontend Assets\square_wave.png");
    }


    class DataGridViewCustomCell : DataGridViewImageCell
    {
        private bool is_odd = false;
        private string _mode = "Flash";
        private string _old_mode = "Flash";
        

        public int rate { get; set; } = 5;
        public string mode
        {
            get { return _mode; }
            set
            {
                this.Dispose();
                if (value == "Fade" && _mode != value)
                {
                    this.Value = Images.FADE_IMAGE;
                } else if (value == "Flash" && _mode != value)
                {
                    this.Value = Images.FLASH_IMAGE;
                }
                _mode = value;
            }
        }
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
