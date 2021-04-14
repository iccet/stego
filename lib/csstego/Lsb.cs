using System;
using System.Runtime.InteropServices;

namespace CsStg
{
    public static class Lsb
    {
        private const string CsStgLib = "libCsStg.so";


        [DllImport(CsStgLib, CallingConvention = CallingConvention.StdCall)]
        public static extern unsafe bool Encode(string data, byte *container, int size);
        
        [DllImport(CsStgLib, CallingConvention = CallingConvention.StdCall)]
        public static extern unsafe string Decode(string data, byte *container, int size);
        

    }
}