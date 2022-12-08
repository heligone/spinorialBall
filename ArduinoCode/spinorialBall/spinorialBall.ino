#include <Adafruit_NeoPixel.h>

#define PIN 12
#define N_LEDS 32

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* carte arduino feather 32u4 basic proto 
 *  
 */

/* Adafruit feather 32u4 basic proto 
 * Adafuit BNO055 9DOF Inertial Measurment unit
 * 
 *  Connections
   ===========
   Connect SCL to SCL pin (analog 3 on Arduino Feather 32u4)
   Connect SDA to SDA pin (analog 2 on Arduino Feather 32u4)
   Connect Analog 12 to LED DATA BUS
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

int isCalibrated;
uint8_t system0, gyro0, accel0, mag0;
unsigned long currentTime=0;
unsigned long previousTime=0;

int initTest;
imu::Quaternion quat_i;
imu::Quaternion quat_raw;
imu::Quaternion quat;


/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void) {
  initTest = 1;
  isCalibrated = 0;

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  Serial.begin(115200);
  //Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor in Gyroscope mode only - no magnetic sensor*/
  if (!bno.begin( OPERATION_MODE_IMUPLUS )) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

   // bno.Adafruit_BNO055::setMode(OPERATION_MODE_IMUPLUS);

  delay(1000);
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void) {


  while (isCalibrated == 0) {
      chase(strip.Color(255, 0, 0));
      system0 = gyro0 = accel0 = mag0 = 0;
      bno.getCalibration(&system0, &gyro0, &accel0, &mag0);
         displayCalStatus();

      if (gyro0 == 3 && mag0 >= 0) {
        isCalibrated = 1;
      }
    }

  double gamma;
  double delta;

  if (initTest == 1) {
      for (int i = 0; i <= 31; i++) {
      strip.setPixelColor(i, (0, 255, 0));
      strip.clear();
      //chase(strip.Color(255, 0, 0));
          }
       previousTime=millis();
       currentTime=millis();
       while ((currentTime-previousTime)<5000)
         {
          currentTime=millis();
      chase(strip.Color(0, 255, 0));
        }
            
    /* Get initial sensor event */
    sensors_event_t event0;
    bno.getEvent(&event0);
    quat_i = bno.getQuat();
    initTest = 0;
    delay(BNO055_SAMPLERATE_DELAY_MS);
  }


  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Debug info*/
  int8_t mode = bno.Adafruit_BNO055::getMode();

  /* Optional: Display calibration status */
   displayCalStatus();
  // displaySensorStatus();

/* Initialise rotation position*/
  quat_raw = bno.getQuat();
  quat = quat_raw * quat_i.conjugate() * (-1.0);
  quat.normalize();

  double norm_up = sqrt(quat.w() * quat.w() + quat.z() * quat.z());
  double norm_down = sqrt(quat.x() * quat.x() + quat.y() * quat.y());

  // phases entre -pi et pi
  if (norm_up != 0) {
    gamma = acos(quat.w() / norm_up);
    if (quat.z() > 0) {
      gamma = -gamma;
    }
  } else {
    gamma = 0;
  }

  if (norm_down != 0) {
    delta = acos(quat.y() / norm_down);
    if (quat.x() > 0) {
      delta = -delta;
    }
  } else {
    delta = 0;
  }

  // entre 0 et 65536
  int gamma2 = (int)((180 * (1 + gamma / PI))) * 65536 / 360;
  int delta2 = (int)((180 * (1 + delta / PI))) * 65536 / 360;

  int sat_up = norm_up * 255;
  int sat_down = norm_down * 255;

  uint32_t rgbcolor1 = strip.gamma32(strip.ColorHSV(gamma2, 255, sat_up));
  uint32_t rgbcolor0 = strip.gamma32(strip.ColorHSV(delta2, 255, sat_down));

/* Set LED colors */
  strip.setPixelColor(0, rgbcolor0);
  strip.setPixelColor(1, rgbcolor1);
  strip.setPixelColor(2, rgbcolor0);
  strip.setPixelColor(3, rgbcolor1);
  strip.setPixelColor(4, rgbcolor0);
  strip.setPixelColor(5, rgbcolor1);
  strip.setPixelColor(6, rgbcolor0);
  strip.setPixelColor(7, rgbcolor0);
  strip.setPixelColor(8, rgbcolor0);
  strip.setPixelColor(9, rgbcolor1);
  strip.setPixelColor(10, rgbcolor0);
  strip.setPixelColor(11, rgbcolor0);
  strip.setPixelColor(12, rgbcolor1);
  strip.setPixelColor(13, rgbcolor0);
  strip.setPixelColor(14, rgbcolor0);
  strip.setPixelColor(15, rgbcolor1);
  strip.setPixelColor(16, rgbcolor0);
  strip.setPixelColor(17, rgbcolor0);
  strip.setPixelColor(18, rgbcolor1);
  strip.setPixelColor(19, rgbcolor0);
  strip.setPixelColor(20, rgbcolor0);
  strip.setPixelColor(21, rgbcolor1);
  strip.setPixelColor(22, rgbcolor0);
  strip.setPixelColor(23, rgbcolor0);
  strip.setPixelColor(24, rgbcolor1);
  strip.setPixelColor(25, rgbcolor0);
  strip.setPixelColor(26, rgbcolor1);
  strip.setPixelColor(27, rgbcolor0);
  strip.setPixelColor(28, rgbcolor1);
  strip.setPixelColor(29, rgbcolor0);
  strip.setPixelColor(30, rgbcolor1);
  strip.setPixelColor(31, rgbcolor0);

  //strip.fill(rgbcolor1);
  strip.show();

  /* Debug Info : Display the quat data */
  Serial.print("Mode");
  Serial.print(mode);
  Serial.print(",");
  Serial.print("qW:");
  Serial.print(quat.w(), 4);
  Serial.print(",");
  Serial.print("qX:");
  Serial.print( quat.x(), 4);
  Serial.print(",");
  Serial.print("qY:");
  Serial.print( quat.y(), 4);
  Serial.print(",");
  Serial.print("qZ:");
  Serial.println(quat.z(), 4);

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();
  //Serial.println();

  /* New line for the next sample */
  //Serial.println("");

  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}


/* LED chase Blink */
static void chase(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i, c);      // Draw new pixel
    strip.setPixelColor(i - 4, 0);  // Erase pixel a few steps back
    strip.show();
    delay(10);
  }
}

/* Code below from Adafruit open Source libraies */
/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
    
*/
/**************************************************************************/
void displaySensorDetails(void) {
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" xxx");
  Serial.print("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" xxx");
  Serial.print("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
*/
/**************************************************************************/
void displaySensorStatus(void) {
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  Serial.println("");
  Serial.print("System Status:0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void) {
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system) {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.println(system, DEC);
  Serial.print("G:");
  Serial.println(gyro, DEC);
  Serial.print("A:");
  Serial.println(accel, DEC);
  Serial.print("M:");
  Serial.println(mag, DEC);

  
}
