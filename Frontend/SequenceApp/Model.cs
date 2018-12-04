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
        private int _color;
        
        public int color { get => _color; set => _color = value; }
        public string mode { get; set; }
        public int duration { get; set; }
        public int intensity { get; set; }
        public int rate { get; set; }
        public bool isFinal { get; set; } = false;
        
        // 8 bits | 8 bits | 8 bits | 2 bits | 2 bits | 3 bits | 1 bit
        // rate   | beats  | intnsty| color c| action |  xxxx  | final
        // 31-24  | 23-16  | 15-8   | 7-6    | 5-4    |   3-1  | 0
        // actions: flash, fade, ramp up, ramp down

        public Instruction() {}

        public Instruction(int rate, int color, string mode, int intensity)
        {
            this.rate = rate;
            this.color = color;
            this.mode = mode;
            this.intensity = intensity;
        }

        public Instruction(CellData cell)
        {
            this.rate = cell.rate;
            this.color = cell.color;
            this.intensity = cell.intensity;
            this.mode = cell.mode;
        }

        public CellData getCellData()
        {
            return new CellData() { rate = rate, color = color, mode = mode, intensity = intensity };
        }

        public string getInstructionString()
        {
            string instruction = "";
            instruction += fixBinarySize(Convert.ToString(rate, 2), 8);
            instruction += fixBinarySize(Convert.ToString(duration, 2), 8);
            instruction += fixBinarySize(Convert.ToString(intensity, 2), 8);
            instruction += fixBinarySize(Convert.ToString(color, 2), 2);
            string modeString = Convert.ToString(mode == "Flash" ? 0 : mode == "Fade" ? 1 : 2, 2);
            instruction += fixBinarySize(modeString, 2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";
            return instruction;
        }

        public string fixBinarySize(string binary, int size)
        {
            if (binary.Length < size)
            {
                for(int i = 0; i < size - binary.Length; i++)
                {
                    binary = "0" + binary;
                }
            }

            return binary;
        }
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

    public class CellData
    {
        public int rate = 5;
        public string mode = "flash";
        public int color = 0;
        public int intensity = 0;

        public bool Equals(CellData cell)
        {
            if (rate != cell.rate) return false;
            if (!mode.Equals(cell.mode)) return false;
            if (color != cell.color) return false;
            if (intensity != cell.intensity) return false;
            return true;
        }
    }

    public class CellModeEvaluation
    {
        public List<int> normalTouchedRows;
        public List<int> colorTouchedRows;

        public CellModeEvaluation()
        {
            normalTouchedRows = new List<int>();
            colorTouchedRows = new List<int>();
        }
    }

    public class SequenceExporter
    {
        public SequenceExporter()
        {

        }

        public bool export(CellData[,] data)
        {
            List<Instruction>[] instructions = buildInstructions(data);
            string output_string = "";
            for ( int i = 0; i < instructions.Length; i++)
            {
                output_string += constructChannelString(instructions[i].ToArray());
            }

            return false;
        }

        private string constructChannelString( Instruction[] instructions)
        {
            string channel_output_string = "";

            for(int i = 0; i < instructions.Length; i++)
            {

            }

            return channel_output_string;
        }

        private List<Instruction>[] buildInstructions(CellData[,] data)
        {
            List<Instruction>[] channelInstructions = new List<Instruction>[3];
            for(int i = 0; i < channelInstructions.Length; i++)
            {
                channelInstructions[i] = new List<Instruction>();
            }
            Instruction current; // = new Instruction(data[0, 0].rate, data[0, 0].color, data[0, 0].mode, data[0, 0].intensity);
            
            for(int i = 0; i < channelInstructions.Length; i++)
            {
                channelInstructions[i].Add(new Instruction(data[i, 0]));
                current = channelInstructions[i][0]; // C# is reference based which means the pointer to the array index is being assigned a value at its location
                for (int c = 0; c < data.GetLength(1); c++)
                {
                    if (data[i,c].Equals(current.getCellData())) current.duration++;
                    else
                    {
                        channelInstructions[i].Add(new Instruction(data[i,c]));
                        current = channelInstructions[i][channelInstructions[i].Count - 1];
                    }
                }
            }

            return channelInstructions;
        }
    }
}
