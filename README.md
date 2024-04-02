# sm_layouts
Custom QMK Library for international layouts.

This library is designed to provide support for international layouts in QMK. 
Currently Cyrillic ЙЦУКЕН with Mac and PC layouts are supported only, but feel free to ask for another layouts or implement yours in MRs. 

This library supports the following features:
- Cyrillic ЙЦУКЕН keycodes (both WIN and MAC symbol layouts), typing them is based on standard unicode mechanisms in QMK
- Every keycode is independent from input sources in your OS and other layouts. In other words, you may use DVORAK for English layer (and shortcuts) and ЙЦУКЕН (or any other configuration) for Russian layer.
- Shift support. E.g. tapping `CYR_YA` will produce 0x044F unicode symbol (which is `я`), tapping `shift + CYR_YA` will produce 0x042F (which is `Я`)
- Other modifiers support for shortcuts. E.g. tapping `ctrl + alt + CYR_YA` will find a keycode in underlying layer and will send it to system (e.g. with ЙЦУКЕН + QWERTY layouts that would be interpreted as `ctrl + alt + z`)
- One-shot mods support, both shifts and other modifiers
- Weak mods support, both shifts and other modifiers
- Caps word support
- Combo support
- Easy installation and usage (can't make it easier than that)
- NO LT() and MT() support. That's kinda tricky to implement. If you need it, please leave your vote in corresponding issue on github
- Ask for your features and layout support in issues on github


## Installation
1. Enable unicode support in your QMK firmware. Usually you need to add `UNICODE_ENABLE = yes` to your `rules.mk` file. See [QMK Unicode Official Documentation](https://docs.qmk.fm/#/feature_unicode) for more information.


2. Clone `sm_layouts.h` and `sm_layouts_keycodes.h` into your QMK keymap directory (next to your keymap.c file)


3. Edit your `config.h`

   3.1. Enable desired layouts (see "List of available layouts and keycodes" below). You can enable several layouts, for example: 
   ```c
   #define SM_LAYOUTS_CYR_ENABLED
   #define SM_LAYOUTS_CYR_WIN_SYMBOLS_ENABLED
   ```

   3.2. (Optional) Specify shortcut layer. By default, it's `0` (base layer). You can change it by adding `#define SM_LAYOUTS_SHORTCUT_LAYER 5` (5 — your desired shortcut layer index) to your `config.h` file.


4. Edit your `keymap.c` 

   4.1. Add `#include "sm_layouts_keycodes.h"` and `#include "sm_layouts.h"` at the top. It's important to include `sm_layouts_keycodes.h` first.

   4.2. Add `if (!process_sm_layouts(keycode, record)) return false;` in the beginning of your `process_record_user` function. It should look like this:
   ```c
   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (!process_sm_layouts(keycode, record)) return false;
   
     // Rest of your code here
     return true;
   }
   ```
   
   4.3. Add `SM_LAYOUTS_KEYCODES` to your keymap's `enum custom_keycodes` list. It should look like this:
   ```c
   enum custom_keycodes {
     YOUR_CODE_1 = SAFE_RANGE,
     YOUR_CODE_2,
     // Rest of your custom keycodes here
   
     SM_LAYOUTS_KEYCODES,
   };
   ```
   If you didn't have added any custom keycodes before, you need to create one with explicit beginning. It should look like this:
   ```c
   enum custom_keycodes {
     CUSTOM_KEYCODES_BEGIN = SAFE_RANGE,
     SM_LAYOUTS_KEYCODES,
   };
   ```
   Please note that you can put `SM_LAYOUTS_KEYCODES` anywhere except the beginning of the enum. It's important to explicitly define the beginning of your custom keycodes range with `SAFE_RANGE`.

   4.4 Once you have `SM_LAYOUTS_KEYCODES` in your `enum custom_keycodes`, you can add extra keycodes to your keymap `PROGMEM keymaps`.
   List of available keycodes depends options you have enabled in config.h.
   See "List of available layouts and keycodes" below for more information.
   Also check "Copy-paste keymaps", there are typical keyboard layouts, so you can just copy and paste them.

## List of available layouts and keycodes
### Cyrillic ЙЦУКЕН 

To enable this keycodes add `#define SM_LAYOUTS_CYR_ENABLED` to your `config.h` file.
This will give you the following keycodes:
- `CYR_A` — `а` or `А` (shifted) 
- `CYR_B` — `б` or `Б` (shifted) 
- `CYR_V` — `в` or `В` (shifted) 
- `CYR_G` — `г` or `Г` (shifted) 
- `CYR_D` — `д` or `Д` (shifted) 
- `CYR_E` — `е` or `Е` (shifted) 
- `CYR_YO` — `ё` or `Ё` (shifted) 
- `CYR_ZH` — `ж` or `Ж` (shifted) 
- `CYR_ZZ` — `з` or `З` (shifted) 
- `CYR_I` — `и` or `И` (shifted) 
- `CYR_YY` — `й` or `Й` (shifted) 
- `CYR_K` — `к` or `К` (shifted) 
- `CYR_L` — `л` or `Л` (shifted) 
- `CYR_M` — `м` or `М` (shifted) 
- `CYR_N` — `н` or `Н` (shifted) 
- `CYR_O` — `о` or `О` (shifted) 
- `CYR_P` — `п` or `П` (shifted) 
- `CYR_R` — `р` or `Р` (shifted) 
- `CYR_SS` — `с` or `С` (shifted) 
- `CYR_T` — `т` or `Т` (shifted) 
- `CYR_U` — `у` or `У` (shifted) 
- `CYR_F` — `ф` or `Ф` (shifted) 
- `CYR_H` — `х` or `Х` (shifted) 
- `CYR_CC` — `ц` or `Ц` (shifted) 
- `CYR_CH` — `ч` or `Ч` (shifted) 
- `CYR_SH` — `ш` or `Ш` (shifted) 
- `CYR_SCH` — `щ` or `Щ` (shifted) 
- `CYR_SLD` — `ъ` or `Ъ` (shifted) 
- `CYR_YI` — `ы` or `Ы` (shifted) 
- `CYR_SFT` — `ь` or `Ь` (shifted) 
- `CYR_YE` — `э` or `Э` (shifted) 
- `CYR_YU` — `ю` or `Ю` (shifted) 
- `CYR_YA` — `я` or `Я` (shifted)


### Windows symbols for Cyrillic ЙЦУКЕН

To enable this keycodes add `#define SM_LAYOUTS_CYR_WIN_SYMBOLS_ENABLED` to your `config.h` file.
This will give you the following keycodes:
- `CYR_W1` — `1` or `!` (shifted)
- `CYR_W2` — `2` or `"` (shifted)
- `CYR_W3` — `3` or `№` (shifted)
- `CYR_W4` — `4` or `;` (shifted)
- `CYR_W5` — `5` or `%` (shifted)
- `CYR_W6` — `6` or `:` (shifted)
- `CYR_W7` — `7` or `?` (shifted)
- `CYR_W8` — `8` or `*` (shifted)
- `CYR_W9` — `9` or `(` (shifted)
- `CYR_W0` — `0` or `)` (shifted)
- `CYR_WDOT` — `.` or `,` (shifted)
- `CYR_WSLASH` — `\` or `/` (shifted)


### Mac symbols for Cyrillic ЙЦУКЕН

To enable this keycodes add `#define SM_LAYOUTS_CYR_MAC_SYMBOLS_ENABLED` to your `config.h` file.
This will give you the following keycodes:
- `CYR_M1` — `1` or `!` (shifted)
- `CYR_M2` — `2` or `"` (shifted)
- `CYR_M3` — `3` or `№` (shifted)
- `CYR_M4` — `4` or `%` (shifted)
- `CYR_M5` — `5` or `:` (shifted)
- `CYR_M6` — `6` or `,` (shifted)
- `CYR_M7` — `7` or `.` (shifted)
- `CYR_M8` — `8` or `;` (shifted)
- `CYR_M9` — `9` or `(` (shifted)
- `CYR_M0` — `0` or `)` (shifted)
- `CYR_MSLASH` — `/` or `?` (shifted)
- `CYR_MBRC` — `[` or `]` (shifted)


## Copy-paste keymaps
### ANSI 60% keyboard with Cyrillic ЙЦУКЕН for Win
```c
CYR_YO,    CYR_W1,    CYR_W2,    CYR_W3,    CYR_W4,    CYR_W5,    CYR_W6,    CYR_W7,    CYR_W8,    CYR_W9,    CYR_W0,    KC_MINS,    KC_EQL,    KC_BSPC,
KC_TAB,       CYR_YY,    CYR_CC,    CYR_U,     CYR_K,     CYR_E,     CYR_N,     CYR_G,     CYR_SH,    CYR_SCH,   CYR_ZZ,   CYR_H,      CYR_SLD, CYR_WSLASH,   
KC_CAPS_LOCK,    CYR_F,    CYR_YI,     CYR_V,     CYR_A,     CYR_P,     CYR_R,     CYR_O,     CYR_L,     CYR_D,    CYR_ZH,    CYR_YE,           KC_ENTER,
KC_LSFT,            CYR_YA,   CYR_CH,     CYR_SS,    CYR_M,     CYR_I,     CYR_T,     CYR_SFT,   CYR_B,     CYR_YU,   CYR_WDOT,                 KC_RSFT,
```


### ANSI 60% keyboard with Cyrillic ЙЦУКЕН for Mac
```c
CYR_MBRC,   CYR_M1,    CYR_M2,    CYR_M3,    CYR_M4,    CYR_M5,    CYR_M6,    CYR_M7,    CYR_M8,    CYR_M9,    CYR_M0,    KC_MINS,    KC_EQL,    KC_BSPC,
KC_TAB,        CYR_YY,    CYR_CC,    CYR_U,     CYR_K,     CYR_E,     CYR_N,     CYR_G,     CYR_SH,    CYR_SCH,   CYR_ZZ,   CYR_H,      CYR_SLD, CYR_YO,   
KC_CAPS_LOCK,     CYR_F,    CYR_YI,     CYR_V,     CYR_A,     CYR_P,     CYR_R,     CYR_O,     CYR_L,     CYR_D,     CYR_ZH,   CYR_YE,           KC_ENTER,
KC_LSFT,             CYR_YA,   CYR_CH,     CYR_SS,    CYR_M,     CYR_I,     CYR_T,     CYR_SFT,   CYR_B,     CYR_YU,    CYR_MSLASH,              KC_RSFT,
```

### Split 3x6 keyboard with Cyrillic ЙЦУКЕН (with Win dot only)
```c
CYR_YO,    CYR_YY,   CYR_CC,    CYR_U,    CYR_K,    CYR_E,         CYR_N,    CYR_G,   CYR_SH,  CYR_SCH,   CYR_ZZ,    CYR_H, 
XXXXXXX,    CYR_F,   CYR_YI,    CYR_V,    CYR_A,    CYR_P,         CYR_R,    CYR_O,    CYR_L,    CYR_D,   CYR_ZH,   CYR_YE, 
XXXXXXX,   CYR_YA,   CYR_CH,   CYR_SS,    CYR_M,    CYR_I,         CYR_T,  CYR_SFT,    CYR_B,   CYR_YU, CYR_WDOT,  CYR_SLD, 
```
Please note that CYR_SLD and CYR_YO don't have a free key in 3x6, so I moved them a bit. You can change it to your needs.


## Advices for better experience

### Update macOS behavior with unicode   
Normally QMK sends `R_OPT + unicode` for macOS. It's not very convenient due to many applications have `R_OPT + Number` or `R_OPT + A/B/C/D/E/F` shortcuts.
MacOS also accepts unicode symbols with `R_OPT + R_SHIFT + unicode` combination.
To make it work you will need to patch `unicode.c` or `process_unicode.c` (depends on firmware version) file in QMK yourself.
1. Open `quantum/process_keycode/process_unicode.c` and `quantum/unicode/unicode.c` (if you have it in your QMK directory).
2. Replace `register_code(UNICODE_KEY_MAC);` with 
   ```c
   register_code(KC_LEFT_ALT);
   register_code(KC_LEFT_SHIFT);
   ```
3. Replace every `unregister_code(UNICODE_KEY_MAC);` with 
   ```c
   unregister_code(KC_LEFT_SHIFT);
   unregister_code(KC_LEFT_ALT);
    ```
4. Rebuild your firmware and flash it to your keyboard.


### Update chrome shortcuts
Go to page `chrome://extensions/shortcuts` and update shortcuts for your extensions. 
There is an option `Focus on inactive dialogs` that uses `ALT + SHIFT + A` shortcut. You'd better change it to another one.
Otherwise, you will have a conflict with `R_ALT + R_SHIFT + A` unicode combination.

### Update other applications shortcuts
Please check your applications shortcuts and update them if needed.
In my cases I had to review shortcuts for JetBrains IDEs, iTerm2, and VSCode.
 