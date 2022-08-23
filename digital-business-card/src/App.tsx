/* eslint-disable jsx-a11y/anchor-is-valid */
import React from 'react';
import './App.css';
import { FaEnvelope, FaGithub, FaLinkedin, FaInstagram } from "react-icons/fa";


export function CardFooter(){
  return(
    <div className='footer-icons'>
    <FaGithub className='github-icon'/>
    <FaInstagram/>
    </div>
  )
}

export function CardHeader() {
  return (
    <header >
        <img className='profile' src= {require("./images/profile-photo.JPG")} alt="" />
        <div className='info'>
          <h3>Mason Manca</h3>
          <h5>Student at Gonzaga University</h5>
          <a href="#">MasonManca.website</a>
          <div className='christ'>
          <button className='Email'> <FaEnvelope className='email-icon'/> Email</button>
          <button className='Linked'> <FaLinkedin className='linked-icon'/> Linkedin</button> 
          </div>
          <h4>About</h4>
          <p>Lorem ipsum dolor sit amet consectetur adipisicing elit. Aut, tempore. Lorem ipsum dolor sit amet consectetur adipisicing elit. Nesciunt, tempore vel voluptates suscipit voluptatem corrupti.</p>
          <h4>Interests</h4>
          <p>Lorem ipsum dolor sit amet consectetur adipisicing elit. Molestiae, dolorem. Lorem ipsum dolor sit, amet consectetur adipisicing elit. Vel voluptates ullam nam. Eligendi, tempore voluptas.</p>
         </div>
         <div className='test'></div>
      </header>
  )
}

function App() {
  return (
    <div className="Card">
      <div className='secret'></div>

      <header className="card-header">
      <CardHeader/>
      </header>

      <footer>
        <nav>
          <CardFooter/>
        </nav>
      </footer>
    </div>
  );
}

export default App;