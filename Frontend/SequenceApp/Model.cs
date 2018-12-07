using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO.Ports;
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

        public Instruction() { }

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

        public byte[] getInstructionBytes()
        {
            string instruction = "";
            byte[] instr = new byte[4];
            // Instruction
            instruction += fixBinarySize(Convert.ToString(color, 2),2);
            instruction += fixBinarySize(Convert.ToString(modeToInt(mode), 2),2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";
            instr[0] = Convert.ToByte(Convert.ToInt32(instruction, 2));
            // Rate
            instruction = fixBinarySize(Convert.ToString(rate, 2), 8);
            instr[1] = Convert.ToByte(Convert.ToInt32(instruction, 2));
            // Duration
            instruction = fixBinarySize(Convert.ToString(duration, 2), 8);
            instr[2] = Convert.ToByte(Convert.ToInt32(instruction, 2));
            // Intensity
            instruction = fixBinarySize(Convert.ToString(intensity, 2), 8);
            instr[3] = Convert.ToByte(Convert.ToInt32(instruction, 2));
            /*
            instruction += fixBinarySize(Convert.ToString(color, 2), 2);
            string modeString = Convert.ToString(mode == "Flash" ? 0 : mode == "Fade" ? 1 : 2, 2);
            instruction += fixBinarySize(modeString, 2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";
            */
            return instr;
        }

        public string getInstructionString()
        {
            string instruction = "";

            instruction += fixBinarySize(Convert.ToString(color, 2), 2);
            instruction += fixBinarySize(Convert.ToString(modeToInt(mode), 2), 2);
            instruction += "000";
            instruction += isFinal ? "1" : "0";
            instruction += fixBinarySize(Convert.ToString(rate, 2), 8);
            instruction += fixBinarySize(Convert.ToString(duration, 2), 8);
            instruction += fixBinarySize(Convert.ToString(intensity, 2), 8);

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
        SerialPort port;
        bool isConnected;
        
        public SequenceExporter()
        {
            isConnected = false;
        }

        public bool export(CellData[,] data, int slot, bool willProgram)
        {
            if(isConnected)
            {
                List<Instruction>[] instructions = buildInstructions(data);

                string output_string = constructSequenceString(instructions, slot, willProgram);
                //port.WriteLine("*PVWWOW*END*END");
                //port.Write(output_string.ToCharArray(),0, output_string.Length);
                //port.Write("*PVWCrud before this*END*END");
                port.Write(output_string);
                return true;
            }

            return false;
        }

        public bool connect(string comPort)
        {
            try
            {
                port = new SerialPort(comPort, 9600, Parity.None, 8, StopBits.One);
                port.Open();
                port.Write("!.");
                isConnected = true;

            } catch
            {
                return false;
            }
            return true;
        }

        private void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort p = (SerialPort)sender;
            //numberLabel.Text = p.ReadExisting();
        }

        
        private string constructSequenceString(List<Instruction>[] instructions, int slot, bool willProgram)
        {
            // original was 25 x 32
            Bitmap map = new Bitmap(16, 16);

            // last instruction has extra *END

            string header = "";
            if(willProgram)
            {
                header = "*" + slot.ToString() + slot.ToString() + slot.ToString();
            } else
            {
                header = "*PVW";
            }
            string sequence_output_string = header;

            List<Instruction> instruction_l = new List<Instruction>();

            for(int i = 0; i < instructions.Length; i++)
            {
                for(int j = 0; j < instructions[i].Count; j++)
                {
                    instruction_l.Add(instructions[i][j]);
                }
            }

            for (int i = 0; i < instruction_l.Count; i++)
            {
                //byte[] instruction_s = instruction_l[i].getInstructionBytes();
                //int output1 = Convert.ToInt32(instruction_s[0]);
                //int output2 = Convert.ToInt32(instruction_s[1]);
                //int output3 = Convert.ToInt32(instruction_s[2]);
                //int output4 = Convert.ToInt32(instruction_s[3]);
                //map.SetPixel(i % 16, i / 16, Color.FromArgb(output1,output2,output3,output4));
                //sequence_output_string += Encoding.UTF8.GetString(instruction_s, 0, instruction_s.Length);
                sequence_output_string += instruction_l[i].getInstructionString();
            }

            sequence_output_string += "*END*END";
            //map.Save("pattern.jpg", ImageFormat.Jpeg);
            return sequence_output_string;
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
                if(current.rate == 5 && current.mode == "Fade" && current.intensity == 0)
                {
                    channelInstructions[i].Remove(current);
                }
                if(channelInstructions[i].Count > 0)
                {
                    current = channelInstructions[i].Last();
                    current.isFinal = true;
                }
            }

            return channelInstructions;
        }
    }
}
