
#define V1 7
#define F1 6
#define B1 5
#define Defo1 67
#define Defo2 90
#define slow 5
#define V2 4
#define F2 2
#define B2 3
#define Curve1 50
#define Curve2 66
#define Under1 10
#define Under2 10
#define T 10
int v1 = 0;//左の速さ
int v2 = 0;//右の速さ
int pinSensorR = 1;
int pinSensorL = 2;
int pinSensorC = 3;
int pinSensorRR = 4;
int lineCount = 0;
void setup()
{
  pinMode(pinSensorR, INPUT);
  pinMode(pinSensorL, INPUT);
  pinMode(pinSensorC, INPUT);
  pinMode(V1, OUTPUT);
  pinMode(F1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(V2, OUTPUT);
  pinMode(F2, OUTPUT);
  pinMode(B2, OUTPUT);
  digitalWrite(F1, LOW);
  digitalWrite(F2, LOW);
  Serial.begin(9600);
  v1 = Defo1;
  v2 = Defo2;
  //GitHubの使い方わからん！！！！！！！！！！！！
  //margeって何？？？
}

void loop() 
{
  unsigned long now = millis();

  int valSensorR = analogRead(pinSensorR);/*220オームの抵抗で300以上で黒線*/
  int valSensorL = analogRead(pinSensorL);
  int valSensorC = analogRead(pinSensorC);
  int valSensorRR = analogRead(pinSensorRR);
  delay(100);
  if (valSensorC > 300)
  {
    v1 = Defo1;
    v2 = Defo2;
    Serial.print("default Speed1\n");
    digitalWrite(F1, HIGH);
    digitalWrite(B1, LOW);
    analogWrite(V1, v1);
    //-----------------------------------
    Serial.print("v1、v2 = ");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print("\n");
    //--------------------------------------
    //Serial.print("front\n");             //前に進む（左車輪）

    digitalWrite(F2, HIGH);
    digitalWrite(B2, LOW);
    analogWrite(V2, v2);                                      //前に進む（右車輪）
    // Serial.print("front\n" v2);　
    if(valSensorRR > 300 && lineCount >= 2)                    //右に直角に曲がる
  { 
 Serial.print("直角に曲がる\n");
 //v1 = v1 - slow;
  if (v2 < Under2 + 1)
 {
 v2 = Under2 + 1;
 }
 v2 = 0;
 if (v2 < 6)
 {
  v2 = 6;
  Serial.print("Max turn right\n");
  }
 analogWrite(V2, v2);//右に曲がる
  //-----------------------------------
  Serial.print("v1、v2 = ");
          Serial.print(v1);
          Serial.print(",");
          Serial.print(v2);
          Serial.print("\n");
            //----------------------------------- 
      delay(1700);//曲がる時間
      }
    if(valSensorR > 300 && valSensorL > 300 )                                                          //全て黒
    {
      ++lineCount;
      if(lineCount % 2 == 0)
   {
    Serial.print("直角に曲がる\n");
      //v1 = v1 - slow;
 if (v1 < Under1 + 1)
 {
 v1 = Under1 + 1;
 }
 v1 = 0;
  
  Serial.print("Max turn left\n");
          analogWrite(V1, v1);//左に曲がる
             //-----------------------------------
          Serial.print("v1、v2 = ");
          Serial.print(v1);
          Serial.print(",");
          Serial.print(v2);
          Serial.print("\n");
              //----------------------------------- 
      delay(1500);//曲がる時間
    }
     delay(200);   //カウント増加の防止
  }
    else if (valSensorR > 300 && valSensorL < 300 && v2 > Under2)                     //中央、右が黒
    {
    //v2 = v2 - slow;
      if (v2 < Under2 + 1)
      {
        v2 = Under2 + 1;
      }
      v2 = Curve2 + T; 
      if (v2 < 6)
      {
        v2 = 6;
        Serial.print("Max turn right\n");
      }
      analogWrite(V2, v2);      
                             //右に曲がる
      //-----------------------------------
      Serial.print("v1、v2 = ");
      Serial.print(v1);
      Serial.print(",");
      Serial.print(v2);
      Serial.print("\n");
      //-----------------------------------
    }
    else if (valSensorR < 300 && valSensorL > 300 && v1 > Under1)                  //中央、左が黒
    {

      //v1 = v1 - slow;
      if (v1 < Under1 + 1)
      {
        v1 = Under1 + 1;
      }
      v1 = Curve1 + T;
      if (v1 < 6)
      {
        v1 = 6;
        Serial.print("Max turn left\n");
      }
      analogWrite(V1, v1);//左に曲がる
      //-----------------------------------
      Serial.print("v1、v2 = ");
      Serial.print(v1);
      Serial.print(",");
      Serial.print(v2);
      Serial.print("\n");
      //-----------------------------------
    }
    else                                                                          //真ん中だけが黒判定
      {
        v1 = Defo1;
        v2 = Defo2;//元のスピードに
        Serial.print("真ん中だけが黒\n");
        analogWrite(V2, v2);//わからん
        analogWrite(V1, v1);
        //-----------------------------------
        Serial.print("v1、v2 = ");
        Serial.print(v1);
        Serial.print(",");
        Serial.print(v2);
        Serial.print("\n");
        //-----------------------------------
      }
    
    }
  else if (valSensorR > 300 && valSensorL < 300 && v2 > Under2)                   //右だけ黒
  {
    Serial.print("右だけが黒\n");
    //v2 = v2 - slow;
    if (v2 < Under2 + 1)
    {
      v2 = Under2 + 1;
    }
    v2 = Curve2;
    
    if (v2 < 6)
    {
      v2 = 6;
      Serial.print("Max turn right\n");
    }
    analogWrite(V2, v2);//右に曲がる
   
    //-----------------------------------
    Serial.print("v1、v2 = ");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print("\n");
    //-----------------------------------
  }
  else if (valSensorR < 300 && valSensorL > 300 && v1 > Under1)                     //左だけ黒
  {
    Serial.print("左だけが黒\n");
    //v1 = v1 - slow;
    if (v1 < Under1 + 1)
    {
      v1 = Under1 + 1;
    }
    v1 = Curve1;
    if (v1 < 6)
    {
      v1 = 6;
      Serial.print("Max turn left\n");
    }
    analogWrite(V1, v1);//左に曲がる
    //-----------------------------------
    Serial.print("v1、v2 = ");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print("\n");
    //-----------------------------------
  }
  
  else                                                                               //全部白
  {
    v1 = Defo1;
    v2 = Defo2;//元のスピードに
    digitalWrite(F1, LOW);
    digitalWrite(B1, HIGH);
    digitalWrite(F2, LOW);
    digitalWrite(B2, HIGH);

    Serial.print("全部白\n");
    analogWrite(V2, v2);
    analogWrite(V1, v1);
    delay(500);
    digitalWrite(F1, HIGH);
    digitalWrite(B1, LOW);
     digitalWrite(F2, HIGH);
    digitalWrite(B2, LOW);
    //-----------------------------------
    Serial.print("v1、v2 = ");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print("\n");
    Serial.println("");
    //-----------------------------------
  }
  delay(50);
}
