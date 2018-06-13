using System;
using System.Windows.Input;

namespace SeniorProject
{
    public class RelayCommand : ICommand
    {
        #region Private Members
        private Action mAction;
        #endregion

        #region Public Events
        public event EventHandler CanExecuteChanged = (sender, e) => { };
        #endregion

        #region Constructor
        /// <summary>
        /// Default Constructor
        /// </summary>
        public RelayCommand(Action action)
        {
            mAction = action;
        }
        #endregion

        #region Command Methods
        /// <summary>
        /// All relay commands can excute always
        /// </summary>
        /// <param name="parameter"></param>
        /// <returns></returns>
        public bool CanExecute(object parameter)
        {
            return true;
        }


        /// <summary>
        /// Execute the command Action
        /// </summary>
        /// <param name="parameter"></param>
        public void Execute(object parameter)
        {
            mAction();
        }
        #endregion
    }
}
