#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

// Hardware - Palmilha (FSR 402 + Actuador Magnético)
const int PIN_FSR = 34;        // ADC para o FSR 402 no calcanhar
const int PIN_MOSFET = 25;     // PWM para o MOSFET / Amortecimento
const int LIMIAR_PASSO = 2000; // Sensibilidade de pressão para contar o passo

// Variáveis de Telemetria
volatile unsigned long totalPassos = 0;
bool passoEmAndamento = false;
int ultimaLeituraFSR = 0;

// Dashboard Cyberpunk Integrado
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Projeto 5º Elemento - Painel Cyberpunk Horizontal</title>
    <style>
        body { 
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
            background-color: #080d1a; 
            color: #e0f7fa; 
            margin: 0;
            padding: 20px; 
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 90vh;
        }
        .card { 
            background: #101b35; 
            padding: 25px 30px; 
            border-radius: 16px; 
            max-width: 900px; 
            width: 100%;
            box-shadow: 0 0 30px rgba(0, 240, 255, 0.25), inset 0 0 15px rgba(0, 240, 255, 0.1); 
            border: 2px solid #00f0ff;
        }
        h2 { 
            text-align: center; 
            color: #00f0ff; 
            margin-top: 0;
            margin-bottom: 2px; 
            font-size: 1.8em;
            text-shadow: 0 0 10px #00f0ff, 0 0 20px #00f0ff;
            letter-spacing: 2px;
        }
        p.sub { 
            text-align: center; 
            font-size: 0.95em; 
            color: #ffd166; 
            margin-top: 0; 
            margin-bottom: 20px;
            font-weight: 600;
            letter-spacing: 1px;
        }
        
        .telemetria-box {
            display: flex;
            justify-content: space-around;
            align-items: center;
            background: #080d1a;
            border: 1px solid #00f0ff;
            border-radius: 8px;
            padding: 10px;
            margin-bottom: 20px;
            box-shadow: 0 0 10px rgba(0, 240, 255, 0.15);
        }
        .telemetria-item { text-align: center; }
        .telemetria-val { font-size: 1.5em; font-weight: bold; color: #00f0ff; }

        .grid-container {
            display: table;
            width: 100%;
            table-layout: fixed;
        }
        .coluna {
            display: table-cell;
            vertical-align: top;
            width: 50%;
        }
        .coluna-esquerda { padding-right: 15px; }
        .coluna-direita { padding-left: 15px; }

        label { 
            display: block; 
            margin-top: 10px; 
            font-weight: bold; 
            color: #00f0ff; 
            font-size: 0.85em;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        input, select { 
            width: 100%; 
            padding: 8px 10px; 
            margin-top: 4px; 
            border-radius: 8px; 
            border: 1px solid #00b4d8; 
            box-sizing: border-box; 
            background-color: #080d1a; 
            color: #ffffff; 
            font-size: 0.9em;
            outline: none;
            transition: 0.3s;
        }
        input:focus, select:focus {
            border-color: #ffd166;
            box-shadow: 0 0 10px #ffd166;
        }

        .alimentos-grid { 
            display: grid; 
            grid-template-columns: 1fr; 
            gap: 5px; 
            max-height: 280px; 
            overflow-y: auto; 
            background: #080d1a; 
            padding: 10px; 
            border-radius: 8px; 
            margin-top: 6px; 
            border: 1px solid #00b4d8; 
        }
        .alimento-item { 
            display: flex; 
            align-items: center; 
            justify-content: space-between; 
            font-size: 0.82em; 
            padding: 4px 6px;
            border-bottom: 1px solid #101b35;
            background: rgba(255,255,255,0.02);
            border-radius: 4px;
        }
        .alimento-item span { color: #e0f7fa; }
        .alimento-item input { width: auto; cursor: pointer; accent-color: #00f0ff; margin: 0; }

        button { 
            width: 100%;
            background: linear-gradient(90deg, #00f0ff, #0077b6); 
            color: #080d1a; 
            font-weight: 800; 
            cursor: pointer; 
            margin-top: 18px; 
            padding: 12px;
            border: none; 
            border-radius: 8px;
            font-size: 1em; 
            text-transform: uppercase;
            letter-spacing: 1.5px;
            box-shadow: 0 0 15px rgba(0, 240, 255, 0.4);
            transition: 0.3s;
        }
        button:hover { 
            background: linear-gradient(90deg, #ffd166, #ffb703);
            box-shadow: 0 0 25px rgba(255, 209, 102, 0.6);
            color: #000;
        }

        .resultado { 
            margin-top: 20px; 
            padding: 15px; 
            border-radius: 10px; 
            display: none; 
            text-align: center; 
            background-color: #080d1a; 
            border: 1.5px solid #00f0ff; 
            box-shadow: 0 0 15px rgba(0,240,255,0.25);
        }
        .resultado h3 { color: #ffd166; margin-top: 0; font-size: 1.1em; text-transform: uppercase; letter-spacing: 1px; }
        .res-linha { display: flex; justify-content: space-around; margin: 8px 0; font-size: 1em; }
    </style>
</head>
<body>

<div class="card">
    <h2>⚡ PROJETO 5º ELEMENTO</h2>
    <p class="sub">PAINEL DE BALANÇO ENERGÉTICO EMBARCADO</p>

    <div class="telemetria-box">
        <div class="telemetria-item">
            <span style="font-size:0.75em; color:#ffd166;">PASSOS CONTADOS (HARDWARE)</span>
            <div id="livePassos" class="telemetria-val">0</div>
        </div>
        <div class="telemetria-item">
            <span style="font-size:0.75em; color:#00f0ff;">PRESSÃO FSR 402 (ADC)</span>
            <div id="liveFsr" class="telemetria-val" style="color:#ffd166;">0</div>
        </div>
    </div>

    <div class="grid-container">
        <div class="coluna coluna-esquerda">
            <label>Selecione os Alimentos do Dia:</label>
            <div class="alimentos-grid">
                <div class="alimento-item"><span>Café c/ Açúcar (60 kcal)</span><input type="checkbox" value="60" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Café c/ Leite (110 kcal)</span><input type="checkbox" value="110" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Achocolatado c/ Leite (180 kcal)</span><input type="checkbox" value="180" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Pão c/ Manteiga (200 kcal)</span><input type="checkbox" value="200" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Pão Presunto e Queijo (310 kcal)</span><input type="checkbox" value="310" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Pão de Alho (2 un - 420 kcal)</span><input type="checkbox" value="420" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Bolo Caseiro (2 fatias - 320 kcal)</span><input type="checkbox" value="320" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Refrigerante Copo (85 kcal)</span><input type="checkbox" value="85" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Cerveja (3 latas - 450 kcal)</span><input type="checkbox" value="450" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Coxinha / Pastel (2 un - 600 kcal)</span><input type="checkbox" value="600" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Cachorro-Quente Completo (400 kcal)</span><input type="checkbox" value="400" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Arroz + Feijão (205 kcal)</span><input type="checkbox" value="205" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Bife Grelhado (200 kcal)</span><input type="checkbox" value="200" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Frango Assado (220 kcal)</span><input type="checkbox" value="220" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Feijoada (350 kcal)</span><input type="checkbox" value="350" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Lasanha (380 kcal)</span><input type="checkbox" value="380" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Macarronada (320 kcal)</span><input type="checkbox" value="320" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Churrasco Completo (500g - 1350 kcal)</span><input type="checkbox" value="1350" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Linguiça Toscana (2 gomos - 500 kcal)</span><input type="checkbox" value="500" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Salada de Maionese (250 kcal)</span><input type="checkbox" value="250" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Batata Gratinada (220 kcal)</span><input type="checkbox" value="220" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Farofa Temperada (150 kcal)</span><input type="checkbox" value="150" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Batata Frita Porção (300 kcal)</span><input type="checkbox" value="300" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>X-Bacon (650 kcal)</span><input type="checkbox" value="650" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>X-Calota Porção (850 kcal)</span><input type="checkbox" value="850" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Pizza Porção (3 fatias - 900 kcal)</span><input type="checkbox" value="900" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Milk-shake (450 kcal)</span><input type="checkbox" value="450" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Sorvete Porção (3 bolas - 350 kcal)</span><input type="checkbox" value="350" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Pudim de Leite (280 kcal)</span><input type="checkbox" value="280" onchange="somarAlimentos()"></div>
                <div class="alimento-item"><span>Torta de Limão (320 kcal)</span><input type="checkbox" value="320" onchange="somarAlimentos()"></div>
            </div>
        </div>

        <div class="coluna coluna-direita">
            <label style="color:#ffd166; border-bottom: 1px solid #ffd166; padding-bottom: 2px;">👤 Avaliação Individual:</label>
            <div style="display: flex; gap: 6px;">
                <div style="flex: 1;">
                    <label for="sexo" style="color:#ffd166;">Sexo:</label>
                    <select id="sexo">
                        <option value="M">Homem</option>
                        <option value="F">Mulher</option>
                    </select>
                </div>
                <div style="flex: 1;">
                    <label for="peso" style="color:#ffd166;">Peso (kg):</label>
                    <input type="number" id="peso" value="131.95" step="0.1">
                </div>
                <div style="flex: 1;">
                    <label for="altura" style="color:#ffd166;">Altura (cm):</label>
                    <input type="number" id="altura" value="185">
                </div>
                <div style="flex: 1;">
                    <label for="idade" style="color:#ffd166;">Idade:</label>
                    <input type="number" id="idade" value="53">
                </div>
            </div>

            <label for="consumo">Consumo Calórico Total (kcal):</label>
            <input type="number" id="consumo" value="0">

            <label for="passos">Passos do Dia:</label>
            <input type="number" id="passos" value="0">

            <label for="met">Atividade Física (MET):</label>
            <select id="met">
                <option value="0.0">Nenhuma Atividade (0.0 MET)</option>
                <option value="3.0">Caminhada Leve (3.0 MET)</option>
                <option value="4.5">Natação Leve (4.5 MET)</option>
                <option value="6.0">Corrida Moderada (6.0 MET)</option>
                <option value="6.8">Bike Moderada (6.8 MET)</option>
                <option value="8.0">Musculação Intensa (8.0 MET)</option>
                <option value="8.0">Futebol / Ciclismo Intenso (8.0 MET)</option>
            </select>

            <label for="tempo">Tempo da Atividade (minutos):</label>
            <input type="number" id="tempo" value="45">

            <button onclick="calcular()">⚡ CALCULAR BALANÇO</button>
        </div>
    </div>

    <div id="resultado" class="resultado"></div>
</div>

<script>
function somarAlimentos() {
    let total = 0;
    const checkboxes = document.querySelectorAll('.alimentos-grid input[type="checkbox"]:checked');
    checkboxes.forEach(cb => { total += parseFloat(cb.value); });
    document.getElementById('consumo').value = total;
}

async function sincronizarHardware() {
    try {
        const res = await fetch('/api/dados');
        if (res.ok) {
            const data = await res.json();
            document.getElementById('livePassos').innerText = data.passos;
            document.getElementById('liveFsr').innerText = data.fsr;
            
            const inputPassos = document.getElementById('passos');
            if (inputPassos.dataset.manual !== "true") {
                inputPassos.value = data.passos;
            }
        }
    } catch(e) {}
}

document.getElementById('passos').addEventListener('input', function() {
    this.dataset.manual = "true";
});

setInterval(sincronizarHardware, 1000);

function calcular() {
    const sexo = document.getElementById('sexo').value;
    const peso = parseFloat(document.getElementById('peso').value) || 0;
    const altura = parseFloat(document.getElementById('altura').value) || 0;
    const idade = parseFloat(document.getElementById('idade').value) || 0;

    let tmbBase = (10 * peso) + (6.25 * altura) - (5 * idade);
    tmbBase += (sexo === 'M') ? 5 : -161;

    const passos = parseFloat(document.getElementById('passos').value) || 0;
    const consumo = parseFloat(document.getElementById('consumo').value) || 0;
    const met = parseFloat(document.getElementById('met').value) || 0;
    const tempo = parseFloat(document.getElementById('tempo').value) || 0;

    const gastoPassos = passos * 0.05;
    const gastoMet = met * peso * (tempo / 60.0);
    const gastoTotal = tmbBase + gastoPassos + gastoMet;
    const balanco = consumo - gastoTotal;

    const resDiv = document.getElementById('resultado');
    resDiv.style.display = 'block';

    let cor = balanco < 0 ? '#00e676' : '#ff5252';
    let status = balanco < 0 ? 'DÉFICIT CALÓRICO' : 'SUPERÁVIT CALÓRICO';

    resDiv.innerHTML = `
        <h3>📊 RESULTADO DA AVALIAÇÃO INDIVIDUAL</h3>
        <p style="color:#aaa; font-size:0.9em; margin-bottom:10px;">TMB Calculada (${sexo === 'M' ? 'Homem' : 'Mulher'}): <b>${tmbBase.toFixed(1)} kcal</b></p>
        <div class="res-linha">
            <span>Consumo Total: <b style="color:#ffd166;">${consumo.toFixed(0)} kcal</b></span>
            <span>Gasto Estimado: <b style="color:#00f0ff;">${gastoTotal.toFixed(1)} kcal</b></span>
        </div>
        <hr style="border-color: #00b4d8; opacity: 0.3; margin: 12px 0;">
        <p style="color: ${cor}; font-size: 1.3em; margin: 5px 0; font-weight: bold; text-shadow: 0 0 10px ${cor};">
            ${status}: ${Math.abs(balanco).toFixed(1)} kcal
        </p>
    `;
}
</script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

void handleApiDados() {
  String json = "{\"passos\":" + String(totalPassos) + ",\"fsr\":" + String(ultimaLeituraFSR) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_FSR, INPUT);
  pinMode(PIN_MOSFET, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Conectado! IP do ESP32: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/api/dados", handleApiDados);
  server.begin();
}

void loop() {
  server.handleClient();

  // Leitura do FSR 402 no calcanhar
  ultimaLeituraFSR = analogRead(PIN_FSR);

  // Amortecimento Magnético
  int pwmVal = map(ultimaLeituraFSR, 0, 4095, 0, 255);
  analogWrite(PIN_MOSFET, pwmVal);

  // Validação do passo por pressão
  if (ultimaLeituraFSR > LIMIAR_PASSO && !passoEmAndamento) {
    passoEmAndamento = true;
    totalPassos++;
  } else if (ultimaLeituraFSR < (LIMIAR_PASSO - 400) && passoEmAndamento) {
    passoEmAndamento = false;
  }

  delay(20);
}
