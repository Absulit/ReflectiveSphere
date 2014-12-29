/*
    The MIT License (MIT)
    
    Copyright (c) 2014 Sebastián Sanabria Díaz
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
  
                         
/*	 
        darkSky()   
        heightField(tgaPath, newTexture, newScale)        
        plainSky(skyTexture,textures, height)
        turb(color1,color2)	           
	    textfield(string,fontName,extrusion,space) 
	    building(numColumns, columnHeight, columnWidth, space, floorWidth, columnTexture, windowTexture, position)	    
	    explosion(colorMap, position, rotation, turbulenceVal, scaleVal)   
	    smoke() 
	    glow(color) 
	    cubeObj(X,Y,Z) 
	    photonGlobal(filename, loadBool)  
	    photonLoadGlobal(filename)  
	    photonContent() 
	    photonLightSource()
	    dFx(obj,mx,my,mz,rx,ry,rz) 
	    illuminate(obj, lightSourcePosition, lightSourceColor)   
	    plain(plainHeight, reflectionA, reflectionB, plainTexture)  
	    bgColor(value)
	    --

	bola(X,Y,Z,radio)
	caja(X,Y,Z,XX,YY,ZZ,rx,ry,rz) 
	luzVisible(X,Y,Z,radio,Color,textura,quitarColor) 
	reflejo(valor)  
	caustico(valor) 
	sombraAtenuada()
	medio(Color)
	mar(inferior,superior,Color) 
	mar2(altura)
	neblina (Distancia, Color) 
	niebla(altitud, distancia, Color)   
	laser(X,Y,Z,COLOR)
	camara(X,Y,Z,vX,vY,vZ,Angulo)
	mover(X,Y,Z)  
	rayos(mediaOn, normalOn)
	rayos2(mediaOn, normalOn)   
	rayos2(mediaOn, normalOn)
	espejo()
	atmosfera(escala)  
	cielo(PIGMENT_COLOR_MAP,textura)
	aguaNormal()
	juliaEsfera(X,Y,Z,radio,factor,textura) 
	sol(X,Y,Z,radio,Color,textura,quitarColor,quitarAtmosfera)

	piramide(X,Y,Z,textura,pigmento,Reflejo)   
	restar(A,B)
*/ 


#macro darkSky()
sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.75  color CornflowerBlue]
      [1.00  color MidnightBlue]
    }
    scale 2
    translate <-1, -1, -1>
  }
  pigment {
    bozo
    turbulence 0.6
    octaves 7
    omega .49876
    lambda 2.5432
    color_map {
      [0.0 color rgbf<.75, .75, .75, 0.1>]
      [0.4 color rgbf<.9, .9, .9, .9>]
      [0.7 color rgbf<1, 1, 1, 1>]
    }
    scale 6/10
    scale <1, 0.3, 0.3>
  }
  pigment {
    bozo
    turbulence 0.6
    octaves 8
    omega .5123
    lambda 2.56578
    color_map {
      [0.0 color rgbf<.375, .375, .375, 0.2>]
      [0.4 color rgbf<.45, .45, .45, .9>]
      [0.6 color rgbf<0.5, 0.5, 0.5, 1>]
    }
    scale 6/10
    scale <1, 0.3, 0.3>
  }
  
}
#end

#macro heightField(tgaPath, newTexture, newScale)
        height_field {
                tga tgaPath
                smooth
                translate <-.5, -.5, -.5>//center at origin      
                texture{newTexture}
                scale newScale 
        }
#end    

#macro plainSky(skyTexture,textures, height)     
        #local tam = dimension_size(textures,1);
        plane {
            y,
            20000
            hollow on
            texture{skyTexture}
            finish { diffuse 0 ambient 1 } 
        } 
        #while(tam > 0) 
                #local tex = textures[tam - 1]
                inc(height,10)
                plane{   
                  y, 
                  height 
                  hollow on                 
                  texture{tex scale 10}               
                }
                dec(tam, 1)
        #end
#end

