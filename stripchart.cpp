/* OpenProcessing Tweak of *@*http://www.openprocessing.org/sketch/6789*@* */
/* !do not delete the line above, required for linking your tweak if you upload again */
/**
 * Demonstration for a "stripchart recorder" class.
 */
 
 
#include "stripchart.h"
 
 

int main() {
 
 Stripchart s1(10, 50, 180, 50, 45,   -1.0, 1.0); 
   Stripchart s2(10, 110, 180, 50, 45,   -1.0, 1.0 );
  //frameRate(30);
 int i=1;

    while ( s2.window->isOpen() )
    {
    	 s1.window->clear();
    	 s2.window->clear();
    	 
 	 s1.plot(cos(s1.radians(i  % 360)));
         i++;	 
 
	 s2.addData(sin(s2.radians(n)));
	 s2.addData(sin(s2.radians(n + 1)));
	 s2.addData(sin(s2.radians(n + 2)));
	   
	  n = (n + 3) % 360;
	  
	  s2.display(); 
	  
	  s1.window->display();	  
         
 
	sf::Event event;
        while ( s2.window->pollEvent(event) )
        {
          if ( (event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape)) ){
                s2.window->close();
                s1.window->close();
          }
        }
                    
    }
   return EXIT_SUCCESS;
}
 
