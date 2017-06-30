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
        public class LandXmlParser
        {
            public LandXmlParser(string filename)
            {
                this.handle = new IntPtr(0);
                this.handle = LandXmlParser_Create(filename);
            }


            public DigitalElevationModel DigitalElevationModel
            {
                get
                {
                    return new DigitalElevationModel(LandXmlParser_GetDigitalElevationModel(this.handle));
                }
            }

            public AlignmentModel AlignmentModel 
            {
                get
                {
                    return new AlignmentModel(LandXmlParser_GetAlignmentModel(this.handle));
                }
            }

            public BlueCore.Math.vector3d Center 
            {
                get 
                {
                    return LandXmlParser_GetModelCenter(this.handle);
                }
            }

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr LandXmlParser_Create( [MarshalAs(UnmanagedType.LPStr)]string filename );

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr LandXmlParser_GetAlignmentModel(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr LandXmlParser_GetDigitalElevationModel(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static BlueFramework.BlueCore.Math.vector3d LandXmlParser_GetModelCenter(IntPtr handle);

            private IntPtr handle;
        }
    }
}
