using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace BlueFramework
{
    namespace BlueCore
    {
        namespace Math
        {
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct vector2d
            {
                public double x;
                public double y;
            }

            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct vector3d
            {
                public double x;
                public double y;
                public double z;
            }
        }
    }
}

namespace BlueFramework
{
    namespace Infrastructure
    {
        static class DLL
        {
            public const string Filename = @"C:\Users\Dominic\Desktop\Studium\MA4\Master-Thesis\Implementierung\build\Visual Studio 2013\BlueInfrastructureCenter\Debug\BlueFramework.Infrastructured.dll";
            // public const string Filename = @"C:\build\vs2013\BlueInfrastructureCenter\Debug\BlueFramework.Infrastructured.dll";
        }
    } // end namespace Infrastructure
} // end namespace BlueFramework
