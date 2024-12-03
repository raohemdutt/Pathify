const express = require("express");
const cors = require("cors");

//RUN node server.js to start server

const app = express();
const PORT = 5000;

// Middleware
app.use(cors()); // Allows requests from React (on a different port)
app.use(express.json()); // Parses JSON request bodies

// Example data (simulate c++ from josh)
let exampleData = [
{
    long: 23.5,
    lat: 34.5,
    name: "Dubai",
    djkTime: 1.3,
    AStrTime: 1.6,
    PrevNodes: [[24.5, 34.5],[23.4,34.5],[24.6, 56.4],[34.2,53.6],[35.4, 64.3]]
},
];

const naem = "j";

// GET endpoint
app.get(`/process?lat=${naem}&lng=${naem}&price=${naem}`, (req, res) => {
//   res.json(exampleData); // Send the data as JSON
//   var long = exampleData.path[]
});

// Start the server
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
