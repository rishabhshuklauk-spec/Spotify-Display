#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <driver/i2s.h>

#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define BTN_LEFT   32
#define BTN_MID    33
#define BTN_RIGHT  25

#define I2S_BCLK   26
#define I2S_LRC    27
#define I2S_DOUT   22

void setup() {
  Serial.begin(115200);
  Serial.println("Booting Spotify Display...");

  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_MID, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("System Ready!");
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Waiting for input...");

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = true
  };
  
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };
  
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

void loop() {
  if (digitalRead(BTN_LEFT) == LOW) {
    Serial.println("Previous Track Button Pressed");
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.println("Action: PREV TRACK");
    delay(200);
  }
  
  if (digitalRead(BTN_MID) == LOW) {
    Serial.println("Play/Pause Button Pressed");
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.println("Action: PLAY/PAUSE");
    delay(200);
  }
  
  if (digitalRead(BTN_RIGHT) == LOW) {
    Serial.println("Next Track Button Pressed");
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.println("Action: NEXT TRACK");
    delay(200);
  }
}
