//extra libarie(s) som behöves för att projektet ska fungera
#include <Servo.h>

const double l = 8.1; // längden på det individuala lego segmenten av projektet
const double d = 5.15; // längden mellan servosen
const int dellay = 2000; // mängden delay mellan punkter
//double x = 2.5; // x kordinaten för där ytersa pungten ska hamna
//double y = 12; // y kordinaten 
 
//double c = sqrt(pow(x,2)+pow(y,2)); //petageras sats på x och y från origo(sträckan från en av servosen till ytersa pungten)

//double e = sqrt(pow((d-x),2)+pow(y,2)); //peragars sats på x och y från d distans från origo()

//double a1 = atan(y/x);

//double a2 = acos((l*l-c*c-l*l)/(-2*l*c));

//double b1 = atan(y/(d-x));

//double b2 = acos((l*l-l*l-e*e)/(-2*l*l*e));

//int a = a1 + a2;

//int b = 180 - (b1+b2);

//double t1 = (atan(y/x) + acos((pow(l,2) + pow(c,2) - pow(l,2))/(2*l*c))) ; // genom trigonometri så räknar jag ut ett 
//double t2 = (atan(y/(d-x)) + acos((pow(l,2) + pow(e,2) - pow(l,2))/(2*l*e)));

//int pos1 = t1 * (180/3.1415); // tar t1 och omvandlar det till ett använtbar vinkel i int format så att servon kan läsa det
//int pos2 = t2  * (180/3.1415); // tar t2 och omvandlar det till ett använtbar vinkel i int format så att servon kan läsa det
// skapar servo objekt
Servo myservo1;
Servo myservo2;

void setup() {
Serial.begin(9600); // startar serial monitorn
myservo1.attach(9);// sätter servo objekt till en pin på breadbordet
myservo2.attach(11);// sätter servo objekt till en pin på breadbordet
myservo1.write(90);// nollställer servosarna innan den sätter till en position
myservo2.write(90);
delay(5000); //delay så den tar 5 sekunder innan  den börjar så den har tid att nollställa
//Serial.println(a);
//Serial.println(b);//
//Serial.println(t1);
//Serial.println(t2);

}

void loop() {
  // skriver ut vinkarna i serial monitorn


// sätter servo vinklarna med lite kaliberring ut efter vad jag oberverat för mina servos
/* en före deta vertion som resulterade i väldigt korvade linjer
myservo2.write(180-poscalcy(2.5,15)-5);
myservo1.write(poscalcx(2.5,15)+3);
myservo2.write(180-poscalcy(2.5,15)-5);
myservo1.write(poscalcx(2.5,15)+3);
delay(dellay); // delay ifall jag vill sätta en till position
myservo1.write(poscalcx(1,5)+3);
myservo2.write(180-poscalcy(1,5)-5);
myservo1.write(poscalcx(1,5)+3);
myservo2.write(180-poscalcy(1,5)-5);
delay(dellay); // delay ifall jag vill sätta en till position
myservo1.write(poscalcx(5,14)+3);
myservo2.write(180-poscalcy(5,14)-5);
myservo1.write(poscalcx(5,14)+3);
myservo2.write(180-poscalcy(5,14)-5);
delay(dellay); // delay ifall jag vill sätta en till position
myservo1.write(poscalcx(0,14)+3);
myservo2.write(180-poscalcy(0,14)-5);
myservo1.write(poscalcx(0,14)+3);
myservo2.write(180-poscalcy(0,14)-5);
delay(dellay); // delay ifall jag vill sätta en till position
myservo1.write(poscalcx(4,5)+3);
myservo2.write(180-poscalcy(4,5)-5);
myservo1.write(poscalcx(4,5)+3);
myservo2.write(180-poscalcy(4,5)-5);
delay(dellay); // delay ifall jag vill sätta en till position
*/
raklinje(2.5,15,1,5); // kallar på min funktion som gör att den går i en rakare linje mellan x y start kodinater och x y slut kodinater
delay(dellay); // delay som mest ger klarhet när den är klar med en rörelse
raklinje(1,5,5,14);
delay(dellay);
myservo1.write(poscalcx(0,14)+3); // elfter som min funtion fungerar genom att ta ett luntning på sträkan den ska röra sig fungerar den inte när x/y star och destionation är samma så här måste jag gera den simplare
myservo2.write(180-poscalcy(0,14)-5);
myservo1.write(poscalcx(0,14)+3);
myservo2.write(180-poscalcy(0,14)-5);
delay(dellay);
raklinje(0,14,4,5);
delay(dellay);
raklinje(4,5,2.5,15);
delay(dellay);
}

