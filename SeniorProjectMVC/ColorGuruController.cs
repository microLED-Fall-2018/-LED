using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProjectMVC
{   
    class ColorGuruController
    {
        private Form1 window;
        private Set set;
        private List<Pattern> patterns;
        private Pattern currentPattern;

        public ColorGuruController(Form1 window)
        {
            this.window = window;
            set = new Set();
            patterns = new List<Pattern>();
            currentPattern = new Pattern();

            window.AddColorClicked += AddColorHandler;
            window.RemoveColorClicked += RemoveColorHandler;
            window.SavePatternClicked += SavePatternHandler;
            window.DeletePatternClicked+= DeletePatternHandler;
            window.DurationChanged += DurationChangedHandler;
            window.ColorChanged += ColorChangedHandler;
            window.LoadPatternClicked += LoadPatternClickedHandler;
            window.AddPatternButtonClicked += AddPatternButtonClickedHandler;
            window.RemovePatternButtonClicked += RemovePatternButtonClickedHandler;
            window.ColorSelectionChanged += ColorSelectionChangedHandler;
            window.ExportButtonClicked += ExportButtonClickedHandler;
        }

        public void AddColorHandler(Color c, int duration)
        {
            currentPattern.addColor(new PatternColor(c, duration));
        }

        public void RemoveColorHandler(int index)
        {
            if (!currentPattern.removeColor(index))
                throw new InvalidOperationException();
        }

        public void SavePatternHandler()
        {
            patterns.Add(currentPattern);
            currentPattern = new Pattern();
        }

        public void DeletePatternHandler(int index)
        {
            patterns.RemoveAt(index);
        }

        public void DurationChangedHandler(int duration, int index)
        {
            currentPattern.colors[index].duration = duration;
        }

        public void ColorChangedHandler(Color color, int index)
        {
            currentPattern.colors[index].color = color;
        }

        public void LoadPatternClickedHandler(int index)
        {
            //currentPattern.colors.Clear();
            foreach(PatternColor pColor in patterns[index].colors)
            {
                window.ColorAdder = pColor.color;
            }
            currentPattern = patterns[index];
            patterns.RemoveAt(index);
        }

        public void AddPatternButtonClickedHandler(int index)
        {
            set.addPattern(patterns[index]);
            patterns.RemoveAt(index);
        }
        
        public void RemovePatternButtonClickedHandler(int index)
        {
            patterns.Add(set.patterns[index]);
            set.removePattern(index);
        }

        public void ColorSelectionChangedHandler(int index)
        {
            window.DurationLoader = currentPattern.colors[index].duration;
        }

        public void ExportButtonClickedHandler(string fileName)
        {
            Saver.WriteToFile(fileName, set);
        }
    }
}
