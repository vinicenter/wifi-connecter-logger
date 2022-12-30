void sendHttpRequest(char* content) {
    HTTPClient http;

    http.begin(apiurl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(content);

    Serial.println("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
}
