using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestApplication
{
    //Prove to myself that everything in C# is passed by pointer
    class Bob
    {
        public bool isBob = true;
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

    class Instruction
    {
        private int _color;

        public int color { get => _color; set => _color = value; }
        public string mode { get; set; }
        public int duration { get; set; }
        public int intensity { get; set; }
        public int rate { get; set; }
        public bool isFinal { get; set; } = false;

        public Instruction() { }

        public Instruction(int rate, int color, string mode, int intensity, bool isLast)
        {
            this.rate = rate;
            this.color = color;
            this.mode = mode;
            this.intensity = intensity;
            this.isFinal = isLast;
        }

        public Instruction(CellData cell, bool isLast)
        {
            this.rate = cell.rate;
            this.color = cell.color;
            this.intensity = cell.intensity;
            this.mode = cell.mode;
            this.isFinal = isLast;
        }

        public CellData getCellData()
        {
            return new CellData() { rate = rate, color = color, mode = mode, intensity = intensity };
        }


        // 8 bits | 8 bits | 8 bits | 2 bits | 2 bits | 3 bits | 1 bit
        // rate   | beats  | intnsty| color c| action |  xxxx  | final
        // 31-24  | 23-16  | 15-8   | 7-6    | 5-4    |   3-1  | 0
        // actions: flash, fade, ramp up, ramp down

        // 8 bits | 8 bits | 8 bits | 8 bits
        // instr  | rate   | dur    | intensity
        // instr  =  7:6   | 5:4    | 3:1    | 0
        //          color  | type   | unused | is last
        private int modeToInt(string mode)
        {
            int modeInt = 0;
            switch (mode)
            {
                case "Flash":
                    modeInt = 0;
                    break;
                case "Fade":
                    modeInt = 1;
                    break;
                case "Ramp Up":
                    modeInt = 2;
                    break;
                case "Ramp Down":
                    modeInt = 3;
                    break;
            }
            return modeInt;
        }

        public string getInstructionString()
        {
            string instruction = "";
            // Instruction
            instruction += fixBinarySize(Convert.ToString(color, 2),2);
            instruction += fixBinarySize(Convert.ToString(modeToInt(mode), 2),2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";

            // Rate
            instruction += fixBinarySize(Convert.ToString(rate, 2), 8);

            // Duration
            instruction += fixBinarySize(Convert.ToString(duration, 2), 8);

            // Intensity
            instruction += fixBinarySize(Convert.ToString(intensity, 2), 8);

            /*
            instruction += fixBinarySize(Convert.ToString(color, 2), 2);
            string modeString = Convert.ToString(mode == "Flash" ? 0 : mode == "Fade" ? 1 : 2, 2);
            instruction += fixBinarySize(modeString, 2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";
            */
            return instruction;
        }

        public string fixBinarySize(string binary, int size)
        {
            if (binary.Length < size)
            {
                int length = binary.Length;
                for (int i = 0; i < size - length; i++)
                {
                    binary = "0" + binary;
                }
            }

            return binary;
        }
    }

    class Program
    {
        public Program()
        {
            
        }

        static void Main(string[] args)
        {
            /*
            Program p = new Program();
            // 8 bits | 8 bits | 8 bits | 8 bits
            // instr  | rate   | dur    | intensity
            Console.WriteLine("8 bits | 8 bits | 8 bits | 8 bits");
            Console.WriteLine("instr  | rate   | dur    | intensity");
            // instr  =  7:6   | 5:4    | 3:1    | 0
            //          color  | type   | unused | is last
            Instruction s = new Instruction(50, 1, "Flash", 255, true);
            string i_s = s.getInstructionString();
            string instr     = i_s.Substring(0, 8);
            string rate      = i_s.Substring(8, 8);
            string dur       = i_s.Substring(16, 8);
            string intensity = i_s.Substring(24, 8);
            Console.WriteLine("Instruction " + instr);
            Console.WriteLine("Rate " + rate);
            Console.WriteLine("Duration " + dur);
            Console.WriteLine("Intensity" + intensity);
            */

            Console.WriteLine(Convert.ToInt32("00010000", 2));
        }
    }
}
