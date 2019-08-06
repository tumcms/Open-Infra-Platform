using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using BlueFramework.Infrastructure;

namespace DotNetWrapperTest
{
    class Program
    {
        static void Main(string[] args)
        {
            string fileName = @"C:/Users/Dominic/Desktop/Studium/MA4/Master-Thesis/Implementierung/blueinfrastructurecenter/testdata/LandXML/Mainbruecke_Klingenberg.xml";

            LandXmlParser parser = new LandXmlParser(fileName);
            DigitalElevationModel digitalElevationModel = parser.DigitalElevationModel;
            AlignmentModel alignmentModel = parser.AlignmentModel;


            int number = alignmentModel.AlignmentsCount;
            Alignment2DBased3D alignment = alignmentModel.GetAlignmentByIndex(0);
            List<Alignment2DBased3D> all = alignmentModel.GetAllAlignments();

            foreach(Alignment2DBased3D al in all)
            {
                System.Console.WriteLine(al.ToString());

                for (double lerpParamter = 0; lerpParamter < 1.0f; lerpParamter += 0.02)
                {
                    System.Console.WriteLine(lerpParamter + "; " + "(" + al.GetPosition(lerpParamter).x + "," + al.GetPosition(lerpParamter).y + ")" + " HEIGHT: " + digitalElevationModel.GetHeightAtPosition(al.GetPosition(lerpParamter).x, al.GetPosition(lerpParamter).y));
                    ;
                }
            }

            int nr = digitalElevationModel.SurfaceCount;
            Surface s = digitalElevationModel.GetSurface(0);

            nr = s.PointsCount;
            nr = s.FaceCount;

            BlueFramework.BlueCore.Math.vector3d point = s.GetPoint(0);
            BlueFramework.BlueCore.Math.vector3d face = s.GetFace(0);

            System.Console.WriteLine("Start staion: " + alignment.GetStartStation());
            System.Console.WriteLine("End staion: " + alignment.GetEndStation());


            System.Console.WriteLine("Position: "
                + alignment.GetPosition(0.1).x + ","
                + alignment.GetPosition(0.1).y + ","
                + alignment.GetPosition(0.1).z
            );


            HorizontalAlignmentElement2DClothoid c = new HorizontalAlignmentElement2DClothoid();
            for (double lerpParamter = 0; lerpParamter < 1.0f; lerpParamter += 0.02)
            {
                System.Console.WriteLine(lerpParamter + "; " + "(" + c.GetPosition(lerpParamter).x + "," + c.GetPosition(lerpParamter).y + ")");
            }

            System.Console.ReadLine();
        }
    }
}
