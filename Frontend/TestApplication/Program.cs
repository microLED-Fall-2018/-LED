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
    class Program
    {
        public List<Bob> bobs;
        public Bob b;

        public Program()
        {
            b = new Bob();
            bobs = new List<Bob>();
            bobs.Add(b);
            b.isBob = false;
        }

        static void Main(string[] args)
        {
            Program p = new Program();
            Console.WriteLine(p.bobs[0].isBob);
            p.b = new Bob();
            Console.WriteLine(p.bobs[0].isBob);
            p.bobs.Add(p.b);
            Console.WriteLine(p.bobs[1].isBob);
        }
    }
}
