#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; 

void setup() {
 Serial.begin(9600);
 while (!Serial){
  ; // wait for serial port to connect. Needed for native USB port only
 }

Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  int16_t v1, v2, v3, mv1;
  //Read cell and module voltage. positive - negative
  v1 = analogRead(1)-analogRead(0);
  v2 = analogRead(3)-analogRead(2);
  v3 = analogRead(5)-analogRead(4);
  mv1 = analogRead(7)-analogRead(6);

  int16_t c1, c2, c3, mc1;
  //Read cell and module current. positive - reference
  c1 = analogRead(9)-analogRead(8);
  v2 = analogRead(10)-analogRead(8);
  v3 = analogRead(11)-analogRead(8);
  mv1 = analogRead(12)-analogRead(8);

  //create string from voltage and current reads
  String dataString = String(v1) + "," + String(v2) + "," + String(v3) + "," + String(mv1) + "," + String(c1) + "," + String(c2) + "," + String(c3) + "," + String(mc1);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println("writing data to file");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  }
  delay(1000);
}
