#include "settings.cpp"

unsigned long matrix_previousTime = millis();

//--Gesichter Presets--------------------------------------------------------------------------
static const uint8_t PROGMEM
  
    smile1_bmp[] =
  { B00000000,
    B00000000,
    B01000010,
    B10100101,    
    B00000000,
    B00000000,
    B00100100,
    B00011000 },
    smile2_bmp[] =
  { B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000,
    B00100100,
    B00011000 },
     angry1_bmp[] =
  { B00000000,
    B00000000,
    B10100101,
    B01000010,    
    B10100101,
    B00000000,
    B00000000,
    B00111100 },
    angry2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111100 },
   happy1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000 },
  happy2_bmp[] =
  { B00000000,
    B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
    cry1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B11100111,    
    B00000000,
    B00000000,
    B00011000,
    B00100100 },
    cry2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B01000000,
    B00000000,
    B00000000 },
    cry3_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B01000010,
    B00000000,
    B01000000 },
    cry4_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B00000000,
    B00000010,
    B01000010 },
    sleep1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11100111,
    B00000000,
    B00000000,
    B00000000 },
  sleep2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
     B11100111,
    B00000000,
    B00000000 };

//--LED Matrix------------------------------------------------------------------------

//Funktionen welche verschiedene (animierte) Gesichter auf der LED Matrix darstellen können

void emoji_happy(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, happy1_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, happy2_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_smile(){
   matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, smile1_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, smile2_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_angry(){
   matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, angry2_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
  } 

  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, angry1_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_cry(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 300 && currentTime - matrix_previousTime < 600) {
    matrix.clear();
    matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry2_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  } 

  if(currentTime - matrix_previousTime > 600 && currentTime - matrix_previousTime < 900){
    matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry3_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();   
  } 

  if(currentTime - matrix_previousTime > 900){
    matrix.clear();
     matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry4_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay(); 
    matrix_previousTime = currentTime;
  } 
}

void emoji_sleep(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, sleep1_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, sleep2_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}
