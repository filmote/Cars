/*
void move(Car thisCar, uint8_t pixels, int16_t roadUpper, int16_t roadLower) {

  if (thisCar.getEnabled()) {

    bool noCollisions_XY = true;
    bool noCollisions_X = true;
    bool noCollisions_Y = true;
  
    SQ7x8 x = thisCar.getX() - pixels - thisCar.getSpeedX();
    SQ7x8 y = thisCar.getY();

    if (x >= 0) {  // No steering for cars leaving screen ..
      
      switch (thisCar.getSteeringType()) {
    
        case (SteeringType::FollowRoad):
    
          if (thisCar.getRoadUpper() > 0 && thisCar.getRoadLower() > 0) {
    
            if (thisCar.getRoadUpper() > roadUpper) {      // Road is going up.
              y = y - 2;
            }
            else if (thisCar.getRoadUpper() < roadUpper) {      // Road is going down.
              y = y + 2;
            }
            
          }
    
          break;
    
        case (SteeringType::ZigZag):

          if (thisCar.getGoingUp()) {
    
            if (y.GetInteger() > roadUpper) {
              y = y - _speedY;        
            }
            else {
              thisCar.setGoingUp(!thisCar.getGoingUp());
            }
            
          }
          else {
            if (y.GetInteger() + (thisCar.getHeight()) < roadLower) {
              y = y + _speedY;        
            }
            else {
              thisCar.setGoingUp(!thisCar.getGoingUp());
            }
            
          }
          
          break;
    
        case (SteeringType::Random):
   
          randomCount--;
          
          if (randomCount == 0) {
            
            if (randomNumber > 0) {
              randomNumber = 0;
            }
            else {
              randomNumber = random((uint8_t)RoadType::First, (uint8_t)RoadType::Count);   
            }
      
            randomCount = random(15, 30);
            
          }
          
          switch ((RoadType)randomNumber) {
            
            case RoadType::Straight:
              break;
              
            case RoadType::Up:
//Serial.println("Up");
              if (y > roadUpper) {
                y = y - _speedY;
              }
              break;
              
            case RoadType::Down:
//Serial.println("Down");
              if (y < roadLower) {
                y = y + _speedY;
              }
              break;
              
          }
          
          break;
          
      }
      
    }
    
    for (uint8_t i = 0; i < 3; ++i) {
  
      const Car &car = _cars[i];
 //     car.debug();
  
      if (car != *this && car.getEnabled()) {

        
        if (collide(car.getRect(), thisCar.getRect(x.GetInteger(), y.GetInteger()))) {

          noCollisions_XY = false;
          

          if (collide(car.getRect(), thisCar.getRect(x.GetInteger(), thisCar.getY().GetInteger()))) {

            noCollisions_X = false;
            
          }

          else if (collide(car.getRect(), thisCar.getRect(thisCar.getX().GetInteger(), y.GetInteger()))) {

            noCollisions_Y = false;

          }
  
//          thisCar.debug();
          break;
  
        }
  
      }
  
    }

    // No collision occured with this 
    if (noCollisions_XY) {
//Serial.println("noCollisions_XY");      

      thisCar.setX(x); 
      thisCar.setY(y); 
  
    }
    else {
      
      if (noCollisions_X) { 
//Serial.println("noCollisions_X");      
        thisCar.setX(x); 
      }
      else  if (noCollisions_Y) { 
//Serial.println("noCollisions_Y");      
        thisCar.setY(y); 
      }
      else {
        thisCar.setX(thisCar.getX() - thisCar.getSpeedX()); 
      }
      

    }

    this.setRoadUpper(roadUpper);
    this.setRoadLower(roadLower);
  
//  Serial.print("thisCar.getWidth(): ");
//  Serial.print(thisCar.getWidth());
//  Serial.print(", thisCar.getX(): ");
//  Serial.print(thisCar.getX().GetInteger());
//  Serial.print(", enabled: ");
//  Serial.print(_enabled);
    _enabled = (thisCar.getWidth() + thisCar.getX().GetInteger() > 0);
//  Serial.print(", ");
//  Serial.println(_enabled);

//    if (!_enabled) {
//      Serial.print(F("Car_"));
//      Serial.print(thisCar.getName());
//      Serial.println(F(" enabled = false"));
//    }

  }
  
}
*/
