import React, {useState} from 'react'
import styles from "../index.css"
import Search from "./Search"
import Header from "./Header"
import HomeScreen from '../imgs/homepage_img.jpg'
import PathPage from './PathPage'

export default function Home({curLocation, setCurLocation, optPropData, setOptPropData}) {
    const [pathCurIdx, setPathCurIdx] = useState(0);
    console.log(curLocation);
  return (
    <section class={`bg-cover bg-center h-[100vh] w-[100%] absolute`}  style={{ backgroundImage: `url(${HomeScreen})` }}>
        <Header></Header>
        <Search setPathCurIdx={setPathCurIdx} curLocation={curLocation} setCurLocation={setCurLocation} optPropData={optPropData} setOptPropData={setOptPropData}></Search>
        <dialog id="pathModal" className="modal"><PathPage curIdx={pathCurIdx} setCurIdx={setPathCurIdx} curLocation={curLocation} optPropData={optPropData} setOptPropData={setOptPropData}></PathPage></dialog>
    </section>
  )
}
