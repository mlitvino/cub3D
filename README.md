# cub3D

The goal of the cub3d is to make something using raycasting (like Wolfenstein 3D).

This project uses [MLX42](https://github.com/codam-coding-college/MLX42), an improved version of an old and non-updatable library minilibx.
For sounds and music, I use [raudio](https://github.com/raysan5/raudio). It's a standalone module of Raylib. In short, Raylib depends on MiniAudio.

## The game

You play as Van Helsing, a monster hunter. You must traverse the forest and castle, destroying the monsters that stand in your way.

## Preview

<img width="680" height="400" alt="photo-collage png" src="https://github.com/user-attachments/assets/cd23853e-bc37-4de1-8ed3-8ce25cde4d42" />

## Controls

<img width="680" height="400" alt="controls" src="https://github.com/user-attachments/assets/be3315f2-6118-4b5e-bc8f-0f3a883b3ed6" />



## Web version

If you do not want to or cannot build the source files, you can try the web version! It lacks sound and performance, unlike the local version. 

https://mlitvino.github.io/cub3D/

## Usage

Dependencies: 

To ensure that you have all the required dependencies, I recommend you run this command 

    apt-get install -y \
      build-essential \
      cmake \
      pkg-config \
      libx11-dev \
      libxrandr-dev \
      libxinerama-dev \
      libxcursor-dev \
      libxi-dev \
      libglfw3-dev \
      libgl1-mesa-dev \
      libglu1-mesa-dev \
      zlib1g-dev \
      libbsd-dev \
      libxext-dev

* go to cub3D_bonus directory
* make ``make``
* To run level 1:
  * ``./cub3D map/forest.cub``
* To run level 2:
  * ``./cub3D map/castle.cub``

## Credits

- **Music**: [alkakrab Game Music](mailto:alkakrab04@gmail.com)  
- **Textures (wolf & weapon)**: Viktoriia Lebedeva
- **Textures (walls and grass)**: Jestan twitter: @jestanpixels, e-mail: jestanql@hotmail.com
- **Other textures**: sora (via OpenAI)

