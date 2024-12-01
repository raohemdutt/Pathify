import React, { useState, useEffect } from 'react'
import MapWithRoute from "./Map.jsx"

export default function PathPage({curLocation}) {

  const [optPropData, setOptPropData] = useState({
    long: 0,
    lat: 0,
    name: 0,
    djkTime: 0,
    AStrTime: 0,
    PrevNodes: [[24.5, 34.5],[23.4,34.5],[24.6, 56.4],[34.2,53.6],[35.4, 64.3]]
  });  

  const [curIdx, setCurIdx] = useState(0);

  // Manage interval for updating curIdx
  useEffect(() => {
    
    if (curIdx >= optPropData.PrevNodes.length) return; // Stop interval if all nodes are processed

    const intervalId = setTimeout(() => {
      setCurIdx((prevIdx) => {
        if (prevIdx <= optPropData.PrevNodes.length - 1) {
          return prevIdx + 1;
        } else {
          clearInterval(intervalId); // Clear the interval when reaching the end
          return prevIdx;
        }
      });
    }, 3000);

    return () => clearInterval(intervalId); // Cleanup on component unmount
  }, [curIdx, optPropData.PrevNodes.length]);

  return (
    <>
        <div className="modal-box bg-primary max-w-[100vw] w-[80vw] h-[41vw] 2xl:h-[30.9vw]">
            <div className="card lg:card-side bg-base-100 shadow-xl">
                <div className="card-body">
                        <div className="modal-action flex flex-col justify-center items-center mt-[0] 2xl:mt-[3vw]">
                            <div class="font-medium">
                                Found an Optimal Property in {curLocation.djk === true ? optPropData.djkTime : optPropData.AStrTime} seconds using {curLocation.djk === true ? "Djkstra's" : "A-Star's"} Algorithm at {optPropData.lat}° Latitude and {optPropData.long}° Longitude 
                            </div>
                            <div class="font-semibold" style={{color: "#fb3030", margin: "inherit"}}>
                                {curLocation.djk === true ? "A-Star's" : "Djkstra's"} Algorithm took {curLocation.djk === true ? optPropData.AStrTime : optPropData.djkTime} seconds
                            </div>
                        </div>
                        {/* Render MapWithRoute for the current node */}
                        {curIdx < optPropData.PrevNodes.length && (
                        <MapWithRoute
                            latStart={optPropData.PrevNodes[curIdx][0]}
                            longStart={optPropData.PrevNodes[curIdx][1]}
                            latEnd={optPropData.lat}
                            longEnd={optPropData.long}
                        />
                        )}
                        {/* Render final location map once the interval finishes */}
                        {curIdx === optPropData.PrevNodes.length-1 && (
                        <MapWithRoute
                            latStart={curLocation.lat}
                            longStart={curLocation.long}
                            latEnd={optPropData.lat}
                            longEnd={optPropData.long}
                        />
                        )}
                </div>
            </div>
        </div>
        <form method="dialog" className="modal-backdrop">
            <button>close</button>
        </form>
    </>
  )
}
