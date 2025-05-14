# Fractol

Fractol is a graphical project that visualizes various mathematical fractals, such as Mandelbrot, Julia, and Newton. The project was created as part of the 42 School curriculum and uses the MLX42 graphical library.

## Features

- Fractal visualization:
  - Mandelbrot
  - Julia
  - Newton (bonus mode)
- Dynamic zooming in and out using the mouse or keyboard.
- User interaction support:
  - Panning the view.
  - Real-time parameter adjustments for fractals.
- Bonus mode with additional features.

## Requirements

- Linux operating system
- Installed libraries:
  - MLX42
  - glfw
  - libft (custom library included as a submodule).

## Installation

1. Clone the repository:  
   git clone https://github.com/trosinski08/fractol.git  
   cd fractol  

2. Initialize submodules:  
   git submodule update --init --recursive  

3. Install required packages (e.g., on WSL):  
   sudo apt update  
   sudo apt install libglfw3-dev build-essential cmake  

4. Build the project:  
   make 

## Usage

Run the program with the appropriate arguments:  
./fractol [fractal] [optional parameters]  

### Examples:
- Mandelbrot:  
  ./fractol mandelbrot  

- Julia (with parameters):  
  ./fractol julia -0.8 0.156  

- Newton (bonus mode):  
  ./fractol newton  

## Author

This project was created by Tomasz Rosiński as part of the 42 School curriculum.