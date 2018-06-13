using PropertyChanged;
using System.ComponentModel;

namespace SeniorProject
{
    /// <summary>
    /// A base view model taht fires Property Changed events
    /// </summary>
    public class BaseViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Event fired when child property is changed
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;
    }
}
