#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
   
static int frameCount = 0;
 
 
class Stripchart   
{

public:	
	Stripchart ( sf::RenderWindow& parent, 
					int x, 
					int y, 
					int nSamples, 
					int h, 
					int period,
					sf::Color color , 
 	   				float minValue, 
 	   				float maxValue )
{
	parent_pnt = &parent; 
        
        this->x = x;
      	this->y = y;
      	this->nSamples = nSamples; 
      	this->h = h;
      	this->period = period;
        this->color = color;
    	
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
}
//------------------------------------------------------------------------------  
 
  /*
   * Add a data points to be plotted.
   *
   * @param value the value to plot
   *
   */

void addData(double value)
{
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
//------------------------------------------------------------------------------

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
   
    rectangle.setPosition(0.0f, 0.0f);
    //size del rettangolo
    sf::Vector2f rect_size( nSamples + rightSpace + 2 * HSPACE,  h + 2 * VSPACE);
    rectangle.setSize(rect_size); 
    
    rectangle.setFillColor(sf::Color( 255,255,255,0));
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
    
    //space for legend 
    rightSpace = (int)std::max( rectw1, rectw2); 
    
    parent_pnt->draw( rectangle );
    parent_pnt->draw( text1 );
    parent_pnt->draw( text2 );
    
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    
    //chart'axis
    line( 
    		x + HSPACE, 
    		y + VSPACE + h/2, 
    		x + nSamples + rightSpace - HSPACE, 
    		y + VSPACE + h/2, 
    		line1, 
    		sf::Color(192,192,192)
    	); 
    
    line(  
    		x + nSamples + 1, 
    		y + VSPACE,  
    		x + nSamples + 1, 
    		y + h - VSPACE,
    		line2, 
    		sf::Color(192,192,192)
    	);
   
    for(int i = 0; i <  nPoints; i++)
    {
	arrayPos = ( startPos + i) %  nSamples;
      
        if ( period > 0 && arrayPos %  period == 0)//linea verticale
        {
        	sf::Vertex line3[2];
        
        	line( 
        		x + nSamples - nPoints + i,
        		y + VSPACE, 
        		x + nSamples -  
        		nPoints + i, 
        		y + h -VSPACE,
        		line3, 
        		sf::Color(192,192,192)
        	    );
         }
         yPos = VSPACE + h * (1 - (points[arrayPos] - minValue) / (maxValue - minValue));
      
         // Draw a point for the first item, then connect all the other points with lines
         if (i == 0)
         { 
		sf::Vertex point1[1];
		//first point
	        point(  
	        	x + nSamples - nPoints + i,  
	        	y +  yPos, point1,    
	        	color
	             ); 
      	 }
         else
         { 	//plot line
		sf::Vertex line4[2];
        
        	line(  
        		x + prevX, 
        		y + prevY, 
        		x + nSamples - nPoints + i, 
        		y + yPos,
        		line4,  
        		color
        	    );
         }
         
         prevX = nSamples - nPoints + i;
         prevY = yPos;
    }
     
  }
//------------------------------------------------------------------------------  
 
  void plot(double value)
  {
	addData(value);
    	display();
  }
//------------------------------------------------------------------------------
  
  double  radians(double degree) 
  {
    	return  degree * M_PI / 180.0;
       
  } 
//------------------------------------------------------------------------------  
  
  void line(int x, int y, int x1, int y1, sf::Vertex line[2] ,sf::Color c)
  {
  	  
	line[0] = 
    		sf::Vertex(sf::Vector2f(x, y), c);
    	line[1] = 
    		sf::Vertex(sf::Vector2f(x1, y1), c);
	
	parent_pnt->draw(line, 2, sf::Lines );
  }
//------------------------------------------------------------------------------
  	
  void point(int x, int y , sf::Vertex  loc[1], sf::Color c)
  {
  	  loc[0] = 
    		sf::Vertex(sf::Vector2f(x, y), c);
	
	  parent_pnt->draw(loc, 1, sf::Points);
  }
//------------------------------------------------------------------------------
 	
  template <typename T>
  std::string format(const T a_value, const int n = 1)
  {
	std::ostringstream out;
    	out << std::setprecision(n) << a_value;
    	return out.str();
  }
 
  int  x;           // horizontal position of chart
  int  y;           // vertical position of chart

private:
  int  nSamples;    // number of samples to display (affects width)
  int  h;           // height of chart
  int  dataPos;     // where does next data point go?
  int  startPos;    // where do we start plotting?
  int  nPoints;     // number of points currently in the array
  int  period;      // how often to draw a gray line
  float  minValue;  // minimum value to display
  float  maxValue;  // maximum value to display
  float *points;    // the data points to plot
  float d ;
   
   //SFML  types
  sf::Font font;
  sf::RectangleShape rectangle;
  sf::RenderWindow* parent_pnt;
  sf::Color  color;
    
  std::string minString;  // minimum value as a string
  std::string maxString;  // maximum value as a string
  float prevX;    // remember previous point
  float prevY;
  int rightSpace ;
  int VSPACE ;
  int HSPACE ;

};
