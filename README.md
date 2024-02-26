# MusicMatch

MusicMatch is a social app that connects people with similar geek/taste in music whilelist showing you the profiles with whom your music taste matches the most.

## Getting Started

To get started with MusicMatch, follow these steps:

1. **Obtain a Unique Access Token from Spotify**: You can acquire a unique access token from Spotify's developer platform. This token is essential for accessing Spotify's API and retrieving music data. You can obtain this token manually using Postman by performing a GET request to the Spotify API. Once obtained, insert the access token into the code at:
   ```cpp
   const string TOKEN = "YOUR_ACCESS_TOKEN_HERE";

2. **Integrate the necessary libraries**:
   - [cpr library](https://github.com/libcpr/cpr) for making GET requests to the Spotify API.
   - [SQLite3](https://www.sqlite.org/index.html) for storing user data in a serverless database.
   
   Alternatively, you can use [vcpkg](https://github.com/microsoft/vcpkg) to easily install these libraries.

3. **Set up your development environment**:
   - MusicMatch was built and tested in Visual Studio with the above mentioned C++ libraries.
   - Manually integrate these libraries into your Visual Studio project.
