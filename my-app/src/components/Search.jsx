import React, { useState } from 'react'

export default function Search({setPathCurIdx, curLocation, setCurLocation, optPropData, setOptPropData}) {
  const [isLoading, setLoading] = useState(false);

  // When submit button clicked setCurlocation Info
  function setLongLat() {
    let longs = [];
    let lats = [];
    for(let i=0; i<=180; i++) {
      if(i <= 90) {
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

  function setPrice() {
    let prices = [];
    for(let i=0; i<=10000000; i+=10000) {
      prices.push(
        <option>${i}</option>
      )
    }
    return prices;
  }

  function setArea() {
    let area = [];
    for(let i=0; i<=100000; i+=250) {
      area.push(
        <option>{i}ft²</option>
      )
    }
    return area;
  }

  function renderPriceArea() {
    return curLocation.priceBased ? setPrice() : setArea();
  }

  const handlePriceAreaChange = (event) => {
    const value = event.target.value;
    if(value === "Price") {
      setCurLocation((prevState) => ({
        ...prevState,
        priceBased: true
      }));
    }
    else {
      setCurLocation((prevState) => ({
        ...prevState,
        priceBased: false
      }));
    }
  }

  const handleLatChange = (event) => {
    const value = event.target.value;
    setCurLocation((prevState) => ({
      ...prevState,
      lat: parseFloat(value)
    }));
  }

  const handleLongChange = (event) => {
    const value = event.target.value;
    setCurLocation((prevState) => ({
      ...prevState,
      long: parseFloat(value)
    }));
  }

  const handlePriceAreaValChange = (event) => {
    const value = event.target.value;
    setCurLocation((prevState) => ({
      ...prevState,
      target: value
    }));
  }

  const handleAlgoChange = (event) => {
    const value = event.target.value;
    if(value == "Djk") {
      setCurLocation((prevState) => ({
        ...prevState,
        djk: true
      }));
    }
    else {
      setCurLocation((prevState) => ({
        ...prevState,
        djk: false
      }));
    }
  }

  const handleDirChange = (event, dir) => {
    // const value = event.target.value;
    if(dir === "North") {
      if(curLocation.lat < 0) {
        setCurLocation((prevState) => ({
          ...prevState,
          lat: Math.abs(curLocation.lat),
          dirNS: "North"
        }));
      }
      else {
        setCurLocation((prevState) => ({
          ...prevState,
          dirNS: "North"
        }));
      }
    }
    else if(dir === "South") {
      if(curLocation.lat > 0) {
        setCurLocation((prevState) => ({
          ...prevState,
          lat: -Math.abs(curLocation.lat),
          dirNS: "South"
        }));
      }
      else {
        setCurLocation((prevState) => ({
          ...prevState,
          lat: curLocation.lat,
          dirNS: "South"
        }));
      }
    }
    else if(dir === "West") {
      if(curLocation.long > 0) {
        setCurLocation((prevState) => ({
          ...prevState,
          long: -Math.abs(curLocation.long),
          dirWE: "West"
        }));
      }
      else {
        setCurLocation((prevState) => ({
          ...prevState,
          long: curLocation.long,
          dirWE: "West"
        }));
      }
    }
    else if (dir == "East") {
      if(curLocation.long < 0) {
        setCurLocation((prevState) => ({
          ...prevState,
          
          long: Math.abs(curLocation.long),
          dirWE: "East"
        }));
      }
      else {
        setCurLocation((prevState) => ({
          ...prevState,
          long: curLocation.long,
          dirWE: "East"
        }));
      }
    }
  }

  const findPathButton = async () => {
    setLoading(true);
    setPathCurIdx(0);
    // Should put laoding wheel here
    const response = await fetch(`http://0.0.0.0:8008/process?lat=${curLocation.lat}&lng=${curLocation.long}&price=${curLocation.target}`);
    // A star gives three nodes with end being target
    const data = await response.json();
    console.log(data)
    console.log("Data on line 178 should be above this line");
    setLoading(false)
    setOptPropData((prevState) => ({
      ...prevState,
      long: data.path[data.path.length-1].longitude,
      lat: data.path[data.path.length-1].latitude,
      djkTime: 0, // Waiting from Josh JSON
      AstrTime: 0, // Waiting from Josh JSON
      target: 10.00, // Waiting from Josh JSON
      PrevNodes: [[data.path[0].longitude,data.path[0].latitude],[data.path[1].longitude,data.path[1].latitude]],
    }));
    console.log(optPropData);
    document.getElementById('pathModal').showModal()
  }

  const callLoadingScreen = () => {
    return <div class="fixed inset-0 flex items-center justify-center ">
              <span className="w-[8vw] loading loading-spinner loading-lg"></span>
          </div>
  }

  console.log(curLocation);

  // For some reason removing labe causes err, may have to use desginated Daisy UI component
  return (
    <>
      {isLoading ? 
      callLoadingScreen()
      : 
      <div class="flex flex-col h-screen items-center">
      <section class="flex items-center justify-evenly rounded-md w-[85%] bg-[#f0ffffc9] mt-[25vh] h-[45vh]">
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              {/* <span className="label-text">Start Location</span> */}
              <span className="label-text-alt">Coordinates Only</span>
            </div>
            <input type="text" placeholder="Longitude" className="input input-bordered w-full max-w-xs" onChange={handleLongChange} />
            {/* <select className="select select-bordered" onChange={handleLongChange}>
              <option disabled selected>Pick Longitude</option>
              {setLongLat()[0]}
            </select> */}
          <section class="mb-[2vh]">
            <div className="form-control">
            <label className="label cursor-pointer">
                <span className="label-text">West</span>
                <input type="radio" name="radio-10" className="radio checked:bg-red-500"  onChange={(e) => handleDirChange(e, "West")} defaultChecked/>
              </label>
            </div>
            <div className="form-control">
              <label className="label cursor-pointer">
                <span className="label-text">East</span>
                <input type="radio" name="radio-10" className="radio checked:bg-blue-500"  onChange={(e) => handleDirChange(e, "East")}/>
              </label>
          </div>
          </section>
            <div className="label">
              {/* <span className="label-text">Start Location</span> */}
              <span className="label-text-alt">Coordinates Only</span>
            </div>
            <input type="text" placeholder="Latitude" className="input input-bordered w-full max-w-xs" onChange={handleLatChange} />
            {/* <select className="select select-bordered" onChange={handleLatChange}>
              <option disabled selected>Pick Latitude</option>
              {setLongLat()[1]}
            </select> */}
            <section>
            <div className="form-control">
            <label className="label cursor-pointer">
                <span className="label-text">North</span>
                <input type="radio" name="radio-11" className="radio checked:bg-red-500" onChange={(e) => handleDirChange(e, "North")} defaultChecked />
            </label>
            </div>
            <div className="form-control">
              <label className="label cursor-pointer">
                <span className="label-text">South</span>
                <input type="radio" name="radio-11" className="radio checked:bg-blue-500"  onChange={(e) => handleDirChange(e, "South")}/>
              </label>
          </div>
          </section>
          </label>
        </div>
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              {/* <span className="label-text">Search By</span>
              <span className="label-text-alt">Priority</span> */}
            </div>
            <select className="select select-bordered" onChange={handlePriceAreaChange}>
              <option disabled selected>Search By</option>
              {/* For loop react component with options, should just pass in I think text to component, create state for this hashmap of text as well */}
              <option value="Price">Price</option>
              <option value="Size">Size</option>
            </select>
            <select className="select select-bordered" onChange={handleAlgoChange}>
              <option disabled selected>Algorithm</option>
              {/* For loop react component with options, should just pass in I think text to component, create state for this hashmap of text as well */}
              <option value="Djk">Djkstras</option>
              <option value="A-Star">A-Star</option>
            </select>
          </label>
        </div>
        {/* Conditionnaly render below based on if user picks sort by price or size */}
        <div class="w-[17vw]">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              {/* <span className="label-text">Target Price/Size</span>
              <span className="label-text-alt">$/sq. ft</span> */}
            </div>
            <div className="label">
              {/* <span className="label-text">Start Location</span> */}
              <span className="label-text-alt">Optimal Value</span>
            </div>
            <select className="select select-bordered"  onChange={handlePriceAreaValChange}>
              <option disabled selected>Pick Target {curLocation.priceBased === true ? "Price" : "Area"}</option>
              {/* For loop react component with options, should just pass in I think text to component, create state for this hashmap of text as well */}
              {renderPriceArea()}
            </select>
          </label>
        </div>
        </section>
      <section class="flex justify-center mt-[10vh]">
        <button onClick={()=>findPathButton()} className="btn btn-primary text-white w-[25vw]">Find Your Path -{`>`}</button>
      </section>
    </div>
    }
    </>
  )
}
