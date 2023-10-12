#include <Servo.h>

//Declaración de pins a utilizar
//Sensores infrarrojos
int ir1 = 34;
int ir2 =35;
int ir3 = 47;

//Dual motor
int e1 = 2;
int m1 = 50;
int e2 = 3;
int m2 = 52;

//Ultrasonido
int trig = 28;
int echo = 29;

//Servo motor
Servo myServo;

//LED
int green = 41;
int red = 40;
int r= 6;
int b = 4;
int g = 5;

void adelante(){ //Función que hará que el robot avance hacia adelante
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  analogWrite(e1, 210);
  analogWrite(e2, 210);

  analogWrite(r, 255);
  analogWrite(g, 255);
  analogWrite(b, 0);
}
void derecha(){ //Función que hará que el robot gire a la izquierda
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  analogWrite(e1, 150);
  analogWrite(e2, LOW);

  analogWrite(r, 254);
  analogWrite(g, 52);
  analogWrite(b, 126);
}
void izquierda(){ //Función que hará que el robot gire hacia la derecha
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  analogWrite(e1, LOW);
  analogWrite(e2, 150);

  analogWrite(r, 0);
  analogWrite(g, 0);
  analogWrite(b, 255);
  
}
void detener(){ //Función que hará que el robot gire hacia la derecha
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  analogWrite(e1, LOW);
  analogWrite(e2, LOW);
  
}

void setup() {
  // Configuración de parámetros iniciales del robot
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  myServo.attach(24);
  myServo.write(0);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  //Acciones a ejecutar por el robot
  int left = digitalRead(ir1); //Estado del sensor infrarrojo izquierdo
  int right = digitalRead(ir2); //Estado del sensor infrarrojo derecho
  int center = digitalRead(ir3); //Estado del sensor infrarrojo del centro
  digitalWrite(trig, LOW);
  delayMicroseconds(3);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  

  float tiempo = pulseIn(echo, HIGH);
  tiempo= tiempo/2;
  float distancia = tiempo/29.2; //Cálculo de la distancia detectada por el ultrasonido
  Serial.println(distancia);
  if(left==1 && center==1){ //Detección de si el robot se encuentra en la línea
    if(distancia < 10 && distancia >9.5){ //Detección de si hay un objeto frente al robot
      detener();
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      int i;

      analogWrite(r, 255);
      analogWrite(g, 255);
      analogWrite(b, 255);
      for(i=5; i<=180; i+=60){
        myServo.write(i);
        delay(200);
      }

      for(i=180; i>=0; i-=60){
        myServo.write(i);
        delay(200);
      }
    }else{
      Serial.println("adelante");
      adelante();
      
    }

  }else if(right ==1){
    derecha();
    delay(500);

  }
  
  else if(left ==0 && center==1){ //Detección de si el robot se encuentra a la derecha de la línea
    Serial.println("derecha");
    derecha();
    delay(100);
  }else if(left == 1 && center==0){ //Detección de si el robot se encuentra a la izquierda de la línea
    Serial.println("izquierda");
    izquierda();
    delay(100);
  }


}