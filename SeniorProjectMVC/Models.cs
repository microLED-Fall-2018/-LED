using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProjectMVC
{
    public class PatternColor
    {
        public Color color { get; set; }
        public int duration { get; set; }

        public int R, G, B, A;
        public PatternColor(Color color, int duration)
        {
            this.color = color;
            this.duration = duration;
            R = color.R;
            G = color.G;
            B = color.B;
            A = color.A;
        }
    }

    public class Pattern
    {
        public String name { get; set; }
        public List<PatternColor> colors;

        public Pattern()
        {
            colors = new List<PatternColor>();
        }

        public void addColor(PatternColor color)
        {
            colors.Add(color);
        }

        public void changeColor(int index, Color color)
        {
            colors[index] = new PatternColor(color, colors[index].duration);
        }

        public bool removeColor(int index)
        {
            if(colors.Count > index & index >= 0)
            {
                colors.RemoveAt(index);
                return true;
            }
            return false;
        }
    }

    public class Set
    {
        public List<Pattern> patterns;
        
        public Set()
        {
            patterns = new List<Pattern>();
        }

        public void addPattern(Pattern pattern)
        {
            patterns.Add(pattern);
        }

        public bool removePattern(int index)
        {
            if (patterns.Count > index & index >= 0)
            {
                patterns.RemoveAt(index);
                return true;
            }
            return false;
        }
    }

    public class Saver
    {
        public static string SerializeSet(Set set)
        {
            return JsonConvert.SerializeObject(set, Formatting.Indented);
        }

        public static void WriteToFile(string FileName, Set set)
        {
            using (Stream s = File.Open(FileName, FileMode.OpenOrCreate))
            {
                using (StreamWriter sw = new StreamWriter(s))
                {
                    sw.Write(Saver.SerializeSet(set));
                }
            }
        }
    }
}
