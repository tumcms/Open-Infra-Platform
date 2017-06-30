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

#include "ImportOkstra.h"

#undef _DEBUG

#include "DateiAusgabe.h"
#include "DateiEingabe.h"
#include "XMLEingabeKonverter.h"
#include "CTEEingabeKonverter.h"
#include "DateiProtokollant.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h"
#include "OpenInfraPlatform/Infrastructure/Core/Line2.h"
#include <regex>
#include <boost/filesystem.hpp>

std::string latinToUTF8(const std::string& str);

class OpenInfraPlatform::Infrastructure::ImportOkstra::OkstraImportImpl : public Import
{
public:
	enum class OKSTRA_PVI_Type
	{
		Start,
		Line,
		Parabola,
	};

	struct OKSTRA_PVI
	{
		OKSTRA_PVI_Type pvi_type;
		buw::Vector2d Position;
		double Anfangssteigung;
		double Endsteigung;

		// pvi_type : Parabola
		double Ausrundung;
		double Tangentenlaenge;
	};

public:
	OkstraImportImpl(const std::string& filename) : 
		Import(filename)
	{
		Oklabi::DateiAusgabe *logFile = Oklabi::DateiAusgabe::Erzeuge(Oklabi::Text("oklabi.txt"));
		Oklabi::Protokollant* logger = Oklabi::DateiProtokollant::Erzeuge(logFile);
		Oklabi::Umgebung::Registriere(logger);
		Oklabi::Umgebung::Melde(-1, Oklabi::Text("Test"), Oklabi::eMeldTyp::info, Oklabi::eProtokollTyp::meldungen);
		Oklabi::Datenbestand* bestand;

		buw::String buwstrFilename = filename.c_str();
		if (buwstrFilename.toLower().endsWith(".xml"))
		{
			bestand = LiesXML(filename);
		}
		else if (buwstrFilename.toLower().endsWith(".cte"))
		{
			bestand = LiesCTE(filename);
		}
		
		majorVersion = bestand->GibVersion()->GibHauptversion();
		minorVersion = bestand->GibVersion()->GibUnterversion();

		// Über den Bestand laufen, die Fachobjekte aufzählen

		Oklabi::ObjektartListType list;
		list.push_back(Oklabi::Objektart::Gib("Trasse", bestand->GibVersion()));
		list.push_back(Oklabi::Objektart::Gib("DGM", bestand->GibVersion()));

		Oklabi::Objektartfilter* filter = Oklabi::Objektartfilter::Erzeuge(&list);

		Oklabi::Enumerator* enumerator = bestand->GibEnumerator(filter);

		int objekte = 0;
		while (!enumerator->IstBeendet())
		{
			// Objekt aus Enumerator auslesen
			++objekte;
			Oklabi::Fachobjekt* fachobjekt = enumerator->GibObjekt<Oklabi::Fachobjekt*>();
			const Oklabi::Objektart* oa = fachobjekt->GibObjektart();
			std::string objektartname = fachobjekt->GibObjektartname();

			if (objektartname == "Trasse")
			{
				const Oklabi::AnyType* hat_Achse = fachobjekt->Gib("hat_Achse");
				Oklabi::Enumerator* achsEnumerator = hat_Achse->GibEnumerator();

				while (!achsEnumerator->IstBeendet())
				{
					Oklabi::Fachobjekt* achse = achsEnumerator->GibObjekt<Oklabi::Fachobjekt*>();

					besucheAchse(achse);

					achsEnumerator->Weiter();
				}

			}
			else if (objektartname == "DGM")
			{
				digitalElevationModel_ = std::make_shared<buw::DigitalElevationModel>();
				Oklabi::Fachobjekt* dgm = enumerator->GibObjekt<Oklabi::Fachobjekt*>();

				besucheDGM(dgm);

			}
			enumerator->Weiter();
		}

		bestand->Vernichte();
		filter->Vernichte();
		logger->Vernichte();
		logFile->Vernichte();
	}

