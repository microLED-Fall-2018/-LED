using SeniorProject.ViewModel;


namespace SeniorProject
{
    public static class JSONConverter
    {
        public static string SerializePattern(PatternViewModel pat)
        {
            return Newtonsoft.Json.JsonConvert.SerializeObject(pat);
        }
        public static string SerializeSet(SetViewModel set)
        {
            return Newtonsoft.Json.JsonConvert.SerializeObject(set);
        }

        public static PatternViewModel DeserializeJSONPattern(string json)
        {
            return Newtonsoft.Json.JsonConvert.DeserializeObject<PatternViewModel>(json);
        }

        public static SetViewModel DeserializeJSONSet(string json)
        {
            return Newtonsoft.Json.JsonConvert.DeserializeObject<SetViewModel>(json);
        }
    }
}
