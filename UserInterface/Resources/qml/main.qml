import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    visible: true
	
	id: root
	
	property variant position : QtPositioning.coordinate(0, 153.1);
	property int zoomLevel : 8;
	property int minZoomLevel : map.minimumZoomLevel;
	property int maxZoomLevel : map.maximumZoomLevel;

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
		id: map
        anchors.fill: root
        plugin: mapPlugin
        zoomLevel: root.zoomLevel;
		center : root.position;
    }
}
