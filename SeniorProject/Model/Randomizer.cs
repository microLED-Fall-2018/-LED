using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    class Randomizer
    {
        public static Pattern randomPattern
        {
            get
            {
                return RandomizePattern();
            }
        }

        public static Color randomColor
        {
            get
            {
                return RandomizeColor();
            }
        }

        private static Pattern RandomizePattern()
        {
            Random rand = new Random();
            int numColors = rand.Next(20,100);
            Pattern randomPattern = new Pattern();
            for(int i = 0; i < numColors; i++)
            {
                randomPattern.Insert(RandomizeColor(rand.Next(0,10000)));
            }


            return randomPattern;
        }

        private static Color RandomizeColor()
        {
            //                              random R         random G            random B            ensure that the brightness isn't too low and there's some strobe
            Random rand = new Random();
            return new Color(rand.Next(0, 255), rand.Next(0, 255), rand.Next(0, 255), rand.Next(0, 100) > 50 ? rand.Next(50, 100) : 0, rand.Next(50, 500));
        }

        private static Color RandomizeColor(int seed)
        {
            //                              random R         random G            random B            ensure that the brightness isn't too low and there's some strobe
            Random rand = new Random(seed);
            return new Color(rand.Next(0, 255), rand.Next(0, 255), rand.Next(0, 255), rand.Next(0, 100) > 50 ? rand.Next(50, 100) : 0, rand.Next(50, 500));
        }
    }
}
