#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Projeto_5Elemento";
const char* password = "senha_calculadora";

WebServer server(80);

const float PESO_ATUAL = 131.95;
const float TMB_BASE = 2216.0;

String paginaHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Projeto 5 Elemento - Painel Web</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #121212; color: #fff; padding: 20px; text-align: center; }";
  html += ".card { background: #1e1e1e; padding: 20px; border-radius: 10px; max-width: 400px; margin: 0 auto; box-shadow: 0 4px 8px rgba(0,0,0,0.5); }";
  html += "h2 { color: #00e676; }";
  html += "label { display: block; margin: 10px 0 5px; text-align: left; }";
  html += "input, select { width: 100%; padding: 10px; margin-bottom: 15px; border-radius: 5px; border: none; box-sizing: border-box; }";
  html += "button { background: #00e676; color: #000; font-weight: bold; padding: 12px; width: 100%; border: none; border-radius: 5px; cursor: pointer; }";
  html += ".resultado { margin-top: 20px; font-size: 1.2em; font-weight: bold; color: #00e676; }";
  html += "</style></head><body>";
  html += "<div class='card'>";
  html += "<h2>⚡ PROJETO 5º ELEMENTO</h2>";
  html += "<p>Calculadora de Déficit Calórico Embarcada</p><hr>";
  html += "<form action='/calcular' method='POST'>";
  html += "<label>Passos do Dia:</label><input type='number' name='passos' value='0'>";
  html += "<label>Consumo Calórico (kcal):</label><input type='number' name='consumo' value='0'>";
  html += "<label>Atividade MET:</label>";
  html += "<select name='met'>";
  html += "<option value='0.0'>Nenhuma (0.0 MET)</option>";
  html += "<option value='4.0'>Bike Leve (4.0 MET)</option>";
  html += "<option value='6.8'>Bike Moderada (6.8 MET)</option>";
  html += "<option value='3.0'>Caminhada Leve (3.0 MET)</option>";
  html += "<option value='5.0'>Musculação (5.0 MET)</option>";
  html += "<option value='4.5'>Natação Leve (4.5 MET)</option>";
  html += "<option value='8.0'>Crossfit (8.0 MET)</option>";
  html += "<option value='11.5'>Corrida na Areia (11.5 MET)</option>";
  html += "</select>";
  html += "<label>Tempo da Atividade (minutos):</label><input type='number' name='tempo' value='0'>";
  html += "<button type='submit'>Calcular Balanço</button>";
  html += "</form>";
  html += "</div></body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", paginaHTML());
}

void handleCalcular() {
  int passos = server.arg("passos").toInt();
  float consumo = server.arg("consumo").toFloat();
  float met = server.arg("met").toFloat();
  int tempo = server.arg("tempo").toInt();

  float gastoPassos = passos * 0.05;
  float gastoMet = met * PESO_ATUAL * (tempo / 60.0);
  float gastoTotal = TMB_BASE + gastoPassos + gastoMet;
  float balanco = consumo - gastoTotal;

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>body{font-family:Arial;background:#121212;color:#fff;text-align:center;padding:20px;} .card{background:#1e1e1e;padding:20px;border-radius:10px;max-width:400px;margin:0 auto;} a{color:#00e676;}</style></head><body>";
  html += "<div class='card'><h2>📊 Resultado do Dia</h2>";
  html += "<p>Gasto Total: <b>" + String(gastoTotal, 1) + " kcal</b></p>";
  
  if (balanco < 0) {
    html += "<p style='color:#00e676;'>Déficit Calórico: <b>" + String(balanco, 1) + " kcal</b></p>";
  } else {
    html += "<p style='color:#ff5252;'>Superávit Calórico: <b>+" + String(balanco, 1) + " kcal</b></p>";
  }
  
  html += "<br><a href='/'>← Novo Cálculo</a></div></body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  
  Serial.println("Ponto de Acesso Criado!");
  Serial.print("IP do Servidor Web: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/calcular", handleCalcular);
  server.begin();
}

void loop() {
  server.handleClient();
}
