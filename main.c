#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define BORDER_LEFT 10
#define BORDER_RIGHT 10
#define BORDER_TOP 5
#define BORDER_BOTTOM 1

struct Ball {
  int posY, posX;
  int vY, vX;
} typedef Ball;

struct Rectangle {
  int posY;
  int height;
  int score;
} typedef Rectangle;

void initialize() {
  // Inicializar la librería
  initscr();
  // Desactiva el búfer de linea, captura teclas inmediatamente sin presionar
  // Enter
  cbreak();
  // Impide que se impriman los caracteres que teclee
  noecho();
  // Habilita teclas especiales
  keypad(stdscr, TRUE);
  // Convierte getch en no bloqueante, si no hay entrada devuelve Err
  // inmediatamente
  nodelay(stdscr, TRUE);
  // Cambia la visibilidad del cursor: 0 | 1 | 2
  curs_set(0);
}

int main() {
  initialize();
  int y, x;
  getmaxyx(stdscr, y, x);
  Ball ball = {0, 0, 1, 1};
  Rectangle rectangle1 = {y / 2 - 2, 5, 0};
  Rectangle enemy = {y / 2 - 2, 5, 0};
  // Macro que almacena en las variables y & x la altura y ancho máximos de la
  // terminal

  int vyEnemy = 1;
  while (TRUE) {
    char c = getch();
    erase();
    mvaddstr(BORDER_TOP, x / 2 - 20,
             "Bienvenido a Ping Pong Sahur - 'E' para salir");
    // Marco
    mvvline(6, 10, ACS_VLINE, y - BORDER_TOP - BORDER_BOTTOM - 1);
    mvvline(6, x - 10, ACS_VLINE, y - BORDER_TOP - BORDER_BOTTOM - 1);
    mvhline(6, 10, ACS_HLINE, x - 20 + 1);
    mvhline(y - BORDER_BOTTOM, 10, ACS_HLINE, x - 20 + 1);

    // Players
    mvvline(rectangle1.posY, 20, ACS_VLINE, rectangle1.height);
    mvvline(enemy.posY, x - 20, ACS_VLINE, enemy.height);

    // Ball
    mvaddch(ball.posY, ball.posX, ACS_BLOCK);

    if (c == 'e' || c == 'E')
      break;
    if ((c == 'w' || c == 'W') && rectangle1.posY > BORDER_TOP + 2)
      rectangle1.posY--;
    if ((c == 's' || c == 'S') &&
        rectangle1.posY < y - rectangle1.height - BORDER_BOTTOM)
      rectangle1.posY++;

    if (enemy.posY >= y - enemy.height - BORDER_BOTTOM)
      vyEnemy = -1;
    if (enemy.posY <= BORDER_TOP + 2)
      vyEnemy = 1;

    enemy.posY += vyEnemy;
    refresh();
    napms(30);
  }
  // Obtiene el caracter
  curs_set(1);
  return 0;
}
