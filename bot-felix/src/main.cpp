#include "settings.cpp"


//OUR Libraries:
#include "lib_LCDDisplay.cpp" //included arduino main library
#include "lib_LEDMatrix.cpp"  //included arduino main library
#include "lib_TiltSensor.cpp" //included arduino main library
#include "lib_DHT.cpp"
#include "lib_RTC.cpp"

//--Loop------------------------------------------------------------------------

void loop() {
  //dispNeigung(tilt);
  botLiegt = readNeigung(tilt);
  //Schleife um zu testen, ob der Bot liegt oder nicht
  if(!botLiegt){

    //testen, ob wir nicht die gewünschten wiederhohlungen überschreiten
      if(countLernWiederhohlungen + 1 == counterButtonWiederhohlungen){
          istLetzterDurchgang = true;
        }
      if(countLernWiederhohlungen < counterButtonWiederhohlungen){
        //Funktion zum Stellen auf undefiniert, start und stop für den start Button
        if(digitalRead(buttonStart) == HIGH){
          counterButtonStart++;
          Serial.println(counterButtonStart);
            delay(500);
          if(counterButtonStart ==3){
            counterButtonStart = 0;
          } 
        } 

        //Auswahl der Lernzeit Wiederhohlungen wird nur ausgeführt, wenn der Start knopf noch nicht gedrückt wurde
        if(counterButtonStart == 0){
          //Auswahl der Lernzeit wiederhohlungen:
          lernzeitAuswahl();
        } else if(counterButtonStart == 1){ //Wird eingeleitet, wenn der Knopf gedrückt wurde um den Lernvorgang zu starten
            lerne();
        } else if(counterButtonStart == 2){ //Wird eingeleitet, wenn der Knopf gedrückt wurde um den Lernvorgang zu stoppen
            displayText("Felix: ", "Du hast aufgehoert zu lernen!");
        } else if(counterButtonStart == 3){
          // noch nicht implementiert, mögliches zurücksetzen
        }

      }  else {
        displayText("Felix: ", "Du hast alle Wiederhohlungen absolviert!");
      }
  
  } else {
    sleep();
    
 }  
}

void sleep() {
    emoji_sleep();
    displayText("Felix:", "zzzz...zz...zzzzzzzzz...zzzzzzzz...zzzzzz...zzzzzz...zzzzzzzzzzzz...");
}


//Funktion zum Auswählen der Wiederhohlungen
void lernzeitAuswahl(){
  if(digitalRead(buttonWiederhohlungen) == HIGH){
        counterButtonWiederhohlungen++;
        Serial.println(counterButtonWiederhohlungen);
        delay(500);
        if(counterButtonWiederhohlungen == 11){
        counterButtonWiederhohlungen = 1;
        }
      } 
      lernAnzahl = "Durchläufe: " + counterButtonWiederhohlungen;
      displayText("Felix:", (String)counterButtonWiederhohlungen);
}


//Funktion für den Lerntimer
void lerne(){
  //Beginn mit dem Lernablauf (mit gesetztem counter) wenn der start Knopf gedrückt wird

  //Teste ob die Temperatur (und Luftfeuchtigkeit) zum lernen geeignet sind
  if(guteTemperatur()){
    lerntGerade = LearnTimer(0.20,0.10);
    if(lerntGerade){
      //Serial.println("Lernphase");
      //matrix.clear();
      emoji_happy();
      displayText("Felix:", "Es ist Zeit zu lernen!");
    } else{
      //Serial.println("Pause");
      //matrix.clear();
      emoji_smile();
      displayText("Felix:", "Jetzt solltest du eine Pause machen!");
    }

    if(lerntGerade != hatGelernt){
      Serial.println(lernzeit);
      if(lerntGerade){
        //code für die Lernphase
        hatGelernt = true;
      } else{
        hatGelernt = false;
      } 
    }
  } else{
    //matrix.clear();
    emoji_cry();
    displayText("Felix:", "Bei der Temperatur kannst du nicht vernünftig lernen!");
  }
}