	void besucheAchse(Oklabi::Fachobjekt* achse)
	{
		const Oklabi::AnyType* hat_Achselement = achse->Gib("hat_Achselement");
		Oklabi::Enumerator* elementEnumerator = hat_Achselement->GibEnumerator();

		const Oklabi::Fachobjekt* achselement = elementEnumerator->GibObjekt<Oklabi::Fachobjekt*>();
		double station = achselement->Gib("Anfangsstation_rechnerisch")->Gib<double>();

		currentHorizontalAlignment_ = std::make_shared<HorizontalAlignment2D>(station);
		currentVerticalAlignment_ = std::make_shared<VerticalAlignment2D>();
		currentAlignment_ = std::make_shared<buw::Alignment2DBased3D>(currentHorizontalAlignment_, currentVerticalAlignment_);
		alignmentModel_->addAlignment(currentAlignment_);

		std::string strBezeichnung = achse->Gib("Bezeichnung")->Gib<Oklabi::Text>();
		strBezeichnung = latinToUTF8(strBezeichnung);
		currentAlignment_->setName(strBezeichnung);

		int numElements = 0;
		while (!elementEnumerator->IstBeendet())
		{
			numElements++;
			elementEnumerator->Weiter();
		}

		// FIXED!!! not a bug anymore ---- 'probably a bug in oklabi, when importing OKSTRA 2.016 the enumerator lists every object twice'
		//if (majorVersion == 2)
		//	numElements *= 0.5;

		elementEnumerator->ZumAnfang();

		for (int i = 0; i < numElements; i++)
		{
			Oklabi::Fachobjekt* achselement = elementEnumerator->GibObjekt<Oklabi::Fachobjekt*>();
			besucheAchselement(achselement);

			elementEnumerator->Weiter();
		}

		if (majorVersion == 1)
		{
			const Oklabi::Fachobjekt* laengsschnitt = getFirstElement(achse, "hat_Laengsschnitt");
			if (laengsschnitt)
			{
				const Oklabi::Fachobjekt* gradiente = getFirstElement(laengsschnitt, "hat_Gradiente");
				if (gradiente)
					besucheGradiente(gradiente);
			}
		}
		else if (majorVersion == 2)
		{
			const Oklabi::Fachobjekt* gradiente = getFirstElement(achse, "hat_Gradiente");
			if (gradiente)
				besucheGradiente(gradiente);
		}
	}

