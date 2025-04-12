# SpaceTraders C++ Client

This is a C++ client for the [SpaceTraders API](https://spacetraders.io/), built with ImGui for a graphical interface. It allows interaction with the game's backend systems, such as agents, contracts, ships, and navigation.

It is the counter-part to my [SpaceTraders PHP Implementation](https://github.com/leon-witlif/space-traders)

## Project setup

Create a `config.json` file with the following layout

```json
{
    "accountToken": "<Your account token>",
    "agents": [
        {
            "name": "MyAgent1",
            "token": "<Your agent token>"
        }
    ]
}
```

Information on how to obtain the tokens can be found here: https://spacetraders.io/quickstart/new-game

## Requirements / Dependencies

- C++17 compatible compiler
- [OpenSSL](https://www.openssl.org/)
- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [Premake5](https://premake.github.io/)

## Building the project

### Linux

1. `vendor/bin/premake5 gmake`
2. `make`

### Windows

1. Set up the following environment variables
   1. `OPENSSL_ROOT`
2. `vendor\bin\premake5 vs2022`
3. Build the project

## Running the project

### GUI

Run the binary/executable found in `bin/SpaceTraders/<build-configuration>/`

### Contract Runner (WIP)

Run the binary/executable found in `bin/Contract/<build-configuration>/`
