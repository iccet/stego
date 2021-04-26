using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Xml.Linq;

namespace SharedData
{
    class Program
    {
        private static readonly string BaseDir = AppDomain.CurrentDomain.BaseDirectory;
        private static readonly string Name = AppDomain.CurrentDomain.FriendlyName;

        private static void Main(string[] args)
        {
            var fileName = string.Join('.', Name, "resx");
            string[] extensions = { "jpg", "png" };
            
            var files = extensions.SelectMany(e => Directory.GetFiles(BaseDir, $"*.{e}"))
                .Select(f => new FileInfo(f));

            var res = XDocument.Load(fileName, LoadOptions.None);
            
            foreach (var file in files)
            {
                using var stream = new MemoryStream();
                var bitmap = new Bitmap(file.Open(FileMode.Open));
                
                bitmap.Save(stream, ImageFormat.Jpeg);
                var value = Convert.ToBase64String(stream.ToArray());
                res.Element("root")?.Add(new XElement("data",
                    new XAttribute("name", Path.GetFileNameWithoutExtension(file.Name)),
                    new XElement("value", value)));
            }
            
            res.Save(string.Join('.', Name, "Generated", "resx"));

        }
    }
}