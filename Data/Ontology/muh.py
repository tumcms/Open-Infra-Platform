import rdflib

test_file = "/some/file"

uri=RDF.Uri(string="file:"+test_file)

parser=RDF.Parser(name="turtle")
if parser is None:
  raise Exception("Failed to create RDF.Parser raptor")

count=0
for s in parser.parse_as_stream(uri,uri):
  count=count+1

print("Parsing added",count,"statements")