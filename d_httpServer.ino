const char* pageIndex = "<!DOCTYPE html><html><head> <meta charset='utf-8'><title>ESP32 Painel</title><meta name='viewport' content='initial-scale=1, maximum-scale=1'> <style>body{font-family: arial; margin: 0; padding: 0; background: rgb(2,0,36); background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(9,9,121,1) 50%, rgba(34,0,131,1) 100%);}.container{display: flex; justify-content: center; align-items: center; height: 100vh;}.form{width: 300px; background: #fff; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.2); padding: 10px; display: flex; flex-direction: column; justify-content: center;}form{display: flex; flex-direction: column; justify-content: center;}p{font-size: large;}</style></head><body> <div class='container'> <div class='form'> <p>ESP32 Painel</p><div> <h6>SSID: %SSID%</h6> <h6>PASSWORD: %PASSWORD%</h6> <h6>APIURL: %APIURL%</h6> </div><form action='/' method='post'> <textarea placeholder='Informações a serem enviadas para a API' style='height: 100px' type='text' name='content' required ></textarea> <button type='submit' > Enviar dados </button> </form> <a style='margin-top: 16px' href='/down'>Desconectar ESP32 da rede</a> </div></div></body></html>";
const char* pageConectar = "<!DOCTYPE html><html><head> <meta charset='utf-8'><title>ESP32 Configuração</title><meta name='viewport' content='initial-scale=1, maximum-scale=1'> <style>body{font-family: arial; margin: 0; padding: 0; background: rgb(2,0,36); background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(9,9,121,1) 50%, rgba(34,0,131,1) 100%);}.container{display: flex; justify-content: center; align-items: center; height: 100vh;}.form{width: 300px; background: #fff; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.2); padding: 10px; display: flex; flex-direction: column;}form{display: flex; align-items: center; flex-direction: column;}input{width: 100%; height: 40px; border: 1px solid #ccc; border-radius: 5px; padding: 0 10px; margin-bottom: 10px; margin: 5px;}label{display: flex; align-items: center; flex-direction: column;}p{font-size: large;}</style></head><body> <div class='container'> <div class='form'> <p>Rede Wi-Fi ESP32</p><form action='conectar' method='post'> <label> <input placeholder='SSID' type='text' name='ssid' required> <input placeholder='SENHA' type='password' name='password' required> </label> <button type='submit'>Conectar</button> </form> </div></div></body></html>";
const char* pageConectarDone = "<!DOCTYPE html><html><head> <meta charset='utf-8'><title>ESP32 Configuração</title><meta name='viewport' content='initial-scale=1, maximum-scale=1'> <style>body{font-family: arial; margin: 0; padding: 0; background: rgb(2,0,36); background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(9,9,121,1) 50%, rgba(34,0,131,1) 100%);}.container{display: flex; justify-content: center; align-items: center; height: 100vh;}.form{width: 500px; background: #fff; border-radius: 10px; padding: 10px; display: flex; flex-direction: column;}p{font-size: large;}</style></head><body> <div class='container'> <div class='form'> <p>Recebemos suas informações e estamos tentando conectar...</p><p>Caso não seja possível conectar o ESP32, será ativado o modo AP novamente.</p><p>Caso a conexão for bem sucedida, você deve ver o ESP32 conectado a sua rede Wi-Fi.</p></div></div></body></html>";

void startHttpServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/ as GET");
    if (wifiMode == "station") {
      request->send_P(200, "text/html", pageIndex);
    } else {
      request->send_P(200, "text/html", pageConectar);
    }
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("/ as POST");

    if (wifiMode == "station") {
      int params = request->params();

      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("index - POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

        if (p->name() == "content") sendHttpRequest((char*) p->value().c_str());
      }

      request->send_P(200, "text/html", pageIndex);
    }
  });

  server.on("/conectar", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("/conectar as POST");
    if (wifiMode == "ap") {
      int params = request->params();

      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("conectar - POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

        if (p->name() == "ssid") ssid = (char*) p->value().c_str();
        if (p->name() == "password") password = (char*) p->value().c_str();
      }

      request->send_P(200, "text/html", pageConectarDone);

      setWifiStation();
    }
  });

  server.on("/down", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/down as GET");

    if (wifiMode == "station") setWifiAp();
  });

  server.begin();
}
