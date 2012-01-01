int playersCounted = false;
const int buttonPin = 12;
const int countFinishedPin = 2;
int playerPins[] = { 3, 5, 6, 9, 10, 11};
const int maxNumPlayers = 6;
int playerCount = 1;
int currentPlayer = 0;
int i;

long lastButtonChange = 0;
long debounceDelay = 500;

long lastFlashChange = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(countFinishedPin, INPUT);
  for (i = 0; i < playerCount; i++)
  {
    pinMode(playerPins[i], OUTPUT);
  }
}

void loop()
{
  if (millis() - lastButtonChange > debounceDelay)
  {
    if (playersCounted)
    {
      showWhoseTurn();
    }
    else
    {
      countPlayers();
    }
  }
}

void showWhoseTurn()
{
  if (digitalRead(buttonPin))
  {
    lastButtonChange = millis();
    advancePlayer();
  }
}

void countPlayers()
{
  if (digitalRead(countFinishedPin) || playerCount == maxNumPlayers)
  {
    lastButtonChange = millis();
    playersCounted = true;
    for (i = 1; i < maxNumPlayers; i++)
    {
      digitalWrite(playerPins[i], LOW);
    }
  }
  else
  {
    flashWaitingLights();
    if (digitalRead(buttonPin))
    {
      lastButtonChange = millis();
      playerCount++;
    }
  }
}

void advancePlayer()
{
  int nextPlayer = currentPlayer + 1;
  if (nextPlayer == playerCount)
  {
    nextPlayer = 0;
  }
  switchLights(currentPlayer, nextPlayer);
  currentPlayer = nextPlayer;
}

void switchLights(int currentPlayer, int nextPlayer)
{
  const int increment = 10;
  int j = 255;
  for (i = 0; i < 256; i += increment)
  {
    analogWrite(playerPins[nextPlayer], i);
    analogWrite(playerPins[currentPlayer], j);
    delay(10);
    j -= increment;
  }
  digitalWrite(playerPins[nextPlayer], HIGH);
  digitalWrite(playerPins[currentPlayer], LOW);
}

void flashWaitingLights()
{
  static int pinState = 0;
  for (i = 0; i < playerCount; i++)
  {
    digitalWrite(playerPins[i], HIGH);
  }
  if (millis() - lastFlashChange > 500)
  {
    for (i = playerCount; i < maxNumPlayers; i++)
    {
      digitalWrite(playerPins[i], pinState);
    }
    pinState = 1 - pinState;
    lastFlashChange = millis();
  }
}
