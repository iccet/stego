using System;
using System.Runtime.InteropServices;

namespace CsStg
{
    public abstract class AbstractEncoder
    {
        protected const string CsStgLib =
#if WINDOWS
    "libCsStg.dll"
#else
    "libCsStg.so"
#endif
    ;

        protected abstract unsafe bool Encode(string data, byte *container, int size);

        protected abstract unsafe int Decode(byte *container, int size, out IntPtr data);

        public unsafe string Decode(byte[] container)
        {
            fixed (byte* p = container)
            {
                _ = Decode(p, container.Length, out var data);
                return Marshal.PtrToStringAnsi(data);
            }
        }

        public unsafe bool Encode(string data, byte[] container)
        {
            fixed (byte* p = container)
            {
                return Encode(data, p, container.Length);
            }
        }

    }
}