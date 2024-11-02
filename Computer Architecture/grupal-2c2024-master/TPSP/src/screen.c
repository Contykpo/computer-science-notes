/* ** por compatibilidad se omiten tildes **
==============================================================================
TALLER System Programming - Arquitectura y Organizacion de Computadoras - FCEN
==============================================================================

  Definicion de funciones de impresion por pantalla.
*/

#include "screen.h"
#include "defines.h"
#include "colors.h"

uint8_t nada;

uint8_t foregroundCharacterColor      = C_FG_WHITE;
uint8_t foregroundNameCharacterColor  = C_FG_RED;

uint8_t clamp_color_with_wrap_around(uint8_t color)
{
  return color % 16;
}

void print(const char* text, uint32_t x, uint32_t y, uint16_t attr) {
  ca(*p)[VIDEO_COLS] = (ca(*)[VIDEO_COLS])VIDEO; 
  int32_t i;
  for (i = 0; text[i] != 0; i++) {
    p[y][x].c = (uint8_t)text[i];
    p[y][x].a = (uint8_t)attr;
    x++;
    if (x == VIDEO_COLS) {
      x = 0;
      y++;
    }
  }
}

void print_dec(uint32_t numero, uint32_t size, uint32_t x, uint32_t y,
               uint16_t attr) {
  ca(*p)[VIDEO_COLS] = (ca(*)[VIDEO_COLS])VIDEO; 
  uint32_t i;
  uint8_t letras[16] = "0123456789";

  for (i = 0; i < size; i++) {
    uint32_t resto = numero % 10;
    numero = numero / 10;
    p[y][x + size - i - 1].c = letras[resto];
    p[y][x + size - i - 1].a = attr;
  }
}

void print_hex(uint32_t numero, int32_t size, uint32_t x, uint32_t y,
               uint16_t attr) {
  ca(*p)[VIDEO_COLS] = (ca(*)[VIDEO_COLS])VIDEO; 
  int32_t i;
  uint8_t hexa[8];
  uint8_t letras[16] = "0123456789ABCDEF";
  hexa[0] = letras[(numero & 0x0000000F) >> 0];
  hexa[1] = letras[(numero & 0x000000F0) >> 4];
  hexa[2] = letras[(numero & 0x00000F00) >> 8];
  hexa[3] = letras[(numero & 0x0000F000) >> 12];
  hexa[4] = letras[(numero & 0x000F0000) >> 16];
  hexa[5] = letras[(numero & 0x00F00000) >> 20];
  hexa[6] = letras[(numero & 0x0F000000) >> 24];
  hexa[7] = letras[(numero & 0xF0000000) >> 28];
  for (i = 0; i < size; i++) {
    p[y][x + size - i - 1].c = hexa[i];
    p[y][x + size - i - 1].a = attr;
  }
}

void screen_draw_box(uint32_t fInit, uint32_t cInit, uint32_t fSize,
                     uint32_t cSize, uint8_t character, uint8_t attr) {
  ca(*p)[VIDEO_COLS] = (ca(*)[VIDEO_COLS])VIDEO;
  uint32_t f;
  uint32_t c;
  for (f = fInit; f < fInit + fSize; f++) {
    for (c = cInit; c < cInit + cSize; c++) {
      p[f][c].c = character;
      p[f][c].a = attr;
    }
  }
}