#macro turb(color1, color2)  
	//pigment {
	        bozo
	        turbulence 1
	        lambda 2
	        color_map {
	          [0.00, 0.33 color1 color rgb <1, 0, 0>]
	          //[0.33, 0.66 color rgbf <1, 1, 1, 1> color rgbf <1, 1, 1, 1>]
	          [0.66, 1.00 color2 color rgb <1, 0, 0>]
	        }
	      
	    
	//}
#end

#macro textfield(string,fontName,extrusion,space) 
	text {
	  ttf
	  concat(fontName,".ttf"),
	  string,
	  extrusion, 
	  space 
	}           
#end 

#macro building(numColumns, columnHeight, columnWidth, space, floorWidth, columnTexture, windowTexture, position)
	//create column
	#local column =
    	box {
    	  position
    	  <position.x+2, position.y+2, position.z+2>	  
    	  scale <columnWidth,columnHeight,columnWidth> 
    	  texture{columnTexture}
    	}	
	#local c = 1;
	#local f = 1;   
	
	//create a column square
	#while(c < numColumns)
		#while(f < numColumns) 
			#if((f = 1)|(f = numColumns-1) | (c = 1)|(c = numColumns-1))
				object{
					column
					translate<(f * space), position.y, (c*space)>
				} 
			#end
			inc(f,1)
		#end 
		set(f,1)
		inc(c,1)
	#end
	 
	#local corner   = (numColumns * space) - 3; 
	#local floorObj =    
	
    	//floors
    	box {
    	  <space, 0, space>  
    	  < corner,  floorWidth, corner>  
    	  texture{columnTexture}
    	} 
	
	#while(f < columnHeight)
		object{
			floorObj
			mover( position.x, f + position.y, position.z)
		}
		inc(f,1)
	#end
	
	//windows
	box {
	  <space + position.x, position.y, space + position.z>
	  < corner + position.x,  columnHeight + position.y, corner + position.z>
	  
	  texture{windowTexture}
	}  


#end




#macro set(n,Val)
	#local n = Val;
#end

#macro inc(n, k)
	#local n = n + k;
	//n
#end

#macro dec(n, k) 
	#local n = n - k;
#end 

#macro print(Str)
	#debug Str
#end

#macro println(Str)
	#debug concat(Str,"\n")
#end 

#macro printN(N)
	#debug str(N,6,3)
#end 

#macro printA(miArray)
	#local tam = dimension_size(miArray,1); 
	#local pos = 1;
	#while(pos < tam)
		
	#end
#end 

/*#macro for(cont,cond,Inc,bloque)
	#while(cond)
		bloque
		inc(In)
	#end
#end*/






#macro explosion(colorMap, position, rotation, turbulenceVal, scaleVal)
sphere { 
        0, 1
        pigment {color rgbt <1,1,1,1>}
        interior{
                media{
                        emission 1
                        samples 20 
                        density { 
                                spherical
                                turbulence turbulenceVal
                                //frequency 2
                                color_map{colorMap}                              
                        }
                        scale .5
                }
        
        }
        
        hollow on
        scale 1.5 
        scale scaleVal 
        mover( position.x, position.y, position.z) 
        rotate<rotation.x, rotation.y, rotation.z>  
        no_shadow
}
#end 



#macro smoke()
        pigment{Clear}
        no_reflection
        hollow on 

        interior{  
                //ior 2.5
                media {
                        // (---general values---)
                        intervals 10           // number of intervals used for sampling [10]
                        samples 1,1            // minimum and maximum number of samples taken per interval [1,1]
                        confidence 0.9         // statistic parameter higher->better quality [0.9]
                          variance 1.0/128       // statistic parameter lower->better quality [1.0/128]
                          ratio 0.9              // distribution between lit and unlit areas [0.9]
                          // (---media types---)
                          absorption rgb<0,0,0>  // absorbing media, block light of specified color
                          //emission Orange  // emitting media, emit light of specified color
  
                          scattering {           // scattering media
                            5,                   // scattering type 1=isotropic; 2=Mie haze; 3=Mie murky
                                                 // 4=Rayleigh; 5=Henyey-Greenstein
                            rgb<.5,.5,.5>           // color
                            eccentricity 0.25  // eccentricity for type 5 [0.0]
                            extinction 1.0     // for balancing amount of absorption [1.0]
                          }
                          // (---method---)
                          //method 1             // old Povray 3.1 method
                          //method 2             // new method with even distribution
                          method 3               // adaptive sampling
                          aa_threshold 0.1     // accuracy threshold for method 3 [0.1]
                          //aa_level 4           // maximum recursion depth for method 3 [4]
                          jitter 0.5           // randomness for method 2&3
                          // (---density---)
                          /*
                          density {
                            spherical            // any pattern
                            color_map {...}      // color_map
                            //density_map {...}  // or alternatively density_map
                          }*/
                        
        }
}
#end 


  
#macro glow(rgbColor)
  media { 
    emission 1
    density { 
      spherical   
      poly_wave 5
      density_map { 
        [0 rgb 0]
        [1 rgb rgbColor]
      }
    }
    method 3
  }
