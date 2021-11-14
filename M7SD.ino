//Two 74HC595 shift registers are used to select one of the 4 displays (outputs Qa to Qd of the U2 circuit on logic high level) 
//and to switch on (low level) or off (high level) one of the segments (a to g) or the decimal point (h) (outputs Qa to Qh of the U3 circuit)
//(high level) or the decimal point (h) (outputs Qa to Qh of circuit U3).
//We will create two tables containing the numbers to be sent to U2 and U3, such as ://

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

//The show() subroutine displays the 4 numbers contained in the following array:
//unsigned char digit1[] = 1, 2, 3, 4;. 
//For each digit, we set the latch to 0, we use the shiftOut command for table and salt ://

void show(int num, int sh){
  digitalWrite(latch, 0);
  shiftOut(data, clk, MSBFIRST, table[num]);
  shiftOut(data, clk, MSBFIRST, sel[sh]);
  digitalWrite(latch, 1);
  delay(2);
}
