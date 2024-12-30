Het programma maakt gebruik van de PS2Keyboard-bibliotheek om invoer van een PS2-toetsenbord te verwerken.
Er is een wachtrij gedefinieerd om de getypte tekens op te slaan, met een maximale grootte van 128 tekens.
Er zijn functies gedefinieerd om tekens toe te voegen aan de wachtrij, er tekens uit te halen en de wachtrij leeg te maken.
De ps2poll() - functie leest invoer van het toetsenbord en voegt de tekens toe aan de wachtrij.
De mydelay() - functie zorgt voor een vertraging met een bepaalde tijd, waarbij de ps2poll() - functie wordt aangeroepen om invoer van het toetsenbord te blijven verwerken.
Er zijn functies gedefinieerd om een punt(dit), een streep(dah)
De dit()-functie genereert een punt door de LED aan te zetten, een toon te genereren en vervolgens na de juiste tijdsduur. (gebaseerd op de snelheid in woorden per minuut) de LED uit te zetten en de toon te stoppen.

De dah() - functie genereert een streep op dezelfde manier, maar met een tijdsduur van drie keer de lengte van een punt.
De lspace() - functie genereert een korte pauze door een vertraging van twee keer de lengte van een punt.
De space() - functie genereert een lange pauze door een vertraging van vier keer de lengte van een punt.
De sendcode() - functie neemt een Morse - code - symbool als invoer(in de vorm van een byte met de bits die de punten en strepen representeren) en genereert het bijbehorende Morse - code - patroon door herhaaldelijk de dit() en dah() - functies aan te roepen, afgewisseld met lspace() - pauzes.
De send() - functie is verantwoordelijk voor het vertalen van een individueel teken naar het bijbehorende Morse - code - symbool.
Deze functie maakt gebruik van de sendcode() - functie om het Morse - code - patroon te genereren.
De loop() - functie is de hoofdlus van het programma.Hierin wordt de ps2poll() - functie aangeroepen om invoer van het toetsenbord te verwerken.
Als er tekens in de wachtrij staan, worden deze één voor één verzonden met behulp van de send() - functie.

Het belangrijkste doel van deze functies is om het Morse - code - genereren te abstraheren en te encapsuleren, zodat het eenvoudig kan worden gebruikt in de rest van het programma.De dit(), dah(), lspace() en space() - functies vormen de bouwstenen voor het genereren van Morse - code - symbolen, terwijl de sendcode() en send() - functies het vertalen en verzenden van tekens naar Morse - code - patronen afhandelen. 
Er zijn tabellen gedefinieerd met de Morse-code-symbolen voor letters en cijfers.

In de setup() - functie worden de pinnen voor de LED en de toon geïnitialiseerd, de seriële communicatie gestart en het PS2 - toetsenbord geïnitialiseerd.

Het belangrijkste doel van dit programma is om een Morse - code - toetsenbordfunctionaliteit te bieden.
Wanneer de gebruiker op het toetsenbord typt, worden de tekens in de wachtrij opgeslagen en vervolgens als Morse - code - symbolen verzonden.
De LED en de toon geven visuele en auditieve feedback over de verzonden tekens.

Het programma biedt ook enkele speciale functies, zoals het leegmaken van de wachtrij bij het indrukken van de Escape - toets en het automatisch verzenden van "CQ CQ CQ DE ON4JES ON4JES ON4JES" bij het indrukken van de '%' - toets.
