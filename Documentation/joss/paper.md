---
title: 'TUM Open Infra Platform: open source package for simultaneous viewing and analysis of Industry Foundation Classes (IFC) and Point Cloud Data (PCD) models'
tags:
  - industry foundation classes (IFC)
  - point cloud data (PCD)
  - EXPRESS parser
authors:
  - name: Stefan Jaud^[corresponding author]
    orcid: 0000-0003-0387-3440
    affiliation: 1
  - name: Helge Hecht
    affiliation: 1
  - name: Julian Amann
    affiliation: 1
  - name: Jonas Schlenger
    affiliation: 1
affiliations:
 - name: Chair for Computational Modelling and Simulation, Technical University of Munich
   index: 1
date: 24 December 2020
bibliography: paper.bib
---

# Summary

*TUM Open Infra Platform* (OIP) is an open source application for
 viewing and analysis of different BIM models used in the civil engineering field.
OIP supports reading, visualization, navigating, and handling of:

- Industry Foundation Classes (IFC) models as specified in ISO 16739 [@iso16739];
- Point Cloud Data (PCD) models as supported by the Cloud Compare library [CloudCompare].

Multiple models can be loaded at once and compared between each other (see Figure \ref{fig:ifcpcd}).
Their absolute position is accounted for, so the models can be checked against one another for internal differences based on location of elements.

![A PCD model together with an IFC model loaded in OIP.\label{fig:ifcpcd}](../images/ifc_and_pcd.png)

Additionally, OIP incorporates its own EXPRESS lexer and parser.
This enables automatic code generation for IFC early-binding library [@Hecht:2019:FBI].
As such, complete contents of IFC files can be interpreted and analysed.
Moreover, type safety is guaranteed at compile time thus reducing the risk for bugs and errors.

Let it be stated here that OIP serves as a prototypical playground for developments.
During the past 3 years, OIP was completely restructured and its code base overhauled - the IFC now stands as the internal model [@Hecht:2019:FBI].
Major elements were already realigned, while some (previously available) functionality is still considered as work-in-progress.

# Statement of Need

The Architecture, Engineering and Construction (AEC) domain is in its transition from 2D design processes to 3D object-oriented modelling. 
Building Information Modelling (BIM) is steadily gaining importance replacing the conventional Computer-Aided Design (CAD) practices
 and getting implemented in every aspect of the very complex software and stakeholder landscape [@Jaud:2018:iccce].

During the development of IFC standard, a clear need for an independent software
 capable of consuming and producing IFC files according to the newly developed schemata was determined [@Amann:2015:OIP; @Amann:2015:ICCBEI].
OIP fulfils this role by being open source and based on well known libraries (like Qt and Boost).

Additionally, the EXPRESS parser provided proved useful for automatically producing
 source code and data models from newly developed schemata as needed [@vilgertshofer:2017:iwcce].

With the emergence of Scan2BIM and ScanVsBIM research field (deriving from or merely comparing PCD and BIM models),
 a tool that supports both PCD and IFC data is a welcomed addition to the research processes.
Recently, OIP was selected among many other software solutions as best suitable for the development of a Scan+BIM platform [@Valero:2020:ISARC].

# Research Projects

The origins of the software date back to the first projects expanding IFC for infrastructure
 at the Technical University of Munich [@Singer:2014:IfcAlignment; @Amann:2015:OIP; @Amann:2015:OKSTRA; @Amann:2015:ICCBEI].
There, first implementations of roads' geometric concepts and interfacing between multiple standards (like IFC, OKSTRA and LandXML) have been explored.

![A view of road geometry on terrain's surface with clearly marked cuts and fills.](../images/Beta1_5_Windows8_1.png)

Further on, many prototypical additions were implemented during the course of projects:

- support for `IFC4x1`, `IFC4x2`, and `IFC4x3` candidate versions of the IFC standard during their development [@Jaud:2020:siBIM];
- support for first experimental IFC schema additions for tunnel [@vilgertshofer:2017:iwcce];
- support for linked data approaches [@Beetz:2019:linkeddata];
- support for PCD and their analysis [@Hecht:2018:PCdtoAlignment];
- support for IFC Programming Language (IFC-PL) [@Amann:2018:diss].

# Acknowledgements

The development of the software has been supported through many projects founded by:

- buildingSMART International Ltd.;
- Federal Ministry for Transport and Digital Infrastructure, Germany (Bundesministerium für Verkehr und digitale Infrastruktur);
- Federal Highway Research Institute, Germany (Bundesanstallt für Straßenwesen);
- German research Foundation, Germany (Deutsche Forschungsgesellschaft).

We gratefully acknowledge their support.

# References

