using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace BlueFramework
{
    namespace Infrastructure
    {
        public class Alignment2DBased3D
        {
            public Alignment2DBased3D()
            {
                handle = new IntPtr(0);
                handle = Alignment2DBased3D_Create();
            }

            public Alignment2DBased3D(IntPtr ptr)
            {
                handle = new IntPtr(0);
                handle = ptr;
            }

            ~Alignment2DBased3D()
            {
                Alignment2DBased3D_Destroy(handle);
            }

            public double GetStartStation()
            {
                return Alignment2DBased3D_getStartStation(handle);
            }

            public double GetEndStation()
            {
                return Alignment2DBased3D_getEndStation(handle);
            }

            public BlueCore.Math.vector3d GetPosition(double station)
            {
                return Alignment2DBased3D_getPosition(handle, station);
            }

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr Alignment2DBased3D_Create();

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static void Alignment2DBased3D_Destroy(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static double Alignment2DBased3D_getStartStation(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static double Alignment2DBased3D_getEndStation(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static BlueCore.Math.vector3d Alignment2DBased3D_getPosition(IntPtr handle, double station);

            /*
            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static StringBuilder Alignment2DBased3D_getName(IntPtr handle);

            public override string ToString()
            {
                return Alignment2DBased3D_getName(handle).ToString();
            }
            */

            private IntPtr handle;
        }
    }
}
