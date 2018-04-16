/*
    Copyright (c) 2018 Technical University of Munich
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

static std::string getStringFromEnum(std::string name, int value) {

	if(name == "IfcActionRequestTypeEnumEnum" && value == 0)
		return "EMAIL";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 1)
		return "FAX";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 2)
		return "PHONE";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 3)
		return "POST";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 4)
		return "VERBAL";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcActionRequestTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 0)
		return "DEAD_LOAD_G";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 1)
		return "COMPLETION_G1";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 2)
		return "LIVE_LOAD_Q";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 3)
		return "SNOW_S";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 4)
		return "WIND_W";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 5)
		return "PRESTRESSING_P";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 6)
		return "SETTLEMENT_U";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 7)
		return "TEMPERATURE_T";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 8)
		return "EARTHQUAKE_E";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 9)
		return "FIRE";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 10)
		return "IMPULSE";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 11)
		return "IMPACT";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 12)
		return "TRANSPORT";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 13)
		return "ERECTION";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 14)
		return "PROPPING";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 15)
		return "SYSTEM_IMPERFECTION";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 16)
		return "SHRINKAGE";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 17)
		return "CREEP";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 18)
		return "LACK_OF_FIT";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 19)
		return "BUOYANCY";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 20)
		return "ICE";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 21)
		return "CURRENT";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 22)
		return "WAVE";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 23)
		return "RAIN";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 24)
		return "BRAKES";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 25)
		return "USERDEFINED";

	if(name == "IfcActionSourceTypeEnumEnum" && value == 26)
		return "NOTDEFINED";

	if(name == "IfcActionTypeEnumEnum" && value == 0)
		return "PERMANENT_G";

	if(name == "IfcActionTypeEnumEnum" && value == 1)
		return "VARIABLE_Q";

	if(name == "IfcActionTypeEnumEnum" && value == 2)
		return "EXTRAORDINARY_A";

	if(name == "IfcActionTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcActionTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcActuatorTypeEnumEnum" && value == 0)
		return "ELECTRICACTUATOR";

	if(name == "IfcActuatorTypeEnumEnum" && value == 1)
		return "HANDOPERATEDACTUATOR";

	if(name == "IfcActuatorTypeEnumEnum" && value == 2)
		return "HYDRAULICACTUATOR";

	if(name == "IfcActuatorTypeEnumEnum" && value == 3)
		return "PNEUMATICACTUATOR";

	if(name == "IfcActuatorTypeEnumEnum" && value == 4)
		return "THERMOSTATICACTUATOR";

	if(name == "IfcActuatorTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcActuatorTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcAddressTypeEnumEnum" && value == 0)
		return "OFFICE";

	if(name == "IfcAddressTypeEnumEnum" && value == 1)
		return "SITE";

	if(name == "IfcAddressTypeEnumEnum" && value == 2)
		return "HOME";

	if(name == "IfcAddressTypeEnumEnum" && value == 3)
		return "DISTRIBUTIONPOINT";

	if(name == "IfcAddressTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcAirTerminalBoxTypeEnumEnum" && value == 0)
		return "CONSTANTFLOW";

	if(name == "IfcAirTerminalBoxTypeEnumEnum" && value == 1)
		return "VARIABLEFLOWPRESSUREDEPENDANT";

	if(name == "IfcAirTerminalBoxTypeEnumEnum" && value == 2)
		return "VARIABLEFLOWPRESSUREINDEPENDANT";

	if(name == "IfcAirTerminalBoxTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcAirTerminalBoxTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 0)
		return "DIFFUSER";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 1)
		return "GRILLE";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 2)
		return "LOUVRE";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 3)
		return "REGISTER";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcAirTerminalTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 0)
		return "FIXEDPLATECOUNTERFLOWEXCHANGER";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 1)
		return "FIXEDPLATECROSSFLOWEXCHANGER";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 2)
		return "FIXEDPLATEPARALLELFLOWEXCHANGER";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 3)
		return "ROTARYWHEEL";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 4)
		return "RUNAROUNDCOILLOOP";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 5)
		return "HEATPIPE";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 6)
		return "TWINTOWERENTHALPYRECOVERYLOOPS";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 7)
		return "THERMOSIPHONSEALEDTUBEHEATEXCHANGERS";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 8)
		return "THERMOSIPHONCOILTYPEHEATEXCHANGERS";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcAirToAirHeatRecoveryTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcAlarmTypeEnumEnum" && value == 0)
		return "BELL";

	if(name == "IfcAlarmTypeEnumEnum" && value == 1)
		return "BREAKGLASSBUTTON";

	if(name == "IfcAlarmTypeEnumEnum" && value == 2)
		return "LIGHT";

	if(name == "IfcAlarmTypeEnumEnum" && value == 3)
		return "MANUALPULLBOX";

	if(name == "IfcAlarmTypeEnumEnum" && value == 4)
		return "SIREN";

	if(name == "IfcAlarmTypeEnumEnum" && value == 5)
		return "WHISTLE";

	if(name == "IfcAlarmTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcAlarmTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcAlignmentTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcAlignmentTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcAnalysisModelTypeEnumEnum" && value == 0)
		return "IN_PLANE_LOADING_2D";

	if(name == "IfcAnalysisModelTypeEnumEnum" && value == 1)
		return "OUT_PLANE_LOADING_2D";

	if(name == "IfcAnalysisModelTypeEnumEnum" && value == 2)
		return "LOADING_3D";

	if(name == "IfcAnalysisModelTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcAnalysisModelTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 0)
		return "FIRST_ORDER_THEORY";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 1)
		return "SECOND_ORDER_THEORY";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 2)
		return "THIRD_ORDER_THEORY";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 3)
		return "FULL_NONLINEAR_THEORY";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcAnalysisTheoryTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcArithmeticOperatorEnumEnum" && value == 0)
		return "ADD";

	if(name == "IfcArithmeticOperatorEnumEnum" && value == 1)
		return "DIVIDE";

	if(name == "IfcArithmeticOperatorEnumEnum" && value == 2)
		return "MULTIPLY";

	if(name == "IfcArithmeticOperatorEnumEnum" && value == 3)
		return "SUBTRACT";

	if(name == "IfcAssemblyPlaceEnumEnum" && value == 0)
		return "SITE";

	if(name == "IfcAssemblyPlaceEnumEnum" && value == 1)
		return "FACTORY";

	if(name == "IfcAssemblyPlaceEnumEnum" && value == 2)
		return "NOTDEFINED";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 0)
		return "AMPLIFIER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 1)
		return "CAMERA";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 2)
		return "DISPLAY";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 3)
		return "MICROPHONE";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 4)
		return "PLAYER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 5)
		return "PROJECTOR";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 6)
		return "RECEIVER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 7)
		return "SPEAKER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 8)
		return "SWITCHER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 9)
		return "TELEPHONE";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 10)
		return "TUNER";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 11)
		return "USERDEFINED";

	if(name == "IfcAudioVisualApplianceTypeEnumEnum" && value == 12)
		return "NOTDEFINED";

	if(name == "IfcBeamTypeEnumEnum" && value == 0)
		return "BEAM";

	if(name == "IfcBeamTypeEnumEnum" && value == 1)
		return "JOIST";

	if(name == "IfcBeamTypeEnumEnum" && value == 2)
		return "HOLLOWCORE";

	if(name == "IfcBeamTypeEnumEnum" && value == 3)
		return "LINTEL";

	if(name == "IfcBeamTypeEnumEnum" && value == 4)
		return "SPANDREL";

	if(name == "IfcBeamTypeEnumEnum" && value == 5)
		return "T_BEAM";

	if(name == "IfcBeamTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcBeamTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcBenchmarkEnumEnum" && value == 0)
		return "GREATERTHAN";

	if(name == "IfcBenchmarkEnumEnum" && value == 1)
		return "GREATERTHANOREQUALTO";

	if(name == "IfcBenchmarkEnumEnum" && value == 2)
		return "LESSTHAN";

	if(name == "IfcBenchmarkEnumEnum" && value == 3)
		return "LESSTHANOREQUALTO";

	if(name == "IfcBenchmarkEnumEnum" && value == 4)
		return "EQUALTO";

	if(name == "IfcBenchmarkEnumEnum" && value == 5)
		return "NOTEQUALTO";

	if(name == "IfcBenchmarkEnumEnum" && value == 6)
		return "INCLUDES";

	if(name == "IfcBenchmarkEnumEnum" && value == 7)
		return "NOTINCLUDES";

	if(name == "IfcBenchmarkEnumEnum" && value == 8)
		return "INCLUDEDIN";

	if(name == "IfcBenchmarkEnumEnum" && value == 9)
		return "NOTINCLUDEDIN";

	if(name == "IfcBoilerTypeEnumEnum" && value == 0)
		return "WATER";

	if(name == "IfcBoilerTypeEnumEnum" && value == 1)
		return "STEAM";

	if(name == "IfcBoilerTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcBoilerTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcBooleanOperatorEnum" && value == 0)
		return "UNION";

	if(name == "IfcBooleanOperatorEnum" && value == 1)
		return "INTERSECTION";

	if(name == "IfcBooleanOperatorEnum" && value == 2)
		return "DIFFERENCE";

	if(name == "IfcBSplineCurveFormEnum" && value == 0)
		return "POLYLINE_FORM";

	if(name == "IfcBSplineCurveFormEnum" && value == 1)
		return "CIRCULAR_ARC";

	if(name == "IfcBSplineCurveFormEnum" && value == 2)
		return "ELLIPTIC_ARC";

	if(name == "IfcBSplineCurveFormEnum" && value == 3)
		return "PARABOLIC_ARC";

	if(name == "IfcBSplineCurveFormEnum" && value == 4)
		return "HYPERBOLIC_ARC";

	if(name == "IfcBSplineCurveFormEnum" && value == 5)
		return "UNSPECIFIED";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 0)
		return "PLANE_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 1)
		return "CYLINDRICAL_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 2)
		return "CONICAL_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 3)
		return "SPHERICAL_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 4)
		return "TOROIDAL_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 5)
		return "SURF_OF_REVOLUTION";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 6)
		return "RULED_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 7)
		return "GENERALISED_CONE";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 8)
		return "QUADRIC_SURF";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 9)
		return "SURF_OF_LINEAR_EXTRUSION";

	if(name == "IfcBSplineSurfaceFormEnum" && value == 10)
		return "UNSPECIFIED";

	if(name == "IfcBuildingElementPartTypeEnumEnum" && value == 0)
		return "INSULATION";

	if(name == "IfcBuildingElementPartTypeEnumEnum" && value == 1)
		return "PRECASTPANEL";

	if(name == "IfcBuildingElementPartTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcBuildingElementPartTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 0)
		return "COMPLEX";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 1)
		return "ELEMENT";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 2)
		return "PARTIAL";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 3)
		return "PROVISIONFORVOID";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 4)
		return "PROVISIONFORSPACE";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcBuildingElementProxyTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 0)
		return "FENESTRATION";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 1)
		return "FOUNDATION";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 2)
		return "LOADBEARING";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 3)
		return "OUTERSHELL";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 4)
		return "SHADING";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 5)
		return "TRANSPORT";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcBuildingSystemTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcBurnerTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcBurnerTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 0)
		return "BEND";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 1)
		return "CROSS";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 2)
		return "REDUCER";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 3)
		return "TEE";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcCableCarrierFittingTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 0)
		return "CABLELADDERSEGMENT";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 1)
		return "CABLETRAYSEGMENT";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 2)
		return "CABLETRUNKINGSEGMENT";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 3)
		return "CONDUITSEGMENT";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcCableCarrierSegmentTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 0)
		return "CONNECTOR";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 1)
		return "ENTRY";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 2)
		return "EXIT";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 3)
		return "JUNCTION";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 4)
		return "TRANSITION";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcCableFittingTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 0)
		return "BUSBARSEGMENT";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 1)
		return "CABLESEGMENT";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 2)
		return "CONDUCTORSEGMENT";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 3)
		return "CORESEGMENT";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcCableSegmentTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcChangeActionEnumEnum" && value == 0)
		return "NOCHANGE";

	if(name == "IfcChangeActionEnumEnum" && value == 1)
		return "MODIFIED";

	if(name == "IfcChangeActionEnumEnum" && value == 2)
		return "ADDED";

	if(name == "IfcChangeActionEnumEnum" && value == 3)
		return "DELETED";

	if(name == "IfcChangeActionEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcChillerTypeEnumEnum" && value == 0)
		return "AIRCOOLED";

	if(name == "IfcChillerTypeEnumEnum" && value == 1)
		return "WATERCOOLED";

	if(name == "IfcChillerTypeEnumEnum" && value == 2)
		return "HEATRECOVERY";

	if(name == "IfcChillerTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcChillerTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcChimneyTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcChimneyTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcCoilTypeEnumEnum" && value == 0)
		return "DXCOOLINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 1)
		return "ELECTRICHEATINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 2)
		return "GASHEATINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 3)
		return "HYDRONICCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 4)
		return "STEAMHEATINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 5)
		return "WATERCOOLINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 6)
		return "WATERHEATINGCOIL";

	if(name == "IfcCoilTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcCoilTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcColumnTypeEnumEnum" && value == 0)
		return "COLUMN";

	if(name == "IfcColumnTypeEnumEnum" && value == 1)
		return "PILASTER";

	if(name == "IfcColumnTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcColumnTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 0)
		return "ANTENNA";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 1)
		return "COMPUTER";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 2)
		return "FAX";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 3)
		return "GATEWAY";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 4)
		return "MODEM";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 5)
		return "NETWORKAPPLIANCE";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 6)
		return "NETWORKBRIDGE";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 7)
		return "NETWORKHUB";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 8)
		return "PRINTER";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 9)
		return "REPEATER";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 10)
		return "ROUTER";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 11)
		return "SCANNER";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 12)
		return "USERDEFINED";

	if(name == "IfcCommunicationsApplianceTypeEnumEnum" && value == 13)
		return "NOTDEFINED";

	if(name == "IfcComplexPropertyTemplateTypeEnumEnum" && value == 0)
		return "P_COMPLEX";

	if(name == "IfcComplexPropertyTemplateTypeEnumEnum" && value == 1)
		return "Q_COMPLEX";

	if(name == "IfcCompressorTypeEnumEnum" && value == 0)
		return "DYNAMIC";

	if(name == "IfcCompressorTypeEnumEnum" && value == 1)
		return "RECIPROCATING";

	if(name == "IfcCompressorTypeEnumEnum" && value == 2)
		return "ROTARY";

	if(name == "IfcCompressorTypeEnumEnum" && value == 3)
		return "SCROLL";

	if(name == "IfcCompressorTypeEnumEnum" && value == 4)
		return "TROCHOIDAL";

	if(name == "IfcCompressorTypeEnumEnum" && value == 5)
		return "SINGLESTAGE";

	if(name == "IfcCompressorTypeEnumEnum" && value == 6)
		return "BOOSTER";

	if(name == "IfcCompressorTypeEnumEnum" && value == 7)
		return "OPENTYPE";

	if(name == "IfcCompressorTypeEnumEnum" && value == 8)
		return "HERMETIC";

	if(name == "IfcCompressorTypeEnumEnum" && value == 9)
		return "SEMIHERMETIC";

	if(name == "IfcCompressorTypeEnumEnum" && value == 10)
		return "WELDEDSHELLHERMETIC";

	if(name == "IfcCompressorTypeEnumEnum" && value == 11)
		return "ROLLINGPISTON";

	if(name == "IfcCompressorTypeEnumEnum" && value == 12)
		return "ROTARYVANE";

	if(name == "IfcCompressorTypeEnumEnum" && value == 13)
		return "SINGLESCREW";

	if(name == "IfcCompressorTypeEnumEnum" && value == 14)
		return "TWINSCREW";

	if(name == "IfcCompressorTypeEnumEnum" && value == 15)
		return "USERDEFINED";

	if(name == "IfcCompressorTypeEnumEnum" && value == 16)
		return "NOTDEFINED";

	if(name == "IfcCondenserTypeEnumEnum" && value == 0)
		return "AIRCOOLED";

	if(name == "IfcCondenserTypeEnumEnum" && value == 1)
		return "EVAPORATIVECOOLED";

	if(name == "IfcCondenserTypeEnumEnum" && value == 2)
		return "WATERCOOLED";

	if(name == "IfcCondenserTypeEnumEnum" && value == 3)
		return "WATERCOOLEDBRAZEDPLATE";

	if(name == "IfcCondenserTypeEnumEnum" && value == 4)
		return "WATERCOOLEDSHELLCOIL";

	if(name == "IfcCondenserTypeEnumEnum" && value == 5)
		return "WATERCOOLEDSHELLTUBE";

	if(name == "IfcCondenserTypeEnumEnum" && value == 6)
		return "WATERCOOLEDTUBEINTUBE";

	if(name == "IfcCondenserTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcCondenserTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcConnectionTypeEnumEnum" && value == 0)
		return "ATPATH";

	if(name == "IfcConnectionTypeEnumEnum" && value == 1)
		return "ATSTART";

	if(name == "IfcConnectionTypeEnumEnum" && value == 2)
		return "ATEND";

	if(name == "IfcConnectionTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcConstraintEnumEnum" && value == 0)
		return "HARD";

	if(name == "IfcConstraintEnumEnum" && value == 1)
		return "SOFT";

	if(name == "IfcConstraintEnumEnum" && value == 2)
		return "ADVISORY";

	if(name == "IfcConstraintEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcConstraintEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 0)
		return "DEMOLISHING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 1)
		return "EARTHMOVING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 2)
		return "ERECTING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 3)
		return "HEATING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 4)
		return "LIGHTING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 5)
		return "PAVING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 6)
		return "PUMPING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 7)
		return "TRANSPORTING";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcConstructionEquipmentResourceTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 0)
		return "AGGREGATES";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 1)
		return "CONCRETE";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 2)
		return "DRYWALL";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 3)
		return "FUEL";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 4)
		return "GYPSUM";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 5)
		return "MASONRY";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 6)
		return "METAL";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 7)
		return "PLASTIC";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 8)
		return "WOOD";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcConstructionMaterialResourceTypeEnumEnum" && value == 10)
		return "USERDEFINED";

	if(name == "IfcConstructionProductResourceTypeEnumEnum" && value == 0)
		return "ASSEMBLY";

	if(name == "IfcConstructionProductResourceTypeEnumEnum" && value == 1)
		return "FORMWORK";

	if(name == "IfcConstructionProductResourceTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcConstructionProductResourceTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcControllerTypeEnumEnum" && value == 0)
		return "FLOATING";

	if(name == "IfcControllerTypeEnumEnum" && value == 1)
		return "PROGRAMMABLE";

	if(name == "IfcControllerTypeEnumEnum" && value == 2)
		return "PROPORTIONAL";

	if(name == "IfcControllerTypeEnumEnum" && value == 3)
		return "MULTIPOSITION";

	if(name == "IfcControllerTypeEnumEnum" && value == 4)
		return "TWOPOSITION";

	if(name == "IfcControllerTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcControllerTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcCooledBeamTypeEnumEnum" && value == 0)
		return "ACTIVE";

	if(name == "IfcCooledBeamTypeEnumEnum" && value == 1)
		return "PASSIVE";

	if(name == "IfcCooledBeamTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcCooledBeamTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcCoolingTowerTypeEnumEnum" && value == 0)
		return "NATURALDRAFT";

	if(name == "IfcCoolingTowerTypeEnumEnum" && value == 1)
		return "MECHANICALINDUCEDDRAFT";

	if(name == "IfcCoolingTowerTypeEnumEnum" && value == 2)
		return "MECHANICALFORCEDDRAFT";

	if(name == "IfcCoolingTowerTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcCoolingTowerTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcCostItemTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcCostItemTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 0)
		return "BUDGET";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 1)
		return "COSTPLAN";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 2)
		return "ESTIMATE";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 3)
		return "TENDER";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 4)
		return "PRICEDBILLOFQUANTITIES";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 5)
		return "UNPRICEDBILLOFQUANTITIES";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 6)
		return "SCHEDULEOFRATES";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcCostScheduleTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcCoveringTypeEnumEnum" && value == 0)
		return "CEILING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 1)
		return "FLOORING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 2)
		return "CLADDING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 3)
		return "ROOFING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 4)
		return "MOLDING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 5)
		return "SKIRTINGBOARD";

	if(name == "IfcCoveringTypeEnumEnum" && value == 6)
		return "INSULATION";

	if(name == "IfcCoveringTypeEnumEnum" && value == 7)
		return "MEMBRANE";

	if(name == "IfcCoveringTypeEnumEnum" && value == 8)
		return "SLEEVING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 9)
		return "WRAPPING";

	if(name == "IfcCoveringTypeEnumEnum" && value == 10)
		return "USERDEFINED";

	if(name == "IfcCoveringTypeEnumEnum" && value == 11)
		return "NOTDEFINED";

	if(name == "IfcCrewResourceTypeEnumEnum" && value == 0)
		return "OFFICE";

	if(name == "IfcCrewResourceTypeEnumEnum" && value == 1)
		return "SITE";

	if(name == "IfcCrewResourceTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcCrewResourceTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcCurtainWallTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcCurtainWallTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcCurveInterpolationEnumEnum" && value == 0)
		return "LINEAR";

	if(name == "IfcCurveInterpolationEnumEnum" && value == 1)
		return "LOG_LINEAR";

	if(name == "IfcCurveInterpolationEnumEnum" && value == 2)
		return "LOG_LOG";

	if(name == "IfcCurveInterpolationEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcDamperTypeEnumEnum" && value == 0)
		return "BACKDRAFTDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 1)
		return "BALANCINGDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 2)
		return "BLASTDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 3)
		return "CONTROLDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 4)
		return "FIREDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 5)
		return "FIRESMOKEDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 6)
		return "FUMEHOODEXHAUST";

	if(name == "IfcDamperTypeEnumEnum" && value == 7)
		return "GRAVITYDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 8)
		return "GRAVITYRELIEFDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 9)
		return "RELIEFDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 10)
		return "SMOKEDAMPER";

	if(name == "IfcDamperTypeEnumEnum" && value == 11)
		return "USERDEFINED";

	if(name == "IfcDamperTypeEnumEnum" && value == 12)
		return "NOTDEFINED";

	if(name == "IfcDataOriginEnumEnum" && value == 0)
		return "MEASURED";

	if(name == "IfcDataOriginEnumEnum" && value == 1)
		return "PREDICTED";

	if(name == "IfcDataOriginEnumEnum" && value == 2)
		return "SIMULATED";

	if(name == "IfcDataOriginEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcDataOriginEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcDerivedUnitEnumEnum" && value == 0)
		return "ANGULARVELOCITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 1)
		return "AREADENSITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 2)
		return "COMPOUNDPLANEANGLEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 3)
		return "DYNAMICVISCOSITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 4)
		return "HEATFLUXDENSITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 5)
		return "INTEGERCOUNTRATEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 6)
		return "ISOTHERMALMOISTURECAPACITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 7)
		return "KINEMATICVISCOSITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 8)
		return "LINEARVELOCITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 9)
		return "MASSDENSITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 10)
		return "MASSFLOWRATEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 11)
		return "MOISTUREDIFFUSIVITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 12)
		return "MOLECULARWEIGHTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 13)
		return "SPECIFICHEATCAPACITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 14)
		return "THERMALADMITTANCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 15)
		return "THERMALCONDUCTANCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 16)
		return "THERMALRESISTANCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 17)
		return "THERMALTRANSMITTANCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 18)
		return "VAPORPERMEABILITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 19)
		return "VOLUMETRICFLOWRATEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 20)
		return "ROTATIONALFREQUENCYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 21)
		return "TORQUEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 22)
		return "MOMENTOFINERTIAUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 23)
		return "LINEARMOMENTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 24)
		return "LINEARFORCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 25)
		return "PLANARFORCEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 26)
		return "MODULUSOFELASTICITYUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 27)
		return "SHEARMODULUSUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 28)
		return "LINEARSTIFFNESSUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 29)
		return "ROTATIONALSTIFFNESSUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 30)
		return "MODULUSOFSUBGRADEREACTIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 31)
		return "ACCELERATIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 32)
		return "CURVATUREUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 33)
		return "HEATINGVALUEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 34)
		return "IONCONCENTRATIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 35)
		return "LUMINOUSINTENSITYDISTRIBUTIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 36)
		return "MASSPERLENGTHUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 37)
		return "MODULUSOFLINEARSUBGRADEREACTIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 38)
		return "MODULUSOFROTATIONALSUBGRADEREACTIONUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 39)
		return "PHUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 40)
		return "ROTATIONALMASSUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 41)
		return "SECTIONAREAINTEGRALUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 42)
		return "SECTIONMODULUSUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 43)
		return "SOUNDPOWERLEVELUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 44)
		return "SOUNDPOWERUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 45)
		return "SOUNDPRESSURELEVELUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 46)
		return "SOUNDPRESSUREUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 47)
		return "TEMPERATUREGRADIENTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 48)
		return "TEMPERATURERATEOFCHANGEUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 49)
		return "THERMALEXPANSIONCOEFFICIENTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 50)
		return "WARPINGCONSTANTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 51)
		return "WARPINGMOMENTUNIT";

	if(name == "IfcDerivedUnitEnumEnum" && value == 52)
		return "USERDEFINED";

	if(name == "IfcDirectionSenseEnumEnum" && value == 0)
		return "POSITIVE";

	if(name == "IfcDirectionSenseEnumEnum" && value == 1)
		return "NEGATIVE";

	if(name == "IfcDiscreteAccessoryTypeEnumEnum" && value == 0)
		return "ANCHORPLATE";

	if(name == "IfcDiscreteAccessoryTypeEnumEnum" && value == 1)
		return "BRACKET";

	if(name == "IfcDiscreteAccessoryTypeEnumEnum" && value == 2)
		return "SHOE";

	if(name == "IfcDiscreteAccessoryTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcDiscreteAccessoryTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 0)
		return "FORMEDDUCT";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 1)
		return "INSPECTIONCHAMBER";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 2)
		return "INSPECTIONPIT";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 3)
		return "MANHOLE";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 4)
		return "METERCHAMBER";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 5)
		return "SUMP";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 6)
		return "TRENCH";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 7)
		return "VALVECHAMBER";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcDistributionChamberElementTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 0)
		return "CABLE";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 1)
		return "CABLECARRIER";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 2)
		return "DUCT";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 3)
		return "PIPE";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcDistributionPortTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcDistributionSystemEnumEnum" && value == 0)
		return "AIRCONDITIONING";

	if(name == "IfcDistributionSystemEnumEnum" && value == 1)
		return "AUDIOVISUAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 2)
		return "CHEMICAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 3)
		return "CHILLEDWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 4)
		return "COMMUNICATION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 5)
		return "COMPRESSEDAIR";

	if(name == "IfcDistributionSystemEnumEnum" && value == 6)
		return "CONDENSERWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 7)
		return "CONTROL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 8)
		return "CONVEYING";

	if(name == "IfcDistributionSystemEnumEnum" && value == 9)
		return "DATA";

	if(name == "IfcDistributionSystemEnumEnum" && value == 10)
		return "DISPOSAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 11)
		return "DOMESTICCOLDWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 12)
		return "DOMESTICHOTWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 13)
		return "DRAINAGE";

	if(name == "IfcDistributionSystemEnumEnum" && value == 14)
		return "EARTHING";

	if(name == "IfcDistributionSystemEnumEnum" && value == 15)
		return "ELECTRICAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 16)
		return "ELECTROACOUSTIC";

	if(name == "IfcDistributionSystemEnumEnum" && value == 17)
		return "EXHAUST";

	if(name == "IfcDistributionSystemEnumEnum" && value == 18)
		return "FIREPROTECTION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 19)
		return "FUEL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 20)
		return "GAS";

	if(name == "IfcDistributionSystemEnumEnum" && value == 21)
		return "HAZARDOUS";

	if(name == "IfcDistributionSystemEnumEnum" && value == 22)
		return "HEATING";

	if(name == "IfcDistributionSystemEnumEnum" && value == 23)
		return "LIGHTING";

	if(name == "IfcDistributionSystemEnumEnum" && value == 24)
		return "LIGHTNINGPROTECTION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 25)
		return "MUNICIPALSOLIDWASTE";

	if(name == "IfcDistributionSystemEnumEnum" && value == 26)
		return "OIL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 27)
		return "OPERATIONAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 28)
		return "POWERGENERATION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 29)
		return "RAINWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 30)
		return "REFRIGERATION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 31)
		return "SECURITY";

	if(name == "IfcDistributionSystemEnumEnum" && value == 32)
		return "SEWAGE";

	if(name == "IfcDistributionSystemEnumEnum" && value == 33)
		return "SIGNAL";

	if(name == "IfcDistributionSystemEnumEnum" && value == 34)
		return "STORMWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 35)
		return "TELEPHONE";

	if(name == "IfcDistributionSystemEnumEnum" && value == 36)
		return "TV";

	if(name == "IfcDistributionSystemEnumEnum" && value == 37)
		return "VACUUM";

	if(name == "IfcDistributionSystemEnumEnum" && value == 38)
		return "VENT";

	if(name == "IfcDistributionSystemEnumEnum" && value == 39)
		return "VENTILATION";

	if(name == "IfcDistributionSystemEnumEnum" && value == 40)
		return "WASTEWATER";

	if(name == "IfcDistributionSystemEnumEnum" && value == 41)
		return "WATERSUPPLY";

	if(name == "IfcDistributionSystemEnumEnum" && value == 42)
		return "USERDEFINED";

	if(name == "IfcDistributionSystemEnumEnum" && value == 43)
		return "NOTDEFINED";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 0)
		return "PUBLIC";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 1)
		return "RESTRICTED";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 2)
		return "CONFIDENTIAL";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 3)
		return "PERSONAL";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcDocumentConfidentialityEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcDocumentStatusEnumEnum" && value == 0)
		return "DRAFT";

	if(name == "IfcDocumentStatusEnumEnum" && value == 1)
		return "FINALDRAFT";

	if(name == "IfcDocumentStatusEnumEnum" && value == 2)
		return "FINAL";

	if(name == "IfcDocumentStatusEnumEnum" && value == 3)
		return "REVISION";

	if(name == "IfcDocumentStatusEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 0)
		return "SWINGING";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 1)
		return "DOUBLE_ACTING";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 2)
		return "SLIDING";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 3)
		return "FOLDING";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 4)
		return "REVOLVING";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 5)
		return "ROLLINGUP";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 6)
		return "FIXEDPANEL";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcDoorPanelOperationEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcDoorPanelPositionEnumEnum" && value == 0)
		return "LEFT";

	if(name == "IfcDoorPanelPositionEnumEnum" && value == 1)
		return "MIDDLE";

	if(name == "IfcDoorPanelPositionEnumEnum" && value == 2)
		return "RIGHT";

	if(name == "IfcDoorPanelPositionEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 0)
		return "ALUMINIUM";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 1)
		return "HIGH_GRADE_STEEL";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 2)
		return "STEEL";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 3)
		return "WOOD";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 4)
		return "ALUMINIUM_WOOD";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 5)
		return "ALUMINIUM_PLASTIC";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 6)
		return "PLASTIC";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcDoorStyleConstructionEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 0)
		return "SINGLE_SWING_LEFT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 1)
		return "SINGLE_SWING_RIGHT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 2)
		return "DOUBLE_DOOR_SINGLE_SWING";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 3)
		return "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 4)
		return "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 5)
		return "DOUBLE_SWING_LEFT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 6)
		return "DOUBLE_SWING_RIGHT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 7)
		return "DOUBLE_DOOR_DOUBLE_SWING";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 8)
		return "SLIDING_TO_LEFT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 9)
		return "SLIDING_TO_RIGHT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 10)
		return "DOUBLE_DOOR_SLIDING";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 11)
		return "FOLDING_TO_LEFT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 12)
		return "FOLDING_TO_RIGHT";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 13)
		return "DOUBLE_DOOR_FOLDING";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 14)
		return "REVOLVING";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 15)
		return "ROLLINGUP";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 16)
		return "USERDEFINED";

	if(name == "IfcDoorStyleOperationEnumEnum" && value == 17)
		return "NOTDEFINED";

	if(name == "IfcDoorTypeEnumEnum" && value == 0)
		return "DOOR";

	if(name == "IfcDoorTypeEnumEnum" && value == 1)
		return "GATE";

	if(name == "IfcDoorTypeEnumEnum" && value == 2)
		return "TRAPDOOR";

	if(name == "IfcDoorTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcDoorTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 0)
		return "SINGLE_SWING_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 1)
		return "SINGLE_SWING_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 2)
		return "DOUBLE_DOOR_SINGLE_SWING";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 3)
		return "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 4)
		return "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 5)
		return "DOUBLE_SWING_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 6)
		return "DOUBLE_SWING_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 7)
		return "DOUBLE_DOOR_DOUBLE_SWING";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 8)
		return "SLIDING_TO_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 9)
		return "SLIDING_TO_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 10)
		return "DOUBLE_DOOR_SLIDING";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 11)
		return "FOLDING_TO_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 12)
		return "FOLDING_TO_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 13)
		return "DOUBLE_DOOR_FOLDING";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 14)
		return "REVOLVING";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 15)
		return "ROLLINGUP";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 16)
		return "SWING_FIXED_LEFT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 17)
		return "SWING_FIXED_RIGHT";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 18)
		return "USERDEFINED";

	if(name == "IfcDoorTypeOperationEnumEnum" && value == 19)
		return "NOTDEFINED";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 0)
		return "BEND";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 1)
		return "CONNECTOR";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 2)
		return "ENTRY";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 3)
		return "EXIT";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 4)
		return "JUNCTION";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 5)
		return "OBSTRUCTION";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 6)
		return "TRANSITION";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcDuctFittingTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcDuctSegmentTypeEnumEnum" && value == 0)
		return "RIGIDSEGMENT";

	if(name == "IfcDuctSegmentTypeEnumEnum" && value == 1)
		return "FLEXIBLESEGMENT";

	if(name == "IfcDuctSegmentTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcDuctSegmentTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcDuctSilencerTypeEnumEnum" && value == 0)
		return "FLATOVAL";

	if(name == "IfcDuctSilencerTypeEnumEnum" && value == 1)
		return "RECTANGULAR";

	if(name == "IfcDuctSilencerTypeEnumEnum" && value == 2)
		return "ROUND";

	if(name == "IfcDuctSilencerTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcDuctSilencerTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 0)
		return "DISHWASHER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 1)
		return "ELECTRICCOOKER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 2)
		return "FREESTANDINGELECTRICHEATER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 3)
		return "FREESTANDINGFAN";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 4)
		return "FREESTANDINGWATERHEATER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 5)
		return "FREESTANDINGWATERCOOLER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 6)
		return "FREEZER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 7)
		return "FRIDGE_FREEZER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 8)
		return "HANDDRYER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 9)
		return "KITCHENMACHINE";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 10)
		return "MICROWAVE";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 11)
		return "PHOTOCOPIER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 12)
		return "REFRIGERATOR";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 13)
		return "TUMBLEDRYER";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 14)
		return "VENDINGMACHINE";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 15)
		return "WASHINGMACHINE";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 16)
		return "USERDEFINED";

	if(name == "IfcElectricApplianceTypeEnumEnum" && value == 17)
		return "NOTDEFINED";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 0)
		return "CONSUMERUNIT";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 1)
		return "DISTRIBUTIONBOARD";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 2)
		return "MOTORCONTROLCENTRE";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 3)
		return "SWITCHBOARD";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcElectricDistributionBoardTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 0)
		return "BATTERY";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 1)
		return "CAPACITORBANK";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 2)
		return "HARMONICFILTER";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 3)
		return "INDUCTORBANK";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 4)
		return "UPS";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcElectricFlowStorageDeviceTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcElectricGeneratorTypeEnumEnum" && value == 0)
		return "CHP";

	if(name == "IfcElectricGeneratorTypeEnumEnum" && value == 1)
		return "ENGINEGENERATOR";

	if(name == "IfcElectricGeneratorTypeEnumEnum" && value == 2)
		return "STANDALONE";

	if(name == "IfcElectricGeneratorTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcElectricGeneratorTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 0)
		return "DC";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 1)
		return "INDUCTION";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 2)
		return "POLYPHASE";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 3)
		return "RELUCTANCESYNCHRONOUS";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 4)
		return "SYNCHRONOUS";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcElectricMotorTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcElectricTimeControlTypeEnumEnum" && value == 0)
		return "TIMECLOCK";

	if(name == "IfcElectricTimeControlTypeEnumEnum" && value == 1)
		return "TIMEDELAY";

	if(name == "IfcElectricTimeControlTypeEnumEnum" && value == 2)
		return "RELAY";

	if(name == "IfcElectricTimeControlTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcElectricTimeControlTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 0)
		return "ACCESSORY_ASSEMBLY";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 1)
		return "ARCH";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 2)
		return "BEAM_GRID";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 3)
		return "BRACED_FRAME";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 4)
		return "GIRDER";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 5)
		return "REINFORCEMENT_UNIT";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 6)
		return "RIGID_FRAME";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 7)
		return "SLAB_FIELD";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 8)
		return "TRUSS";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcElementAssemblyTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcElementCompositionEnumEnum" && value == 0)
		return "COMPLEX";

	if(name == "IfcElementCompositionEnumEnum" && value == 1)
		return "ELEMENT";

	if(name == "IfcElementCompositionEnumEnum" && value == 2)
		return "PARTIAL";

	if(name == "IfcEngineTypeEnumEnum" && value == 0)
		return "EXTERNALCOMBUSTION";

	if(name == "IfcEngineTypeEnumEnum" && value == 1)
		return "INTERNALCOMBUSTION";

	if(name == "IfcEngineTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcEngineTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 0)
		return "DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 1)
		return "DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 2)
		return "DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 3)
		return "DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 4)
		return "DIRECTEVAPORATIVEAIRWASHER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 5)
		return "INDIRECTEVAPORATIVEPACKAGEAIRCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 6)
		return "INDIRECTEVAPORATIVEWETCOIL";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 7)
		return "INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 8)
		return "INDIRECTDIRECTCOMBINATION";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcEvaporativeCoolerTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 0)
		return "DIRECTEXPANSION";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 1)
		return "DIRECTEXPANSIONSHELLANDTUBE";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 2)
		return "DIRECTEXPANSIONTUBEINTUBE";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 3)
		return "DIRECTEXPANSIONBRAZEDPLATE";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 4)
		return "FLOODEDSHELLANDTUBE";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 5)
		return "SHELLANDCOIL";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcEvaporatorTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 0)
		return "EVENTRULE";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 1)
		return "EVENTMESSAGE";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 2)
		return "EVENTTIME";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 3)
		return "EVENTCOMPLEX";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcEventTriggerTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcEventTypeEnumEnum" && value == 0)
		return "STARTEVENT";

	if(name == "IfcEventTypeEnumEnum" && value == 1)
		return "ENDEVENT";

	if(name == "IfcEventTypeEnumEnum" && value == 2)
		return "INTERMEDIATEEVENT";

	if(name == "IfcEventTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcEventTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 0)
		return "EXTERNAL";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 1)
		return "EXTERNAL_EARTH";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 2)
		return "EXTERNAL_WATER";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 3)
		return "EXTERNAL_FIRE";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcExternalSpatialElementTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcFanTypeEnumEnum" && value == 0)
		return "CENTRIFUGALFORWARDCURVED";

	if(name == "IfcFanTypeEnumEnum" && value == 1)
		return "CENTRIFUGALRADIAL";

	if(name == "IfcFanTypeEnumEnum" && value == 2)
		return "CENTRIFUGALBACKWARDINCLINEDCURVED";

	if(name == "IfcFanTypeEnumEnum" && value == 3)
		return "CENTRIFUGALAIRFOIL";

	if(name == "IfcFanTypeEnumEnum" && value == 4)
		return "TUBEAXIAL";

	if(name == "IfcFanTypeEnumEnum" && value == 5)
		return "VANEAXIAL";

	if(name == "IfcFanTypeEnumEnum" && value == 6)
		return "PROPELLORAXIAL";

	if(name == "IfcFanTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcFanTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcFastenerTypeEnumEnum" && value == 0)
		return "GLUE";

	if(name == "IfcFastenerTypeEnumEnum" && value == 1)
		return "MORTAR";

	if(name == "IfcFastenerTypeEnumEnum" && value == 2)
		return "WELD";

	if(name == "IfcFastenerTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcFastenerTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcFilterTypeEnumEnum" && value == 0)
		return "AIRPARTICLEFILTER";

	if(name == "IfcFilterTypeEnumEnum" && value == 1)
		return "COMPRESSEDAIRFILTER";

	if(name == "IfcFilterTypeEnumEnum" && value == 2)
		return "ODORFILTER";

	if(name == "IfcFilterTypeEnumEnum" && value == 3)
		return "OILFILTER";

	if(name == "IfcFilterTypeEnumEnum" && value == 4)
		return "STRAINER";

	if(name == "IfcFilterTypeEnumEnum" && value == 5)
		return "WATERFILTER";

	if(name == "IfcFilterTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcFilterTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 0)
		return "BREECHINGINLET";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 1)
		return "FIREHYDRANT";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 2)
		return "HOSEREEL";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 3)
		return "SPRINKLER";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 4)
		return "SPRINKLERDEFLECTOR";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcFireSuppressionTerminalTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcFlowDirectionEnumEnum" && value == 0)
		return "SOURCE";

	if(name == "IfcFlowDirectionEnumEnum" && value == 1)
		return "SINK";

	if(name == "IfcFlowDirectionEnumEnum" && value == 2)
		return "SOURCEANDSINK";

	if(name == "IfcFlowDirectionEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 0)
		return "PRESSUREGAUGE";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 1)
		return "THERMOMETER";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 2)
		return "AMMETER";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 3)
		return "FREQUENCYMETER";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 4)
		return "POWERFACTORMETER";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 5)
		return "PHASEANGLEMETER";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 6)
		return "VOLTMETER_PEAK";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 7)
		return "VOLTMETER_RMS";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcFlowInstrumentTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 0)
		return "ENERGYMETER";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 1)
		return "GASMETER";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 2)
		return "OILMETER";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 3)
		return "WATERMETER";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcFlowMeterTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcFootingTypeEnumEnum" && value == 0)
		return "CAISSON_FOUNDATION";

	if(name == "IfcFootingTypeEnumEnum" && value == 1)
		return "FOOTING_BEAM";

	if(name == "IfcFootingTypeEnumEnum" && value == 2)
		return "PAD_FOOTING";

	if(name == "IfcFootingTypeEnumEnum" && value == 3)
		return "PILE_CAP";

	if(name == "IfcFootingTypeEnumEnum" && value == 4)
		return "STRIP_FOOTING";

	if(name == "IfcFootingTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcFootingTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 0)
		return "CHAIR";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 1)
		return "TABLE";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 2)
		return "DESK";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 3)
		return "BED";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 4)
		return "FILECABINET";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 5)
		return "SHELF";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 6)
		return "SOFA";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcFurnitureTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcGeographicElementTypeEnumEnum" && value == 0)
		return "TERRAIN";

	if(name == "IfcGeographicElementTypeEnumEnum" && value == 1)
		return "USERDEFINED";

	if(name == "IfcGeographicElementTypeEnumEnum" && value == 2)
		return "NOTDEFINED";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 0)
		return "GRAPH_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 1)
		return "SKETCH_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 2)
		return "MODEL_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 3)
		return "PLAN_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 4)
		return "REFLECTED_PLAN_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 5)
		return "SECTION_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 6)
		return "ELEVATION_VIEW";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcGeometricProjectionEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcGlobalOrLocalEnumEnum" && value == 0)
		return "GLOBAL_COORDS";

	if(name == "IfcGlobalOrLocalEnumEnum" && value == 1)
		return "LOCAL_COORDS";

	if(name == "IfcGridTypeEnumEnum" && value == 0)
		return "RECTANGULAR";

	if(name == "IfcGridTypeEnumEnum" && value == 1)
		return "RADIAL";

	if(name == "IfcGridTypeEnumEnum" && value == 2)
		return "TRIANGULAR";

	if(name == "IfcGridTypeEnumEnum" && value == 3)
		return "IRREGULAR";

	if(name == "IfcGridTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcGridTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcHeatExchangerTypeEnumEnum" && value == 0)
		return "PLATE";

	if(name == "IfcHeatExchangerTypeEnumEnum" && value == 1)
		return "SHELLANDTUBE";

	if(name == "IfcHeatExchangerTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcHeatExchangerTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 0)
		return "STEAMINJECTION";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 1)
		return "ADIABATICAIRWASHER";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 2)
		return "ADIABATICPAN";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 3)
		return "ADIABATICWETTEDELEMENT";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 4)
		return "ADIABATICATOMIZING";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 5)
		return "ADIABATICULTRASONIC";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 6)
		return "ADIABATICRIGIDMEDIA";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 7)
		return "ADIABATICCOMPRESSEDAIRNOZZLE";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 8)
		return "ASSISTEDELECTRIC";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 9)
		return "ASSISTEDNATURALGAS";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 10)
		return "ASSISTEDPROPANE";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 11)
		return "ASSISTEDBUTANE";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 12)
		return "ASSISTEDSTEAM";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 13)
		return "USERDEFINED";

	if(name == "IfcHumidifierTypeEnumEnum" && value == 14)
		return "NOTDEFINED";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 0)
		return "CYCLONIC";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 1)
		return "GREASE";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 2)
		return "OIL";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 3)
		return "PETROL";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcInterceptorTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 0)
		return "INTERNAL";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 1)
		return "EXTERNAL";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 2)
		return "EXTERNAL_EARTH";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 3)
		return "EXTERNAL_WATER";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 4)
		return "EXTERNAL_FIRE";

	if(name == "IfcInternalOrExternalEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcInventoryTypeEnumEnum" && value == 0)
		return "ASSETINVENTORY";

	if(name == "IfcInventoryTypeEnumEnum" && value == 1)
		return "SPACEINVENTORY";

	if(name == "IfcInventoryTypeEnumEnum" && value == 2)
		return "FURNITUREINVENTORY";

	if(name == "IfcInventoryTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcInventoryTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcJunctionBoxTypeEnumEnum" && value == 0)
		return "DATA";

	if(name == "IfcJunctionBoxTypeEnumEnum" && value == 1)
		return "POWER";

	if(name == "IfcJunctionBoxTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcJunctionBoxTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcKnotTypeEnum" && value == 0)
		return "UNIFORM_KNOTS";

	if(name == "IfcKnotTypeEnum" && value == 1)
		return "QUASI_UNIFORM_KNOTS";

	if(name == "IfcKnotTypeEnum" && value == 2)
		return "PIECEWISE_BEZIER_KNOTS";

	if(name == "IfcKnotTypeEnum" && value == 3)
		return "UNSPECIFIED";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 0)
		return "ADMINISTRATION";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 1)
		return "CARPENTRY";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 2)
		return "CLEANING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 3)
		return "CONCRETE";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 4)
		return "DRYWALL";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 5)
		return "ELECTRIC";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 6)
		return "FINISHING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 7)
		return "FLOORING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 8)
		return "GENERAL";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 9)
		return "HVAC";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 10)
		return "LANDSCAPING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 11)
		return "MASONRY";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 12)
		return "PAINTING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 13)
		return "PAVING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 14)
		return "PLUMBING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 15)
		return "ROOFING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 16)
		return "SITEGRADING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 17)
		return "STEELWORK";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 18)
		return "SURVEYING";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 19)
		return "USERDEFINED";

	if(name == "IfcLaborResourceTypeEnumEnum" && value == 20)
		return "NOTDEFINED";

	if(name == "IfcLampTypeEnumEnum" && value == 0)
		return "COMPACTFLUORESCENT";

	if(name == "IfcLampTypeEnumEnum" && value == 1)
		return "FLUORESCENT";

	if(name == "IfcLampTypeEnumEnum" && value == 2)
		return "HALOGEN";

	if(name == "IfcLampTypeEnumEnum" && value == 3)
		return "HIGHPRESSUREMERCURY";

	if(name == "IfcLampTypeEnumEnum" && value == 4)
		return "HIGHPRESSURESODIUM";

	if(name == "IfcLampTypeEnumEnum" && value == 5)
		return "LED";

	if(name == "IfcLampTypeEnumEnum" && value == 6)
		return "METALHALIDE";

	if(name == "IfcLampTypeEnumEnum" && value == 7)
		return "OLED";

	if(name == "IfcLampTypeEnumEnum" && value == 8)
		return "TUNGSTENFILAMENT";

	if(name == "IfcLampTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcLampTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcLayerSetDirectionEnumEnum" && value == 0)
		return "AXIS1";

	if(name == "IfcLayerSetDirectionEnumEnum" && value == 1)
		return "AXIS2";

	if(name == "IfcLayerSetDirectionEnumEnum" && value == 2)
		return "AXIS3";

	if(name == "IfcLightDistributionCurveEnumEnum" && value == 0)
		return "TYPE_A";

	if(name == "IfcLightDistributionCurveEnumEnum" && value == 1)
		return "TYPE_B";

	if(name == "IfcLightDistributionCurveEnumEnum" && value == 2)
		return "TYPE_C";

	if(name == "IfcLightDistributionCurveEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 0)
		return "COMPACTFLUORESCENT";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 1)
		return "FLUORESCENT";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 2)
		return "HIGHPRESSUREMERCURY";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 3)
		return "HIGHPRESSURESODIUM";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 4)
		return "LIGHTEMITTINGDIODE";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 5)
		return "LOWPRESSURESODIUM";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 6)
		return "LOWVOLTAGEHALOGEN";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 7)
		return "MAINVOLTAGEHALOGEN";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 8)
		return "METALHALIDE";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 9)
		return "TUNGSTENFILAMENT";

	if(name == "IfcLightEmissionSourceEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcLightFixtureTypeEnumEnum" && value == 0)
		return "POINTSOURCE";

	if(name == "IfcLightFixtureTypeEnumEnum" && value == 1)
		return "DIRECTIONSOURCE";

	if(name == "IfcLightFixtureTypeEnumEnum" && value == 2)
		return "SECURITYLIGHTING";

	if(name == "IfcLightFixtureTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcLightFixtureTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcLoadGroupTypeEnumEnum" && value == 0)
		return "LOAD_GROUP";

	if(name == "IfcLoadGroupTypeEnumEnum" && value == 1)
		return "LOAD_CASE";

	if(name == "IfcLoadGroupTypeEnumEnum" && value == 2)
		return "LOAD_COMBINATION";

	if(name == "IfcLoadGroupTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcLoadGroupTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcLogicalOperatorEnumEnum" && value == 0)
		return "LOGICALAND";

	if(name == "IfcLogicalOperatorEnumEnum" && value == 1)
		return "LOGICALOR";

	if(name == "IfcLogicalOperatorEnumEnum" && value == 2)
		return "LOGICALXOR";

	if(name == "IfcLogicalOperatorEnumEnum" && value == 3)
		return "LOGICALNOTAND";

	if(name == "IfcLogicalOperatorEnumEnum" && value == 4)
		return "LOGICALNOTOR";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 0)
		return "ANCHORBOLT";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 1)
		return "BOLT";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 2)
		return "DOWEL";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 3)
		return "NAIL";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 4)
		return "NAILPLATE";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 5)
		return "RIVET";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 6)
		return "SCREW";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 7)
		return "SHEARCONNECTOR";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 8)
		return "STAPLE";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 9)
		return "STUDSHEARCONNECTOR";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 10)
		return "USERDEFINED";

	if(name == "IfcMechanicalFastenerTypeEnumEnum" && value == 11)
		return "NOTDEFINED";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 0)
		return "AIRSTATION";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 1)
		return "FEEDAIRUNIT";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 2)
		return "OXYGENGENERATOR";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 3)
		return "OXYGENPLANT";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 4)
		return "VACUUMSTATION";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcMedicalDeviceTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcMemberTypeEnumEnum" && value == 0)
		return "BRACE";

	if(name == "IfcMemberTypeEnumEnum" && value == 1)
		return "CHORD";

	if(name == "IfcMemberTypeEnumEnum" && value == 2)
		return "COLLAR";

	if(name == "IfcMemberTypeEnumEnum" && value == 3)
		return "MEMBER";

	if(name == "IfcMemberTypeEnumEnum" && value == 4)
		return "MULLION";

	if(name == "IfcMemberTypeEnumEnum" && value == 5)
		return "PLATE";

	if(name == "IfcMemberTypeEnumEnum" && value == 6)
		return "POST";

	if(name == "IfcMemberTypeEnumEnum" && value == 7)
		return "PURLIN";

	if(name == "IfcMemberTypeEnumEnum" && value == 8)
		return "RAFTER";

	if(name == "IfcMemberTypeEnumEnum" && value == 9)
		return "STRINGER";

	if(name == "IfcMemberTypeEnumEnum" && value == 10)
		return "STRUT";

	if(name == "IfcMemberTypeEnumEnum" && value == 11)
		return "STUD";

	if(name == "IfcMemberTypeEnumEnum" && value == 12)
		return "USERDEFINED";

	if(name == "IfcMemberTypeEnumEnum" && value == 13)
		return "NOTDEFINED";

	if(name == "IfcMotorConnectionTypeEnumEnum" && value == 0)
		return "BELTDRIVE";

	if(name == "IfcMotorConnectionTypeEnumEnum" && value == 1)
		return "COUPLING";

	if(name == "IfcMotorConnectionTypeEnumEnum" && value == 2)
		return "DIRECTDRIVE";

	if(name == "IfcMotorConnectionTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcMotorConnectionTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcNullStyleEnum" && value == 0)
		return "NULL";

	if(name == "IfcObjectiveEnumEnum" && value == 0)
		return "CODECOMPLIANCE";

	if(name == "IfcObjectiveEnumEnum" && value == 1)
		return "CODEWAIVER";

	if(name == "IfcObjectiveEnumEnum" && value == 2)
		return "DESIGNINTENT";

	if(name == "IfcObjectiveEnumEnum" && value == 3)
		return "EXTERNAL";

	if(name == "IfcObjectiveEnumEnum" && value == 4)
		return "HEALTHANDSAFETY";

	if(name == "IfcObjectiveEnumEnum" && value == 5)
		return "MERGECONFLICT";

	if(name == "IfcObjectiveEnumEnum" && value == 6)
		return "MODELVIEW";

	if(name == "IfcObjectiveEnumEnum" && value == 7)
		return "PARAMETER";

	if(name == "IfcObjectiveEnumEnum" && value == 8)
		return "REQUIREMENT";

	if(name == "IfcObjectiveEnumEnum" && value == 9)
		return "SPECIFICATION";

	if(name == "IfcObjectiveEnumEnum" && value == 10)
		return "TRIGGERCONDITION";

	if(name == "IfcObjectiveEnumEnum" && value == 11)
		return "USERDEFINED";

	if(name == "IfcObjectiveEnumEnum" && value == 12)
		return "NOTDEFINED";

	if(name == "IfcObjectTypeEnumEnum" && value == 0)
		return "PRODUCT";

	if(name == "IfcObjectTypeEnumEnum" && value == 1)
		return "PROCESS";

	if(name == "IfcObjectTypeEnumEnum" && value == 2)
		return "CONTROL";

	if(name == "IfcObjectTypeEnumEnum" && value == 3)
		return "RESOURCE";

	if(name == "IfcObjectTypeEnumEnum" && value == 4)
		return "ACTOR";

	if(name == "IfcObjectTypeEnumEnum" && value == 5)
		return "GROUP";

	if(name == "IfcObjectTypeEnumEnum" && value == 6)
		return "PROJECT";

	if(name == "IfcObjectTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcOccupantTypeEnumEnum" && value == 0)
		return "ASSIGNEE";

	if(name == "IfcOccupantTypeEnumEnum" && value == 1)
		return "ASSIGNOR";

	if(name == "IfcOccupantTypeEnumEnum" && value == 2)
		return "LESSEE";

	if(name == "IfcOccupantTypeEnumEnum" && value == 3)
		return "LESSOR";

	if(name == "IfcOccupantTypeEnumEnum" && value == 4)
		return "LETTINGAGENT";

	if(name == "IfcOccupantTypeEnumEnum" && value == 5)
		return "OWNER";

	if(name == "IfcOccupantTypeEnumEnum" && value == 6)
		return "TENANT";

	if(name == "IfcOccupantTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcOccupantTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcOpeningElementTypeEnumEnum" && value == 0)
		return "OPENING";

	if(name == "IfcOpeningElementTypeEnumEnum" && value == 1)
		return "RECESS";

	if(name == "IfcOpeningElementTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcOpeningElementTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcOutletTypeEnumEnum" && value == 0)
		return "AUDIOVISUALOUTLET";

	if(name == "IfcOutletTypeEnumEnum" && value == 1)
		return "COMMUNICATIONSOUTLET";

	if(name == "IfcOutletTypeEnumEnum" && value == 2)
		return "POWEROUTLET";

	if(name == "IfcOutletTypeEnumEnum" && value == 3)
		return "DATAOUTLET";

	if(name == "IfcOutletTypeEnumEnum" && value == 4)
		return "TELEPHONEOUTLET";

	if(name == "IfcOutletTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcOutletTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcPerformanceHistoryTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcPerformanceHistoryTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcPermeableCoveringOperationEnumEnum" && value == 0)
		return "GRILL";

	if(name == "IfcPermeableCoveringOperationEnumEnum" && value == 1)
		return "LOUVER";

	if(name == "IfcPermeableCoveringOperationEnumEnum" && value == 2)
		return "SCREEN";

	if(name == "IfcPermeableCoveringOperationEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcPermeableCoveringOperationEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcPermitTypeEnumEnum" && value == 0)
		return "ACCESS";

	if(name == "IfcPermitTypeEnumEnum" && value == 1)
		return "BUILDING";

	if(name == "IfcPermitTypeEnumEnum" && value == 2)
		return "WORK";

	if(name == "IfcPermitTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcPermitTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcPhysicalOrVirtualEnumEnum" && value == 0)
		return "PHYSICAL";

	if(name == "IfcPhysicalOrVirtualEnumEnum" && value == 1)
		return "VIRTUAL";

	if(name == "IfcPhysicalOrVirtualEnumEnum" && value == 2)
		return "NOTDEFINED";

	if(name == "IfcPileConstructionEnumEnum" && value == 0)
		return "CAST_IN_PLACE";

	if(name == "IfcPileConstructionEnumEnum" && value == 1)
		return "COMPOSITE";

	if(name == "IfcPileConstructionEnumEnum" && value == 2)
		return "PRECAST_CONCRETE";

	if(name == "IfcPileConstructionEnumEnum" && value == 3)
		return "PREFAB_STEEL";

	if(name == "IfcPileConstructionEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcPileConstructionEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcPileTypeEnumEnum" && value == 0)
		return "BORED";

	if(name == "IfcPileTypeEnumEnum" && value == 1)
		return "DRIVEN";

	if(name == "IfcPileTypeEnumEnum" && value == 2)
		return "JETGROUTING";

	if(name == "IfcPileTypeEnumEnum" && value == 3)
		return "COHESION";

	if(name == "IfcPileTypeEnumEnum" && value == 4)
		return "FRICTION";

	if(name == "IfcPileTypeEnumEnum" && value == 5)
		return "SUPPORT";

	if(name == "IfcPileTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcPileTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 0)
		return "BEND";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 1)
		return "CONNECTOR";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 2)
		return "ENTRY";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 3)
		return "EXIT";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 4)
		return "JUNCTION";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 5)
		return "OBSTRUCTION";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 6)
		return "TRANSITION";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcPipeFittingTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 0)
		return "CULVERT";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 1)
		return "FLEXIBLESEGMENT";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 2)
		return "RIGIDSEGMENT";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 3)
		return "GUTTER";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 4)
		return "SPOOL";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcPipeSegmentTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcPlateTypeEnumEnum" && value == 0)
		return "CURTAIN_PANEL";

	if(name == "IfcPlateTypeEnumEnum" && value == 1)
		return "SHEET";

	if(name == "IfcPlateTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcPlateTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcPreferredSurfaceCurveRepresentationEnum" && value == 0)
		return "CURVE3D";

	if(name == "IfcPreferredSurfaceCurveRepresentationEnum" && value == 1)
		return "PCURVE_S1";

	if(name == "IfcPreferredSurfaceCurveRepresentationEnum" && value == 2)
		return "PCURVE_S2";

	if(name == "IfcProcedureTypeEnumEnum" && value == 0)
		return "ADVICE_CAUTION";

	if(name == "IfcProcedureTypeEnumEnum" && value == 1)
		return "ADVICE_NOTE";

	if(name == "IfcProcedureTypeEnumEnum" && value == 2)
		return "ADVICE_WARNING";

	if(name == "IfcProcedureTypeEnumEnum" && value == 3)
		return "CALIBRATION";

	if(name == "IfcProcedureTypeEnumEnum" && value == 4)
		return "DIAGNOSTIC";

	if(name == "IfcProcedureTypeEnumEnum" && value == 5)
		return "SHUTDOWN";

	if(name == "IfcProcedureTypeEnumEnum" && value == 6)
		return "STARTUP";

	if(name == "IfcProcedureTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcProcedureTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcProfileTypeEnumEnum" && value == 0)
		return "CURVE";

	if(name == "IfcProfileTypeEnumEnum" && value == 1)
		return "AREA";

	if(name == "IfcProjectedOrTrueLengthEnumEnum" && value == 0)
		return "PROJECTED_LENGTH";

	if(name == "IfcProjectedOrTrueLengthEnumEnum" && value == 1)
		return "TRUE_LENGTH";

	if(name == "IfcProjectionElementTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcProjectionElementTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 0)
		return "CHANGEORDER";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 1)
		return "MAINTENANCEWORKORDER";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 2)
		return "MOVEORDER";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 3)
		return "PURCHASEORDER";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 4)
		return "WORKORDER";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcProjectOrderTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 0)
		return "PSET_TYPEDRIVENONLY";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 1)
		return "PSET_TYPEDRIVENOVERRIDE";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 2)
		return "PSET_OCCURRENCEDRIVEN";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 3)
		return "PSET_PERFORMANCEDRIVEN";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 4)
		return "QTO_TYPEDRIVENONLY";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 5)
		return "QTO_TYPEDRIVENOVERRIDE";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 6)
		return "QTO_OCCURRENCEDRIVEN";

	if(name == "IfcPropertySetTemplateTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 0)
		return "ELECTRONIC";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 1)
		return "ELECTROMAGNETIC";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 2)
		return "RESIDUALCURRENT";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 3)
		return "THERMAL";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcProtectiveDeviceTrippingUnitTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 0)
		return "CIRCUITBREAKER";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 1)
		return "EARTHLEAKAGECIRCUITBREAKER";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 2)
		return "EARTHINGSWITCH";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 3)
		return "FUSEDISCONNECTOR";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 4)
		return "RESIDUALCURRENTCIRCUITBREAKER";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 5)
		return "RESIDUALCURRENTSWITCH";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 6)
		return "VARISTOR";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcProtectiveDeviceTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcPumpTypeEnumEnum" && value == 0)
		return "CIRCULATOR";

	if(name == "IfcPumpTypeEnumEnum" && value == 1)
		return "ENDSUCTION";

	if(name == "IfcPumpTypeEnumEnum" && value == 2)
		return "SPLITCASE";

	if(name == "IfcPumpTypeEnumEnum" && value == 3)
		return "SUBMERSIBLEPUMP";

	if(name == "IfcPumpTypeEnumEnum" && value == 4)
		return "SUMPPUMP";

	if(name == "IfcPumpTypeEnumEnum" && value == 5)
		return "VERTICALINLINE";

	if(name == "IfcPumpTypeEnumEnum" && value == 6)
		return "VERTICALTURBINE";

	if(name == "IfcPumpTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcPumpTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcRailingTypeEnumEnum" && value == 0)
		return "HANDRAIL";

	if(name == "IfcRailingTypeEnumEnum" && value == 1)
		return "GUARDRAIL";

	if(name == "IfcRailingTypeEnumEnum" && value == 2)
		return "BALUSTRADE";

	if(name == "IfcRailingTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcRailingTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcRampFlightTypeEnumEnum" && value == 0)
		return "STRAIGHT";

	if(name == "IfcRampFlightTypeEnumEnum" && value == 1)
		return "SPIRAL";

	if(name == "IfcRampFlightTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcRampFlightTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcRampTypeEnumEnum" && value == 0)
		return "STRAIGHT_RUN_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 1)
		return "TWO_STRAIGHT_RUN_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 2)
		return "QUARTER_TURN_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 3)
		return "TWO_QUARTER_TURN_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 4)
		return "HALF_TURN_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 5)
		return "SPIRAL_RAMP";

	if(name == "IfcRampTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcRampTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 0)
		return "DAILY";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 1)
		return "WEEKLY";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 2)
		return "MONTHLY_BY_DAY_OF_MONTH";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 3)
		return "MONTHLY_BY_POSITION";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 4)
		return "BY_DAY_COUNT";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 5)
		return "BY_WEEKDAY_COUNT";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 6)
		return "YEARLY_BY_DAY_OF_MONTH";

	if(name == "IfcRecurrenceTypeEnumEnum" && value == 7)
		return "YEARLY_BY_POSITION";

	if(name == "IfcReferentTypeEnumEnum" && value == 0)
		return "KILOPOINT";

	if(name == "IfcReferentTypeEnumEnum" && value == 1)
		return "MILEPOINT";

	if(name == "IfcReferentTypeEnumEnum" && value == 2)
		return "STATION";

	if(name == "IfcReferentTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcReferentTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 0)
		return "BLINN";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 1)
		return "FLAT";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 2)
		return "GLASS";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 3)
		return "MATT";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 4)
		return "METAL";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 5)
		return "MIRROR";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 6)
		return "PHONG";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 7)
		return "PLASTIC";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 8)
		return "STRAUSS";

	if(name == "IfcReflectanceMethodEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 0)
		return "MAIN";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 1)
		return "SHEAR";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 2)
		return "LIGATURE";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 3)
		return "STUD";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 4)
		return "PUNCHING";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 5)
		return "EDGE";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 6)
		return "RING";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 7)
		return "ANCHORING";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcReinforcingBarRoleEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcReinforcingBarSurfaceEnumEnum" && value == 0)
		return "PLAIN";

	if(name == "IfcReinforcingBarSurfaceEnumEnum" && value == 1)
		return "TEXTURED";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 0)
		return "ANCHORING";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 1)
		return "EDGE";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 2)
		return "LIGATURE";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 3)
		return "MAIN";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 4)
		return "PUNCHING";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 5)
		return "RING";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 6)
		return "SHEAR";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 7)
		return "STUD";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcReinforcingBarTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcReinforcingMeshTypeEnumEnum" && value == 0)
		return "USERDEFINED";

	if(name == "IfcReinforcingMeshTypeEnumEnum" && value == 1)
		return "NOTDEFINED";

	if(name == "IfcRoleEnumEnum" && value == 0)
		return "SUPPLIER";

	if(name == "IfcRoleEnumEnum" && value == 1)
		return "MANUFACTURER";

	if(name == "IfcRoleEnumEnum" && value == 2)
		return "CONTRACTOR";

	if(name == "IfcRoleEnumEnum" && value == 3)
		return "SUBCONTRACTOR";

	if(name == "IfcRoleEnumEnum" && value == 4)
		return "ARCHITECT";

	if(name == "IfcRoleEnumEnum" && value == 5)
		return "STRUCTURALENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 6)
		return "COSTENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 7)
		return "CLIENT";

	if(name == "IfcRoleEnumEnum" && value == 8)
		return "BUILDINGOWNER";

	if(name == "IfcRoleEnumEnum" && value == 9)
		return "BUILDINGOPERATOR";

	if(name == "IfcRoleEnumEnum" && value == 10)
		return "MECHANICALENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 11)
		return "ELECTRICALENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 12)
		return "PROJECTMANAGER";

	if(name == "IfcRoleEnumEnum" && value == 13)
		return "FACILITIESMANAGER";

	if(name == "IfcRoleEnumEnum" && value == 14)
		return "CIVILENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 15)
		return "COMMISSIONINGENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 16)
		return "ENGINEER";

	if(name == "IfcRoleEnumEnum" && value == 17)
		return "OWNER";

	if(name == "IfcRoleEnumEnum" && value == 18)
		return "CONSULTANT";

	if(name == "IfcRoleEnumEnum" && value == 19)
		return "CONSTRUCTIONMANAGER";

	if(name == "IfcRoleEnumEnum" && value == 20)
		return "FIELDCONSTRUCTIONMANAGER";

	if(name == "IfcRoleEnumEnum" && value == 21)
		return "RESELLER";

	if(name == "IfcRoleEnumEnum" && value == 22)
		return "USERDEFINED";

	if(name == "IfcRoofTypeEnumEnum" && value == 0)
		return "FLAT_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 1)
		return "SHED_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 2)
		return "GABLE_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 3)
		return "HIP_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 4)
		return "HIPPED_GABLE_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 5)
		return "GAMBREL_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 6)
		return "MANSARD_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 7)
		return "BARREL_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 8)
		return "RAINBOW_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 9)
		return "BUTTERFLY_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 10)
		return "PAVILION_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 11)
		return "DOME_ROOF";

	if(name == "IfcRoofTypeEnumEnum" && value == 12)
		return "FREEFORM";

	if(name == "IfcRoofTypeEnumEnum" && value == 13)
		return "USERDEFINED";

	if(name == "IfcRoofTypeEnumEnum" && value == 14)
		return "NOTDEFINED";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 0)
		return "BATH";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 1)
		return "BIDET";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 2)
		return "CISTERN";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 3)
		return "SHOWER";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 4)
		return "SINK";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 5)
		return "SANITARYFOUNTAIN";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 6)
		return "TOILETPAN";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 7)
		return "URINAL";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 8)
		return "WASHHANDBASIN";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 9)
		return "WCSEAT";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 10)
		return "USERDEFINED";

	if(name == "IfcSanitaryTerminalTypeEnumEnum" && value == 11)
		return "NOTDEFINED";

	if(name == "IfcSectionTypeEnumEnum" && value == 0)
		return "UNIFORM";

	if(name == "IfcSectionTypeEnumEnum" && value == 1)
		return "TAPERED";

	if(name == "IfcSensorTypeEnumEnum" && value == 0)
		return "COSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 1)
		return "CO2SENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 2)
		return "CONDUCTANCESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 3)
		return "CONTACTSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 4)
		return "FIRESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 5)
		return "FLOWSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 6)
		return "FROSTSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 7)
		return "GASSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 8)
		return "HEATSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 9)
		return "HUMIDITYSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 10)
		return "IDENTIFIERSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 11)
		return "IONCONCENTRATIONSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 12)
		return "LEVELSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 13)
		return "LIGHTSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 14)
		return "MOISTURESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 15)
		return "MOVEMENTSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 16)
		return "PHSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 17)
		return "PRESSURESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 18)
		return "RADIATIONSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 19)
		return "RADIOACTIVITYSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 20)
		return "SMOKESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 21)
		return "SOUNDSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 22)
		return "TEMPERATURESENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 23)
		return "WINDSENSOR";

	if(name == "IfcSensorTypeEnumEnum" && value == 24)
		return "USERDEFINED";

	if(name == "IfcSensorTypeEnumEnum" && value == 25)
		return "NOTDEFINED";

	if(name == "IfcSequenceEnumEnum" && value == 0)
		return "START_START";

	if(name == "IfcSequenceEnumEnum" && value == 1)
		return "START_FINISH";

	if(name == "IfcSequenceEnumEnum" && value == 2)
		return "FINISH_START";

	if(name == "IfcSequenceEnumEnum" && value == 3)
		return "FINISH_FINISH";

	if(name == "IfcSequenceEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcSequenceEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcShadingDeviceTypeEnumEnum" && value == 0)
		return "JALOUSIE";

	if(name == "IfcShadingDeviceTypeEnumEnum" && value == 1)
		return "SHUTTER";

	if(name == "IfcShadingDeviceTypeEnumEnum" && value == 2)
		return "AWNING";

	if(name == "IfcShadingDeviceTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcShadingDeviceTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 0)
		return "P_SINGLEVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 1)
		return "P_ENUMERATEDVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 2)
		return "P_BOUNDEDVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 3)
		return "P_LISTVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 4)
		return "P_TABLEVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 5)
		return "P_REFERENCEVALUE";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 6)
		return "Q_LENGTH";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 7)
		return "Q_AREA";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 8)
		return "Q_VOLUME";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 9)
		return "Q_COUNT";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 10)
		return "Q_WEIGHT";

	if(name == "IfcSimplePropertyTemplateTypeEnumEnum" && value == 11)
		return "Q_TIME";

	if(name == "IfcSIPrefixEnum" && value == 0)
		return "EXA";

	if(name == "IfcSIPrefixEnum" && value == 1)
		return "PETA";

	if(name == "IfcSIPrefixEnum" && value == 2)
		return "TERA";

	if(name == "IfcSIPrefixEnum" && value == 3)
		return "GIGA";

	if(name == "IfcSIPrefixEnum" && value == 4)
		return "MEGA";

	if(name == "IfcSIPrefixEnum" && value == 5)
		return "KILO";

	if(name == "IfcSIPrefixEnum" && value == 6)
		return "HECTO";

	if(name == "IfcSIPrefixEnum" && value == 7)
		return "DECA";

	if(name == "IfcSIPrefixEnum" && value == 8)
		return "DECI";

	if(name == "IfcSIPrefixEnum" && value == 9)
		return "CENTI";

	if(name == "IfcSIPrefixEnum" && value == 10)
		return "MILLI";

	if(name == "IfcSIPrefixEnum" && value == 11)
		return "MICRO";

	if(name == "IfcSIPrefixEnum" && value == 12)
		return "NANO";

	if(name == "IfcSIPrefixEnum" && value == 13)
		return "PICO";

	if(name == "IfcSIPrefixEnum" && value == 14)
		return "FEMTO";

	if(name == "IfcSIPrefixEnum" && value == 15)
		return "ATTO";

	if(name == "IfcSIUnitNameEnum" && value == 0)
		return "AMPERE";

	if(name == "IfcSIUnitNameEnum" && value == 1)
		return "BECQUEREL";

	if(name == "IfcSIUnitNameEnum" && value == 2)
		return "CANDELA";

	if(name == "IfcSIUnitNameEnum" && value == 3)
		return "COULOMB";

	if(name == "IfcSIUnitNameEnum" && value == 4)
		return "CUBIC_METRE";

	if(name == "IfcSIUnitNameEnum" && value == 5)
		return "DEGREE_CELSIUS";

	if(name == "IfcSIUnitNameEnum" && value == 6)
		return "FARAD";

	if(name == "IfcSIUnitNameEnum" && value == 7)
		return "GRAM";

	if(name == "IfcSIUnitNameEnum" && value == 8)
		return "GRAY";

	if(name == "IfcSIUnitNameEnum" && value == 9)
		return "HENRY";

	if(name == "IfcSIUnitNameEnum" && value == 10)
		return "HERTZ";

	if(name == "IfcSIUnitNameEnum" && value == 11)
		return "JOULE";

	if(name == "IfcSIUnitNameEnum" && value == 12)
		return "KELVIN";

	if(name == "IfcSIUnitNameEnum" && value == 13)
		return "LUMEN";

	if(name == "IfcSIUnitNameEnum" && value == 14)
		return "LUX";

	if(name == "IfcSIUnitNameEnum" && value == 15)
		return "METRE";

	if(name == "IfcSIUnitNameEnum" && value == 16)
		return "MOLE";

	if(name == "IfcSIUnitNameEnum" && value == 17)
		return "NEWTON";

	if(name == "IfcSIUnitNameEnum" && value == 18)
		return "OHM";

	if(name == "IfcSIUnitNameEnum" && value == 19)
		return "PASCAL";

	if(name == "IfcSIUnitNameEnum" && value == 20)
		return "RADIAN";

	if(name == "IfcSIUnitNameEnum" && value == 21)
		return "SECOND";

	if(name == "IfcSIUnitNameEnum" && value == 22)
		return "SIEMENS";

	if(name == "IfcSIUnitNameEnum" && value == 23)
		return "SIEVERT";

	if(name == "IfcSIUnitNameEnum" && value == 24)
		return "SQUARE_METRE";

	if(name == "IfcSIUnitNameEnum" && value == 25)
		return "STERADIAN";

	if(name == "IfcSIUnitNameEnum" && value == 26)
		return "TESLA";

	if(name == "IfcSIUnitNameEnum" && value == 27)
		return "VOLT";

	if(name == "IfcSIUnitNameEnum" && value == 28)
		return "WATT";

	if(name == "IfcSIUnitNameEnum" && value == 29)
		return "WEBER";

	if(name == "IfcSlabTypeEnumEnum" && value == 0)
		return "FLOOR";

	if(name == "IfcSlabTypeEnumEnum" && value == 1)
		return "ROOF";

	if(name == "IfcSlabTypeEnumEnum" && value == 2)
		return "LANDING";

	if(name == "IfcSlabTypeEnumEnum" && value == 3)
		return "BASESLAB";

	if(name == "IfcSlabTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcSlabTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcSolarDeviceTypeEnumEnum" && value == 0)
		return "SOLARCOLLECTOR";

	if(name == "IfcSolarDeviceTypeEnumEnum" && value == 1)
		return "SOLARPANEL";

	if(name == "IfcSolarDeviceTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcSolarDeviceTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcSpaceHeaterTypeEnumEnum" && value == 0)
		return "CONVECTOR";

	if(name == "IfcSpaceHeaterTypeEnumEnum" && value == 1)
		return "RADIATOR";

	if(name == "IfcSpaceHeaterTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcSpaceHeaterTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcSpaceTypeEnumEnum" && value == 0)
		return "SPACE";

	if(name == "IfcSpaceTypeEnumEnum" && value == 1)
		return "PARKING";

	if(name == "IfcSpaceTypeEnumEnum" && value == 2)
		return "GFA";

	if(name == "IfcSpaceTypeEnumEnum" && value == 3)
		return "INTERNAL";

	if(name == "IfcSpaceTypeEnumEnum" && value == 4)
		return "EXTERNAL";

	if(name == "IfcSpaceTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcSpaceTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 0)
		return "CONSTRUCTION";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 1)
		return "FIRESAFETY";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 2)
		return "LIGHTING";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 3)
		return "OCCUPANCY";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 4)
		return "SECURITY";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 5)
		return "THERMAL";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 6)
		return "TRANSPORT";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 7)
		return "VENTILATION";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcSpatialZoneTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcStackTerminalTypeEnumEnum" && value == 0)
		return "BIRDCAGE";

	if(name == "IfcStackTerminalTypeEnumEnum" && value == 1)
		return "COWL";

	if(name == "IfcStackTerminalTypeEnumEnum" && value == 2)
		return "RAINWATERHOPPER";

	if(name == "IfcStackTerminalTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcStackTerminalTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 0)
		return "STRAIGHT";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 1)
		return "WINDER";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 2)
		return "SPIRAL";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 3)
		return "CURVED";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 4)
		return "FREEFORM";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcStairFlightTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcStairTypeEnumEnum" && value == 0)
		return "STRAIGHT_RUN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 1)
		return "TWO_STRAIGHT_RUN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 2)
		return "QUARTER_WINDING_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 3)
		return "QUARTER_TURN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 4)
		return "HALF_WINDING_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 5)
		return "HALF_TURN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 6)
		return "TWO_QUARTER_WINDING_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 7)
		return "TWO_QUARTER_TURN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 8)
		return "THREE_QUARTER_WINDING_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 9)
		return "THREE_QUARTER_TURN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 10)
		return "SPIRAL_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 11)
		return "DOUBLE_RETURN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 12)
		return "CURVED_RUN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 13)
		return "TWO_CURVED_RUN_STAIR";

	if(name == "IfcStairTypeEnumEnum" && value == 14)
		return "USERDEFINED";

	if(name == "IfcStairTypeEnumEnum" && value == 15)
		return "NOTDEFINED";

	if(name == "IfcStateEnumEnum" && value == 0)
		return "READWRITE";

	if(name == "IfcStateEnumEnum" && value == 1)
		return "READONLY";

	if(name == "IfcStateEnumEnum" && value == 2)
		return "LOCKED";

	if(name == "IfcStateEnumEnum" && value == 3)
		return "READWRITELOCKED";

	if(name == "IfcStateEnumEnum" && value == 4)
		return "READONLYLOCKED";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 0)
		return "CONST";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 1)
		return "LINEAR";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 2)
		return "POLYGONAL";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 3)
		return "EQUIDISTANT";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 4)
		return "SINUS";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 5)
		return "PARABOLA";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 6)
		return "DISCRETE";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcStructuralCurveActivityTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 0)
		return "RIGID_JOINED_MEMBER";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 1)
		return "PIN_JOINED_MEMBER";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 2)
		return "CABLE";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 3)
		return "TENSION_MEMBER";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 4)
		return "COMPRESSION_MEMBER";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcStructuralCurveMemberTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 0)
		return "CONST";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 1)
		return "BILINEAR";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 2)
		return "DISCRETE";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 3)
		return "ISOCONTOUR";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcStructuralSurfaceActivityTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcStructuralSurfaceMemberTypeEnumEnum" && value == 0)
		return "BENDING_ELEMENT";

	if(name == "IfcStructuralSurfaceMemberTypeEnumEnum" && value == 1)
		return "MEMBRANE_ELEMENT";

	if(name == "IfcStructuralSurfaceMemberTypeEnumEnum" && value == 2)
		return "SHELL";

	if(name == "IfcStructuralSurfaceMemberTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcStructuralSurfaceMemberTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcSubContractResourceTypeEnumEnum" && value == 0)
		return "PURCHASE";

	if(name == "IfcSubContractResourceTypeEnumEnum" && value == 1)
		return "WORK";

	if(name == "IfcSubContractResourceTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcSubContractResourceTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcSurfaceFeatureTypeEnumEnum" && value == 0)
		return "MARK";

	if(name == "IfcSurfaceFeatureTypeEnumEnum" && value == 1)
		return "TAG";

	if(name == "IfcSurfaceFeatureTypeEnumEnum" && value == 2)
		return "TREATMENT";

	if(name == "IfcSurfaceFeatureTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcSurfaceFeatureTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcSurfaceSideEnum" && value == 0)
		return "POSITIVE";

	if(name == "IfcSurfaceSideEnum" && value == 1)
		return "NEGATIVE";

	if(name == "IfcSurfaceSideEnum" && value == 2)
		return "BOTH";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 0)
		return "CONTACTOR";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 1)
		return "DIMMERSWITCH";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 2)
		return "EMERGENCYSTOP";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 3)
		return "KEYPAD";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 4)
		return "MOMENTARYSWITCH";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 5)
		return "SELECTORSWITCH";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 6)
		return "STARTER";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 7)
		return "SWITCHDISCONNECTOR";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 8)
		return "TOGGLESWITCH";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcSwitchingDeviceTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcSystemFurnitureElementTypeEnumEnum" && value == 0)
		return "PANEL";

	if(name == "IfcSystemFurnitureElementTypeEnumEnum" && value == 1)
		return "WORKSURFACE";

	if(name == "IfcSystemFurnitureElementTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcSystemFurnitureElementTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcTankTypeEnumEnum" && value == 0)
		return "BASIN";

	if(name == "IfcTankTypeEnumEnum" && value == 1)
		return "BREAKPRESSURE";

	if(name == "IfcTankTypeEnumEnum" && value == 2)
		return "EXPANSION";

	if(name == "IfcTankTypeEnumEnum" && value == 3)
		return "FEEDANDEXPANSION";

	if(name == "IfcTankTypeEnumEnum" && value == 4)
		return "PRESSUREVESSEL";

	if(name == "IfcTankTypeEnumEnum" && value == 5)
		return "STORAGE";

	if(name == "IfcTankTypeEnumEnum" && value == 6)
		return "VESSEL";

	if(name == "IfcTankTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcTankTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcTaskDurationEnumEnum" && value == 0)
		return "ELAPSEDTIME";

	if(name == "IfcTaskDurationEnumEnum" && value == 1)
		return "WORKTIME";

	if(name == "IfcTaskDurationEnumEnum" && value == 2)
		return "NOTDEFINED";

	if(name == "IfcTaskTypeEnumEnum" && value == 0)
		return "ATTENDANCE";

	if(name == "IfcTaskTypeEnumEnum" && value == 1)
		return "CONSTRUCTION";

	if(name == "IfcTaskTypeEnumEnum" && value == 2)
		return "DEMOLITION";

	if(name == "IfcTaskTypeEnumEnum" && value == 3)
		return "DISMANTLE";

	if(name == "IfcTaskTypeEnumEnum" && value == 4)
		return "DISPOSAL";

	if(name == "IfcTaskTypeEnumEnum" && value == 5)
		return "INSTALLATION";

	if(name == "IfcTaskTypeEnumEnum" && value == 6)
		return "LOGISTIC";

	if(name == "IfcTaskTypeEnumEnum" && value == 7)
		return "MAINTENANCE";

	if(name == "IfcTaskTypeEnumEnum" && value == 8)
		return "MOVE";

	if(name == "IfcTaskTypeEnumEnum" && value == 9)
		return "OPERATION";

	if(name == "IfcTaskTypeEnumEnum" && value == 10)
		return "REMOVAL";

	if(name == "IfcTaskTypeEnumEnum" && value == 11)
		return "RENOVATION";

	if(name == "IfcTaskTypeEnumEnum" && value == 12)
		return "USERDEFINED";

	if(name == "IfcTaskTypeEnumEnum" && value == 13)
		return "NOTDEFINED";

	if(name == "IfcTendonAnchorTypeEnumEnum" && value == 0)
		return "COUPLER";

	if(name == "IfcTendonAnchorTypeEnumEnum" && value == 1)
		return "FIXED_END";

	if(name == "IfcTendonAnchorTypeEnumEnum" && value == 2)
		return "TENSIONING_END";

	if(name == "IfcTendonAnchorTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcTendonAnchorTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcTendonTypeEnumEnum" && value == 0)
		return "BAR";

	if(name == "IfcTendonTypeEnumEnum" && value == 1)
		return "COATED";

	if(name == "IfcTendonTypeEnumEnum" && value == 2)
		return "STRAND";

	if(name == "IfcTendonTypeEnumEnum" && value == 3)
		return "WIRE";

	if(name == "IfcTendonTypeEnumEnum" && value == 4)
		return "USERDEFINED";

	if(name == "IfcTendonTypeEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcTextPathEnum" && value == 0)
		return "LEFT";

	if(name == "IfcTextPathEnum" && value == 1)
		return "RIGHT";

	if(name == "IfcTextPathEnum" && value == 2)
		return "UP";

	if(name == "IfcTextPathEnum" && value == 3)
		return "DOWN";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 0)
		return "CONTINUOUS";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 1)
		return "DISCRETE";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 2)
		return "DISCRETEBINARY";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 3)
		return "PIECEWISEBINARY";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 4)
		return "PIECEWISECONSTANT";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 5)
		return "PIECEWISECONTINUOUS";

	if(name == "IfcTimeSeriesDataTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcTransformerTypeEnumEnum" && value == 0)
		return "CURRENT";

	if(name == "IfcTransformerTypeEnumEnum" && value == 1)
		return "FREQUENCY";

	if(name == "IfcTransformerTypeEnumEnum" && value == 2)
		return "INVERTER";

	if(name == "IfcTransformerTypeEnumEnum" && value == 3)
		return "RECTIFIER";

	if(name == "IfcTransformerTypeEnumEnum" && value == 4)
		return "VOLTAGE";

	if(name == "IfcTransformerTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcTransformerTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcTransitionCodeEnum" && value == 0)
		return "DISCONTINUOUS";

	if(name == "IfcTransitionCodeEnum" && value == 1)
		return "CONTINUOUS";

	if(name == "IfcTransitionCodeEnum" && value == 2)
		return "CONTSAMEGRADIENT";

	if(name == "IfcTransitionCodeEnum" && value == 3)
		return "CONTSAMEGRADIENTSAMECURVATURE";

	if(name == "IfcTransitionCurveTypeEnum" && value == 0)
		return "BIQUADRATICPARABOLA";

	if(name == "IfcTransitionCurveTypeEnum" && value == 1)
		return "BLOSSCURVE";

	if(name == "IfcTransitionCurveTypeEnum" && value == 2)
		return "CLOTHOIDCURVE";

	if(name == "IfcTransitionCurveTypeEnum" && value == 3)
		return "COSINECURVE";

	if(name == "IfcTransitionCurveTypeEnum" && value == 4)
		return "CUBICPARABOLA";

	if(name == "IfcTransitionCurveTypeEnum" && value == 5)
		return "SINECURVE";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 0)
		return "ELEVATOR";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 1)
		return "ESCALATOR";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 2)
		return "MOVINGWALKWAY";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 3)
		return "CRANEWAY";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 4)
		return "LIFTINGGEAR";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcTransportElementTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcTrimmingPreferenceEnum" && value == 0)
		return "CARTESIAN";

	if(name == "IfcTrimmingPreferenceEnum" && value == 1)
		return "PARAMETER";

	if(name == "IfcTrimmingPreferenceEnum" && value == 2)
		return "UNSPECIFIED";

	if(name == "IfcTubeBundleTypeEnumEnum" && value == 0)
		return "FINNED";

	if(name == "IfcTubeBundleTypeEnumEnum" && value == 1)
		return "USERDEFINED";

	if(name == "IfcTubeBundleTypeEnumEnum" && value == 2)
		return "NOTDEFINED";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 0)
		return "ALARMPANEL";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 1)
		return "CONTROLPANEL";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 2)
		return "GASDETECTIONPANEL";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 3)
		return "INDICATORPANEL";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 4)
		return "MIMICPANEL";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 5)
		return "HUMIDISTAT";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 6)
		return "THERMOSTAT";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 7)
		return "WEATHERSTATION";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 8)
		return "USERDEFINED";

	if(name == "IfcUnitaryControlElementTypeEnumEnum" && value == 9)
		return "NOTDEFINED";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 0)
		return "AIRHANDLER";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 1)
		return "AIRCONDITIONINGUNIT";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 2)
		return "DEHUMIDIFIER";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 3)
		return "SPLITSYSTEM";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 4)
		return "ROOFTOPUNIT";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 5)
		return "USERDEFINED";

	if(name == "IfcUnitaryEquipmentTypeEnumEnum" && value == 6)
		return "NOTDEFINED";

	if(name == "IfcUnitEnumEnum" && value == 0)
		return "ABSORBEDDOSEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 1)
		return "AMOUNTOFSUBSTANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 2)
		return "AREAUNIT";

	if(name == "IfcUnitEnumEnum" && value == 3)
		return "DOSEEQUIVALENTUNIT";

	if(name == "IfcUnitEnumEnum" && value == 4)
		return "ELECTRICCAPACITANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 5)
		return "ELECTRICCHARGEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 6)
		return "ELECTRICCONDUCTANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 7)
		return "ELECTRICCURRENTUNIT";

	if(name == "IfcUnitEnumEnum" && value == 8)
		return "ELECTRICRESISTANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 9)
		return "ELECTRICVOLTAGEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 10)
		return "ENERGYUNIT";

	if(name == "IfcUnitEnumEnum" && value == 11)
		return "FORCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 12)
		return "FREQUENCYUNIT";

	if(name == "IfcUnitEnumEnum" && value == 13)
		return "ILLUMINANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 14)
		return "INDUCTANCEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 15)
		return "LENGTHUNIT";

	if(name == "IfcUnitEnumEnum" && value == 16)
		return "LUMINOUSFLUXUNIT";

	if(name == "IfcUnitEnumEnum" && value == 17)
		return "LUMINOUSINTENSITYUNIT";

	if(name == "IfcUnitEnumEnum" && value == 18)
		return "MAGNETICFLUXDENSITYUNIT";

	if(name == "IfcUnitEnumEnum" && value == 19)
		return "MAGNETICFLUXUNIT";

	if(name == "IfcUnitEnumEnum" && value == 20)
		return "MASSUNIT";

	if(name == "IfcUnitEnumEnum" && value == 21)
		return "PLANEANGLEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 22)
		return "POWERUNIT";

	if(name == "IfcUnitEnumEnum" && value == 23)
		return "PRESSUREUNIT";

	if(name == "IfcUnitEnumEnum" && value == 24)
		return "RADIOACTIVITYUNIT";

	if(name == "IfcUnitEnumEnum" && value == 25)
		return "SOLIDANGLEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 26)
		return "THERMODYNAMICTEMPERATUREUNIT";

	if(name == "IfcUnitEnumEnum" && value == 27)
		return "TIMEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 28)
		return "VOLUMEUNIT";

	if(name == "IfcUnitEnumEnum" && value == 29)
		return "USERDEFINED";

	if(name == "IfcValveTypeEnumEnum" && value == 0)
		return "AIRRELEASE";

	if(name == "IfcValveTypeEnumEnum" && value == 1)
		return "ANTIVACUUM";

	if(name == "IfcValveTypeEnumEnum" && value == 2)
		return "CHANGEOVER";

	if(name == "IfcValveTypeEnumEnum" && value == 3)
		return "CHECK";

	if(name == "IfcValveTypeEnumEnum" && value == 4)
		return "COMMISSIONING";

	if(name == "IfcValveTypeEnumEnum" && value == 5)
		return "DIVERTING";

	if(name == "IfcValveTypeEnumEnum" && value == 6)
		return "DRAWOFFCOCK";

	if(name == "IfcValveTypeEnumEnum" && value == 7)
		return "DOUBLECHECK";

	if(name == "IfcValveTypeEnumEnum" && value == 8)
		return "DOUBLEREGULATING";

	if(name == "IfcValveTypeEnumEnum" && value == 9)
		return "FAUCET";

	if(name == "IfcValveTypeEnumEnum" && value == 10)
		return "FLUSHING";

	if(name == "IfcValveTypeEnumEnum" && value == 11)
		return "GASCOCK";

	if(name == "IfcValveTypeEnumEnum" && value == 12)
		return "GASTAP";

	if(name == "IfcValveTypeEnumEnum" && value == 13)
		return "ISOLATING";

	if(name == "IfcValveTypeEnumEnum" && value == 14)
		return "MIXING";

	if(name == "IfcValveTypeEnumEnum" && value == 15)
		return "PRESSUREREDUCING";

	if(name == "IfcValveTypeEnumEnum" && value == 16)
		return "PRESSURERELIEF";

	if(name == "IfcValveTypeEnumEnum" && value == 17)
		return "REGULATING";

	if(name == "IfcValveTypeEnumEnum" && value == 18)
		return "SAFETYCUTOFF";

	if(name == "IfcValveTypeEnumEnum" && value == 19)
		return "STEAMTRAP";

	if(name == "IfcValveTypeEnumEnum" && value == 20)
		return "STOPCOCK";

	if(name == "IfcValveTypeEnumEnum" && value == 21)
		return "USERDEFINED";

	if(name == "IfcValveTypeEnumEnum" && value == 22)
		return "NOTDEFINED";

	if(name == "IfcVibrationIsolatorTypeEnumEnum" && value == 0)
		return "COMPRESSION";

	if(name == "IfcVibrationIsolatorTypeEnumEnum" && value == 1)
		return "SPRING";

	if(name == "IfcVibrationIsolatorTypeEnumEnum" && value == 2)
		return "USERDEFINED";

	if(name == "IfcVibrationIsolatorTypeEnumEnum" && value == 3)
		return "NOTDEFINED";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 0)
		return "CUTOUT";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 1)
		return "NOTCH";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 2)
		return "HOLE";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 3)
		return "MITER";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 4)
		return "CHAMFER";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 5)
		return "EDGE";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 6)
		return "USERDEFINED";

	if(name == "IfcVoidingFeatureTypeEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcWallTypeEnumEnum" && value == 0)
		return "MOVABLE";

	if(name == "IfcWallTypeEnumEnum" && value == 1)
		return "PARAPET";

	if(name == "IfcWallTypeEnumEnum" && value == 2)
		return "PARTITIONING";

	if(name == "IfcWallTypeEnumEnum" && value == 3)
		return "PLUMBINGWALL";

	if(name == "IfcWallTypeEnumEnum" && value == 4)
		return "SHEAR";

	if(name == "IfcWallTypeEnumEnum" && value == 5)
		return "SOLIDWALL";

	if(name == "IfcWallTypeEnumEnum" && value == 6)
		return "STANDARD";

	if(name == "IfcWallTypeEnumEnum" && value == 7)
		return "POLYGONAL";

	if(name == "IfcWallTypeEnumEnum" && value == 8)
		return "ELEMENTEDWALL";

	if(name == "IfcWallTypeEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcWallTypeEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 0)
		return "FLOORTRAP";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 1)
		return "FLOORWASTE";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 2)
		return "GULLYSUMP";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 3)
		return "GULLYTRAP";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 4)
		return "ROOFDRAIN";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 5)
		return "WASTEDISPOSALUNIT";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 6)
		return "WASTETRAP";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 7)
		return "USERDEFINED";

	if(name == "IfcWasteTerminalTypeEnumEnum" && value == 8)
		return "NOTDEFINED";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 0)
		return "SIDEHUNGRIGHTHAND";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 1)
		return "SIDEHUNGLEFTHAND";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 2)
		return "TILTANDTURNRIGHTHAND";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 3)
		return "TILTANDTURNLEFTHAND";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 4)
		return "TOPHUNG";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 5)
		return "BOTTOMHUNG";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 6)
		return "PIVOTHORIZONTAL";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 7)
		return "PIVOTVERTICAL";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 8)
		return "SLIDINGHORIZONTAL";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 9)
		return "SLIDINGVERTICAL";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 10)
		return "REMOVABLECASEMENT";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 11)
		return "FIXEDCASEMENT";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 12)
		return "OTHEROPERATION";

	if(name == "IfcWindowPanelOperationEnumEnum" && value == 13)
		return "NOTDEFINED";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 0)
		return "LEFT";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 1)
		return "MIDDLE";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 2)
		return "RIGHT";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 3)
		return "BOTTOM";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 4)
		return "TOP";

	if(name == "IfcWindowPanelPositionEnumEnum" && value == 5)
		return "NOTDEFINED";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 0)
		return "ALUMINIUM";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 1)
		return "HIGH_GRADE_STEEL";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 2)
		return "STEEL";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 3)
		return "WOOD";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 4)
		return "ALUMINIUM_WOOD";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 5)
		return "PLASTIC";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 6)
		return "OTHER_CONSTRUCTION";

	if(name == "IfcWindowStyleConstructionEnumEnum" && value == 7)
		return "NOTDEFINED";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 0)
		return "SINGLE_PANEL";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 1)
		return "DOUBLE_PANEL_VERTICAL";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 2)
		return "DOUBLE_PANEL_HORIZONTAL";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 3)
		return "TRIPLE_PANEL_VERTICAL";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 4)
		return "TRIPLE_PANEL_BOTTOM";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 5)
		return "TRIPLE_PANEL_TOP";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 6)
		return "TRIPLE_PANEL_LEFT";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 7)
		return "TRIPLE_PANEL_RIGHT";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 8)
		return "TRIPLE_PANEL_HORIZONTAL";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcWindowStyleOperationEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcWindowTypeEnumEnum" && value == 0)
		return "WINDOW";

	if(name == "IfcWindowTypeEnumEnum" && value == 1)
		return "SKYLIGHT";

	if(name == "IfcWindowTypeEnumEnum" && value == 2)
		return "LIGHTDOME";

	if(name == "IfcWindowTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcWindowTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 0)
		return "SINGLE_PANEL";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 1)
		return "DOUBLE_PANEL_VERTICAL";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 2)
		return "DOUBLE_PANEL_HORIZONTAL";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 3)
		return "TRIPLE_PANEL_VERTICAL";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 4)
		return "TRIPLE_PANEL_BOTTOM";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 5)
		return "TRIPLE_PANEL_TOP";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 6)
		return "TRIPLE_PANEL_LEFT";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 7)
		return "TRIPLE_PANEL_RIGHT";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 8)
		return "TRIPLE_PANEL_HORIZONTAL";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 9)
		return "USERDEFINED";

	if(name == "IfcWindowTypePartitioningEnumEnum" && value == 10)
		return "NOTDEFINED";

	if(name == "IfcWorkCalendarTypeEnumEnum" && value == 0)
		return "FIRSTSHIFT";

	if(name == "IfcWorkCalendarTypeEnumEnum" && value == 1)
		return "SECONDSHIFT";

	if(name == "IfcWorkCalendarTypeEnumEnum" && value == 2)
		return "THIRDSHIFT";

	if(name == "IfcWorkCalendarTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcWorkCalendarTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcWorkPlanTypeEnumEnum" && value == 0)
		return "ACTUAL";

	if(name == "IfcWorkPlanTypeEnumEnum" && value == 1)
		return "BASELINE";

	if(name == "IfcWorkPlanTypeEnumEnum" && value == 2)
		return "PLANNED";

	if(name == "IfcWorkPlanTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcWorkPlanTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	if(name == "IfcWorkScheduleTypeEnumEnum" && value == 0)
		return "ACTUAL";

	if(name == "IfcWorkScheduleTypeEnumEnum" && value == 1)
		return "BASELINE";

	if(name == "IfcWorkScheduleTypeEnumEnum" && value == 2)
		return "PLANNED";

	if(name == "IfcWorkScheduleTypeEnumEnum" && value == 3)
		return "USERDEFINED";

	if(name == "IfcWorkScheduleTypeEnumEnum" && value == 4)
		return "NOTDEFINED";

	return "";
}
