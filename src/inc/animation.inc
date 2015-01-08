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

//Animation
//-ga +kfi1 +kff30 +kc -p 

/*
 -GA	Remove output from console for speed
 -A0.1  Anti Alias false with 0.1
 +R2    AA type
 +KFI1  Key Frame Initial (do not change) 
 +KFF30 Key Frame Final, change per animation

 ************no tocar***normalizado****
 *+KI0 valor inicial de clock  en 0   *
 *+KF1 valor final de clock en 1      *
 **************************************
 +KC Activate cyclic animation 
 **************************************
 
 Animation Segment
 +sf10  Segment start Frame
 +ef20  Segment end Frame
 
 -gs -gw only outputs what I wrote
 	
		animArray(miArray)    
		animLapso(valInicial, valFinal, frameInicial, frameFinal)
        anim(valInicial, valFinal) 
        animVector(vI,vF)    
*/

#macro rotateAnim(initVal, iterations, increment)
    #if(clock_on)
		#local lapse = final_clock / iterations;////the final clock value might change
		#local currentClock = clock;
		//clock betwen laps should be equal
		#while(currentClock >= lapse)
			dec(currentClock, lapse)
		#end
		#local return = initVal * iterations * currentClock;
		#if(increment)
			#local return = return * clock;
		#end
		return
	#else
		initVal
	#end
#end 

//arrayAnim(array[10]{ 1.1, 2 ,2, 2, 3, 3.5, 3.5, 10, 10, 12})
#macro arrayAnim(arrayVal)
   	//miArray es una lista de numeros por los q a travez del tiempo se desplazara	  
   
	#local tam = dimension_size(arrayVal,1);
	#local taml = tam - 1;
	#if(clock_on)	   
		#local lapso = final_clock / taml;//puede ser q el valor final de clock cambie
		#local actual = int(taml * clock);
		#local siguiente = actual + 1;
		
		#local valInicial = arrayVal[actual]; 
		#local valFinal = arrayVal[siguiente];
		#local distancia = valFinal - valInicial;
		
		#local clockInicial = lapso * actual;
		#local clockFinal = lapso * siguiente;
		#local tiempo = clockFinal - clockInicial;
		
		#local velocidad = distancia / tiempo;
		
		#local tiempoActual = clock;
		//el clock entre lapsos debe ser igual
		#while(tiempoActual >= lapso)
		dec(tiempoActual,lapso)
		#end 
		
		#local return = valInicial + (velocidad  * tiempoActual);
	#else 
		#local return = miArray[int(taml * clock)];
	#end
	return
#end

#macro lapseAnim(initValue, endValue, initClick, endClock)
    #if(initClick >= endClock)
        #error "endClock must be greater than initClick"
    #end   
    #local return = 0;
    #if(clock >= initClick)    
        #if(clock <= endClock)
            /*valInicial + frame_number - frameInicial * (valFinal - valInicial)/(frameFinal - frameInicial)
            valInicial + frame_number - frameInicial *                 dv/df 
            valInicial +    transcurrido        *                        r                                */   
            #local return = initValue + (clock - initClick) * ((endValue - initValue) / (endClock - initClick));                       
        #else  
            #local return = endValue;       
        #end
    #else
        #local return = initValue;
    #end 
    return
#end 

#macro anim(initValue, endValue)
    #if(initValue = endValue)
        #error "Silly! why an animation with two equal values!"
    #end 
	#local distanceVal  = endValue - initValue;
	#local time         = final_clock - initial_clock;
	#local speed        = distanceVal / time;
    initValue + (speed * clock)       
    //initValue + (((valFinal - initValue) / (final_frame - initial_frame + 1)) * frame_number)
#end    

#macro vectorAnim(initVector,finalVector)         
        <anim(initVector.x, finalVector.x), anim(initVector.y, finalVector.y), anim(initVector.z, finalVector.z)>
#end