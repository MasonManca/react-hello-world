import React from 'react';
import './App.css';
import Contact from './Components/Contact';
import images from './Components/images'; 


function App() {
  return (
    <div className="contacts">
    <Contact 
        image={images.mrWhiskerson}
        name="Mr. Whiskerson"
        phone="(212) 555-1234"
        email="mr.whiskaz@catnap.meow"
    />
    <Contact 
        image={images.felix}
        name="Fluffykins"
        phone="(212) 555-2345"
        email="fluff@me.com"
    />
    <Contact 
        image={images.fluffykins}
        name="Felix"
        phone="(212) 555-4567"
        email="thecat@hotmail.com"
    />
    <Contact 
        image={images.pumpkin}
        name="Pumpkin"
        phone="(0800) CAT KING"
        email="pumpkin@scrimba.com"
    />
</div>
  );
}

export default App;
