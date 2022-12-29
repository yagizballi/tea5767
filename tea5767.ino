#include <Wire.h>
#include <LiquidCrystal.h>
#include <TEA5767Radio.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
TEA5767Radio radio = TEA5767Radio();

double frekans = 87.5; //Başlangıç frekansı belirlendi.
double frekans_pt = 87.5; //Potun başlangıç frekansı belirlendi.

void setup()
{
  Serial.begin(9600); //Çıktı alabilmek için seri iletişim başlatıldı.
  Wire.begin(); //LCD için I2C haberleşmesi başlatıldı.
  lcd.begin (16, 2);  //LCD pikselleri belirlendi(16x2).
  lcd.setCursor(0, 0); //Sonraki satırın LCD ekrandaki konumunun pikselleri belirtildi.
  lcd.print("Arduino FM Radyo");  //LCD ekrana "Arduino FM Radyo" yazdırıldı.
  Serial.println("Arduino FM Radyo ");  //Seri iletişim çıktısına Arduino FM Radyo yazdırıldı.
}

void loop()
{

  int pot_deger = analogRead(A0); //pot_deger değişkenine A0 pinine bağlı olan devre elemanının (potansiyometre) çıktısı seçildi.

  frekans = ((double)pot_deger * (108.0 - 87.5)) / 1024.0 + 87.5; //Potansiyometreden alınan değer aralığı frekans değer aralığı ile hizalandı ve double değişkeni olan frekans'a atandı.
  frekans = ((int)(frekans * 10)) / 10.0; //Frekans değeri yuvarlandı.

  if (frekans_pt != frekans)
  {
    lcd.setCursor(6, 1); //Sonraki satırın LCD ekrandaki konumunun pikselleri belirtildi.
    lcd.print(frekans, 1);  //LCD ekrana frekans yazdırıldı.
    Serial.print("Frekans: ");  //Seri iletişime "Frekans: " çıktısı verildi.
    Serial.println(frekans);  //Seri iletişimde satır başına frekans yazdırıldı.
    lcd.print("MHz "); //LCD ekrana "MHZ " yazdırıldı. MHz'den sonra bırakılan boşluk frekans değeri 3 karakterden 2 karaktere düştüğünde oluşan harf tekrarını engellemek için yapılmıştır.
    lcd.setCursor(6, 1);  //Sonraki satırın LCD Ekrandaki konumunun pikselleri belirtildi.
    radio.setFrequency(frekans);  //TEA5767 modülünde frekans, "frekans" değeri olarak seçildi.
    frekans_pt = frekans; //Pot değeri frekans'a eşitlendi.
  }
}