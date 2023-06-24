#include <Arduino.h>
#include <Wire.h>
 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
 
char input[12];
int count = 0;
 
int a;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
 
double total = 0;
int count_prod = 0;
 
void setup ()
{
  pinMode(A4, INPUT_PULLUP);
 
  lcd.clear();
  Wire.begin();
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print(" AUTOMATIC BILL");
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print(" SHOPPING CART ");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  delay (2000);
  lcd.setCursor(3, 1);
  lcd.print("SUPER MARKET");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Plz Add iTem");
}
void loop()
{
     count = 0;
  while (Serial.available() && count < 12)
  {
    input[count] = Serial.read();
    count++;
    delay(5);
  }
  int a = digitalRead(A4);
 
  if ((strncmp(input, "4A00A6C3032C", 12) == 0) && (a == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Butter Added       ");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("Price :- 50.00      ");
    p1++;
    delay(2000);
    total = total + 50.00;
    count_prod++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Price :-");
 
    lcd.setCursor(0, 1);
    lcd.print(total);
 
  }
  else if ((strncmp(input, "4A00A6C3032C", 12) == 0) && (a == 0))
  {
    if (p1 > 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Butter Removed!!!        ");
      delay(2000);
      p1--;
      total = total - 50.00;
      count_prod--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price :-");
 
      lcd.setCursor(0, 1);
      lcd.print(total);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");
      delay(2000);
      lcd.clear();
    }
  }
 
 
  if ((strncmp(input, "4A00A6684ACE", 12) == 0) && (a == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Milk Added       ");
    delay(3000);
    lcd.setCursor(0, 1);
    lcd.print("Price :- 20.00      ");
    p2++;
    delay(2000);
    total = total + 20.00;
    count_prod++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Price :-");
 
    lcd.setCursor(0, 1);
    lcd.print(total);
 
  }
 
  else if ((strncmp(input, "4A00A6684ACE", 12) == 0) && (a == 0))
  {
    if (p2 > 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Milk Removed!!!        ");
      delay(2000);
      p2--;
      total = total - 20.00;
      count_prod--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price :-");
      lcd.setCursor(0, 1);
      lcd.print(total);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");
      delay(2000);
      lcd.clear();
    }
  }
 
 
if ((strncmp(input, "4A00A65140FD", 12) == 0) && (a == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tea Added       ");
    delay(3000);
    lcd.setCursor(0, 1);
    lcd.print("Price :- 45.00      ");
    p3++;
    delay(2000);
    total = total + 45.00;
    count_prod++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Price :-");
 
    lcd.setCursor(0, 1);
    lcd.print(total);
 
  }
 
  else if ((strncmp(input, "4A00A65140FD", 12) == 0) && (a == 0))
  {
    if (p3 > 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tea Removed!!! ");
      delay(2000);
      p3--;
      total = total - 45.00;
      count_prod--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price :-");
      lcd.setCursor(0, 1);
      lcd.print(total);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!");
      delay(2000);
      lcd.clear();
    }
  }
if ((strncmp(input, "4A00A665EA63", 12) == 0) && (a == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Perfume Added       ");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("Price :- 300.00      ");
    p4++;
    delay(2000);
    total = total + 300.00;
    count_prod++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Price :-");
 
    lcd.setCursor(0, 1);
    lcd.print(total);
 
  }
  else if ((strncmp(input, "4A00A665EA63", 12) == 0) && (a == 0))
  {
    if (p4 > 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Perfume Removed!!!        ");
      delay(2000);
      p4--;
      total = total - 300.00;
      count_prod--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price :-");
 
      lcd.setCursor(0, 1);
      lcd.print(total);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");
      delay(2000);
      lcd.clear();
    }
  }
if ((strncmp(input, "4A00A6C3AB84", 12) == 0) && (a == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Tshirt Added       ");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("Price :- 500.00      ");
    p5++;
    delay(2000);
    total = total + 500.00;
    count_prod++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Price :-");
 
    lcd.setCursor(0, 1);
    lcd.print(total);
 
  }
  else if ((strncmp(input, "4A00A6C3AB84", 12) == 0) && (a == 0))
  {
    if (p5 > 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tshirt Removed!!!        ");
      delay(2000);
      p5--;
      total = total - 500.00;
      count_prod--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Price :-");
 
      lcd.setCursor(0, 1);
      lcd.print(total);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");
      delay(2000);
      lcd.clear();
    }
  }
}