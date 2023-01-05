import React from "react";
import "./App.css";
import Navbar from "./components/Navbar";
import Hero from "./components/Hero";
import Card from "./components/Card";



function Airbnb() {
  return (
    <div className="airbnb-app">
      <header className="App-header">
        <Navbar/>
      </header>
      <body>
        <Hero/>
         <Card
          img = "Katie.png"
          rating = "5.0"
          reviewCount = {6}
          country = "United States"
          title = "Life Lessons with Katie Zaferes"
          price = {136}
        /> 
      </body>
    </div>
  );
}

export default Airbnb;