#end

#macro cubeObj(X,Y,Z) 
        box {
          <0,0,0> <X,Y,Z>  
        }
#end

#macro photonGlobal(filename, saveToFile)   
        photons {   
 
		    spacing 0.05
		    autostop 0
		    jitter 0
		#if(saveToFile)  
                count 10000
                media 100 
		        save_file filename
		#else 
		        load_file filename
		#end
                                            
        }  
        max_trace_level 5  
#end 

#macro photonLoadGlobal(filename)
        photons {
                spacing 0.1
                //count 10000
                //media 100
                load_file filename                            
        }  
        max_trace_level 5  
#end

#macro photonContent()  
	pigment {White filter .9}
	finish {
		reflection {0.2 fresnel metallic}
	}
	interior {
		ior 1.5
		dispersion 1.05
		dispersion_samples 20
	}
    photons {
        target .5
        refraction on
        reflection on
    }        
#end

#macro photonLightSource()
  photons {
    refraction on
    reflection on
    //area_light
  }
#end

#macro dFx(obj,mx,my,mz,rx,ry,rz) 
        object{
                obj  
                pigment {Clear }        
                interior {
                        fade_distance 2
                        fade_power 3
                        ior 2.4
                }
                reflejo(.2, 1) 
                caustico(2)  
                rotate<rx,ry,rz> 
                mover(mx,my,mz) 
                photonContent()
        }
#end
 
 
//TODO: check this macro 
#macro illuminate(obj, lightSourcePosition, lightSourceColor)  
   light_source {                                                  
     lightSourcePosition                                                                              
     color lightSourceColor
     looks_like { 
        object{
                obj
                finish{ambient 1} 
                translate lightSourcePosition
        }
     }    
     //media_attenuation on 
   }
#end



#macro plain(plainHeight, reflectionA, reflectionB, plainTexture)
	plane {
		y, plainHeight 
		hollow on
		texture{plainTexture finish{reflection {reflectionA, reflectionB}}}
		#debug "Plain Finished\n"
	}
#end

//-----------------------------------------------

#macro bgColor(value)
   background {color value} 
#end  

#macro bola(X,Y,Z,radio,Reflejo)  
   sphere{
      <X,Y,Z>,radio
      texture{      
         T_Glass1 
         scale 1  
         finish {reflection Reflejo ambient 0}//reflejo original 1 o 2  
      }
      // photon block for an object
	  photons{
	    target //1.0          // spacing multiplier for photons hitting the object
	    refraction on
	    reflection on
	  }       
	  pigment {Clear }
     //interior{caustics 2  ior 1.5}        
   }
#end

#macro caja(X,Y,Z,XX,YY,ZZ,rx,ry,rz,Reflejo)
  box {
    <X, Y, Z>  // Near lower left corner
    < XX, YY, ZZ>   // Far upper right corner
    texture {
      T_Glass1     // Pre-defined from stones.inc
      scale 1       // Scale by the same amount in all directions 
      finish {reflection Reflejo }//reflejo original 1 o 2 
   }  
   //interior{caustics 2 ior 1.5}                             
   rotate y*rx    
   rotate z*ry  
   rotate x*rz 
   photons{
    target 1.0          // spacing multiplier for photons hitting the object
    refraction on
    reflection on
    //collect off       // ignore photons
    //pass_through      // do not influence photons
  }
  }                                  
#end

