/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is free
    software; you can redistribute it and/or modify it under the terms
    of the GNU General Public License Version 3 as published by the Free
    Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef OpenInfraPlatform_ExpressBindingGenerator_GeneratorCPP_18047f8d_098b_4199_b0bb_835a22ba9848_h
#define OpenInfraPlatform_ExpressBindingGenerator_GeneratorCPP_18047f8d_098b_4199_b0bb_835a22ba9848_h

#include "Generator/Generator.h"
#include "Meta/Schema.h"
#include "General/namespace.h"
#include <iostream>
#include <set>
#include <map>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class GeneratorOIP : public Generator {
public:
    GeneratorOIP(const std::string& outputDirectory);

    virtual ~GeneratorOIP();

	void generate(const Schema& schema) override { generateREFACTORED(schema); }

	void generateREFACTORED(const Schema &schema);

private:
    void createEntitiesMapHeaderFile(const Schema &schema);

	void createTypesHeaderFileREFACTORED(const Schema &schema);
	
	void createEntitiesHeaderFileREFACTORED(const Schema &schema);

	void generateEntitySourceFileREFACTORED(const Schema &schema, const Entity &entity) const;

	void generateTypeHeaderFileREFACTORED(const Schema &schema, const Type &type) const ;

	void generateTypeSourceFileREFACTORED(const Schema &schema, const Type &type) const;

	void generateReaderFiles(const Schema &schema);

	void generateWriterFile(const Schema &schema);

	void generateEMTFiles(const Schema &schema);

    std::string convertSimpleTypeToCPPType(const Schema &schema, std::string simpleType) const;

    void includeFile(const std::string &filename, std::ofstream &file);

	void generateCMakeListsFileREFACTORED(const Schema &schema);

	void generateEntityHeaderFileREFACTORED(const Schema &schema, const Entity &entity)const;

	void generateSchemaHeader(const Schema& schema);

	void generateNamespaceHeader(const Schema &schema);

private:
    // main function for preparation
    void prepareGeneration(const Schema& schema);
    // prepares the paths, mkdir the directories needed
    void preparePaths(const Schema& schema);
    // prepares the sets of includes
    void prepareIncludes(const Schema& schema);
    // figures out the schema parts (splits up)
    void prepareSplits(const Schema& schema);
	// gets the API define
	std::string getAPIDefine(const std::string& name) const;
    // gets the API guard
    std::string getAPIGuard(const std::string& name) const;

    // figuring out includes
    void getCachedIncludes(const std::string& name, std::set<std::string>& types, std::set<std::string>& entities) const;
    void resolveSelectTypeIncludes(const Schema& schema, const Type& type, std::set<std::string>& includes, std::set<std::string>& resolved);
    void resolveEntityIncludes(const Schema& schema, const Entity& entity, std::set<std::string>& includes, std::set<std::string>& resolved);
    void resolveIncludes(const Schema& schema, const Type& type);
    void resolveIncludes(const Schema& schema, const Entity& entity);

    std::map<std::string, std::set<std::string>> cacheIncludesTypes; //< cached set of includes for each type (saves computational time)
    std::map<std::string, std::set<std::string>> cacheIncludesEntities; //< cached set of includes for each entity (saves computational time)

private:
    // get the relative path given the entity's name and the folder
	std::string getFolder(const std::string& name) const;

    // map with (entity/type name) -> (folder name in SRC folder where to save it)
    std::map<std::string,std::string> mapFolderInSrc_; 
    // paths
    std::string outputDirectory_;
    std::string rootDirectory_;
	std::string sourceDirectory_;
	std::string readerPath_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_EXPRESSBINDINGGENERATOR_INTO_OIP_NAMESPACE(GeneratorOIP)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_GeneratorCPP_18047f8d_098b_4199_b0bb_835a22ba9848_h
