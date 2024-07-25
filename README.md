![image](https://github.com/user-attachments/assets/e9effe58-8963-4e5c-996e-52682ba15627)

## Demo

https://twitter.com/arcbtc/status/1567639231333277697

## Bill of Materials

The parts for this ATM should be approximately £200-£250!

You can run the FOSSA as either coin machine and bill acceptor, or either on their own.

### Primary FOSSA components

| Part    | Description    | Buy (UK)    | Estimated cost |
|-------------|-------------|-------------|-------------|
| ESP32 WT32-SC01 | This is the ESP32 touchscreen. No wifi required. Should be supplied with a USB-C to USB cable | Ebay or [AliExpress](https://www.aliexpress.com/item/1005003191471709.html) | **£45** |
| Option: NV10USB+ bill acceptor | The bill acceptor option to account cash notes. To accept GBP request that it be set to GBP and SIO mode. | [Ebay (second hand)](https://www.ebay.co.uk/itm/263398460026) | **£70-£150** |
| Option: DG600F(S) Multi Coin Acceptor | The coin acceptor option. The "S" denotes the front panel (stainless steel sheet version, where we can 3D print a black panel for it). | [AliExpress](https://www.aliexpress.com/w/wholesale-DG600F(S)-Multi-Coin-Acceptor.html?spm=a2g0o.home.search.0) or Ebay (second-hand) | **£30** |
| Screw terminal block | Easily connect the wires without soldering. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B08LNWMMHQ) | **£1** |
| 12v power supply | Best to get one with terminal block adapter (12v battery also works well, for unplugged version). | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MTBTXDJ/) | **£8** |
| 12v to 5v step down converter with USB | 12V to 5V: The adapter converter module can convert unstable voltage DC 12V to stable DC 5V / 15W 3A output. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B07QQ587K3) | **£5**
| Male-to-female GPIO jumpers | Plug and play GPIO connectors | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MJZDXBB) | **£5**
| Option: Aluminum "medicine box" | Cheap medicine box for the cash machine | Amazon (UK) | **£30** |
| Option: Amazon Basic Home Safe | More secure box | Amazon (UK) | **£70** |
| Option: 58mm 701 USB Thermal Receipt Printer | Print receipts for users. **NB The 3D printed enclosure does not currently fit this**. | [Ebay (UK)](https://www.ebay.co.uk/itm/293668439213) | **£25** |

![image](https://github.com/user-attachments/assets/35098b91-8d00-4885-bc16-ace9bb804597)

### 3D printed enclosure fixtures & fittings

For the 3D printed version, you will need:

| Part    | Description    | Buy (UK)    |
|-------------|-------------|-------------|
| M4 x 16mm pan head security torx tamper resistant bolts | These hold the front facia to the back box. Anything longer than 14mm - 55mm is fine. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B0BTTRPBQV/) |
| Tamper-proof torx wrench (T20) | To tighten the front facia Torx bolts. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B0D53LNNRW) |
| Brass insert nuts, M4 x 6mm L x 6mm OD | Female threaded heat set knurled embedded insert nuts for 3D printing. These are string than trying to create threads in the 3D print. Using a soldering iron, these are heated up and pushed into the backbox for better attachment of the facia. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MCVW4GQ/) |
| M4 x 30mm carriage/coach bolts | These are to replace the bolts supplied with the coin acceptor to accommodate the thickness of the facia. | [Amazon (UK)](https://www.ebay.co.uk/itm/386550912089?var=653926055961) |
| 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector | This allows the 12V adaptor to plug into the ATM's outside. The box assumes a diameter of 7.7mm (like these). | [Amazon (UK)](https://www.amazon.co.uk/dp/B01N3679B8) |
| 2.2mm Quick Disconnect Female Spade Connector | This allows us to crimp a cable and connect to the 5.5mm x 2.1mm DC Power Jack Socket | |
| Cabinet draw tubular 16mm lock | This will be mounted on the door. | [Amazon (UK)](https://www.amazon.co.uk/Litensh-Tubular-Cylinder-Cupboard-Letterbox/dp/B09SHWXWXC/) |
| Optional: Rubber feet (D30x22xH15) | If you want to have this one on the table, some rubber feet will go at the bottom of the backbox with an M5 bolt. You can also use adhesive versions. Grooves in the bottom of the box will support up to 30mm in diameter. | [Amazon (UK)](https://www.amazon.co.uk/dp/B0CQ23M5Z5) |
| Optional: M5 x 16mm hex socket bolts | To screw the rubber feet into the back box. | [Amazon (UK)](https://www.amazon.co.uk/16mm-Socket-Button-Head-Screws/dp/B09BG8XNM7) |
| Optional: M5 nylon nuts | To screw the rubber feet into the backbox. | [Amazon (UK)](https://www.amazon.co.uk/Bolt-Base-Stainless-Insert-Nylock) |
| Optional: Adhesive security plate and locking cable | Secure the ATM when desk mounted. | [Amazon (UK)](https://www.amazon.co.uk/I3C-Security-Anti-Theft-Hardware-Smartphone/dp/B07FM93JL6) |

## Build

A video tutorial is available here on how to construct the FOSSA:

[https://www.youtube.com/watch?v=vbyYb9Yiu_k](https://www.youtube.com/watch?v=vbyYb9Yiu_k)

### Step 1: Hardware Setup

> **STAY TUNED FOR A WIRING HARNESS TO MAKE THIS PLUG AND PLAY AND YOU CAN SKIP TO STEP 2.**

This method requires no soldering. We do this by using GPIO jumpers and terminal blocks. Forst, split the terminal block into a block a 3 (our LIVE terminal), and a block of 4 (our GROUND terminal).

The wiring reference is as follows:

![image](https://github.com/user-attachments/assets/3d7f7c32-9b69-4405-b0c6-579e2ec194bd)

**To connect the bill acceptor**:

1. Connect the Rx (pin 32) and Tx (pin 33) to 1 and 5 on the bill acceptor.
2. Using a GPIO jumper, connect the live wire (pin 15) to the first LIVE terminal block at an available terminal.
3. Using a GPIO jumper, connect the ground wire (pin 16) to a second GROUND terminal block of block at an available terminal.
4. Connect the positive wire (red) of the 12V to 5V power converter and connect it to the LIVE terminal block at an available terminal.
5. Connect the negative wire (black) of the 12V to 5V power converter and connect it to the GROUND terminal block at an available terminal.
6. Connect the ground pin (e.g. pin 5) of the WT32-SC01 and connect it to the 2nd terminal of the GROUND terminal block at an available terminal.

| NV10USB+ Pin | WT32-SC01 Pin No. (Not GPIO No.) | Power Supply   |
|----------|-----------|----------------|
| 1 (Tx)  | 31         | N/A |
| 5 (Rx)  | 29         | N/A |
| 15 (12V DC+) | N/A | 12V DC+ |
| 16 (GND) | 5         | GND            |

> The bill acceptor needs to be programmed to your currency and set to `SIO` mode, usually you can buy them preconfigured. If you have to program, buy <a href="https://www.innovative-technology.com/shop/cables/nv9-nv10-usb-host-cable-detail">this wire</a> and download the Validator Manager software <a href="https://www.dropbox.com/sh/2mle0czl2j2w7yq/AABie6AJQTq-tXmBv1TUhBUGa?dl=0">here</a> or <a href="http://www.innovative-technology.com/support/secure-download">here</a> (sadly only runs on windows, so use a friends machine). Details on programming can be found <a href="https://github.com/arcbtc/fossa/blob/main/NV10Manual_2.PDF.pdf">here</a>. Its relatively straight forward to program, plug in USB host cable, turn on holding config button for 2 secs, open the Validator Manager software.

Page 42 of the <a href="NV10 operations manual.pdf">NV10 USB Operations Manual</a> shows a wiring diagram for the NV10 USB host cable if you want to build your own programming cable.

> (Ignore all the hardware requirements for programming in the guide, you just need the host cable! Don't try using the programming cards in the guide, thats an old system these machines no longer support "Many Bothans died to bring us this information,")

**To connect the coin acceptor**:

> NB You can usually order the coin acceptor pre-programmed to your currencies, otherwise you will need to train the acceptor using <a href="https://www.youtube.com/watch?v=Dyun1xjKqc4">this guide</a>.

1. Set the 3 dip switch to high (this sends integers to the WT32-SC01 rather than pulses).
2. Using a GPIO jumper, connect the interrupt pin (pin 5) on the coin accepter, to the 5V pin (pin 2) on the WT32-SC01.
3. Using a GPIO jumper, connect the serial out (pin 2) on the coin accepter, to pin 4 on the  WT32-SC01.
4. Using a GPIO jumper, connect the live pin (pin 1) to the LIVE terminal block at an available terminal.
5. Using a GPIO jumper, connect the GND pin (pin 3) on the coin accepter, to the GROUND terminal block at an available terminal.

| DG600F(S) Pin | WT32-SC01 Pin No. (Not GPIO No.) | Power Supply
| ------------- | ------------- | ------------- | 
| 5 | 2 | N/A |
| 4 | N/A | N/A |
| 3 (GND) | N/A | GROUND
| 2 (serial out) | 4 | N/A
| 1 (12V) | N/A | LIVE

**To connect the 12V power supply**:

1. Connect a GPIO pin to the live connection (+) on the 12V power supply terminal block adapter, to the LIVE terminal block at an available terminal.
2. Connect a GPIO pin to the ground connection (-) on the 12V power supply terminal block adapter, to the GROUND terminal block at an available terminal.

**To complete the terminal blocks**:

1. Connect each of the terminals in the LIVE terminal block to each other so they all receive power by looping over wire from terminals 1 to 2 and 1 to 3.
2. Connect each of the terminals in the GROUND terminal block to each other so they all receive power by looping over wire from terminals 1 to 2 and 1 to 3 and 1 to 4.

**To connect to power**:

1. Plug in the WT32-SC01 to the USB connector of the 12V to 5V power converter.
2. Plug in the connection terminal of the 12V power supply and connect to mains power.

You should hear the bill acceptor and coin acceptors turn on.

### Step 2: Configure LNBits

To configure your LNBits instance to pull funds from:

1. Login to your instance of LNBits.
2. Create a wallet.
3. Go to manage extensions and find LNURLDevice and enable.
4. Open the LNURLDevice extension, click "New LNURLDevice Instance" and give it a title of ATM and choose the respect wallet for the ATM. Select the correct currency (e.g. GBP), "ATM" and a percentage for the commission.
5. Copy the link it gives you.

### Step 3: Programming the WT32-SC01

The ATM is configured in two parts, the ATM itself, and LNBits running on a separate node.

To setup your Arduino IDE:

1. If you have not already done so, install the Arduino IDE from [https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software).
2. Install the ESP32 libraries. You can do this by copying the stable release version link, currently `https://espressif.github.io/arduino-esp32/package_esp32_index.json` and putting in the `File` > `Preferences...` > `Additional Board Manager URLs` (see: [https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html))
3. Install the boards by going to `Tools` > `Board` > `Board Manager...` and searching for ESP32 and clicking Install.
4. Copy the libraries from this projects <a href="/libraries">libraries</a> folder, to your `"/Arduino/libraries"` folder (usually in OS `"Home"` directory)
5. Clone the repo, and open accessPointFOSSA.
6. Select the relevant port and ESP32 dev module.
7. Go to `Sketch` > `Upload`.
8. Once uploaded, if you press the screen on the WT32-SC01 device it will launch the access portal.

To configure the ATM:

1. Connect the access portal wi-fi (`Device-fa7ce5a4` for example).
2. Open the access portal.
2. Enter a new password.
3. Enter the coin denomitions (if you are using a coin acceptor, separated by a comma)
4. Enter the max. withdrawl in fiat (e.g. "30" for 30 GBP).
5. Enter a percentage charge for the service (e.g. "10" for 10%).
6. Click `Save`.
7. Once it has saved, unplug and plug the WT32-SC01 back in again. You should see the `Fiat for Sats` screen.

### Step 4: Enclosure

> Please note, that this ATM is designed to be attended (such as on a shop counter) rather than something that can be left unattended and mounted to a wall.

#### Option A: 3D printed enclosure

If you want to want to print your own enclosure, we recommend these settings:

1. Print the Facia
    - STL: [FOSSA ATM Facia](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Facia.stl)
    - Material: PETG
    - Infill: 10-100%
    - Supports: No
3. Print the backbox
    - STL: [FOSSA ATM Backbox](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Back%20Box.stl)  
    - Material: PETG  
    - Infill: 10-100%  
    - Supports: Yes (you "paint" out all but the door in Prusa slicer)  
4. Use a soldering iron to melt the brass female embedded insert nuts into the 6 holes for the facia (see picture 1 below)
5. OPTIONAL: If using the coin acceptor, replace the coach bolts with longer bolts (M4 x 30mm carriage/coach bolts) to account for the thickness of the facia.
6. Mount the bill acceptor so it is "smiling" (see picture 2) with the supplied mounting bracket and screws as pictured (see picture 3). Note, you can remove the bill input feed from the main part of the unit and then re-attach.
7. Mount the screen into the display.
8. Mount the 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector in the hole in the back left of the backbox.
9. Connect wires from the connection terminal to the 2.2mm Quick Disconnect Female Spade Connector and plug to the inside of the 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector.
10. OPTIONAL: Mount the Rubber feet (D30x22xH15) using the M5 x 16mm hex socket bolts and M5 nylon nuts (be careful not to over-tighten).
11. Using the Tamper-proof torx wrench (T20), use the screw in the M4 x 16mm pan head security torx tamper resistant bolts to secure the facia to the backbox.
12. Plugin the power supply.

<img src="https://github.com/user-attachments/assets/39873ac8-1ef9-4c2b-bcc4-506820e62112" width="200"/>
<img src="https://github.com/user-attachments/assets/61ee23e7-b92f-47cd-ab6f-13e64144af66" width="356"/>
<img src="https://github.com/user-attachments/assets/92c031d8-09a2-44ad-b408-c5d6ed206a37" width="356"/>

#### Option B: Mount in box

Use the templates provided <a href="cuttingTemplate.pdf">here</a>. print out at 100% on standard UK A4, and check the dimensions are correct after printing. Its useful if the pins on the bill acceptor and coin mech are accessible.

* For the `Aluminim Storage Box` solution, holes can be cut with a sharp knife (clearly not secure, but fine for somewhere you can keep an eye on the ATM or for demoes).

* For the `Home Safe` solution, holes can be cut with angle grinder and a very thin cutter. (If you have not used an angle grinder before, don't be scared, they're cheap, easy enought to use, and very useful. Just take your time and wear safetly equipment.)

> We use CT1 sealent/adhesive (or similar) for mounting screen, although the screen has screw points, which should prob be used for added security.

And there you have it, have fun, tag us on Twitter / Nostr with all your cool setups!

## Get in touch

> <i>Join our <a href="https://t.me/makerbits">telegram support/chat</a>.</i>
