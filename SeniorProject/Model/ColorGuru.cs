using PropertyChanged;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    class ColorGuru : BaseViewModel
    {
        public  List<Set>    sets;
        public Set activeSet { get; set; }
        public  Pattern     activePattern { get; set; }
        public  Color       activeColor { get; set; }

        int activeSetIndex;

        public ColorGuru()
        {
            sets = new List<Set>();
            activeSet = new Set();
            
            activeSetIndex = 0;
            Insert(activeSet);
        }

        public void Insert(Set set)
        {
            if (activeSetIndex == sets.Count)
                Add(set);
            else
                sets.Insert(++activeSetIndex, set);
        }

        private void Add(Set set)
        {
            sets.Add(set);
            activeSetIndex++;
        }

        public void NewColor()
        {
            activeColor = new Color();
            activePattern.Insert(activeColor);
        }

        public void NewPattern()
        {
            activePattern = new Pattern();
            activeSet.Insert(activePattern);
        }

        public void NewSet()
        {
            activeSet = new Set();
            Insert(activeSet); 
        }

        public void LoadColor(int index)
        {
            activePattern.activeColorIndex = index;
            activeColor = activePattern.colors[index];
        }

        public void LoadPattern(int index)
        {
            activeSet.activePatternIndex = index;
            activePattern = activeSet.patterns[index];
            activeColor = activePattern.colors[activePattern.activeColorIndex];
        }

        public void LoadSet(int index)
        {
            activeSetIndex = index;
            activeSet = sets[index];
            activePattern = activeSet.patterns[activeSet.activePatternIndex];
            activeColor = activePattern.colors[activePattern.activeColorIndex];
        }

        public void ColorChanged(int R, int G, int B, int A)
        {
            activeColor.R = R;
            activeColor.G = G;
            activeColor.B = B;
            activeColor.A = A;
        }

        public void DurationChanged(int duration)
        {
            activeColor.duration = duration;
        }

        public void RandomizePattern()
        {
            activePattern = Randomizer.randomPattern;
        }

        public void OpenPattern(string json)
        {
            activePattern = JSONConverter.DeserializeJSONPattern(json);
            activeSet.Insert(activePattern);
        }

        public void OpenSet(string json)
        {
            activeSet = JSONConverter.DeserializeJSONSet(json);
            Insert(activeSet);
        }
    }
}
