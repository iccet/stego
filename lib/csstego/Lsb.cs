using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace CsStg
{
    public static class Lsb
    {
        private const string CsStgLib =
#if WINDOWS
    "libCsStg.dll"
#else
    "libCsStg.so"
#endif
    ;

        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern unsafe bool Encode(string data, byte *container, int size);
        
        [DllImport(CsStgLib, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern unsafe int Decode(byte *container, int size, out IntPtr data);

        public static unsafe string Decode(byte[] container)
        {
            fixed (byte* p = container)
            {
                var length = Decode(p, container.Length, out var data);
                Debug.Assert(length > 0);
                return Marshal.PtrToStringUTF8(data, length);
            }
        }

        public static unsafe bool Encode(string data, byte[] container)
        {
            fixed (byte* p = container)
            {
                return Encode(data, p, container.Length);
            }
        }

    }
}