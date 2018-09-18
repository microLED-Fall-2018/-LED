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

            window.AddColorClicked += AddColorHandler;
            window.AddBeatClicked += AddBeatHandler;
            window.RemoveBeatClicked += RemoveBeatHandler;
        }

        public void AddColorHandler(Color c, int index)
        {

        }

        public void AddBeatHandler(Color c, int index)
        {

        }

        public void RemoveBeatHandler(int index)
        {

        }
    }
}
