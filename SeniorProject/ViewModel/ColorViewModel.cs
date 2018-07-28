using SeniorProject.Model;
using System;
using System.Windows.Media;

namespace SeniorProject
{
    public class ColorViewModel : BaseViewModel
    {
        public System.Windows.Media.Color color { get; set; }
        public byte R { get; set; }
        public byte G { get; set; }
        public byte B { get; set; }
        public byte A { get; set; }
        public int duration { get; set; }

        public ColorViewModel()
        {
            R = 100;
            G = 100; 
            B = 100;
            A = 255;
            duration = 100;
            color = Color.FromArgb(A, R, G, B);
        }
        
        public ColorViewModel(byte R, byte G, byte B, byte A, int duration)
        {
            this.R = R;
            this.G = G;
            this.B = B;
            this.A = A;
            this.duration = duration;
            color = Color.FromArgb(A,R,G,B);
        }
    }
}
