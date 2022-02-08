import { h } from "preact";
import { Router } from "preact-router";

import Header from "./header";

// Code-splitting is automated for `routes` directory
import Home from "../routes/home";
import Update from "../routes/update";
import Error from "../routes/error";

const App = () => (
  <div id="app">
    <Header />
    <Router>
      <Home path="/" />
      <Update path="/update" />
      <Error default />
    </Router>
  </div>
);

export default App;
