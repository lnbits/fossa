// Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
String translate(String key, String language) {
  const char* translations = R"(
[en]
usbT = USB config mode
tapScreenT = TAP SCREEN WHEN FINISHED
scanMeT = SCAN ME TAP SCREEN WHEN FINISHED
totalT = Total: 
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = FOR
fiatT = FIAT!
feedT = feed me fiat.
chargeT = % charge
printingT = Printing
waitT = please wait
workingT = Working...
thisVoucherT = This voucher can be redeemed for
ofBitcoinT = of Bitcoin
thankYouT = Thank you
scanMeClaimT = Scan me with a Lightning wallet to get your Bitcoin
tooMuchFiatT = Too much FIAT!
contactOwnerT = Please contact owner

[es]
usbT = Modo de configuracion USB
tapScreenT = TOQUE LA PANTALLA CUANDO TERMINE
scanMeT = ESCANEME TOQUE LA PANTALLA CUANDO TERMINE
totalT = Total:
fossaT = FOSSA! Cajero Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = dame fiat.
chargeT = % de carga
printingT = Imprimiendo
waitT = por favor espera
workingT = Trabajando...
thisVoucherT = Este vale se puede canjear por
ofBitcoinT = de Bitcoin
thankYouT = Gracias
scanMeClaimT = Escanéame con una billetera Lightning para recibir tu Bitcoin
tooMuchFiatT = ¡Demasiado FIAT!
contactOwnerT = Por favor contacta al propietario

[fr]
usbT = Mode de configuration USB
tapScreenT = TOUCHEZ L ECRAN QUAND TERMINE
scanMeT = SCANEZ MOI TOUCHEZ L ECRAN QUAND TERMINE
totalT = Total:
fossaT = FOSSA! Distributeur Bitcoin
satsT = SATS
forT = POUR
fiatT = FIAT!
feedT = nourrissez moi de fiat
chargeT = % charge
printingT = Impression
waitT = veuillez patienter
workingT = En cours...
thisVoucherT = Ce bon peut être échangé contre
ofBitcoinT = de Bitcoin
thankYouT = Merci
scanMeClaimT = Scannez-moi avec un portefeuille Lightning pour obtenir votre Bitcoin
tooMuchFiatT = Trop de FIAT !
contactOwnerT = Veuillez contacter le propriétaire

[de]
usbT = USB-Konfigurationsmodus
tapScreenT = BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
scanMeT = SCANNEN SIE MICH BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
totalT = Gesamt:
fossaT = FOSSA! Bitcoin-Geldautomat
satsT = SATS
forT = FUER
fiatT = FIAT!
feedT = fuettere mich mit Fiat
chargeT = % Ladung
printingT = Drucken
waitT = bitte warten
workingT = Arbeitet...
thisVoucherT = Dieser Gutschein kann eingelöst werden für
ofBitcoinT = von Bitcoin
thankYouT = Danke
scanMeClaimT = Scannen Sie mich mit einem Lightning-Wallet, um Ihr Bitcoin zu erhalten
tooMuchFiatT = Zu viel FIAT!
contactOwnerT = Bitte kontaktieren Sie den Besitzer

[it]
usbT = Modalita di configurazione USB
tapScreenT = TOCCA LO SCHERMO QUANDO FINITO
scanMeT = SCAN SIONAMI TOCCA LO SCHERMO QUANDO FINITO
totalT = Totale:
fossaT = FOSSA! Bancomat Bitcoin
satsT = SATS
forT = PER
fiatT = FIAT!
feedT = dammelo in fiat
chargeT = % carica
printingT = Stampa in corso
waitT = attendere prego
workingT = Funzionamento...
thisVoucherT = Questo voucher può essere riscattato per
ofBitcoinT = di Bitcoin
thankYouT = Grazie
scanMeClaimT = Scansionami con un portafoglio Lightning per ottenere il tuo Bitcoin
tooMuchFiatT = Troppo FIAT!
contactOwnerT = Per favore contatta il proprietario

[pt]
usbT = Modo de configuracao USB
tapScreenT = TOQUE NA TELA QUANDO TERMINAR
scanMeT = ESCANEIE ME TOQUE NA TELA QUANDO TERMINAR
totalT = Total:
fossaT = FOSSA! Caixa eletrônico Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = me dê fiat
chargeT = % de carga
printingT = Imprimindo
waitT = por favor aguarde
workingT = Trabalhando...
thisVoucherT = Este voucher pode ser resgatado por
ofBitcoinT = de Bitcoin
thankYouT = Obrigado
scanMeClaimT = Escaneie-me com uma carteira Lightning para obter seu Bitcoin
tooMuchFiatT = Muito FIAT!
contactOwnerT = Por favor, entre em contato com o proprietário

[pl]
usbT = Tryb konfiguracji USB
tapScreenT = DOTKNIJ EKRAN PO UKONCZENIU
scanMeT = SCANUJ MNIE DOTKNIJ EKRAN PO UKONCZENIU
totalT = Razem:
fossaT = FOSSA! Bankomat Bitcoin
satsT = SATS
forT = DLA
fiatT = FIAT!
feedT = daj mi fiat
chargeT = % ladunku
printingT = Drukowanie
waitT = proszę czekać
workingT = Pracuje...
thisVoucherT = Ten bon może być wymieniony na
ofBitcoinT = Bitcoin
thankYouT = Dziękuję
scanMeClaimT = Zeskanuj mnie portfelem Lightning, aby otrzymać swój Bitcoin
tooMuchFiatT = Za dużo FIAT!
contactOwnerT = Proszę skontaktować się z właścicielem

[hu]
usbT = USB konfiguracios mod
tapScreenT = TAP IN EKRANRA HA VEGE
scanMeT = SZKENNELJ ENGEM TAP IN EKRANRA HA VEGE
totalT = Osszesen:
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = SZAMARA
fiatT = FIAT!
feedT = etess meg fiatot
chargeT = % toltes
printingT = Nyomtat
waitT = kerlek varj
workingT = Dolgozik...
thisVoucherT = Ez a kupon beváltható
ofBitcoinT = Bitcoin-ra
thankYouT = Köszönöm
scanMeClaimT = Szkenneljen be egy Lightning pénztárcával, hogy megkapja a Bitcoinját
tooMuchFiatT = Túl sok FIAT!
contactOwnerT = Kérjük, lépjen kapcsolatba a tulajdonossal

[tr]
usbT = USB yapilandirma modu
tapScreenT = BITTIGINDE EKRANA DOKUNUN
scanMeT = BENI TARAYIN BITTIGINDE EKRANA DOKUNUN
totalT = Toplam:
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = I CIN
fiatT = FIAT!
feedT = bana fiat ver
chargeT = % sarj
printingT = Yazdiriliyor
waitT = lutfen bekleyin
workingT = Calisiyor...
thisVoucherT = Bu kupon şunun için kullanılabilir
ofBitcoinT = Bitcoin
thankYouT = Teşekkür ederim
scanMeClaimT = Bitcoin'inizi almak için beni bir Lightning cüzdanı ile tarayın
tooMuchFiatT = Çok fazla FIAT!
contactOwnerT = Lütfen sahibine ulaşın

[ro]
usbT = Modul de configurare USB
tapScreenT = ATINGETI ECRANUL CAND TERMINATI
scanMeT = SCANATI-MA ATINGETI ECRANUL CAND TERMINATI
totalT = Total:
fossaT = FOSSA! Bancomat Bitcoin
satsT = SATS
forT = PENTRU
fiatT = FIAT!
feedT = da-mi fiat
chargeT = % incarcare
printingT = Tiparire
waitT = va rog asteptati
workingT = Lucreaza...
thisVoucherT = Acest voucher poate fi răscumpărat pentru
ofBitcoinT = de Bitcoin
thankYouT = Mulțumesc
scanMeClaimT = Scanează-mă cu un portofel Lightning pentru a primi Bitcoinul tău
tooMuchFiatT = Prea mult FIAT!
contactOwnerT = Vă rugăm să contactați proprietarul

[fi]
usbT = USB-konfigurointitila
tapScreenT = KOSKETA NÄYTTÖÄ VALMIINA
scanMeT = SKANNAA MINUT KOSKETA NÄYTTÖÄ VALMIINA
totalT = Yhteensä:
fossaT = FOSSA! Bitcoin-ATK
satsT = SATS
forT = KÄYTETTÄVÄ
fiatT = FIAT!
feedT = anna minulle fiat
chargeT = % lataus
printingT = Tulostus
waitT = ole hyvä ja odota
workingT = Työskentelee...
thisVoucherT = Tämä kuponki voidaan lunastaa seuraavaan:
ofBitcoinT = Bitcoinia
thankYouT = Kiitos
scanMeClaimT = Skannaa minut Lightning-lompakolla saadaksesi Bitcoinisi
tooMuchFiatT = Liikaa FIATia!
contactOwnerT = Ole hyvä ja ota yhteyttä omistajaan

[sv]
usbT = USB-konfigurationsläge
tapScreenT = TRYCK PÅ SKÄRMEN NÄR KLAR
scanMeT = SKANNA MIG TRYCK PÅ SKÄRMEN NÄR KLAR
totalT = Totalt:
fossaT = FOSSA! Bitcoin-automat
satsT = SATS
forT = FÖR
fiatT = FIAT!
feedT = mata mig fiat
chargeT = % laddning
printingT = Utskrift
waitT = vänligen vänta
workingT = Arbetar...
thisVoucherT = Denna kupong kan lösas in för
ofBitcoinT = Bitcoin
thankYouT = Tack
scanMeClaimT = Skanna mig med en Lightning-plånbok för att få din Bitcoin
tooMuchFiatT = För mycket FIAT!
contactOwnerT = Vänligen kontakta ägaren
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
  usbT = translate("usbT", language);
  tapScreenT = translate("tapScreenT", language);
  scanMeT = translate("scanMeT", language);
  totalT = translate("totalT", language);
  fossaT = translate("fossaT", language);
  satsT = translate("satsT", language);
  forT = translate("forT", language);
  fiatT = translate("fiatT", language);
  feedT = translate("feedT", language);
  chargeT = translate("chargeT", language);
  printingT = translate("printingT", language);
  waitT = translate("waitT", language);
  workingT = translate("workingT", language);
  thisVoucherT = translate("chargeT", language);
  ofBitcoinT = translate("printingT", language);
  thankYouT = translate("waitT", language);
  scanMeClaimT = translate("workingT", language);
  tooMuchFiatT = translate("tooMuchFiatT", language);
  contactOwnerT = translate("contactOwnerT", language);
}
