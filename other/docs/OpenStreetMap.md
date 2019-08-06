# OpenStreetMap Import #

The Website [https://www.openstreetmap.org/export](https://www.openstreetmap.org/export) can be used to export OpenStreetMap in the file format OSM XML.

The exported OSM XML looks something like this:
    
    <?xml version="1.0" encoding="UTF-8"?>
    <osm version="0.6" generator="CGImap 0.3.3 (7048 thorn-02.openstreetmap.org)" copyright="OpenStreetMap and contributors" attribution="http://www.openstreetmap.org/copyright" license="http://opendatacommons.org/licenses/odbl/1-0/">
     <bounds minlat="48.1407000" minlon="11.5529000" maxlat="48.1581000" maxlon="11.5913000"/>
     <node id="361780" visible="true" version="6" changeset="7837892" timestamp="2011-04-11T21:43:40Z" user="Michael Forster" uid="64536" lat="48.1426236" lon="11.5602278"/>
     <node id="361802" visible="true" version="5" changeset="10762121" timestamp="2012-02-22T19:08:27Z" user="Peter14" uid="13832" lat="48.1502601" lon="11.5583653">
      <tag k="highway" v="traffic_signals"/>
     </node>
     < id="3node61774" visible="true" version="15" changeset="30663933" timestamp="2015-04-30T15:59:21Z" user="Anoniman" uid="354141" lat="48.1406916" lon="11.5678080">
      <tag k="TMC:cid_58:tabcd_1:Class" v="Point"/>
      <tag k="TMC:cid_58:tabcd_1:Direction" v="negative"/>
      <tag k="TMC:cid_58:tabcd_1:LCLversion" v="9.00"/>
      <tag k="TMC:cid_58:tabcd_1:LocationCode" v="35364"/>
      <tag k="TMC:cid_58:tabcd_1:NextLocationCode" v="27930"/>
      <tag k="TMC:cid_58:tabcd_1:PrevLocationCode" v="27929"/>
     </node>
     <node id="361791" visible="true" version="5" changeset="26490251" timestamp="2014-11-01T20:25:32Z" user="heilbron" uid="78613" lat="48.1469127" lon="11.5588963"/>
     <node id="363205" visible="true" version="3" changeset="8444587" timestamp="2011-06-15T07:28:06Z" user="Broky" uid="68974" lat="48.1530836" lon="11.5516384"/>
     <node id="363204" visible="true" version="5" changeset="24127160" timestamp="2014-07-13T19:02:26Z" user="Mloni" uid="367380" lat="48.1552132" lon="11.5524848">
      <tag k="highway" v="traffic_signals"/>
     </node>
     <node id="363192" visible="true" version="3" changeset="8921564" timestamp="2011-08-04T17:20:51Z" user="ToniE" uid="8748" lat="48.1476224" lon="11.5520490"/>
     <node id="363187" visible="true" version="10" changeset="10718541" timestamp="2012-02-18T10:26:34Z" user="Peter14" uid="13832" lat="48.1434870" lon="11.5575184"/>
     <node id="363179" visible="true" version="6" changeset="8780609" timestamp="2011-07-20T17:12:36Z" user="bahnpirat" uid="13203" lat="48.1408871" lon="11.5615991">
      <tag k="railway" v="switch"/>
      <tag k="ref" v="54"/>
     </node>
     ...
 
From this data an alignment can be reconstructed.
 
 
See also:
[http://wiki.openstreetmap.org/wiki/3D_development](http://wiki.openstreetmap.org/wiki/3D_development)
[http://www.akgsoftware.de/fileadmin/user_upload/ePublishing/PROFILE_01_2014/files/assets/basic-html/page14.html](http://www.akgsoftware.de/fileadmin/user_upload/ePublishing/PROFILE_01_2014/files/assets/basic-html/page14.html)
[https://www.openstreetmap.org/export#map=16/48.1494/11.5721](https://www.openstreetmap.org/export#map=16/48.1494/11.5721)