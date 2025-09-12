export const addressesAndFiles = [
  {
    address: "0x1000",
    fileName: "fossa.ino.bootloader.bin",
  },
  {
    address: "0x8000",
    fileName: "fossa.ino.partitions.bin",
  },
  {
    address: "0xE000",
    fileName: "boot_app0.bin",
  },
  {
    address: "0x10000",
    fileName: "fossa.ino.bin",
  },
];

export const configPath = "elements.json";
export const elements = [
  {
    name: "config_lnurl",
    value: "",
    label: "ATM string from LNURLDevices extension",
    type: "text",
  },
  {
    name: "config_bill_ints",
    value: "",
    label: "Bill denominations seperated by comma ie: 1,5,10,20,50,100",
    type: "text",
  },
  {
    name: "config_coin_floats",
    value: "",
    label: "Coin floats seperated by comma ie: 0.05,0.1,0.2,0.5,1,2 - no more than 6",
    type: "text",
  },
  {
    name: "config_charge",
    value: "20",
    label: "Percentage you will charge for the service ie 10 for 10 percent",
    type: "text",
  },
  {
    name: "config_max_amount",
    value: "40",
    label: "Max amount allowed to be withdrawn in one transaction",
    type: "text",
  },
  {
    name: "config_max_amount_reset",
    value: "500",
    label: "Max amout before the atm stops withdrawals and wait to be emptied",
    type: "text",
  },
  {
    name: "config_printer",
    value: "false",
    label: "Set true if you have a thermal printer connected",
    type: "text",
  },
  {
    name: "config_lang",
    value: "en",
    label: "2 letter language code. Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv, nl",
    type: "text",
  }
];
