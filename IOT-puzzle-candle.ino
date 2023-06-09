#define DEBUG

#define puzzle 8
#define clock_game 9
#define fireplace 10
#define relay 11
#define buttons 12

#define button1 A0
#define button2 A1
#define button3 A2
#define button4 A3
#define button5 A4 
#define button6 A5

bool button1_sit = false;
bool button2_sit = false;
bool button3_sit = false;
bool button4_sit = false;
bool button5_sit = false;
bool button6_sit = false; 

#define light1 2
#define light2 3
#define light3 4
#define light4 5
#define light5 6
#define light6 7



// 
bool game_started = false;

int button1_voltage = 0;
int button2_voltage = 0;
int button3_voltage = 0;
int button4_voltage = 0;
int button5_voltage = 0;
int button6_voltage = 0;

bool light1_state = true;
bool light2_state = true;
bool light3_state = true;
bool light4_state = true;
bool light5_state = true;
bool light6_state = true;

#define button1_value 1
#define button2_value 2
#define button3_value 3
#define button4_value 4
#define button5_value 5
#define button6_value 6


int order[6] = {};
int correctOrder[6] = {3, 1, 4, 6, 2, 5};


void setup() {
  Serial.begin(9600);
  for(int i = 2; i <= 7; i++){
    pinMode(i,OUTPUT);
    }
  pinMode(puzzle,INPUT);
  pinMode(clock_game,OUTPUT);
  pinMode(fireplace,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(buttons,OUTPUT);
  digitalWrite(fireplace,HIGH);
}

void loop() {
    int puzzle_game = digitalRead(puzzle);
    Serial.println("Puzzle game "+ String(puzzle_game));
    if (puzzle_game == 0) {
      deactive_game();
      return;
      }
 
      #ifdef DEBUG
      Serial.println("Puzzle Complated");
      #endif

        if (!game_started)
        {
            light_sit();
            game_started = true;
            digitalWrite(relay,HIGH);
            digitalWrite(fireplace, LOW);
            delay(200);
            digitalWrite(relay,LOW);
            
        }

        read_buttons();
        write_buttons_to_serial();

        if (button1_voltage > 1000 && light1_state )
        {
            digitalWrite(light1, LOW);
            addValue(button1_value);
            light1_state = false;
        }
        if (button2_voltage > 1000 && light2_state)
        {
            digitalWrite(light2, LOW);
            addValue(button2_value);
            light2_state = false;
        }
        if (button3_voltage > 1000 && light3_state)
        {
            digitalWrite(light3, LOW);
            addValue(button3_value);
            light3_state = false;
        }
        if (button4_voltage > 1000 && light4_state)
        {
            digitalWrite(light4, LOW);
            addValue(button4_value);
            light4_state = false;
        }
        if (button5_voltage > 1000 && light5_state)
        {
            digitalWrite(light5, LOW);
            addValue(button5_value);
            light5_state = false;
        }
        if (button6_voltage > 900 && light6_state)
        {
            digitalWrite(light6, LOW);
            addValue(button6_value);
            light6_state = false;
        }

        
        if (light1_state == false && light2_state == false && light3_state == false && light4_state == false && light5_state == false && light6_state == false)
        {
            
            if (checkOrder())
                {
                    // roleleri tetikliyoruz
                    digitalWrite(clock_game, HIGH);
                    delay(3000);
                    digitalWrite(fireplace,HIGH);
                    digitalWrite(clock_game, LOW);

                    
                    
                    while (digitalRead(puzzle))
                    {   
                        int deger = digitalRead(puzzle);
                        Serial.println("oyunun bitmesi bekleniyor "+ String(deger));
                        digitalWrite(buttons,HIGH);
                    }
                    game_started = false;
                    digitalWrite(buttons,LOW);
                    reset_game();
                    Serial.println("Game_started false ");
                }
                // 
                 else {
                    reset_game();
                }
        }

        


   
    
   
  } 

// 

// oyunun reseti demek, tüm ışıkların yanık olması demek.
void reset_game() {
    for(int i = 2; i <= 7; i++){
      delay(400);
      digitalWrite(i,HIGH);
      button1_voltage = 0;
        button2_voltage = 0;
        button3_voltage = 0;
        button4_voltage = 0;
        button5_voltage = 0;
        button6_voltage = 0;

        light1_state = true;
        light2_state = true;
        light3_state = true;
        light4_state = true;
        light5_state = true;
        light6_state = true;
  }
}

// oyunun deaktif olması demek, tüm ışıkların kapanması demek.
void deactive_game() {
      for(int i = 2; i <= 7; i++){
      digitalWrite(i,LOW);
      button1_voltage = 0;
        button2_voltage = 0;
        button3_voltage = 0;
        button4_voltage = 0;
        button5_voltage = 0;
        button6_voltage = 0;

        light1_state = false;
        light2_state = false;
        light3_state = false;
        light4_state = false;
        light5_state = false;
        light6_state = false;
  }
}

void light_sit(){
 for(int i = 2; i <= 7; i++){
 digitalWrite(i,HIGH);
 light1_state = true;
 light2_state= true;
 light3_state= true;
 light4_state= true;
 light5_state= true;
 light6_state= true;
 delay(400); 
 } 
}

void read_buttons() {
    button1_voltage = analogRead(button1);
    button2_voltage = analogRead(button2);
    button3_voltage = analogRead(button3);
    button4_voltage = analogRead(button4);
    button5_voltage = analogRead(button5);
    button6_voltage = analogRead(button6);
}

void write_buttons_to_serial(){
    Serial.println("Button1 " + String(button1_voltage) + " Button2 " + String(button2_voltage)+ " Button3 " + String(button3_voltage) + " Button4 " + String(button4_voltage)+" Button5 " + String(button5_voltage) + " Button6 " + String(button6_voltage));
}

void addValue(int value) { 
    for (int i = 0; i < 5; i++) {
        order[i] = order[i + 1];
    }
    
    order[5] = value;
}

bool checkOrder () {
    for (int i = 0; i < 6; i++) {
        if (order[i] != correctOrder[i]) {
            return false;
        }
    }
    return true;
}
