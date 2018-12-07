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
        iForm1 window;
        SequenceExporter exporter;


        public Controller(Form1 form)
        {
            window = form;
            exporter = new SequenceExporter();
            window.ExportClicked += ExportClickedHandler;
            window.ConnectClicked += ConnectClickedHandler;
        }

        public void ExportClickedHandler(CellData[,] cells)
        {
            exporter.export(cells);
        }

        public void ConnectClickedHandler(string comPort)
        {
            window.didConnect = exporter.connect(comPort);
        }
    }
}
