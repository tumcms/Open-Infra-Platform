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
        public  class HorizontalAlignmentElement2DClothoid
        {
            public HorizontalAlignmentElement2DClothoid()
            {
                handle = new IntPtr(0);
                handle = HorizontalAlignmentElement2DClothoid_Create();
            }

            ~HorizontalAlignmentElement2DClothoid()
            {
                HorizontalAlignmentElement2DClothoid_Destroy(handle);
            }

            public BlueCore.Math.vector2d GetPosition(double lerpParamter)
            {
                return HorizontalAlignmentElement2DClothoid_getPosition(handle, lerpParamter);
            }

            public double Length
            {
                get
                {
                    return GetLength();
                }
            }

            private double GetLength()
            {
                return HorizontalAlignmentElement2DClothoid_getLength(handle);
            }

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr HorizontalAlignmentElement2DClothoid_Create();

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static void HorizontalAlignmentElement2DClothoid_Destroy(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static double HorizontalAlignmentElement2DClothoid_getLength(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static BlueCore.Math.vector2d HorizontalAlignmentElement2DClothoid_getPosition(IntPtr handle, double lerpParamter);

            private IntPtr handle;
        }
    }
}