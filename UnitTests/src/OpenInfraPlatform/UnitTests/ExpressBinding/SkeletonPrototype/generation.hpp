#ifndef GENERATED
#define GENERATED

#include "skeleton.hpp"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/list/for_each.hpp>

using IfcStrippedOptional = bool;
using IfcAbsorbedDoseMeasure = double;
using IfcAmountOfSubstanceMeasure = double;

namespace IFC3_SKELETON {
	#define LIST ((IfcReal, Value), ((IfcApplication, ApplicationDeveloper, Version, data3), ((IfcAppliedValue, data1, data2, data3), ((IfcApproval, data1, data2, data3), BOOST_PP_NIL))))
	BOOST_PP_LIST_FOR_EACH(TEMPLATE_GENERATION, _, LIST)
}

namespace IFC4_SKELETON
{
	TEMPLATE_GENERATION(IfcReal, Value)
    TEMPLATE_GENERATION(IfcApplication, ApplicationDeveloper, Version, data3)
    TEMPLATE_GENERATION(IfcAppliedValue, data1, data2, data3)
    TEMPLATE_GENERATION(IfcApproval, data1, data2, data3)
}

namespace IFC5_SKELETON {
	TEMPLATE_GENERATION(IfcReal, Value)
	TEMPLATE_GENERATION(IfcApplication, ApplicationDeveloper, Version, data3)
	TEMPLATE_GENERATION(IfcAppliedValue, data1, data2, data3)
	TEMPLATE_GENERATION(IfcApproval, data1, data2, data3)
}


#endif
