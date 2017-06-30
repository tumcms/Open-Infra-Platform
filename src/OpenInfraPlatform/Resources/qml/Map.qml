import QtQuick 2.6
import QtPositioning 5.6
import QtLocation 5.6

Item {
    id: root
	
	property variant position : QtPositioning.coordinate(0, 153.1);
	property int zoomLevel : 8;
	property int minZoomLevel : map.minimumZoomLevel;
	property int maxZoomLevel : map.maximumZoomLevel;
	
	Plugin {
		id: osmPlugin;
		name: "osm";
		//specify plugin parameters if necessary
		//PluginParameter {...}
		//PluginParameter {...}
		//...
	}

	Map {
		id: map
		anchors.fill: root;
		plugin: osmPlugin;
		zoomLevel: root.zoomLevel;
		center : root.position;
		
		MapQuickItem {
			id: marker;
			coordinate : root.position;
			anchorPoint.x: markerRect.width / 2;
			anchorPoint.y: markerRect.height / 2;
			sourceItem: Rectangle {
				id: markerRect;
				 width: 30;
				 height: width;
				 color: "#800000FF";
				 radius: width / 2;
			}
		}
	}
}