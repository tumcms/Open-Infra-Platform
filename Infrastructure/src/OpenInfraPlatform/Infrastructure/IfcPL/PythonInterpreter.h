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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_PythonInterpreter_cb349df2_929d_479b_9aa4_eb7ec061b693_h
#define OpenInfraPlatform_Infrastructure_PythonInterpreter_cb349df2_929d_479b_9aa4_eb7ec061b693_h

#include <iostream>
//#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

/*
namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct Vector2d
		{
			double x;
			double y;
		};

		struct eType
		{
			enum Enum
			{
				Int,
				Double,
				Vector2d
			};
		};

		struct argument
		{
			argument(const char* name, const eType::Enum type) :
				name(name), type(type)
			{

			}

			std::string		name;
			eType::Enum		type;
		};

		struct pythonInterpreterDescription
		{
			const char*				moduleName;
			const char*				functionName;
			std::vector<argument>   arguments;
			eType::Enum				returnType;

			int getArgumentCount()
			{
				return arguments.size();
			}
		};

		class PythonInterpreter
		{
		public:
			virtual ~PythonInterpreter()
			{
				Py_Finalize();
			}

			static PythonInterpreter& getInstance()
			{
				static PythonInterpreter instance;
				return instance;
			}

			void execute2(pythonInterpreterDescription& pid,
				const Vector2d& start, 
				const Vector2d& end,
				const double length,
				const double radiusStart,
				const double radiusEnd,
				const bool clockwise)
			{
				/// Get module
				PyObject *pName = PyUnicode_FromString(pid.moduleName);
				// Error checking of pName left out

				PyObject *pModule = PyImport_Import(pName);
				Py_DECREF(pName);

				if (pModule == nullptr)
				{
					PyErr_Print();

					std::cout << "Failed to load \"" << pid.moduleName << "\"" << std::endl;
					throw std::runtime_error("Failed to load module");
				}

				///  injection
				PyObject* po_start_x = PyFloat_FromDouble(start.x);
				PyObject *po_start = PyObject_GetAttrString(pModule,"start");
				PyObject_SetAttrString(po_start, "x", po_start_x);

				PyObject* po_start_y = PyFloat_FromDouble(start.y);
				PyObject_SetAttrString(po_start, "y", po_start_y);

				PyObject* po_end_x = PyFloat_FromDouble(end.x);
				PyObject *po_end = PyObject_GetAttrString(pModule,"end");
				PyObject_SetAttrString(po_end, "x", po_end_x);

				PyObject* po_end_y = PyFloat_FromDouble(end.y);
				PyObject_SetAttrString(po_end, "y", po_end_y);

				PyObject* po_length = PyFloat_FromDouble(length);
				PyObject_SetAttrString(pModule,"length", po_length);

				PyObject* po_startCurvature = PyFloat_FromDouble(1.0/radiusStart);
				PyObject_SetAttrString(pModule,"startCurvature", po_startCurvature);

				PyObject* po_endCurvature = PyFloat_FromDouble(1.0/radiusEnd);
				PyObject_SetAttrString(pModule,"endCurvature", po_endCurvature);

				PyObject* po_clockwise = PyBool_FromLong(clockwise);
				PyObject_SetAttrString(pModule,"clockwise", po_clockwise);

				//  injection - end
				PyObject  *pFuncPreExecution = PyObject_GetAttrString(pModule, pid.functionName);
				/// preExecution event

				/// end - preExecution event

				/// Get function
				PyObject  *pFunc = PyObject_GetAttrString(pModule, pid.functionName);
				// pFunc is a new reference

				if (pFunc && PyCallable_Check(pFunc)) 
				{
					PyObject *pArgs = PyTuple_New(pid.getArgumentCount());

					PyObject *pValue = nullptr;

					// setup function parameters
					for (int i = 0; i < pid.getArgumentCount(); ++i) 
					{
						if (pid.arguments[i].type == eType::Int)
						{
							pValue = PyLong_FromLong(atoi(pid.arguments[i].name.c_str()));
						}
						else
						{
							pValue = PyFloat_FromDouble(atof(pid.arguments[i].name.c_str()));
						}

						if (!pValue) 
						{
							Py_DECREF(pArgs);
							Py_DECREF(pModule);
							std::cout << "Cannot convert argument" << std::endl;
							throw std::runtime_error("Cannot convert argument");
						}
						// pValue reference stolen here:
						PyTuple_SetItem(pArgs, i, pValue);
					}

					pValue = PyObject_CallObject(pFunc, pArgs);
					Py_DECREF(pArgs);

					if (pValue != nullptr)
					{
						switch (pid.returnType)
						{
						case eType::Int:
							//std::cout << "Result of call: " << PyLong_AsLong(pValue) << std::endl;
							intValue_ = PyLong_AsLong(pValue);
							break;

						case eType::Double:
							//std::cout << "Result of call: " << PyFloat_AsDouble(pValue) << std::endl;
							doubleValue_ = PyFloat_AsDouble(pValue);
							break;

						case  eType::Vector2d:
							{
								PyObject *temp = PyObject_GetAttrString(pValue, "x");
								if (temp == NULL) {
									// error handling
								}
								double x = PyFloat_AsDouble(temp);

								// clean up reference when done with temp
								Py_DECREF(temp);


								temp = PyObject_GetAttrString(pValue, "y");
								if (temp == NULL) {
									// error handling
								}
								double y = PyFloat_AsDouble(temp);

								// clean up reference when done with temp
								Py_DECREF(temp);

								vectorValue_.x = x;
								vectorValue_.y = y;
							}
							break;

						default:
							break;
						}

						Py_DECREF(pValue);
					}
					else 
					{
						Py_DECREF(pFunc);
						Py_DECREF(pModule);
						PyErr_Print();
						std::cout << "Call failed" << std::endl;
						throw std::runtime_error("Call failed");
					}
				}
				else
				{
					if (PyErr_Occurred())
						PyErr_Print();

					std::cout << "Cannot find function \"" << pid.functionName << "\"" << std::endl;
				}

				Py_XDECREF(pFunc);
				Py_DECREF(pModule);
			}

			double getDoubleValue() const { return doubleValue_; }
			int getIntValue() const { return intValue_; }
			Vector2d getVector2dValue() const { return vectorValue_; }

		private:
			double		doubleValue_;
			int			intValue_;
			Vector2d	vectorValue_;

			PythonInterpreter()
			{
				Py_Initialize();

				PyObject* sysPath = PySys_GetObject((char*)"path");
				PyObject* programName = PyUnicode_FromString("Data/DesignAutomation");
				PyList_Append(sysPath, programName);
				Py_DECREF(programName);
			}
		};
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::PythonInterpreter;
}

*/

#endif // end define OpenInfraPlatform_Infrastructure_PythonInterpreter_cb349df2_929d_479b_9aa4_eb7ec061b693_h
