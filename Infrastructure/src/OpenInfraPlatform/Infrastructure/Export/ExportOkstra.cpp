/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ExportOkstra.h"

#include "DateiAusgabe.h"
#include "DateiEingabe.h"
#include "XMLEingabeKonverter.h"
#include "XMLAusgabeKonverter.h"
#include "CTEAusgabeKonverter.h"
#include "DateiProtokollant.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"


class OpenInfraPlatform::Infrastructure::ExportOkstra::OkstraExportImpl : public Export
{
public:
	OkstraExportImpl(int majorV, int minorV, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
		Export(am, dem, filename)
	{
		majorVersion = majorV;
		minorVersion = minorV;

		Oklabi::DateiAusgabe *logFile = Oklabi::DateiAusgabe::Erzeuge("oklabi.txt");
		Oklabi::Protokollant* logger = Oklabi::DateiProtokollant::Erzeuge(logFile);
		Oklabi::Umgebung::Registriere(logger);
		Oklabi::Umgebung::Melde(-1, "OKSTRA Export", Oklabi::eMeldTyp::info, Oklabi::eProtokollTyp::meldungen);

		Oklabi::DateiAusgabe* outputFile = Oklabi::DateiAusgabe::Erzeuge(filename);
		Oklabi::AusgabeKonverter* outputConverter;

		buw::String bfilename = filename;
		bfilename = bfilename.toLower();
		if (bfilename.endsWith(".xml"))
		{
			outputConverter = Oklabi::XMLAusgabeKonverter::Erzeuge(outputFile);
		}
		else if (bfilename.endsWith(".cte"))
		{
			outputConverter = Oklabi::CTEAusgabeKonverter::Erzeuge(outputFile);
		}
		else
			assert(false);

		version = Oklabi::Version::Erzeuge(majorVersion, minorVersion);
		bestand = Oklabi::Datenbestand::Erzeuge(version);

		if (digitalElevationModel_->getSurfaceCount())
		{
			exportDigitalElevationModel(digitalElevationModel_);
		}

		if (alignmentModel_->getAlignmentCount()> 0)
		{
			Oklabi::Fachobjekt* trasse = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Trasse", version));
			
			trasse->Setze("Bezeichnung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Trasse"));

			Oklabi::Fachobjekt* bestandsstatus = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Bestandsstatus", version));
			Oklabi::Fachobjekt* artAchse = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Art_Achse", version));
			Oklabi::Fachobjekt* artGradiente = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Art_Gradiente", version));

			if (majorVersion == 1)
			{
				bestandsstatus->Setze("Kennung", Oklabi::AnyType::Erzeuge(6));
				bestandsstatus->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("unbekannt"));
				artAchse->Setze("Kennung", Oklabi::AnyType::Erzeuge(1));
				artAchse->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Hauptachse"));
				artGradiente->Setze("Kennung", Oklabi::AnyType::Erzeuge(1));
				artGradiente->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Hauptfahrbahn"));
			}
			else if (majorVersion == 2)
			{
				bestandsstatus->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("6"));
				artAchse->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("1"));
				artGradiente->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("1"));
			}

			for (const auto& alignment : alignmentModel_->getAlignments())
			{				
				if (alignment->getType() == buw::e3DAlignmentType::e3DBased)
					continue;;

				Oklabi::Fachobjekt* achse = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achse", version));
				trasse->FuegeHinzu("hat_Achse", Oklabi::AnyType::Erzeuge(achse));

				achse->Setze("Bezeichnung", Oklabi::AnyType::Erzeuge<Oklabi::Text>(alignment->getName().toCString()));
				achse->Setze("Bestandsstatus", Oklabi::AnyType::Erzeuge(bestandsstatus));
				achse->Setze("Art_Achse", Oklabi::AnyType::Erzeuge(artAchse));

				buw::ReferenceCounted<buw::Alignment2DBased3D> alignment2D = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment);
				buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = alignment2D->getHorizontalAlignment();
				buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment = alignment2D->getVerticalAlignment();

				exportHorizontalAlignment(horizontalAlignment, achse);

				// Vertical Alignments
				if (alignment2D->hasVerticalAlignment() && verticalAlignment->getAlignmentElementCount() > 0)
				{
					Oklabi::Fachobjekt* gradiente = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Gradiente", version));

					if (majorVersion == 1)
					{
						Oklabi::Fachobjekt* laengsschnitt = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Laengsschnitt", version));
						achse->FuegeHinzu("hat_Laengsschnitt", Oklabi::AnyType::Erzeuge(laengsschnitt));
						trasse->FuegeHinzu("hat_Laengsschnitt", Oklabi::AnyType::Erzeuge(laengsschnitt)); 
						laengsschnitt->FuegeHinzu("hat_Gradiente", Oklabi::AnyType::Erzeuge(gradiente));
					}
					else if (majorVersion == 2)
					{
						achse->FuegeHinzu("hat_Gradiente", Oklabi::AnyType::Erzeuge(gradiente));
					}					

					gradiente->Setze("Bezeichnung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("unbenannt"));
					gradiente->Setze("Bestandsstatus", Oklabi::AnyType::Erzeuge(bestandsstatus));
					gradiente->Setze("Art_Gradiente", Oklabi::AnyType::Erzeuge(artGradiente));

					exportVerticalAlignment(verticalAlignment, gradiente);
				}
			}
		}

		outputConverter->Entlade(bestand);

		bestand->Vernichte();
		version->Vernichte();
		outputConverter->Vernichte();
		outputFile->Vernichte();
		logger->Vernichte();
		logFile->Vernichte();
	}

