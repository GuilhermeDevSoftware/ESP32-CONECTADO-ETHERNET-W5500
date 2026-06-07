#include <SPI.h>
#include <Ethernet.h>

#define PINO_SCK   18
#define PINO_MISO  19
#define PINO_MOSI  23
#define PINO_CS     5
#define PINO_RST   26

byte mac[] = {
  0x02, 0x12, 0x34, 0x56, 0x78, 0x90
};

void reiniciarW5500() {
  pinMode(PINO_RST, OUTPUT);

  digitalWrite(PINO_RST, LOW);
  delay(200);

  digitalWrite(PINO_RST, HIGH);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Iniciando ESP32 + W5500...");

  reiniciarW5500();

  SPI.begin(PINO_SCK, PINO_MISO, PINO_MOSI, PINO_CS);
  Ethernet.init(PINO_CS);

  Serial.println("Procurando endereco IP via DHCP...");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha ao obter IP via DHCP.");
    return;
  }

  delay(1000);

  Serial.println("Ethernet conectada!");

  Serial.print("IP Ethernet: ");
  Serial.println(Ethernet.localIP());

  Serial.print("Mascara de rede: ");
  Serial.println(Ethernet.subnetMask());

  Serial.print("Gateway: ");
  Serial.println(Ethernet.gatewayIP());

  Serial.print("Servidor DNS: ");
  Serial.println(Ethernet.dnsServerIP());

  EthernetClient cliente;

  Serial.println();
  Serial.println("Testando acesso a internet...");

  if (cliente.connect("example.com", 80)) {
    Serial.println("Internet funcionando!");

    cliente.println("GET / HTTP/1.1");
    cliente.println("Host: example.com");
    cliente.println("Connection: close");
    cliente.println();

    cliente.stop();
  } else {
    Serial.println("Sem acesso a internet.");
  }
}

void loop() {
}