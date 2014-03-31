#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
   

//#define radians(angleDegrees) (angleDegrees * M_PI / 180.0) 
 
class Stripchart   {
 
public:	
  std::string title;
   
 Stripchart(){}
 ~Stripchart(){}
 
  Stripchart(sf::RenderWindow& parent, int x, int y, int nSamples, int h, int period,sf::Color color , 
 						 float minValue, float maxValue)
 	 					 
  {
     parent_pnt = &parent; 
     
     title = "Test";
     
      this->x = x;
      this->y = y;
      this->nSamples = nSamples; 
      this->h = h;
      this->period = period;
     
    // make sure minimum and max are in proper order
      this->minValue = std::min(minValue, maxValue);
      this->maxValue = std::max(minValue, maxValue);
     
    // and convert them to a string with minimal numbr of decimal places
    minString =  format( minValue);
    maxString =  format( maxValue);
     nPoints = 0;
     dataPos = 0;
     startPos = 0;
     points = new float[ nSamples];
    
    
    
     font.loadFromFile("sansation.ttf");
      this->color = color;
     
  }
  
 
 
  int  x;           // horizontal position of chart
  int  y;           // vertical position of chart
  int  nSamples;    // number of samples to display (affects width)
  int  h;           // height of chart
   
  int  dataPos;     // where does next data point go?
  int  startPos;    // where do we start plotting?
  int  nPoints;     // number of points currently in the array
  int  period;      // how often to draw a gray line
  float  minValue;  // minimum value to display
  float  maxValue;  // maximum value to display
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
    if(value >  maxValue)value =  maxValue;
    else if(value <  minValue) value =  minValue;
    
    
    points[ dataPos] = value;    
    dataPos = ( dataPos + 1) %  nSamples; // wrap around when array fills

    /*
     * If the array isn't full yet, add to the end of the array
     * Otherwise, the start point for plotting moves through
     * the array.
     */
    if ( nPoints <  nSamples)
    {
       nPoints++;
    }
    else
    {
       startPos = ( startPos + 1) %  nSamples;
    }
  }
 template <typename T>
  T& addChannel(T& channel) {
 
      return  channel;
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
    sf::Vector2f rect_size( nSamples + rightSpace + 2 * HSPACE,  h + 2 * VSPACE);
    rectangle.setSize(rect_size); 
    
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.move( x,  y);
    
    //valore massimo
    sf::Text text1(maxString, font,12);int rectw1 = text1.getLocalBounds().width;
    text1.setColor(sf::Color(0,0,0));
    text1.setPosition( nSamples + 2, VSPACE -2 );
    text1.move( x  ,  y ); 
  
    //valore minimo  
    sf::Text text2(minString, font,12);int rectw2 = text2.getLocalBounds().width;
    text2.setColor(sf::Color(0,0,0));
    text2.setPosition( nSamples + 2,  h - VSPACE-8);
    text2.move( x,  y);
 
    rightSpace = (int)std::max( rectw1, rectw2); 
    
    parent_pnt->draw( rectangle );
    parent_pnt->draw( text1 );
    parent_pnt->draw( text2 );
    
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    
    //assi della chart
    line( x + HSPACE,  y + VSPACE +  h / 2,  x +  nSamples + rightSpace - HSPACE, y + VSPACE +  h / 2, line1, sf::Color(192,192,192));
    
    line(  x+  nSamples + 1, y +  VSPACE,  x +     nSamples + 1, y +   h - VSPACE,line2, sf::Color(192,192,192));
   
    for(int i = 0; i <  nPoints; i++)
    {
      arrayPos = ( startPos + i) %  nSamples;
      if ( period > 0 && arrayPos %  period == 0)//linea verticale
      {
        sf::Vertex line3[2];
        line( x +  nSamples -  nPoints + i, y +  VSPACE, x +   nSamples -  nPoints + i, y +   h - VSPACE,line3, sf::Color(192,192,192));
      }
     
      yPos = VSPACE +  h * (1  - (points[arrayPos] -  minValue) / ( maxValue -  minValue));
      
      // Draw a point for the first item, then connect all the other points with lines
      if (i == 0)
      { 
      	 sf::Vertex line4[1];
         point(  x + nSamples -  nPoints + i,  y +  yPos, line4,    color);//first point
      }
      else
      { 
      	sf::Vertex line5[2];
        line(   x + prevX, y +  prevY, x +     nSamples -  nPoints + i, y +  yPos,line5,  color);//plot
      }
      prevX =  nSamples -  nPoints + i;
      prevY = yPos;
    }
     
  }
  
  void line(int x, int y, int x1, int y1, sf::Vertex line[2] ,sf::Color c)
  {
  	  
	line[0] = 
    		sf::Vertex(sf::Vector2f(x, y), c);
    	line[1] = 
    		sf::Vertex(sf::Vector2f(x1, y1), c);
	

	parent_pnt->draw(line, 2, sf::Lines );
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
  
 sf::Color  color;
 
  
       
   float prevX;    // remember previous point
   float prevY;
   int rightSpace ;
   int VSPACE ;
   int HSPACE ;
};
