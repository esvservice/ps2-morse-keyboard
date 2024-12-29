#include "PS2Keyboard.h"

// board: arduino nano ATmega328P
// 
// Het programma maakt gebruik van de PS2Keyboard-bibliotheek om invoer van een PS2-toetsenbord te verwerken.
// Er is een wachtrij gedefinieerd om de getypte tekens op te slaan, met een maximale grootte van 128 tekens.
// Er zijn functies gedefinieerd om tekens toe te voegen aan de wachtrij, er tekens uit te halen en de wachtrij leeg te maken.
// De ps2poll() - functie leest invoer van het toetsenbord en voegt de tekens toe aan de wachtrij.
// De mydelay() - functie zorgt voor een vertraging met een bepaalde tijd, waarbij de ps2poll() - functie wordt aangeroepen om invoer van 
// het toetsenbord te blijven verwerken.
// Er zijn functies gedefinieerd om een punt(dit), een streep(dah)
// De dit()-functie genereert een punt door de LED aan te zetten, een toon te genereren en vervolgens na de juiste tijdsduur 
// (gebaseerd op de snelheid in woorden per minuut) de LED uit te zetten en de toon te stoppen.

// De dah() - functie genereert een streep op dezelfde manier, maar met een tijdsduur van drie keer de lengte van een punt.
// De lspace() - functie genereert een korte pauze door een vertraging van twee keer de lengte van een punt.
// De space() - functie genereert een lange pauze door een vertraging van vier keer de lengte van een punt.
// De sendcode() - functie neemt een Morse - code - symbool als invoer(in de vorm van een byte met de bits die de punten en strepen representeren) 
// en genereert het bijbehorende Morse - code - patroon door herhaaldelijk de dit() en dah() - functies aan te roepen, afgewisseld met lspace() - pauzes.
// De send() - functie is verantwoordelijk voor het vertalen van een individueel teken naar het bijbehorende Morse - code - symbool.
// Deze functie maakt gebruik van de sendcode() - functie om het Morse - code - patroon te genereren.
// De loop() - functie is de hoofdlus van het programma.Hierin wordt de ps2poll() - functie aangeroepen om invoer van het toetsenbord te verwerken.
// Als er tekens in de wachtrij staan, worden deze één voor één verzonden met behulp van de send() - functie.

// Het belangrijkste doel van deze functies is om het Morse - code - genereren te abstraheren en te encapsuleren, 
// zodat het eenvoudig kan worden gebruikt in de rest van het programma.De dit(), dah(), lspace() en space() - functies vormen 
// de bouwstenen voor het genereren van Morse - code - symbolen, terwijl de sendcode() en send() - functies het vertalen en verzenden 
// van tekens naar Morse - code - patronen afhandelen. 
// Er zijn tabellen gedefinieerd met de Morse-code-symbolen voor letters en cijfers.

//In de setup() - functie worden de pinnen voor de LED en de toon geïnitialiseerd, de seriële communicatie gestart en het PS2 - toetsenbord geïnitialiseerd.

// Het belangrijkste doel van dit programma is om een Morse - code - toetsenbordfunctionaliteit te bieden.
// Wanneer de gebruiker op het toetsenbord typt, worden de tekens in de wachtrij opgeslagen en vervolgens als Morse - code - symbolen verzonden.
// De LED en de toon geven visuele en auditieve feedback over de verzonden tekens.

// Het programma biedt ook enkele speciale functies, zoals het leegmaken van de wachtrij bij het indrukken van de Escape - toets 
// en het automatisch verzenden van "CQ CQ CQ DE ON4JES ON4JES ON4JES" bij het indrukken van de '%' - toets.

// Definities voor de wachtrij
#define QUEUESIZE (128)
#define QUEUEMASK (QUEUESIZE-1)

int aborted = 0;
int qhead = 0;
int qtail = 0;
char queue[QUEUESIZE];

// Functie om een teken toe te voegen aan de wachtrij
void queueadd(char ch) {
    queue[qtail++] = ch;
    qtail &= QUEUEMASK;
}

// Functie om een string toe te voegen aan de wachtrij
void queueadd(char* s) {
    while (*s)
        queueadd(*s++);
}

// Functie om een teken uit de wachtrij te halen
char queuepop() {
    char ch;
    ch = queue[qhead++];
    qhead &= QUEUEMASK;
    return ch;
}

// Functie om te controleren of de wachtrij vol is
int queuefull() {
    return (((qtail + 1) & QUEUEMASK) == qhead);
}

