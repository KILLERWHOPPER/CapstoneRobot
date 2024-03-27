/* BASE CODE FROM Prometheus Swan Project */

#include "network.hpp"

// PARAMETERS

char ssid[] = "iPhone Lisa";          // your network SSID (name)
char pass[] = "PourEloi";      // your network password
char server[] = "172.20.10.2";    // IP address of the server you want to connect to
int port = 3000;                    // port number
int robot_id = 0;

// GLOBAL VARIABLES

int status = WL_IDLE_STATUS;       // the WiFi connection status
const int bufferSize = 1024; // Adjust the buffer size based on your message size
char message[bufferSize];
WiFiClient client;

WiFiMulti wifimulti;

bool noObstacle = true;

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
    // int bytesRead = client.readBytes(message, bufferSize);
    // message[bytesRead] = '\0';

    // read the message until a newline character is encountered:
    String message = client.readStringUntil('\n');

    Serial.println("Message received from the server:");
    Serial.println(message);

    // Decode the received message and execute corresponding command
    decodeMessage(message);

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

void registration() {
    // send a message to the server:
    String jsonMessage = "{\"id\":" + String(robot_id) + ",\"command\":\"register\"}";

    client.print(jsonMessage);

    Serial.println("Registration message sent to the server");
}

void decodeMessage(String jsonString) {
  DynamicJsonDocument doc(200);
  
  // Parse the JSON string
  DeserializationError error = deserializeJson(doc, jsonString);
  
  // Check for parsing errors
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Extract values from the JSON document
  String command = doc["command"];
  
  // Extract float data array
  JsonArray floatDataArray = doc["float_data"];
  float floatData = 0.0; // Assuming there's only one element in the array
  if (floatDataArray.size() > 0) {
    floatData = floatDataArray[0]; // Extract the first element
  }
  
  handleCommand(command, floatData);
}

void handleCommand(String command, float data) {
  if (command == "move") {
    Serial.println("Received move command");

    int intervals = 10;
    int totalSegments = static_cast<int>(abs(data) / intervals); // Calculate total number of segments
    float segmentDistance = (data < 0) ? -intervals : intervals; 

    for (int i = 0; i < totalSegments; i++) {
      // Verify that there is no obstacle
      if (data < 0) {
        can_move_backward();
      } else {
        can_move_forward();
      }
      
      if (noObstacle) {
        // Process move command for the segment distance
        move_distance(segmentDistance);
      } else {
        // Stop moving if obstacle detected
        break;
      }
    }
  } else if (command == "turn") {
    // Process turn command
    Serial.println("Received turn command");
    turn_angle(data);
  }
}