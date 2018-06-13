using SeniorProject.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SeniorProject
{
    class ColorGuruViewModel : BaseViewModel
    {
        public ColorGuru guru { get; set; }
        public Set activeSet { get; set; }
        public Pattern activePattern { get; set; }
        public Color activeColor { get; set; }

        public ObservableCollection<Set> Sets { get; set; }

        public ICommand LoadSetCommand { get; set; }
        //view logic

        /// <summary>
        /// Opens an existing set in the interface
        /// </summary>
        private void LoadSet()
        {

        }
    }
}
