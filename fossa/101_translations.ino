// Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
String translate(String key, String language) {
  const char* translations = R"(
[en]
usb = USB config mode
tapScreen = TAP SCREEN WHEN FINISHED
scanMe = SCAN ME TAP SCREEN WHEN FINISHED
total = Total: 
fossa = FOSSA! Bitcoin ATM
sats = SATS
forT = FOR
fiat = FIAT!
feed = feed me fiat.
charge = % charge
printing = Printing
wait = please wait
working = Working...

[es]
usb = Modo de configuracion USB
tapScreen = TOQUE LA PANTALLA CUANDO TERMINE
scanMe = ESCANEME TOQUE LA PANTALLA CUANDO TERMINE
total = Total: 
fossa = FOSSA! Cajero Bitcoin
sats = SATS
forT = PARA
fiat = FIAT!
feed = dame fiat.
charge = % de carga
printing = Imprimiendo
wait = por favor espera
working = Trabajando...

[fr]
usb = Mode de configuration USB
tapScreen = TOUCHEZ L ECRAN QUAND TERMINE
scanMe = SCANEZ MOI TOUCHEZ L ECRAN QUAND TERMINE
total = Total: 
fossa = FOSSA! Distributeur Bitcoin
sats = SATS
forT = POUR
fiat = FIAT!
feed = nourrissez moi de fiat
charge = % charge
printing = Impression
wait = veuillez patienter
working = En cours...

[de]
usb = USB-Konfigurationsmodus
tapScreen = BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
scanMe = SCANNEN SIE MICH BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
total = Gesamt: 
fossa = FOSSA! Bitcoin-Geldautomat
sats = SATS
forT = FUER
fiat = FIAT!
feed = fuettere mich mit Fiat
charge = % Ladung
printing = Drucken
wait = bitte warten
working = Arbeitet...

[it]
usb = Modalita di configurazione USB
tapScreen = TOCCA LO SCHERMO QUANDO FINITO
scanMe = SCAN SIONAMI TOCCA LO SCHERMO QUANDO FINITO
total = Totale: 
fossa = FOSSA! Bancomat Bitcoin
sats = SATS
forT = PER
fiat = FIAT!
feed = dammelo in fiat
charge = % carica
printing = Stampa in corso
wait = attendere prego
working = Funzionamento...

[pt]
usb = Modo de configuracao USB
tapScreen = TOQUE NA TELA QUANDO TERMINAR
scanMe = ESCANEIE ME TOQUE NA TELA QUANDO TERMINAR
total = Total: 
fossa = FOSSA! Caixa eletrônico Bitcoin
sats = SATS
forT = PARA
fiat = FIAT!
feed = me dê fiat
charge = % de carga
printing = Imprimindo
wait = por favor aguarde
working = Trabalhando...

[pl]
usb = Tryb konfiguracji USB
tapScreen = DOTKNIJ EKRAN PO UKONCZENIU
scanMe = SCANUJ MNIE DOTKNIJ EKRAN PO UKONCZENIU
total = Razem: 
fossa = FOSSA! Bankomat Bitcoin
sats = SATS
forT = DLA
fiat = FIAT!
feed = daj mi fiat
charge = % ladunku
printing = Drukowanie
wait = proszę czekać
working = Pracuje...

[hu]
usb = USB konfiguracios mod
tapScreen = TAP IN EKRANRA HA VEGE
scanMe = SZKENNELJ ENGEM TAP IN EKRANRA HA VEGE
total = Osszesen: 
fossa = FOSSA! Bitcoin ATM
sats = SATS
forT = SZAMARA
fiat = FIAT!
feed = etess meg fiatot
charge = % toltes
printing = Nyomtat
wait = kerlek varj
working = Dolgozik...

[tr]
usb = USB yapilandirma modu
tapScreen = BITTIGINDE EKRANA DOKUNUN
scanMe = BENI TARAYIN BITTIGINDE EKRANA DOKUNUN
total = Toplam: 
fossa = FOSSA! Bitcoin ATM
sats = SATS
forT = I CIN
fiat = FIAT!
feed = bana fiat ver
charge = % sarj
printing = Yazdiriliyor
wait = lutfen bekleyin
working = Calisiyor...

[ro]
usb = Modul de configurare USB
tapScreen = ATINGETI ECRANUL CAND TERMINATI
scanMe = SCANATI-MA ATINGETI ECRANUL CAND TERMINATI
total = Total: 
fossa = FOSSA! Bancomat Bitcoin
sats = SATS
forT = PENTRU
fiat = FIAT!
feed = da-mi fiat
charge = % incarcare
printing = Tiparire
wait = va rog asteptati
working = Lucreaza...

[fi]
usb = USB-konfigurointitila
tapScreen = KOSKETA NÄYTTÖÄ VALMIINA
scanMe = SKANNAA MINUT KOSKETA NÄYTTÖÄ VALMIINA
total = Yhteensä: 
fossa = FOSSA! Bitcoin-ATK
sats = SATS
forT = KÄYTETTÄVÄ
fiat = FIAT!
feed = anna minulle fiat
charge = % lataus
printing = Tulostus
wait = ole hyvä ja odota
working = Työskentelee...

[sv]
usb = USB-konfigurationsläge
tapScreen = TRYCK PÅ SKÄRMEN NÄR KLAR
scanMe = SKANNA MIG TRYCK PÅ SKÄRMEN NÄR KLAR
total = Totalt: 
fossa = FOSSA! Bitcoin-automat
sats = SATS
forT = FÖR
fiat = FIAT!
feed = mata mig fiat
charge = % laddning
printing = Utskrift
wait = vänligen vänta
working = Arbetar...
)";

  String line;
  bool inCorrectLanguage = false;
  int startPos = 0;
  int endPos;

  while (startPos < strlen(translations)) {
    endPos = startPos;
    while (translations[endPos] != '\n' && translations[endPos] != '\0') {
      endPos++;
    }
    line = String(translations).substring(startPos, endPos);
    line.trim();  // Trim line
    startPos = endPos + 1;

    if (line.length() == 0) {
      continue;
    }

    // Check for language section
    if (line.startsWith("[")) {
      inCorrectLanguage = (line == "[" + language + "]");
      continue;
    }

    if (inCorrectLanguage) {
      int separatorPos = line.indexOf('=');
      if (separatorPos != -1) {
        String currentKey = line.substring(0, separatorPos);
        currentKey.trim();  // Trim key separately

        String value = line.substring(separatorPos + 1);
        value.trim();  // Trim value separately

        if (currentKey == key) {
          return value;
        }
      }
    }
  }

  return key;  // Return the key if no translation is found
}

void translateAll(String language) {
  usbT = translate("usb", language);
  tapScreenT = translate("tapScreen", language);
  scanMeT = translate("scanMe", language);
  totalT = translate("total", language);
  fossaT = translate("fossa", language);
  satsT = translate("sats", language);
  forT = translate("forT", language);
  fiatT = translate("fiat", language);
  feedT = translate("feed", language);
  chargeT = translate("charge", language);
  printingT = translate("printing", language);
  waitT = translate("wait", language);
  workingT = translate("working", language);
}
