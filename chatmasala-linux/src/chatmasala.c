/* ChatMasala
 * Copyright (C) 2013 Vikram Fugro <vikram.fugro@gmail.com>
 *
 * chatmasala.c : main application
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

enum
{
  COL_ICON = 0,
  COL_TEXT,
  NUM_COLS
};


typedef struct tMsg tMsg;
typedef struct tClient tClient;
typedef struct sApp_s sApp_s;


struct tMsg
{
  gchar* msg;
  gchar* self; 
};


struct tClient
{
  gchar id[5];
  gchar* ip;
  gchar* name;
  GtkTreeIter iter;
  
  GtkWidget* window;
  GtkWidget* tview;
  GtkWidget* alias_window;
  gint unread;
  gboolean toggle_hint;

  GList* iMsgs;
};



struct sApp_s
{
  GtkListStore* listStore;
  GtkWidget* window;
  GtkWidget* treeView;
  GtkWidget* entry;
  GdkPixbuf* icon;

  gboolean alter_allowed;
  
  GSocket* lSocket;
  GIOChannel* lChannel;
  GList* clist;
  gint count;
};


static void update_cli (tClient*, tMsg*, GdkWindowState);
static void cleanup (tClient*);
static void add_to_listStore (tClient*);

/* GdkPixbuf RGBA C-Source image dump */
#ifdef __SUNPRO_C
#pragma align 4 (my_pixbuf)
#endif
#ifdef __GNUC__
static const guint8 my_pixbuf[] __attribute__ ((__aligned__ (4))) =
#else
static const guint8 my_pixbuf[] =
#endif
{ ""
  /* Pixbuf magic (0x47646b50) */
  "GdkP"
  /* length: header (24) + pixel_data (1024) */
  "\0\0\4\30"
  /* pixdata_type (0x1010002) */
  "\1\1\0\2"
  /* rowstride (64) */
  "\0\0\0@"
  /* width (16) */
  "\0\0\0\20"
  /* height (16) */
  "\0\0\0\20"
  /* pixel_data: */
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\12S\10\21\15U1G\0`\344\25"
  "\14UB\0\12Q\11\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0P\0l\376\345\265\353\377\344\256\352\377\344\250\352"
  "\377\343\246\350\377\342\243\350\377\341\237\347\377\204\0\262\377.\7"
  "^\214\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0B\3\211\0\264\377\333"
  "\224\344\377\332\220\343\377\333\212\344\377\332\206\344\377\326}\342"
  "\377\325y\340\377\324v\340\377\322u\337\377\321v\340\377\177\0\252\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\221\0\274\377\321q\337\377\320m\340"
  "\377\314i\335\377\315d\335\377\313Y\332\377\312W\332\377\310V\332\377"
  "\310S\332\377\310S\332\377\307S\331\377\232\0\303\377Z\0}\337\0\0\0\0"
  "\0\0\0\0~\0\250\377\304S\330\377\305P\330\377\304G\327\377\302B\330\377"
  "\300\77\326\377\300<\326\377\301:\327\377\2767\326\377\2773\326\377\275"
  "2\326\377\274-\325\377\274,\325\377\237\0\310\377\0\0\0\0\0\0\1\0\242"
  "\0\310\377\3003\326\377\274/\325\377\274-\325\377\272-\326\377\272&\325"
  "\377\266'\324\377\241\0\311\377\237\0\307\377\233\0\305\377\233\0\304"
  "\377\235\0\306\377\243\0\312\377\250\0\314\377\0\0\0\1\0\0\17\2\250\0"
  "\316\377\267\40\325\377\267\"\324\377\267\37\326\377\255\0\321\377\254"
  "\0\320\377\245\0\314\377\230\0\303\377k\5\230\377s\257\341\377b\252\337"
  "\377)F\216\377\227\0\302\377\245\0\314\377\0\0!\1\0\0\0\1\261\0\325\377"
  "\262\0\325\377\263\0\326\377\267\0\327\377\271\0\330\377\260\27\323\377"
  "\215\26\267\377\211\276\350\377\200\274\350\377w\270\350\377o\264\346"
  "\377i\257\346\377k\263\346\377\223\30\273\377\15\0\254\3\0\0\0\0\271"
  "\15\331\377\275\34\333\377\276!\335\377\300%\336\377\300,\335\377\252"
  ")\314\377&\226\342\3775\243\347\377+\235\347\377\36\233\346\377\15\232"
  "\347\377\0\227\350\377\0\227\346\377\0\207\343\377\0\0v\2\0\0\0\0\0\15"
  "M\15\3131\342\377\3154\343\377\316<\345\377\306;\341\377\210+\262\377"
  "\0\224\347\377\0\224\350\377\0\226\350\377\0\215\346\377\0\215\346\377"
  "\0\215\346\377\0\217\347\377\0\217\350\377\0\0\0\0\0\0\0\0\0\0\0\0\11"
  "\17U\31\305\12\346\377\323M\350\377\316J\343\377\2200\267\377\0\225\351"
  "\377\0\227\355\377\0\231\354\377\0\237\355\377\0\241\355\377\0\241\355"
  "\377\0\243\356\377\0\242\356\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\17\1\326D\354\377\323I\350\377\257-\322\377\0\243\361\377\0\256\361"
  "\377\0\271\364\3778\301\364\377D\303\364\377F\305\365\377K\305\366\377"
  "\0$Q\14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\3\17O\25\345o\361\377\325=\353"
  "\377\0\7H\10,\0\244\10\0\251\371\376S\311\367\377M\307\370\377`\320\372"
  "\377\1\221\353\367\0\27K\6\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\212"
  "\0\330\377.!p1\0\0\0\1\0\0\0\0\0\0""2\2^\307\367\377\0""9gg\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};


static sApp_s sApp, *app; 


static gint 
find_client (gconstpointer a, gconstpointer b)
{
  gchar* id = (gchar*) b;
  tClient* cli = (tClient*) a;
  GInetAddress* net = g_inet_address_new_from_string (id);

  if (net) {
    g_object_unref (net);
    return g_strcmp0 (id, cli->ip);
  } else {
    return g_strcmp0 (id, cli->id);
  }
}


static void
view_popup_menu_onChat (GtkWidget *menuitem, gpointer userdata)
{
  tClient* cli = userdata;
  update_cli (cli, NULL, 0);  
}


static void
view_popup_menu_onDetails (GtkWidget *menuitem, gpointer userdata)
{
  tClient* cli = userdata;
  GtkWidget* info;
  gint id = 0;  
  
  info = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, 
    GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
    "%s\n\nIP: %s", cli->name ? cli->name : "", cli->ip);  

  gtk_widget_show_all (info);
  gtk_widget_grab_focus (info);

  while (!(id == GTK_RESPONSE_CANCEL 
        || id == GTK_RESPONSE_OK 
        || id == GTK_RESPONSE_CLOSE
        || id == GTK_RESPONSE_DELETE_EVENT))
    id = gtk_dialog_run (GTK_DIALOG (info));

  gtk_widget_destroy (info);
}


