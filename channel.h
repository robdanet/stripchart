#include "stripchart.h"
#define TRUE  1
#define FALSE 0
int frameCount;
class Channel  
{
public:
  sf::Color colour;    // color of dots to plot
  int dataPos;     // where does next data point go?
  int startPos;    // where do we start plotting?
  int nPoints;     // number of points currently in the array
  int  nSamples;    // number of samples (copy this from parent)
  float * points;  // the data points to plot
  Stripchart* parent;
  int period;
  float  minValue,  maxValue;
  bool visible;  // allows you to hide or show a channel
  
  int  h;           // height of chart
 Channel(){}
 ~Channel(){}
 
  Channel(Stripchart& parent, int nSamples, int h, int period, sf::Color colour , 
 						 float minValue, float maxValue)
  {
    nPoints = 0;
    dataPos = 0;
    startPos = 0;
    
    this->nSamples =  nSamples;
    this->period = period;
    this->h = h;
    points = new float[ nSamples];
    this->colour = colour;
    visible = TRUE;
     this->parent = &parent;
     this->minValue = minValue;
     this->maxValue = maxValue;
  }
 
 
  void addData(float value)
  {
  
    if(value >  maxValue)value =  maxValue;
    else if(value <  minValue) value =  minValue;
    
    points[dataPos] = value;    
    dataPos = (dataPos + 1) % nSamples; // wrap around when array fills
    /*
     * If the array isn't full yet, add to the end of the array
     * Otherwise, the start point for plotting moves through
     * the array.
     */
    if (nPoints < nSamples)
    {
      nPoints++;
    }
    else
    {
      startPos = (startPos + 1) % nSamples;
    }
  }

  void display()
  {
    int arrayPos;
    float yPos;
    VSPACE = 2;
    HSPACE = 2;
  /*  for (int i = 0; i < nPoints; i++)
    {
      arrayPos = (startPos + i) % nSamples;
      if ( period > 0 && arrayPos %  period == 0)
      {
        sf::Color col(192, 192, 192);
        sf::Vertex line1[2];
        parent->line(parent-> x + nSamples - nPoints + i, parent-> y + VSPACE,
        parent-> x +  nSamples - nPoints + i,  parent-> y +  h -  VSPACE, line1,  col);
      }
    //  if (visible)
    // {
         
        yPos =  VSPACE +
           h * (1 - (points[arrayPos] -  minValue) / ( maxValue -  minValue));

        // Draw a point for the first item, then connect all the other points with lines
        if (i == 0)
        {
          sf::Vertex point1[1];
          parent->point( parent-> x + nSamples - nPoints + i, parent-> y + yPos, point1, colour);
        }
        else
        {
           sf::Vertex line2[2];
           parent->line( parent-> x +    prevX, parent-> y + prevY, parent-> x  + nSamples - nPoints + i,
             parent-> y + yPos, line2, colour);
        }
        prevX = nSamples - nPoints + i;
        prevY = yPos;
     // }
    }/*/
    for(int i = 0; i <  nPoints; i++)
    {
      arrayPos = ( startPos + i) %  nSamples;
      if ( period > 0 && arrayPos %  period == 0)//linea verticale
      {
        sf::Vertex line3[2];
       parent-> line( parent->x +  nSamples -  nPoints + i, parent->y +  VSPACE, parent->x +   nSamples -  nPoints + i,parent-> y +   h - VSPACE,line3, sf::Color(192,192,192));
      }
     
      yPos = VSPACE +  h * (1  - (points[arrayPos] -  minValue) / ( maxValue -  minValue));
      
      // Draw a point for the first item, then connect all the other points with lines
      if (i == 0)
      { 
      	 sf::Vertex line4[1];
        parent-> point( parent-> x + nSamples -  nPoints + i, parent-> y +  yPos, line4,    colour);//first point
      }
      else
      { 
      	sf::Vertex line5[2];
     parent->   line(  parent-> x + prevX, parent->y +  prevY, parent->x +     nSamples -  nPoints + i,parent-> y +  yPos,line5,  colour);//plot
      }
      prevX =  nSamples -  nPoints + i;
      prevY = yPos;
    } 
    
    // parent->plot(parent->radians(frameCount % 360));
  }

  void toggle()
  {
    visible = ! visible;
  }
  protected:   
       
   float prevX;    // remember previous point
   float prevY;
   int rightSpace ;
   int VSPACE ;
   int HSPACE ;
};

 

