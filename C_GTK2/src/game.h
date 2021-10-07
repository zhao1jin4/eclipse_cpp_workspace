
/* GTK - GIMP工具包
 * 版权 (C) 1995-1997 Peter Mattis, Spencer Kimball 和 Josh MacDonald 所有
 *
 * 本程序是自由软件。你可以在自由软件基金发布的 GNU GPL 的条款下重新分发
 * 或修改它。GPL 可以使用版本 2 或(由你选择)任何随后的版本。
 *
 * 本程序分发的目的是它可能对其他人有用，但不提供任何的担保，包括隐含的
 * 和适合特定用途的保证。请查阅GNU通用公共许可证获得详细的信息。
 *
 * 你应该已经随该软件一起收到一份GNU通用公共许可。如果还没有，请写信给
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__


#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TICTACTOE(obj)          GTK_CHECK_CAST (obj, tictactoe_get_type (), Tictactoe)
#define TICTACTOE_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, tictactoe_get_type (), TictactoeClass)
#define IS_TICTACTOE(obj)       GTK_CHECK_TYPE (obj, tictactoe_get_type ())


typedef struct _Tictactoe       Tictactoe;
typedef struct _TictactoeClass  TictactoeClass;

struct _Tictactoe
{
  GtkVBox vbox;

  GtkWidget *buttons[3][3];
};

struct _TictactoeClass
{
  GtkVBoxClass parent_class;

  void (* tictactoe) (Tictactoe *ttt);
};

GtkType        tictactoe_get_type        (void);
GtkWidget*     tictactoe_new             (void);
void	       tictactoe_clear           (Tictactoe *ttt);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TICTACTOE_H__ */


GtkType
tictactoe_get_type ()
{
  static guint ttt_type = 0;

  if (!ttt_type)
    {
      GtkTypeInfo ttt_info =
      {
	"Tictactoe",
	sizeof (Tictactoe),
	sizeof (TictactoeClass),
	(GtkClassInitFunc) tictactoe_class_init,
	(GtkObjectInitFunc) tictactoe_init,
	(GtkArgSetFunc) NULL,
        (GtkArgGetFunc) NULL
      };

      ttt_type = gtk_type_unique (gtk_vbox_get_type (), &ttt_info);
    }

  return ttt_type;
}


struct _GtkTypeInfo
{
  gchar *type_name;
  guint object_size;
  guint class_size;
  GtkClassInitFunc class_init_func;
  GtkObjectInitFunc object_init_func;
  GtkArgSetFunc arg_set_func;
  GtkArgGetFunc arg_get_func;
};

enum {
  TICTACTOE_SIGNAL,
  LAST_SIGNAL
};


static gint tictactoe_signals[LAST_SIGNAL] = { 0 };



gint gtk_signal_new( const gchar         *name,
                     GtkSignalRunType     run_type,
                     GtkType              object_type,
                     gint                 function_offset,
                     GtkSignalMarshaller  marshaller,
                     GtkType              return_val,
                     guint                nparams,
                     ...);



typedef enum
{
  GTK_TYPE_INVALID,
  GTK_TYPE_NONE,
  GTK_TYPE_CHAR,
  GTK_TYPE_BOOL,
  GTK_TYPE_INT,
  GTK_TYPE_UINT,
  GTK_TYPE_LONG,
  GTK_TYPE_ULONG,
  GTK_TYPE_FLOAT,
  GTK_TYPE_DOUBLE,
  GTK_TYPE_STRING,
  GTK_TYPE_ENUM,
  GTK_TYPE_FLAGS,
  GTK_TYPE_BOXED,
  GTK_TYPE_FOREIGN,
  GTK_TYPE_CALLBACK,
  GTK_TYPE_ARGS,

  GTK_TYPE_POINTER,

  /* 如果下面两个最终能被删除就好了。*/
  GTK_TYPE_SIGNAL,
  GTK_TYPE_C_CALLBACK,

  GTK_TYPE_OBJECT

} GtkFundamentalType;


static void
tictactoe_init (Tictactoe *ttt)
{
  GtkWidget *table;
  gint i,j;

  table = gtk_table_new (3, 3, TRUE);
  gtk_container_add (GTK_CONTAINER(ttt), table);
  gtk_widget_show (table);

  for (i=0;i<3; i++)
    for (j=0;j<3; j++)
      {
	ttt->buttons[i][j] = gtk_toggle_button_new ();
	gtk_table_attach_defaults (GTK_TABLE(table), ttt->buttons[i][j],
				   i, i+1, j, j+1);
	gtk_signal_connect (GTK_OBJECT (ttt->buttons[i][j]), "toggled",
			    GTK_SIGNAL_FUNC (tictactoe_toggle), ttt);
	gtk_widget_set_size_request (ttt->buttons[i][j], 20, 20);
	gtk_widget_show (ttt->buttons[i][j]);
      }
}


GtkWidget*
tictactoe_new ()
{
  return GTK_WIDGET ( gtk_type_new (tictactoe_get_type ()));
}

void
tictactoe_clear (Tictactoe *ttt)
{
  int i,j;

  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      {
	gtk_signal_handler_block_by_data (GTK_OBJECT(ttt->buttons[i][j]), ttt);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (ttt->buttons[i][j]),
				     FALSE);
	gtk_signal_handler_unblock_by_data (GTK_OBJECT(ttt->buttons[i][j]), ttt);
      }
}

static void
tictactoe_toggle (GtkWidget *widget, Tictactoe *ttt)
{
  int i,k;

  static int rwins[8][3] = { { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 } };
  static int cwins[8][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 2, 1, 0 } };

  int success, found;

  for (k=0; k<8; k++)
    {
      success = TRUE;
      found = FALSE;

      for (i=0;i<3;i++)
	{
	  success = success &&
	    GTK_TOGGLE_BUTTON(ttt->buttons[rwins[k][i]][cwins[k][i]])->active;
	  found = found ||
	    ttt->buttons[rwins[k][i]][cwins[k][i]] == widget;
	}

      if (success && found)
	{
	  gtk_signal_emit (GTK_OBJECT (ttt),
			   tictactoe_signals[TICTACTOE_SIGNAL]);
	  break;
	}
    }
}
