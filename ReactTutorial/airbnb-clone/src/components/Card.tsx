import React from 'react';
import { FaStar } from 'react-icons/fa';

export default function Card(props){
          // img = "Katie.png"
          // rating = {5.0}
          // reviewCount = {6}
          // country = "United States"
          // title = "Life Lessons with Katie Zaferes"
          // price = {136}
    return(
        <section className='card'>
            <img src={require(`../images/${props.img}`)} className='katie' alt="help" />
            <div className='card-stats'>
                <FaStar className='star' />
                <span>{props.rating} </span>
                <span className='gray'>({props.reviewCount}) • </span>
                <span className='gray'>{props.country}</span>
            </div>
            <p>{props.title}</p>
            <p> <span className='bold'> From ${props.price} </span> / person </p>
            
            {/* <img src={require("../images/wedding.png")} className="wedding" alt="" />
            <p></p>
            <img src={require("../images/mountain-bike.png")} className='bike' alt="" /> */}
        </section>
    )
}