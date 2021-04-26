using System;
using System.Runtime.InteropServices;

namespace CsStg
{
    public class Lsb : AbstractEncoder
    {

        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern unsafe bool LsbEncode(string data, byte *container, int size);
        
        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern unsafe int LsbDecode(byte *container, int size, out IntPtr data);

        protected override unsafe bool Encode(string data, byte* container, int size)
        {
            return LsbEncode(data, container, size);
        }

        protected override unsafe int Decode(byte* container, int size, out IntPtr data)
        {
            return LsbDecode(container, size, out data);
        }
    }
}