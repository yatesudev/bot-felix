#include <Arduino.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();


namespace EmojiExpressions {
    extern void emoji_happy();
    extern void emoji_smile();
    extern void emoji_angry();
    extern void emoji_cry();
    extern void emoji_sleep();
}