	void besucheAchselement(Oklabi::Fachobjekt* fachobjekt)
	{
		buw::Vector2d start, end;

		const Oklabi::Fachobjekt* achshauptpunktBeginn = getFirstElement(fachobjekt, "beginnt_bei_Achshauptpunkt");
		if (achshauptpunktBeginn)
		{
			if (majorVersion == 1)
			{
				const Oklabi::Fachobjekt* punkt = getFirstElement(achshauptpunktBeginn, "dargestellt_von_Punkt");
				if (punkt)
				{
					const Oklabi::Koordinate koord = punkt->Gib("hat_Lage")->Gib<Oklabi::Koordinate>();
					start.x() = koord.X();
					start.y() = koord.Y();
				}
			}
			else if (majorVersion == 2)
			{
				const Oklabi::GeoPunkt* geo = static_cast<const Oklabi::GeoPunkt*>(achshauptpunktBeginn->Gib("Punktgeometrie")->Gib<Oklabi::Geometrie*>());
				start.x() = geo->X();
				start.y() = geo->Y();
			}
			
		}
		else
			return;

		const Oklabi::Fachobjekt* achshauptpunktEnde = getFirstElement(fachobjekt, "endet_bei_Achshauptpunkt");
		if (achshauptpunktEnde)
		{
			if (majorVersion == 1)
			{
				const Oklabi::Fachobjekt* punkt = getFirstElement(achshauptpunktEnde, "dargestellt_von_Punkt");
				if (punkt)
				{
					const Oklabi::Koordinate koord = punkt->Gib("hat_Lage")->Gib<Oklabi::Koordinate>();
					end.x() = koord.X();
					end.y() = koord.Y();
				}
			}
			else if (majorVersion == 2)
			{
				const Oklabi::GeoPunkt* geo = static_cast<const Oklabi::GeoPunkt*>(achshauptpunktEnde->Gib("Punktgeometrie")->Gib<Oklabi::Geometrie*>());
				end.x() = geo->X();
				end.y() = geo->Y();
			}
		}
		else
			return;

		const Oklabi::Fachobjekt* elementTyp = getFirstElement(fachobjekt, "Elementtyp");
		if (elementTyp)
		{
			Oklabi::Text type = elementTyp->Gib("Langtext")->Gib<Oklabi::Text>();
			if (type == "Gerade")
			{
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line =
					std::make_shared<buw::HorizontalAlignmentElement2DLine>(start, end);

				currentHorizontalAlignment_->addElement(line);
			}
			else if (type == "Klothoide")
			{
				double length =				fachobjekt->Gib("Laenge")->Gib<double>();
				double startRadius =		fachobjekt->Gib("Radius_zu_Beginn")->Gib<double>();
				double endRadius =			fachobjekt->Gib("Radius_am_Ende")->Gib<double>();
				double clothoidConstant =	fachobjekt->Gib("Parameter")->Gib<double>();
				double startDirection =		fachobjekt->Gib("Richtung")->Gib<double>();

				double startCurvature = 0;
				if (startRadius != 0 && startRadius != std::numeric_limits<double>::infinity())
					startCurvature = 1 / abs(startRadius);

				double endCurvature = 0;
				if (endRadius != 0 && endRadius != std::numeric_limits<double>::infinity())
					endCurvature = 1 / abs(endRadius);

				bool isEntry = buw::HorizontalAlignmentElement2DClothoid::computeEntry(startCurvature, endCurvature);
				bool clockwise = (startRadius > 0  && endRadius >=0 ) || (endRadius > 0 && startRadius >= 0);

				buw::clothoidDescription desc(start,
					startDirection,
					startCurvature,
					!clockwise,
					clothoidConstant,
					isEntry,
					length);
				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = std::make_shared<buw::HorizontalAlignmentElement2DClothoid>(desc);

				currentHorizontalAlignment_->addElement(clothoid);
			}
			else if (type == "Kreisbogen, tangential")
			{
				double startDirection = fachobjekt->Gib("Richtung")->Gib<double>();
				double radius = fachobjekt->Gib("Radius_zu_Beginn")->Gib<double>();

				// compute center point
				buw::Vector2d toCenter = buw::createRotationMatrix(startDirection + 0.5 * buw::constantsd::pi()) * buw::Vector2d(1.0, 0.0);

				bool clockwise = radius > 0;

				buw::Vector2d center = start - toCenter.block<2,1>(0,0) * radius;


				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc = std::make_shared<buw::HorizontalAlignmentElement2DArc>(
					center,
					start,
					end,
					clockwise);

				currentHorizontalAlignment_->addElement(arc);
			}
		}
	}

