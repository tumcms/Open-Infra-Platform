
import os

ifcEntityFolder = "D:/Uni/HiWi/blueinfrastructurecenter/Ifc2x3/src/OpenInfraPlatform/Ifc2x3/entity/include"
ifcNamespace = "Ifc2x3"
applicationNamespace = "OpenInfraPlatform"
basicStructName = "BasicIfc2x3EntityTypes"
ifcStructName = "Ifc2x3EntityTypes"
templateEntityFile = "EMTBasicIfc2x3EntityTypes.h"
entityFile = "EMTIfc2x3EntityTypes.h"
ifcClasses = []

files = os.listdir(ifcEntityFolder)

for file in files:
    if file.endswith(".h"):
        ifcClasses.append(file[:-2])

with open(templateEntityFile, "w") as file:
    file.write("\n#pragma once\n\n")
    file.write("namespace emt\n")
    file.write("{\n")
    file.write("\ttemplate <\n")
    for cls in ifcClasses[:-1]:
        file.write("\t\ttypename " + cls + "T" + ",\n")

    file.write("\t\ttypename " + ifcClasses[-1:][0] + "T" + "\n")
    file.write("\t>\n")

    file.write("\tstruct " + basicStructName + "\n")
    file.write("\t{\n")

    for cls in ifcClasses:
        file.write("\t\ttypedef " + cls + "T " + cls + ";\n")

    file.write("\t};\n")
    file.write("}")

with open(entityFile, "w") as file:
    file.write("\n#pragma once\n\n")
    file.write("#include \"" + templateEntityFile + "\"\n\n")
    file.write("namespace " + applicationNamespace + "\n")
    file.write("{\n")
    file.write("\tnamespace " + ifcNamespace + "\n")
    file.write("\t{\n")
    for cls in ifcClasses:
        file.write("\t\t class " + cls + ";\n")

    file.write("\t}\n")
    file.write("}\n\n")

    file.write("namespace emt\n")
    file.write("{\n")
    file.write("\ttypedef " + basicStructName + "<\n")
    for cls in ifcClasses[:-1]:
        file.write("\t\t" + applicationNamespace + "::" + ifcNamespace + "::" + cls + ",\n")

    file.write("\t\t" + applicationNamespace + "::" + ifcNamespace + "::" + ifcClasses[-1:][0] + "\n")
    file.write("\t>\n")
    file.write("\t" + ifcStructName + ";\n")
    file.write("}\n")

