import './App.css';
import styles from "./index.css"
import axios from "axios";
import { useEffect, useState } from 'react';
import Home from './components/Home';

function App() {
  const [curLocation, setCurLocation] = useState({
      long: 10.0,
      dirWE: "West",
      dirNS: "North",
      lat: 10.0,
      priceBased: true,
      target: 10.00,
      djk: true,
    }
  );

  const [optPropData, setOptPropData] = useState({
    long: 0,
    lat: 0,
    name: 0,
    djkTime: 0,
    AStrTime: 0,
    PrevNodes: [[24.5, 34.5],[23.4,34.5],[24.6, 56.4],[34.2,53.6],[35.4, 64.3]]
  });  

  const getAlgoData = async () => {
    try {
      const response = await axios.get("http://localhost:5000/api/data");
      setCurLocation(response.data);
    }
    catch (err) {
      console.err("Failed fethcing c++ data from algorithms");
    }
  }

  // Uncomment below and start server when c++ code ready with CROW
  // useEffect(() => {
  //   getAlgoData();
  // }, [])

  return (
    <>
      <Home curLocation={curLocation} setCurLocation={setCurLocation} optPropData={optPropData} setOptPropData={setOptPropData}></Home>
    </>
  );
}

export default App;