char logo [VIDEO_FILS][VIDEO_COLS] = {
"%%%%%%%#+-:=%%%%%%%%%%%%%%%%%%%%%%%%%%#*#+***++-+%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%%%#*=:.+%%%%%%%%%%%%%%%%%%%%%%%%%********++#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%%%=-::=#%%%%%%%%%%%%%%%%%%%%%%%%#********++*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%%*=-:-#%%%%%%%%%%%%%%%%%%%%%%%%%##*******+=:*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%#*+=:=%%%%%%%%%%%%%%%%%%%%%%%%%####**++***+==%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%#*+=:=%%%%%%%%%%%%%%%%%%%%%%%%#************--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%##**+*%%%%%%%%%%%%%%%%%%%%%%%#*****++**+*+--+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%#***#*%%%%%%%%%%%%%%%%%%%%%%%#****#***+*#*-==+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%#*++*#%%%%%%%%%%%%%%%%%%%%#####***********+=-:-*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%#*+=+#%%%%%%%%%%%%%%%%#%######*******+*+=+++=--+##%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%##*++*%%%%%%%%%%%%%%##########*##**++**+++**++--=*##%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%*#*+=+%%%%%%%%%%###%##########***++++*******+======#####%%%%%%%%%%%%%%%%%%%%%%",
"%*%*=-=#%%####################**+***+****++++++++++++********##%%%%%%%%%%%%%%%%",
"%*%*-:-########################****+++++*#%%%#####%%%%%##%@@%%#%##*+*#%%%%%%%%%",
"%#+*=::+####################*#######%%@@@@%#%%@@@@@@@@@@@@@@@@@@@@%%@%%**%%%%%%",
"%%**+=-:*##########****#%%%%%%%@@%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%##%%%%",
"%%%#%#+=:=##%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%##%%%",
"%%%#%%*+=-#%@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%####%@@@@@@@@@@@@@@@@@@@@@%#%%%%",
"%%%%%%#*++*%@@@@@@@@@@@@@@@@@@@@@@@@@%%%%*+*%%%###**#%@@@@@@@@@@@@@@@@@@@#%%%%%",
"%%%%#%%#*+*%@@@@@@@@@@@@@@@@@@@@@%%@%#%%%+==+********#%%%@@@@@@@@@@@@@@%%%%%%%%",
"%%%%%%@%#++#@@@@@@@@@@@@@@@@@@@%#%%%%#**#=----====++**##%@@@@@@@@@@@%%####%%%%%",
"%%%%%%%%%*+*@@@@@@@@@@@@@@@@@@%###***+=#%#++***+---==--=*%@@@%#############%%%%",
"%%%%%%%%@%*=*#%@@@@@@@@@@@@@@@%#+*++=+#%%%@%###%%*=----+=##********#########%%%",
"%%%%%##%@%*+=####*#######%%%@@%*=++=+##########%###+-:-=:=+**********#########%",
"%%%%%###%%#+=+##*********++*%@%*=++*%%%%#+***#%#%##*=:-=-+**+++++****##########",
"%%%%#####@%#+=**********+*%@@@%++*+*%###***##%#####*+-==+##%#==++*****#########",
"%%%%##+::*%%**+********+*%@@@@@++**#%##%#%#*#####%#+===**%###*=++=+****#######%",
"%%%%##*=:=%%#++*******#%%%%%%@@#++**#%#*####%%%%#%*=+++*%%%##***++===***######%",
"%%%####+=+#%##+***#*#%%#%#%%#%@@%#*+*#%%#%*####%#*=+*##%####*******++--+*#####%",
"%%%#####+=+%%#**###%##%%%##%##%@@@%#**%@%*##%%%%#++#%%%####*******+**++++===*#%",
"%%%###*+=++#%#**###%%%#%########%%@%%%%%#@@@@%%**#%##@%##*****+**********+++++#",
"%%%#*+==**#%%#**#################**#%%%##@@###++#%#%%####**++*+++++*+++*+**+*++",
"%%%##*-+**#%%%#**###*########**##*****#%%@@@@@@@%#**#*****++***++++++*++*#*#**-",
"%%%###*+=:-*%%#*+####*#######*********++**##@%%#****++*************+**#**##**#*",
"%%%%##*=--:.=%%*+=**=:-*####*********+*++++++*+********+**+***********#*#**#***",
"%%%%%%#*#*+-::+#*=:-=*****##***************+*+++***+*++*+++++++*+*+************",
"%%%%%%##%#+*+--##*+##****#**#***+++******+********+****+***++***********##**###",
"%%%%%#**###*+===*#*+************+++*+++*+************++++++**********#####%%#%%",
"%%%%%%%%@@@@@@*-:+*=*##****************+++*******+++******************########%",
"%%%%%%%%@@@%@@%#@%#*+***###********###***#**++++*+++*******#*+*####*#####*#####",
"%%%%%%%@@@%%#%%@@@%#****##%*###***+******+*++****+**+****++*++**+***#####%%%#%%",
"%%%%%%#%@%%#**#%@@@%#*#########****+*#******+++*+***+**+************#######%%%%",
"%%%%%%+#%%#+++#%@@@@%*#####*###****+******+++*****+*++++++************#**#%%%%%",
"%%%%%++*%%#*==*%@@@%%*#%#############*#######**#**++*******##*****#**###*#%%%%@",
"@%%%#++*####===*@@@%%%%%###***####*#**#####**#********###**###*###**######%%%%@",
"@@@%#***####*==*@@@@@%%##########***###***####*+**##*#****##**#######%####%#%@@",
"@@@######%%%%*-+@@@@@@@%%%%**####%%##*##########*******##*###*##%%%###%%%%%%%@%",
"%@%#%%#%@@@@%%##%@@@%%@%########%####%##**####*****##******##*#####%%#####%%%%#"
};

