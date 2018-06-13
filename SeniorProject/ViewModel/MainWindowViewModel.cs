using PropertyChanged;
using System.Windows;


namespace SeniorProject
{
    class MainWindowViewModel : BaseViewModel
    {
        private Window window;

        public string file { get; set; } = "_File";

        public MainWindowViewModel(Window window)
        {
            this.window = window;
        }
    }
}