static void
on_entry_activate (GtkEntry* entry, gpointer userdata)
{
  tClient* cli = userdata;

  if (cli) {
    GtkTextBuffer* buffer = NULL;
    GList* list = cli->iMsgs;
    GtkTextIter start, end;
    tMsg* msg;
    gchar* str;
    GdkWindowState state = GDK_WINDOW_STATE_WITHDRAWN;
      
    if (cli->window) {
      buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (cli->tview));
      state = gdk_window_get_state (cli->window->window);
    }      

    if (cli->name)
      g_free (cli->name);
    cli->name = g_strdup (gtk_entry_get_text (entry));
    gtk_entry_set_text (entry, "");

    str = cli->name;
    if (cli->name) {
      if (strlen (cli->name) == 0) {
        g_free (cli->name);
        cli->name = NULL;
        str = cli->ip;
      } 
    } else 
      str = cli->ip;

    if (buffer) {
      gtk_text_buffer_get_start_iter (buffer, &start);        
      gtk_text_buffer_get_end_iter (buffer, &end);
      gtk_text_buffer_delete (buffer, &start, &end);        
    }
    
    while (list) {
      msg = list->data;
      update_cli (cli, msg, state);
      list = g_list_next (list);
    }

    if (cli->window)
      gtk_window_set_title (GTK_WINDOW (cli->window), str);

    gtk_list_store_set(app->listStore, &cli->iter,
        COL_TEXT, str,
        -1);

    gtk_widget_destroy (cli->alias_window);
  
  } else if (entry == GTK_ENTRY (app->entry) && app->alter_allowed) {
    const gchar* text = gtk_entry_get_text (entry);
    GInetAddress* ip = g_inet_address_new_from_string (text);

    if (ip) {
      GList* cItem = g_list_find_custom (app->clist, text, find_client);

      if (!cItem) {
        tClient* cli = g_new0 (tClient, 1);

        cli->ip = g_strdup (text);
        app->clist = g_list_append (app->clist, cli);

        add_to_listStore (cli);
      }

      g_object_unref (ip);
    }
    
    gtk_entry_set_text (entry, "");
  
  } else {
    gtk_widget_grab_focus (GTK_WIDGET (app->entry));  
  } 
}


