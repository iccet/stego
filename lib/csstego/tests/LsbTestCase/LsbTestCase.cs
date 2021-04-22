using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Resources;
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
        private readonly ResourceManager _manager;

        public LsbTestCase(ITestOutputHelper output)
        {
            _output = output;
            _crypto = new RNGCryptoServiceProvider();
            _manager = new ResourceManager(
                string.Join('.', nameof(LsbTestCase), "SharedData"),
                GetType().Assembly); 
        }

        [Fact]
        public void EncodeBytesTest()
        {
            var bytes = new byte[1000];
            _crypto.GetBytes(bytes);
            var oldBytes = (byte[])bytes.Clone();
            
            Assert.Equal(bytes.Length, oldBytes.Length);

            Assert.True(Lsb.Encode("test", bytes));
            Assert.False(oldBytes.SequenceEqual(bytes));
            
            Assert.False(Lsb.Encode("4D4F19E2-36d5-45CC-BF98-578406e33bc1", bytes));
        }

        private IEnumerable<string> Resources()
        {
            foreach (DictionaryEntry entry in _manager.GetResourceSet(CultureInfo.CurrentUICulture, true, true))
            {
                yield return entry.Value as string;
            }
        }
        
        [Fact]
        public void EncodeImageTest()
        {
            Assert.All(Resources(), s =>
            {
                var image = Image.FromStream(new MemoryStream(Convert.FromBase64String(s)));
                var bitmap = new Bitmap(image);

                using var stream = new MemoryStream();

                bitmap.Save(stream, ImageFormat.Png);
                var bytes = stream.ToArray();

                Assert.True(Lsb.Encode("E2D9DAA5-1A21-458E-BAE3-0960A76FBABA", bytes));
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
            
            Assert.True(Lsb.Encode(data, bytes));
            
            Assert.Equal(data, Lsb.Decode(bytes));
        }
        
    }
}