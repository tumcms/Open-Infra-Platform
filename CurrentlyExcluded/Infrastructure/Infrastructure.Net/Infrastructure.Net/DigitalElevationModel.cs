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
        public class DigitalElevationModel
        {
            public DigitalElevationModel(IntPtr handle)
            {
                this.handle = handle;
            }

            public double GetHeightAtPosition(double x, double y)
            {
                return DigitalElevationModel_getHeightAtPosition(handle, x, y);
            }

            public int SurfaceCount { get { return DigitalElevationModel_SurfaceCount(handle); } }

            public Surface GetSurface(int index)
            {
                return new Surface(DigitalElevationModel_GetSurface(handle, index));
            }

            public List<Surface> GetAllSurfaces()
            {
                List<Surface> output = new List<Surface>();

                for (int i = 0; i < SurfaceCount; i++)
                {
                    output.Add(new Surface(DigitalElevationModel_GetSurface(handle, i)));
                }
                return output;
            }

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static double DigitalElevationModel_getHeightAtPosition(IntPtr handle, double x, double y);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static int DigitalElevationModel_SurfaceCount(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr DigitalElevationModel_GetSurface(IntPtr handle,int index);

            private IntPtr handle;
        }
    }
}
