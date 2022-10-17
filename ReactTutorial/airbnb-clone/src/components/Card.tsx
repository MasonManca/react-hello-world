import React from 'react';
import { FaStar } from 'react-icons/fa';

export default function Card(){
    return(
        <section className='card'>
            <img src={require("../images/Katie.png")} className='katie' alt="" />
            <div className='card-stats'>
                <FaStar className='star' />
                <span>5.0</span>
                <span className='gray'>(6) • </span>
                <span className='gray'>USA</span>
            </div>
            <p>Life Lessons with Katie Zaferes</p>
            <p> <span className='bold'> From $136 </span> / person </p>
            
            {/* <img src={require("../images/wedding.png")} className="wedding" alt="" />
            <p></p>
            <img src={require("../images/mountain-bike.png")} className='bike' alt="" /> */}
        </section>
    )
}