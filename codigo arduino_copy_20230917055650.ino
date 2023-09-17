////TERMO Y LUXO///
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define PIN_WIRE_SDA         ()
#define PIN_WIRE_SCL         ())
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <BH1750.h>
BH1750 lightMeter;
#include <SPI.h>    // incluye libreria interfaz SPI
#include <SD.h>     // incluye libreria para tarjetas SD
#define SSpin 53    // Slave Select en pin digital 53
File archivo;     // objeto archivo del tipo File
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels

/////////////AQUI VA REALMENTE EL PROGRAMA/////////////
void setup() {
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  mlx.begin();  
  Wire.begin();
  lightMeter.begin();
  
  //Serial.println(F("BH1750 Test"));
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);  
  pixels.clear(); // Set all pixel colors to 'off'
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA PRIMERA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos11.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA PRIMERA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA SEGUNDA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos12.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA SEGUNDA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA TERCERA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos13.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA TERCERA SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA cuarta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos14.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA cuarta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA quinta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos15.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA quinta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA sexta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos16.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA sexta SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA septima SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos17.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA septima SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA octava SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos18.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA octava SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA novena SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos19.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA novena SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////A PARTIR DE AQUI COMIENZA decima SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD   
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos10.txt", FILE_WRITE); // apertura para lectura/escritura de archivo, UN NOMBRE DIFERENTE PARA CADA SERIE DE MEDICIONES 
if (archivo) {  
  for (int i=0; i < 60; i++){     //MEDIR SIN LU PARA ESTABILIZAR TEMPERATURA INICIAL
  float lux = lightMeter.readLightLevel();
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
    archivo.print(i/4 ); //////////////////AQUI COMMIENZA A ESCRIBIREN ARCHIVO
    //archivo.print(" \tAmbiente = ");
    archivo.print(mlx.readAmbientTempC()  ); 
    //archivo.print("ºC\tObjeto = "); 
    archivo.print(mlx.readObjectTempC() ); 
    //archivo.print("ºC");
    //archivo.print("\tLight= ");
    archivo.println(lux);
    //archivo.println("lx"); 
    Serial.print(i/4  );//////////////ESTA PARTE ES PARA ESCRIBIR EN MONITOR
    Serial.print("\tAmbiente = "  );
    Serial.print(mlx.readAmbientTempC() ); 
    Serial.print("ºC\tObjeto = "  ); 
    Serial.print(mlx.readObjectTempC()  ); 
    Serial.print("ºC" );
    Serial.print("\tLight= "  );
    Serial.print(lux  );
    Serial.println("lx");
  delay (250);   //////////////////////////////////TIEMPO ENTRE MEDICION Y MEDICION
  }
for (int i=60; i < 180; i++){ // MEDIR CON LUZ PRENDIDA
 float lux = lightMeter.readLightLevel();   
pixels.setPixelColor(1,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(2,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(3,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(4,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(5,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(6,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(7,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(8,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(9,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(10,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(11,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(12,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(13,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(14,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(15,pixels.Color(83.94,131.98,66.98));
pixels.setPixelColor(16,pixels.Color(83.94,131.98,66.98));
pixels.show();   // Send the updated pixel colors to the hardware.
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()  ); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()   ); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4  );
  Serial.print("\tAmbiente= "  );
  Serial.print(mlx.readAmbientTempC() ); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight=  ");
  Serial.print(lux  );
  Serial.println("lx");
delay(250);
}
for (int i=180; i < 421; i++){     /// APAGAR LA LUZ Y VOLVER A ESTABILIZAR LA TEMPERATURA
  float lux = lightMeter.readLightLevel();  
  pixels.clear(); // Set all pixel colors to 'off' 
  pixels.show();   // Send the updated pixel colors to the hardware. 
  archivo.print(i/4 );
  //archivo.print(" \tAmbiente = ");
  archivo.print(mlx.readAmbientTempC()); 
  //archivo.print("ºC\tObjeto = "); 
  archivo.print(mlx.readObjectTempC()); 
  //archivo.print("ºC");
  //archivo.print("\tLight= ");
  archivo.print(lux);
  //archivo.println("lx");
  Serial.print(i/4);
  Serial.print("\tAmbiente = "  );
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "  ); 
  Serial.print(mlx.readObjectTempC()  ); 
  Serial.print("ºC" );
  Serial.print("\tLight= "  );
  Serial.print(lux);
  Serial.println("lx");       
    delay (250);
}
  archivo.close();        // cierre de archivo
  Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie 
}
else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////TERMINA decima SERIE DE MEDICIONES////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void loop () {      // funcion loop() obligatoria de declarar pero no utilizada

  // nada por aqui
}