static void
entry_alias_quit (GtkWidget* widget, gpointer udata)
{
  tClient* cli = udata;
  cli->alias_window = NULL;

  app->alter_allowed = TRUE;
}


static void
view_popup_menu_onAlias (GtkWidget *menuitem, gpointer userdata)
{
  tClient* cli = userdata;
  GtkWidget* window, *vbox, *entry;
  gchar buf[50];

  sprintf (buf, "Set Alias for %s\n", cli->ip);
  
  cli->alias_window = window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (window), 350, 50);
  gtk_window_set_title (GTK_WINDOW (window), buf);
    
  vbox = gtk_vbox_new (FALSE, 0); 
  gtk_container_add (GTK_CONTAINER (window), vbox);    

  entry = gtk_entry_new ();
  g_signal_connect (G_OBJECT (entry), "activate", 
      G_CALLBACK (on_entry_activate), userdata);
  g_signal_connect (G_OBJECT (window), "destroy", 
      G_CALLBACK (entry_alias_quit), userdata);
  gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);

  app->alter_allowed = FALSE;
  gtk_widget_show_all (window);
}


static void
view_popup_menu_onRemove (GtkWidget *menuitem, gpointer userdata)
{
  tClient* cli = userdata;
  GtkTreeIter iter;
  GList* list;
  int i = 0;

  gtk_tree_model_get_iter_from_string (
    GTK_TREE_MODEL (app->listStore), &iter, cli->id);  
  gtk_list_store_remove (app->listStore, &iter);

  app->clist = g_list_remove (app->clist, cli);
  app->count--;
  
  cleanup (cli);
  g_free (cli);

  list = app->clist;
  while (list) {
    tClient* c = list->data;  
  
    sprintf (c->id, "%d", i);  
  
    list = g_list_next (list);
    i++;
  }

  g_assert (i == app->count);
}


static void
view_popup_menu_onCancel (GtkWidget *menuitem, gpointer userdata)
{
  tClient* cli = userdata;
}


static void
view_popup_menu (GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
{
  GtkWidget *menu, *menuitem;

  menu = gtk_menu_new();

  menuitem = gtk_menu_item_new_with_label("Chat");
  g_signal_connect(menuitem, "activate",
      (GCallback) view_popup_menu_onChat, userdata);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
  
  menuitem = gtk_menu_item_new_with_label("Details");
  g_signal_connect(menuitem, "activate",
      (GCallback) view_popup_menu_onDetails, userdata);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

  menuitem = gtk_menu_item_new_with_label("Rename (Alias)");
  g_signal_connect(menuitem, "activate",
      (GCallback) view_popup_menu_onAlias, userdata);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
  
  menuitem = gtk_menu_item_new_with_label("Remove");
  g_signal_connect(menuitem, "activate",
      (GCallback) view_popup_menu_onRemove, userdata);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
  
  menuitem = gtk_menu_item_new_with_label("Cancel");
  g_signal_connect(menuitem, "activate",
      (GCallback) view_popup_menu_onCancel, treeview);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

  gtk_widget_show_all(menu);

  gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
      (event != NULL) ? event->button : 0,
      gdk_event_get_time((GdkEvent*)event));
}



static gboolean
view_onButtonPressed (GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
{
  //printf ("button pressed %d %d\n", event->type == GDK_BUTTON_PRESS, event->button);
  if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3)
  {
    //g_print ("Single right click on the tree view.\n");

    if (app->alter_allowed)
    {
      GtkTreeSelection *selection;

      selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

      if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
      {
        GtkTreePath *path;        

        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview),
              (gint) event->x, 
              (gint) event->y,
              &path, NULL, NULL, NULL))
        {
          gchar *spath;
          GList* cItem;
          tClient* cli;
          GtkTreeIter iter;

          gtk_tree_selection_unselect_all(selection);
          gtk_tree_selection_select_path(selection, path);
          gtk_tree_model_get_iter (GTK_TREE_MODEL(app->listStore), &iter, path);
          spath = gtk_tree_path_to_string (path);

          cItem = g_list_find_custom (app->clist, spath, find_client);
          cli = cItem->data;
          cli->iter = iter; 

          g_free (spath);
          gtk_tree_path_free (path);
          view_popup_menu(treeview, event, cli);
        }
      }
    } 

    return TRUE;
  }

  return FALSE;
}



