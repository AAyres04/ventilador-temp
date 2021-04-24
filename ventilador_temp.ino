int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;        //The variable we will use to store temperature in degrees. 
char serialInput;
String result = "";
double maxTemp = 70;
unsigned long lastTempRead = 0;
unsigned long lastUserTempInput = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
  pinMode(13, OUTPUT);    // sets the digital pin 13 as output
}
void loop() {
  // put your main code here, to run repeatedly:
  // Check the input every 50 milisecs.
  if(millis() - lastUserTempInput >=50) {
    lastUserTempInput = millis();
    userTempInput();
  }
  // Check the temperature every 1000 milisecs (1 sec).
  if(millis() - lastTempRead >=1000) {
    lastTempRead = millis();
    tempRead();
  }
}

void tempRead(){
  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees
  if(temp > maxTemp){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  Serial.print("Current Temperature: ");
  Serial.println(temp);
}

void userTempInput(){
  if(Serial.available()){
    serialInput=Serial.read();
    result.concat(serialInput);
  }else if(!Serial.available() && result!=""){
    Serial.println("New max temp: " + result);
    maxTemp = result.toDouble(); // 0 if invalid
    result="";
  }
}