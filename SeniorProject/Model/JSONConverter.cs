using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    public static class JSONConverter
    {
        public static string SerializePattern( Pattern pat)
        {
            return Newtonsoft.Json.JsonConvert.SerializeObject(pat);
        }
        public static string SerializeSet(Set set)
        {
            return Newtonsoft.Json.JsonConvert.SerializeObject(set);
        }

        public static Pattern DeserializeJSONPattern(string json)
        {
            return Newtonsoft.Json.JsonConvert.DeserializeObject<Pattern>(json);
        }

        public static Set DeserializeJSONSet(string json)
        {
            return Newtonsoft.Json.JsonConvert.DeserializeObject<Set>(json);
        }
    }
}
