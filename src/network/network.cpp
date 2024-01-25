/* CODE FROM Prometheus Swan Project */

#include <wifiMulti.h>

// PARAMETERS

char ssid[] = "Galaxy";          // your network SSID (name)
char pass[] = "1029946339";      // your network password
char server[] = "192.168.190.56";    // IP address of the server you want to connect to
int port = 3000;                    // port number
int robot_id = 0;

// GLOBAL VARIABLES

int status = WL_IDLE_STATUS;       // the WiFi connection status
const int bufferSize = 1024; // Adjust the buffer size based on your message size
char message[bufferSize];
WiFiClient client;

WiFiMulti wifimulti;



void registration() {
    // send a message to the server:
    String jsonMessage = "{\"id\":" + String(robot_id) + ",\"command\":\"register\"}";

    client.print(jsonMessage);

    Serial.println("Registration message sent to the server");
}

void setup_network() {
  // initialize serial communication:
  Serial.begin(9600);

  wifimulti.addAP(ssid, pass);
  // attempt to connect to WiFi network:
  while (wifimulti.run() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WiFi: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    //status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(500);
  }
  Serial.println("Connected to WiFi");

  // print your Nano 33 IoT's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // establish a TCP connection to the server:
  Serial.println("Connecting to server...");
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
    registration();
  } else {
    // if the connection failed, print an error message:
    Serial.println("Connection to server failed");
  }
}

void loop_network() {
  // if there are incoming bytes available from the server:
  if (client.available()) {
    // read the bytes and print them to the serial monitor:
    int bytesRead = client.readBytes(message, bufferSize);
    message[bytesRead] = '\0';

    Serial.println("Message received from the server:");
    Serial.println(message);

    Serial.println("Sending message back...");
    String jsonMessage = "{\"id\":" + String(robot_id) + ",\"text\":\"ack\"}";
    // Send the JSON message to the server
    client.print(jsonMessage);
  }

  // if the server closed the connection:
  if (!client.connected()) {
    Serial.println();
    Serial.println("Server disconnected");
    // stop the client:
    client.stop();
    // attempt to reconnect to the server:
    Serial.println("Attempting to reconnect to server...");
    if (client.connect(server, port)) {
      Serial.println("Reconnected to server");
      registration();
    } else {
      Serial.println("Reconnection to server failed");
    }
  }
}
