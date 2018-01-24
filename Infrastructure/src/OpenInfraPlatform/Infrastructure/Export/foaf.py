import rdflib as rd
from rdflib.namespace import RDF
from rdflib.namespace import FOAF

joe = rd.URIRef("http://www.example.org/~joe/contact.rdf#joesmith")
joeEmail = rd.URIRef('mailto:joe.smith@example.org')
joeHome = rd.URIRef('http://www.example.org/~joe/')
joeFamily = rd.Literal('Smith')
joeName = rd.Literal('Joe')

g = rd.Graph()

g.bind('foaf', FOAF, False)

print(RDF.type)
print(FOAF.Person)
g.add((joe, RDF.type, FOAF.Person)) # <---- HERE...
g.add((joe, FOAF.mbox, joeEmail))
g.add((joe, FOAF.homepage, joeHome))
g.add((joe, FOAF.family_name, joeFamily))
g.add((joe, FOAF.givenname, joeName))

fp = open('outfile.rdf','wb')
fp.write(g.serialize(format='pretty-xml'))  # <---- ...AND HERE
fp.close()