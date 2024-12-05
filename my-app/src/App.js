import './App.css';
import styles from "./index.css"
import axios from "axios";
import { useEffect, useState } from 'react';
import Home from './components/Home';

function App() {
  // User Inputted Data
  const [curLocation, setCurLocation] = useState({
      long: 45.0792,
      dirWE: "East",
      dirNS: "North",
      lat: 23.8859,
      priceBased: true,
      target: 10.00,
      djk: true,
    }
  );

  // C++ Algorithm Return data
  const [optPropData, setOptPropData] = useState({
    long: 0,
    lat: 0,
    name: 0,
    djkTime: 0,
    AStrTime: 0,
    djkSpace: 0,
    AStrSpace: 0,
    PrevNodes: [[24.5, 34.5],[23.4,34.5],[24.6, 56.4],[34.2,53.6],[35.4, 64.3]] // First is latitude and second is longitude
  });  

  return (
    <>
      <Home curLocation={curLocation} setCurLocation={setCurLocation} optPropData={optPropData} setOptPropData={setOptPropData}></Home>
    </>
  );
}

export default App;