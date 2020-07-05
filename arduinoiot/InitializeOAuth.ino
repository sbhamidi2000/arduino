#include <Bridge.h>
#include <TembooYunShield.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Bridge.begin();
  Console.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Console.println("Running InitializeOAuth - Run #" + String(calls++));
    
    TembooYunShieldChoreo InitializeOAuthChoreo;

    // Invoke the Temboo client
    InitializeOAuthChoreo.begin();

    // Set Temboo account credentials
    InitializeOAuthChoreo.setAccountName(TEMBOO_ACCOUNT);
    InitializeOAuthChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    InitializeOAuthChoreo.setAppKey(TEMBOO_APP_KEY);
    InitializeOAuthChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
    
    // Set Choreo inputs
    InitializeOAuthChoreo.addInput("Scope", "yourValueHere");
    InitializeOAuthChoreo.addInput("ClientID", "yourValueHere");
    
    // Identify the Choreo to run
    InitializeOAuthChoreo.setChoreo("/Library/Google/OAuth/InitializeOAuth");
    
    // Run the Choreo; when results are available, print them to Console
    InitializeOAuthChoreo.run();
    
    while(InitializeOAuthChoreo.available()) {
      char c = InitializeOAuthChoreo.read();
      Console.print(c);
    }
    InitializeOAuthChoreo.close();
  }

  Console.println("Waiting...");
  delay(30000); // wait 30 seconds between InitializeOAuth calls
}