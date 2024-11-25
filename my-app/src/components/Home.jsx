import React from 'react'
import styles from "../index.css"
import Search from "./Search"
import Header from "./Header"

export default function Home() {
  return (
    <section class="bg-amber-50 h-[100vh] w-[100%] absolute">
        <Header></Header>
        <Search></Search>
        {/* <div class="text-black">Home</div>
        <button className="btn">Daisy UI/Tailwind Button</button> */}
    </section>
  )
}
