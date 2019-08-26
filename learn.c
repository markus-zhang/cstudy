#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int ch;

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  printw("Type a short sentence to see features, enter to quit: \n");

  int row = 1;
  int col = 0;
  int numchar = 0;
  char rows[3];
  char cols[3];

  while (1)
  {
    ch = getch();

    if (ch == '\n')
    {
      break;
    }
    else
    {
      numchar += 1;
      mvaddch(row, col, ch | A_BOLD | A_UNDERLINE);
      refresh();
    }

    col = (col < 20) ? col + 1 : 0;
    row = (col == 0 && numchar > 1) ? row + 1 : row;

    // maximum of 4 rows
    if (row >= 4)
    {
      // Clear every line except the first line
      move(1, 0);
      clrtoeol();
      row = 1;
    }

    sprintf(cols, "%d", col); 
    sprintf(rows, "%d", row); 
    mvprintw(55, 0, rows);  
    mvprintw(55, 3, cols);  
    refresh();
  }

  /*
  char* input = malloc(sizeof(char) * 20);
  if (!input)
  {
    printw("Failed to allocate memroy for input, shutting down...\n");
    getchar();
    return 1;
  }

  input = fgets(input, 20, stdin);

  for (int i = 0; i <= strlen(input) - 1; i += 1)
  {
    mvaddch(20, i + 1, input[i] | A_BOLD | A_UNDERLINE);
    refresh();
  }
  */

  endwin();

  return 0;

}
