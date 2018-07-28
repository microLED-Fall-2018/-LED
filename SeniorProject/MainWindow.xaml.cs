using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using SeniorProject.Model;
using System.Web;
using SeniorProject.ViewModel;

namespace SeniorProject
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            /* Test Code for JSONConverter
            set = new Set();
            set.patterns.Add(new Pattern());
            set.patterns[0].colors.Add(new Model.Color(100, 100, 100, 100, 10));
            set.patterns[0].colors.Add(new Model.Color());
            string test = JSONConverter.SerializeSet(set);
            Set someSet = JSONConverter.DeserializeJSONSet(test);
            */
            ColorGuruViewModel blah = new ColorGuruViewModel(this);
            InitializeComponent();
            this.DataContext = blah;
            patternList.ItemsSource = blah.activeSet.patterns;
            //ColorListView.ItemsSource = blah.activePattern.colors;
            Background = new SolidColorBrush(Color.FromArgb(0xFF, 53, 56, 61));
        }
    }
}