#macro luzVisible(X,Y,Z,radio,Color,textura,quitarColor)
   light_source {                                                  
     <X,Y,Z>                                                                               
     color Color
     looks_like { 
         sphere { 
            <X,Y,Z>                                                                              
            radio 
            texture{
                textura
                pigment{Color+(White/4)}                           
                finish{
                  reflection .5  
                  ambient 3
                }
            }
            #if(!quitarColor)
            	pigment{Clear}    
            #end
            interior { ior 1.5 }
            // photon block for a light source
                photons {
                        refraction on
                        reflection on			  
                }
         } 
     }    
     media_attenuation on
   }
#end

#macro reflejo(luz,sombra)   
   	finish{reflection{ luz, sombra  fresnel .5} conserve_energy} 
   	//finish{reflection{ .03, 1  fresnel .5} conserve_energy}
   	//interior{ior 1.5}   
   	#debug "Reflejo Terminado\n"
#end
    
#macro caustico(valor) 
	interior{caustics valor} 
#end

#macro sombraAtenuada()
        interior{
        	fade_distance 20
            	fade_power 3
        }
#end 

#macro medio(Color)
        media {    // atmospheric media sample
          intervals 10
          scattering { 1, Color }
          samples 1, 10
          confidence 0.9999
          variance 1/1000
          ratio 0.9
        }      
	#debug "Medio Terminado\n"
#end  
    
#macro mar(inferior,superior,Color) 
plane { y, inferior
    texture {
      pigment { color Color }
      finish { ambient 0.1 diffuse 0.7 }
      scale 0.01
    }
  }

  // y la superficie del agua

  plane { y, superior
    texture {
      pigment { rgbf <0.6, 0.67, 0.72, 0.9> }
      normal {
        bumps 1
        scale <.75, .25, .25>
        rotate <0, 45, 0>
      }
      
    }  
    reflejo(.5,.33)
    caustico(32)
  }     
  #debug "Mar Terminado\n"
#end

#macro mar2(altura)
	plane { y, altura
	   texture {
	      T_Chrome_2D
	      normal {
	         waves 0.05
	         frequency 5000.0
	         scale 3000.0
	      }

	   }
	   //finish{conserve_energy}   
	}
#end

#macro neblina (Distancia,Color) 
	fog {
	  fog_type 1
	  distance Distancia
	  color Color
	}
	// atmospheric media can be generated by adding a media statement
	// to the scene not attached to any specific object
	media {    // atmospheric media sample
	  intervals 10
	  scattering { 1, rgb 0.03 }
	  samples 1, 10
	  confidence 0.9999
	  variance 1/1000
	  ratio 0.9
	} 
#end

#macro niebla(base, altitud, distancia, Color)
	fog {
	  fog_type 2
	  fog_alt altitud
	  fog_offset base
	  color Color//rgb <0.7, 0.8, 0.9>
	  distance distancia// = 800
	}
#end

#macro laser(X,Y,Z,COLOR)
	light_source{
                <X,Y,Z>, COLOR cylinder
                media_attenuation on  
	}
#end 
                    
                    
                    
#macro anguloAVector(Angulo) 
	#local Angulo = -Angulo + 90;
	#local Angulo = mod(Angulo, 360);
	#local xFinal = cos(radians(Angulo));
	#local yFinal = sin(radians(Angulo)); 
	<xFinal,yFinal,0>
	
#end  

#macro angulosAVector(Angulos)
	#local Z = -Angulos.z + 90;
	#local Z = mod(Angulos.z, 360);
	#local Z = radians(Z);
	#local xFinal = cos(Z);
	#local yFinal = sin(Z); 
	#local zFinal = 0;
	<xFinal,yFinal,zFinal>
#end
                    
#macro camara(Origen,Destino,Angulo,Zoom,Sky)
	camera {	  		
	  location  Origen
	  look_at   Destino
	  right     x*image_width/image_height
	  angle     Zoom
	  sky       Sky	  
	  rotate    Angulo 
	}  
	#debug "Camara Terminada\n"
#end  

#macro cinema(Origen,Destino,Angulo,Zoom)
	camera {	  		
	  location  Origen
	  look_at   Destino
	  right     x*16/9
	  angle     Zoom
	  sky       y	  
	  rotate    Angulo
	}   
	#debug "Camara cinema Terminada\n"
