
#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  57600
#define DXL_ID    2
char serial;
DynamixelWorkbench dxl_wb;
int motorSpeed = 0;
int flag = 0;
void setup() 
{
      pinMode(6, OUTPUT); 
        pinMode(5, OUTPUT); 
  Serial.begin(57600);
  // while(!Serial); // Wait for Opening Serial Monitor

  const char *log;
  bool result = false;

  uint8_t dxl_id = DXL_ID;
  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }

  result = dxl_wb.ping(dxl_id, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.wheelMode(dxl_id, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  else
  {
    Serial.println("Succeed to change wheel mode");
    Serial.println("Dynamixel is moving...");
  }
      digitalWrite(6, HIGH); 
}
void loop() 
{
  serial = Serial.read();
  uint8_t dxl_id = DXL_ID; 

  if (serial == 'a'){
    digitalWrite(6, LOW); 
    delay(10);
    flag = 1;
  } //power on
  
  if (serial == 'b'){
    digitalWrite(6, HIGH); 
    delay(10);
    flag = 2;
  } //power off
  
  if (serial == 'c'){
    Serial.println("K"); 
    delay(10); 
    Serial.println("X"); 
    delay(10);
  }
  if(flag == 1){
  if (serial == '0'){motorSpeed = -900; delay(100);} 
  if (serial == '1'){motorSpeed = -1400; delay(100);} 
  if (serial == '2'){motorSpeed = -1900; delay(100);} 
  if (serial == '3'){motorSpeed = -2400; delay(100);} 
  if (serial == '4'){motorSpeed = -2900; delay(100);}
  }
  else if(flag == 2){
    motorSpeed = 0;
    }
    dxl_wb.goalVelocity(dxl_id, motorSpeed);
    delay(10);
    serial = 0;
}
