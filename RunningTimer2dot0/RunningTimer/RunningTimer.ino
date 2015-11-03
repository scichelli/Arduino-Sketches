#define motor 10
#define walk 7
#define run 8
#define button 2
int buttonState = 0;

void setup()
{
  pinMode(motor, OUTPUT);
  pinMode(walk, OUTPUT);
  pinMode(run, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(walk, HIGH);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(button);
  if (buttonState)
  {
    digitalWrite(walk, HIGH);
    digitalWrite(run, LOW);
    analogWrite(motor, 0);
  }
  else
  {
    digitalWrite(walk, LOW);
    digitalWrite(run, HIGH);
    analogWrite(motor, 710);
  }
  Serial.println("Start");
  float* runProgram = getProgram(1, 1);
  Serial.println(runProgram[0]);
  for (int i = 1; i < runProgram[0]; i++)
  {
    Serial.println(runProgram[i]);
  }
}

float* getProgramDoesNotWork(int week, int day, int* out_arraySize)
{
  float week1[] = {1, 2, 3, 4};
  float week2[] = {1, 2, 3, 4, 5, 6};
  switch(week)
  {
    case 1:
      *out_arraySize = 4;
      return &(week1[0]);
    case 2:
      *out_arraySize = 6;
      return &(week2[0]);
  }
}

float* getProgram(int week, int day)
{ 
//  float runProgram[10];
//  if (week == 1) 
//  {
//      runProgram[0] = 5; runProgram[1] = 1; runProgram[2] = 2; runProgram[3] = 3; runProgram[4] = 4; 
//  }
//  else
//  {
//      runProgram[0] = 7; runProgram[1] = 1; runProgram[2] = 2; runProgram[3] = 3; runProgram[4] = 4; runProgram[5] = 5; runProgram[6] = 6; 
//  }    
  float runProgram[10];
  switch(week)
  {
    case 1:
      runProgram[0] = 5; runProgram[1] = 1; runProgram[2] = 2; runProgram[3] = 3; runProgram[4] = 4; 
      return &(runProgram[0]);
//      break;
    case 2:
      runProgram[0] = 7; runProgram[1] = 1; runProgram[2] = 2; runProgram[3] = 3; runProgram[4] = 4; runProgram[5] = 5; runProgram[6] = 6; 
      return &(runProgram[0]);
//      break;
//    default:
//      runProgram[0] = 7; runProgram[1] = 1; runProgram[2] = 2; runProgram[3] = 3; runProgram[4] = 4; runProgram[5] = 5; runProgram[6] = 6; 
//      break;
  }
//  return &(runProgram[0]);
}
