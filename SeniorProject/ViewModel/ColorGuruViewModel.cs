using SeniorProject.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace SeniorProject.ViewModel
{
    class ColorGuruViewModel : BaseViewModel
    {
        private Window window;

        public ObservableCollection<SetViewModel> sets { get; set; }
        public SetViewModel activeSet { get; set; }
        public PatternViewModel activePattern { get; set; }
        public ColorViewModel activeColor { get; set; }
        //ref this for databinding of observers
        public String file { get; set; } = "File";

        public String setName { get; set; } = "SetName";

        int activeSetIndex;
        
        public ColorGuruViewModel(Window window)
        {
            this.window = window;
            
            sets = new ObservableCollection<SetViewModel>();
            activeSet = new SetViewModel();
            activePattern = new PatternViewModel();
            activeColor = new ColorViewModel();

            activeSet.Insert(activePattern);
            activeSet.Insert(activePattern);
            activeSet.Insert(activePattern);
            activeSet.Insert(activePattern);
            activeSet.Insert(activePattern);
            activeSet.Insert(activePattern);

            activeSetIndex = 0;
            Insert(activeSet);
        }

        public void Insert(SetViewModel set)
        {
            if (activeSetIndex == sets.Count)
                Add(set);
            else
                sets.Insert(++activeSetIndex, set);
        }

        private void Add(SetViewModel set)
        {
            sets.Add(set);
            activeSetIndex++;
        }

        public void NewColor()
        {
            activeColor = new ColorViewModel();
            activePattern.Insert(activeColor);
        }

        public void NewPattern()
        {
            activePattern = new PatternViewModel();
            activeSet.Insert(activePattern);
        }

        public void NewSet()
        {
            activeSet = new SetViewModel();
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

        public void ColorChanged(byte R, byte G, byte B, byte A)
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
