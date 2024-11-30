import React, { useState } from 'react'
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

  return (
    <>
        <div className="modal-box bg-primary max-w-[100vw] w-[80vw] h-[41vw] 2xl:h-[30.9vw]">
            <div className="card lg:card-side bg-base-100 shadow-xl">
            {/* <figure>
                <Image src={glasses_wall_pic} className='w-[35vw] h-[29.03vw]'></Image>
            </figure> */}
                <div className="card-body">
                        <div className="modal-action flex flex-col justify-center items-center mt-[0] 2xl:mt-[3vw]">
                            <div class="font-medium">
                                Found an Optimal Property in {curLocation.djk === true ? optPropData.djkTime : optPropData.AStrTime} seconds using {curLocation.djk === true ? "Djkstra's" : "A-Star's"} Algorithm at {optPropData.lat}° Latitude and {optPropData.long}° Longitude 
                            </div>
                            <div class="font-semibold" style={{color: "#fb3030", margin: "inherit"}}>
                                {curLocation.djk === true ? "A-Star's" : "Djkstra's"} Algorithm took {curLocation.djk === true ? optPropData.AStrTime : optPropData.djkTime} seconds
                            </div>
                        </div>
                        {/* Lopp through all past nodes and insert embed, then isnert embed on last location */}
                        {/* <iframe width="600" height="450" style={{"border":0}} loading="lazy" allowfullscreen src="https://www.google.com/maps/embed/v1/place?q=place_id:ChIJQatg2-VAXz4RlsWijU8N6EQ&key=AIzaSyAxUna0O0shXH2e2Uz9fLaBTSY8oxIezsM"></iframe> */}
                        <MapWithRoute latStart={curLocation.lat} longStart={curLocation.long} latEnd={optPropData.lat} longEnd={optPropData.long}></MapWithRoute>
                </div>
            </div>
        </div>
        <form method="dialog" className="modal-backdrop">
            <button>close</button>
        </form>
    </>
  )
}
