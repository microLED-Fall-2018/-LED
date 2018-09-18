using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SequenceApp
{
    class Instruction
    {
        private char _color;

        /* length in beats*/
        public char color { get => _color; set => _color = value; }
        public int mode { get; set; }
        public int duration { get; set; }
        public int intensity { get; set; }
    }

    class Beat
    {
        public int mode { get; set; }
        public Color color { get; set; }
        public bool isRGB { get; set; }

        public Beat(int mode, Color c, bool isRGB)
        {
            this.mode = mode;
            this.color = c;
            this.isRGB = isRGB;
        }
    }

    class Sequence
    {
        public Beat[] beats { get; }
        private Beat CLEAR_BEAT;

        public Sequence()
        {
            CLEAR_BEAT = new Beat(-1, Color.White, false);
        }

        public void addBeat(int number, int mode, Color c, bool isRGB)
        {
            beats[number] = new Beat(mode, c, isRGB);
        }

        public void removeBeat(int number)
        {
            beats[number] = CLEAR_BEAT;
        }
    }
}
