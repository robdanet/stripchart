/**
 *   Demonstration for a "stripchart recorder" class.
 */
 
 
#include "stripchart.h"
 
  

int main() {
 
    sf::RenderWindow  window(sf::VideoMode(400,250), "Strip Chart Sim") ;
    window.setFramerateLimit(30);
   
    Stripchart s1(window, 10, 50, 180, 50, 45, sf::Color(0, 128, 0), -1.0f, 1.0f);
    Stripchart s2(window, 10, 110, 180, 50, 45, sf::Color(255, 0, 0), -1.0f, 1.0f); 
    Stripchart s3(window, 10, 170, 120, 50, 0, sf::Color(0, 128, 128),  0, 400);
    Stripchart s4(window, 200, 170, 120, 50, 0, sf::Color(128, 0, 128), 0, 250);
    
    int frameCount = 0;
    int n = 0; 
    int mouseX, mouseY;
    
    while ( window.isOpen() )
    {
    	 window.clear(sf::Color(255,255,255));
    	  
 
    	
 	 s1.plot(cos( radians(frameCount % 360)));
 	
 	 s2.addData(sin(radians(n)));//+sin(radians(n)));
         s2.addData(sin(radians(n)));
  	 s2.addData(sin(radians(n)));
 	 s2.display();
 	
 	 n = (n + 3) % 360; 
 	
	/* The last two charts track mouseX and mouseY movement */
	s3.plot(mouseX);
	s4.plot(mouseY);

        
         frameCount++;	
         
         window.display();
 
	sf::Event event;
        while ( window.pollEvent(event) )
        {
          if ( (event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape)) ){
                 
                window.close();
          }
          else if(event.type == sf::Event::MouseMoved) {
          	mouseX = event.mouseMove.x;
          	mouseY = event.mouseMove.y;
          	std::cout << "\nMouseX: "<< mouseX << "\nMouseY: " << mouseY << std::endl;
          }
           
        }
                    
    }
   return EXIT_SUCCESS;
}
 
