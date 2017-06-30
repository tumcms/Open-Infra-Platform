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
        public class Surface
        {
            public Surface(IntPtr ptr)
            {
                handle = new IntPtr(0);
                handle = ptr;
            }

            public int PointsCount { get { return Surface_GetPointsCount(handle); } }
            public int FaceCount { get { return Surface_GetFaceCount(handle); } }

            public BlueCore.Math.vector3d GetPoint(int index)
            {
                return Surface_GetPoint(handle, index);
            }

            public BlueCore.Math.vector3d GetFace(int index)
            {
                return Surface_GetFace(handle, index);
            }

            public List<BlueCore.Math.vector3d> GetAllPoints()
            {
                List<BlueCore.Math.vector3d> output = new List<BlueCore.Math.vector3d>();

                for (int i = 0; i < PointsCount; i++)
                {
                    output.Add(Surface_GetPoint(handle, i));
                }

                return output;
            }

            public List<BlueCore.Math.vector3d> GetAllFaces()
            {
                List<BlueCore.Math.vector3d> output = new List<BlueCore.Math.vector3d>();

                for (int i = 0; i < FaceCount; i++)
                {
                    output.Add(Surface_GetFace(handle, i));
                }
                return output;
            }


            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static int Surface_GetPointsCount(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static int Surface_GetFaceCount(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static BlueCore.Math.vector3d Surface_GetPoint(IntPtr handle, int index);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static BlueCore.Math.vector3d Surface_GetFace(IntPtr handle, int index);

            private IntPtr handle;
        }
    }
}