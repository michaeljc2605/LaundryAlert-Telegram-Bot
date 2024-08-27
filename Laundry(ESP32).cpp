//Basic codes
//Import Library for Wifi,client and Telegram functions
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials , SSID = Network Name, Password is Password
#define WIFI_SSID "ARIFFIN0000"
#define WIFI_PASSWORD "6566W96k"

//Retrieve info about the bot itself
#define BOT_TOKEN "6735878499:AAGtpp6ImleEE3WuTtVyVEsbxwcwPAZC_xw"

//Setup bot
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

//Pins for Rx = retrieve, Tx= transmit 
#define RXp2 16
#define TXp2 17

//Code for sound sensor 
const int sPin = 35;
int sValue =0;
int Smode =0;
int Stored = 0;

// mean time between scan messages
const unsigned long BOT_MTBS = 1000; 

void handleNewMessages(int numNewMessages)
{
  Serial.print("HandleNewMessages");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";
    
    if(text == "/start") //Start of the Laundry machine tab 
    {
      Smode=0;
      String menu = "@Laundry Bot has started\n" + from_name + ".\n";
      menu += "Choose from the following options\n\n";
      menu += "/Lstatus: to check the availability of the laundry machine\n";
      menu += "/LstatusOFF: to check the availability of the laundry machine\n";
      bot.sendMessage(chat_id, menu, "Markdown");
    }

    if(text == "/Lstatus")
    {
      String msg = "Check ON: Laundry Machine Status";
      bot.sendMessage(chat_id,msg,"Markdown"); 
      Smode = 1;
    }

    if(text == "/LstatusOFF")
    {
      String msg = "Check OFF: Laundry Machine Status";
      bot.sendMessage(chat_id,msg,"Markdown"); 
      Smode = 0;
    }
  }
}

void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

    //attempt to connect to Wifi network:
    Serial.print("Connecting to Wifi SSID ");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nWiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
}
void loop() {

    String chat_id = bot.messages[0].chat_id;
    if (millis() - bot_lasttime > BOT_MTBS)
    {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages)
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }

    bot_lasttime = millis();
}

    Serial.println("Waiting for Message...");
    Serial2.readStringUntil('N');
    if(Serial2.readStringUntil('N')!= 0)
    {
    Serial.println("Message Received...");
    Serial.println("ON");
    
    if (Smode ==1)
    {bot.sendMessage(chat_id,"Laundry is running");}

    }
}