static void
view_onRowActivated (GtkTreeView *treeview,
    GtkTreePath        *path,
    GtkTreeViewColumn  *col,
    gpointer            userdata)
{
  GtkTreeModel *model;
  GtkTreeIter   iter;

  //g_print ("A row has been double-clicked!\n");

  model = gtk_tree_view_get_model(treeview);

  if (gtk_tree_model_get_iter(model, &iter, path))
  {
    GtkTreeSelection *selection;
    gchar* spath;
    GList* cItem;
    tClient* cli;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
    gtk_tree_selection_unselect_all (selection);
    gtk_tree_selection_select_path (selection, path);

    spath = gtk_tree_path_to_string (path);

    cItem = g_list_find_custom (app->clist, spath, find_client);
    cli = cItem->data;
    cli->iter = iter;

    g_free (spath);
    view_popup_menu_onChat (NULL, cli);
  }
}


static GtkWidget *
create_treeview (void)
{
  GtkTreeModel      *model;
  GtkTreeViewColumn *col;
  GtkCellRenderer   *renderer;
  GtkWidget         *view;

  app->listStore = gtk_list_store_new (2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
  model = GTK_TREE_MODEL (app->listStore);

  app->treeView = view = gtk_tree_view_new_with_model (model);

  g_signal_connect(view, "button-press-event", (GCallback) view_onButtonPressed, NULL);
  g_signal_connect(view, "row-activated", (GCallback) view_onRowActivated, NULL);

  col = gtk_tree_view_column_new ();
  gtk_tree_view_column_set_title (col, "Buddies");

  renderer = gtk_cell_renderer_pixbuf_new ();
  gtk_tree_view_column_pack_start (col, renderer, FALSE);
  gtk_tree_view_column_set_attributes (col, renderer,
      "pixbuf", COL_ICON, NULL);

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_column_pack_start (col, renderer, TRUE);
  gtk_tree_view_column_set_attributes (col, renderer,
      "text", COL_TEXT, NULL);
  
  gtk_tree_view_append_column (GTK_TREE_VIEW (view), col);

  gtk_widget_show_all (view);

  return view;
}



static void
func (gpointer data, gpointer udata)
{
  tClient* cli = data;

  if (cli->unread) {
    GtkTreeIter iter;

    gtk_tree_model_get_iter_from_string (
        GTK_TREE_MODEL (app->listStore), &iter, cli->id);

    if (cli->window) {
      const gchar* str = cli->name ? cli->name : cli->ip;
      gchar buf[20];
      gchar* title;

      sprintf (buf, " : %d unread", cli->unread);
      title = g_strconcat (str, buf, NULL);
      gtk_window_set_title (GTK_WINDOW (cli->window), title);
      g_free (title);

      gtk_window_set_urgency_hint (GTK_WINDOW (cli->window), cli->toggle_hint); 
    }

    gtk_list_store_set (app->listStore, &iter,
        COL_ICON, cli->toggle_hint ? app->icon : NULL,
        -1);

    cli->toggle_hint ^= 1;
  }
}


static gboolean
monitor (gpointer data)
{
  g_list_foreach (app->clist, func, NULL);

  return TRUE;
}


static void
freeMsgFunc (gpointer data)
{
  tMsg* msg = data;
  
  if (msg) {
    if (msg->self)
      g_free (msg->self);
    if (msg->msg)
      g_free (msg->msg);
    g_free (msg);
  }
}


static void
cleanup (tClient* cli)
{
  g_list_free_full (cli->iMsgs, freeMsgFunc);
  cli->iMsgs = NULL;
  if (cli->name)
    g_free (cli->name);
  cli->name = NULL;
  g_free (cli->ip);
  cli->ip = NULL;
  if (cli->window)
    gtk_widget_destroy (cli->window);
  cli->window = NULL;
  if (cli->alias_window)
    gtk_widget_destroy (cli->alias_window);
  cli->alias_window = NULL;
  cli->tview = NULL;
}


static void
freeCliFunc (gpointer data)
{
  tClient* cli = data;
  if (cli) {
    cleanup (cli);
    g_free (cli);
  }
}


static void
cli_cleanup (void)
{
  g_list_free_full (app->clist, freeCliFunc);
  app->clist = NULL;
}


static void
add_to_listStore (tClient* cli)
{
  GtkTreeIter iter;

  gtk_list_store_append (app->listStore, &iter);
  gtk_list_store_set (app->listStore, &iter,
      COL_ICON, app->icon,
      COL_TEXT, cli->ip,
      -1);

  sprintf (cli->id, "%d", app->count++);
}


static gboolean 
cli_window_quit (GtkWidget *widget,
    GdkEvent  *event,
    gpointer   data )
{
  tClient* cli = data;

  //g_print ("delete event occurred\n");
  update_cli (cli, NULL, GDK_WINDOW_STATE_WITHDRAWN);

  return (TRUE);
}


static gboolean
send_message (GSocket* sock, tMsg* msg)
{
  gboolean ret = FALSE;
  gint toSend = 0, rt;
  gchar buf[12];
  gchar* message = NULL, *m;    

  sprintf (buf, "!chat!%05u", (guint) strlen (msg->msg));
  m = message = g_strconcat (buf, msg->msg, NULL);
  toSend = strlen (message);

  while (toSend > 0) {
    rt = g_socket_send (sock, m, toSend, NULL, NULL);
    
    if (rt == 0) {
      g_socket_shutdown (sock, TRUE, TRUE, NULL);
      break; 
    } else if (rt < 0) {
      break;
    }

    m += rt;
    toSend -= rt; 
  }

  ret = !!!toSend;

done:
  if (message)
    g_free (message);
  return ret;
}



static gboolean 
on_key_press (GtkWidget * widget, GdkEventKey* rKey, gpointer userdata) 
{
  tClient* cli = userdata;

  if (rKey->type == GDK_KEY_PRESS) {
    //g_print("%x\n", rKey->keyval);

    switch (rKey->keyval)
    {
      case GDK_KEY_Return: {
        GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widget));
        gchar* text; 
        GInetAddress *ip;
        GtkTextIter start, end;
          
        gtk_text_buffer_get_start_iter (buffer, &start);        
        gtk_text_buffer_get_end_iter (buffer, &end);
        text = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
        gtk_text_buffer_delete (buffer, &start, &end);        

        if (text && strlen (text) > 0) {
          if (cli) { 
            GSocketAddress *address;
            tMsg* msg;
            GSocket* sock;

            msg = g_new0 (tMsg, 1);
            msg->msg = text;

            ip = g_inet_address_new_from_string (cli->ip);
            address = g_inet_socket_address_new (ip, 5231);
            g_object_unref (ip);
            sock = g_socket_new (G_SOCKET_FAMILY_IPV4,
                G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL);
  
            g_socket_set_timeout (sock, 2);  

            if (g_socket_connect (sock, address, NULL, NULL)) {
              if (!send_message (sock, msg))
                msg->self = g_strdup ("me (failed to deliver)");
              else
                msg->self = g_strdup ("me");
            } else {
              msg->self = g_strdup ("me (failed to deliver)");
            }

            g_object_unref (address);
              
            //g_print ("got message %s\n", msg->msg);
            g_socket_close (sock, NULL);
            g_object_unref (sock);

            cli->iMsgs = g_list_append (cli->iMsgs, msg);  
            update_cli (cli, msg, gdk_window_get_state (cli->window->window));
          }
        } else if (text) {
          g_free (text);
        }
        return TRUE; 
      }
      break;
    }
  }

  return FALSE;
}


