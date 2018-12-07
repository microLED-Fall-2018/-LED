using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.ViewModel
{
    public class PatternViewModel : BaseViewModel
    {
        public String patternName { get; set; } = "Default Pattern";
        public ObservableCollection<ColorViewModel> colors;
        public int activeColorIndex;
        public PatternViewModel()
        {
            activeColorIndex = 0;
            colors = new ObservableCollection<ColorViewModel>();
            Add(new ColorViewModel());
        }

        public PatternViewModel(ObservableCollection<ColorViewModel> colors)
        {
            this.colors = colors;
        }

        private void Add(ColorViewModel color)
        {
            colors.Add(color);
            activeColorIndex++;
        }

        public void Insert(ColorViewModel color)
        {
            if (activeColorIndex == colors.Count)
                Add(color);
            else
                colors.Insert(++activeColorIndex, color);
        }

        public override string ToString()
        {
            return patternName;
        }
    }
}
