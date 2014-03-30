#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

//#define radians(angleDegrees) (angleDegrees * M_PI / 180.0) 
  
class Stripchart {
public:	
  std::string title;
   
 
 
  Stripchart(sf::RenderWindow& parent, int x, int y, int nSamples, int h, int period,sf::Color color , 
 						 float minValue, float maxValue)
 	 					 
  {
     parent_pnt = &parent; 
     
     title = "Test";
     
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
    
     font.loadFromFile("sansation.ttf");
     __color = color;
     
  }
  
 
 
  int __x;           // horizontal position of chart
  int __y;           // vertical position of chart
  int __nSamples;    // number of samples to display (affects width)
  int __h;           // height of chart
  
  int __dataPos;     // where does next data point go?
  int __startPos;    // where do we start plotting?
  int __nPoints;     // number of points currently in the array
  int __period;      // how often to draw a gray line
  float __minValue;  // minimum value to display
  float __maxValue;  // maximum value to display
  float *points;  // the data points to plot
 
  /**
   * SFML stuff
   */
   
   sf::Font font;
   sf::RectangleShape rectangle;
   sf::RenderWindow* parent_pnt;
   
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
    
     
     
     
    
    VSPACE = 2;
    HSPACE = 2;
 
    // reserve space for the max/min value legend
    //rightSpace = std::max( minString.length(), maxString.length()) * 10;
    
    rectangle.setPosition(0.0f, 0.0f);
    //size del rettangolo
    sf::Vector2f rect_size(__nSamples + rightSpace + 2 * HSPACE, __h + 2 * VSPACE);
    rectangle.setSize(rect_size); 
    
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.move(__x, __y);
    
    //valore massimo
    sf::Text text1(maxString, font,12);int rectw1 = text1.getLocalBounds().width;
    text1.setColor(sf::Color(0,0,0));
    text1.setPosition(__nSamples + 2, VSPACE -2 );
    text1.move(__x  , __y ); 
  
    //valore minimo  
    sf::Text text2(minString, font,12);int rectw2 = text2.getLocalBounds().width;
    text2.setColor(sf::Color(0,0,0));
    text2.setPosition(__nSamples + 2, __h - VSPACE-8);
    text2.move(__x, __y);
 
    rightSpace = (int)std::max( rectw1, rectw2); 
    
    parent_pnt->draw( rectangle );
    parent_pnt->draw( text1 );
    parent_pnt->draw( text2 );
    
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    
    //assi della chart
    line(__x + HSPACE, __y + VSPACE + __h / 2, __x + __nSamples + rightSpace - HSPACE,__y + VSPACE + __h / 2, line1, sf::Color(192,192,192));
    
    line( __x+ __nSamples + 1,__y +  VSPACE, __x +    __nSamples + 1,__y +  __h - VSPACE,line2, sf::Color(192,192,192));
   
    for(int i = 0; i < __nPoints; i++)
    {
      arrayPos = (__startPos + i) % __nSamples;
      if (__period > 0 && arrayPos % __period == 0)//linea verticale
      {
        sf::Vertex line3[2];
        line(__x + __nSamples - __nPoints + i,__y +  VSPACE,__x +  __nSamples - __nPoints + i,__y +  __h - VSPACE,line3, sf::Color(192,192,192));
      }
     
      yPos = VSPACE + __h * (1  - (points[arrayPos] - __minValue) / (__maxValue - __minValue));
      
      // Draw a point for the first item, then connect all the other points with lines
      if (i == 0)
      { 
      	 sf::Vertex line4[1];
         point( __x +__nSamples - __nPoints + i, __y +  yPos, line4,   __color);//first point
      }
      else
      { 
      	sf::Vertex line5[2];
        line(  __x + prevX,__y +  prevY,__x +    __nSamples - __nPoints + i,__y +  yPos,line5, __color);//plot
      }
      prevX = __nSamples - __nPoints + i;
      prevY = yPos;
    }
  }
  
  void line(int x, int y, int x1, int y1, sf::Vertex line[2] ,sf::Color c)
  {
  	  
	line[0] = 
    		sf::Vertex(sf::Vector2f(x, y), c);
    	line[1] = 
    		sf::Vertex(sf::Vector2f(x1, y1), c);
	

	parent_pnt->draw(line, 2, sf::Lines);
  }
  	
   void point(int x, int y , sf::Vertex  loc[1], sf::Color c)
  {
  	   
	loc[0] = 
    		sf::Vertex(sf::Vector2f(x, y), c);
	

	parent_pnt->draw(loc, 1, sf::Points);
  }
 
  void plot(double value)
  {
    addData(value);
    display();
  }
  
   double  radians(double degree) {
    	double r = degree * M_PI / 180.0;
       return r;
   } 
  
private:   	
  template <typename T>
  std::string format(const T a_value, const int n = 1)
  {
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
  }
  
  float d ; 
  std::string minString;  // minimum value as a string
  std::string maxString;  // maximum value as a string
  
 sf::Color __color;
   
  float prevX;    // remember previous point
  float prevY;
   
 
   int rightSpace ;
   int VSPACE ;
   int HSPACE ;
};
