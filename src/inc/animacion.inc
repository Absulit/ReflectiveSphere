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

//Animacion
//-ga +kfi1 +kff30 +kc -p 
/*
 -GA	Evita salida a la consola para aumentar velocidad
 -A0.1  Anti Alias false con 0.1
 +R2 Tipo de AA
 +KFI1 Cuadro de inicio(no cambiar) 
 +KFF30 Cuadro final, cambiar por animacion  

 ************no tocar***normalizado****
 *+KI0 valor inicial de clock  en 0   *
 *+KF1 valor final de clock en 1      *
 **************************************
 +KC Activar animacion ciclica 
 **************************************
 segmento de animacion
 +sf10  inicio de segmento
 +ef20  fin de segmento 
 
 -gs -gw solo se imprime lo que yo mando a escribir
 	
		animArray(miArray)    
		animLapso(valInicial, valFinal, frameInicial, frameFinal)
        	anim(valInicial, valFinal) 
        	animVector(vI,vF)    
*/

#macro animRotar(valInicial, iteraciones, incremento)
	#if(clock_on)
		#local lapso = final_clock / iteraciones;//puede ser q el valor final de clock cambie
		#local tiempoActual = clock;
		//el clock entre lapsos debe ser igual
		#while(tiempoActual >= lapso)
			dec(tiempoActual,lapso)
		#end
		#local return = valInicial * iteraciones * tiempoActual;
		#if(incremento)
			#local return = return * clock;
		#end
		return
	#else
		valInicial
	#end
#end 

//animArray(array[10]{ 1.1, 2 ,2, 2, 3, 3.5, 3.5, 10, 10, 12})
#macro animArray(miArray)
   	//miArray es una lista de numeros por los q a travez del tiempo se desplazara	  
   
	#local tam = dimension_size(miArray,1);
	#local taml = tam - 1;
	#if(clock_on)	   
		#local lapso = final_clock / taml;//puede ser q el valor final de clock cambie
		#local actual = int(taml * clock);
		#local siguiente = actual + 1;
		
		#local valInicial = miArray[actual]; 
		#local valFinal = miArray[siguiente];
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

#macro animLapso(valInicial, valFinal, clockInicial, clockFinal)
        #if(clockInicial >= clockFinal)
                #error "clockFinal debe ser mayor a clockInicial"
        #end   
        #local return = 0;
        #if(clock >= clockInicial)    
                #if(clock <= clockFinal)
                        /*valInicial + frame_number - frameInicial * (valFinal - valInicial)/(frameFinal - frameInicial)
                        valInicial + frame_number - frameInicial *                 dv/df 
                        valInicial +    transcurrido        *                        r                                */   
                        #local return = valInicial + (clock - clockInicial) * ((valFinal - valInicial) / (clockFinal - clockInicial));
                                 
                #else  
                        #local return = valFinal;       
                #end
        #else
                #local return = valInicial;
        #end 
        return
#end 

#macro anim(valInicial, valFinal)
        #if(valInicial = valFinal)
                #error "Seas boli! para q anim con dos valores iguales!"
        #end 
	#local distancia = valFinal - valInicial;
	#local tiempo = final_clock - initial_clock;
	#local velocidad = distancia / tiempo;
        valInicial + (velocidad * clock)       
        //valInicial + (((valFinal - valInicial) / (final_frame - initial_frame + 1)) * frame_number)
#end    

#macro animVector(vI,vF)         
        <anim(vI.x,vF.x), anim(vI.y,vF.y), anim(vI.z,vF.z)>
#end