#end   

#macro camaraBlur(Origen,Destino,Angulo,Zoom)
	camera {  
	  perspective //keyword is facultative in this case
	  location  Origen
	  look_at   Destino 
	  angle Zoom
	  sky y  
	  rotate    Angulo
	  blur_samples 120 //add samples if you got a fast computer 
	  aperture 10
          focal_point Destino
	  right     x*image_width/image_height
	}  
	#debug "Camara Blur Terminada\n"
#end 




#macro mover(X,Y,Z)
	translate<X,Y,Z>
#end 



#macro espejo()  
	finish { reflection {1.0} ambient 0 diffuse 0 }
#end

#macro atmosfera(distancia)
	sphere{0,1 scale distancia hollow
	       texture{pigment{Clear}finish{ambient 0 diffuse 0}}
	       interior{
	               media{
	                       scattering {5,0.00034 eccentricity 0.7 extinction 0.8}
	                       absorption <255-23,255-171,255-239>*0.0005/255
	                       intervals 3
	                       method 3
	               }
	       }
	}
#end

#macro cielo(PIGMENT_COLOR_MAP,textura)
	sphere {                  // --- Sky ---
	  <0, 0, 0>, 1
	  texture {
                PIGMENT_COLOR_MAP
	        finish { diffuse 0 ambient 1 }
	  }
	  texture{textura} 
	  /*#if(iorAire)
	        interior{
	                ior Air_Ior
	                dispersion 1.1
	                dispersion_samples 10
	        }
	  #end*/
	  scale 10000
	  hollow on
	  no_shadow
	}  
	#debug "Cielo Terminado\n"
#end

#macro aguaNormal()
	normal{
	    bozo 1
	    normal_map {
	        [ 0.3 waves translate -0.5 scale <1, 0.05, 1>*100000 frequency 100000]
	        [ 0.7 ripples translate -0.5 scale <1, 0.7, 1>*100000 frequency 100000]
	        [ 0.85 ripples translate -0.5 scale <1, 0.6, 1>*100000 frequency 100000]
	        [ 1.0 ripples translate -0.5  scale 100000 frequency 100000]
	    }
	    scale 1
	}
#end

#macro juliaEsfera(X,Y,Z,radio,factor,textura,Reflejo)
	sphere{ 
		translate <X,Y,Z>
		radio
		texture{textura}
		normal{ 
		 julia <-.5,.5> factor
		 exponent 4
		 slope_map { [0 <0,0>][.5 <.5,1>][1 <1,0>] }
		 rotate x*30
		}
		finish { specular .5 reflection Reflejo }
			  
	}
#end
 
#macro juliaEsfera2(X,Y,Z,radio,factor,textura,Reflejo)
sphere {
  <X,Y,Z> // center of sphere <X Y Z>
  radio       // radius of sphere  
  texture{textura}
  pigment {
      julia <0.353, 0.288>, factor
      interior 1, 1
      color_map { 
	    [0 rgb 0]
        [0.2 rgb x]
        [0.4 rgb x+y]
        [1 rgb 1]
        [1 rgb 0]
      }
    }
  reflejo(Reflejo)

}

#end
#macro sol(X,Y,Z,radio,Color,textura,quitarColor,quitarAtmosfera)
	luzVisible(X,Y,Z,radio,Color,textura,quitarColor)
	#if(!quitarAtmosfera)
		atmosfera(410)
	#end  
	#debug "Sol Terminado.\nEs Genial!!!"
#end 


#macro piramide(X,Y,Z,textura,pigmento,Reflejo)
  prism {
    conic_sweep
    linear_spline
    0, // height 1
    1, // height 2
    5, // the number of points making up the shape...
    <4,4>,<-4,4>,<-4,-4>,<4,-4>,<4,4>
    rotate <180, 0, 0>    
    scale <1, 4, 1>
    
    pigment {pigmento}
    texture{textura}
    reflejo(Reflejo)
    caustico(Reflejo/2) 
    finish{irid{.25}}
    translate <X,Y,Z>
  }
#end       

#macro restar(A,B)
        difference{
                object{A}
                object{B}
        }
#end