	void besucheGradiente(const Oklabi::Fachobjekt* gradiente)
	{
		std::vector<OKSTRA_PVI> pvis;

		if (majorVersion == 1) // OKSTRA 1.x
		{
			const Oklabi::AnyType* hat_LS_Koor = gradiente->Gib("hat_LS_Koor");
			Oklabi::Enumerator* koorEnumerator = hat_LS_Koor->GibEnumerator();

			while (!koorEnumerator->IstBeendet())
			{
				Oklabi::Fachobjekt* ls_koor = koorEnumerator->GibObjekt<Oklabi::Fachobjekt*>();

				OKSTRA_PVI pvi;
				pvi.Position = buw::Vector2d(ls_koor->Gib("Station")->Gib<double>(), ls_koor->Gib("Hoehe")->Gib<double>());
				pvi.pvi_type = OKSTRA_PVI_Type::Start;

				const Oklabi::Fachobjekt* punktfolge = getFirstElement(ls_koor, "folgt_auf_LS_Koor");
				if (punktfolge)
				{
					pvi.pvi_type = OKSTRA_PVI_Type::Line;

					const Oklabi::Fachobjekt* tangenteGerade = getFirstElement(punktfolge, "hat_Tangente_Gerade");
					if (tangenteGerade)
					{
						const Oklabi::Fachobjekt* tangentenFolge = getFirstElement(tangenteGerade, "folgt_auf_Tangente_Gerade");
						if (tangentenFolge)
						{
							const Oklabi::Fachobjekt* ausrundung = getFirstElement(tangentenFolge, "hat_Ausrundung");
							if (ausrundung)
							{
								pvis.back().pvi_type = OKSTRA_PVI_Type::Parabola;
								pvis.back().Ausrundung = ausrundung->Gib("Ausrundungsparameter")->Gib<double>();
							}
						}
					}
				}
				pvis.push_back(pvi);

				koorEnumerator->Weiter();
			}
		}
		else if (majorVersion == 2) // OKSTRA 2.x
		{
			const Oklabi::AnyType* hat_LS_Koor = gradiente->Gib("hat_Grad_Koor");
			Oklabi::Enumerator* koorEnumerator = hat_LS_Koor->GibEnumerator();

			while (!koorEnumerator->IstBeendet())
			{
				Oklabi::Fachobjekt* grad_koor = koorEnumerator->GibObjekt<Oklabi::Fachobjekt*>();

				OKSTRA_PVI pvi;
				pvi.Position = buw::Vector2d(grad_koor->Gib("Station")->Gib<double>(), grad_koor->Gib("Hoehe")->Gib<double>());
				pvi.pvi_type = OKSTRA_PVI_Type::Line;

				const Oklabi::Fachobjekt* ausrundung = getFirstElement(grad_koor, "hat_Ausrundung");
				if (ausrundung)
				{
					pvi.Ausrundung = ausrundung->Gib("Scheitelradius")->Gib<double>();
					pvi.pvi_type = OKSTRA_PVI_Type::Parabola;
				}

				pvis.push_back(pvi);
				koorEnumerator->Weiter();
			}

			if (pvis.size() > 0)
				pvis[0].pvi_type = OKSTRA_PVI_Type::Start;
		}


		// calculate missing values
		for (int i = 0; i < pvis.size(); i++)
		{
			OKSTRA_PVI_Type type = pvis[i].pvi_type;

			if (type != OKSTRA_PVI_Type::Start)
				pvis[i].Anfangssteigung = buw::Line2d(pvis[i - 1].Position, pvis[i].Position).getGradient();

			if (type != OKSTRA_PVI_Type::Line)
				pvis[i].Endsteigung = buw::Line2d(pvis[i].Position, pvis[i + 1].Position).getGradient();

			if (pvis[i].pvi_type == OKSTRA_PVI_Type::Parabola)
			{
				pvis[i].Ausrundung *= pvis[i].Anfangssteigung > pvis[i].Endsteigung ? -1 : 1;
				pvis[i].Tangentenlaenge = pvis[i].Ausrundung * (pvis[i].Endsteigung - pvis[i].Anfangssteigung) / 2.0;
			}
		}

		// evaluate pvis
		buw::Vector2d lastPosition;
		for (int i = 0; i < pvis.size(); i++)
		{
			if (pvis[i].pvi_type == OKSTRA_PVI_Type::Start)
				lastPosition = pvis[i].Position;

			else if (pvis[i].pvi_type == OKSTRA_PVI_Type::Parabola)
			{
				buw::Line2d l1(pvis[i - 1].Position, pvis[i].Position);
				buw::Line2d l2(pvis[i].Position, pvis[i + 1].Position);

				buw::Vector2d pvc = l1.eval(pvis[i].Position.x() - pvis[i].Tangentenlaenge);
				buw::Vector2d pvt = l2.eval(pvis[i].Position.x() + pvis[i].Tangentenlaenge);

				auto line = std::make_shared<buw::VerticalAlignmentElement2DLine>(lastPosition, pvc);
				auto parabola = std::make_shared<buw::VerticalAlignmentElement2DParabola>(pvc, pvt, pvis[i].Anfangssteigung, pvis[i].Endsteigung);

				currentVerticalAlignment_->addElement(line);
				currentVerticalAlignment_->addElement(parabola);

				lastPosition = pvt;
			}

			else if (pvis[i].pvi_type == OKSTRA_PVI_Type::Line)
			{
				auto line = std::make_shared<buw::VerticalAlignmentElement2DLine>(lastPosition, pvis[i].Position);
				currentVerticalAlignment_->addElement(line);

				lastPosition = pvis[i].Position;
			}
		}

	}

