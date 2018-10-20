using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SequenceApp
{
    class Controller
    {
        Form1 window;

        public Controller(Form1 form)
        {
            window = form;
            
            window.ExportClicked += ExportClickedHandler;
        }

        public void ExportClickedHandler(CellData[,] colors)
        {

        }
    }
}
