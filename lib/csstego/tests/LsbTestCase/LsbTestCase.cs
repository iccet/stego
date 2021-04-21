using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using CsStg;
using Xunit;
using Xunit.Abstractions;

namespace LsbTestCase
{
    public class LsbTestCase
    {
        private readonly ITestOutputHelper _output;
        private readonly RNGCryptoServiceProvider _crypto;
        private const string Data = "test";

        public LsbTestCase(ITestOutputHelper output)
        {
            _output = output;
            _crypto = new RNGCryptoServiceProvider();
        }

        [Fact]
        public void EncodeBytesTest()
        {
            var bytes = new byte[1000];
            _crypto.GetBytes(bytes);
            var oldBytes = (byte[])bytes.Clone();
            
            Assert.Equal(bytes.Length, oldBytes.Length);

            Assert.True(Lsb.Encode(Data, bytes));
            Assert.False(oldBytes.SequenceEqual(bytes));
        }
        
        [Fact]
        public void EncodeImageTest()
        {
            var bitmap = new Bitmap(100, 100);

            using var stream = new MemoryStream();
            
            bitmap.Save(stream, ImageFormat.Png);
            var bytes = stream.ToArray();
            
            Assert.True(Lsb.Encode(Data, bytes));
        }

        [Fact]
        public void DecodeBytesTest()
        {
            var bytes = new byte[1000];
            _crypto.GetBytes(bytes);
            
            Assert.True(Lsb.Encode(Data, bytes));
            
            Assert.Equal(Data, Lsb.Decode(bytes));
        }
        
    }
}