// Functie om te controleren of de wachtrij leeg is
int queueempty() {
    return (qhead == qtail);
}

// Functie om de wachtrij leeg te maken
void queueflush() {
    qhead = qtail;
}

// Pinnen voor de LED en de toon
int pin = 13;
int tpin = 10;

// Definitie voor de snelheid in woorden per minuut
#define WPM (20)
int ditlen = 1200 / WPM;

PS2Keyboard kbd;

// Functie om invoer van het toetsenbord te verwerken
inline void ps2poll() {
    char ch;
    while (kbd.available()) {
        if (queuefull()) {
            Serial.print("");
        }
        else {
            switch (ch = kbd.read()) {
            case '\033':
                queueflush();
                Serial.flush();
                Serial.println("== FLUSH ==");
                aborted = 1;
                break;
            case '%':
                queueadd("CQ CQ CQ DE ON4JES ON4JES ON4JES \r\n");
                break;
            default:
                queueadd(ch);
                break;
            }
        }
    }
}

// Functie om te vertragen met een bepaalde tijd
void mydelay(unsigned long ms) {
    unsigned long t = millis();
    while (millis() - t < ms)
        ps2poll();
}

#define FREQ (700)

// Functie om een toonschaal af te spelen
void scale() {
    long f = 220L;
    int i;

    for (i = 0; i <= 12; i++) {
        tone(tpin, (int)f);
        f *= 1059L;
        f /= 1000L;
        Serial.println(f);
        delay(300);
    }
    noTone(tpin);
}

// Functie om een punt (dit) te genereren
void dit() {
    digitalWrite(pin, HIGH);
    tone(tpin, FREQ);
    mydelay(ditlen);
    digitalWrite(pin, LOW);
    noTone(tpin);
    mydelay(ditlen);
}

// Functie om een streep (dah) te genereren
void dah() {
    digitalWrite(pin, HIGH);
    tone(tpin, FREQ);
    mydelay(3 * ditlen);
    digitalWrite(pin, LOW);
    noTone(tpin);
    mydelay(ditlen);
}

// Functie om een korte pauze te genereren
void lspace() {
    mydelay(2 * ditlen);
}

// Functie om een lange pauze te genereren
void space() {
    mydelay(4 * ditlen);
}

// Functie die wordt uitgevoerd bij het opstarten van het programma
void setup() {
    pinMode(pin, OUTPUT);
    pinMode(tpin, OUTPUT);
    Serial.begin(9600);
    kbd.begin(4, 3);
    Serial.println("Morse Code Keyboard by ON4JES");
}

// Tabel met Morse-code-symbolen voor letters
char ltab[] = {
  0b101,    // A
  0b11000,  // B
  // Meer Morse-code-symbolen voor letters
};

// Tabel met Morse-code-symbolen voor cijfers
char ntab[] = {
  0b111111, // 0
  0b101111, // 1
  // Meer Morse-code-symbolen voor cijfers
};

// Functie om een Morse-code-symbool te verzenden
void sendcode(char code) {
    int i;

    for (i = 7; i >= 0; i--)
        if (code & (1 << i))
            break;

    for (i--; i >= 0; i--) {
        if (code & (1 << i))
            dah();
        else
            dit();
    }
    lspace();
}

// Functie om een teken te verzenden
void send(char ch) {
    if (isalpha(ch)) {
        if (islower(ch))
            ch = toupper(ch);
        sendcode(ltab[ch - 'A']);
    }
    else if (isdigit(ch))
        sendcode(ntab[ch - '0']);
    else if (ch == ' ' || ch == '\r' || ch == '\n')
        space();
    else if (ch == '.')
        sendcode(0b1010101);
    else if (ch == ',')
        sendcode(0b1110011);
    else if (ch == '!')
        sendcode(0b1101011);
    else if (ch == '?')
        sendcode(0b1001100);
    else if (ch == '/')
        sendcode(0b110010);
    else if (ch == '+')
        sendcode(0b101010);
    else if (ch == '-')
        sendcode(0b1100001);
    else if (ch == '=')
        sendcode(0b110001);
    else if (ch == '@')
        sendcode(0b1011010);
    else
        return; // Negeer alle andere tekens

    if (!aborted) {
        Serial.print(ch);
        if (ch == 13)
            Serial.print((char)10);
    }
    aborted = 0;
}

// Hoofdlus van het programma
void loop() {
    ps2poll();

    if (!queueempty())
        send(queuepop());
}
