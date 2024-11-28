import React from 'react'

export default function Search(curLocation, setCurLocation) {

  // When submit button clicked setCurlocation Info
  function setLongLat() {
    let longs = [];
    let lats = [];
    for(let i=0; i<=360; i++) {
      if(i <= 180) {
        lats.push(
          <option>{i}</option>
        )
      }
      longs.push(
        <option>{i}</option>
      )
    }
    let output = [longs, lats];
    return output;
  }


  return (
    <div class="flex flex-col h-screen">
      <section class="flex items-center justify-evenly mt-[35vh]">
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              <span className="label-text">Start Location</span>
              <span className="label-text-alt">Coordinates</span>
            </div>
            <select className="select select-bordered">
              <option disabled selected>Pick Longitude</option>
              {setLongLat()[0]}
            </select>
            <select className="select select-bordered">
              <option disabled selected>Pick Latitude</option>
              {setLongLat()[1]}
            </select>
          </label>
        </div>
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              <span className="label-text">Search By</span>
              <span className="label-text-alt">Priority</span>
            </div>
            <select className="select select-bordered">
              <option disabled selected>Search Type</option>
              {/* For loop react component with options, should just pass in I think text to component, create state for this hashmap of text as well */}
              <option>Price</option>
              <option>Size</option>
            </select>
          </label>
        </div>
        {/* Conditionnaly render below based on if user picks sort by price or size */}
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              <span className="label-text">Target Price/Size</span>
              <span className="label-text-alt">$/sq. ft</span>
            </div>
            <select className="select select-bordered">
              <option disabled selected>Pick Target Price</option>
              {/* For loop react component with options, should just pass in I think text to component, create state for this hashmap of text as well */}
              <option>$100000</option>
              <option>$500000</option>
              <option>$750000</option>
            </select>
          </label>
        </div>
        </section>
      <section class="flex justify-center mt-[10vh]">
        <button className="btn btn-outline btn-primary w-[25vw]">Find Your Path -{`>`}</button>
      </section>
    </div>
  )
}
