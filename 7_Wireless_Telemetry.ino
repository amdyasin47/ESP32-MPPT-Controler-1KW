void setupWiFi(){
  if(enableWiFi==1){
    Blynk.begin(auth,ssid,pass);
    WIFI = 1;
  
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset settings - for testing
    //wifiManager.resetSettings();

    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);

    //fetches ssid and pass and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    if(!wifiManager.autoConnect()) {
      Serial.println("failed to connect and hit timeout");
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(1000);
    } 
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED() {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Device Is Online");
  lcd.setCursor(0, 1);
  lcd.print("Device Is Ready");
  digitalWrite(IOT_Not_LED, LOW);
  digitalWrite(IOT_LED, HIGH);
  digitalWrite(WiFi_Not_LED, LOW);
  digitalWrite(WiFi_LED, HIGH);
  delay(1000);
  lcd.clear();
}

// This function is called every time the device is Disconnected from the Blynk.Cloud
BLYNK_DISCONNECTED() {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Device DisConnected");
  lcd.setCursor(0, 1);
  lcd.print("No Internet");
  digitalWrite(IOT_Not_LED, HIGH);
  digitalWrite(IOT_LED, LOW);
  delay(1000);
  lcd.clear();
}


void configModeCallback (WiFiManager *myWiFiManager) {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wellcome To The");
  lcd.setCursor(0, 1);
  lcd.print("MPPT Update Sys");
  delay(2000);
  digitalWrite(4, HIGH);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Smart MPPT");
  WiFi.softAP("Smart MPPT", "");
  lcd.setCursor(3, 1);
  lcd.print(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


void Wireless_Telemetry(){
  
  ////////// WIFI TELEMETRY ////////// 
  if(enableWiFi==1){
    int LED1, LED2, LED3, LED4;                      //Declare LED brightness variable 
    if(buckEnable==1)      {LED1=200;}else{LED1=0;}  //BATTERY CHARGING STATUS
    if(batteryPercent>=99 ){LED2=200;}else{LED2=0;}  //FULL CHARGE STATUS
    if(batteryPercent<=10) {LED3=200;}else{LED3=0;}  //LOW BATTERY STATUS
    if(IUV==0)             {LED4=200;}else{LED4=0;}  //PV INPUT PRESENCE STATUS

    
  if (WiFi.status() != WL_CONNECTED)
  {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" No WiFi");
    digitalWrite(IOT_Not_LED, HIGH);
    digitalWrite(IOT_LED, LOW);
    digitalWrite(WiFi_Not_LED, HIGH);
    digitalWrite(WiFi_LED, LOW);
    Blynk.begin(auth, ssid, pass);
    ESP.restart();
    delay(1000);
  } else {
    digitalWrite(WiFi_Not_LED, LOW);
    digitalWrite(WiFi_LED, HIGH);
    Blynk.run();
  } 
    Blynk.virtualWrite(0,powerInput); 
    Blynk.virtualWrite(1,batteryPercent);
    Blynk.virtualWrite(2,voltageInput);    
    Blynk.virtualWrite(3,currentInput);   
    Blynk.virtualWrite(4,voltageOutput); 
    Blynk.virtualWrite(5,currentOutput); 
    Blynk.virtualWrite(6,temperature); 
    Blynk.virtualWrite(7,Wh/1000); 
    Blynk.virtualWrite(8,energySavings);       
    Blynk.virtualWrite(9,LED1);               //LED - Battery Charging Status
    Blynk.virtualWrite(10,LED2);               //LED - Full Battery Charge Status
    Blynk.virtualWrite(11,LED3);               //LED - Low Battery Charge Status
    Blynk.virtualWrite(12,LED4);               //LED - PV Harvesting
    
    Blynk.virtualWrite(13,voltageBatteryMin);  //Minimum Battery Voltage (Read & Write)
    Blynk.virtualWrite(14,voltageBatteryMax);  //Maximum Battery Voltage (Read & Write)
    Blynk.virtualWrite(15,currentCharging);    //Charging Current  (Read & Write)
    Blynk.virtualWrite(16,electricalPrice);    //Electrical Price  (Write)
  }
  ////////// WIFI TELEMETRY ////////// 
  if(enableBluetooth==1){
    //ADD BLUETOOTH CODE
  }
  
} 
