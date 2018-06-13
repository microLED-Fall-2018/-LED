using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace SeniorProject.Model
{
    static class HTTPClient
    {
        public static void PostSet(Set set)
        {
            var httpWebRequest = (HttpWebRequest)WebRequest.Create("http://url");
            httpWebRequest.ContentType = "application/json";
            httpWebRequest.Method = "POST";

            using (var streamWriter = new StreamWriter(httpWebRequest.GetRequestStream()))
            {
                string json = JSONConverter.SerializeSet(set);

                streamWriter.Write(json);
                streamWriter.Flush();
                streamWriter.Close();
            }

            var httpResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            using (var streamReader = new StreamReader(httpResponse.GetResponseStream()))
            {
                var result = streamReader.ReadToEnd();
            }
        }

        public static void PostPattern(Pattern pattern)
        {
            var httpWebRequest = (HttpWebRequest)WebRequest.Create("http://url");
            httpWebRequest.ContentType = "application/json";
            httpWebRequest.Method = "POST";

            using (var streamWriter = new StreamWriter(httpWebRequest.GetRequestStream()))
            {
                string json = JSONConverter.SerializePattern(pattern);

                streamWriter.Write(json);
                streamWriter.Flush();
                streamWriter.Close();
            }

            var httpResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            using (var streamReader = new StreamReader(httpResponse.GetResponseStream()))
            {
                var result = streamReader.ReadToEnd();
            }
        }

        public static Set GetSet(int setID)
        {
            string json;
            var httpWebRequest = (HttpWebRequest)WebRequest.Create("http://url");
            httpWebRequest.Method = "GET";

            var httpReponse = (HttpWebResponse)httpWebRequest.GetResponse();
            using (var streamReader = new StreamReader(httpReponse.GetResponseStream()))
            {
                json = streamReader.ReadToEnd();
            }

            return JSONConverter.DeserializeJSONSet(json);
        }

        public static Pattern GetPattern(int patternID)
        {
            string json;
            var httpWebRequest = (HttpWebRequest)WebRequest.Create("http://url");
            httpWebRequest.Method = "GET";

            var httpReponse = (HttpWebResponse)httpWebRequest.GetResponse();
            using (var streamReader = new StreamReader(httpReponse.GetResponseStream()))
            {
                json = streamReader.ReadToEnd();
            }

            return JSONConverter.DeserializeJSONPattern(json);
        }
    }
}
