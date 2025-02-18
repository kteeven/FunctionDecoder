
#include "dfPLayerFunctions.h"
// #include "Arduino.h"

void initDF(DFRobotDFPlayerMini &obj, SoftwareSerial &obj1)
{
  Serial.println("init DF PLAYER ... ");

  
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!obj.begin(obj1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  printHelp();
  
  obj.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  obj.volume(20);  //Set volume value (0~30).
 // myDFPlayer.volumeUp(); //Volume Up
 // myDFPlayer.volumeDown(); //Volume Down
  
  //----Set different EQ----
  obj.EQ(DFPLAYER_EQ_NORMAL);
//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
  
  //----Set device we use SD as default----
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
obj.outputDevice(DFPLAYER_DEVICE_SD);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);
  
  //----Mp3 control----
//  myDFPlayer.sleep();     //sleep
//  myDFPlayer.reset();     //Reset the module
//  myDFPlayer.enableDAC();  //Enable On-chip DAC
//  myDFPlayer.disableDAC();  //Disable On-chip DAC
obj.outputSetting(true, 15); //output setting, enable the output and set the gain to 15
 


}
 void printHelp(){
    Serial.println("DFPlayer Commands:");
    Serial.println(" h - help");
    Serial.println(" > - next ");
    Serial.println(" < - previous");
    Serial.println(" p3 - play");
    Serial.println(" p3,5 - play folder 3, file 5");
    Serial.println(" P3,5 - play large folder 3, file 5");
    Serial.println(" P3 - play file 3 in MP3 folder"); 
    Serial.println(" + - volume up");
    Serial.println(" - - volume down");
    Serial.println(" v10 - set volume to 10");
    Serial.println(" b - Pause");
    Serial.println(" s - start ");
    Serial.println(" z - sleep ");
    Serial.println(" L - enable loop all");
    Serial.println(" l - disable loop all");
    Serial.println(" L3 - loop folder 3");
    Serial.println(" l3 - loop file 3");
    Serial.println(" A3 - advertise file 3");
    Serial.println(" a - stop advertise "); 
    Serial.println(" qx - query No. x");
    Serial.println("     x = 1 - read state");
    Serial.println("     x = 2 - read volume");
    Serial.println("     x = 3 - read equalizer");
    Serial.println("     x = 4 - read file counts");
    Serial.println("     x = 5 - read current file number");
    Serial.println("     x = 6 - read file counts in folder");
    Serial.println("     x = 7 - read folder counts");
  }

void readCommand(DFRobotDFPlayerMini &obj){
    char cmd = ' ';
    int value1, value2 = 0;
    cmd = Serial.read();
    value1 = Serial.parseInt();
    value2 = Serial.parseInt();
   
    Serial.print(("Value1 = "));
    Serial.println((value1));
    Serial.print(("Value2 = "));
    Serial.println((value2));
    switch(cmd){
      case 'h': 
        printHelp();
        break;
        
      case '>':
        obj.next();
        break;
        
      case '<':
      obj.previous();
        break;
        
      case 'p':
        if(value2 == 0) obj.play(value1);
        else if(value1 != 0) obj.playFolder(value1, value2);
        break;
   
      case 'P':
        if(value2 == 0) obj.playMp3Folder(value1); 
        else if(value1 != 0)obj.playLargeFolder(value1, value2);
        break;
      
      case '+':
      obj.volumeUp(); 
        break;
        
      case '-':
      obj.volumeDown();
        break;
        
      case 'v':
      obj.volume(value1);
        break;
        
      case 'b':
      obj.pause();
        break;
   
      case 's':
      obj.start();
        break;
            
      case 'z':
      obj.sleep();
        break;
        
      case 'L':
        if(value1 == 0) obj.enableLoopAll();
        else obj.loopFolder(value1);
        break;
      
      case 'l':
        if(value1 == 0) obj.disableLoopAll();
        else obj.loop(value1);
        break;
      
      case 'A':
      obj.advertise(value1);
        break;
      
      case 'a':
      obj.stopAdvertise();
        break;
      
      case 'q':
        if(value1 == 1) Serial.println(obj.readState()); 
        else if(value1 == 2) Serial.println(obj.readVolume());
        else if(value1 == 3) Serial.println(obj.readEQ());
        else if(value1 == 4) Serial.println(obj.readFileCounts());
        else if(value1 == 5) Serial.println(obj.readFolderCounts());
        else if(value1 == 6) Serial.println(obj.readCurrentFileNumber());
        break;
      default:
        Serial.println("Ungültiges Kommando");
        break;
    }
   
   }


   void printDetail(uint8_t type, int value){
    switch (type) {
      case TimeOut:
        Serial.println(F("Time Out!"));
        break;
      case WrongStack:
        Serial.println(F("Stack Wrong!"));
        break;
      case DFPlayerCardInserted:
        Serial.println(F("Card Inserted!"));
        break;
      case DFPlayerCardRemoved:
        Serial.println(F("Card Removed!"));
        break;
      case DFPlayerCardOnline:
        Serial.println(F("Card Online!"));
        break;
      case DFPlayerUSBInserted:
        Serial.println("USB Inserted!");
        break;
      case DFPlayerUSBRemoved:
        Serial.println("USB Removed!");
        break;
      case DFPlayerPlayFinished:
        Serial.print(F("Number:"));
        Serial.print(value);
        Serial.println(F(" Play Finished!"));
        break;
      case DFPlayerError:
        Serial.print(F("DFPlayerError:"));
        switch (value) {
          case Busy:
            Serial.println(F("Card not found"));
            break;
          case Sleeping:
            Serial.println(F("Sleeping"));
            break;
          case SerialWrongStack:
            Serial.println(F("Get Wrong Stack"));
            break;
          case CheckSumNotMatch:
            Serial.println(F("Check Sum Not Match"));
            break;
          case FileIndexOut:
            Serial.println(F("File Index Out of Bound"));
            break;
          case FileMismatch:
            Serial.println(F("Cannot Find File"));
            break;
          case Advertise:
            Serial.println(F("In Advertise"));
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }  
  }