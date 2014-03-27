#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

  int n = 0;  
  
class Stripchart {
public:	
  std::string title;
  sf::RenderWindow*  window ;
  Stripchart(){}
  ~Stripchart(){ 
  	delete window;
  	 
 }
 
  Stripchart(int x, int y, int nSamples, int h, int period,  
 						 float minValue, float maxValue)
 	 					 
  {
     title = "Test";
     window = new sf::RenderWindow(sf::VideoMode(400,250), title) ;
     __x = x;
     __y = y;
     __nSamples = nSamples; 
     __h = h;
     __period = period;
     
    // make sure minimum and max are in proper order
     __minValue = std::min(minValue, maxValue);
     __maxValue = std::max(minValue, maxValue);
    
    // and convert them to a string with minimal numbr of decimal places
    minString =  format(__minValue);
    maxString =  format(__maxValue);
    __nPoints = 0;
    __dataPos = 0;
    __startPos = 0;
    points = new float[__nSamples];
     
  }
  
 
 
  int __x;           // horizontal position of chart
  int __y;           // vertical position of chart
  int __nSamples;    // number of samples to display (affects width)
  int __h;           // height of chart
 // sf::Color __colour;    // color of dots to plot
  int __dataPos;     // where does next data point go?
  int __startPos;    // where do we start plotting?
  int __nPoints;     // number of points currently in the array
  int __period;      // how often to draw a gray line
  float __minValue;  // minimum value to display
  float __maxValue;  // maximum value to display
  float *points;  // the data points to plot
  
  
private:
 // template <typename T> std::string format(const T& t) { ostringstream os; os<<t; return os.str(); } 
	
  template <typename T>
  std::string format(const T a_value, const int n = 1)
  {
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
  }
  float d ;//= new DecimalFormat("0.#");
  std::string minString;  // minimum value as a string
  std::string maxString;  // maximum value as a string
  
 
  sf::Font legendFont  ;
  float prevX;    // remember previous point
  float prevY;
  Stripchart* windowstripchart;
 
   int rightSpace ;
   int VSPACE ;
   int HSPACE ;
  
public:
  /**
   * Add a data point to be plotted.
   * At this point you may be wondering why I am using an array
   * instead of an ArrayList. Although programmaticaly it may
   * be easier to add a new value to the list and remove the
   * first one, it takes much less compute time to calculate
   * a mod and keep track of where the oldest data is. 
   *
   * @param value the value to plot
   */
  void addData(double value)
  {
    //value = constrain(value, minValue, maxValue);
    if(value > __maxValue)value = __maxValue;
    else if(value < __minValue) value = __minValue;
    
    
    points[__dataPos] = value;    
    __dataPos = (__dataPos + 1) % __nSamples; // wrap around when array fills

    /*
     * If the array isn't full yet, add to the end of the array
     * Otherwise, the start point for plotting moves through
     * the array.
     */
    if (__nPoints < __nSamples)
    {
      __nPoints++;
    }
    else
    {
      __startPos = (__startPos + 1) % __nSamples;
    }
  }
  
  void display()
  {
    int arrayPos;
    float yPos;
    
    sf::Font font;
    sf::RectangleShape rectangle;
     
    font.loadFromFile("sansation.ttf");
    VSPACE = 2;
    HSPACE = 2;
 
    // reserve space for the max/min value legend
    rightSpace = std::max( minString.length(), maxString.length());
    rectangle.setPosition(0.0f, 0.0f);
    //size del rettangolo
    sf::Vector2f rect_size(__nSamples + rightSpace + 2 * HSPACE, __h + 2 * VSPACE);
    rectangle.setSize(rect_size); 
    
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.move(__x, __y);
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    line(HSPACE, VSPACE + __h / 2, __nSamples + rightSpace - HSPACE, VSPACE + __h / 2, line1);
    line(__nSamples + 1, VSPACE, __nSamples + 1, __h - VSPACE,line2);
    
  
    sf::Text text(minString, legendFont,12);
   
    text.setPosition(__nSamples + 2, __h - VSPACE);
    text.move(__x, __y);
    
    sf::Text text2(maxString, legendFont,12);
     
    text2.setPosition(__nSamples + 2, VSPACE + 8);
    text2.move(__x, __y);
    
    window->draw( rectangle );
    window->draw( text );
    window->draw( text2 );
   // window->display();
    for(int i = 0; i < __nPoints; i++)
    {
      arrayPos = (__startPos + i) % __nSamples;
      if (__period > 0 && arrayPos % __period == 0)
      {
        sf::Vertex line3[2];
        line(__nSamples - __nPoints + i, VSPACE, __nSamples - __nPoints + i, __h - VSPACE,line3);
      }
     
      yPos = VSPACE + __h * (1  - (points[arrayPos] - __minValue) / (__maxValue - __minValue));
      
      // Draw a point for the first item, then connect all the other points with lines
      if (i == 0)
      {  sf::Vertex line4[2];
         line(__nSamples - __nPoints + i, yPos, __nSamples - __nPoints + i, yPos,line4);//points
      }
      else
      { sf::Vertex line5[2];
        line(prevX, prevY, __nSamples - __nPoints + i, yPos,line5);
      }
      prevX = __nSamples - __nPoints + i;
      prevY = yPos;
    }
  
  }
  
  void line(int x, int y, int x1, int y1, sf::Vertex line[2] )
  {
  	  //line   = new sf::Vertex[2];
	line[0] = 
    		sf::Vertex(sf::Vector2f(x, y));
    	line[1] = 
    		sf::Vertex(sf::Vector2f(x1, y1));
	

	window->draw(line, 2, sf::Lines);
  }
  	
 double  radians(double degree) {
    double r = degree*(360.0/M_PI);
    return r;
}
 
  void plot(double value)
  {
    addData(value);
    display();
  }
  
/*  void run(){
    
 
    Stripchart s1(10, 50, 180, 50, 45,   -1.0, 1.0); 
   // Stripchart s2(10, 110, 180, 50, 45,   -1.0, 1.0 );
  //frameRate(30);
 int i=1;

    while (window->isOpen())
    {
    	window->clear();
 	 s1.plot(cos(s1.radians(i  % 360)));
         i++;	 
 
	// s2.addData(sin(s2.radians(n)));
	// s2.addData(sin(s2.radians(n + 1)));
	// s2.addData(sin(s2.radians(n + 2)));
	   
	  n = (n + 3) % 360;
	// s2.display(); 
         window->display();
 
	sf::Event event;
        while (window->pollEvent(event))
        {
         if ( (event.type == sf::Event::Closed)   )
                window->close();
                   }
                    
    }
  
  }*/
};
