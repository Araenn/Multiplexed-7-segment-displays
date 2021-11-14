unsigned char table[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char sel[] = {0xF1,0xF2,0xF4,0xF8};
unsigned char numbers[] = {1,2,3,4,5,6,7,8,9};

int i;
int n;
char character;

#define latch 4
#define clk 7
#define data 8 


void setup() {
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  if(Serial.available() > 0){
      n = Serial.available();
      if(n >= 4){
        for(i = 0; i < n; i++){
          character = Serial.read();
          if(character - 0x30 >= 0 && character - 0x39 <= 9){
            numbers[i] = caract - 0x30;
          }
          else{
            Serial.println("ERROR");
          }
        }    
      }
    }
  for(i = 0; i < n; i++){
     show(numbers[i], i);
  }
}
void show(int num, int sh){
  digitalWrite(latch, 0);
  shiftOut(data, clk, MSBFIRST, table[num]);
  shiftOut(data, clk, MSBFIRST, sel[sh]);
  digitalWrite(latch, 1);
  delay(2);
}