	void besucheDGM(const Oklabi::Fachobjekt* dgm)
	{
		buw::ReferenceCounted<buw::Surface> surface = std::make_shared<buw::Surface>();

		const Oklabi::AnyType* hat_Dreiecke = dgm->Gib("hat_Dreiecke");
		Oklabi::Enumerator* dreieckEnumerator = hat_Dreiecke->GibEnumerator();

		std::map<int, int> idToIndex;

		while (!dreieckEnumerator->IstBeendet())
		{
			buw::Vector3i indices;
			int vertex = 0;

			Oklabi::Fachobjekt* dreieck = dreieckEnumerator->GibObjekt<Oklabi::Fachobjekt*>();
			const Oklabi::AnyType* hat_Punkte = dreieck->Gib("hat_Punkte");
			Oklabi::Enumerator* punktEnumerator = hat_Punkte->GibEnumerator();
			while (!punktEnumerator->IstBeendet())
			{
				if (vertex >= 3)
					break;

				Oklabi::Fachobjekt* punkt = punktEnumerator->GibObjekt<Oklabi::Fachobjekt*>();

				int id = punkt->Gib("Oklabinummer")->Gib<int>();

				if (idToIndex.find(id) == idToIndex.end())
				{
					if (majorVersion == 1)
					{
						const Oklabi::Fachobjekt* dargestellt = getFirstElement(punkt, "dargestellt_von_Punkt");
						if (dargestellt)
						{
							Oklabi::Koordinate koord = dargestellt->Gib("hat_Lage")->Gib<Oklabi::Koordinate>();

							buw::Vector3d p(koord.X(), koord.Y(), koord.Z());


							idToIndex[id] = surface->getPointCount();
							surface->addPoint(p);
						}
					}
					else if (majorVersion == 2)
					{
						const Oklabi::GeoPunkt* geo = static_cast<const Oklabi::GeoPunkt*>(punkt->Gib("Punktgeometrie")->Gib<Oklabi::Geometrie*>());

						buw::Vector3d p(geo->X(), geo->Y(), geo->Z());

						idToIndex[id] = surface->getPointCount();
						surface->addPoint(p);
					}

				}

				indices[vertex] = idToIndex[id];				
				vertex++;

				punktEnumerator->Weiter();
			}
			surface->addTriangle(indices);

			dreieckEnumerator->Weiter();
		}

		digitalElevationModel_->addSurface(surface);
	}

private:
	const Oklabi::Fachobjekt* getFirstElement(const Oklabi::Fachobjekt* fachobjekt, const Oklabi::Text& name)
	{
		const Oklabi::AnyType* container = fachobjekt->Gib(name);
		if (container->IstUnbelegt())
			return nullptr;
		if (container->GibTyp() != Oklabi::eTyp::objectType)
			return nullptr;
		if (container->IstMehrwertig())
		{
			Oklabi::Enumerator* enumerator = container->GibEnumerator();
			return enumerator->GibObjekt<Oklabi::Fachobjekt*>();
		}
		else
			return container->Gib<Oklabi::Fachobjekt*>(); //<- not tested, if this assertion occurs please try it out
	}

