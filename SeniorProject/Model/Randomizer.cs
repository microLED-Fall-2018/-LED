using SeniorProject.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    class Randomizer
    {
        public static PatternViewModel randomPattern
        {
            get
            {
                return RandomizePattern();
            }
        }

        public static ColorViewModel randomColor
        {
            get
            {
                return RandomizeColor();
            }
        }

        private static PatternViewModel RandomizePattern()
        {
            Random rand = new Random();
            int numColors = rand.Next(20,100);
            PatternViewModel randomPattern = new PatternViewModel();
            for(int i = 0; i < numColors; i++)
            {
                randomPattern.Insert(RandomizeColor(rand.Next(0,10000)));
            }


            return randomPattern;
        }

        private static ColorViewModel RandomizeColor()
        {
            //                              random R         random G            random B            ensure that the brightness isn't too low and there's some strobe
            Random rand = new Random();
            return new ColorViewModel((byte)rand.Next(0, 255), (byte)rand.Next(0, 255), (byte)rand.Next(0, 255), (byte)(rand.Next(0, 100) > 50 ? rand.Next(50, 100) : 0), rand.Next(50, 500));
        }

        private static ColorViewModel RandomizeColor(int seed)
        {
            //                              random R         random G            random B            ensure that the brightness isn't too low and there's some strobe
            Random rand = new Random(seed);
            return new ColorViewModel((byte)rand.Next(0, 255), (byte)rand.Next(0, 255), (byte)rand.Next(0, 255), (byte)(rand.Next(0, 100) > 50 ? rand.Next(50, 100) : 0), rand.Next(50, 500));
        }
    }
}
