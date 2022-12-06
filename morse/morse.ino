#define KEY_SELECT 4
#define KEY_PLAY 2
#define KEY_DELETE 3
#define LED_RED 5
#define LED_GREEN 6
#define SPEAKER 9

#define _null     120
#define _one      278
#define _timeOut  400
#define _fix      80
#define _herz     1800

#define _NULL 0
#define _ONE 1
#define _TIMEOUT 2
//•−−• •−• •• •−− • −
uint8_t dataBuzzerHello[] = {0, 1, 1, 0, 2, 0, 1, 0, 2, 0, 0, 2, 1, 1, 2, 0, 2, 1};
uint8_t dataSave[128];
short countData;
unsigned long timer;
short timer_result;

boolean _isClick;

void Morse(uint8_t value)
{
  if(value == _NULL)
  {
    tone(SPEAKER, _herz); digitalWrite(LED_RED, HIGH);    delay(_null);
    noTone(SPEAKER);      digitalWrite(LED_RED, LOW);     delay(_fix);
  }
  if(value == _ONE)
  {
    tone(SPEAKER, _herz); digitalWrite(LED_GREEN, HIGH);  delay(_one);
    noTone(SPEAKER);      digitalWrite(LED_GREEN, LOW);   delay(_fix);
  }
  if(value == _TIMEOUT)                                   delay(_timeOut);
}

void setup() {
  pinMode(KEY_SELECT, INPUT);
  pinMode(KEY_PLAY, INPUT);
  pinMode(KEY_DELETE, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  for(int i; i < sizeof(dataBuzzerHello); i++) Morse(dataBuzzerHello[i]);
}

void loop() {
  if(digitalRead(KEY_SELECT) == HIGH) _isClick = true;
  else  if(digitalRead(KEY_SELECT) == LOW) _isClick = false;

  if(digitalRead(KEY_PLAY) == HIGH)
  {
    for(int i; i < countData; i++) Morse(dataSave[i]);
  }
  if(digitalRead(KEY_DELETE) == HIGH)
  {
    for(int i; i < countData; i++) dataSave[i] = 0; countData = 0;
  }

  if(_isClick && !timer) 
  {
    tone(SPEAKER, _herz);
    timer = millis();
  }


  if(!_isClick && timer)
  {
    noTone(SPEAKER);
    timer_result = millis() - timer;
    
    if(timer_result <= _null) 
    {
      digitalWrite(LED_RED, HIGH);
      delay(5); 
      digitalWrite(LED_RED, LOW);
      dataSave[countData] = _NULL;
      countData++;        
    }

    if(timer_result >= _null && timer_result < _one)
    {
      digitalWrite(LED_GREEN, HIGH);
      delay(5); 
      digitalWrite(LED_GREEN, LOW); 
      dataSave[countData] = _ONE;
      countData++;
    }

    timer_result = millis();
    timer = 0;
  }
}
