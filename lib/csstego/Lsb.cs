using System;
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

        [DllImport(CsStgLib, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern unsafe bool Encode(in string data, byte *container, int size);
        
        [DllImport(CsStgLib, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern unsafe bool Decode(in byte *container, int size, out IntPtr data);

    }
}