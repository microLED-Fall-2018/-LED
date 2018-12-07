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

        // globals to be stored
        bool willProgram = false;
        int slot = 0;

        public Controller(Form1 form)
        {
            window = form;
            exporter = new SequenceExporter();
            window.ExportClicked += ExportClickedHandler;
            window.ConnectClicked += ConnectClickedHandler;
            window.SlotChanged += SlotChangedHandler;
            window.ProgramChecked += ProgramCheckedHandler;
        }

        public void ExportClickedHandler(CellData[,] cells)
        {
            exporter.export(cells, slot, willProgram);
        }

        public void ConnectClickedHandler(string comPort)
        {
            window.didConnect = exporter.connect(comPort);
        }

        public void ProgramCheckedHandler(bool willProgram)
        {
            this.willProgram = willProgram;
        }

        public void SlotChangedHandler(int slotValue)
        {
            slot = slotValue-1;
        }
    }
}