int poscalcx(double x, double y){
double c = sqrt(pow(x,2)+pow(y,2)); //pythagoras sats på x och y från origo(sträckan från en av servosen till ytersta punkten)

double t1 = (atan(y/x) + acos((pow(l,2) + pow(c,2) - pow(l,2))/(2*l*c))) ; // genom trigonometri så räknar jag ut ett värde på vinkel mellan 0 och 180

 int pos1 = t1 * (180/3.1415); // tar t1 och omvandlar det till ett användbar vinkel i int format så att servon kan läsa det
  Serial.println(pos1);
 return pos1;
}

int poscalcy(double x, double y){

double e = sqrt(pow((d-x),2)+pow(y,2)); //pythagoras sats på x och y från d distans från origo i xled (sträckan från en av servosen till ytersta punkten)
 
double t2 = (atan(y/(d-x)) + acos((pow(l,2) + pow(e,2) - pow(l,2))/(2*l*e))); // genom trigonometri så räknar jag ut ett värde på vinkel mellan 0 och 180

 int pos2 = t2  * (180/3.1415); // tar t2 och omvandlar det till ett användbar vinkel i int format så att servon kan läsa det
Serial.println(pos2);
return pos2;
}

int raklinje(double xstar, double ystar, double xslut, double yslut){
double k = (xstar-xslut)/(ystar-yslut); // lutnignen på sträkan som vill ritas
Serial.println(k);
if (xstar < xslut){ // vertionen av funtionen som funkar när x och y är mindre i början gemfört med slutet
if (ystar < yslut){
for (double i = 0;  (xstar + i) <= xslut; i +=k){
  Serial.println(i);
 Serial.println("moved");
myservo1.write(poscalcx((xstar + i),(ystar + i/k))+3);
myservo2.write(180-poscalcy((xstar + i),(ystar + i/k))-5);
delay(500);
}
} else { // vertionen av funtionen som funkar när x är mindre i början gemfört med slutet medan y var störe innan
for (double i = 0;  (xstar - i) <= xslut; i +=k){
  Serial.println(i);
 Serial.println("moved");
myservo1.write(poscalcx((xstar - i),(ystar - i/k))+3);
myservo2.write(180-poscalcy((xstar - i),(ystar - i/k))-5);
delay(500);
}
}
}
if (xstar > xslut){ // vertionen av funtionen som funkar när x är störe i början gemfört med slutet medan y var mindre
if (ystar < yslut){
for (double i = 0;  (xstar + i) >= xslut; i +=k){
  Serial.println(i);
 Serial.println("moved");
myservo1.write(poscalcx((xstar + i),(ystar + i/k))+3);
myservo2.write(180-poscalcy((xstar + i),(ystar + i/k))-5);
delay(500);
}
} 
else {  // vertionen av funtionen som funkar när x och y är störe i början gemfört med slutet
for (double i = 0;  (xstar - i) >= xslut; i +=k){
  Serial.println(i);
 Serial.println("moved");
myservo1.write(poscalcx((xstar - i),(ystar - i/k))+3);
myservo2.write(180-poscalcy((xstar - i),(ystar - i/k))-5);
delay(500);
}
}
}
}
