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
        public class AlignmentModel
        {
          
            public AlignmentModel(IntPtr handle)
            {
                this.handle = handle;
            }

            public int AlignmentsCount
            {
                get { return AlignmentModel_AlignmentsCount(this.handle); }
            }

            public Alignment2DBased3D GetAlignmentByIndex(int index)
            {
                return new Alignment2DBased3D(AlignmentModel_GetAlignmentByIndex(handle, index));
            }

            public List<Alignment2DBased3D> GetAllAlignments()
            {
                List<Alignment2DBased3D> alignments = new List<Alignment2DBased3D>();

                for (int i = 0; i < AlignmentsCount; i++)
                {
                    Alignment2DBased3D alignment = new Alignment2DBased3D(AlignmentModel_GetAlignmentByIndex(handle, i));
                    if (alignment != null) alignments.Add(alignment);
                }

                return alignments;

            }

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static int AlignmentModel_AlignmentsCount(IntPtr handle);

            [DllImport(DLL.Filename, CallingConvention = CallingConvention.Cdecl)]
            private extern static IntPtr AlignmentModel_GetAlignmentByIndex(IntPtr handle, int index);

            private IntPtr handle;
        }
    }
}