uint8_t linesBeforeFirstName = 16;
uint8_t linesBeforeSecondName = 38;

void screen_draw_layout(void) {
  uint16_t characterColor     = foregroundCharacterColor | C_BG_BLACK;
  uint16_t nameCharacterColor = foregroundNameCharacterColor | C_BG_RED;

  for(uint8_t i = 0; i < linesBeforeFirstName; ++i)
  {
    print(logo[i], 0, i, characterColor);
    foregroundCharacterColor = clamp_color_with_wrap_around(foregroundCharacterColor + 1);
    characterColor = foregroundCharacterColor | C_BG_BLACK;
  }

  foregroundNameCharacterColor  = clamp_color_with_wrap_around(foregroundNameCharacterColor + linesBeforeFirstName);
  nameCharacterColor            = foregroundNameCharacterColor | C_BG_RED;

  print("%%##*+-::########%@@@@@@%%@@@@@@@@@", 0, 16, characterColor);
  print("CARLOS", 35, 16, nameCharacterColor);
  print("@", 41, 16, characterColor);
  print("IGNACIO", 42, 16, nameCharacterColor);
  print("@", 49, 16, characterColor);
  print("SCIRICA", 50, 16, nameCharacterColor);
  print("@@@@@@@@@@@@@@@%##%%%%", 57, 16, characterColor);

  foregroundCharacterColor = clamp_color_with_wrap_around(foregroundCharacterColor + 1);
  characterColor = foregroundCharacterColor | C_BG_BLACK;

  for(uint8_t i = linesBeforeFirstName + 1; i < linesBeforeSecondName; ++i)
  {
    print(logo[i], 0, i, characterColor);
    foregroundCharacterColor = clamp_color_with_wrap_around(foregroundCharacterColor + 1);
    characterColor = foregroundCharacterColor | C_BG_BLACK;
  }

  foregroundNameCharacterColor  = clamp_color_with_wrap_around(foregroundNameCharacterColor + (linesBeforeSecondName - linesBeforeFirstName - 1) );
  nameCharacterColor            = foregroundNameCharacterColor | C_BG_RED;
  
  print("%%%%%%*=+*+:...-#*+#***%####***#**+",0,38,characterColor);
  print("SAMUEL", 35, 38, nameCharacterColor);
  print("*",41,38,characterColor);
  print("FURLANICH", 42, 38, nameCharacterColor);
  print("***+******++*+**+*###+*%%###",51,38,characterColor);

  foregroundCharacterColor = clamp_color_with_wrap_around(foregroundCharacterColor + 1);
  characterColor = foregroundCharacterColor | C_BG_BLACK;

  for(uint8_t i = linesBeforeSecondName + 1; i < VIDEO_FILS; ++i)
  {
    print(logo[i], 0, i, characterColor);
    foregroundCharacterColor = clamp_color_with_wrap_around(foregroundCharacterColor + 1);
    characterColor = foregroundCharacterColor | C_BG_BLACK;
  }
}

void matame(void){
  for(uint32_t i = 0; i < 4000000; ++i)
  {
    for(uint32_t j = 0; j < 20-1; ++j)
    {
      nada *= i * j / 10 - j;
    }
  }
}