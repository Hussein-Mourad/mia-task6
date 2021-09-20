# Harry Maze

## Harry

- Set pinMode of components and set motor speed
- If the middle sensors only is HIGH then we are on the line and need to go forward
- If the left and and middle sensors are HIGH then we need to turn left
- If the left sensor only is HIGH then we need to go left as the line could be curved
- If the right and and middle sensors are HIGH then we need to turn right
- If the right sensor only is HIGH then we need to go right as the line could be curved
- If all the sensors are LOW then we are at a wrong edge and we need to go backwards
- If all sensors are HIGH then we reached our destination, so we need to stop

## Safe

- Set pin mode of encoders pins to input pull up and led to output
- Attach an interrupt on each encoder channels 
- Save the reading in each encoder counter
- Divide the counter by PPR multiplied by 4 as there are 4 interrupts for each pulse
- Multiply the value by 360 to convert it to degrees 
- Mod the value by 360 to cap it to 360
- If the first encoder's angle equals 37 then turn on the led
- If the second encoder's angle equals 10 then turn on the led
- If the third encoder's angle equals 54 then turn on the led
- Else turn it off after 100 ms