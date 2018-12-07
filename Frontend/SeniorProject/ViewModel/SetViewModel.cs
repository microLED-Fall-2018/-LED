using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SeniorProject.ViewModel
{
    public class SetViewModel: BaseViewModel
    {
        public string setName { get; set; } = "Default Set";
        public ObservableCollection<PatternViewModel> patterns;
        public int activePatternIndex;
        public SetViewModel()
        {
            activePatternIndex = 0;
            patterns = new ObservableCollection<PatternViewModel>();
            Add(new PatternViewModel());
        }

        public SetViewModel(ObservableCollection<PatternViewModel> patterns)
        {
            this.patterns = patterns;
        }

        private void Add(PatternViewModel pattern)
        {
            patterns.Add(pattern);
            activePatternIndex++;
        }

        public void Insert(PatternViewModel pattern)
        {
            if (activePatternIndex == patterns.Count)
                Add(pattern);
            else
                patterns.Insert(++activePatternIndex, pattern);
        }

        public override string ToString()
        {
            return setName;
        }
    }
}
