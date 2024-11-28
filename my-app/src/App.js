import './App.css';
import styles from "./index.css"
import { useState } from 'react';
import Home from './components/Home';

function App() {



  const [curLocation, setCurLocation] = useState({
    CurLocation: {
      long: 10.0,
      lat: 10.0,
      priceBased: true,
      target: 10.00,
    }
  });

  return (
    <>
      <Home curLocation={curLocation} setCurLocation={setCurLocation}></Home>
    </>
  );
}

export default App;
