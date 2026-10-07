# Car Radio 7 Buttons + 1 Encoder w/button Unit

## Code

Designed in CodevisionAVR.  

## Schematics, PCB

Device was designed for Gainta G200MF enclosure.  
You can find my project for Proteus 9 and exported pdf files in "Schematic & PCB" folder.  

If you want to use this project somehow, please add my credentials or reference as "Rinon Ninqueon".

## Features

* All buttons has adjustable resistance
* Adjustable brightness
* Learning mode (3 seconds waiting) for car radio
* Connect ILL wire to turn on the illumination along with the vehicle's headlights
* Connect ACC to turn device on only with the vehicle's ignition
* PicoBlade connectors for compact mounting

## Controls

Default mapping is 2 any buttons, "prev" button, encoder w/button, "next" button, 3 any buttons.  
Long press Encoder activates Menu mode.

| Menu  | Encoder rotate | Encoder short press | Encoder long press | Description |
| ------- | ---------- | ---- | ---- | ----------- |
| Home | As button short press | As button short press | Enter menu | Default mode from startup |
| Menu | Select submenu | Enter submenu | Exit to home | Selected menu as button will be highlighted |
| 1) Learning | As button long press | As button long press | Exit to menu | Acive button will be blinking |
| 2) Brightness | Select brightness | Exit to menu | --- | Adjusting brightness in realtime |
| 3) Buttons | Select button | Enter code menu | Exit to menu | Selected button will be blinking |
| Code | Change button code | Exit to Button select | --- | Three buttons will be blinking several times at 10 seconds, indicating three decimal digits |

