# Cub3d
_This project has been created as part of the 42 curriculum by jose-ara and romorale._

![Gameplay](https://github.com/ocxpke/cub3D/blob/develop/rosa/key_test/gp.gif)

## Description
This project is inspired by the 3D game Wolfenstein, which is considered the first FPS ever created.

The objective is to create a game with a 3d view using the raycasting technique.
With raycasting, you simulate the view by projecting rays from the player's position to calculate the depth and perspective.
The environment in the first-person view will be generated from a 2d map grid.
This grid must be in a file in .cub format, taken by the program as a first argument.
It will only execute the game if the file is valid.

### **A valid file should only contain the following elements:**

<ins>4 wall texture type identifiers</ins> (NO, SO, WE, EA) followed by 1 space and then the path to the texture image file. Any missing, repeated or wrong file types will make the file invalid. It must be in this format and none other.
Here is an example of valid texture paths:
```
NO ./path_to_the_north_texture

SO ./path_to_the_south_texture

WE ./path_to_the_west_texture

EA ./path_to_the_east_texture
```
<ins>2 floor and ceiling color value identifiers</ins> (F, C) followed by 1 space and then the RGB values. They must range from 0 to 255, each separated by a comma. Any missing, repeated or wrong identifiers or color values will make the file invalid. It must be in this format and none other.
Here is an example of valid texture paths:
```
F 220,100,0

C 225,30,0
```
<ins>1 map grid</ins> which always has to be the last element in the file. It must contain only the following characters:

- '0' for empty spaces
- '1' for walls
- 'N', 'S', 'E' or 'W' for the player's starting position and spawning orientation
- Bonus characters are 'P' for doorways and 'K' for keys
- Spaces can be a valid part of the map as long as it respects the rules.

### **The map structure needs to follow certain rules:**

- Must be closed/surrounded (up, down, left, right and all corners) by walls
- Only 1 player character used, represented with 'N', 'S', 'E' or 'W' for the player's starting position
- Spaces are valid as long as it's outside the walls. No tabs allowed, and no empty lines with newline or spaces only
- Only '0', 'N', 'S', 'E', 'W' (and bonus 'P' And 'K') characters allowed within the map walls ('1')

If any of these rules is broken, the program will return an error. Here is an example of a simple valid map:
```
111111
100101
101001
1100N1
111111
```
### **Order of elements in the file:**

- Except for the map, each type of information from an element can be separated by one or more spaces
- Except for the map content which always has to be the last, each type of element can be set in any order in the file
- Except for the map content, each type of element can be separated by one or more empty lines

## Instructions

Use "make" to compile. Run "./cub3d" and the first argument with the path to the .cub text file. Example:
```
./cub3d ./folder/map.cub
```
### **Gameplay:**

The left and right arrow keys to look left and right.
The W A S D keys to move. Pressing ESC will close the window and quit the program.
Clicking on the cross on the window will also close the window and quit the program.

## Technical details

The library used in this proyect is MLX42. The .cub file is parsed and validated before the game is started.
The player spawns with the view orientation and position set on the map.
The file can be edited to change colors, textures and map structure.
4 different images (.png) are used for the wall texture depending on its orientation (north, south, east and west).
The floor and ceiling are drawn in the same color as the rgb value in the .cub file.

### **Bonus list:**

- Wall collisions
- A minimap
- Doors
- Animated sprites and textures
- Rotating the point of view with the mouse
- Textured floor and ceiling

Screen captures:

![Gameplay](https://github.com/ocxpke/cub3D/blob/develop/rosa/key_test/e.png)

![Gameplay](https://github.com/ocxpke/cub3D/blob/develop/rosa/key_test/a.png)

## Resources

"Lode's Computer Graphics Tutorial" by Lode Vandevenne [Link](https://lodev.org/cgtutor/raycasting.html)

"Raycasting Basics" by Shaun Ratcliff [Link](https://splashkit.io/guides/physics/6-raycasting-basics/)

"Ray-Casting Tutorial For Game Development And Other Purposes" by F. Permadi [Link](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

"A raycasting engine in 7 easy steps" by Austin Z. Henley [Link](https://austinhenley.com/blog/raycasting.html)

"Ray-Casting [C]" by ismail_assil [Link](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13)

"3D Ray-casting Game with Cub3D" by Abdilah CH [Link](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a)

"Raycasting in C | 42 Cub3D" by Beqa Tvildiani [link](https://www.youtube.com/watch?v=G9i78WoBBIU)
