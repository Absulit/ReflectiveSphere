# ReflectiveSphere

Set of include files to provide a fast PovRay scene set up

## Installation

Download PovRay and Install
Download repo:

Open PovRay and go to: Tools/Edit master POVRAY.INI
and add the following path

Library_Path="C:\ReflectiveSphere\src\inc" 

I also add a custom directory for my .pov files
Library_Path="C:\my-directory\pov"

## Usage

TODO: Write usage instructions

If you are lazy add the following include which adds all the inner includes

 #include "todos.inc"  

Also if you want to be specific you can add one of the following

 #include "incs.inc"         // inc related files from PovRay that you might need
 #include "macros.inc"       // bunch of macros
//#include "rays.inc"       // macros for raytracing 
 #include "constantes.inc"   // constants such as light source
 #include "animacion.inc"    // animation related 

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History

TODO: Write history


## Credits

Sebastián Sanabria Díaz 

## License

MIT