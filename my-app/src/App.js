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
      <Home curLocation={curLocation} setCurLocation={setCurLocation}></Home>
    </>
  );
}

export default App;
