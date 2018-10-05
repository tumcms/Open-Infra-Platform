#include "generation.hpp"
#include <string>
#include <boost/variant.hpp>

namespace EXPRESS
{
    namespace IFC4_Entities
    {
		using IfcReal = IFC4_SKELETON::IfcReal_Skelaton<float>;
        using IfcApplication = IFC4_SKELETON::IfcApplication_Skelaton<IfcStrippedOptional, IfcAbsorbedDoseMeasure, std::string>;
    }

	namespace IFC5_Entities {
		using IfcReal = IFC4_SKELETON::IfcReal_Skelaton<double>;
		using IfcApplication = IFC4_SKELETON::IfcApplication_Skelaton<IfcStrippedOptional, IfcAbsorbedDoseMeasure, std::string>;
	}

	namespace IFC_Entities {
		using IfcReal = IFC4_SKELETON::IfcReal_Skelaton<boost::variant<double, float>>;
		using IfcApplication = IFC4_SKELETON::IfcApplication_Skelaton<IfcStrippedOptional, IfcAbsorbedDoseMeasure, std::string>;
	}
}
