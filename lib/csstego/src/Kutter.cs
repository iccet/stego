using System;
using System.Runtime.InteropServices;

namespace CsStg
{
    public class Kutter : AbstractEncoder
    {
        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern unsafe bool KutterEncode(string data, byte *container, int size);
        
        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern unsafe int KutterDecode(byte *container, int size, out IntPtr data);

        protected override unsafe bool Encode(string data, byte* container, int size)
        {
            return KutterEncode(data, container, size);
        }

        protected override unsafe int Decode(byte* container, int size, out IntPtr data)
        {
            return KutterDecode(container, size, out data);
        }
    }
}