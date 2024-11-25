import React from 'react'
import PathifyLogo from '../imgs/pathifyLogo.png'

export default function Header() {
  return (
    <section class="flex flex-row justify-between bg-white h-[7.38vh] fixed w-full z-[1] top-[0%] shadow-md">
      <div class="flex items-center ml-[2%]">
        <a href='/'>
          <img class="w-[3vw] h-[3vw] mr-[5px]" src={PathifyLogo}></img>
        </a>
        <a href='/'>
          <div class="text-black font-bold">Pathify - Saudi Arabia</div>
        </a>
      </div>
    </section>
  )
}