static gboolean
window_state_func (GtkWidget* widget, GdkEventWindowState *event, gpointer udata)
{
  tClient* cli = udata;
  gboolean notified = !(event->new_window_state & GDK_WINDOW_STATE_ICONIFIED
      || event->new_window_state & GDK_WINDOW_STATE_WITHDRAWN 
      || event->new_window_state & GDK_WINDOW_STATE_BELOW) && cli->unread;

  //printf ("@@: %d\n", event->new_window_state & GDK_WINDOW_STATE_BELOW);

  if (notified) {
    GtkTreeIter iter;

    gtk_tree_model_get_iter_from_string (
        GTK_TREE_MODEL (app->listStore), &iter, cli->id);
  
    gtk_window_set_title (GTK_WINDOW (widget), cli->name ? cli->name : cli->ip);
    gtk_window_set_urgency_hint (GTK_WINDOW (widget), FALSE);
    gtk_list_store_set (app->listStore, &iter,
        COL_ICON, app->icon,
        -1);

    cli->unread = 0;
  }

  return FALSE;
}


static void
update_cli (tClient* cli, tMsg* msg, GdkWindowState state)
{
  GList* list;

  if (G_UNLIKELY (cli->window == NULL)) {
    GtkWidget *text_view, *swindow;
    GtkWidget *vbox;
    GdkColor color;

    cli->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW (cli->window), 600, 420);
    gtk_window_set_title (GTK_WINDOW (cli->window), cli->ip);
    g_signal_connect(cli->window, "delete_event", G_CALLBACK (cli_window_quit), cli);
    gtk_container_set_border_width (GTK_CONTAINER (cli->window), 2);

    vbox = gtk_vbox_new (FALSE, 10); 
    gtk_container_add (GTK_CONTAINER (cli->window), vbox);    
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);

    swindow = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_size_request (swindow, -1, 370);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
        GTK_POLICY_NEVER,
        GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (vbox), swindow, TRUE, TRUE, 0);

    text_view = gtk_text_view_new ();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (text_view), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (text_view), FALSE);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text_view), GTK_WRAP_WORD);
    gtk_container_add (GTK_CONTAINER (swindow), text_view);
    cli->tview = text_view;

    text_view = gtk_text_view_new ();
    gtk_widget_set_size_request (text_view, -1, 30);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text_view), GTK_WRAP_CHAR);
    gtk_box_pack_start (GTK_BOX (vbox), text_view, TRUE, TRUE, 0);
    gdk_color_parse ("lightblue", &color);
    gtk_widget_modify_base (text_view, GTK_STATE_NORMAL, &color);  
    g_signal_connect (text_view, "key_press_event", G_CALLBACK (on_key_press), cli);
    gtk_widget_grab_focus (text_view); 

    g_signal_connect (G_OBJECT (cli->window), "window-state-event", 
        G_CALLBACK (window_state_func), cli);
  }

  if (msg) {
    GtkTextBuffer* buffer;
    GtkTextIter iter, start, end;
    GtkTextTag* tag;
    gint offset, rOffset, ofs = 0;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (cli->tview));

    gtk_text_buffer_get_end_iter (buffer, &iter);

    if (msg->self) {
      gtk_text_buffer_insert (buffer, &iter, msg->self, -1); 
      offset = strlen (msg->self);
    } else if (cli->name) {
      gtk_text_buffer_insert (buffer, &iter, cli->name, -1); 
      offset = strlen (cli->name);
      ofs = 11;
    } else {
      gtk_text_buffer_insert (buffer, &iter, cli->ip, -1); 
      offset = strlen (cli->ip);
      ofs = 11;
    }
      
    gtk_text_buffer_insert (buffer, &iter, " :  ", -1); 
    offset += 4;   
    
    tag = gtk_text_buffer_create_tag (buffer, NULL,
                        "foreground", "black", NULL);
    rOffset = gtk_text_iter_get_offset  (&iter);
    gtk_text_buffer_get_iter_at_offset (buffer, &start, rOffset - offset);
    gtk_text_buffer_get_iter_at_offset (buffer, &end, rOffset);
    gtk_text_buffer_apply_tag (buffer, tag, &start, &end);
    //g_object_unref (tag);

    offset = strlen (msg->msg) - ofs;
    gtk_text_buffer_insert (buffer, &iter, msg->msg + ofs, -1); 
    rOffset = gtk_text_iter_get_offset  (&iter);   

    if (msg->self)
      tag = gtk_text_buffer_create_tag (buffer, NULL,
                        "foreground", "blue", NULL);
    else
      tag = gtk_text_buffer_create_tag (buffer, NULL,
                        "foreground", "purple", NULL);
    rOffset = gtk_text_iter_get_offset  (&iter);
    gtk_text_buffer_get_iter_at_offset (buffer, &start, rOffset - offset);
    gtk_text_buffer_get_iter_at_offset (buffer, &end, rOffset);
    gtk_text_buffer_apply_tag (buffer, tag, &start, &end);
    //g_object_unref (tag);

    gtk_text_buffer_insert (buffer, &iter, "\n", -1);
    gtk_text_buffer_insert (buffer, &iter, "\n", -1);
    //gtk_text_buffer_get_end_iter (buffer, &iter);
    gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (cli->tview), &iter, 0.0, TRUE, 0.0, 0.0);
  }

  if (cli->window) {
    if (state & GDK_WINDOW_STATE_ICONIFIED) {
      gtk_window_iconify (GTK_WINDOW (cli->window));
    } else {
      gtk_window_deiconify (GTK_WINDOW (cli->window));
    }
    
    if (state & GDK_WINDOW_STATE_WITHDRAWN) {
      gtk_widget_hide_all (cli->window); 
      
    } else {
      gtk_widget_show_all (cli->window); 
    }
  }
}