	Oklabi::Datenbestand* LiesXML(const std::string &filename)
	{
		Oklabi::Eingabe* inputFile = Oklabi::DateiEingabe::Erzeuge(Oklabi::Text(filename.c_str()));
		static_cast<Oklabi::DateiEingabe*>(inputFile)->SetzeKodierung(Oklabi::eKodierung::UTF8);
		Oklabi::XMLEingabeKonverter* inputConverter = Oklabi::XMLEingabeKonverter::Erzeuge(inputFile);

		Oklabi::Version* version = inputConverter->GibVersion();
		std::string strVers = version->GibText();

		strVers = buw::replace(strVers, ".", "");

		if (strVers.size() > 4)	strVers = strVers.substr(0, 4);
		if (strVers == "1008")
			strVers += "1";
		else if (strVers == "1009")
			strVers += "4";
		else if (strVers == "1010")
			strVers += "1";
		std::string schLoc = "schema/" + strVers + "/okstra.xsd";
		if (boost::filesystem::exists(schLoc))
		{
			// Es gibt eine lokale Repräsentation der Schemadateien: diese verwenden // todo warum wird lokale nicht verwendet?
			if (strVers.size() > 4) strVers = strVers.substr(0, 4);
			schLoc = "http://schema.okstra.de/" + strVers + "/okstra " + buw::replace(schLoc, " ", "%20");
			inputConverter->SetzeSchemaLocation(schLoc);
		}

		// Datenbestand einlesen und abliefern
		// Am längten dauert die Validierung der Datei!
		Oklabi::Datenbestand* bestand = inputConverter->Lade(nullptr);

		inputFile->Schliesse();

		inputConverter->Vernichte();
		inputFile->Vernichte();

		return bestand;
	}

	Oklabi::Datenbestand* LiesCTE(const std::string &filename)
	{
		Oklabi::Eingabe* inputFile = Oklabi::DateiEingabe::Erzeuge(Oklabi::Text(filename.c_str()));
		Oklabi::CTEEingabeKonverter* inputConverter = Oklabi::CTEEingabeKonverter::Erzeuge(inputFile);

		// Datenbestand einlesen und abliefern
		// Am längten dauert die Validierung der Datei!
		Oklabi::Datenbestand* bestand = inputConverter->Lade(nullptr);

		inputFile->Schliesse();

		inputConverter->Vernichte();
		inputFile->Vernichte();

		return bestand;
	}

private:
	buw::ReferenceCounted<buw::Alignment2DBased3D>		currentAlignment_ = nullptr;
	buw::ReferenceCounted<buw::HorizontalAlignment2D>		currentHorizontalAlignment_;
	buw::ReferenceCounted<buw::VerticalAlignment2D>		currentVerticalAlignment_;

	int									majorVersion, minorVersion;
};

OpenInfraPlatform::Infrastructure::ImportOkstra::ImportOkstra(const std::string& filename) :
	Import(filename),
	impl_(new OkstraImportImpl(filename))
{
	alignmentModel_ = impl_->getAlignmentModel();
	digitalElevationModel_ = impl_->getDigitalElevationModel();
}


std::string latinToUTF8(const std::string& str)
{
	std::string utf8Str;
	for (char c : str)
	{
		uint8_t ch = c; /* assume that code points above 0xff are impossible since latin-1 is 8-bit */

		if (ch < 0x80) {
			utf8Str.append(1, ch);
		}
		else {
			utf8Str.append(1, 0xc0 | (ch & 0xc0) >> 6); /* first byte, simplified since our range is only 8-bits */
			utf8Str.append(1, 0x80 | (ch & 0x3f));
		}
	}

	return utf8Str;
}