import React from "react";
import { FaEnvelope, FaPhone } from "react-icons/fa";

function Contact({image,name,phone,email}){
    return(
        <div className="contact-card">
            <img src={image} className='fun' alt="photo" />
            <h3>{name}</h3>
            <div className="info-group">
                <FaPhone/>
                <p>{phone}</p>
            </div>
            <div className="info-group">
                <p> <FaEnvelope/>{email}</p>
            </div>
        </div>
    )
}
export default Contact;