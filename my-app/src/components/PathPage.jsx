import React, { useState, useEffect } from 'react'
import MapWithRoute from "./Map.jsx"

export default function PathPage({curIdx, setCurIdx, curLocation, optPropData, setOptPropData}) {
  
  // Manage interval for updating curIdx
  const [hasMounted, setHasMounted] = useState(false);
  useEffect(() => {
    if (!hasMounted) {
        setHasMounted(true); // Mark the component as "mounted"
        return; // Skip the effect on initial load
    }
    
    if (curIdx >= optPropData.PrevNodes.length) return; // Stop interval if all nodes are processed

    // Handle Map Animation
    const intervalId = setTimeout(() => {
    
      setCurIdx((prevIdx) => {
        if (prevIdx < optPropData.PrevNodes.length) {
          return prevIdx + 1;
        } else {
          clearInterval(intervalId); // Clear the interval when reaching the end
          return prevIdx;
        }
      });
    }, 3000);

    return () => clearInterval(intervalId); // Cleanup on component unmount
  }, [curIdx, optPropData]);

  return (
    <>
        <div className="modal-box bg-primary max-w-[100vw] w-[80vw] h-[41vw] 2xl:h-[30.9vw]">
            <div className="card lg:card-side bg-base-100 shadow-xl">
                <div className="card-body">
                        {/* Render Space and Time Results */}
                        <div className="modal-action flex flex-col justify-center items-center mt-[0] 2xl:mt-[3vw]">
                            <div class="font-medium">
                                Found an Optimal Property in {curLocation.djk === true ? optPropData.djkTime : optPropData.AStrTime} seconds and {curLocation.djk === true ? optPropData.djkSpace : optPropData.AStrSpace} bytes using {curLocation.djk === true ? "Djkstra's" : "A-Star's"} Algorithm at {optPropData.lat}° Latitude and {optPropData.long}° Longitude 
                            </div>
                            <div class="font-semibold" style={{color: "#fb3030", margin: "inherit"}}>
                                {curLocation.djk === true ? "A-Star's" : "Djkstra's"} Algorithm took {curLocation.djk === true ? optPropData.AStrTime : optPropData.djkTime} seconds and {curLocation.djk === true ? optPropData.AStrSpace : optPropData.djkSpace} bytes
                            </div>
                        </div>
                        {/* Render MapWithRoute for the current node */}
                        {curIdx < optPropData.PrevNodes.length && (
                        <MapWithRoute
                            latStart={curLocation.lat}
                            longStart={curLocation.long}
                            latEnd={optPropData.PrevNodes[curIdx][0]}
                            longEnd={optPropData.PrevNodes[curIdx][1]}
                        />
                        )}
                        {/* Render final location map once the interval finishes */}
                        {curIdx === optPropData.PrevNodes.length && (
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