static tMsg*
recv_message (GSocket* sock)
{
  gchar buffer [2048];
  gint recv = g_socket_receive (sock, buffer, 11, NULL, NULL);
  tMsg* msg = NULL; 
  GByteArray* iBuf = NULL;  
  gint iLen = 0;  

  if (recv == 11) {
    if (!strncmp (buffer, "!chat!", 6)) {
      iLen = atoi (buffer + 6);        
    } else { 
      goto done;
    }
  } else {
    goto done;
  }

  iBuf = g_byte_array_new ();
  iBuf = g_byte_array_append (iBuf, buffer, recv);

  while (1) {
    recv = g_socket_receive (sock, buffer, 2048, NULL, NULL);

    if (recv < 0) {
      break; 
    } else if (recv == 0) {
      g_socket_shutdown (sock, TRUE, TRUE, NULL);
      break;
    }

    iBuf = g_byte_array_append (iBuf, buffer, recv);

    if (iLen + 11 == iBuf->len) {
      msg = g_new0 (tMsg, 1);

      buffer[0] = '\0';
      iBuf = g_byte_array_append  (iBuf, buffer, 1);

      msg->self = NULL;
      msg->msg = g_strdup (iBuf->data);
    }
  }

done:
  if (iBuf)
    g_byte_array_unref (iBuf);
  return msg;
}


