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
        <Card/>
      </body>
    </div>
  );
}

export default Airbnb;
