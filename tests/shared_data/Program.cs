using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Resources;

namespace SharedData
{
    class Program
    {
        private static readonly string Path = AppDomain.CurrentDomain.BaseDirectory;
        private static readonly string Name = AppDomain.CurrentDomain.FriendlyName;

        private static void Main(string[] args)
        {
            var writer = new ResourceWriter($@"{Name}.resx");
            string[] extensions = { "jpg", "png" };
            
            var files = extensions.SelectMany(e => Directory.GetFiles(Path, $"*.{e}"))
                .Select(f => new FileInfo(f));
            
            foreach (var file in files)
            {
                var bmp = new Bitmap(file.Open(FileMode.Open));
                var stream = new MemoryStream();
                bmp.Save(stream, ImageFormat.Jpeg);

                writer.AddResource(file.Name, stream);
            }

            writer.Generate();
            writer.Close();
        }
    }
}