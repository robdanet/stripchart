/**
 * Demonstration for a "stripchart recorder" class.
 * 28/03/14 22:43:25 
 */
 
#include "channel.h"
 
   

int main() {
 sf::ContextSettings settings;
settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(400,250), "Strip Chart Sim", sf::Style::Default, settings) ;
    window.setFramerateLimit(30);
    int nChannels = 1;
    int nSample = 180, nSample2 = 120;
    int height = 50;
    int period = 45;
    
    
    sf::Color chancol (0 ,200, 0);
 
   
    Stripchart s1(window, 10, 50, nSample, 50, 45, sf::Color(0, 128, 0), -1.0f, 1.0f);
    Stripchart s2(window, 10, 110, nSample, 50, 45, sf::Color(255, 0, 0), -1.0f, 1.0f);
    Stripchart s3(window, 10, 170, nSample2, 50, 0, sf::Color(0, 128, 128), 0, 400);
    Stripchart s4(window, 200, 170, nSample2, 50, 0, sf::Color(128, 0, 128), 0, 250);
    Channel    channel (s1, nSample,height, period,chancol, -1.0f, 1.0f);
    
     
    int n = 0;
    int mouseX, mouseY;
    
    while ( window.isOpen() )
    {
         window.clear(sf::Color(255,255,255));
         
    		//channel.addData( sin(s1.radians(n))) ;
                 
           
           
           
          s1.addChannel(channel);//.display(); oppure channel.display();
   	  channel.addData( sin(s1.radians(n))) ;
   	  channel.display();
  	  s1.plot(cos( s1.radians(frameCount % 360)));
  	  
  	  
  	  s2.addData(sin(s2.radians(n))); 
          s2.addData(sin(s2.radians(n+1)));
  	  s2.addData(sin(s2.radians(n+2)));
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
		if ((event.type == sf::Event::Closed) ||
		   ( (event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape) )) {
		         
		        window.close();
		}
		else if((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::C)) {
			channel.toggle();
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
