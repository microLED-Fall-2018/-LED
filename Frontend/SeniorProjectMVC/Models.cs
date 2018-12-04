using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.IO.Ports;
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

    public class SerialCommunicator
    {
        private SerialPort port;

        public SerialCommunicator()
        {
        }

        public bool connect(string selectedPort)
        {
            try
            {
                port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
                port.Open();
                port.Write("!.");
                return true;
            } catch
            {
                return false;
            }
        }

        public void disconnect()
        {
            port.Write("R255.");
            port.Write("G255.");
            port.Write("B255.");
            port.Write("?.");
            port.Close();
        }

        public void setColor(Color c)
        {
            int r = 255 - c.R;
            int g = 255 - c.G;
            int b = 255 - c.B;
            // keep values in range of 0 to 255
            r = r > 255 ? 255 : r;
            r = r < 0 ? 0 : r;
            g = g > 255 ? 255 : g;
            g = g < 0 ? 0 : g;
            b = b > 255 ? 255 : b;
            b = b < 0 ? 0 : b;

            if (r > 0)
            {
                port.Write($"R{r}.");
            }
            if (g > 0)
            {
                port.Write($"G{g}.");
            }
            if (b > 0)
            {
                port.Write($"B{b}.");
            }
        }
    }
}
