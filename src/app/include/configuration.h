#pragma once
#include <QtCore>
#include <QSettings>

class configuration {
    private:
        static QSettings *settings;

    public:

        static        void        Init( )                               { configuration::settings = new QSettings();             }
        static    QVariant        read( QString key, QVariant def_val ) { return configuration::settings->value( key, def_val ); }
        static        void       write( QString key, QVariant val )     { configuration::settings->setValue( key, val );         }
        static   QSettings     *master( )                               { return settings;                             }


    class  UI {
        public:
            static QString      getKey( QString k ) { return UI() + "/" + k;  }
          operator QString            (           ) { return "UI";            }

            static int control_buttons_size( ) { return read( getKey( "control_buttons_size" ),  36).toInt(); }
            static void control_buttons_size( const QVariant &val ) { write( getKey( "control_buttons_size" ), val); }

            static  int width( ) { return read( getKey( "width" ), 200 ).toInt(); }
            static void width( const QVariant &val ) { write( getKey( "width" ), val); }

            static  int min_width( ) { return read( getKey( "min_width" ), 160 ).toInt(); }
            static void min_width( const QVariant &val ) { write( getKey( "min_width" ), val); }

            static  int max_width( ) { return read( getKey( "max_width" ), 400 ).toInt(); }
            static void max_width( const QVariant &val ) { write( getKey( "max_width" ), val); }

            static  int min_control_buttons_width( ) { return read( getKey( "min_control_buttons_width" ), 24 ).toInt(); }
            static void min_control_buttons_width( const QVariant &val ) { write( getKey( "min_control_buttons_width" ), val); }

            static  int max_control_buttons_width( ) { return read( getKey( "max_control_buttons_width" ), 64 ).toInt(); }
            static void max_control_buttons_width( const QVariant &val ) { write( getKey( "max_control_buttons_width" ), val); }

            static  int opacity( ) { return read( getKey( "opacity" ), 100 ).toInt(); }
            static void opacity( const QVariant &val ) { write( getKey( "opacity" ), val); }
    };


    class Application {
        public:
            static QString      getKey( QString k ) { return Application() + "/" + k; }
          operator QString            (           ) { return "Application";           }

            static QString  plugins_directory( ) { return read( getKey( "plugins_directory" ), "plugins" ).toString().toLower(); }
            static    void  plugins_directory( const QVariant &val ) { write( getKey("plugins_directory"), val); }

            static QString   themes_directory( ) { return read( getKey( "themes_directory"  ), "themes" ).toString().toLower(); }
            static    void   themes_directory( const QVariant &val ) { write( getKey("themes_directory" ), val); }

            static QString         theme_name( ) { return read( getKey( "theme_name" ), "default.qss" ).toString().toLower(); }
            static    void         theme_name( const QVariant &val ) { write( getKey("theme_name" ), val); }

            static     int    virtual_desktop( ) { return read( getKey( "virtual_desktop"), 0 ).toInt (); }
            static    void    virtual_desktop( const QVariant &val ) { write( getKey( "virtual_desktop"), val ); }

            static QString position_on_screen( ) { return read( getKey("position_on_screen"), "right").toString().toLower(); }
            static    void position_on_screen( const QVariant &val ) { write( getKey("position_on_screen"), val); }
    };


    class Plugins     {
        public:
            static QString      getKey( QString k ) { return k;           }
          operator QString            (           ) { return "Plugins";   }

            static QString        uuid( ) { return read( getKey( "uuid"        ), QVariant()    ).toString().toLower(); }
            static QString   file_name( ) { return read( getKey( "file_name"   ), QVariant()    ).toString().toLower(); }

            static    void        uuid( const QVariant &val ) { write( getKey(    "uuid"        ), val     ); }
            static    void   file_name( const QVariant &val ) { write( getKey(    "file_name"   ), val     ); }
    };
};