static gboolean
accept_connections (GIOChannel* iochannel, GIOCondition condition, gpointer data)
{
  if (condition & G_IO_IN) {
    GSocket* sock;
    GSocketAddress* addr;
    GInetAddress* iaddr;        
    gchar* ip;
    tClient* cli;
    GList* cItem;
    tMsg* msg;

    sock = g_socket_accept (app->lSocket, NULL, NULL);
    addr = g_socket_get_remote_address (sock, NULL);
    iaddr = g_inet_socket_address_get_address ((GInetSocketAddress*) addr);        
    ip = g_inet_address_to_string (iaddr);
    g_object_unref (addr);
   
    //g_print ("got a connection from %s\n", ip);

    cItem = g_list_find_custom (app->clist, ip, find_client);
    
    if (!cItem) {
      cli = g_new0 (tClient, 1);
      
      cli->ip = g_strdup (ip);
      app->clist = g_list_append (app->clist, cli);

      add_to_listStore (cli);
    } else {
      cli = (tClient*) cItem->data;
    }

    
    if ((msg = recv_message (sock))) {
      GdkWindowState state = GDK_WINDOW_STATE_ICONIFIED;
      //g_print ("got message %s\n", msg->msg);
      
      if (G_LIKELY (cli->window)) {
        state = gdk_window_get_state (cli->window->window);
        if (state & GDK_WINDOW_STATE_WITHDRAWN) {
          state &= ~GDK_WINDOW_STATE_WITHDRAWN;
          state |= GDK_WINDOW_STATE_ICONIFIED;
        }
      }
      
      if (state & GDK_WINDOW_STATE_ICONIFIED ||
          state & GDK_WINDOW_STATE_BELOW) {
        cli->unread++;
      }

      cli->iMsgs = g_list_append (cli->iMsgs, msg); 
        
      update_cli (cli, msg, state);
    }
     
    g_socket_close (sock, NULL);
    g_object_unref (sock);
    g_free (ip);
  } 

  return TRUE;
}


static void
about_clicked (GtkButton* button, gpointer data)
{
  GtkAboutDialog* about;
  gint id = 0;
  const gchar* author[] = {"Vikram F \"cotigao\" <vikram.fugro@gmail.com>", NULL};

  about = (GtkAboutDialog*) gtk_about_dialog_new ();
  gtk_about_dialog_set_program_name (about, "Chat Masala");
  gtk_about_dialog_set_version (about, "v0.1");
  gtk_about_dialog_set_authors (about, author);
  gtk_about_dialog_set_comments (about, "Papdi Chat!");

  gtk_widget_show_all (GTK_WIDGET (about));
  gtk_widget_grab_focus (GTK_WIDGET (about));

  while (!(id == GTK_RESPONSE_CANCEL 
        || id == GTK_RESPONSE_OK 
        || id == GTK_RESPONSE_CLOSE
        || id == GTK_RESPONSE_DELETE_EVENT))
    id = gtk_dialog_run (GTK_DIALOG (about));

  gtk_widget_destroy (GTK_WIDGET (about));
}


