using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace LearnMVVM.ViewModel
{
    class BaseViewModel : INotifyPropertyChanged
    {
        private Window window;

        public event PropertyChangedEventHandler PropertyChanged;

        public string test { get; set; } = "something";

        public BaseViewModel(Window window)
        {
            this.window = window;
        }
    }
}
