using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProjectMVC
{
    interface IColorGuru
    {
        event Action<Color, int> AddColorClicked;
        event Action<int> RemoveColorClicked;
        event Action SavePatternClicked;
        event Action<int> DeletePatternClicked;
        event Action<int, int> DurationChanged;
        event Action<Color, int> ColorChanged;
        event Action<int> LoadPatternClicked;
        event Action<int> AddPatternButtonClicked;
        event Action<int> RemovePatternButtonClicked;
        event Action<int> ColorSelectionChanged;
        event Action<string> ExportButtonClicked;
        event Action<string> ConnectButtonClicked;
        event Action DisconnectButtonClicked;

        Color ColorAdder { set; }
        int DurationLoader { set; }
    }
}
