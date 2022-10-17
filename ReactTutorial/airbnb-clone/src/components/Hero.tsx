import React from 'react';

export default function Hero(){
    return(
        <section className='hero'>
            <img src= {(require("../images/Hero.png"))} className='hero-photo' alt="" />
            <h1 className='hero-heading' >Online Experiences</h1>
            <p className='hero-p'>
                Join unique interative activities led by 
                one-of-a-kind hosts-all wihout leaving home
            </p>
        </section>
    )
}