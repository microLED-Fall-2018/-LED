using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    public class Color
    {

        public int R, G, B, A;
        public int duration; //ms

        public Color()
        {
            R = G = B = A = 0;
            duration = 10;
        }

        public Color(int R, int G, int B, int A, int duration)
        {
            this.R = R;
            this.G = G;
            this.B = B;
            this.A = A;
            this.duration = duration;
        }
    }

    public class Pattern
    {
        public List<Color> colors;
        public int activeColorIndex;
        public Pattern()
        {
            activeColorIndex = 0;
            colors = new List<Color>();
            Add(new Color());
        }

        public Pattern(List<Color> colors)
        {
            this.colors = colors;
        }

        private void Add(Color color)
        {
            colors.Add(color);
            activeColorIndex++;
        }

        public void Insert(Color color)
        {
            if(activeColorIndex == colors.Count)
                Add(color);
            else
                colors.Insert(++activeColorIndex, color);
        }
    }

    public class Set
    {
        public List<Pattern> patterns;
        public int activePatternIndex;
        public Set()
        {
            activePatternIndex = 0;
            patterns = new List<Pattern>();
            Add(new Pattern());
        }

        public Set(List<Pattern> patterns)
        {
            this.patterns = patterns;
        }

        private void Add(Pattern pattern)
        {
            patterns.Add(pattern);
            activePatternIndex++;
        }

        public void Insert(Pattern pattern)
        {
            if (activePatternIndex == patterns.Count)
                Add(pattern);
            else
                patterns.Insert(++activePatternIndex, pattern);
        }
    }
}
