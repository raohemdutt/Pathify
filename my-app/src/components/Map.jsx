import React, { useState, useEffect, useRef} from "react";
import { GoogleMap, useLoadScript, useJsApiLoader, DirectionsRenderer } from "@react-google-maps/api";

export default function MapWithRoute({latStart, longStart, latEnd, longEnd}) {
  const [directionsResponse, setDirectionsResponse] = useState(null);

  // Your API key
  const apiKey = "AIzaSyDKiHa8mxW4mnv49WVgOSItbvNtYxHfTtc";

  console.log("API Key:", apiKey);

  // Coordinates of the locations
  const origin = { lat: latStart, lng: longStart }; // Example: New York City
  const destination = { lat: latEnd, lng: longEnd }; // Example: Los Angeles

  let isLoaded = true;

  // Load Google Maps script
  // const { isLoaded, loadError } = useJsApiLoader({
  //   googleMapsApiKey: apiKey,
  //   libraries: ["places"], // Load additional libraries if needed
  // });

  // if (loadError) {
  //   console.error("Google Maps API load error:", loadError);
  //   return <div>Error loading maps.</div>;
  // }

  // console.log("isLoaded:", isLoaded);

  // // Calculate the route
  // const calculateRoute = async () => {
  //   if (!window.google) return;

  //   const directionsService = new window.google.maps.DirectionsService();

  //   try {
  //     const results = await directionsService.route({
  //       origin,
  //       destination,
  //       travelMode: window.google.maps.TravelMode.DRIVING, // Options: DRIVING, WALKING, BICYCLING, TRANSIT
  //     });
  //     setDirectionsResponse(results);
  //   } catch (error) {
  //     console.error("Error calculating route:", error);
  //   }
  // };

  // // Initialize map and calculate route when loaded
  // React.useEffect(() => {
  //   if (isLoaded) calculateRoute();
  //   console.log("isLoaded:", isLoaded);
  // }, [isLoaded]);

  // if (!isLoaded) {
  //   return <div>Loading...</div>;
  // }

  // return (
  //   <GoogleMap
  //     center={origin}
  //     zoom={5}
  //     mapContainerStyle={{ width: "100%", height: "500px" }}
  //   >
  //     {directionsResponse && <DirectionsRenderer directions={directionsResponse} />}
  //   </GoogleMap>
  // );

  return <div>{isLoaded ? "Maps Loaded!" : "Loading Maps..."}</div>;
};

// import React from "react";
// import { GoogleMap, useLoadScript } from "@react-google-maps/api";

// const MapWithRoute = () => {
//   const { isLoaded } = useLoadScript({
//     googleMapsApiKey: "YOUR_API_KEY",
//     libraries: ["places"],
//   });

//   if (!isLoaded) return <div>Loading...</div>;

//   return (
//     <GoogleMap
//       center={{ lat: 40.712776, lng: -74.005974 }} // Example: New York City
//       zoom={10}
//       mapContainerStyle={{ width: "100%", height: "500px" }}
//     />
//   );
// };

// export default MapWithRoute;