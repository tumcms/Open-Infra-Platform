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

    void generate(const Schema &schema);

	void generateREFACTORED(const Schema &schema);

private:
    void createEntitiesMapHeaderFile(const Schema &schema);

    void createTypesHeaderFile(const Schema &schema);

	void createTypesHeaderFileREFACTORED(const Schema &schema);
	
	void createEntitiesHeaderFile(const Schema &schema);

	void createEntitiesHeaderFileREFACTORED(const Schema &schema);

	void generateEntitySourceFile(const Schema &schema, const Entity &entity);

	void generateEntitySourceFileREFACTORED(const Schema &schema, const Entity &entity) const;

    void generateTypeHeaderFile(const Schema &schema, const Type &type);

	void generateTypeHeaderFileREFACTORED(const Schema &schema, const Type &type) const ;

    void generateTypeSourceFile(const Schema &schema, const Type &type);
    
	void generateTypeSourceFileREFACTORED(const Schema &schema, const Type &type) const;

    void generateTypeSourceFileGetStepParameter(const Type &type, std::ofstream &out, const Schema &schema);

	void generateReaderFiles(const Schema &schema);

	void generateWriterFile(const Schema &schema);

	void generateEMTFiles(const Schema &schema);

    std::string convertSimpleTypeToCPPType(const Schema &schema, std::string simpleType) const;

    void includeFile(const std::string &filename, std::ofstream &file);

    void generateCMakeListsFile(const Schema &schema);

	void generateCMakeListsFileREFACTORED(const Schema &schema);


    void createEntityBrokerCPPFile(const Schema &schema);

    void generateEntityHeaderFile(const Schema &schema, const Entity &entity);

	void generateEntityHeaderFileREFACTORED(const Schema &schema, const Entity &entity)const;

    void generateEntityEnumsHeaderFile(const Schema &schema);

	void generateSchemaHeader(const Schema& schema);

	void generateNamespaceHeader(const Schema &schema);

private:
    // figuring out includes
    bool isIncluding(const std::string& name, std::string str ) const;
    void getCachedIncludes(const std::string& name, std::set<std::string>& types, std::set<std::string>& entities) const;
    void resolveSelectTypeIncludes(const Schema& schema, const Type& type, std::set<std::string>& includes, std::set<std::string>& resolved);
    void resolveEntityIncludes(const Schema& schema, const Entity& entity, std::set<std::string>& includes, std::set<std::string>& resolved);
    void resolveIncludes(const Schema& schema, const Type& type);
    void resolveIncludes(const Schema& schema, const Entity& entity);

    std::map<std::string, std::set<std::string>> cacheIncludesTypes; //< cached set of includes for each type (saves computational time)
    std::map<std::string, std::set<std::string>> cacheIncludesEntities; //< cached set of includes for each entity (saves computational time)
    std::string outputDirectory_;
    std::string rootDirectory_;
    std::string sourceDirectory_;
    std::string guidPath_;
    std::string entityPath_;
	std::string selectPath_;
	std::string entityRootPath_;
	std::string selectRootPath_;
	std::string typePath_;
    std::string readerPath_;
    std::string modelPath_;
    std::string writerPath_;
    std::string xmlPath_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(GeneratorOIP)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_GeneratorCPP_18047f8d_098b_4199_b0bb_835a22ba9848_h
