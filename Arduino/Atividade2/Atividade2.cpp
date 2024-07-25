/*Arduino 1*/
#define but1 2
#define but2 4
#define led1 3
#define led2 5


//int led = 2;

int leituraBut1 = 0;
int leituraBut2 = 0;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);

}

void loop()
{
  leituraBut1 = digitalRead(but1);
  leituraBut2 = digitalRead(but2);
  
  digitalWrite(led1, leituraBut1);
  digitalWrite(led2, leituraBut2);
}



//Semaforo setup
//pinMode(ledVerm1, OUTPUT);
 // pinMode(ledAmar1, OUTPUT);
  //pinMode(ledVerd1, OUTPUT);
  //pinMode(ledVerd2, OUTPUT);
  //pinMode(ledAmar2, OUTPUT);
  //pinMode(ledVerm2, OUTPUT);

//Semaforo loop
//digitalWrite(ledVerd1, HIGH);
  //digitalWrite(ledVerm1, LOW);

  //digitalWrite(ledVerm2, HIGH);
  //digitalWrite(ledAmar2, LOW);
//  delay(3000);
  
 // digitalWrite(ledVerd1, LOW);
  //digitalWrite(ledAmar1, HIGH);
  //delay(2000);
  
 // digitalWrite(ledAmar1, LOW);
 // digitalWrite(ledVerm1, HIGH);
  
  //digitalWrite(ledVerm2, LOW);
  //digitalWrite(ledVerd2, HIGH);
  //delay(4000);
  
  //digitalWrite(ledAmar2, HIGH);
  //digitalWrite(ledVerd2, LOW);
  //delay(3000);
  
  //digitalWrite(ledAmar2, LOW);

/*Arduino 2*/
#define ledVerm1 2
#define ledAmar1 3
#define ledVerd1 4
#define ledVerd2 5
#define ledAmar2 6
#define ledVerm2 7
//int led = 2;

void setup()
{
  pinMode(ledVerm1, OUTPUT);
  pinMode(ledAmar1, OUTPUT);
  pinMode(ledVerd1, OUTPUT);
  pinMode(ledVerd2, OUTPUT);
  pinMode(ledAmar2, OUTPUT);
  pinMode(ledVerm2, OUTPUT);

}

void loop()
{
  
  digitalWrite(ledVerd1, HIGH);
  digitalWrite(ledVerm1, LOW);

  digitalWrite(ledVerm2, HIGH);
  digitalWrite(ledAmar2, LOW);
  delay(3000);
  
  digitalWrite(ledVerd1, LOW);
  digitalWrite(ledAmar1, HIGH);
  delay(2000);
  
  digitalWrite(ledAmar1, LOW);
  digitalWrite(ledVerm1, HIGH);
  
  digitalWrite(ledVerm2, LOW);
  digitalWrite(ledVerd2, HIGH);
  delay(4000);
  
  digitalWrite(ledAmar2, HIGH);
  digitalWrite(ledVerd2, LOW);
  delay(3000);
  
  digitalWrite(ledAmar2, LOW);


  
  


}

/*Arduino 3*/
#define but1 2
#define but2 4
#define but3 7
#define led1 3
#define led2 5


int leituraBut1 = 0;
int leituraBut2 = 0;
int leituraBut3 = 0;
int modo = 0;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);

}

void loop()
{
  leituraBut1 = digitalRead(but1);
  leituraBut2 = digitalRead(but2);
  leituraBut3 = digitalRead(but3);
  
  if(leituraBut1 == HIGH)
  {
    modo = 1;
  }
  
  else if(leituraBut2 == HIGH)
  {
    modo = 2;
  }
  else if(leituraBut3 == HIGH)
  {
  	modo = 3;
  }
  
  if(modo == 0)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  else if(modo == 1)
  {
    int count = 0;
    do{
	digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(200);
	digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
     delay(200);
    count++;
    }while(count < 3);
    modo = 2;
  }
  
  else if (modo == 2)
  {
    int count = 0;
   	do
    {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(1000);      
        
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(1000);
    count++;
    }
    while(count < 4);    
    modo = 3;    
  }
  else if(modo == 3)
  {
    int count = 0;
    do{
    digitalWrite(led1, HIGH);
    delay(1000);
    
    digitalWrite(led2, HIGH);
    delay(1000);
      
    digitalWrite(led2, LOW);
    delay(1000);
      
    digitalWrite(led1, LOW);
    delay(1000);
    count++;
    }while(count < 3);
    
    modo = 1;
    
    
  }
  
  
}




