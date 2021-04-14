using System;
using System.Collections;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Security.Cryptography;
using CsStg;
using Xunit;
using Xunit.Abstractions;

namespace LsbTestCase
{
    public unsafe class LsbTestCase
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
            var random = new byte[100];
            _crypto.GetBytes(random);
            
            fixed (byte* p = random)
            {
                Assert.True(Lsb.Encode(Data, p, random.Length));
            }
        }
        
        [Fact]
        public void EncodeImageTest()
        {
            var bitmap = new Bitmap(10, 10);

            using var stream = new MemoryStream();
            
            bitmap.Save(stream, ImageFormat.Png);
            var random = stream.ToArray();
            
            fixed (byte* p = random)
            {
                Assert.True(Lsb.Encode(Data, p, random.Length));
            }
        }
    }
}