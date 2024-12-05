# Pathify
DSA Project 3, Team 27

Created by Hemdutt Rao, Kai McFarlane, and Joshua Brunk

# Video Feature Overview
https://youtu.be/xJs6t-H56fE

# How To Run Pathify Locally 👨‍💻

## Initial Setup (Using CLion with cMake) 📖
1) Clone our repositry to your local machine.
2) Run ```npm install``` to install necessary packages to run code.
3) Install CLion on your device.

## Setting Up Front End 🎨
4) Run ```npm run start``` inside the my-app directory to start the front-end server on port [3000](http://localhost:3000/).

## Setting Up Backend 🛜
5) Open up a new project in CLion named Untitled2.
6) Copy and Paste all contents of the CLionImplementation folder in the repsotory into the main directory of your CLion project.
7) If asked, ```overwrite?```, click ```overwrite all```.
8) Hit green arrow in top right to run the server.
9) If error appears due to Asio package, to right hit debug, and hit install Asio with vcpg. This will allow CROW to run smoothly on port [8008](http://0.0.0.0:8008/).
Once all these steps are completed, Pathify is ready to go 🚀.

# Important Application Run Info ‼️
* Our API information and ports are already connected, so altering said ports in the backend or front-end file will mean it will need updates everywhere.
* Every User will have there own CMAKE file upon running the server. If you want to update this file, do not commit your changes to the debug folder to the repository.
* We use the url of our server for our request paramters, so changes to that url when fetching from the front-end will change the ouput of the server.


