//CODIGO PARA EL MAESTRO (ARDUINO UNO)
#include <SoftwareSerial.h> 
SoftwareSerial blue(2,3);


    #include <TinyGPS.h>
    #include <SFE_BMP180.h>
    #include <DHT.h>
    #include <Wire.h> 

    #define DHTPIN 4               //PIN(4)
    #define DHTTYPE DHT22              //Tipo de dht
    DHT dht(DHTPIN,DHTTYPE);
    SFE_BMP180 pressure;            //SDA(A4) SCL(A5)                      
    TinyGPS gps;
    //SoftwareSerial ss(5,6);       //TX(2) ; RX(3)


    
String inc = "";
char income;
int bandera = 0;
int Dato = 0;
const int pulsador = 8;

  int encendido = 0;

char v;
String k,a;

void setup(){
  Serial.begin(9600);
  blue.begin(9600);
      //ss.begin(9600);
      dht.begin();
      pressure.begin();
      
  pinMode(pulsador,INPUT);
  digitalWrite(pulsador,LOW);
}

void loop() {
    if(Serial.available()>0)
   {
    income = ((byte)Serial.read());
    inc+=income;
   }

   if(inc== "INICIO")
   bandera = 1;
   if(inc=="IGNICION")
   bandera = 2;
   if(digitalRead(pulsador)==HIGH)
   bandera=3;
   if(inc=="" && blue.available()>0)
   bandera=4;

   switch(bandera){
    case 1:
    sensores();
    break;
    
    case 2:
    movimiento();
    break;

    case 3:
    manual();
    break;

    case 4:
    envio();
    break;
   }
}

void sensores(){
  blue.write('1');
  inc="";
  bandera=0;
}

void envio(){
  
  if (blue.available()>0)
  {
  Dato = blue.read();
    if (Dato == '%')
    {
      while(1)
      {
        v = blue.read();
        if (v == '/')
        {a = k;
         k = "";
            encendido = 1;
            
        break;}
        else
        {
          if (v >0){
            k+=v;
          }
        }
      }
    }
  //Serial.println(Dato-48);
  //delay(200);
  }
 if (encendido == 1)
 {
            char s2;
            double T,P;
            float h,t;
            h=dht.readHumidity();
            t=dht.readTemperature();
            s2 = pressure.startPressure(3);
            if(s2!=0)
            {s2=pressure.getPressure(P,T);}

          Serial.print("-17,5467");
          Serial.print("LAT\t");
          Serial.print("-64,7658");
          Serial.print("LONG\t");
          Serial.print(h);
          Serial.print("%\t");
          Serial.print(t);
          Serial.print("C\t");
          Serial.print(P*100);
          Serial.print("hPa\t");
          Serial.println(a);
          delay(200);
 }
  /*if (Serial.available()>0)
    {
      bandera = 2;
      inc ="";                                
    }*/              
}

void movimiento(){
  Serial.println("IGNICION");
  inc="";   
}

void manual(){
  Serial.println("MANUAL");
  inc="";
}

