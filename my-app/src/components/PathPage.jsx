import React from 'react'

export default function PathPage() {
  return (
    <>
        <div className="modal-box bg-primary max-w-[100vw] w-[70vw] h-[32.2vw] 2xl:h-[30.9vw]">
            <div className="card lg:card-side bg-base-100 shadow-xl">
            {/* <figure>
                <Image src={glasses_wall_pic} className='w-[35vw] h-[29.03vw]'></Image>
            </figure> */}
                <div className="card-body">
                        <div className="modal-action flex flex-col justify-center mt-[0] 2xl:mt-[3vw]">
                            Path Page
                        </div>
                </div>
            </div>
        </div>
        <form method="dialog" className="modal-backdrop">
            <button>close</button>
        </form>
    </>
  )
}
