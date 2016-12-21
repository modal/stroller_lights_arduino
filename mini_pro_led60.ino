#include <Adafruit_NeoPixel.h>
//#include <Fast_LED.h>

#define LED_CNT                 60
#define LED_PIN                 11

#if 0

Board:    Arduino Pro or Pro Mini
CPU:      ATMEGA328 5V


#endif


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_CNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t white_clr = strip.Color(0xff, 0xff, 0xff);
uint32_t yellow_clr = strip.Color(0xff, 0xff, 0x00);
uint32_t red_clr = strip.Color(0x20, 0x00, 0x00);
uint32_t grn_clr = strip.Color(0x00, 0x20, 0x00);
uint32_t off_clr = strip.Color(0x00, 0x00, 0x00);

void setup()
{
    strip.begin();
    static int red = 0xff;
    static int blue = 0x40;
    static int green = 0x20;
    strip.setBrightness(0xb0);

    static int state = 0;

    //    while(1)
    //    {
    //      static int j = 0;
    //      strip.setPixelColor(j, red, blue, green);       //red/blue/green
    //
    //
    //
    //      delay(10);
    //      strip.show();
    //      j = ++j % LED_CNT;
    //      if((LED_CNT - 1 ) == j)
    //      {
    //          int temp = 0;
    //          temp = red;
    //          red = green;
    //          green = blue;
    //          blue = temp;
    //      }
    //    }

    int front_cnt = 0;

#define LOW_YEL        5
#define UP_YEL        (LED_CNT - 5)
#define LO_WHT        24
#define HI_WHT        35
    while(1)
    {
        for(int j = 0; j < LED_CNT; j++)
        {
            if(j < LOW_YEL || j > UP_YEL )
            {
                if(state)
                {
                    strip.setPixelColor(j, yellow_clr);
                }else {
                    strip.setPixelColor(j, off_clr);
                }
                continue;
            }

            if(j > LO_WHT && j < HI_WHT)
            {
                //static int state_loc = 0;

                if(front_cnt % 3)
                {
                    strip.setPixelColor(j, off_clr);
                }else
                {
                    strip.setPixelColor(j, white_clr);
                }
            }

            if(((j > LOW_YEL) && j < (LO_WHT + 1)))
            {
                switch(front_cnt)
                {
                    default:
                        strip.setPixelColor(j, off_clr);
                        continue;
                    case 1:
                        strip.setPixelColor(j, red_clr);
                        continue;
                    case 5:
                        strip.setPixelColor(j, grn_clr);
                        continue;
                }
            }
            if((j > (HI_WHT - 1)) && j < UP_YEL)
            {
                switch(front_cnt)
                {
                    default:
                        strip.setPixelColor(j, off_clr);
                        continue;
                    case 2:
                        strip.setPixelColor(j, grn_clr);
                        continue;
                    case 6:
                        strip.setPixelColor(j, red_clr);
                        continue;
                }
            }
        }
        delay(100);
        strip.show();
        state ^= 1;
        front_cnt = ++front_cnt % 8;
    }
}

void loop()
{}
