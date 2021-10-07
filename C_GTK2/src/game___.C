namespace gtk2_game
{

#include <gtk/gtk.h>
/*
#include "game.h"


// 当赢了时调用
void
win (GtkWidget *widget, gpointer data)
{
  g_print ("Yay!\n");
  tictactoe_clear (TICTACTOE (widget));
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *ttt;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW (window), "Aspect Frame");

  gtk_signal_connect (GTK_OBJECT (window), "destroy",
		      GTK_SIGNAL_FUNC (gtk_exit), NULL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  // 创建一个新的井字游戏构件
  ttt = tictactoe_new ();
  gtk_container_add (GTK_CONTAINER (window), ttt);
  gtk_widget_show (ttt);

  // 连接 "tictactoe" 信号的处理函数
  gtk_signal_connect (GTK_OBJECT (ttt), "tictactoe",
		      GTK_SIGNAL_FUNC (win), NULL);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
*/

}