static void
add_ip_clicked (GtkButton* button, gpointer data)
{
  if (app->alter_allowed)
    on_entry_activate (GTK_ENTRY (app->entry), NULL);
}


int
main (int argc, char **argv)
{
  GtkWidget *window, *view, *swindow;
  GtkWidget* vbox, *button, *hbox;
  GtkWidget *align, *entry;
  GInetAddress *inet_address;
  GSocketAddress *addr;
  GError* err = NULL;
  gint fd;

  app = &sApp;
  gtk_init(&argc, &argv);
  memset (app, 0, sizeof (sApp_s)); 

  app->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (app->window), 200, 500);
  gtk_window_set_title (GTK_WINDOW (app->window), "Chat Masala");
  g_signal_connect(app->window, "destroy", gtk_main_quit, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (app->window), 2);

  vbox = gtk_vbox_new (FALSE, 3);
  gtk_container_add (GTK_CONTAINER(app->window), vbox);

  button = gtk_button_new_with_label ("");
  gtk_widget_set_size_request (button, 55, 20);
  gtk_label_set_markup (GTK_LABEL (GTK_BIN(button)->child), "<span font_desc=\"7.0\">About</span>");
  gtk_label_set_use_markup (GTK_LABEL(GTK_BIN(button)->child), TRUE);
  g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK (about_clicked), NULL);

  align = gtk_alignment_new (0, 0, 0, 0);
  gtk_container_add (GTK_CONTAINER(align), button);

  button = gtk_button_new_with_label ("");
  gtk_widget_set_size_request (button, 55, 30);
  gtk_label_set_use_markup (GTK_LABEL(GTK_BIN(button)->child), TRUE);
  gtk_label_set_markup (GTK_LABEL (GTK_BIN(button)->child), "<span font_desc=\"10.0\">Add IP</span>");
  g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK (add_ip_clicked), NULL);

  entry = gtk_entry_new ();
  gtk_widget_set_size_request (entry, 135, 30);
  g_signal_connect (G_OBJECT (entry), "activate", G_CALLBACK (on_entry_activate), NULL);
  app->entry = entry;

  hbox = gtk_hbox_new (FALSE, 0);  
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 3);  

#if 0
  label = gtk_label_new ("");
  gtk_widget_set_size_request (label, 55, 30);
  gtk_label_set_use_markup (GTK_LABEL(label), TRUE);
  gtk_label_set_markup (GTK_LABEL (label), "<span font_desc=\"10.0\">Identifier:</span>");

  entry = gtk_entry_new ();
  gtk_widget_set_size_request (entry, 135, 30);
  g_signal_connect (G_OBJECT (entry), "activate", G_CALLBACK (on_entry_activate), NULL);
  app->entry2 = entry;

  hbox2 = gtk_hbox_new (FALSE, 0);  
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox2), entry, TRUE, TRUE, 3);  
#endif

  view = create_treeview ();
  swindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
      GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add (GTK_CONTAINER (swindow), view);

  gtk_box_pack_start (GTK_BOX (vbox), align, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), swindow, TRUE, TRUE, 0);

  app->lSocket = g_socket_new (G_SOCKET_FAMILY_IPV4, 
      G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL);
  inet_address = g_inet_address_new_any (G_SOCKET_FAMILY_IPV4);
  addr = g_inet_socket_address_new (inet_address, 5231);
  g_object_unref (inet_address);
  g_socket_bind (app->lSocket, addr, TRUE, NULL);
  g_object_unref (addr);
  g_socket_listen (app->lSocket, NULL);
  fd = g_socket_get_fd (app->lSocket);
  app->lChannel = g_io_channel_unix_new (fd);
  g_io_add_watch (app->lChannel, G_IO_IN | G_IO_HUP, accept_connections, NULL);
  g_io_channel_set_close_on_unref (app->lChannel, FALSE);

  app->icon = gdk_pixbuf_new_from_inline (-1, my_pixbuf, FALSE, NULL);
  g_timeout_add (500, monitor, NULL); 
  gtk_widget_show_all (app->window);
  app->alter_allowed = TRUE;
  gtk_widget_grab_focus (app->entry); 

  gtk_main();
    
  g_object_unref (app->icon); 
 
  cli_cleanup ();
  g_io_channel_unref (app->lChannel);  
  g_socket_close (app->lSocket, NULL);
  g_object_unref (app->lSocket);

  return 0;
}

