int ir1 = 34;
int ir2 =35;
int e1 = 2;
int m1 = 50;
int e2 = 3;
int m2 = 52;

void adelante(){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  analogWrite(e1, 85);
  analogWrite(e2, 85);
}
void izquierda(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  analogWrite(e1, 110);
  analogWrite(e2, LOW);
}
void derecha(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  analogWrite(e1, LOW);
  analogWrite(e2, 110);
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int left = digitalRead(ir1);
  int right = digitalRead(ir2);
  //Serial.print(left);
  //Serial.print(" ");
  //Serial.println(right);
  if(left==0 && right ==0){
    Serial.println("adelante");
    adelante();

  }else if(left ==1 && right==0){
    Serial.println("izquierda");
    izquierda();
    delay(500);
  }else if(left == 0 && right==1){
    Serial.println("derecha");
    derecha();
    delay(500);
  }





}
