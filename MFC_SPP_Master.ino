String Text ;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    Text = Serial.readStringUntil('\n');
    Serial1.println(Text);
  }
}
