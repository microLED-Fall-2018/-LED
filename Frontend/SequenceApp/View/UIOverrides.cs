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
        private static string fade_path = Path.Combine(Environment.CurrentDirectory, @"assets\", "sine_wave_small.png");
        private static string flash_path = Path.Combine(Environment.CurrentDirectory, @"assets\", "square_wave.png");

        public static Bitmap FADE_IMAGE = new Bitmap(fade_path);
        public static Bitmap FLASH_IMAGE = new Bitmap(flash_path);
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
