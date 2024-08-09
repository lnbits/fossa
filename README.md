![image](https://github.com/user-attachments/assets/a38bac69-6a07-4f44-831e-a95966f420ba)

Welcome to the FOSSA project! FOSSA is an innovative, open-source Bitcoin Lightning ATM designed to be cost-effective and easy to build. Utilizing standard components such as an ESP32 microcontroller, a multi-coin acceptor, and a bill acceptor, FOSSA allows anyone to convert loose fiat change into Bitcoin efficiently. The project includes comprehensive instructions and resources, making it accessible for hobbyists and developers to create a fully functional Bitcoin ATM. Dive in and get started building your own FOSSA!

## Demo

https://twitter.com/arcbtc/status/1567639231333277697

## Bill of Materials

The parts for this ATM should be approximately £200-£250!

You can run the FOSSA as a coin machine, a bill acceptor, or both.

### Primary FOSSA components

| Part                                         | Description                                                                                                                                                                         | Buy (UK)                                                                                                                  | Estimated cost |
| -------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------- | -------------- |
| ESP32 WT32-SC01                              | This is the ESP32 touchscreen. You don't need any Wi-Fi. It should be supplied with a USB-C to USB cable. Note that the ESP32 WT32-SC01 is different from the ESP32 WT32-SC01 PLUS! | Ebay or [AliExpress](https://www.aliexpress.com/item/1005003191471709.html)                                               | **£45**        |
| Option: NV10USB+ bill acceptor               | The bill acceptor option to accept cash notes. To accept GBP, you should request that it be set to GBP and SIO mode when purchasing.                                                | [Ebay (second hand)](https://www.ebay.co.uk/itm/263398460026)                                                             | **£70-£150**   |
| Option: DG600F(S) Multi Coin Acceptor        | The coin acceptor option. The "S" denotes the front panel (stainless steel sheet version, where we can 3D print a black panel for it).                                              | [AliExpress](<https://www.aliexpress.com/w/wholesale-DG600F(S)-Multi-Coin-Acceptor.html?spm=a2g0o.home.search.0>) or eBay | **£30**        |
| Screw terminal block                         | Easily connect the wires without soldering.                                                                                                                                         | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B08LNWMMHQ)                                                             | **£1**         |
| 12v power supply                             | Best to get one with terminal block adapter (12v battery also works well, for unplugged version).                                                                                   | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MTBTXDJ/)                                                            | **£8**         |
| 12v to 5v step down converter with USB       | 12V to 5V: The adapter converter module can convert unstable voltage DC 12V to stable DC 5V / 15W 3A output.                                                                        | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B07QQ587K3)                                                             | **£5**         |
| Male-to-female GPIO jumpers                  | Plug and play GPIO connectors                                                                                                                                                       | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MJZDXBB)                                                             | **£5**         |
| Option: Aluminum "medicine box"              | Cheap medicine box for the cash machine                                                                                                                                             | Amazon (UK)                                                                                                               | **£30**        |
| Option: Amazon Basic Home Safe               | More secure box                                                                                                                                                                     | Amazon (UK)                                                                                                               | **£70**        |
| Option: 58mm 701 USB Thermal Receipt Printer | Print receipts for users. **NB The 3D printed enclosure does not currently fit this**.                                                                                              | [Ebay (UK)](https://www.ebay.co.uk/itm/293668439213)                                                                      | **£25**        |

![image](https://github.com/user-attachments/assets/35098b91-8d00-4885-bc16-ace9bb804597)

### 3D printed enclosure fixtures & fittings

For the 3D-printed version, you will need:

| Part                                                            | Description                                                                                                                                                                                                                                          | Buy (UK)                                                                                           |
| --------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| M4 x 16mm pan head security torx tamper-resistant bolts         | These hold the front facia to the back box. Anything longer than 14mm - 55mm is fine.                                                                                                                                                                | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B0BTTRPBQV/)                                     |
| Tamper-proof torx wrench (T20)                                  | To tighten the front facia Torx bolts.                                                                                                                                                                                                               | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B0D53LNNRW)                                      |
| Brass insert nuts, M4 x 6mm L x 6mm OD                          | Female threaded heat set knurled embedded insert nuts for 3D printing. These are stronger than trying to create threads in the 3D print. Using a soldering iron, these are heated up and pushed into the backbox for better attachment of the facia. | [Amazon (UK)](https://www.amazon.co.uk/gp/product/B09MCVW4GQ/)                                     |
| M4 x 30mm carriage/coach bolts                                  | These are to replace the bolts supplied with the coin acceptor to accommodate the thickness of the facia.                                                                                                                                            | [eBay (UK)](https://www.ebay.co.uk/itm/386550912089?var=653926055961)                              |
| 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector | This allows the 12V adaptor to plug into the ATM's outside. The box assumes a diameter of 7.7mm (like these).                                                                                                                                        | [Amazon (UK)](https://www.amazon.co.uk/dp/B01N3679B8)                                              |
| 2.2mm Quick Disconnect Female Spade Connector                   | This allows us to crimp a cable and connect to the 5.5mm x 2.1mm DC Power Jack Socket                                                                                                                                                                |                                                                                                    |
| Cabinet draw tubular 16mm lock                                  | This will be mounted on the door.                                                                                                                                                                                                                    | [Amazon (UK)](https://www.amazon.co.uk/Litensh-Tubular-Cylinder-Cupboard-Letterbox/dp/B09SHWXWXC/) |
| Optional: Rubber feet (D30x22xH15)                              | If you want to have this one on the table, some rubber feet will go at the bottom of the backbox with an M5 bolt. You can also use adhesive versions. Grooves in the bottom of the box will support up to 30mm in diameter.                          | [Amazon (UK)](https://www.amazon.co.uk/dp/B0CQ23M5Z5)                                              |
| Optional: M5 x 16mm hex socket bolts                            | To screw the rubber feet into the back box.                                                                                                                                                                                                          | [Amazon (UK)](https://www.amazon.co.uk/16mm-Socket-Button-Head-Screws/dp/B09BG8XNM7)               |
| Optional: M5 nylon nuts                                         | To screw the rubber feet into the backbox.                                                                                                                                                                                                           | [Amazon (UK)](https://www.amazon.co.uk/Bolt-Base-Stainless-Insert-Nylock)                          |
| Optional: Adhesive security plate and locking cable             | Secure the ATM when desk mounted.                                                                                                                                                                                                                    | [Amazon (UK)](https://www.amazon.co.uk/I3C-Security-Anti-Theft-Hardware-Smartphone/dp/B07FM93JL6)  |

## Build

A video tutorial is available here on how to construct the FOSSA:

[https://www.youtube.com/watch?v=vbyYb9Yiu_k](https://www.youtube.com/watch?v=vbyYb9Yiu_k)

### Step 1: Hardware Setup

> **STAY TUNED FOR A WIRING HARNESS TO MAKE THIS PLUG-AND-PLAY, AND YOU CAN SKIP TO STEP 2.**

This method requires no soldering. We do this by using GPIO jumpers and terminal blocks. First, split a terminal block into a block of 3 (our LIVE terminal) and a block of 4 (our GROUND terminal).

The wiring reference is as follows:

![image](https://github.com/user-attachments/assets/3bea19e4-7fa1-449f-b15d-e87d2377bd6c)

**To connect the bill acceptor**:

1. Connect the Rx (GPIO 32) and Tx (GPIO 33), pins 29 and 31, on the WT32-SC01 board to pins 1 and 5, respectively, on the bill acceptor.
2. Using a GPIO jumper, connect the live wire (pin 15) to the first LIVE terminal block at an available terminal.
3. Using a GPIO jumper, connect the ground wire (pin 16) to a second GROUND terminal block of block at an available terminal.
4. Connect the positive wire (red) of the 12V to 5V power converter and connect it to the LIVE terminal block at an available terminal.
5. Connect the negative wire (black) of the 12V to 5V power converter and connect it to the GROUND terminal block at an available terminal.
6. Connect the ground pin (e.g. pin 5) of the WT32-SC01 and connect it to the 2nd terminal of the GROUND terminal block at an available terminal.

| NV10USB+ Pin | WT32-SC01 Pin No. (Not GPIO No.) | Power Supply |
| ------------ | -------------------------------- | ------------ |
| 1 (Tx)       | 31                               | N/A          |
| 5 (Rx)       | 29                               | N/A          |
| 15 (12V DC+) | N/A                              | 12V DC+      |
| 16 (GND)     | 5                                | GND          |

> The bill acceptor needs to be programmed to your currency and set to `SIO` mode. Usually, you can buy them preconfigured. If you have to program, buy <a href="https://www.innovative-technology.com/shop/cables/nv9-nv10-usb-host-cable-detail">this wire</a> and download the Validator Manager software <a href="https://www.dropbox.com/sh/2mle0czl2j2w7yq/AABie6AJQTq-tXmBv1TUhBUGa?dl=0">here</a> or <a href="http://www.innovative-technology.com/support/secure-download">here</a> (sadly only runs on windows, so use a friends machine). Details on programming can be found <a href="https://github.com/arcbtc/fossa/blob/main/NV10Manual_2.PDF.pdf">here</a>. It's relatively straightforward to program the acceptor: plug in the USB host cable, turn it on by holding the config button for 2 seconds, and open the Validator Manager software. If you prefer to build your own programming cable, see page 42 of the <a href="NV10 operations manual.pdf">NV10 USB Operations Manual</a>, which gives a wiring diagram for the NV10 USB host cable. You can ignore all the hardware requirements for programming in the guide; you just need the host cable! Don't try using the programming cards in the guide; that's an old system these machines no longer support - "Many Bothans died to bring us this information"!

**To connect the coin acceptor**:

> NB You can usually order the coin acceptor pre-programmed to your currencies. Otherwise, you will need to train the acceptor using <a href="https://www.youtube.com/watch?v=Dyun1xjKqc4">this guide</a>.

1. Set the 3rd dip switch to high (this sends integers to the WT32-SC01 rather than pulses).
2. Using a GPIO jumper, connect the interrupt pin (pin 5) on the coin accepter to the 5V pin (pin 2) on the WT32-SC01.
3. Using a GPIO jumper, connect the serial out (pin 2) on the coin accepter to pin 4 on the WT32-SC01.
4. Using a GPIO jumper, connect the live pin (pin 1) to the LIVE terminal block at an available terminal.
5. Using a GPIO jumper, connect the GND pin (pin 3) on the coin accepter to the GROUND terminal block at an available terminal.

| DG600F(S) Pin  | WT32-SC01 Pin No. (Not GPIO No.) | Power Supply |
| -------------- | -------------------------------- | ------------ |
| 5              | 2                                | N/A          |
| 4              | N/A                              | N/A          |
| 3 (GND)        | N/A                              | GROUND       |
| 2 (serial out) | 4                                | N/A          |
| 1 (12V)        | N/A                              | LIVE         |

**To connect the 12V power supply**:

1. Connect a GPIO jumper to the live connection (+) on the 12V power supply terminal block adapter to the LIVE terminal block at an available terminal.
2. Connect a GPIO jumper to the ground connection (-) on the 12V power supply terminal block adapter to the GROUND terminal block at an available terminal.

**To complete the terminal blocks**:

1. Connect each terminal in the LIVE terminal block so they all receive power by looping over wires from terminals 1 to 2 and 1 to 3.
2. Connect each terminal in the GROUND terminal block so they all receive power by looping over wires from terminals 1 to 2, 1 to 3 and 1 to 4.

**To connect to power**:

1. Plug in the WT32-SC01 to the USB connector of the 12V to 5V power converter.
2. Plug in the connection terminal of the 12V power supply and connect to mains power.

You should hear the bill acceptor and coin acceptors turn on.

### Step 2: Configure LNBits

To configure your LNBits instance to pull funds from:

1. Login to your instance of LNBits.
2. Create a wallet.
3. Go to `Manage Extensions`, find `LNURLDevice`, and install/enable it.
4. Open the `LNURLDevice` extension, click `New LNURLDevice Instance`, give it the title of `ATM`, and choose the appropriate wallet for the ATM. Select the correct currency (e.g., `GBP`), `ATM` mode, and a percentage for the commission.
5. Copy the link it gives you.

### Step 3: Programming the WT32-SC01

The ATM is configured in two parts: the ATM and LNBits running on a separate node.

To set up your Arduino IDE:

1. If you have not already done so, install the Arduino IDE from [https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software).
2. Install the ESP32 libraries. You can do this by copying the stable release version link, currently `https://espressif.github.io/arduino-esp32/package_esp32_index.json` and putting in the `File` > `Preferences...` > `Additional Board Manager URLs` (see: [https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html))
3. Install the boards by going to `Tools` > `Board` > `Board Manager...`, searching for ESP32, and clicking Install.
4. Copy the libraries from this project <a href="/libraries">libraries</a> folder to your `"/Arduino/libraries"` folder (usually in OS `"Home"` directory)
5. Clone the repo and open accessPointFOSSA.
6. Select the relevant port and ESP32 dev module (from `Tools` > `Port` and selecting the relevant COM port).
7. Go to `Sketch` > `Upload`.
8. Once uploaded, the access portal will launch when you press the screen on the WT32-SC01 device.

To configure the ATM:

1. Connect the access portal wi-fi (`Device-fa7ce5a4`, for example).
2. Open the access portal.
3. Enter a new password.
4. Enter the coin denominations (if you are using a coin acceptor, separated by a comma)
5. Enter the maximum withdrawal amount in fiat (e.g. `30` for 30 GBP).
6. Enter a percentage charge for the service (e.g. `10` for 10%, which should be the same value you entered into LNBits).
7. Click `Save`.
8. unplug and plug the WT32-SC01 back in once saved. You should see the `Fiat for Sats` screen.

### Step 4: Enclosure

> It should be pointed out that this ATM is designed to be attended to (such as on a shop counter) rather than something that can be left unattended and mounted to a wall.

#### Option A: 3D printed enclosure

If you want to want to print your own enclosure, we recommend these settings:

1. Print the Facia
   - STL: [FOSSA ATM Facia](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Facia.stl)
   - Material: PETG
   - Layer: 0.2mm
   - Infill: 10-100% (recommend 20%+)
   - Supports: Yes
   - Notes: To set the Bitcoin logo with a different color, set a color change at layer 114 (13.20mm). In PrucaSlicer, you can "paint" out all the screw holes as they do not need supports. I would also recommend setting a thicker layer parameter, in PrucaSlicer, you can do this by settings `Printer Settings` > `Layers and perimeters` > `Perimeters` to `4`)
2. Print the backbox
   - STL: [FOSSA ATM Backbox](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Back%20Box.stl)
   - Material: PETG
   - Layer: 0.2mm
   - Infill: 10-100% (recommend 20%+)
   - Supports: Yes
   - Notes: In PrusaSlicer you can set `Print Settings` > `Support material` > `First layer expansion` to `1 mm`, `XY separation between an object and its support` to `80%` and `Overhang threshold` to `1 mm`, or, you can "paint" out all but the door as the model has been designed for minimal supports
3. Print the accessories
   - STL: [FOSSA ATM WT-32-SC01 Backplate](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20WT-32-SC01%20Backplate.stl), [FOSSA ATM Coin Slot Cover](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Coin%20Slot%20Cover.stl), [FOSSA ATM 4mm Lock Lever Shim](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%204mm%20Lock%20Lever%20Shim.stl), [FOSSA ATM Door](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%204mm%20Door.stl), [FOSSA ATM Backbox Note Holder](https://github.com/lnbits/fossa/blob/main/3DPrints/FOSSA%20ATM%20Backbox%20Note%20Holder.stl)
   - Material: PETG
   - Layer: 0.2mm
   - Infill: 10-100% (recommend 20%+)
   - Supports: No
4. Use a soldering iron to melt the brass female embedded insert nuts into the six holes for the facia (see picture 1 below)
5. OPTIONAL: If using the coin acceptor, replace the coach bolts with longer bolts (M4 x 30mm carriage/coach bolts) to account for the thickness of the facia.
6. Mount the bill acceptor so it is "smiling" (see picture 2) with the supplied mounting bracket and screws as pictured (see picture 3). You can remove the bill input feed from the main part of the unit and then re-attach it.
7. Mount the screen to the WT-32-SC01 Backplate.
8. Mount the backplate to the Facia with the M4 (4mm x 8mm Inc Head) hex socket countersunk screws.
9. Mount the backbox note holder to the backbox with the M4 (4mm x 8mm Inc Head) hex socket countersunk screws.
10. Mount the 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector in the hole in the back left of the backbox (this directs the notes to the bottom of the box.
11. Connect wires from the connection terminal to the 2.2mm Quick Disconnect Female Spade Connector and plug into the inside of the 5.5mm x 2.1mm DC Power Jack Socket Female Panel Mount Connector.
12. OPTIONAL: Mount the Rubber feet (D30x22xH15) using the M5 x 16mm hex socket bolts and M5 nylon nuts (be careful not to over-tighten).
13. Using the Tamper-proof torx wrench (T20), use the screw in the M4 x 16mm pan head security torx tamper-resistant bolts to secure the facia to the backbox.
14. Plug the power supply in.

<img src="https://github.com/user-attachments/assets/39873ac8-1ef9-4c2b-bcc4-506820e62112" width="150"/>
<img src="https://github.com/user-attachments/assets/61ee23e7-b92f-47cd-ab6f-13e64144af66" width="267"/>
<img src="https://github.com/user-attachments/assets/92c031d8-09a2-44ad-b408-c5d6ed206a37" width="267"/>

#### Option B: Mount in a box

Use the templates provided <a href="cuttingTemplate.pdf">here</a>, print out at 100% on standard UK A4, and check the dimensions are correct after printing. It's helpful if the bill acceptor and coin mech pins are accessible.

- For the `Aluminium Storage Box` solution, holes can be cut with a sharp knife (clearly not secure - but acceptable for somewhere you can keep an eye on the ATM or for demos).

- For the `Home Safe` solution, holes can be cut with an angle grinder and a very thin cutter. (If you have not used an angle grinder before, don't be scared; they're cheap, easy enough to use, and very useful. Take your time and wear safety equipment.)

> We use CT1 sealant/adhesive (or similar) for mounting the screen, although the screen has screw points, which should prob be used for added security.

## Get in touch

And there you have it. Have fun, and tag us on Twitter / Nostr with all your cool setups!

> <i>Join our <a href="https://t.me/makerbits">telegram support/chat</a>.</i>