private:
	void exportDigitalElevationModel(const buw::ReferenceCounted<buw::DigitalElevationModel> digitalElevationModel)
	{
		Oklabi::Fachobjekt* dgm = bestand->FuegeHinzu(Oklabi::Objektart::Gib("DGM", version));
		dgm->Setze("Bezeichnung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Geländemodell"));

		for (int i = 0; i < digitalElevationModel->getSurfaceCount(); i++)
		{
			buw::ReferenceCounted<buw::Surface> surface = digitalElevationModel->getSurface(i);

			const std::vector<buw::Vector3d>& points = surface->getPoints();
			std::vector<Oklabi::Fachobjekt*> punkte;

			for (const buw::Vector3d& p : points)
			{
				Oklabi::Fachobjekt* allg_punkt = bestand->FuegeHinzu(Oklabi::Objektart::Gib("allgemeines_Punktobjekt", version));

				if (majorVersion == 1)
				{
					Oklabi::Fachobjekt* punkt = erzeugePunkt(p);
					allg_punkt->FuegeHinzu("dargestellt_von_Punkt", Oklabi::AnyType::Erzeuge(punkt));					
				}
				else if (majorVersion == 2)
				{
					Oklabi::GeoPunkt* punkt = Oklabi::GeoPunkt::Erzeuge(p.x(), p.y(), p.z());
					allg_punkt->Setze("Punktgeometrie", Oklabi::AnyType::Erzeuge<Oklabi::Geometrie*>(punkt));
				}

				punkte.push_back(allg_punkt);
			}

			const std::vector<buw::Vector3i>& faces = surface->getTriangeFaces();
			for (const buw::Vector3i& face : faces)
			{
				Oklabi::Fachobjekt* dreieck = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Dreieck", version));
				dgm->FuegeHinzu("hat_Dreiecke", Oklabi::AnyType::Erzeuge(dreieck));

				dreieck->FuegeHinzu("hat_Punkte", Oklabi::AnyType::Erzeuge(punkte[face[0]]));
				dreieck->FuegeHinzu("hat_Punkte", Oklabi::AnyType::Erzeuge(punkte[face[1]]));
				dreieck->FuegeHinzu("hat_Punkte", Oklabi::AnyType::Erzeuge(punkte[face[2]]));
			}
		}
	}

	void exportHorizontalAlignment(buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment, Oklabi::Fachobjekt* achse)
	{
		Oklabi::Fachobjekt* typGerade = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achselementtyp", version));
		Oklabi::Fachobjekt* typKreisbogen = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achselementtyp", version));
		Oklabi::Fachobjekt* typeKlothoide = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achselementtyp", version));

		if (majorVersion == 1)
		{
			typGerade->Setze("Kennung", Oklabi::AnyType::Erzeuge(1));
			typGerade->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Gerade"));
			typKreisbogen->Setze("Kennung", Oklabi::AnyType::Erzeuge(2));
			typKreisbogen->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Kreisbogen, tangential"));
			typeKlothoide->Setze("Kennung", Oklabi::AnyType::Erzeuge(12));
			typeKlothoide->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Klothoide"));
		}
		else if (majorVersion == 2)
		{
			typGerade->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("1"));
			typKreisbogen->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("2"));
			typeKlothoide->Setze("Kennung", Oklabi::AnyType::Erzeuge<Oklabi::Text>("12"));
		}

		double station = horizontalAlignment->getStartStation();;
		for (int i = 0; i < horizontalAlignment->getAlignmentElementCount(); i++)
		{
			buw::ReferenceCounted<buw::HorizontalAlignmentElement2D> element = horizontalAlignment->getAlignmentElementByIndex(i);

			Oklabi::Fachobjekt* achselement = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achselement", version));
			achse->FuegeHinzu("hat_Achselement", Oklabi::AnyType::Erzeuge(achselement));

			Oklabi::Fachobjekt* achshauptpunktBeginn = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achshauptpunkt", version));
			Oklabi::Fachobjekt* achshauptpunktEnde = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Achshauptpunkt", version));
			achselement->FuegeHinzu("beginnt_bei_Achshauptpunkt", Oklabi::AnyType::Erzeuge(achshauptpunktBeginn));
			achselement->FuegeHinzu("endet_bei_Achshauptpunkt", Oklabi::AnyType::Erzeuge(achshauptpunktEnde));

			buw::Vector2d start = element->getStartPosition();
			buw::Vector2d end = element->getEndPosition();

			if (majorVersion == 1)
			{
				Oklabi::Fachobjekt* punktBeginn = erzeugePunkt(buw::Vector3d(start.x(), start.y(), 0));
				Oklabi::Fachobjekt* punktEnde = erzeugePunkt(buw::Vector3d(end.x(), end.y(), 0));
				achshauptpunktBeginn->FuegeHinzu("dargestellt_von_Punkt", Oklabi::AnyType::Erzeuge(punktBeginn));
				achshauptpunktEnde->FuegeHinzu("dargestellt_von_Punkt", Oklabi::AnyType::Erzeuge(punktEnde));
			}
			else if (majorVersion == 2)
			{
				Oklabi::GeoPunkt* punktBeginn = Oklabi::GeoPunkt::Erzeuge(start.x(), start.y(), 0);
				Oklabi::GeoPunkt* punktEnde = Oklabi::GeoPunkt::Erzeuge(end.x(), end.y(), 0);

				achshauptpunktBeginn->Setze("Punktgeometrie", Oklabi::AnyType::Erzeuge<Oklabi::Geometrie*>(punktBeginn));
				achshauptpunktEnde->Setze("Punktgeometrie", Oklabi::AnyType::Erzeuge<Oklabi::Geometrie*>(punktEnde));
			}

			achselement->Setze("Laenge", Oklabi::AnyType::Erzeuge(element->getLength()));
			achselement->Setze("Anfangsstation_rechnerisch", Oklabi::AnyType::Erzeuge(station));

			switch (element->getAlignmentType())
			{
			case buw::eHorizontalAlignmentType::Line:
			{
				achselement->FuegeHinzu("Elementtyp", Oklabi::AnyType::Erzeuge(typGerade));

				buw::Vector2d direction = (element->getEndPosition() - element->getStartPosition());
				direction.normalize();

				double angle = acos(direction.x());

				if (direction.y() < 0)
					angle = (2 * M_PI) - angle;

				achselement->Setze("Richtung", Oklabi::AnyType::Erzeuge(angle));
				break;
			}
			case buw::eHorizontalAlignmentType::Arc:
			{
				achselement->FuegeHinzu("Elementtyp", Oklabi::AnyType::Erzeuge(typKreisbogen));

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::static_pointer_cast<buw::HorizontalAlignmentElement2DArc>(element);

				buw::Vector2d normal;
				arc->genericQuery(buw::eAlignmentElementQueryId::Center, &normal);

				bool cwise;
				arc->genericQuery(buw::eAlignmentElementQueryId::Clockwise, &cwise);

				buw::Vector2d yAxis(0, 1.0);
				double radius = arc->getRadius();
				if (!cwise)
				{
					radius *= -1;
					yAxis.y() *= -1;
				}

				normal = arc->getStartPosition() - normal;
				double angle = buw::calculateAngleBetweenVectors(yAxis, normal);

				achselement->Setze("Radius_zu_Beginn", Oklabi::AnyType::Erzeuge(radius));
				achselement->Setze("Radius_am_Ende", Oklabi::AnyType::Erzeuge(radius));
				achselement->Setze("Richtung", Oklabi::AnyType::Erzeuge(angle));
				break;
			}
			case buw::eHorizontalAlignmentType::Clothoid:
			{
				achselement->FuegeHinzu("Elementtyp", Oklabi::AnyType::Erzeuge(typeKlothoide));

				double radiusStart;
				element->genericQuery(buw::eAlignmentElementQueryId::RadiusStart,
					&radiusStart);

				double radiusEnd = 0.0;
				element->genericQuery(buw::eAlignmentElementQueryId::RadiusEnd,
					&radiusEnd);

				double clothoidConstant;
				element->genericQuery(buw::eAlignmentElementQueryId::ClothoidConstant,
					&clothoidConstant);

				double startDirection;
				element->genericQuery(buw::eAlignmentElementQueryId::AlignmentStartDirection1D,
					&startDirection);

				bool cwise;
				element->genericQuery(buw::eAlignmentElementQueryId::Clockwise,
					&cwise);

				if (radiusStart == std::numeric_limits<double>::infinity())
					radiusStart = 0;
				if (radiusEnd == std::numeric_limits<double>::infinity())
					radiusEnd = 0;

				if (!cwise)
				{
					radiusStart *= -1;
					radiusEnd *= -1;
				}

				achselement->Setze("Radius_zu_Beginn", Oklabi::AnyType::Erzeuge(radiusStart));
				achselement->Setze("Radius_am_Ende", Oklabi::AnyType::Erzeuge(radiusEnd));
				achselement->Setze("Parameter", Oklabi::AnyType::Erzeuge(clothoidConstant));
				achselement->Setze("Richtung", Oklabi::AnyType::Erzeuge(startDirection));

				break;
			}
			default:
				break;
			}

			station += element->getLength();
		}
	}

	void exportVerticalAlignment(buw::ReferenceCounted<buw::VerticalAlignment2D> verticalAlignment, Oklabi::Fachobjekt* gradiente)
	{
		Oklabi::Fachobjekt* parabeltyp;

		if (majorVersion == 1)
		{
			parabeltyp = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Ausrundungstyp", version));
			parabeltyp->Setze("Kennung", Oklabi::AnyType::Erzeuge(13));
			parabeltyp->Setze("Langtext", Oklabi::AnyType::Erzeuge<Oklabi::Text>("Parabel 2. Grades"));
		}

		enum class OKSTRA_PVI_Type
		{
			Start,
			Line,
			Parabola
		};

		struct OKSTRA_PVI
		{
			OKSTRA_PVI_Type pvi_type;
			buw::Vector2d Position;

			// pvi_type : Parabola
			double Ausrundung;
		};

		std::vector<OKSTRA_PVI>pvis;

		double station = verticalAlignment->getStartStation();
		for (int i = 0; i < verticalAlignment->getAlignmentElementCount(); i++)
		{
			buw::ReferenceCounted<buw::VerticalAlignmentElement2D> element = verticalAlignment->getAlignmentElementByIndex(i);

			if (i == 0)
			{
				OKSTRA_PVI pvi;
				pvi.pvi_type = OKSTRA_PVI_Type::Start;
				pvi.Position = element->getStartPosition();
				pvis.push_back(pvi);
			}

			if (i == verticalAlignment->getAlignmentElementCount() - 1
				|| (element->getAlignmentType() == buw::eVerticalAlignmentType::Line
				&& verticalAlignment->getAlignmentElementByIndex(i + 1)->getAlignmentType() != buw::eVerticalAlignmentType::Parabola)
				)
			{
				OKSTRA_PVI pvi;
				pvi.pvi_type = OKSTRA_PVI_Type::Line;
				pvi.Position = element->getEndPosition();
				pvis.push_back(pvi);
			}

			if (element->getAlignmentType() == buw::eVerticalAlignmentType::Parabola)
			{
				OKSTRA_PVI pvi;
				pvi.pvi_type = OKSTRA_PVI_Type::Parabola;
				element->genericQuery(buw::eAlignmentElementQueryId::PVI, &pvi.Position);

				double T, startGradient, endGradient;
				element->genericQuery(buw::eAlignmentElementQueryId::IntersectionPointDistance, &T);
				element->genericQuery(buw::eAlignmentElementQueryId::StartGradient, &startGradient);
				element->genericQuery(buw::eAlignmentElementQueryId::EndGradient, &endGradient);

				pvi.Ausrundung = abs(T / (endGradient - startGradient));

				pvis.push_back(pvi);
			}
		}


		if (majorVersion == 1)
		{
			for (int i = 0; i < pvis.size(); i++)
			{
				Oklabi::Fachobjekt* koor = bestand->FuegeHinzu(Oklabi::Objektart::Gib("LS_Koor", version));
				gradiente->FuegeHinzu("hat_LS_Koor", Oklabi::AnyType::Erzeuge(koor));

				koor->Setze("Station", Oklabi::AnyType::Erzeuge(pvis[i].Position.x()));
				koor->Setze("Hoehe", Oklabi::AnyType::Erzeuge(pvis[i].Position.y()));

				if (pvis[i].pvi_type != OKSTRA_PVI_Type::Start)
				{
					Oklabi::Fachobjekt* punktfolge = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Punktfolge", version));
					koor->FuegeHinzu("folgt_auf_LS_Koor", Oklabi::AnyType::Erzeuge(punktfolge));

					Oklabi::Fachobjekt* tangenteGerade = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Tangente_Gerade", version));
					punktfolge->FuegeHinzu("hat_Tangente_Gerade", Oklabi::AnyType::Erzeuge(tangenteGerade));

					if (pvis[i - 1].pvi_type == OKSTRA_PVI_Type::Parabola)
					{
						Oklabi::Fachobjekt* tangentenfolge = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Tangentenfolge", version));
						tangenteGerade->FuegeHinzu("folgt_auf_Tangente_Gerade", Oklabi::AnyType::Erzeuge(tangentenfolge));

						Oklabi::Fachobjekt* ausrundung = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Ausrundung", version));
						tangentenfolge->FuegeHinzu("hat_Ausrundung", Oklabi::AnyType::Erzeuge(ausrundung));

						ausrundung->Setze("Ausrundungsparameter", Oklabi::AnyType::Erzeuge(pvis[i - 1].Ausrundung));
						ausrundung->FuegeHinzu("Ausrundungstyp", Oklabi::AnyType::Erzeuge(parabeltyp));
					}
				}
			}
		}
		else if (majorVersion == 2)
		{
			for (int i = 0; i < pvis.size(); i++)
			{
				Oklabi::Fachobjekt* gradKoor = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Grad_Koor", version));
				gradiente->FuegeHinzu("hat_Grad_Koor", Oklabi::AnyType::Erzeuge(gradKoor));

				gradKoor->Setze("Station", Oklabi::AnyType::Erzeuge(pvis[i].Position.x()));
				gradKoor->Setze("Hoehe", Oklabi::AnyType::Erzeuge(pvis[i].Position.y()));

				if (pvis[i].pvi_type == OKSTRA_PVI_Type::Parabola)
				{
					Oklabi::Fachobjekt* ausrundung = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Ausrundung", version));
					gradKoor->FuegeHinzu("hat_Ausrundung", Oklabi::AnyType::Erzeuge(ausrundung));

					ausrundung->Setze("Scheitelradius", Oklabi::AnyType::Erzeuge(pvis[i].Ausrundung));
				}
			}
		}
	}

	Oklabi::Fachobjekt* erzeugePunkt(const buw::Vector3d& position)
	{
		Oklabi::Fachobjekt* punkt = bestand->FuegeHinzu(Oklabi::Objektart::Gib("Punkt", version));

		Oklabi::Fachobjekt* directposition = bestand->FuegeHinzu(Oklabi::Objektart::Gib("direct_position", version));
		punkt->Setze("hat_Lage", Oklabi::AnyType::Erzeuge(directposition));

		Oklabi::AnyType* koord = Oklabi::AnyType::Erzeuge((double)0, true);
		koord->FuegeHinzuBei<double>(position.x(), 0);
		koord->FuegeHinzuBei<double>(position.y(), 1);
		koord->FuegeHinzuBei<double>(position.z(), 2);
		directposition->Setze("Koordinate", koord);

		return punkt;
	}

private:
	int majorVersion, minorVersion;
	Oklabi::Datenbestand* bestand;
	Oklabi::Version* version;
};

OpenInfraPlatform::Infrastructure::ExportOkstra::ExportOkstra(int majorVersion, int minorVersion, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename) :
Export(am, dem, filename),
impl_(new OkstraExportImpl(majorVersion, minorVersion, am, dem, filename))
{	

}

OpenInfraPlatform::Infrastructure::ExportOkstra::~ExportOkstra()
{

}
