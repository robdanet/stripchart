 /* OpenProcessing Tweak of *@*http://www.openprocessing.org/sketch/6789*@* */
/* !do not delete the line above, required for linking your tweak if you upload again */
/**
 * Demonstration for a "stripchart recorder" class.
 */
 
 
#include "stripchart.h"
 
 

int main() {
 
   sf::RenderWindow  window(sf::VideoMode(400,250), "chart 1") ;
   window.setFramerateLimit(20);
   
   Stripchart s1(window, 10, 50, 180, 50, 45,   -1.0, 1.0); 
   //Stripchart s2(10, 110, 180, 50, 45,   -1.0, 1.0 );
    
 int i=1;

    while ( window.isOpen() )
    {
    	 window.clear(sf::Color(200,200,200));
    	 //s2.window->clear(sf::Color(255,255,255));
    	 
 	 s1.plot(cos(s1.radians(i  % 90)));
         i++;	 
 
	 //s2.addData(sin(s2.radians(n)));
	 //s2.addData(sin(s2.radians(n + 1)));
	 //s2.addData(sin(s2.radians(n + 2)));
	   
	  n = (n + 3) % 360;
	  
	  //s2.display(); 
	  
	 s1.display();	  
         window.display();
 
	sf::Event event;
        while ( window.pollEvent(event) )
        {
          if ( (event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape)) ){
                //s2.window->close();
                window.close();
          }
        }
                    
    }
   return EXIT_SUCCESS;
}
 
