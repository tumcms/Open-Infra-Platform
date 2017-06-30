import os
import re
import sys
	
CurrentPath = os.path.dirname(__file__)

	
def DetermineCurrentRevison():
	pattern = r"""
				changeset: 		# Result preceeded by 'changeset:'		
				(?:\s+)			# Unknown amount of whitespaces
				([0-9]{4})		# Four digit revision number				
			  """
			  
	regex = re.compile(pattern, re.X)	
	
	text = os.popen('hg log -l 1').read()	
	match = regex.match(text)	
	
	revision = -1
	
	if match:
		revision = match.group(1)		
		irev = int(revision) + 1
		return str(irev)
	else:
		print ("Could not retrieve revision number!")	
	
	
def ReplaceFile(fileName, content):
	tempFileName = fileName + '.tmp'
	with open(tempFileName, "w") as tempFile:
		# Write new content to temp file
		tempFile.write(content)
		
	# Delete old file
	os.remove(fileName)
	
	# Rename temp file to old file
	os.rename(tempFileName, fileName)
	
	
def UpdateVersionHeader(revision):
	versionHeader = 'version.h'	
	versionHeaderPath = os.path.join(CurrentPath, '../src/OpenInfraPlatform', versionHeader)
	
	newContent = ''
	pattern = "(?:static const int([\s\t]*)VERSION_REVISION)([\s\t]*)=(?:[\s]*)([0-9]{4})"
	with open(versionHeaderPath, "r") as versionFile:
		fileContent = versionFile.read()
		# Keep amount of spaces from before with \\1 and \\2
		newContent = re.sub(pattern, "static const int\\1VERSION_REVISION\\2= " + revision, fileContent)								
	
	ReplaceFile(versionHeaderPath, newContent)
	
	
def UpdateWixFile(revision):
	wixFile = 'installer.wxs'
	wixFilePath = os.path.join(CurrentPath, '', wixFile)
	
	newContent = ''
	pattern = 'define Version(?:\s+)=(?:\s+)\"([0-9]{1}\.[0-9]{1}\.[0-9]{1})(?:\.[0-9]{4})\"'
	with open(wixFilePath, "r") as wixFile:
		fileContent = wixFile.read()		
		newRev = '.' + str(revision)
		newContent = re.sub(pattern, 'define Version = \"\\1' + newRev + '"', fileContent)
	
	ReplaceFile(wixFilePath, newContent)
	

def UpdateServerVersion(revision):
	versionFile = 'current_version.txt'
	versionFilePath = os.path.join(CurrentPath, 'update', versionFile)
	
	newContent = ''
	pattern = '([0-9]{1}\.[0-9]{1}\.[0-9]{1})(?:\.[0-9]{4})'
	with open(versionFilePath, "r") as versionFile:
		fileContent = versionFile.read()
		newRev = '.' + str(revision)
		newContent = re.sub(pattern, '\\1' + newRev, fileContent)
		
	ReplaceFile(versionFilePath, newContent)
	
	
def main():	
	os.environ["LANGUAGE"] = "en_US.UTF-8"
	
	revision = DetermineCurrentRevison()
	if not revision:
		print("An error occurred. Canceling!")
		return 1
	else:
		print("New Revision is: " + revision)
	
	print("Updating Version.h file!")
	UpdateVersionHeader(revision)
	
	print("Updating WiX Installer file!")
	UpdateWixFile(revision)
	
	print("Updating CurrentVersion!")
	UpdateServerVersion(revision)
	
	return 0
	
	
if __name__ == '__main__':
	sys.exit(main())