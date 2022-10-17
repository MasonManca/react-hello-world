import React from 'react';
import './App.css';


export function ReactHeader() {
  return(
    <nav>
      <img src={require("./images/react-logo.png")} alt="" />
      <h3>ReactFacts</h3>
      <h4 className='course'>React Course - Project 1</h4>
    </nav>
  )
}

export function ReactBody() {
  return(
    <div className='funFacts'>
      <h1>Fun facts about React</h1>
      <ul>
        <li>Was released in 2013</li>
        <li>Was originially created by Jordan Walke</li>
        <li>Has well over 100k stars on GitHub</li>
        <li>Maintained by FaceBook</li>
        <li>Powers thousands of enterprise apps, including mobile apps</li>
      </ul>
    </div>  
  );
}

function App() {
  return (
    <div className="App">
      <header className="App-header">   
      </header>
      <ReactHeader/>
      <body>
      <ReactBody/>
      </body>
    </div>
  );
}

export default App;
