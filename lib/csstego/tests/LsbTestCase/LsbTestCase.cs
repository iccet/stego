using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using CsStg;
using Xunit;
using Xunit.Abstractions;

namespace LsbTestCase
{
    public class LsbTestCase
    {
        private readonly RNGCryptoServiceProvider _crypto;
        private readonly SharedData.SharedData _designer;
        private readonly AbstractEncoder _encoder;

        public LsbTestCase(ITestOutputHelper output)
        {
            _encoder = new Lsb();
            _crypto = new RNGCryptoServiceProvider();
            _designer = new SharedData.SharedData(); 
        }

        [Fact]
        public void EncodeBytesTest()
        {
            var bytes = new byte[1000];
            _crypto.GetBytes(bytes);
            var oldBytes = (byte[])bytes.Clone();
            
            Assert.Equal(bytes.Length, oldBytes.Length);

            Assert.True(_encoder.Encode("test", bytes));
            Assert.False(oldBytes.SequenceEqual(bytes));
            
            Assert.False(_encoder.Encode("4D4F19E2-36d5-45CC-BF98-578406e33bc1", bytes));
        }
        
        [Fact]
        public void EncodeImageTest()
        {
            Assert.All(_designer.Resources(), s =>
            {
                var image = Image.FromStream(new MemoryStream(Convert.FromBase64String(s)));
                var bitmap = new Bitmap(image);

                using var stream = new MemoryStream();

                bitmap.Save(stream, ImageFormat.Png);
                var bytes = stream.ToArray();

                Assert.True(_encoder.Encode("E2D9DAA5-1A21-458E-BAE3-0960A76FBABA", bytes));
            });
        }

        [Theory]
        [InlineData("test")]
        [InlineData("Hello world")]
        [InlineData("Привет мир")]
        public void DecodeBytesTest(string data)
        {
            var bytes = new byte[1000];
            _crypto.GetBytes(bytes);
            
            Assert.True(_encoder.Encode(data, bytes));
            
            Assert.Equal(data, _encoder.Decode(bytes));
        }
        
    }
}