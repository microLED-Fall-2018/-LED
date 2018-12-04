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
        SequenceExporter exporter;


        public Controller(Form1 form)
        {
            window = form;
            exporter = new SequenceExporter();
            window.ExportClicked += ExportClickedHandler;
        }

        public void ExportClickedHandler(CellData[,] cells)
        {
            exporter.export(cells);
        }
    }
}
