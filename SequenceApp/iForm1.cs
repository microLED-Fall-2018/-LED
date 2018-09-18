using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SequenceApp
{
    interface iForm1
    {
        event Action<Color, int> AddBeatClicked;
        event Action<Color, int> AddColorClicked;
        event Action<int> RemoveBeatClicked;
    }
}
