import React from 'react';
import { FaBars } from 'react-icons/fa'


export default function Navbar(){
    return(
        <nav>
            <img src= {(require("../images/bnb.png"))} alt="" />
            <FaBars className='bars'/> 
            
            
        </nav>
    )
}
