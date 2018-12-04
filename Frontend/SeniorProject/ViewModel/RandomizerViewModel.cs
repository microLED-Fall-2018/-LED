using SeniorProject.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SeniorProject.ViewModel
{
    class RandomizerViewModel : BaseViewModel
    {
        public ColorViewModel randomColor
        {
            get 
            {
                return Randomizer.randomColor;
            }
        }

        public PatternViewModel randomPattern
        {
            get
            {
                return Randomizer.randomPattern;
            }
        }

        public RandomizerViewModel()
        {
        }
    }
}
