import React from 'react'
import styles from "../index.css"
import Search from "./Search"
import Header from "./Header"
import HomeScreen from '../imgs/homepage_img.jpg'

export default function Home({curLocation, setCurLocation}) {
    console.log(curLocation);
  return (
    <section class={`bg-cover bg-center h-[100vh] w-[100%] absolute`}  style={{ backgroundImage: `url(${HomeScreen})` }}>
        <Header></Header>
        <Search curLocation={curLocation} setCurLocation={setCurLocation}></Search>
        {/* <div class="text-black">Home</div>
        <button className="btn">Daisy UI/Tailwind Button</button> */}
    </section>
  )
}
