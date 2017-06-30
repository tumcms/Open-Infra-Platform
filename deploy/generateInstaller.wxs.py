import os
import sys

import uuid
import codecs

from xml.sax.saxutils import escape as xml_escape

CurrentPath = os.path.dirname(__file__)
ProjectFolderName = "TUM Open Infra Platform"
ProjectFolder = os.path.join(CurrentPath, ProjectFolderName)

dirString = '<Directory Id="{}" Name="{}">\n'
compRefString = '<ComponentRef Id="{}" />\n'
componentRefs = ''
componentString = """
				<Component Id="{}" DiskId="1" Guid="{}" Win64="yes">
					<File Id="{}" Name="{}" Source="{}" />
				</Component>\n
				  """

def sanitizeName(name):
    if (name[0].isdigit()):
        name = '_' + name

    name = name.replace('-', '_').replace('Ä', '_').replace('Ö', '_').replace('Ü', '_').replace('ä', '_').replace('ö', '_').replace('ü', '_').replace('+', '_')

    return name

def dirAsXML(path):
    global componentRefs

    dirName = xml_escape(os.path.basename(path)) #sanitizeName(xml_escape(os.path.basename(path)))
    dirId = sanitizeName(str(getGUID()))
    result = ''
    if dirName != ProjectFolderName:
        result = dirString.format(dirId, dirName)
		
    dirs = []
    files = []

    for item in os.listdir(path):
        itempath = os.path.join(path, item)
        if os.path.isdir(itempath):
            dirs.append(item)
        elif os.path.isfile(itempath):
            files.append(item)

    print('Adding files...')
    
    if files:
        for f in files:
            fileId = sanitizeName(str(getGUID()))
            fileEscape = xml_escape(f) #sanitizeName(xml_escape(f))
            componentRefs += compRefString.format(fileId)

            # please don't touch this, seriously
            result += componentString.format(fileId, getGUID(), fileId, fileEscape, os.path.relpath(path, f)[3:] + '\\' + f)
            #result += componentString.format(fileEscape.upper(), getGUID(), fileEscape.upper(), fileEscape, os.path.relpath(path, f)[3:] + f)

    print('Adding dirs...')

    if dirs:
        for d in dirs:
            x = dirAsXML(os.path.join(path, d))
            result += '\n'.join('  ' + line for line in x.split('\n'))

    if dirName != ProjectFolderName:
        result += '</Directory>\n'
		
    return result


def getGUID():
    return uuid.uuid4()


def main():
    os.environ["LANGUAGE"] = "en_US.UTF-8"

    installerTemplate = 'installer_template.wxs'
    installerTemplatePath = os.path.join(CurrentPath, installerTemplate)

    dirXml = dirAsXML(ProjectFolder)

    fileContent = ''
    with open(installerTemplatePath, "r") as installerTempl:
        fileContent = installerTempl.read()

    with codecs.open(os.path.join(CurrentPath, 'installer.wxs'), "w", "utf-8") as installerFile:
        newContent = fileContent.format(dirXml, componentRefs)
        installerFile.write(newContent)
        print('Wrote new content')

    return 0


if __name__ == '__main__':
    sys.exit(main())
