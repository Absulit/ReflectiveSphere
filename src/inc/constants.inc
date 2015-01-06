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
        luz
        textura1
        textura2
        texturaCafe
        pigmentoCielo 
        pigmentoCieloAtardecer 
        pigmentoCieloAnochecer
        
        clouds1
        clouds2
        clouds3
        clouds4
        landArea
	ocenanArea
	cloudArea 



*/   
            
//Divine Proportion            
#declare PHI = 1.1618;

//reflejoSuave
#declare softReflectionFinish = 
        finish{reflection{ .33 , 1}}

#declare lightSource =
  light_source {
	<-1.5, 1, -0.5>*10000
	//color rgb <1.0, 0.92, 0.77>
	color rgb <1.0, 0.9, 0.78>*2.3
	photons {
		refraction on
		reflection on
		//area_light
	}
  }
  
#declare texture1 =
texture {
  pigment {
    color rgb 0.8
  }
  finish {
    ambient 0.0
    diffuse 0.6
    specular 0.1
  }
}

#declare texture2 =
texture {
  pigment {
    color rgb <0.9, 0.65, 0.3>
  }
  finish {
    ambient 0.0
    diffuse 0.6
  }
}

#declare brownTexture =
  texture {
    pigment { color rgb <1.0, 0.8, 0.6> } 
  }  
  
#declare skyPigment =
   pigment {
     gradient y
     color_map {
       [0.0 color rgb < 1.0, 1.0, 1.0 >]
       [0.3 color rgb < 0.5, 0.6, 1.0 >]
     }
   } 
   
// pigmentoCieloAtardecer   
#declare skySunsetPigment =
   pigment {
     gradient y
     color_map {
       [0.0 Yellow]    
       [0.3 Orange]   
       [0.5 color rgb < .9, .3, 1 >]
       [0.6 color rgb < 0.5, 0.6, 1.0 >]
     }
   } 
   
//pigmentoCieloAnochecer   
#declare skyEveningPigment =
   pigment {
     gradient y
     color_map {
       [0.0 Red]    
       [0.2 Blue + White]   
       [0.6 Black]
     }
   }   
   
   

     
   
//////////
#declare clouds1 = pigment {
      bozo
      turbulence 1
      color_map {
        [0.0 color White filter 1] 
        [0.5 color White]
        [1.0 color White filter 1]
      }
    }
  #declare clouds2 = pigment {
    agate
    turbulence 1
    color_map {
      [0.0 color White filter 1]
      [0.5 color White]
      [1.0 color White filter 1]
      }
    }
  #declare clouds3 = pigment {
    marble
    turbulence 1
    color_map {
      [0.0 color White filter 1]
      [0.5 color White]
      [1.0 color White filter 1]
    }
  }
  #declare clouds4 = pigment {
    granite
    turbulence 1
    color_map {
      [0.0 color White filter 1]
      [0.5 color White]
      [1.0 color White filter 1]
    }
  }

#declare landAreaTexture = 
	texture {
		pigment {
			agate
			turbulence 1
			lambda 1.5
			omega .8
			octaves 8
			color_map {
				[0.00 color rgb <.5, .25, .15>]
				[0.33 color rgb <.1, .5, .4>]
				[0.86 color rgb <.6, .3, .1>]
				[1.00 color rgb <.5, .25, .15>]
			}
		}
	}
	
#declare oceanAreaTexture = 
//texture{Water}
	texture {
      pigment {
        bozo
        turbulence .5
        lambda 2
        color_map {
          [0.00, 0.33 color rgb <0, 0, 1>
                      color rgb <0, 0, 1>]
          [0.33, 0.66 color rgbf <1, 1, 1, 1>
                      color rgbf <1, 1, 1, 1>]
          [0.66, 1.00 color rgb <0, 0, 1>
                      color rgb <0, 0, 1>]
        }
      }
      //finish{reflection 1}
    }

#declare cloudAreaTexture = texture {
    pigment {
      gradient y
      pigment_map {
        [0.00 clouds1]
        [0.25 clouds2]
        [0.50 clouds3]
        [0.75 clouds4]
        [1.00 clouds1]
      }
    }
  }   
  
#declare T_RedTurbBlack = texture {
    pigment {
        bozo
        turbulence 1
        lambda 2
        color_map {
          [0.00, 0.33 color rgb <1, 0, 0> color rgb <1, 0, 0>]
          //[0.33, 0.66 color rgbf <1, 1, 1, 1> color rgbf <1, 1, 1, 1>]
          [0.66, 1.00 color rgb <0, 0, 0> color rgb <1, 0, 0>]
        }
      
    }
  }    
  
#declare T_RedTurbWhite = texture {
    pigment {
        bozo
        turbulence 1
        lambda 2
        color_map {
          [0.00, 0.33 color rgb <1, 0, 0> color rgb <1, 0, 0>]
          //[0.33, 0.66 color rgbf <1, 1, 1, 1> color rgbf <1, 1, 1, 1>]
          [0.66, 1.00 color rgb <1, 1, 1> color rgb <1, 0, 0>]
        }
      
    }
  }  