import React, { useEffect, useRef } from "react";

const MapWithRoute = ({ latStart, longStart, latEnd, longEnd }) => {
  const mapRef = useRef(null); // Reference to the map container

  useEffect(() => {
    // Ensure the Google Maps API is loaded
    if (!window.google) {
      console.error("Google Maps API not loaded");
      return;
    }

    // Initialize the map
    const map = new window.google.maps.Map(mapRef.current, {
      center: { lat: latStart, lng: longStart }, // Centered at the first location
      zoom: 4, // Adjust zoom level as needed
    });

    // Add markers for both locations
    const markers = [
      { position: { lat: latStart, lng: longStart }, label: "Start" },
      { position: { lat: latEnd, lng: longEnd }, label: "End" },
    ];

    markers.forEach(({ position, label }) => {
      new window.google.maps.Marker({
        position,
        map,
        label,
      });
    });

    // Optional: Add a polyline to connect the markers
    const routePath = new window.google.maps.Polyline({
      path: [
        { lat: latStart, lng: longStart },
        { lat: latEnd, lng: longEnd },
      ],
      geodesic: true,
      strokeColor: "#FF0000",
      strokeOpacity: 1.0,
      strokeWeight: 2,
    });
    routePath.setMap(map);
  }, [latStart, longStart, latEnd, longEnd]);

  return (
    <div ref={mapRef} style={{ width: "100%", height: "53vh" }} id="google-map" class=""></div>
  );
};

export default MapWithRoute;
