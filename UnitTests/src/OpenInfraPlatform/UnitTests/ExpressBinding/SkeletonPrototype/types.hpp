#include "generation.hpp"
#include <string>

namespace EXPRESS
{
    namespace IFC4_Entities
    {
		using IfcReal = IFC4_SKELETON::IfcReal_Skelaton<double>;
        using IfcApplication = IFC4_SKELETON::IfcApplication_Skelaton<IfcStrippedOptional, IfcAbsorbedDoseMeasure, std::string>;
    }

}
