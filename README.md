# Tetris

## Dependencies

OpenGL, SFML, BOOST (for program options)

```bash
sudo apt install -y mesa-common-dev mesa-utils freeglut3-dev 
sudo apt-get install libsfml-dev
sudo apt-get install libboost-all-dev
```

## Compilation

```bash
make
```

## Execution

Use the following command to show executions options :  

```bash
./output/tetris -h
```

## Controls

Here are the control for an AZERTY layout :
 
| Key                  | Usage                                                              |
|----------------------|--------------------------------------------------------------------|
| ESC                  | Pause the game Not available on multiplayer mode (server / client) |
| ARROW_UP             | Move the current tetramino away from your perspective              |
| ARROW_DOWN           | Move the current tetramino towards your perspective                |
| ARROW_LEFT           | Move the current tetramino to the left from your perspective       |
| ARROW_RIGHT          | Move the current tetramino to the right from your perspective      |
| Z                    | Rotate the current tetramino anticlockwise on the X axis           |
| Q                    | Rotate the current tetramino anticlockwise on the Y axis           |
| X                    | Rotate the current tetramino clockwise on the X axis               |
| D                    | Rotate the current tetramino clockwise on the Y axis               |
| A                    | Rotate the current tetramino anticlockwise on the Z axis           |
| E                    | Rotate the current tetramino clockwise on the Z axis               |
| MOUSE_CLICK_AND_DRAG | Move your perspective                                              |

## Utils

* [OpenGL](https://programminggems.wordpress.com/2019/11/27/getting-started-with-opengl-from-c-c/)
* [SFML](https://www.sfml-dev.org/index-fr.php)
* [BOOST](https://www.boost.org/)
