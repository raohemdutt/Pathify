import React from 'react'
import styles from "../index.css"
import Search from "./Search"
import Header from "./Header"
import HomeScreen from '../imgs/homepage_img.jpg'
import PathPage from './PathPage'

export default function Home({curLocation, setCurLocation}) {
    console.log(curLocation);
  return (
    <section class={`bg-cover bg-center h-[100vh] w-[100%] absolute`}  style={{ backgroundImage: `url(${HomeScreen})` }}>
        <Header></Header>
        <Search curLocation={curLocation} setCurLocation={setCurLocation}></Search>
        <dialog id="pathModal" className="modal"><PathPage curLocation={curLocation}></PathPage></dialog>
    </section>
  )
}
